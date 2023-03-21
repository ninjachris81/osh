package com.osh.ui.area;

import androidx.databinding.ObservableField;
import androidx.lifecycle.ViewModel;

public class AreaViewModel extends ViewModel {

    public final ObservableField<AreaFragment.AreaOverlays> currentOverlay = new ObservableField<>(AreaFragment.AreaOverlays.NONE);

    //public final ObservableField<String> test = new ObservableField<>("JUHU");

}