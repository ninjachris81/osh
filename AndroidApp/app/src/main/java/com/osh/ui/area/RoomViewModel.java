package com.osh.ui.area;

import android.view.View;

import androidx.databinding.BindingAdapter;
import androidx.databinding.ObservableBoolean;
import androidx.databinding.ObservableField;
import androidx.lifecycle.ViewModel;

import com.osh.actor.AudioPlaybackActor;
import com.osh.actor.DigitalActor;
import com.osh.datamodel.meta.KnownRoom;
import com.osh.ui.components.ShutterModeButton;

import java.io.Serializable;

public class RoomViewModel extends ViewModel implements Serializable {

    private final KnownRoom room;

    public final ObservableField<String> name = new ObservableField<>("Unknown Room");
    public final ObservableBoolean backgroundVisible = new ObservableBoolean(false);

    public final ObservableField<AudioPlaybackActor> activePlayback = new ObservableField<>();

    public final ObservableBoolean shutterIsAuto = new ObservableBoolean(false);

    public RoomViewModel(KnownRoom room) {
        this.room = room;
        this.name.set(room.getName());
    }

    public KnownRoom getRoom() {
        return room;
    }

}
