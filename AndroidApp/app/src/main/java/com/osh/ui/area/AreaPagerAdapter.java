package com.osh.ui.area;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentStatePagerAdapter;

import com.osh.datamodel.meta.KnownArea;
import com.osh.service.IActorService;
import com.osh.service.IDatamodelService;
import com.osh.service.IValueService;

import java.util.ArrayList;
import java.util.List;

public class AreaPagerAdapter extends FragmentStatePagerAdapter {

    List<Fragment> fragments = new ArrayList<>();
    List<KnownArea> knownAreas = new ArrayList<>();

    private final IDatamodelService datamodelService;

    private final IValueService valueService;

    private final IActorService actorService;

    public AreaPagerAdapter(@NonNull FragmentManager fm, IDatamodelService datamodelService, IValueService valueService, IActorService actorService) {
        super(fm);
        this.datamodelService = datamodelService;
        this.valueService = valueService;
        this.actorService = actorService;

        datamodelService.loadedState().addItemChangeListener(isLoaded -> {
            if (isLoaded) {
                initFragments();
            }
        }, true);

        initFragments();
    }

    private void initFragments() {
        fragments.clear();
        knownAreas.clear();

        for (KnownArea knownArea : datamodelService.getDatamodel().getKnownAreas()) {
            if (knownArea.getId().equals("basement")) {
                registerFragment(basementFragment.newInstance(datamodelService, valueService, actorService), knownArea);
            } else if (knownArea.getId().equals("eg")) {
                registerFragment(egFragment.newInstance(datamodelService, valueService, actorService), knownArea);
            } else if (knownArea.getId().equals("og")) {
                registerFragment(ogFragment.newInstance(datamodelService, valueService, actorService), knownArea);
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
