package com.osh.ui.wbb12;

import androidx.lifecycle.ViewModel;
import androidx.lifecycle.ViewModelProvider;

import com.osh.wbb12.service.IWBB12Service;

public class WBB12ViewModelFactory implements ViewModelProvider.Factory {
    private IWBB12Service wbb12Manager;


    public WBB12ViewModelFactory(IWBB12Service wbb12Manager) {
        this.wbb12Manager = wbb12Manager;
    }


    @Override
    public <T extends ViewModel> T create(Class<T> modelClass) {
        return (T) new WBB12ViewModel(wbb12Manager);
    }
}
