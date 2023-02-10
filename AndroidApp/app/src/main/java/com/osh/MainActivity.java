package com.osh;

import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentContainerView;
import androidx.fragment.app.FragmentManager;

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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        BottomNavigationView bottomNav = findViewById(R.id.nav_view);
        bottomNav.setOnItemSelectedListener(navListener);
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
        getMenuInflater().inflate(R.menu.main_menu, menu);
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

