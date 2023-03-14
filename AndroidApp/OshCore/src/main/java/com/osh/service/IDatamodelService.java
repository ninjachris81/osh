package com.osh.service;

import com.osh.datamodel.DatamodelBase;
import com.osh.utils.IObservableBoolean;

public interface IDatamodelService {

	DatamodelBase getDatamodel();
	
	void save();

	IObservableBoolean loadedState();


}
