package com.osh.utils;

import java.sql.Array;
import java.util.ArrayList;
import java.util.List;

public class ObservableManagerImpl<ITEM_TYPE> implements IObservableManager<ITEM_TYPE>, IObservableListenerHolder<ITEM_TYPE> {

    private final List<IItemChangeListener<ITEM_TYPE>> listeners = new ArrayList<>();

    @Override
    public void addItemChangeListener(IItemChangeListener<ITEM_TYPE> listener) {
        listeners.add(listener);
    }

    @Override
    public void addItemChangeListener(IItemChangeListener<ITEM_TYPE> listener, boolean fireOnConnect) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void invokeListeners(ITEM_TYPE item) {
        for (IItemChangeListener<ITEM_TYPE> listener : listeners) {
            listener.onItemChanged(item);
        }
    }
}
