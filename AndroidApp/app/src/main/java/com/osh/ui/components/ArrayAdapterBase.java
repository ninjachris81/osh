package com.osh.ui.components;

import android.content.Context;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import java.util.List;

public class ArrayAdapterBase<T> extends ArrayAdapter<T> {

    private AutoCompleteTextView view;
    private boolean selectFirst = false;

    public ArrayAdapterBase(@NonNull Context context, int resource, AutoCompleteTextView view, boolean selectFirst) {
        super(context, resource);
        setup(view, selectFirst);
    }

    public ArrayAdapterBase(@NonNull Context context, int resource, @NonNull List<T> objects, AutoCompleteTextView view, boolean selectFirst) {
        super(context, resource, objects);
        setup(view, selectFirst);
    }

    private void setup(AutoCompleteTextView view, boolean selectFirst) {
        this.view = view;
        this.view.setAdapter(this);
        this.selectFirst = selectFirst;
    }

    @Override
    public void add(@Nullable T object) {
        boolean isEmpty = super.isEmpty();
        super.add(object);

        if (this.selectFirst && isEmpty) {
            if (this.getItem(0) instanceof CharSequence) {
                 view.setText((CharSequence) this.getItem(0), false);
            }
        }
    }
}
