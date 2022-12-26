package com.osh;

import static android.widget.Toast.*;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;

import androidx.biometric.BiometricManager;
import androidx.biometric.BiometricPrompt;
import androidx.core.content.ContextCompat;

import android.nfc.NdefMessage;
import android.nfc.NfcAdapter;
import android.os.Bundle;
import android.os.Parcelable;
import android.util.Log;

import com.osh.doorunlock.IDoorUnlockManager;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.math.NumberUtils;

import java.util.concurrent.Executor;

import javax.inject.Inject;

import dagger.hilt.android.AndroidEntryPoint;

@AndroidEntryPoint
public class DoorOpenActivity extends AppCompatActivity implements IDoorUnlockManager.CallbackListener {

    public static final String DU_EXTRA_DOOR_ID = "doorId";
    private static final String TAG = DoorOpenActivity.class.getName();

    public static final String REQUEST_DOOR_UNLOCK_CHALLENGE_INTENT = "com.osh.action.requestDoorUnlockChallenge";

    @Inject
    IDoorUnlockManager doorUnlockManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_door_open);
        handleIntent(getIntent());

        doorUnlockManager.setCallbackListener(this);
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        handleIntent(intent);
    }

    private void handleIntent(Intent intent) {
        if (NfcAdapter.ACTION_NDEF_DISCOVERED.equals(intent.getAction())) {
            Parcelable[] rawMessages =
                    intent.getParcelableArrayExtra(NfcAdapter.EXTRA_NDEF_MESSAGES);
            if (rawMessages != null) {
                NdefMessage[] messages = new NdefMessage[rawMessages.length];

                Log.i(TAG, "Messages: " + rawMessages.length);

                for (int i = 0; i < rawMessages.length; i++) {
                    messages[i] = (NdefMessage) rawMessages[i];

                    if (messages[i].getRecords().length == 1) {
                        String data = new String(messages[i].getRecords()[0].getPayload());

                        if (!StringUtils.isEmpty(data)) {
                            Log.i(TAG, "Requesting challenge");
                            executeAuth(data);
                        } else {
                            Log.w(TAG, "No doorid defined");
                        }
                        Log.i(TAG, data);
                    } else {
                        Log.w(TAG, "Invalid record size");
                    }
                }
            } else {
                Log.w(TAG, "No payload data");
            }
        } else if (REQUEST_DOOR_UNLOCK_CHALLENGE_INTENT.equals(intent.getAction())) {
            Log.i(TAG, "Requesting challenge");

            String doorId = intent.getStringExtra(DU_EXTRA_DOOR_ID);

            if (!StringUtils.isEmpty(doorId)) {
                executeAuth(doorId);
            } else {
                Log.w(TAG, "No doorid defined");
            }
        } else {
            Log.w(TAG, "Ignoring intent");
        }
    }

    private void executeAuth(String doorId) {
        Executor executor;
        BiometricPrompt biometricPrompt;
        BiometricPrompt.PromptInfo promptInfo;

        executor = ContextCompat.getMainExecutor(this);

        biometricPrompt = new BiometricPrompt(DoorOpenActivity.this,
                executor, new BiometricPrompt.AuthenticationCallback() {
            @Override
            public void onAuthenticationError(int errorCode,
                                              @NonNull CharSequence errString) {
                super.onAuthenticationError(errorCode, errString);
                makeText(getApplicationContext(),
                        "Authentication error: " + errString, LENGTH_SHORT)
                        .show();
            }

            @Override
            public void onAuthenticationSucceeded(
                    @NonNull BiometricPrompt.AuthenticationResult result) {
                super.onAuthenticationSucceeded(result);
                doorUnlockManager.requestChallenge("testuser", doorId);
            }

            @Override
            public void onAuthenticationFailed() {
                super.onAuthenticationFailed();
                makeText(getApplicationContext(), "Authentication failed",
                        LENGTH_SHORT)
                        .show();
            }
        });

        promptInfo = new BiometricPrompt.PromptInfo.Builder()
                .setTitle("Biometric login")
                .setNegativeButtonText("Cancel")
                .setSubtitle("Log in to unlock door")
                .setAllowedAuthenticators(BiometricManager.Authenticators.BIOMETRIC_STRONG)
                .build();

        biometricPrompt.authenticate(promptInfo);
    }

    @Override
    public void onAuthSuccess() {

        runOnUiThread(() -> {
            makeText(getApplicationContext(),
                    "Authentication succeeded!", LENGTH_SHORT).show();
        });

    }

    @Override
    public void onAuthFailure() {
        runOnUiThread(() -> {
            makeText(getApplicationContext(),
                    "Authentication Failed!", LENGTH_SHORT).show();
        });
    }
}