package com.osh.ui.area;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.fragment.app.Fragment;

import com.osh.R;
import com.osh.service.IActorService;
import com.osh.service.IDatamodelService;
import com.osh.service.IValueService;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link ogFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class ogFragment extends AreaFragmentBase {

    protected ogFragment() {
    }

    public ogFragment(IDatamodelService datamodelService, IValueService valueService, IActorService actorService) {
        super(datamodelService, valueService, actorService);
    }

    public static ogFragment newInstance(IDatamodelService datamodelService, IValueService valueService, IActorService actorService) {
        return new ogFragment(datamodelService, valueService, actorService);
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View root = inflater.inflate(R.layout.fragment_og, container, false);

        String relayValueGroupId= "allRelays0";
        String toggleValueGroupId = "lightToggles0";
        String shutterValueGroupId = "allShutters0";

        initRoom(root, "sz", R.id.labelSZ);
        initRoomLight(root, relayValueGroupId, "16", toggleValueGroupId, "8", R.id.lightSZ);
        initRoomShutter(root, shutterValueGroupId, "6", R.id.shutterSZ);

        initRoom(root, "uz", R.id.labelUZ);
        initRoomLight(root, relayValueGroupId, "17", toggleValueGroupId, "9", R.id.lightUZ);
        initRoomShutter(root, shutterValueGroupId, "7", R.id.shutterUZ);

        initRoom(root, "b", R.id.labelB);
        initRoomLight(root, relayValueGroupId, "18", toggleValueGroupId, "10", R.id.lightB);
        initRoomShutter(root, shutterValueGroupId, "8", R.id.shutterB1);

        initRoom(root, "wz", R.id.labelWZ);
        initRoomLight(root, relayValueGroupId, "19", toggleValueGroupId, "11", R.id.lightWZ);
        initRoomShutter(root, shutterValueGroupId, "9", R.id.shutterWZ1);

        initRoom(root, "fog", R.id.labelFOG);
        initRoomLight(root, relayValueGroupId, "20", toggleValueGroupId, "12", R.id.lightFOG);

        initRoom(root, "hfo", R.id.labelHFO);
        initRoomLight(root, relayValueGroupId, "21", toggleValueGroupId, "13", R.id.lightHFO);

        return root;
    }



}