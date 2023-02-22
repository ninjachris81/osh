package com.osh.ui.dashboard;

import androidx.lifecycle.ViewModel;
import androidx.lifecycle.ViewModelProvider;

import com.osh.value.IValueManager;
import com.osh.value.ValueManager;

public class DashboardViewModelFactory  implements ViewModelProvider.Factory {

    private final IValueManager valueManager;

    public DashboardViewModelFactory(IValueManager valueManager) {
        this.valueManager = valueManager;
    }

    @Override
    public <T extends ViewModel> T create(Class<T> modelClass) {
        return (T) new DashboardViewModel(valueManager);
    }
}
