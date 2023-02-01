package com.osh.service.impl;

import java.util.EnumSet;
import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.osh.Identifyable;
import com.osh.service.IDefaultService;

public abstract class DefaultServiceImpl<BEANTYPE extends Identifyable, REPOSITORYTYPE> implements IDefaultService<BEANTYPE> {

  private static final Logger log = LoggerFactory.getLogger(DefaultServiceImpl.class);

  protected REPOSITORYTYPE repository;
  
  public abstract Class<BEANTYPE> getBeanClass();
  
  public DefaultServiceImpl() {
  }

  @Override
  public List<BEANTYPE> findAll() {
    //return (List<BEANTYPE>) repository.findAll();
    return null;
  }

  @Override
  public List<BEANTYPE> findAll(int offset, int limit) {
    return findAll();
  }

  @Override
  public int count() {
    //return (int) repository.count();
    return 0;
  }
  
  @Override
  public BEANTYPE findById(String id, EnumSet<LOAD_MODIFIERS> modifiers) {
    BEANTYPE bean;

    /*
    if (modifiers.contains(LOAD_MODIFIERS.FORCE_RELOAD)) {
      bean = repository.findById(id).orElse(null);
    } else {
      bean = findByIdFromCache(id);
    }*/
    
    return null;
  }

  private BEANTYPE findByIdFromCache(String id) {
	  //return repository.findById(id).orElse(null);
    return null;
  }

  @Override
  public void save(BEANTYPE bean) {
    //repository.save(bean);
  }

  @Override
  public void delete(BEANTYPE bean) {
    log.info("Removing {}", bean);
  }

  @Override
  public void deleteAll() {
    //repository.deleteAll();
  }
  
}
