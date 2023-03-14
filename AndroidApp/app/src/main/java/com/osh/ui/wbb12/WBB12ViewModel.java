package com.osh.ui.wbb12;

import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

import com.osh.actor.ValueActor;
import com.osh.value.DoubleValue;
import com.osh.value.IntegerValue;
import com.osh.value.ValueBase;
import com.osh.wbb12.service.IWBB12Service;

import java.util.ArrayList;
import java.util.List;

public class WBB12ViewModel extends ViewModel {

    final List<MutableLiveData<String>> data = new ArrayList<>();
    final List<String> dataLabels = new ArrayList<>();

    final MutableLiveData<Integer> wbb12Consumption;

    final IWBB12Service wbb12Manager;

    public WBB12ViewModel(IWBB12Service wbb12Manager) {
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
                } else if (item instanceof ValueActor) {
                    setValue(liveData, (ValueBase) item);
                } else {
                    // TODO: error
                }
            }, true);

            data.add(liveData);
            dataLabels.add(wbb12Manager.getWBB12Value(key).getId());
        }

        wbb12Consumption = new MutableLiveData<>();
        IntegerValue cons = ((IntegerValue) wbb12Manager.getWBB12Value("wbb12.heatPumpConsumption"));
        wbb12Consumption.postValue(cons.getValue(0));
        cons.addItemChangeListener(item -> {
            wbb12Consumption.postValue(item.getValue(0));
        }, true);
    }

    public void setValue(MutableLiveData<String> liveData, ValueBase val) {
        liveData.postValue(wbb12Manager.getWBB12InputFormat(val.getFullId()).getUnit().withUnit(val, wbb12Manager.getWBB12InputFormat(val.getFullId()).getEnumType()));
    }
}