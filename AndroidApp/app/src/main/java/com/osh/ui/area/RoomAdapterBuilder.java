package com.osh.ui.area;

import android.view.View;

import androidx.fragment.app.FragmentManager;

import com.osh.datamodel.meta.KnownRoom;
import com.osh.service.IServiceContext;

public class RoomAdapterBuilder {

    private final RoomViewModelBuilder modelBuilder;
    private final RoomAdapter adapter;

    public RoomAdapterBuilder(View root, IServiceContext serviceContext, AreaViewModel areaViewModel, FragmentManager fragmentManager, KnownRoom room, int roomBackgroundResId) {
        adapter = new RoomAdapter(root, serviceContext, areaViewModel, fragmentManager, roomBackgroundResId);
        modelBuilder = RoomViewModelBuilder.newRoom(room);
        adapter.setRoomModel(modelBuilder.build());
    }

    public static RoomAdapterBuilder newAdapter(View root, IServiceContext serviceContext, AreaViewModel areaViewModel, FragmentManager fragmentManager, KnownRoom room, int roomBackgroundResId) {
        return new RoomAdapterBuilder(root, serviceContext, areaViewModel, fragmentManager, room, roomBackgroundResId);
    }

    public RoomAdapterBuilder withLight(String lightRelayGroupId, String lightRelayActorId, String lightToggleGroupId, String lightToggleActorId) {
        adapter.bindLight(lightRelayGroupId, lightRelayActorId, lightToggleGroupId, lightToggleActorId);
        return this;
    }

    public RoomAdapterBuilder withShutter(String shutterValueGroup, String shutterActorId, String shutterModeValueGroup, String shutterModeId, int buttonResId) {
        adapter.bindShutter(shutterValueGroup, shutterActorId, shutterModeValueGroup, shutterModeId, buttonResId);
        return this;
    }

    public RoomAdapter build() {
        return adapter;
    }
}
