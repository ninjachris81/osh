package com.osh.data.entity;

import jakarta.persistence.Entity;
import jakarta.persistence.FetchType;
import jakarta.persistence.MappedSuperclass;
import jakarta.persistence.OneToMany;

@Entity(name = "dm_values")
public class ValueBase extends AbstractEntity {

    private String classType;
    @OneToMany(fetch = FetchType.EAGER)
    private ValueGroup valueGroup;

    private int valueType;

    private long valueTimeout;

    private String comment;

    private Boolean alwaysEmit;

    private Boolean persist;

    private int enumCount;


}
