package com.osh.log;

import android.util.Log;

public class LogFacade {


    public static void d(String tag, String msg) {
        Log.d(tag, msg);
    }

    public static void w(String tag, String msg) {
        Log.w(tag, msg);
    }

    public static void i(String tag, String msg) {
        Log.i(tag, msg);
    }
}
