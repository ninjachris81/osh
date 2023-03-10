package com.osh.ui.area;

import android.os.Bundle;
import android.view.View;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;

import com.osh.actor.ActorCmds;
import com.osh.actor.DigitalActor;
import com.osh.actor.ShutterActor;
import com.osh.actor.ToggleActor;
import com.osh.datamodel.meta.KnownRoom;
import com.osh.service.IActorService;
import com.osh.service.IDatamodelService;
import com.osh.service.IValueService;
import com.osh.ui.components.ShutterModeButton;
import com.osh.value.BooleanValue;
import com.osh.value.EnumValue;

public abstract class AreaFragmentBase extends Fragment {

    private IDatamodelService datamodelService;

    private IValueService valueService;

    private IActorService actorService;
    private FragmentActivity activity;

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
        this.activity = getActivity();
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
            activity.runOnUiThread(() -> {
                lightSwitch.setChecked(isEnabled.getValue(false));
            });
        }, true);

        lightSwitch.setOnClickListener((item) -> {
            actorService.publishCmd(lightToggleActor, ActorCmds.ACTOR_CMD_TOGGLE);
        });
    }

    protected void initRoomShutter(View root, String shutterValueGroup, String shutterActorId, String shutterModeValueGroup, String shutterModeId, int buttonResId) {
        ShutterModeButton modeButton = root.findViewById(buttonResId);

        ShutterActor shutterActor = (ShutterActor) datamodelService.getDatamodel().getActor(shutterActorId, shutterValueGroup);
        EnumValue shutterMode = (EnumValue) datamodelService.getDatamodel().getValue(shutterModeId, shutterModeValueGroup);

        /*
        shutterActor.addItemChangeListener(item -> {
            int progress = item.getValue(0);
            activity.runOnUiThread(() -> {
                button.setEnabled(progress == 0 || progress == 100);
                button.setChecked(progress == 100);
            });
        }, true);
         */

        shutterMode.addItemChangeListener(item -> {
            activity.runOnUiThread(() -> {
                modeButton.setAuto(item.getValue(ShutterActor.SHUTTER_OPERATION_MODE_AUTO) == ShutterActor.SHUTTER_OPERATION_MODE_AUTO);
            });
        }, true);

        modeButton.setAutoClickListener(view -> {
            shutterMode.updateValue(ShutterActor.SHUTTER_OPERATION_MODE_AUTO);
            valueService.publishValue(shutterMode);
        });

        modeButton.setUpClickListener(view -> {
            shutterMode.updateValue(ShutterActor.SHUTTER_OPERATION_MODE_MANUAL);
            valueService.publishValue(shutterMode);
            //actorService.publishCmd(shutterActor, ActorCmds.ACTOR_CMD_UP);
        });

        modeButton.setDownClickListener(view -> {
            shutterMode.updateValue(ShutterActor.SHUTTER_OPERATION_MODE_MANUAL);
            valueService.publishValue(shutterMode);
            //actorService.publishCmd(shutterActor, ActorCmds.ACTOR_CMD_DOWN);
        });
    }
}
