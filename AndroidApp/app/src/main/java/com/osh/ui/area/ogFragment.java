package com.osh.ui.area;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.databinding.DataBindingUtil;
import androidx.fragment.app.Fragment;

import com.osh.R;
import com.osh.RoomFragment;
import com.osh.databinding.FragmentOgBinding;
import com.osh.service.IActorService;
import com.osh.service.IAudioActorService;
import com.osh.service.IDatamodelService;
import com.osh.service.IServiceContext;
import com.osh.service.IValueService;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link ogFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class ogFragment extends AreaFragmentBase {

    private FragmentOgBinding binding;
    public ogFragment() {
    }

    public ogFragment(IServiceContext serviceContext, AreaViewModel areaViewModel) {
        super(serviceContext, areaViewModel);
    }

    public static ogFragment newInstance(IServiceContext serviceContext, AreaViewModel areaViewModel) {
        return new ogFragment(serviceContext, areaViewModel);
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        binding = DataBindingUtil.inflate(inflater, R.layout.fragment_og, container, false);

        binding.setAreaData(areaViewModel);

        serviceContext.getDatamodelService().loadedState().addItemChangeListener(item -> {
            if (item.booleanValue()) {
                getActivity().runOnUiThread(() -> {
                    loadArea();
                });
            }
        }, true);

        return binding.getRoot();
    }

    private void loadArea() {
        String relayValueGroupId= "allRelays0";
        String toggleValueGroupId = "lightToggles0";
        String shutterValueGroupId = "allShutters0";
        String shutterModeValueGroupId = "shutterModes0";

        getChildFragmentManager().beginTransaction().replace(R.id.roomSZ, new RoomFragment(serviceContext , areaViewModel, "sz", getChildFragmentManager(), RoomViewModel.RoomPosition.POSITION_BOTTOM).withLight(relayValueGroupId, "16", toggleValueGroupId, "8").withShutter(shutterValueGroupId, "6", shutterModeValueGroupId, "6")).commit();
        getChildFragmentManager().beginTransaction().replace(R.id.roomUZ, new RoomFragment(serviceContext , areaViewModel, "uz", getChildFragmentManager(), RoomViewModel.RoomPosition.POSITION_TOP).withLight(relayValueGroupId, "17", toggleValueGroupId, "9").withShutter(shutterValueGroupId, "7", shutterModeValueGroupId, "7")).commit();
        getChildFragmentManager().beginTransaction().replace(R.id.roomB, new RoomFragment(serviceContext , areaViewModel, "b", getChildFragmentManager(), RoomViewModel.RoomPosition.POSITION_TOP).withLight(relayValueGroupId, "18", toggleValueGroupId, "10").withShutter(shutterValueGroupId, "8", shutterModeValueGroupId, "8")).commit();
        getChildFragmentManager().beginTransaction().replace(R.id.roomWZ, new RoomFragment(serviceContext , areaViewModel, "wz", getChildFragmentManager(), RoomViewModel.RoomPosition.POSITION_BOTTOM).withLight(relayValueGroupId, "19", toggleValueGroupId, "11").withShutter(shutterValueGroupId, "9", shutterModeValueGroupId, "9")).commit();
        getChildFragmentManager().beginTransaction().replace(R.id.roomFOG, new RoomFragment(serviceContext , areaViewModel, "fog", getChildFragmentManager(), RoomViewModel.RoomPosition.POSITION_BOTTOM).withLight(relayValueGroupId, "20", toggleValueGroupId, "12")).commit();
        getChildFragmentManager().beginTransaction().replace(R.id.roomHFO, new RoomFragment(serviceContext , areaViewModel, "hfo", getChildFragmentManager(), RoomViewModel.RoomPosition.POSITION_BOTTOM).withLight(relayValueGroupId, "21", toggleValueGroupId, "13")).commit();
    }


}