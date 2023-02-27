package com.osh.ui.area;

import android.os.Bundle;
import android.view.View;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.fragment.app.Fragment;

import com.osh.actor.ActorCmds;
import com.osh.actor.DigitalActor;
import com.osh.actor.ShutterActor;
import com.osh.actor.ToggleActor;
import com.osh.datamodel.meta.KnownRoom;
import com.osh.service.IActorService;
import com.osh.service.IDatamodelService;
import com.osh.service.IValueService;
import com.osh.value.BooleanValue;

public abstract class AreaFragmentBase extends Fragment {

    private IDatamodelService datamodelService;

    private IValueService valueService;

    private IActorService actorService;

    protected AreaFragmentBase() {
    }

    public AreaFragmentBase(IDatamodelService datamodelService, IValueService valueService, IActorService actorService) {
        this.datamodelService = datamodelService;
        this.valueService = valueService;
        this.actorService = actorService;
    }


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    protected void initRoom(View root, String roomId, int labelResId) {
        KnownRoom room = datamodelService.getDatamodel().getKnownRoom(roomId);

        TextView label = root.findViewById(labelResId);
        label.setText(room.getName());
    }

    protected void initRoomLight(View root, String lightRelayGroupId, String lightRelayActorId, String lightToggleGroupId, String lightToggleActorId, int lightResId) {
        Switch lightSwitch = root.findViewById(lightResId);

        ToggleActor lightToggleActor = (ToggleActor) datamodelService.getDatamodel().getActor(lightToggleActorId, lightToggleGroupId);
        DigitalActor lightActor = (DigitalActor) datamodelService.getDatamodel().getActor(lightRelayActorId, lightRelayGroupId);
        lightActor.addItemChangeListener(isEnabled -> {
            getActivity().runOnUiThread(() -> {
                lightSwitch.setChecked(isEnabled.getValue(false));
            });
        }, true);

        lightSwitch.setOnClickListener((item) -> {
            actorService.publishCmd(lightToggleActor, ActorCmds.ACTOR_CMD_TOGGLE);
        });
    }

    protected void initRoomShutter(View root, String shutterValueGroup, String shutterActorId, int buttonResId) {
        ToggleButton button = root.findViewById(buttonResId);

        ShutterActor shutterActor = (ShutterActor) datamodelService.getDatamodel().getActor(shutterActorId, shutterValueGroup);

        shutterActor.addItemChangeListener(item -> {
            int progress = item.getValue(0);
            getActivity().runOnUiThread(() -> {
                button.setEnabled(progress == 0 || progress == 100);
                button.setChecked(progress == 100);
            });
        }, true);

        button.setOnClickListener(view -> {
            actorService.publishCmd(shutterActor, button.isChecked() ? ActorCmds.ACTOR_CMD_DOWN : ActorCmds.ACTOR_CMD_UP);
        });
    }
}
