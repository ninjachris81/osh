package com.osh.ui.dashboard;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;

import com.osh.MainActivity;
import com.osh.databinding.FragmentDashboardBinding;
import com.osh.value.IValueManager;
import com.osh.value.ValueManager;

import net.steamcrafted.materialiconlib.MaterialIconView;

public class DashboardFragment extends Fragment {

    private FragmentDashboardBinding binding;

    private final IValueManager valueManager;

    public DashboardFragment(IValueManager valueManager) {
        this.valueManager = valueManager;
    }

    public static Fragment newInstance(IValueManager valueManager) {
        return new DashboardFragment(valueManager);
    }

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        DashboardViewModel dashboardViewModel = new ViewModelProvider(this, new DashboardViewModelFactory(valueManager)).get(DashboardViewModel.class);


        binding = FragmentDashboardBinding.inflate(inflater, container, false);
        View root = binding.getRoot();

        final MaterialIconView relayUpIcon = binding.relayUpIcon;
        dashboardViewModel.getRelayUp().observe(getViewLifecycleOwner(), isActive -> {
            relayUpIcon.setVisibility(isActive ? View.VISIBLE : View.INVISIBLE);
        });

        final MaterialIconView relayDownIcon = binding.relayDownIcon;
        dashboardViewModel.getRelayDown().observe(getViewLifecycleOwner(), isActive -> {
            relayDownIcon.setVisibility(isActive ? View.VISIBLE : View.INVISIBLE);
        });

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