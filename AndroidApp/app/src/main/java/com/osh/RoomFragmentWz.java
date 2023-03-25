package com.osh;

import androidx.fragment.app.FragmentManager;

import com.osh.databinding.FragmentRoomWzBinding;
import com.osh.service.IServiceContext;
import com.osh.ui.area.AreaViewModel;
import com.osh.ui.area.RoomViewModel;

import java.util.List;

public class RoomFragmentWz extends RoomFragmentBase<FragmentRoomWzBinding> {

    public RoomFragmentWz() {
    }

    public RoomFragmentWz(IServiceContext serviceContext, AreaViewModel areaViewModel, String roomId, FragmentManager fragmentManager, RoomViewModel.RoomPosition roomPosition) {
        super(serviceContext, areaViewModel, roomId, fragmentManager, roomPosition);
        layout = R.layout.fragment_room_wz;

        shutterModeButtons = List.of(R.id.shutterModeButtonWz0, R.id.shutterModeButtonWz1);
    }

    @Override
    protected void setBindingData() {
        binding.setAreaData(areaViewModel);
        binding.setRoomData(roomViewModel);
        roomViewModel.initBindingArrays(shutterInfos.size());
    }
}
