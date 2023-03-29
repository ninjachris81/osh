package com.osh.data.entity;

import jakarta.persistence.MappedSuperclass;

@MappedSuperclass
public class ActorBase extends AbstractEntity {

    private String classType;


}
