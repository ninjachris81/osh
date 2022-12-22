package com.osh.doorunlock;

import com.osh.user.User;

public interface IDoorUnlockManager {

    void requestChallenge(String userId);

    void requestChallenge(User user);

    void setCallbackListener(CallbackListener listener);

    public interface CallbackListener {

        void onAuthSuccess();

        void onAuthFailure();

    }
}
