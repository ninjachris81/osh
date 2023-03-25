package com.osh.ui.area;

import android.database.Observable;
import android.view.View;

import androidx.concurrent.futures.CallbackToFutureAdapter;
import androidx.databinding.BindingAdapter;
import androidx.databinding.ObservableBoolean;
import androidx.databinding.ObservableDouble;
import androidx.databinding.ObservableField;
import androidx.databinding.ObservableFloat;
import androidx.databinding.ObservableInt;
import androidx.lifecycle.ViewModel;

import com.osh.actor.AudioPlaybackActor;
import com.osh.actor.DigitalActor;
import com.osh.actor.ShutterActor;
import com.osh.datamodel.meta.KnownRoom;
import com.osh.ui.components.ShutterModeButton;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class RoomViewModel extends ViewModel implements Serializable {

    public enum RoomPosition {
        POSITION_TOP,
        POSITION_BOTTOM
    }

    private final KnownRoom room;

    public final ObservableField<String> name = new ObservableField<>("Unknown Room");
    public final ObservableBoolean backgroundVisible = new ObservableBoolean(false);

    public final ObservableField<AudioPlaybackActor> activePlayback = new ObservableField<>();

    public final List<ObservableBoolean> shutterAutoModes = new ArrayList<>();
    public final List<ObservableField<String>> shutterStates = new ArrayList<>();
    public final ObservableField<RoomPosition> roomPosition = new ObservableField<>(RoomPosition.POSITION_TOP);

    public final ObservableDouble temperature = new ObservableDouble(-1);

    public final ObservableDouble humidity = new ObservableDouble(-1);

    public RoomViewModel(KnownRoom room) {
        this.room = room;
        this.name.set(room.getName());
    }

    public KnownRoom getRoom() {
        return room;
    }

    public void initBindingArrays(int shutterCount) {
        for (int i = 0;i<shutterCount;i++) {
            shutterAutoModes.add(new ObservableBoolean(false));
            shutterStates.add(new ObservableField<>(""));
        }
    }

}
