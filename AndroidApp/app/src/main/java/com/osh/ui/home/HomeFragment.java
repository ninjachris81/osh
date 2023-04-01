package com.osh.ui.home;

import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;

import com.osh.DoorOpenActivity;
import com.osh.R;
import com.osh.databinding.FragmentHomeBinding;

public class HomeFragment extends Fragment {

    private FragmentHomeBinding binding;

    public static Fragment newInstance() {
        return new HomeFragment();
    }

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        HomeViewModel homeViewModel =
                new ViewModelProvider(this).get(HomeViewModel.class);

        binding = FragmentHomeBinding.inflate(inflater, container, false);
        View root = binding.getRoot();

        /*
        final TextView textView = binding.textHome;
        homeViewModel.getText().observe(getViewLifecycleOwner(), textView::setText);
         */

        Button unlockDoor = (Button) root.findViewById(R.id.unlockDoor);
        unlockDoor.setOnClickListener(listener -> {
            Intent intent = new Intent(getActivity(), DoorOpenActivity.class);
            startActivity(intent);
            Intent intent2 = new Intent(DoorOpenActivity.REQUEST_DOOR_UNLOCK_CHALLENGE_INTENT);
            intent2.putExtra(DoorOpenActivity.DU_EXTRA_DOOR_ID, "frontDoor.door");
            startActivity(intent2);
        });



        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }
}