package com.osh.ui.area;

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

import com.osh.R;
import com.osh.ui.dialogs.SelectAudioDialogFragment;
import com.osh.actor.ActorCmds;
import com.osh.actor.DigitalActor;
import com.osh.actor.ShutterActor;
import com.osh.actor.ToggleActor;
import com.osh.service.IServiceContext;
import com.osh.ui.components.ShutterModeButton;
import com.osh.value.BooleanValue;
import com.osh.value.DoubleValue;
import com.osh.value.EnumValue;
import com.osh.value.ValueBase;

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
        public final List<String> temperatureIds = new ArrayList<>();
        public final List<String> humidityIds = new ArrayList<>();
        public final List<String> windowStateIds = new ArrayList<>();
    }

    protected AreaViewModel areaViewModel;
    private IServiceContext serviceContext;
    protected BINDING_TYPE binding;

    protected List<ShutterInfo> shutterInfos = new ArrayList<>();

    protected List<Integer> shutterModeButtons = List.of(R.id.shutterModeButton);

    private List<LightInfo> lightInfos = new ArrayList<>();

    protected final SensorInfo sensorInfos = new SensorInfo();

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

        for (int i = 0;i<sensorInfos.temperatureIds.size();i++) {
            bindTemperatureSensor(sensorInfos.temperatureIds.get(i), i);
        }

        for (int i = 0;i<sensorInfos.humidityIds.size();i++) {
            bindHumiditySensor(sensorInfos.humidityIds.get(i), i);
        }

        for (int i = 0;i<sensorInfos.windowStateIds.size();i++) {
            bindWindowState(sensorInfos.windowStateIds.get(i), i);
        }


        return binding.getRoot();
    }


    public RoomFragmentBase withLight(String lightRelayValueGroupId, String lightRelayId, String lightToggleValueGroupId, String lightToggleId) {
        lightInfos.add(new LightInfo(lightRelayValueGroupId, lightRelayId, lightToggleValueGroupId, lightToggleId));
        return this;
    }

    public RoomFragmentBase withTemperature(String valueGroupId, String id) {
        sensorInfos.temperatureIds.add(ValueBase.getFullId(valueGroupId, id));
        return this;
    }

    public RoomFragmentBase withHumidity(String valueGroupId, String id) {
        sensorInfos.humidityIds.add(ValueBase.getFullId(valueGroupId, id));
        return this;
    }
    public RoomFragmentBase withWindowState(String valueGroupId, String id) {
        sensorInfos.windowStateIds.add(ValueBase.getFullId(valueGroupId, id));
        return this;
    }

    protected void bindTemperatureSensor(String temperatureId, int index) {
        DoubleValue tempVal = (DoubleValue) serviceContext.getDatamodelService().getDatamodel().getValue(temperatureId);
        if (tempVal != null) {
            tempVal.addItemChangeListener(item -> {
                roomViewModel.temperatures.get(index).set(item.getValue(-1.0));
            }, true);
        } else {
            throw new RuntimeException("Sensor value not found: " +temperatureId);
        }
    }

    protected  void bindHumiditySensor(String humidityId, int index) {
        DoubleValue humVal = (DoubleValue) serviceContext.getDatamodelService().getDatamodel().getValue(humidityId);
        if (humVal != null) {
            humVal.addItemChangeListener(item -> {
                roomViewModel.humidities.get(index).set(item.getValue(-1.0));
            }, true);
        } else {
            throw new RuntimeException("Sensor value not found: " + humidityId);
        }
    }


    protected void bindWindowState(String windowStateId, int index) {
        BooleanValue stateVal = (BooleanValue) serviceContext.getValueService().getValue(windowStateId);
        if (stateVal != null) {
            stateVal.addItemChangeListener(item -> {
                roomViewModel.windowStates.get(index).set(item.getValue(false));
            });
        } else {
            throw new RuntimeException("Sensor value not found: " + windowStateId);
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