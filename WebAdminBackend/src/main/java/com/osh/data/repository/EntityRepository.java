package com.osh.data.repository;

import com.osh.data.entity.AbstractEntity;
import com.osh.data.entity.AudioPlaybackSource;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;

public interface EntityRepository<BEAN_TYPE extends AbstractEntity> extends
        JpaRepository<BEAN_TYPE, String>,
        JpaSpecificationExecutor<BEAN_TYPE> {
}
