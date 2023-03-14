package com.osh.ui.components;

import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;

import com.google.android.material.chip.Chip;
import com.google.android.material.chip.ChipGroup;
import com.osh.R;

import net.steamcrafted.materialiconlib.MaterialDrawableBuilder;

public class ShutterModeButton extends ChipGroup {

    public ShutterModeButton(Context context) {
        super(context);
        setup();
    }

    public ShutterModeButton(Context context, AttributeSet attrs) {
        super(context, attrs);
        setup();
    }

    public ShutterModeButton(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        setup();
    }

    protected Chip autoSelection;
    protected Chip upSelection;
    protected Chip downSelection;

    protected void setup() {

        autoSelection = new Chip(getContext());
        //autoSelection.setId(R.id.shutter_mode_button_auto_id);
        //autoSelection.setText(getResources().getString(R.string.shutter_mode_auto));

        Drawable autoIcon = MaterialDrawableBuilder.with(getContext()) // provide a context
                .setIcon(MaterialDrawableBuilder.IconValue.CALENDAR_CLOCK) // provide an icon
                .setColor(Color.BLACK) // set the icon color
                .setToActionbarSize() // set the icon size
                .build(); // Finally call build

        autoSelection.setChipIcon(autoIcon);
        autoSelection.setEnsureMinTouchTargetSize(false);
        autoSelection.setCheckable(true);
        //autoSelection.setCheckedIconVisible(false);

        Drawable upIcon = MaterialDrawableBuilder.with(getContext()) // provide a context
                .setIcon(MaterialDrawableBuilder.IconValue.CHEVRON_UP) // provide an icon
                .setColor(Color.BLACK) // set the icon color
                .setToActionbarSize() // set the icon size
                .build(); // Finally call build

        upSelection = new Chip(getContext());
        upSelection.setChipIcon(upIcon);
        upSelection.setEnsureMinTouchTargetSize(false);

        Drawable downIcon = MaterialDrawableBuilder.with(getContext()) // provide a context
                .setIcon(MaterialDrawableBuilder.IconValue.CHEVRON_DOWN) // provide an icon
                .setColor(Color.BLACK) // set the icon color
                .setToActionbarSize() // set the icon size
                .build(); // Finally call build

        downSelection = new Chip(getContext());
        downSelection.setChipIcon(downIcon);
        downSelection.setEnsureMinTouchTargetSize(false);

        this.addView(autoSelection);
        this.addView(upSelection);
        this.addView(downSelection);

        setChipSpacingResource(R.dimen.shutter_mode_button_spacing);
    }

    public void setAuto(boolean isAuto) {
        autoSelection.setEnabled(!isAuto);
        autoSelection.setChecked(isAuto);
    }

    public void setAutoClickListener(OnClickListener listener) {
        autoSelection.setOnClickListener(listener);
    }
    public void setUpClickListener(OnClickListener listener) {
        upSelection.setOnClickListener(listener);
    }

    public void setDownClickListener(OnClickListener listener) {
        downSelection.setOnClickListener(listener);
    }
}
