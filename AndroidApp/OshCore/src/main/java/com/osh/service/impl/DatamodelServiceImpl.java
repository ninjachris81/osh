package com.osh.service.impl;


import com.osh.datamodel.DBDatamodel;
import com.osh.repository.IDatamodelRepository;
import com.osh.service.IDatamodelService;

public class DatamodelServiceImpl extends DefaultServiceImpl<DBDatamodel, IDatamodelRepository> implements IDatamodelService {

	@Override
	public Class<DBDatamodel> getBeanClass() {
		return DBDatamodel.class;
	}

}
