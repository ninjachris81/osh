package com.osh.views;

import com.osh.data.entity.AbstractEntity;
import com.osh.data.entity.KnownArea;
import com.osh.data.entity.KnownRoom;
import com.osh.data.service.ServiceContext;
import com.vaadin.flow.component.html.Span;
import com.vaadin.flow.component.orderedlayout.HorizontalLayout;
import com.vaadin.flow.component.treegrid.TreeGrid;
import com.vaadin.flow.data.provider.DataProviderListener;
import com.vaadin.flow.data.provider.hierarchy.AbstractBackEndHierarchicalDataProvider;
import com.vaadin.flow.data.provider.hierarchy.HierarchicalDataProvider;
import com.vaadin.flow.data.provider.hierarchy.HierarchicalQuery;
import com.vaadin.flow.router.PageTitle;
import com.vaadin.flow.router.Route;
import com.vaadin.flow.shared.Registration;
import org.springframework.data.domain.Pageable;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;


@PageTitle("System Tree")
@Route(value = "SystemTree", layout = MainLayout.class)
public class SystemTreeView extends ViewBase {

    private final TreeGrid<AbstractEntity> treeGrid;

    private final HierarchicalDataProvider<AbstractEntity, Void> dataProvider;

    private final HorizontalLayout layout;
    public SystemTreeView(ServiceContext serviceContext) {
        super(serviceContext);

        treeGrid = new TreeGrid<>();

        dataProvider = getDataProvider();
        treeGrid.setDataProvider(dataProvider);
        //treeGrid.setHierarchyColumn(AbstractEntity::getId);

        treeGrid.addComponentHierarchyColumn(abstractEntity -> {
            if (abstractEntity instanceof KnownArea) {
                return new Span(((KnownArea) abstractEntity).getName());
            } else if (abstractEntity instanceof KnownRoom) {
                return new Span(((KnownRoom) abstractEntity).getName());
            }
            return new Span(abstractEntity.getId());
        });

        layout = new HorizontalLayout(treeGrid);
        add(layout);
    }

    private HierarchicalDataProvider<AbstractEntity, Void> getDataProvider() {
        return new AbstractBackEndHierarchicalDataProvider<AbstractEntity, Void>() {
            @Override
            protected Stream<AbstractEntity> fetchChildrenFromBackEnd(HierarchicalQuery<AbstractEntity, Void> query) {
                List<AbstractEntity> returnList = new ArrayList<>();

                if (query.getParent() == null) {
                    returnList.addAll(serviceContext.getKnownAreaService().list(Pageable.unpaged()).stream().toList());
                } else if (query.getParent() instanceof KnownArea) {
                    returnList.addAll(((KnownArea) query.getParent()).getKnownRooms());
                }
                return returnList.stream();
            }

            @Override
            public int getChildCount(HierarchicalQuery<AbstractEntity, Void> query) {
                if (query.getParent() == null) {
                    return serviceContext.getKnownAreaService().count();
                } else if (query.getParent() instanceof KnownArea) {
                    return ((KnownArea) query.getParent()).getKnownRooms().size();
                } else if (query.getParent() instanceof  KnownRoom) {
                    return ((KnownRoom) query.getParent()).getActors();
                }
                return 0;
            }

            @Override
            public boolean hasChildren(AbstractEntity entity) {
                if (entity instanceof KnownArea) {
                    return !((KnownArea) entity).getKnownRooms().isEmpty();
                }
                return false;
            }
        };
    }
}
