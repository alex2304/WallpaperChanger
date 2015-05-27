package com.parm.wallpaper;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.WallpaperManager;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
//import android.media.Image;
import android.net.Uri;
//import android.os.Message;
import android.os.Parcel;
import android.os.Parcelable;
import android.provider.MediaStore;
//import android.support.annotation.NonNull;
//import android.support.v4.app.DialogFragment;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.DisplayMetrics;
//import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
//import android.widget.Button;
import android.widget.ImageView;
//import android.widget.TextView;

import java.io.IOException;


public class MainActivity  extends ActionBarActivity implements Parcelable {

    ImageView img;
    Bitmap image;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        img = (ImageView) findViewById(R.id.imageView);

        if (savedInstanceState!=null) {
            image = (Bitmap) savedInstanceState.getParcelable("Svdimg");
            img.setImageBitmap(image);
        }

        findViewById(R.id.glrybtn).setOnClickListener(new OnClickActions());
    }

   /* @Override
    protected void onResume() {
        super.onResume();
        setContentView(R.layout.activity_main);

        final AlertDialog.Builder exitDialog = new AlertDialog.Builder(MainActivity.this);
        final CharSequence[] exitOptions = {"Yes", "No"};

        final DialogInterface.OnClickListener exitListener = new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                if (exitOptions[which].equals("Yes")) {
                    finish();
                } else {
                    dialog.dismiss();
                }
            }
        };


        exitDialog.setTitle("Want to close app?").setItems(exitOptions, exitListener);
    }*/

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {

    }


    private class OnClickActions implements View.OnClickListener{
        @Override
        public void onClick(View v) {
            switch(v.getId()) {
                case R.id.glrybtn :
                    openImgDialog();

                    break;
            }

        }

        private void openImgDialog() {
            final AlertDialog.Builder imgDialog = new AlertDialog.Builder(MainActivity.this);
            final CharSequence[] galleryBtnOptions = {"Open gallery", "Cancel"};

            final DialogInterface.OnClickListener imgListener = new DialogInterface.OnClickListener() {

                @Override
                public void onClick(DialogInterface dialog, int which) {
                    if (galleryBtnOptions[which].equals("Open gallery")) {
                        //========================
                        Intent i = new Intent(Intent.ACTION_PICK,android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
                        startActivityForResult(i, 2);
                        //==================================

                    } else if (galleryBtnOptions[which].equals("Cancel")) {
                        dialog.dismiss();
                    }
                }
            };

            imgDialog.setTitle("Open gallery").setItems(galleryBtnOptions, imgListener);

            //imgDialog.setNeutralButton("Push me", listener);
            //imgDialog.setNegativeButton("Cancel", listener);
            imgDialog.show();
        }


    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data){
        super.onActivityResult(requestCode, resultCode, data);
        if ((requestCode == 2) && (resultCode == -1)) {
            //============================================================
            Uri selectedImage = data.getData();
            String[] filePath = { MediaStore.Images.Media.DATA };
            Cursor c = getContentResolver().query(selectedImage, filePath, null, null, null);
            c.moveToFirst();
            int columnIndex = c.getColumnIndex(filePath[0]);
            String picturePath = c.getString(columnIndex);
            image = BitmapFactory.decodeFile(picturePath);
            img.setImageBitmap(BitmapFactory.decodeFile(picturePath));
            c.close();
            //=============================================================
            /*DisplayMetrics disp = new DisplayMetrics();
            getWindowManager().getDefaultDisplay().getMetrics(disp);
            int height = disp.heightPixels;
            int width = disp.widthPixels << 1;
            final BitmapFactory.Options options = new BitmapFactory.Options();
            options.inJustDecodeBounds = true;
            BitmapFactory.decodeFile(picturePath, options);
            options.inSampleSize = calculateInSampleSize(options, width, height);
            options.inJustDecodeBounds = false;
            image = BitmapFactory.decodeFile(picturePath, options);*/
            //=============================================================
            WallpaperManager myWallpaper = WallpaperManager.getInstance(getApplicationContext());
            try {
                myWallpaper.setBitmap(image);

            } catch (IOException e) {
                e.printStackTrace();
            }
            //=============================================================
        }

    }

   /* public static int calculateInSampleSize(BitmapFactory.Options options, int reqWidth, int reqHeight) {
        // Raw height and width of image
        final int height = options.outHeight;
        final int width = options.outWidth;
        int inSampleSize = 1;

        if (height > reqHeight || width > reqWidth) {

            // Calculate ratios of height and width to requested height and width
            final int heightRatio = Math.round((float) height / (float) reqHeight);
            final int widthRatio = Math.round((float) width / (float) reqWidth);

            // Choose the smallest ratio as inSampleSize value, this will guarantee
            // a final image with both dimensions larger than or equal to the
            // requested height and width.
            inSampleSize = heightRatio < widthRatio ? heightRatio : widthRatio;
            options.outHeight=height;
            options.outWidth=width;
        }

        return inSampleSize;
    }*/

    @Override
    protected void onSaveInstanceState(Bundle savedInstanceState) {
        super.onSaveInstanceState(savedInstanceState);
        savedInstanceState.putParcelable("Svdimg", image);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }



}
