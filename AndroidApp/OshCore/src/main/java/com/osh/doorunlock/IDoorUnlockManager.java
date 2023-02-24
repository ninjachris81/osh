package com.osh.doorunlock;

import com.osh.manager.IMqttSupport;
import com.osh.user.User;

public interface IDoorUnlockManager extends IMqttSupport {

    void requestChallenge(String userId, String doorId);

    void requestChallenge(User user, String doorId);

    void setCallbackListener(CallbackListener listener);

    public interface CallbackListener {

        void onAuthSuccess();

        void onAuthFailure();

    }
}
