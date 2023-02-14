package com.osh.ui.wbb12;

import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

import com.osh.value.DoubleValue;
import com.osh.value.IntegerValue;
import com.osh.value.ValueBase;
import com.osh.wbb12.IWBB12Manager;

import java.util.ArrayList;
import java.util.List;

public class WBB12ViewModel extends ViewModel {

    final List<MutableLiveData<String>> data = new ArrayList<>();
    final List<String> dataLabels = new ArrayList<>();

    final IWBB12Manager wbb12Manager;

    public WBB12ViewModel(IWBB12Manager wbb12Manager) {
        this.wbb12Manager = wbb12Manager;

        for (String key : wbb12Manager.getWBB12Keys()) {
            ValueBase val = wbb12Manager.getWBB12Value(key);

            MutableLiveData<String> liveData = new MutableLiveData();
            setValue(liveData, val);

            ((ValueBase) val).addItemChangeListener(item -> {
                if (item instanceof DoubleValue) {
                    setValue(liveData, (ValueBase) item);
                } else if (item instanceof IntegerValue) {
                    setValue(liveData, (ValueBase) item);
                } else {
                    // TODO: error
                }
            });

            data.add(liveData);
            dataLabels.add(wbb12Manager.getWBB12Value(key).getId());
        }
    }

    public void setValue(MutableLiveData<String> liveData, ValueBase val) {
        liveData.postValue(String.valueOf(val.getValue()) + wbb12Manager.getWBB12InputFormat(val.getFullId()).getUnit().getAppendix(true));
    }
}