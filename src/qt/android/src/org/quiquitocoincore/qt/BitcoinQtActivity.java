package org.quiquitocoincore.qt;

import android.os.Bundle;
import android.system.ErrnoException;
import android.system.Os;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.io.File;

public class QuiquitocoinQtActivity extends QtActivity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        final File quiquitocoinDir = new File(getFilesDir().getAbsolutePath() + "/.quiquitocoin");
        if (!quiquitocoinDir.exists()) {
            quiquitocoinDir.mkdir();
        }

        super.onCreate(savedInstanceState);
    }
}
