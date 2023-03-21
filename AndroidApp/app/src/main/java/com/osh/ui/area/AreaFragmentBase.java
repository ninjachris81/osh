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

    protected final Map<String, RoomAdapter> roomAdapters = new HashMap<>();

    private IServiceContext serviceContext;
    protected AreaViewModel areaViewModel;
    private FragmentActivity activity;
    protected AreaFragmentBase() {
    }

    public AreaFragmentBase(IServiceContext serviceContext, AreaViewModel areaViewModel) {
        this.serviceContext = serviceContext;
        this.areaViewModel = areaViewModel;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.activity = getActivity();
    }

    protected RoomAdapterBuilder initRoom(View root, String roomId, int roomBackgroundResId) {
        KnownRoom room = serviceContext.getDatamodelService().getDatamodel().getKnownRoom(roomId);
        return RoomAdapterBuilder.newAdapter(root, serviceContext, areaViewModel, getChildFragmentManager(), room, roomBackgroundResId);
    }

    protected RoomAdapter buildRoom(RoomAdapterBuilder builder) {
        RoomAdapter adapter = builder.build();
        roomAdapters.put(adapter.getRoomModel().getRoom().getId(), adapter);
        return adapter;
    }

}
