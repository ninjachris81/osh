package com.osh.wbb12;

import com.osh.value.ValueBase;

import java.util.Set;

public interface IWBB12Manager {
    Set<String> getWBB12Keys();

    ValueBase getWBB12Value(String fullId);

    WBB12Manager.WBB12Format getWBB12InputFormat(String fullId);
}
