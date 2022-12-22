package com.osh.service.impl;

import com.osh.datamodel.DatamodelView;
import com.osh.repository.IDatamodelViewRepository;
import com.osh.service.IDatamodelViewService;

public class DatamodelViewServiceImpl extends DefaultServiceImpl<DatamodelView, IDatamodelViewRepository> implements IDatamodelViewService {

	@Override
	public Class<DatamodelView> getBeanClass() {
		return DatamodelView.class;
	}

}
