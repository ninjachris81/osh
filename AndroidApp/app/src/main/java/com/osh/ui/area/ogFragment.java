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
        String switchValueGroupId = "allSwitches0";

        initRoom(root, "sz", R.id.labelSZ);
        initRoomLight(root, relayValueGroupId, "16", switchValueGroupId, "8", R.id.lightSZ);

        initRoom(root, "uz", R.id.labelUZ);
        initRoomLight(root, relayValueGroupId, "17", switchValueGroupId, "9", R.id.lightUZ);

        initRoom(root, "b", R.id.labelB);
        initRoomLight(root, relayValueGroupId, "18", switchValueGroupId, "10", R.id.lightB);

        initRoom(root, "wz", R.id.labelWZ);
        initRoomLight(root, relayValueGroupId, "19", switchValueGroupId, "11", R.id.lightWZ);

        initRoom(root, "fog", R.id.labelFOG);
        initRoomLight(root, relayValueGroupId, "20", switchValueGroupId, "12", R.id.lightFOG);

        initRoom(root, "hfo", R.id.labelHFO);
        initRoomLight(root, relayValueGroupId, "21", switchValueGroupId, "13", R.id.lightHFO);

        return root;
    }



}