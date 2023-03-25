package com.osh;

import android.os.Bundle;

import androidx.annotation.IdRes;
import androidx.annotation.LayoutRes;
import androidx.databinding.DataBindingUtil;
import androidx.databinding.Observable;
import androidx.databinding.ViewDataBinding;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;

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
import com.osh.value.DoubleValue;
import com.osh.value.EnumValue;

import java.util.ArrayList;
import java.util.List;

public abstract class RoomFragmentBase<BINDING_TYPE extends ViewDataBinding> extends Fragment {

    @LayoutRes
    protected int layout = R.layout.fragment_room;

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

    public class SensorInfo {
        public String temperatureValueGroupId;
        public String temperatureId;
        public String humidityValueGroupId;
        public String humidityId;

        public SensorInfo(String temperatureValueGroupId, String temperatureId, String humidityValueGroupId, String humidityId) {
            this.temperatureValueGroupId = temperatureValueGroupId;
            this.temperatureId = temperatureId;
            this.humidityValueGroupId = humidityValueGroupId;
            this.humidityId = humidityId;
        }
    }

    protected AreaViewModel areaViewModel;
    private IServiceContext serviceContext;
    protected BINDING_TYPE binding;

    protected List<ShutterInfo> shutterInfos = new ArrayList<>();

    protected List<Integer> shutterModeButtons = List.of(R.id.shutterModeButton);

    private List<LightInfo> lightInfos = new ArrayList<>();

    private List<SensorInfo> sensorInfos = new ArrayList<>();

    protected RoomViewModel roomViewModel;
    private View roomBackground;

    private FragmentManager fragmentManager;
    protected abstract void setBindingData();

    public RoomFragmentBase() {
        // Required empty public constructor
    }

    public RoomFragmentBase(IServiceContext serviceContext, AreaViewModel areaViewModel, String roomId, FragmentManager fragmentManager, RoomViewModel.RoomPosition roomPosition) {
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
        binding = DataBindingUtil.inflate(inflater, this.layout, container, false);

        setBindingData();

        roomBackground = binding.getRoot().findViewById(R.id.roomBackground);
        if (roomBackground == null) {
            throw new RuntimeException("No room background defined!");
        }

        for (LightInfo lightInfo : lightInfos) {
            bindLight(lightInfo);
        }

        if (!shutterInfos.isEmpty() && shutterInfos.size() != shutterModeButtons.size()) {
            throw new RuntimeException("Shutter info mismatch for room " + this.roomViewModel.getRoom().getId());
        }

        for (int i = 0;i<shutterInfos.size();i++) {
            bindShutter(shutterInfos.get(i), shutterModeButtons.get(i), i);
        }

        for (SensorInfo sensorInfo : sensorInfos) {
            bindSensor(sensorInfo);
        }

        return binding.getRoot();
    }


    public RoomFragmentBase withLight(String lightRelayValueGroupId, String lightRelayId, String lightToggleValueGroupId, String lightToggleId) {
        lightInfos.add(new LightInfo(lightRelayValueGroupId, lightRelayId, lightToggleValueGroupId, lightToggleId));
        return this;
    }

    public RoomFragmentBase withSensor(String temperatureValueGroupId, String temperatureId, String humidityValueGroupId, String humidityId) {
        sensorInfos.add(new SensorInfo(temperatureValueGroupId, temperatureId, humidityValueGroupId, humidityId));
        return this;
    }

    protected void bindSensor(SensorInfo sensorInfo) {
        DoubleValue tempVal = (DoubleValue) serviceContext.getDatamodelService().getDatamodel().getValue(sensorInfo.temperatureId, sensorInfo.temperatureValueGroupId);
        if (tempVal != null) {
            tempVal.addItemChangeListener(item -> {
                roomViewModel.temperature.set(item.getValue(-1.0));
            }, true);
        }

        DoubleValue humVal = (DoubleValue) serviceContext.getDatamodelService().getDatamodel().getValue(sensorInfo.humidityId, sensorInfo.humidityValueGroupId);
        if (humVal != null) {
            humVal.addItemChangeListener(item -> {
                roomViewModel.humidity.set(item.getValue(-1.0));
            }, true);
        }

    }

    protected void bindLight(LightInfo lightInfo) {
        ToggleActor lightToggleActor = (ToggleActor) serviceContext.getDatamodelService().getDatamodel().getActor(lightInfo.lightToggleId, lightInfo.lightToggleValueGroupId);
        DigitalActor lightActor = (DigitalActor) serviceContext.getDatamodelService().getDatamodel().getActor(lightInfo.lightRelayId, lightInfo.lightRelayValueGroupId);

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

    public RoomFragmentBase withShutter(String shutterValueGroupId, String shutterId, String shutterModeValueGroupId, String shutterModeId) {
        shutterInfos.add(new ShutterInfo(shutterValueGroupId, shutterId, shutterModeValueGroupId, shutterModeId));
        return this;
    }


    protected void bindShutter(ShutterInfo shutterInfo, @IdRes int shutterModeButton, int index) {
        ShutterModeButton modeButton = binding.getRoot().findViewById(shutterModeButton);
        modeButton.setVisibility(View.VISIBLE);

        ShutterActor shutterActor = (ShutterActor) serviceContext.getDatamodelService().getDatamodel().getActor(shutterInfo.shutterId, shutterInfo.shutterValueGroupId);
        EnumValue shutterMode = (EnumValue) serviceContext.getDatamodelService().getDatamodel().getValue(shutterInfo.shutterModeId, shutterInfo.shutterModeValueGroupId);

        shutterMode.addItemChangeListener(item -> {
            roomViewModel.shutterAutoModes.get(index).set(item.getValue(ShutterActor.SHUTTER_OPERATION_MODE_AUTO) == ShutterActor.SHUTTER_OPERATION_MODE_AUTO);
        }, true);

        shutterActor.addItemChangeListener(item -> {
            roomViewModel.shutterStates.get(index).set(item.getStateAsString());
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