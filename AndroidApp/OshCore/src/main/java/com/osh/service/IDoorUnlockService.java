package com.osh.service;

import com.osh.manager.IMqttSupport;
import com.osh.user.User;

public interface IDoorUnlockService extends IMqttSupport {

    void requestChallenge(String userId, String doorId);

    void requestChallenge(User user, String doorId);

    void setCallbackListener(CallbackListener listener);

    public interface CallbackListener {

        void onAuthSuccess();

        void onAuthFailure();

    }
}
