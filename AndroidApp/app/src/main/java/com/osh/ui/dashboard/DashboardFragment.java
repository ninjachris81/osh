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
import com.osh.service.IValueService;

import net.steamcrafted.materialiconlib.MaterialIconView;

public class DashboardFragment extends Fragment {

    private FragmentDashboardBinding binding;

    private final IValueService valueManager;

    public DashboardFragment(IValueService valueManager) {
        this.valueManager = valueManager;
    }

    public static Fragment newInstance(IValueService valueManager) {
        return new DashboardFragment(valueManager);
    }

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        DashboardViewModel dashboardViewModel = new ViewModelProvider(this, new DashboardViewModelFactory(valueManager)).get(DashboardViewModel.class);


        binding = FragmentDashboardBinding.inflate(inflater, container, false);
        View root = binding.getRoot();

        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }
}