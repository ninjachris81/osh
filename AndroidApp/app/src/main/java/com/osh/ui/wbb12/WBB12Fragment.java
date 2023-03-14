package com.osh.ui.wbb12;

import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModelProvider;

import android.graphics.Paint;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import com.github.mikephil.charting.components.XAxis;
import com.github.mikephil.charting.components.YAxis;
import com.github.mikephil.charting.data.BarData;
import com.github.mikephil.charting.data.BarDataSet;
import com.github.mikephil.charting.data.BarEntry;
import com.github.mikephil.charting.formatter.IndexAxisValueFormatter;
import com.github.mikephil.charting.formatter.PercentFormatter;
import com.osh.databinding.FragmentWbb12Binding;
import com.osh.wbb12.service.IWBB12Service;

import java.util.ArrayList;

public class WBB12Fragment extends Fragment {

    private FragmentWbb12Binding binding;

    private final IWBB12Service wbb12Manager;

    private WBB12ViewModel wbb12ViewModel;

    public WBB12Fragment(IWBB12Service wbb12Manager) {
        this.wbb12Manager = wbb12Manager;
    }

    public static WBB12Fragment newInstance(IWBB12Service wbb12Manager) {
        return new WBB12Fragment(wbb12Manager);
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {

        wbb12ViewModel = new ViewModelProvider(this, new WBB12ViewModelFactory(wbb12Manager)).get(WBB12ViewModel.class);
                //new ViewModelProvider(this).get(WBB12ViewModel.class);

        binding = FragmentWbb12Binding.inflate(inflater, container, false);
        View root = binding.getRoot();

        final ArrayList<String> xVals = new ArrayList<>();
        xVals.add("Consumption");

        //binding.wbb12Consumption.setVisibleXRange(0, 100);
        XAxis axisX = binding.wbb12Consumption.getXAxis();
        //axisX.setAxisMinimum(0);
        //axisX.setAxisMaximum(100);
        axisX.setEnabled(false);
        axisX.setValueFormatter(new IndexAxisValueFormatter(xVals));

        binding.wbb12Consumption.getAxisRight().setEnabled(false);
        YAxis axisLeft = binding.wbb12Consumption.getAxisLeft();
        axisLeft.setAxisMaximum(110);
        axisLeft.setAxisMinimum(-10);
        axisLeft.setEnabled(false);
        binding.wbb12Consumption.setDrawValueAboveBar(false);

        binding.wbb12Consumption.getDescription().setEnabled(true);
        binding.wbb12Consumption.getDescription().setText("Consumption");
        binding.wbb12Consumption.getDescription().setTextSize(30);
        binding.wbb12Consumption.getLegend().setEnabled(false);

        ArrayList<BarEntry> values = new ArrayList<>();
        BarEntry consumptionEntry = new BarEntry(0f, 0f);
        BarDataSet set1 = new BarDataSet(values, "Consumption");
        set1.addEntry(consumptionEntry);
        BarData barData = new BarData(set1);
        barData.setValueTextSize(30);
        barData.setValueFormatter(new PercentFormatter());
        barData.setDrawValues(true);
        binding.wbb12Consumption.setData(barData);

        wbb12ViewModel.wbb12Consumption.observe(getViewLifecycleOwner(), s -> {
            consumptionEntry.setY(s);
            binding.wbb12Consumption.animateY(200);
            binding.wbb12Consumption.getData().notifyDataChanged();
            binding.wbb12Consumption.notifyDataSetChanged();
            binding.wbb12Consumption.invalidate();
        });

        TableLayout wbb12Container = binding.wbb12Container;

        for (int i = 0;i<wbb12ViewModel.data.size();i++) {
            MutableLiveData<String> liveData = wbb12ViewModel.data.get(i);

            TableRow row = new TableRow(this.getContext());

            TextView labelView = new TextView(this.getContext());
            labelView.setText(wbb12ViewModel.dataLabels.get(i));

            TextView valueView = new TextView(this.getContext());
            valueView.setGravity(Gravity.END);
            liveData.observe(getViewLifecycleOwner(), s -> {
                valueView.setText(s);
            });

            row.addView(labelView);
            row.addView(valueView);

            wbb12Container.addView(row);
        }

        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }
}