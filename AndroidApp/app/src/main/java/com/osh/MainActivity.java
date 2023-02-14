package com.osh;

import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;

import com.google.android.material.bottomnavigation.BottomNavigationView;
import com.google.android.material.navigation.NavigationBarView;
import com.osh.actor.ActorCmds;
import com.osh.actor.ActorMessage;
import com.osh.actor.IActorManager;
import com.osh.communication.mqtt.service.ICommunicationManager;
import com.osh.doorunlock.IDoorUnlockManager;
import com.osh.ui.dashboard.DashboardFragment;
import com.osh.ui.home.HomeFragment;
import com.osh.ui.notifications.NotificationsFragment;
import com.osh.ui.wbb12.WBB12Fragment;
import com.osh.value.IValueManager;
import com.osh.wbb12.IWBB12Manager;

import net.steamcrafted.materialiconlib.MaterialDrawableBuilder;
import net.steamcrafted.materialiconlib.MaterialMenuInflater;

import javax.inject.Inject;

import dagger.hilt.android.AndroidEntryPoint;

@AndroidEntryPoint
public class MainActivity extends AppCompatActivity {

    @Inject
    ICommunicationManager communicationManager;

    @Inject
    IActorManager actorManager;

    @Inject
    IDoorUnlockManager doorUnlockManager;

    @Inject
    IWBB12Manager wbb12Manager;

    @Inject
    IValueManager valueManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        BottomNavigationView bottomNav = findViewById(R.id.nav_view);
        bottomNav.setOnItemSelectedListener(navListener);

        MaterialMenuInflater
                .with(this) // Provide the activity context
                .setDefaultColor(Color.BLACK)
                .inflate(R.menu.bottom_nav_menu, bottomNav.getMenu());
    }

    private final NavigationBarView.OnItemSelectedListener navListener = item -> {
        // By using switch we can easily get
        // the selected fragment
        // by using there id.
        Fragment selectedFragment = null;
        switch (item.getItemId()) {
            case R.id.navigation_home:
                selectedFragment = HomeFragment.newInstance();
                break;
            case R.id.navigation_dashboard:
                selectedFragment = DashboardFragment.newInstance();
                break;
            case R.id.navigation_notifications:
                selectedFragment = NotificationsFragment.newInstance();
                break;
            case R.id.navigation_wbb12:
                selectedFragment = WBB12Fragment.newInstance(wbb12Manager);
                break;
        }
        // It will help to replace the
        // one fragment to other.
        if (selectedFragment != null) {
            getSupportFragmentManager().beginTransaction().replace(R.id.nav_host_fragment_activity_main, selectedFragment).commit();
        }
        return true;
    };

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        //getMenuInflater().inflate(R.menu.main_menu, menu);

        MaterialMenuInflater.with(this)
                .setDefaultColor(Color.WHITE)
                .inflate(R.menu.main_menu, menu);

        Drawable wifiOnIcon = MaterialDrawableBuilder.with(this).setIcon(MaterialDrawableBuilder.IconValue.WIFI).setColor(Color.WHITE).build();
        Drawable wifiOffIcon = MaterialDrawableBuilder.with(this).setIcon(MaterialDrawableBuilder.IconValue.WIFI_OFF).setColor(Color.WHITE).build();

        MenuItem connectedStateIcon = menu.findItem(R.id.connected_state_icon);
        communicationManager.connectedState().addItemChangeListener(connectedState -> {
            runOnUiThread(() -> {
                connectedStateIcon.setIcon(connectedState ? wifiOnIcon : wifiOffIcon);
            });
        }, true);

        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here.
        if (item.getItemId() == R.id.menu_settings) {
            Intent intent = new Intent(this, SettingsActivity.class);
            startActivity(intent);
            return true;
        } else {
            return super.onOptionsItemSelected(item);
        }
    }


    public void testShutterUp() {
        ActorMessage msg = new ActorMessage("allShutters0", "0", ActorCmds.ACTOR_CMD_UP);
        communicationManager.sendMessage(msg);
    }

    public void testShutterStop() {
        ActorMessage msg = new ActorMessage("allShutters0", "0", ActorCmds.ACTOR_CMD_STOP);
        communicationManager.sendMessage(msg);
    }

    public void testShutterDown() {
        ActorMessage msg = new ActorMessage("allShutters0", "0", ActorCmds.ACTOR_CMD_DOWN);
        communicationManager.sendMessage(msg);
    }
}

