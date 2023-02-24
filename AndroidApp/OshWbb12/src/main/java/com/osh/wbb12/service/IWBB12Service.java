package com.osh.wbb12.service;

import com.osh.manager.IMqttSupport;
import com.osh.value.ValueBase;
import com.osh.wbb12.service.impl.WBB12ServiceImpl;

import java.util.Set;

public interface IWBB12Service extends IMqttSupport {
    Set<String> getWBB12Keys();

    ValueBase getWBB12Value(String fullId);

    WBB12ServiceImpl.WBB12Format getWBB12InputFormat(String fullId);
}
