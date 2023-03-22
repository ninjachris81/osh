package com.osh.ui.components;

import android.content.Context;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;

import androidx.annotation.NonNull;

import java.util.List;

public class TextSpinnerArrayAdapter extends ArrayAdapterBase<String> {

    public TextSpinnerArrayAdapter(@NonNull Context context, int resource, @NonNull List<String> objects, AutoCompleteTextView view, boolean selectFirst) {
        super(context, resource, objects, view, selectFirst);
    }

    public TextSpinnerArrayAdapter(@NonNull Context context, int resource, AutoCompleteTextView view, boolean selectFirst) {
        super(context, resource, view, selectFirst);
    }


}
