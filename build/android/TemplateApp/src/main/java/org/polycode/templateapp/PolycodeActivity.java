package org.polycode.templateapp;

import android.app.NativeActivity;

/**
 * Created by joachim on 29.02.16.
 */
public class PolycodeActivity extends NativeActivity {
    static {
        System.loadLibrary("ogg");
        System.loadLibrary("vorbis");
    }
}
