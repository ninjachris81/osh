package com.osh.ui.area;

import android.os.Bundle;

import androidx.databinding.DataBindingUtil;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.osh.R;
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

        binding.setRoomFEG(buildRoom(initRoom(binding.getRoot(), "feg", R.id.backgroundFEG)
                .withLight(relayValueGroupId, "0", toggleValueGroupId, "0"))
                .getRoomModel());

        binding.setRoomAZ(buildRoom(initRoom(binding.getRoot(), "az", R.id.backgroundAZ)
                .withLight(relayValueGroupId, "1", toggleValueGroupId, "1")
                .withShutter(shutterValueGroupId, "0", shutterModeValueGroupId, "0", R.id.shutterAZ))
                .getRoomModel());

        binding.setRoomK(buildRoom(initRoom(binding.getRoot(), "k", R.id.backgroundK)
                .withLight(relayValueGroupId, "2", toggleValueGroupId, "2")
                .withShutter(shutterValueGroupId, "1", shutterModeValueGroupId, "1", R.id.shutterK))
                .getRoomModel());


        binding.setRoomEZ(buildRoom(initRoom(binding.getRoot(), "ez", R.id.backgroundEZ)
                .withLight(relayValueGroupId, "3", toggleValueGroupId, "3")
                .withShutter(shutterValueGroupId, "2", shutterModeValueGroupId, "2", R.id.shutterEZ))
                .getRoomModel());


        binding.setRoomWC(buildRoom(initRoom(binding.getRoot(), "wc", R.id.backgroundWC)
                .withLight(relayValueGroupId, "4", toggleValueGroupId, "4")
                .withShutter(shutterValueGroupId, "3", shutterModeValueGroupId, "3", R.id.shutterWC))
                .getRoomModel());


        binding.setRoomVZ(buildRoom(initRoom(binding.getRoot(), "vz", R.id.backgroundVZ)
                .withLight(relayValueGroupId, "5", toggleValueGroupId, "5")
                .withShutter(shutterValueGroupId, "4", shutterModeValueGroupId, "4", R.id.shutterVZ))
                .getRoomModel());


        binding.setRoomHFE(buildRoom(initRoom(binding.getRoot(), "hfe", R.id.backgroundHFE)
                .withLight(relayValueGroupId, "6", toggleValueGroupId, "6"))
                .getRoomModel());

        binding.setRoomNFE(buildRoom(initRoom(binding.getRoot(), "nfe", R.id.backgroundNFE)
                .withLight(relayValueGroupId, "7", toggleValueGroupId, "7"))
                .getRoomModel());

        // TODO: NFE SHUTTER

    }

}