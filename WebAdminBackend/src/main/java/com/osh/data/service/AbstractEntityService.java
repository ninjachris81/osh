package com.osh.data.service;

import com.osh.data.entity.AbstractEntity;
import com.osh.data.entity.AudioPlaybackSource;
import com.osh.data.repository.AudioPlaybackSourceRepository;
import com.osh.data.repository.EntityRepository;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public class AbstractEntityService<BEAN_TYPE extends AbstractEntity, REPO_TYPE extends EntityRepository<BEAN_TYPE>> {

    protected final REPO_TYPE repository;

    public AbstractEntityService(REPO_TYPE repository) {
        this.repository = repository;
    }

    public Optional<BEAN_TYPE> get(String id) {
        return repository.findById(id);
    }

    public BEAN_TYPE update(BEAN_TYPE entity) {
        return repository.save(entity);
    }

    public void delete(String id) {
        repository.deleteById(id);
    }

    public Page<BEAN_TYPE> list(Pageable pageable) {
        return repository.findAll(pageable);
    }

    public Page<BEAN_TYPE> list(Pageable pageable, Specification<BEAN_TYPE> filter) {
        return repository.findAll(filter, pageable);
    }

    public int count() {
        return (int) repository.count();
    }
}
