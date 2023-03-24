package com.osh.ui.components;

import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.view.ViewGroup;

import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.constraintlayout.widget.ConstraintSet;
import androidx.databinding.BindingAdapter;
import androidx.databinding.InverseBindingAdapter;

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
        autoSelection.setChecked(isAuto);
    }

    @BindingAdapter("isAuto")
    public static void setAuto(ShutterModeButton view, boolean newValue) {
        view.setAuto(newValue);
    }

    @InverseBindingAdapter(attribute = "isAuto")
    public static boolean getAuto(ShutterModeButton view) {
        return view.autoSelection.isChecked();
    }

    @BindingAdapter("android:layout_marginBottom")
    public static void setMarginBottom(ShutterModeButton view, float value) {
        if (value > 0) {
            ViewGroup.LayoutParams layoutParams = view.getLayoutParams();
            if (layoutParams instanceof ConstraintLayout.LayoutParams) {
                ((ConstraintLayout.LayoutParams) layoutParams).bottomMargin = (int) value;
            }
            view.setLayoutParams(layoutParams);
        }
    }

    @BindingAdapter("android:layout_marginTop")
    public static void setMarginTop(ShutterModeButton view, float value) {
        if (value > 0) {
            ViewGroup.LayoutParams layoutParams = view.getLayoutParams();
            if (layoutParams instanceof ConstraintLayout.LayoutParams) {
                ((ConstraintLayout.LayoutParams) layoutParams).topMargin = (int) value;
            }
            view.setLayoutParams(layoutParams);
        }
    }

    @BindingAdapter("app:layout_constraintBottom_toBottomOf")
    public static void setContraintBottom(ShutterModeButton view, String constraint) {
        if (!constraint.isEmpty()) {
            ViewGroup.LayoutParams layoutParams = view.getLayoutParams();
            if (layoutParams instanceof ConstraintLayout.LayoutParams) {
                ConstraintLayout parentLayout = (ConstraintLayout) view.getParent();
                ConstraintSet constraintSet = new ConstraintSet();
                constraintSet.clone(parentLayout);

                if (constraint.equals("parent")) {
                    constraintSet.connect(view.getId(), ConstraintSet.BOTTOM, parentLayout.getId(), constraintSet.BOTTOM);
                }

                constraintSet.applyToLayoutParams(view.getId(), (ConstraintLayout.LayoutParams) layoutParams);
            }
            view.setLayoutParams(layoutParams);
        }
    }

    @BindingAdapter("app:layout_constraintTop_toTopOf")
    public static void setContraintTop(ShutterModeButton view, String constraint) {
        if (!constraint.isEmpty()) {
            ViewGroup.LayoutParams layoutParams = view.getLayoutParams();
            if (layoutParams instanceof ConstraintLayout.LayoutParams) {
                ConstraintLayout parentLayout = (ConstraintLayout) view.getParent();
                ConstraintSet constraintSet = new ConstraintSet();
                constraintSet.clone(parentLayout);

                if (constraint.equals("parent")) {
                    constraintSet.connect(view.getId(), ConstraintSet.TOP, parentLayout.getId(), constraintSet.TOP);
                }

                constraintSet.applyToLayoutParams(view.getId(), (ConstraintLayout.LayoutParams) layoutParams);
            }
            view.setLayoutParams(layoutParams);
        }
    }

    @BindingAdapter("clickEnabled")
    public static void setClickEnabled(ShutterModeButton view, boolean enable) {
        for (int i = 0; i<view.getChildCount();i++) {
            view.getChildAt(i).setClickable(enable);
        }
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
