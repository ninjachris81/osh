package com.osh.ui.area;

import android.os.Bundle;
import android.view.View;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;

import com.osh.actor.ActorCmds;
import com.osh.actor.ShutterActor;
import com.osh.datamodel.meta.KnownRoom;
import com.osh.service.IServiceContext;
import com.osh.ui.components.ShutterModeButton;
import com.osh.value.EnumValue;

import java.util.HashMap;
import java.util.Map;

public abstract class AreaFragmentBase extends Fragment {

    protected IServiceContext serviceContext;
    protected AreaViewModel areaViewModel;
    protected AreaFragmentBase() {
    }

    public AreaFragmentBase(IServiceContext serviceContext, AreaViewModel areaViewModel) {
        this.serviceContext = serviceContext;
        this.areaViewModel = areaViewModel;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

}
