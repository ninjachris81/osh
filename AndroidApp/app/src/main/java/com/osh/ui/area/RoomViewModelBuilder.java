package com.osh.ui.area;

import static com.osh.ui.area.AreaFragment.AreaOverlays.AUDIO;
import static com.osh.ui.area.AreaFragment.AreaOverlays.LIGHTS;

import android.view.View;
import android.view.ViewGroup;

import androidx.databinding.Observable;
import androidx.fragment.app.FragmentManager;

import com.osh.R;
import com.osh.SelectAudioDialogFragment;
import com.osh.actor.ActorCmds;
import com.osh.actor.DigitalActor;
import com.osh.actor.ToggleActor;
import com.osh.datamodel.meta.KnownRoom;

public class RoomViewModelBuilder {

    private final RoomViewModel model;

    public RoomViewModelBuilder(KnownRoom room) {
        model = new RoomViewModel(room);
    }

    public static RoomViewModelBuilder newRoom(KnownRoom room) {
        return new RoomViewModelBuilder(room);
    }

    public RoomViewModel build() {
        return model;
    }

}
