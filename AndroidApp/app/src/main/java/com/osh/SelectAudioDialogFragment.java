package com.osh;

import android.content.Context;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.DialogFragment;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import android.widget.Button;
import android.widget.Spinner;

import com.google.android.material.textfield.TextInputLayout;
import com.osh.actor.AudioPlaybackActor;
import com.osh.datamodel.meta.AudioPlaybackSource;
import com.osh.datamodel.meta.KnownRoom;
import com.osh.ui.area.RoomViewModel;
import com.osh.ui.components.AudioPlaybackActorArrayAdapter;
import com.osh.ui.components.AudioPlaybackSourceArrayAdapter;
import com.osh.ui.components.TextImageSpinnerArrayAdapter;
import com.osh.ui.components.TextSpinnerArrayAdapter;

import java.util.ArrayList;
import java.util.List;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link SelectAudioDialogFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class SelectAudioDialogFragment extends DialogFragment {

    public interface StartAudioCallbackHandler {
        void startPlayback(AudioPlaybackActor actor, AudioPlaybackSource source);
    }

    public interface StopAudioCallbackhandler {
        void stopPlayback(AudioPlaybackActor actor);
    }

    public static final String TAG = "SelectAudioDialogFragment";

    private List<AudioPlaybackActor> audioActors;

    private AudioPlaybackActorArrayAdapter audioActorArrayAdapter;

    private List<AudioPlaybackSource> audioPlaybackSources;

    private AudioPlaybackSourceArrayAdapter audioSourceArrayAdapter;

    private AutoCompleteTextView audioActorSpinner;
    private AutoCompleteTextView audioSourceSpinner;

    private StartAudioCallbackHandler startPlaybackCallbackHandler;
    private StopAudioCallbackhandler stopAudioCallbackhandler;

    public SelectAudioDialogFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param roomViewModel Parameter 1.
     * @return A new instance of fragment SelectAudioDialogFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static SelectAudioDialogFragment newInstance() {
        SelectAudioDialogFragment fragment = new SelectAudioDialogFragment();
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View returnView = inflater.inflate(R.layout.fragment_select_audio_dialog, container, false);
        audioActorSpinner = (AutoCompleteTextView) returnView.findViewById(R.id.audio_actors);
        audioSourceSpinner = (AutoCompleteTextView) returnView.findViewById(R.id.audio_sources);

        Button startBtn = returnView.findViewById(R.id.start_btn);
        startBtn.setOnClickListener(view -> {
            String actorId = audioActorSpinner.getText().toString();
            String sourceName = audioSourceSpinner.getText().toString();
            if (!actorId.isEmpty() && !sourceName.isEmpty()) {
                AudioPlaybackActor actor = audioActors.stream().filter(audioPlaybackActor -> audioPlaybackActor.getId().equals(actorId)).findFirst().get();
                AudioPlaybackSource source = audioPlaybackSources.stream().filter(audioPlaybackSource -> audioPlaybackSource.getName().equals(sourceName)).findFirst().get();
                startPlaybackCallbackHandler.startPlayback(actor, source);
            }
        });

        Button stopBtn = returnView.findViewById(R.id.stop_btn);
        stopBtn.setOnClickListener(view -> {
            String actorId = audioActorSpinner.getText().toString();
            if (!actorId.isEmpty()) {
                AudioPlaybackActor actor = audioActors.stream().filter(audioPlaybackActor -> audioPlaybackActor.getId().equals(actorId)).findFirst().get();
                stopAudioCallbackhandler.stopPlayback(actor);
            }
        });

        return returnView;
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        Window window = getDialog().getWindow();
        if(window == null) return;
        WindowManager.LayoutParams params = window.getAttributes();
        params.width = (int) getResources().getDimension(R.dimen.audio_dialog_width);
        params.height = (int) getResources().getDimension(R.dimen.audio_dialog_height);
        window.setAttributes(params);

        audioActorArrayAdapter = new AudioPlaybackActorArrayAdapter(view.getContext(), R.layout.spinner_dropdown_item, audioActors, audioActorSpinner, true);
        audioSourceArrayAdapter = new AudioPlaybackSourceArrayAdapter(view.getContext(), R.layout.spinner_dropdown_item_with_image, audioPlaybackSources, audioSourceSpinner, true);
    }

    public void setAudioActors(List<AudioPlaybackActor> audioActors) {
        this.audioActors = audioActors;
    }

    public void setAudioPlaybackSources(List<AudioPlaybackSource> audioPlaybackSources) {
        this.audioPlaybackSources = audioPlaybackSources;
    }

    public void setStartCallback(StartAudioCallbackHandler startPlaybackCallbackHandler) {
        this.startPlaybackCallbackHandler = startPlaybackCallbackHandler;
    }

    public void setStopAudioCallbackhandler(StopAudioCallbackhandler stopAudioCallbackhandler) {
        this.stopAudioCallbackhandler = stopAudioCallbackhandler;
    }

}