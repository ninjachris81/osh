package com.osh.ui.area;

import androidx.databinding.DataBindingUtil;
import androidx.databinding.Observable;
import androidx.lifecycle.ViewModelProvider;

import android.content.Context;
import android.content.SharedPreferences;
import android.hardware.Camera;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.viewpager.widget.ViewPager;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.google.android.material.chip.ChipGroup;
import com.google.android.material.tabs.TabLayout;
import com.osh.R;
import com.osh.databinding.FragmentAreaBinding;
import com.osh.service.IActorService;
import com.osh.service.IAudioActorService;
import com.osh.service.IDatamodelService;
import com.osh.service.IServiceContext;
import com.osh.service.IValueService;

public class AreaFragment extends Fragment {

    private FragmentAreaBinding binding;

    private AreaViewModel areaViewModel;
    private ViewPager viewPager;

    AreaPagerAdapter areaPagerAdapter;

    private IServiceContext serviceContext;

    public enum AreaOverlays {
        NONE,
        LIGHTS,
        SHUTTERS,
        SENSORS,
        AUDIO,
        PRESENCE
    }

    public AreaFragment(IServiceContext serviceContext) {
        this.serviceContext = serviceContext;
    }

    public static AreaFragment newInstance(IServiceContext serviceContext) {
        return new AreaFragment(serviceContext);
    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        areaViewModel = new ViewModelProvider(this).get(AreaViewModel.class);
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {

        binding = DataBindingUtil.inflate(inflater, R.layout.fragment_area, container, false);

        binding.setAreaData(areaViewModel);

        binding.setLifecycleOwner(this);

        return binding.getRoot();
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        areaPagerAdapter = new AreaPagerAdapter(getChildFragmentManager(), serviceContext, areaViewModel);
        viewPager = view.findViewById(R.id.areaViewPager);
        viewPager.setAdapter(areaPagerAdapter);

        TabLayout tabLayout = view.findViewById(R.id.tab_layout);
        tabLayout.setupWithViewPager(viewPager);

        SharedPreferences sharedPref = getActivity().getPreferences(Context.MODE_PRIVATE);

        tabLayout.addOnTabSelectedListener(new TabLayout.OnTabSelectedListener() {
            @Override
            public void onTabSelected(TabLayout.Tab tab) {
                SharedPreferences.Editor editor = sharedPref.edit();
                editor.putInt(getString(R.string.area_last_tab), tab.getPosition());
                editor.apply();
            }

            @Override
            public void onTabUnselected(TabLayout.Tab tab) {

            }

            @Override
            public void onTabReselected(TabLayout.Tab tab) {

            }
        });
        tabLayout.getTabAt(sharedPref.getInt(getString(R.string.area_last_tab), 0)).select();

        areaViewModel.currentOverlay.set(AreaOverlays.values()[sharedPref.getInt(getString(R.string.area_last_overlay), 0)]);
        areaViewModel.currentOverlay.addOnPropertyChangedCallback(new Observable.OnPropertyChangedCallback() {
            @Override
            public void onPropertyChanged(Observable sender, int propertyId) {
                sharedPref.edit().putInt(getString(R.string.area_last_overlay), areaViewModel.currentOverlay.get().ordinal()).commit();
            }
        });

        ChipGroup overlaySelection = (ChipGroup) view.findViewById(R.id.overlay_selection_group);
        if (overlaySelection != null) {
            overlaySelection.setOnCheckedStateChangeListener((group, checkedIds) -> {
                if (checkedIds.isEmpty()) {
                    areaViewModel.currentOverlay.set(AreaOverlays.NONE);
                } else {
                    switch(checkedIds.get(0)) {
                        case R.id.overlay_lights:
                            areaViewModel.currentOverlay.set(AreaOverlays.LIGHTS);
                            break;
                        case R.id.overlay_shutters:
                            areaViewModel.currentOverlay.set(AreaOverlays.SHUTTERS);
                            break;
                        case R.id.overlay_sensors:
                            areaViewModel.currentOverlay.set(AreaOverlays.SENSORS);
                            break;
                        case R.id.overlay_audio:
                            areaViewModel.currentOverlay.set(AreaOverlays.AUDIO);
                            break;
                        case R.id.overlay_presence:
                            areaViewModel.currentOverlay.set(AreaOverlays.PRESENCE);
                            break;
                    }
                }
            });
        }
    }
}