package com.osh.service;

import java.util.EnumSet;
import java.util.List;

public interface IDefaultService<BEANTYPE> {
  
  public enum LOAD_MODIFIERS {
    NONE,
    FORCE_RELOAD,
    INITIALIZE_CHILDREN
  }

  public List<BEANTYPE> findAll();

  public List<BEANTYPE> findAll(int offset, int limit);

  public int count();

  public BEANTYPE findById(String id, EnumSet<LOAD_MODIFIERS> modifiers);

  public void save(BEANTYPE bean);

  public void delete(BEANTYPE bean);

  public void deleteAll();

}
