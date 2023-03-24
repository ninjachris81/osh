package com.osh;

import android.content.Context;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.databinding.DataBindingUtil;
import androidx.databinding.Observable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;

import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.osh.actor.ActorCmds;
import com.osh.actor.DigitalActor;
import com.osh.actor.ShutterActor;
import com.osh.actor.ToggleActor;
import com.osh.databinding.FragmentRoomBinding;
import com.osh.service.IServiceContext;
import com.osh.ui.area.AreaViewModel;
import com.osh.ui.area.RoomViewModel;
import com.osh.ui.components.ShutterModeButton;
import com.osh.value.EnumValue;

import java.util.ArrayList;
import java.util.List;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link RoomFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class RoomFragment extends Fragment {

    public class ShutterInfo {
        public String shutterValueGroupId;
        public String shutterId;
        public String shutterModeValueGroupId;
        public String shutterModeId;

        public ShutterInfo(String shutterValueGroupId, String shutterId, String shutterModeValueGroupId, String shutterModeId) {
            this.shutterValueGroupId = shutterValueGroupId;
            this.shutterId = shutterId;
            this.shutterModeValueGroupId = shutterModeValueGroupId;
            this.shutterModeId = shutterModeId;
        }
    }

    public class LightInfo {
        public String lightRelayValueGroupId;
        public String lightRelayId;
        public String lightToggleValueGroupId;
        public String lightToggleId;

        public LightInfo(String lightRelayValueGroupId, String lightRelayId, String lightToggleValueGroupId, String lightToggleId) {
            this.lightRelayValueGroupId = lightRelayValueGroupId;
            this.lightRelayId = lightRelayId;
            this.lightToggleValueGroupId = lightToggleValueGroupId;
            this.lightToggleId = lightToggleId;
        }
    }

    private AreaViewModel areaViewModel;
    private IServiceContext serviceContext;
    private FragmentRoomBinding binding;

    private List<ShutterInfo> shutterInfos = new ArrayList<>();

    private List<LightInfo> lightInfos = new ArrayList<>();

    private RoomViewModel roomViewModel;
    private View roomBackground;

    private FragmentManager fragmentManager;

    public RoomFragment() {
        // Required empty public constructor
    }

    public RoomFragment(IServiceContext serviceContext, AreaViewModel areaViewModel, String roomId, FragmentManager fragmentManager, RoomViewModel.RoomPosition roomPosition) {
        this.serviceContext = serviceContext;
        this.areaViewModel = areaViewModel;
        this.roomViewModel = new RoomViewModel(serviceContext.getDatamodelService().getDatamodel().getKnownRoom(roomId));
        this.roomViewModel.roomPosition.set(roomPosition);
        this.fragmentManager = fragmentManager;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            //mParam1 = getArguments().getString(ARG_PARAM1);
            //mParam2 = getArguments().getString(ARG_PARAM2);
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        binding = DataBindingUtil.inflate(inflater, R.layout.fragment_room, container, false);

        roomBackground = binding.getRoot().findViewById(R.id.roomBackground);

        if (hasLight) {
            bindLight();
        }

        if (shutterCount > 0) {
            bindShutter();
        }

        binding.setAreaData(areaViewModel);
        binding.setRoomData(roomViewModel);

        return binding.getRoot();
    }
    public RoomFragment withLight(String lightRelayValueGroupId, String lightRelayId, String lightToggleValueGroupId, String lightToggleId) {
        lightInfos.add(new LightInfo(lightRelayValueGroupId, lightRelayId, lightToggleValueGroupId, lightToggleId));
        return this;
    }

    protected void bindLight() {
        ToggleActor lightToggleActor = (ToggleActor) serviceContext.getDatamodelService().getDatamodel().getActor(this.lightToggleId, this.lightToggleValueGroupId);
        DigitalActor lightActor = (DigitalActor) serviceContext.getDatamodelService().getDatamodel().getActor(this.lightRelayId, this.lightRelayValueGroupId);

        lightActor.addItemChangeListener(isEnabled -> {
            roomViewModel.backgroundVisible.set(isEnabled.getValue(false));
        }, true);

        roomBackground.setOnClickListener((item) -> {
            switch(areaViewModel.currentOverlay.get()) {
                case LIGHTS:
                    serviceContext.getActorService().publishCmd(lightToggleActor, ActorCmds.ACTOR_CMD_TOGGLE);
                    break;
                case AUDIO:
                    SelectAudioDialogFragment dialog = SelectAudioDialogFragment.newInstance();
                    dialog.setAudioActors(serviceContext.getAudioActorService().getAudioActorsByRoom(roomViewModel.getRoom().getId()));
                    dialog.setAudioPlaybackSources(serviceContext.getAudioSourceService().getAudioPlaybackSources());
                    dialog.setStartCallback((actor, source) -> {
                        serviceContext.getActorService().publishCmd(actor, ActorCmds.ACTOR_CMD_SET_VALUE, source.getSourceUrl());
                        serviceContext.getActorService().publishCmd(actor, ActorCmds.ACTOR_CMD_START);
                        roomViewModel.activePlayback.set(actor);
                    });
                    dialog.setStopAudioCallbackhandler((actor) -> {
                        serviceContext.getActorService().publishCmd(actor, ActorCmds.ACTOR_CMD_STOP);
                        //model.activePlayback.set(null);
                    });
                    dialog.show(fragmentManager, SelectAudioDialogFragment.TAG);
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

    public RoomFragment withShutter(String shutterValueGroupId, String shutterId, String shutterModeValueGroupId, String shutterModeId) {
        shutterInfos.add(new ShutterInfo(shutterValueGroupId, shutterId, shutterModeValueGroupId, shutterModeId));
        return this;
    }


    protected void bindShutter() {
        ShutterModeButton modeButton = binding.getRoot().findViewById(R.id.shutterModeButton);
        modeButton.setVisibility(View.VISIBLE);

        ShutterActor shutterActor = (ShutterActor) serviceContext.getDatamodelService().getDatamodel().getActor(this.shutterId, this.shutterValueGroupId);
        EnumValue shutterMode = (EnumValue) serviceContext.getDatamodelService().getDatamodel().getValue(this.shutterModeId, this.shutterModeValueGroupId);

        shutterMode.addItemChangeListener(item -> {
            roomViewModel.shutterIsAuto.set(item.getValue(ShutterActor.SHUTTER_OPERATION_MODE_AUTO) == ShutterActor.SHUTTER_OPERATION_MODE_AUTO);
        }, true);

        shutterActor.addItemChangeListener(item -> {
            roomViewModel.shutterState.set(item.getStateAsString());
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
}