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
import android.widget.Spinner;

import com.google.android.material.textfield.TextInputLayout;
import com.osh.actor.AudioPlaybackActor;
import com.osh.datamodel.meta.KnownRoom;
import com.osh.ui.area.RoomViewModel;

import java.util.ArrayList;
import java.util.List;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link SelectAudioDialogFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class SelectAudioDialogFragment extends DialogFragment {

    public static final String TAG = "SelectAudioDialogFragment";
    private static final String ARG_ROOM = "room";

    // TODO: Rename and change types of parameters
    private RoomViewModel roomViewModel;

    private AutoCompleteTextView audioActorSpinner;

    private List<AudioPlaybackActor> audioActors;

    private List<KnownRoom> knownRooms;

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
    public static SelectAudioDialogFragment newInstance(RoomViewModel roomViewModel) {
        SelectAudioDialogFragment fragment = new SelectAudioDialogFragment();
        Bundle args = new Bundle();
        args.putSerializable(ARG_ROOM, roomViewModel);
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            roomViewModel = (RoomViewModel) getArguments().getSerializable(ARG_ROOM);
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View returnView = inflater.inflate(R.layout.fragment_select_audio_dialog, container, false);
        audioActorSpinner = (AutoCompleteTextView) returnView.findViewById(R.id.audio_actors);
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

        List<String> spinnerArray = new ArrayList<String>();
        for (AudioPlaybackActor actor : audioActors) {
            spinnerArray.add(actor.getId());
        }

        ArrayAdapter<String> spinnerArrayAdapter = new ArrayAdapter<String>(view.getContext(), R.layout.spinner_dropdown_item, spinnerArray);
        audioActorSpinner.setAdapter(spinnerArrayAdapter);
    }

    public void setAudioActors(List<AudioPlaybackActor> audioActors) {
        this.audioActors = audioActors;
   }
}