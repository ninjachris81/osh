package com.osh.service;

import com.j256.ormlite.support.ConnectionSource;
import com.osh.utils.IObservableBoolean;
import com.osh.utils.IObservableListenerHolder;

public interface IDatabaseService {
    ConnectionSource getConnectionSource();

}
