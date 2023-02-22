package com.osh.ui.wbb12;

import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModelProvider;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import com.osh.databinding.FragmentWbb12Binding;
import com.osh.wbb12.IWBB12Manager;

public class WBB12Fragment extends Fragment {

    private FragmentWbb12Binding binding;

    private final IWBB12Manager wbb12Manager;

    private WBB12ViewModel wbb12ViewModel;

    public WBB12Fragment(IWBB12Manager wbb12Manager) {
        this.wbb12Manager = wbb12Manager;
    }

    public static WBB12Fragment newInstance(IWBB12Manager wbb12Manager) {
        return new WBB12Fragment(wbb12Manager);
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {

        wbb12ViewModel = new ViewModelProvider(this, new WBB12ViewModelFactory(wbb12Manager)).get(WBB12ViewModel.class);
                //new ViewModelProvider(this).get(WBB12ViewModel.class);

        binding = FragmentWbb12Binding.inflate(inflater, container, false);
        View root = binding.getRoot();

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