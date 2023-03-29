package com.osh.views;

import com.osh.data.service.ServiceContext;
import com.vaadin.flow.component.html.Div;

public class ViewBase extends Div {

    protected final ServiceContext serviceContext;


    public ViewBase(ServiceContext serviceContext) {
        this.serviceContext = serviceContext;
    }
}
