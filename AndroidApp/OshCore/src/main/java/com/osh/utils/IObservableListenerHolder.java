package com.osh.utils;

public interface IObservableListenerHolder<ITEM_TYPE> {

    void addItemChangeListener(IItemChangeListener<ITEM_TYPE> listener);

    void addItemChangeListener(IItemChangeListener<ITEM_TYPE> listener, boolean fireOnConnect);

}
