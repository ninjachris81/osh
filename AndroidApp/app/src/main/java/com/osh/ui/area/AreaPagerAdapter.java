package com.osh.ui.area;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentStatePagerAdapter;

import com.osh.datamodel.meta.KnownArea;
import com.osh.service.IActorService;
import com.osh.service.IAudioActorService;
import com.osh.service.IDatamodelService;
import com.osh.service.IServiceContext;
import com.osh.service.IValueService;

import java.util.ArrayList;
import java.util.List;

public class AreaPagerAdapter extends FragmentStatePagerAdapter {

    List<Fragment> fragments = new ArrayList<>();
    List<KnownArea> knownAreas = new ArrayList<>();

    private final AreaViewModel areaViewModel;

    private final IServiceContext serviceContext;

    public AreaPagerAdapter(@NonNull FragmentManager fm, IServiceContext serviceContext, AreaViewModel areaViewModel) {
        super(fm);
        this.serviceContext = serviceContext;

        this.areaViewModel = areaViewModel;

        serviceContext.getDatamodelService().loadedState().addItemChangeListener(isLoaded -> {
            if (isLoaded) {
                initFragments();
            }
        }, true);

        initFragments();
    }

    private void initFragments() {
        fragments.clear();
        knownAreas.clear();

        for (KnownArea knownArea : serviceContext.getDatamodelService().getDatamodel().getKnownAreas()) {
            if (knownArea.getId().equals("basement")) {
                registerFragment(basementFragment.newInstance(serviceContext, areaViewModel), knownArea);
            } else if (knownArea.getId().equals("eg")) {
                registerFragment(egFragment.newInstance(serviceContext, areaViewModel), knownArea);
            } else if (knownArea.getId().equals("og")) {
                registerFragment(ogFragment.newInstance(serviceContext, areaViewModel), knownArea);
            }
        }
    }

    private void registerFragment(Fragment fragment, KnownArea knownArea) {
        fragments.add(fragment);
        knownAreas.add(knownArea);
    }

    @NonNull
    @Override
    public Fragment getItem(int position) {
        return fragments.get(position);
    }

    @Override
    public int getCount() {
        return fragments.size();
    }

    @Override
    public CharSequence getPageTitle(int position) {
        return knownAreas.get(position).getName();
    }
}
