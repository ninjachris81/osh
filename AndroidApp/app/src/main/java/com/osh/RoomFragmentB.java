package com.osh;

import androidx.fragment.app.FragmentManager;

import com.osh.databinding.FragmentRoomBBinding;
import com.osh.databinding.FragmentRoomWzBinding;
import com.osh.service.IServiceContext;
import com.osh.ui.area.AreaViewModel;
import com.osh.ui.area.RoomViewModel;

import java.util.List;

public class RoomFragmentB extends RoomFragmentBase<FragmentRoomBBinding> {

    public RoomFragmentB() {
    }

    public RoomFragmentB(IServiceContext serviceContext, AreaViewModel areaViewModel, String roomId, FragmentManager fragmentManager, RoomViewModel.RoomPosition roomPosition) {
        super(serviceContext, areaViewModel, roomId, fragmentManager, roomPosition);
        layout = R.layout.fragment_room_b;

        shutterModeButtons = List.of(R.id.shutterModeButtonB0, R.id.shutterModeButtonB1);
    }

    @Override
    protected void setBindingData() {
        binding.setAreaData(areaViewModel);
        binding.setRoomData(roomViewModel);
        roomViewModel.initBindingArrays(shutterInfos.size());
    }
}
