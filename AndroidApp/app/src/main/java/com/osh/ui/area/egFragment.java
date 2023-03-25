package com.osh.ui.area;

import android.os.Bundle;

import androidx.databinding.DataBindingUtil;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.osh.R;
import com.osh.RoomFragment;
import com.osh.databinding.FragmentEgBinding;
import com.osh.service.IActorService;
import com.osh.service.IAudioActorService;
import com.osh.service.IDatamodelService;
import com.osh.service.IServiceContext;
import com.osh.service.IValueService;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link egFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class egFragment extends AreaFragmentBase {

    private FragmentEgBinding binding;

    public egFragment() {
    }

    public egFragment(IServiceContext serviceContext, AreaViewModel areaViewModel) {
        super(serviceContext, areaViewModel);
    }

    public static egFragment newInstance(IServiceContext serviceContext, AreaViewModel areaViewModel) {
        return new egFragment(serviceContext, areaViewModel);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        //View root = super.onCreateView(inflater, container, savedInstanceState);
        binding = DataBindingUtil.inflate(inflater, R.layout.fragment_eg, container, false);

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
        String tempValueGroupId = "temps";
        String humsValueGroupId = "hums";

        getChildFragmentManager().beginTransaction().replace(R.id.roomFEG, new RoomFragment(serviceContext , areaViewModel, "feg", getChildFragmentManager(), RoomViewModel.RoomPosition.POSITION_TOP)
                .withLight(relayValueGroupId, "0", toggleValueGroupId, "lightFEG")).commit();

        getChildFragmentManager().beginTransaction().replace(R.id.roomAZ, new RoomFragment(serviceContext , areaViewModel, "az", getChildFragmentManager(), RoomViewModel.RoomPosition.POSITION_BOTTOM)
                .withLight(relayValueGroupId, "1", toggleValueGroupId, "lightAZ")
                .withShutter(shutterValueGroupId, "0", shutterModeValueGroupId, "0")
                .withSensor(tempValueGroupId, "25", humsValueGroupId, "25")).commit();

        getChildFragmentManager().beginTransaction().replace(R.id.roomK, new RoomFragment(serviceContext , areaViewModel, "k", getChildFragmentManager(), RoomViewModel.RoomPosition.POSITION_TOP)
                .withLight(relayValueGroupId, "2", toggleValueGroupId, "lightK")
                .withShutter(shutterValueGroupId, "1", shutterModeValueGroupId, "1")).commit();

        getChildFragmentManager().beginTransaction().replace(R.id.roomEZ, new RoomFragment(serviceContext , areaViewModel, "ez", getChildFragmentManager(), RoomViewModel.RoomPosition.POSITION_BOTTOM)
                .withLight(relayValueGroupId, "3", toggleValueGroupId, "lightEZ")
                .withShutter(shutterValueGroupId, "2", shutterModeValueGroupId, "2")).commit();

        getChildFragmentManager().beginTransaction().replace(R.id.roomWC, new RoomFragment(serviceContext , areaViewModel, "wc", getChildFragmentManager(), RoomViewModel.RoomPosition.POSITION_TOP)
                .withLight(relayValueGroupId, "4", toggleValueGroupId, "lightWC")
                .withShutter(shutterValueGroupId, "3", shutterModeValueGroupId, "3")).commit();

        getChildFragmentManager().beginTransaction().replace(R.id.roomVZ, new RoomFragment(serviceContext , areaViewModel, "vz", getChildFragmentManager(), RoomViewModel.RoomPosition.POSITION_TOP)
                .withLight(relayValueGroupId, "5", toggleValueGroupId, "lightVZ")
                .withShutter(shutterValueGroupId, "4", shutterModeValueGroupId, "4")).commit();

        getChildFragmentManager().beginTransaction().replace(R.id.roomHFE, new RoomFragment(serviceContext , areaViewModel, "hfe", getChildFragmentManager(), RoomViewModel.RoomPosition.POSITION_BOTTOM)
                .withLight(relayValueGroupId, "6", toggleValueGroupId, "lightHFE")).commit();

        getChildFragmentManager().beginTransaction().replace(R.id.roomNFE, new RoomFragment(serviceContext , areaViewModel, "nfe", getChildFragmentManager(), RoomViewModel.RoomPosition.POSITION_BOTTOM)
                .withLight(relayValueGroupId, "7", toggleValueGroupId, "lightNFE")
                .withShutter(shutterValueGroupId, "5", shutterModeValueGroupId, "5")).commit();

    }

}