package com.osh.ui.area;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Switch;
import android.widget.TextView;

import com.osh.R;
import com.osh.actor.DigitalActor;
import com.osh.datamodel.meta.KnownRoom;
import com.osh.service.IActorService;
import com.osh.service.IDatamodelService;
import com.osh.service.IValueService;
import com.osh.value.BooleanValue;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link egFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class egFragment extends AreaFragmentBase {


    public egFragment() {
    }

    public egFragment(IDatamodelService datamodelService, IValueService valueService, IActorService actorService) {
        super(datamodelService, valueService, actorService);
    }

    public static egFragment newInstance(IDatamodelService datamodelService, IValueService valueService, IActorService actorService) {
        return new egFragment(datamodelService, valueService, actorService);
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View root = inflater.inflate(R.layout.fragment_eg, container, false);

        String relayValueGroupId= "allRelays0";
        String toggleValueGroupId = "lightToggles0";
        String shutterValueGroupId = "allShutters0";
        String shutterModeValueGroupId = "shutterModes0";

        initRoom(root, "feg", R.id.labelFEG);
        initRoomLight(root, relayValueGroupId, "0", toggleValueGroupId, "0", R.id.lightFEG, R.id.lightBackgroundFEG);

        initRoom(root, "az", R.id.labelAZ);
        initRoomLight(root, relayValueGroupId, "1", toggleValueGroupId, "1", R.id.lightAZ, R.id.lightBackgroundAZ);
        initRoomShutter(root, shutterValueGroupId, "0", shutterModeValueGroupId, "0", R.id.shutterAZ);

        initRoom(root, "k", R.id.labelK);
        initRoomLight(root, relayValueGroupId, "2", toggleValueGroupId, "2", R.id.lightK, R.id.lightBackgroundK);
        initRoomShutter(root, shutterValueGroupId, "1", shutterModeValueGroupId, "1", R.id.shutterK);

        initRoom(root, "ez", R.id.labelEZ);
        initRoomLight(root, relayValueGroupId, "3", toggleValueGroupId, "3", R.id.lightEZ, R.id.lightBackgroundEZ);
        initRoomShutter(root, shutterValueGroupId, "2", shutterModeValueGroupId, "2", R.id.shutterEZ);

        initRoom(root, "wc", R.id.labelWC);
        initRoomLight(root, relayValueGroupId, "4", toggleValueGroupId, "4", R.id.lightWC, R.id.lightBackgroundWC);
        initRoomShutter(root, shutterValueGroupId, "3", shutterModeValueGroupId, "3", R.id.shutterWC);

        initRoom(root, "vz", R.id.labelVZ);
        initRoomLight(root, relayValueGroupId, "5", toggleValueGroupId, "5", R.id.lightVZ, R.id.lightBackgroundVZ);
        initRoomShutter(root, shutterValueGroupId, "4", shutterModeValueGroupId, "4", R.id.shutterVZ);

        initRoom(root, "hfe", R.id.labelHFE);
        initRoomLight(root, relayValueGroupId, "6", toggleValueGroupId, "6", R.id.lightHFE, R.id.lightBackgroundHFE);

        initRoom(root, "nfe", R.id.labelNFE);
        initRoomLight(root, relayValueGroupId, "7", toggleValueGroupId, "7", R.id.lightNFE, R.id.lightBackgroundNFE);
        // TODO: NFE SHUTTER

        return root;
    }



}