package com.osh.ui.components;

import android.content.Context;
import android.widget.AutoCompleteTextView;

import androidx.annotation.NonNull;

import com.osh.actor.AudioPlaybackActor;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class AudioPlaybackActorArrayAdapter extends TextSpinnerArrayAdapter {

    public AudioPlaybackActorArrayAdapter(@NonNull Context context, int resource, @NonNull List<AudioPlaybackActor> audioPlaybackActors, AutoCompleteTextView view, boolean selectFirst) {
        super(context, resource, view, selectFirst);
        for (AudioPlaybackActor actor : audioPlaybackActors) {
            super.add(actor.getId());;
        }
    }

}
