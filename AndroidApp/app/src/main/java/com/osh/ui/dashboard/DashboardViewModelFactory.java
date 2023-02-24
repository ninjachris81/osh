package com.osh.ui.dashboard;

import androidx.lifecycle.ViewModel;
import androidx.lifecycle.ViewModelProvider;

import com.osh.service.IValueService;

public class DashboardViewModelFactory  implements ViewModelProvider.Factory {

    private final IValueService valueManager;

    public DashboardViewModelFactory(IValueService valueManager) {
        this.valueManager = valueManager;
    }

    @Override
    public <T extends ViewModel> T create(Class<T> modelClass) {
        return (T) new DashboardViewModel(valueManager);
    }
}
