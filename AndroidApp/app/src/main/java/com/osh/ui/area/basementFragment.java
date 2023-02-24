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
 * Use the {@link basementFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class basementFragment extends AreaFragmentBase {

    protected basementFragment() {
    }

    public basementFragment(IDatamodelService datamodelService, IValueService valueService, IActorService actorService) {
        super(datamodelService, valueService, actorService);
    }

    public static basementFragment newInstance(IDatamodelService datamodelService, IValueService valueService, IActorService actorService) {
        return new basementFragment(datamodelService, valueService, actorService);
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View root = inflater.inflate(R.layout.fragment_basement, container, false);

        String relayValueGroupId= "allRelays0";
        String switchValueGroupId = "allSwitches0";

        return root;
    }



}