package com.osh.utils;

public abstract class ObservableItemBase<ITEM_TYPE> implements IObservableListenerHolder<ITEM_TYPE>, IValueHolder<ITEM_TYPE> {

    private ObservableManagerImpl<ITEM_TYPE> listenerHolder = new ObservableManagerImpl<>();

    private ITEM_TYPE value;

    public ObservableItemBase(ITEM_TYPE initialValue) {
        this.value = initialValue;
    }

    public void changeValue(ITEM_TYPE newValue) {
        this.value = newValue;
        listenerHolder.invokeListeners(newValue);
    }
    @Override
    public void addItemChangeListener(IItemChangeListener<ITEM_TYPE> listener) {
        listenerHolder.addItemChangeListener(listener);
    }

    @Override
    public void addItemChangeListener(IItemChangeListener<ITEM_TYPE> listener, boolean fireOnConnect) {
        addItemChangeListener(listener);
        if (fireOnConnect) {
            listener.onItemChanged(value);
        }
    }

    @Override
    public ITEM_TYPE getValue() {
        return value;
    }

}
