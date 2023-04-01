package com.osh.service.impl;

import android.util.Base64;

import com.osh.communication.MessageBase;
import com.osh.doorunlock.DoorUnlockMessage;
import com.osh.service.ICommunicationService;
import com.osh.log.LogFacade;
import com.osh.service.IDoorUnlockService;
import com.osh.user.User;

import org.apache.commons.lang3.StringUtils;

import java.nio.charset.Charset;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Map;

public class DoorUnlockServiceImpl implements IDoorUnlockService {

    private static final String TAG = DoorUnlockServiceImpl.class.getName();

    private static final String PSK = "q7XtfMBWAmKYWUekFPxS";

    private ICommunicationService communicationManager;

    private CallbackListener callbackListener;

    public DoorUnlockServiceImpl(ICommunicationService communicationManager) {
        this.communicationManager = communicationManager;
        communicationManager.registerMessageType(MessageBase.MESSAGE_TYPE.MESSAGE_TYPE_DOOR_UNLOCK, this);
    }

    @Override
    public void setCallbackListener(CallbackListener callbackListener) {
        this.callbackListener = callbackListener;
    }

    @Override
    public MessageBase.MESSAGE_TYPE getMessageType() {
        return MessageBase.MESSAGE_TYPE.MESSAGE_TYPE_DOOR_UNLOCK;
    }

        @Override
    public void handleReceivedMessage(MessageBase msg) {
        if (msg instanceof DoorUnlockMessage) {
            DoorUnlockMessage dum = (DoorUnlockMessage) msg;
            if (dum.getValues().containsKey(DoorUnlockMessage.DU_ATTRIB_STAGE)) {
                DoorUnlockMessage.DU_AUTH_STAGE stage = DoorUnlockMessage.DU_AUTH_STAGE.values()[(int) dum.getValues().get(DoorUnlockMessage.DU_ATTRIB_STAGE)];

                switch (stage) {
                    case CHALLENGE_CREATED:
                        String oth = (String) dum.getValues().get(DoorUnlockMessage.DU_ATTRIB_OTH);
                        Long ts = (Long) dum.getValues().get(DoorUnlockMessage.DU_ATTRIB_TS);

                        if (!StringUtils.isEmpty(oth)) {
                            if (ts != null) {
                                respondChallenge(dum.getUserId(), dum.getDoorId(), ts, oth);
                            } else {
                                LogFacade.w(TAG,"TS cannot be empty");
                            }
                        } else {
                            LogFacade.w(TAG,"OTH cannot be empty");
                        }
                        break;
                    case CHALLENGE_SUCCESS:
                        LogFacade.i(TAG, "Auth Success");
                        if (callbackListener != null) {
                            callbackListener.onAuthSuccess();
                        }
                        break;
                    case CHALLENGE_FAILURE:
                        LogFacade.w(TAG, "Auth Failure");
                        if (callbackListener != null) {
                            callbackListener.onAuthFailure();
                        }
                        break;
                }
            }
        }
    }

    private String calculateChallenge(String userId, String doorId, long timestamp, String oth) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-1");

            md.update(String.valueOf(timestamp).getBytes(Charset.forName("ISO-8859-1")));       // Latin1
            md.update(oth.getBytes(Charset.forName("ISO-8859-1")));
            md.update(userId.getBytes(Charset.forName("ISO-8859-1")));
            md.update(PSK.getBytes(Charset.forName("ISO-8859-1")));
            md.update(doorId.getBytes(Charset.forName("ISO-8859-1")));

            return Base64.encodeToString(md.digest(), Base64.NO_WRAP);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }

        return null;
    }

    private void respondChallenge(String userId, String doorId, long ts, String oth) {
        String resultHash = calculateChallenge(userId, doorId, ts, oth);

        LogFacade.d(TAG, resultHash);

        if (resultHash != null) {
            DoorUnlockMessage msg = new DoorUnlockMessage(userId, doorId, Map.of(
                    DoorUnlockMessage.DU_ATTRIB_STAGE, DoorUnlockMessage.DU_AUTH_STAGE.CHALLENGE_CALCULATED.ordinal(),
                    DoorUnlockMessage.DU_ATTRIB_OTH, oth,
                    DoorUnlockMessage.DU_ATTRIB_TS, ts,
                    DoorUnlockMessage.DU_ATTRIB_RESULT_HASH, resultHash
                    ));
            communicationManager.sendMessage(msg);
        } else {
            LogFacade.w(TAG, "Error while calculating result hash");
        }
    }

    @Override
    public void requestChallenge(String userId, String doorId) {
        DoorUnlockMessage msg = new DoorUnlockMessage(userId, doorId, Map.of(DoorUnlockMessage.DU_ATTRIB_STAGE, DoorUnlockMessage.DU_AUTH_STAGE.CHALLENGE_REQUEST.ordinal()));
        communicationManager.sendMessage(msg);
    }

    @Override
    public void requestChallenge(User user, String doorId) {
        requestChallenge(user.getId(), doorId);
    }
}
