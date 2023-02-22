package com.osh.utils;

public class ObservableBoolean implements IObservableBoolean {

    private ObservableManagerImpl<Boolean> listenerHolder = new ObservableManagerImpl<>();

    private Boolean value;

    public ObservableBoolean(boolean initialValue) {
        this.value = initialValue;
    }

    public void changeValue(Boolean newValue) {
        this.value = newValue;
        listenerHolder.invokeListeners(newValue);
    }
    @Override
    public void addItemChangeListener(IItemChangeListener<Boolean> listener) {
        listenerHolder.addItemChangeListener(listener);
    }

    @Override
    public void addItemChangeListener(IItemChangeListener<Boolean> listener, boolean fireOnConnect) {
        addItemChangeListener(listener);
        if (fireOnConnect) {
            listener.onItemChanged(value);
        }
    }

    @Override
    public Boolean getValue() {
        return value;
    }
}
