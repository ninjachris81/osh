package com.osh.ui.area;

import androidx.lifecycle.ViewModelProvider;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.viewpager.widget.ViewPager;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.google.android.material.tabs.TabLayout;
import com.osh.R;
import com.osh.service.IActorService;
import com.osh.service.IDatamodelService;
import com.osh.service.IValueService;

public class AreaFragment extends Fragment {

    private AreaViewModel mViewModel;
    private ViewPager viewPager;

    AreaPagerAdapter areaPagerAdapter;

    private IDatamodelService datamodelService;

    private IValueService valueService;

    private IActorService actorService;


    public AreaFragment(IDatamodelService datamodelService, IValueService valueService, IActorService actorService) {
        this.datamodelService = datamodelService;
        this.valueService = valueService;
        this.actorService = actorService;
    }

    public static AreaFragment newInstance(IDatamodelService datamodelService, IValueService valueService, IActorService actorService) {
        return new AreaFragment(datamodelService, valueService, actorService);
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_area, container, false);
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mViewModel = new ViewModelProvider(this).get(AreaViewModel.class);
        // TODO: Use the ViewModel
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        areaPagerAdapter = new AreaPagerAdapter(getChildFragmentManager(), datamodelService, valueService, actorService);
        viewPager = view.findViewById(R.id.pager);
        viewPager.setAdapter(areaPagerAdapter);

        TabLayout tabLayout = view.findViewById(R.id.tab_layout);
        tabLayout.setupWithViewPager(viewPager);

        SharedPreferences sharedPref = getActivity().getPreferences(Context.MODE_PRIVATE);
        tabLayout.getTabAt(sharedPref.getInt(getString(R.string.area_last_tab), 0)).select();

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
    }
}