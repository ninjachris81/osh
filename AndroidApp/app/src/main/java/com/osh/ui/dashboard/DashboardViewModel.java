package com.osh.ui.dashboard;

import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

import com.osh.value.BooleanValue;
import com.osh.value.IValueManager;
import com.osh.value.ValueBase;
import com.osh.value.ValueGroup;
import com.osh.value.ValueManager;
import com.osh.value.ValueType;

public class DashboardViewModel extends ViewModel {

    private final MutableLiveData<Boolean> relayUp;
    private final MutableLiveData<Boolean> relayDown;

    public DashboardViewModel(IValueManager valueManager) {
        relayUp = new MutableLiveData<>();
        relayDown = new MutableLiveData<>();

        BooleanValue relayUp0 = (BooleanValue) valueManager.getValue("shutterRelays0.0");
        BooleanValue relayDown0 = (BooleanValue) valueManager.getValue("shutterRelays0.1");

        ValueGroup valueGroup = new ValueGroup("shutterRelays0");
        if (relayUp0 == null) {
            relayUp0 = new BooleanValue(valueGroup, "0", ValueType.VT_RELAY_SHUTTER);
            relayUp0.updateValue(false);
            valueManager.registerValue(relayUp0);
        }
        if (relayDown0 == null) {
            relayDown0 = new BooleanValue(valueGroup, "1", ValueType.VT_RELAY_SHUTTER);
            relayDown0.updateValue(false);
            valueManager.registerValue(relayDown0);
        }

        relayUp0.addItemChangeListener(item -> {
            relayUp.setValue(item.getValue());
        }, true);

        relayDown0.addItemChangeListener(item -> {
            relayDown.setValue(item.getValue());
        }, true);
    }

    public MutableLiveData<Boolean> getRelayUp() {
        return relayUp;
    }

    public MutableLiveData<Boolean> getRelayDown() {
        return relayDown;
    }
}