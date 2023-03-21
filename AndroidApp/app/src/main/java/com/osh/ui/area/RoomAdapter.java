package com.osh.ui.area;

import android.view.View;
import android.view.ViewGroup;

import androidx.databinding.Observable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;

import com.osh.R;
import com.osh.SelectAudioDialogFragment;
import com.osh.actor.ActorCmds;
import com.osh.actor.DigitalActor;
import com.osh.actor.ShutterActor;
import com.osh.actor.ToggleActor;
import com.osh.datamodel.meta.KnownRoom;
import com.osh.service.IServiceContext;
import com.osh.ui.components.ShutterModeButton;
import com.osh.value.EnumValue;

public class RoomAdapter {

    private final View root;
    private final IServiceContext serviceContext;
    private final AreaViewModel areaViewModel;

    private final FragmentManager fragmentManager;
    private RoomViewModel model;

    private View roomBackground;

    public RoomAdapter(View root, IServiceContext serviceContext, AreaViewModel areaViewModel, FragmentManager fragmentManager, int roomBackgroundResId) {
        this.root = root;
        this.serviceContext = serviceContext;
        this.areaViewModel = areaViewModel;
        this.fragmentManager = fragmentManager;

        roomBackground = root.findViewById(roomBackgroundResId);

        if (roomBackground == null) {
            throw new RuntimeException("Room background not found " + roomBackgroundResId);
        }
    }


    protected void bindShutter(String shutterValueGroup, String shutterActorId, String shutterModeValueGroup, String shutterModeId, int buttonResId) {
        ShutterModeButton modeButton = root.findViewById(buttonResId);

        ShutterActor shutterActor = (ShutterActor) serviceContext.getDatamodelService().getDatamodel().getActor(shutterActorId, shutterValueGroup);
        EnumValue shutterMode = (EnumValue) serviceContext.getDatamodelService().getDatamodel().getValue(shutterModeId, shutterModeValueGroup);

        shutterMode.addItemChangeListener(item -> {
            model.shutterIsAuto.set(item.getValue(ShutterActor.SHUTTER_OPERATION_MODE_AUTO) == ShutterActor.SHUTTER_OPERATION_MODE_AUTO);
        }, true);

        modeButton.setAutoClickListener(view -> {
            shutterMode.updateValue(shutterMode.getValue(ShutterActor.SHUTTER_OPERATION_MODE_AUTO) == ShutterActor.SHUTTER_OPERATION_MODE_AUTO ? ShutterActor.SHUTTER_OPERATION_MODE_MANUAL : ShutterActor.SHUTTER_OPERATION_MODE_AUTO);
            serviceContext.getValueService().publishValue(shutterMode);
        });

        modeButton.setUpClickListener(view -> {
            shutterMode.updateValue(ShutterActor.SHUTTER_OPERATION_MODE_MANUAL);
            serviceContext.getValueService().publishValue(shutterMode);
            serviceContext.getActorService().publishCmd(shutterActor, ActorCmds.ACTOR_CMD_UP);
        });

        modeButton.setDownClickListener(view -> {
            shutterMode.updateValue(ShutterActor.SHUTTER_OPERATION_MODE_MANUAL);
            serviceContext.getValueService().publishValue(shutterMode);
            serviceContext.getActorService().publishCmd(shutterActor, ActorCmds.ACTOR_CMD_DOWN);
        });
    }

    protected void bindLight(String lightRelayGroupId, String lightRelayActorId, String lightToggleGroupId, String lightToggleActorId) {

        ToggleActor lightToggleActor = (ToggleActor) serviceContext.getDatamodelService().getDatamodel().getActor(lightToggleActorId, lightToggleGroupId);
        DigitalActor lightActor = (DigitalActor) serviceContext.getDatamodelService().getDatamodel().getActor(lightRelayActorId, lightRelayGroupId);

        lightActor.addItemChangeListener(isEnabled -> {
            model.backgroundVisible.set(isEnabled.getValue(false));
        }, true);

        roomBackground.setOnClickListener((item) -> {
            switch(areaViewModel.currentOverlay.get()) {
                case LIGHTS:
                    serviceContext.getActorService().publishCmd(lightToggleActor, ActorCmds.ACTOR_CMD_TOGGLE);
                    break;
                case AUDIO:
                    SelectAudioDialogFragment dialog = SelectAudioDialogFragment.newInstance(model);
                    dialog.show(fragmentManager, SelectAudioDialogFragment.TAG);            // getChildFragmentManager()
                    dialog.setAudioActors(serviceContext.getAudioActorService().getAudioActorsByRoom(model.getRoom().getId()));
                    break;
            }
        });

        areaViewModel.currentOverlay.addOnPropertyChangedCallback(new Observable.OnPropertyChangedCallback() {
            @Override
            public void onPropertyChanged(Observable sender, int propertyId) {
                setBackgroundForOverlay(roomBackground);
            }
        });

        setBackgroundForOverlay(roomBackground);
    }

    protected void setBackgroundForOverlay(View roomBackground) {
        switch(areaViewModel.currentOverlay.get()) {
            case LIGHTS:
                setBackgroundRecursive(roomBackground, R.drawable.light_background);
                break;
            default:
                setBackgroundRecursive(roomBackground, null);
        }
    }

    protected void setBackgroundRecursive(View view, Integer resId) {
        if (view instanceof ViewGroup) {
            for (int i = 0;i<((ViewGroup) view).getChildCount();i++) {
                setBackgroundRecursive(((ViewGroup) view).getChildAt(i), resId);
            }
        } else {
            if (resId == null) {
                view.setBackground(null);
            } else {
                view.setBackgroundResource(resId);
            }
        }
    }

    public void setRoomModel(RoomViewModel model) {
        this.model = model;
    }

    public RoomViewModel getRoomModel() {
        return this.model;
    }

    public View getRoomBackground() {
        return roomBackground;
    }
}
