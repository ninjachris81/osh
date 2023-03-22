package com.osh.ui.components;

import android.content.Context;
import android.graphics.Bitmap;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AutoCompleteTextView;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;

import com.osh.R;
import com.osh.actor.AudioPlaybackActor;
import com.osh.datamodel.meta.AudioPlaybackSource;

import java.util.ArrayList;
import java.util.List;

public class AudioPlaybackSourceArrayAdapter extends TextImageSpinnerArrayAdapter {

    private final List<Bitmap> bitmaps = new ArrayList<>();

    public AudioPlaybackSourceArrayAdapter(@NonNull Context context, int resource, List<AudioPlaybackSource> audioPlaybackSources, AutoCompleteTextView view, boolean selectFirst) {
        super(context, resource, view, selectFirst);

        for (AudioPlaybackSource source : audioPlaybackSources) {
            super.add(source.getName());
            bitmaps.add(source.getImage());
        }
    }

    @Override
    public View getDropDownView(int position, View convertView, ViewGroup parent) {
        return getImageForPosition(position, convertView, parent);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        return getImageForPosition(position, convertView, parent);
    }

    private View getImageForPosition(int position, View convertView, ViewGroup parent) {
        LayoutInflater inflater = (LayoutInflater)getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View row = inflater.inflate(R.layout.spinner_dropdown_item_with_image, parent, false);
        TextView textView = (TextView) row.findViewById(R.id.spinner_dropdown__item_with_text_text);
        textView.setText(this.getItem(position));
        ImageView imageView = (ImageView)row.findViewById(R.id.spinner_dropdown__item_with_text_image);
        imageView.setImageBitmap(bitmaps.get(position));
        return row;
    }
}
