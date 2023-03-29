package com.osh;

import androidx.fragment.app.FragmentManager;

import com.osh.databinding.FragmentRoomBinding;
import com.osh.service.IServiceContext;
import com.osh.ui.area.AreaViewModel;
import com.osh.ui.area.RoomViewModel;

public class RoomFragment extends RoomFragmentBase<FragmentRoomBinding> {
    public RoomFragment() {
    }

    public RoomFragment(IServiceContext serviceContext, AreaViewModel areaViewModel, String roomId, FragmentManager fragmentManager, RoomViewModel.RoomPosition roomPosition) {
        super(serviceContext, areaViewModel, roomId, fragmentManager, roomPosition);
    }

    @Override
    protected void setBindingData() {
        binding.setAreaData(areaViewModel);
        binding.setRoomData(roomViewModel);
        roomViewModel.initShutters(shutterInfos.size());
        roomViewModel.initTemperatures(sensorInfos.temperatureIds.size());
        roomViewModel.initHumidities(sensorInfos.humidityIds.size());
        roomViewModel.initWindowStates(sensorInfos.windowStateIds.size());
    }
}
