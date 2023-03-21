package com.osh.ui.area;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.fragment.app.Fragment;

import com.osh.R;
import com.osh.service.IActorService;
import com.osh.service.IAudioActorService;
import com.osh.service.IDatamodelService;
import com.osh.service.IServiceContext;
import com.osh.service.IValueService;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link basementFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class basementFragment extends AreaFragmentBase {

    public basementFragment() {
    }

    public basementFragment(IServiceContext serviceContext, AreaViewModel areaViewModel) {
        super(serviceContext, areaViewModel);
    }

    public static basementFragment newInstance(IServiceContext serviceContext, AreaViewModel areaViewModel) {
        return new basementFragment(serviceContext, areaViewModel);
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