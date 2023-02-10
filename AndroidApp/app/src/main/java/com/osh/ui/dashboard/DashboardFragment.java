package com.osh.ui.dashboard;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;

import com.osh.MainActivity;
import com.osh.databinding.FragmentDashboardBinding;

public class DashboardFragment extends Fragment {

    private FragmentDashboardBinding binding;

    public static Fragment newInstance() {
        return new DashboardFragment();
    }

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        DashboardViewModel dashboardViewModel =
                new ViewModelProvider(this).get(DashboardViewModel.class);

        binding = FragmentDashboardBinding.inflate(inflater, container, false);
        View root = binding.getRoot();

        MainActivity activity = (MainActivity) getActivity();

        final Button shutterUp = binding.buttonUp;
        shutterUp.setOnClickListener(e -> {
            activity.testShutterUp();
        });

        final Button shutterStop = binding.buttonStop;
        shutterStop.setOnClickListener(e -> {
            activity.testShutterStop();
        });

        final Button shutterDown = binding.buttonDown;
        shutterDown.setOnClickListener(e -> {
            activity.testShutterDown();
        });

        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }
}