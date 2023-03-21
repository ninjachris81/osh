package com.osh.ui.dashboard;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;

import com.osh.databinding.FragmentDashboardBinding;
import com.osh.service.IDatamodelService;
import com.osh.service.IServiceContext;
import com.osh.service.IValueService;

public class DashboardFragment extends Fragment {

    private FragmentDashboardBinding binding;

    private final IServiceContext serviceContext;

    public DashboardFragment(IServiceContext serviceContext) {
        this.serviceContext = serviceContext;
    }

    public static Fragment newInstance(IServiceContext serviceContext) {
        return new DashboardFragment(serviceContext);
    }

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        DashboardViewModel dashboardViewModel = new ViewModelProvider(this, new DashboardViewModelFactory(serviceContext.getValueService())).get(DashboardViewModel.class);

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