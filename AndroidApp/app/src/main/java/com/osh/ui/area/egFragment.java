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


    protected egFragment() {
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
        String switchValueGroupId = "allSwitches0";
        String shutterValueGroupId = "allShutters0";

        initRoom(root, "feg", R.id.labelFEG);
        initRoomLight(root, relayValueGroupId, "0", switchValueGroupId, "0", R.id.lightFEG);

        initRoom(root, "az", R.id.labelAZ);
        initRoomLight(root, relayValueGroupId, "1", switchValueGroupId, "1", R.id.lightAZ);
        initRoomShutter(root, shutterValueGroupId, "0", R.id.shutterAZ);

        initRoom(root, "k", R.id.labelK);
        initRoomLight(root, relayValueGroupId, "2", switchValueGroupId, "2", R.id.lightK);
        initRoomShutter(root, shutterValueGroupId, "1", R.id.shutterK);

        initRoom(root, "ez", R.id.labelEZ);
        initRoomLight(root, relayValueGroupId, "3", switchValueGroupId, "3", R.id.lightEZ);
        initRoomShutter(root, shutterValueGroupId, "2", R.id.shutterEZ);

        initRoom(root, "wc", R.id.labelWC);
        initRoomLight(root, relayValueGroupId, "4", switchValueGroupId, "4", R.id.lightWC);
        initRoomShutter(root, shutterValueGroupId, "3", R.id.shutterWC);

        initRoom(root, "vz", R.id.labelVZ);
        initRoomLight(root, relayValueGroupId, "5", switchValueGroupId, "5", R.id.lightVZ);
        initRoomShutter(root, shutterValueGroupId, "4", R.id.shutterVZ);

        initRoom(root, "hfe", R.id.labelHFE);
        initRoomLight(root, relayValueGroupId, "6", switchValueGroupId, "6", R.id.lightHFE);
        // TODO: NFE

        return root;
    }



}