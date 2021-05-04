package RAC.racontroller;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;
import android.os.Handler;

import androidx.appcompat.app.AppCompatActivity;

import org.adw.library.widgets.discreteseekbar.DiscreteSeekBar;

import RAC.racontroller.API.APIClient;

public class MainActivity extends AppCompatActivity {
    private DiscreteSeekBar sbClaw;
    private DiscreteSeekBar sbElbow;
    private DiscreteSeekBar sbBase;

    private boolean doubleBackToExitPressedOnce = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        sbClaw = findViewById(R.id.sbClaw);
        sbElbow = findViewById(R.id.sbElbow);
        sbBase = findViewById(R.id.sbBase);

        TextView lblIP = findViewById(R.id.lblIPAddress);
        lblIP.setText("IP Address: ".concat(APIClient.getInstance().getIP()));

        initSeekBars();
    }

    private void initSeekBars() {
        sbClaw.setOnProgressChangeListener(new DiscreteSeekBar.OnProgressChangeListener () {
            int progressValue = 0;

            public void onProgressChanged(DiscreteSeekBar seekBar, int progress, boolean fromUser) {
                progressValue = progress;
            }

            public void onStartTrackingTouch(DiscreteSeekBar seekBar) {
            }

            public void onStopTrackingTouch(DiscreteSeekBar seekBar) {
                if(!APIClient.postData("Claw", Integer.toString(progressValue))){
                    Toast.makeText(MainActivity.this, "Something went wrong. Check the connection.", Toast.LENGTH_SHORT).show();
                }
            }
        });

        sbElbow.setOnProgressChangeListener(new DiscreteSeekBar.OnProgressChangeListener () {
            int progressValue = 0;

            public void onProgressChanged(DiscreteSeekBar seekBar, int progress, boolean fromUser) {
                progressValue = progress;
            }

            public void onStartTrackingTouch(DiscreteSeekBar seekBar) {
            }

            public void onStopTrackingTouch(DiscreteSeekBar seekBar) {
                if(!APIClient.postData("Elbow", Integer.toString(progressValue))){
                    Toast.makeText(MainActivity.this, "Something went wrong. Check the connection.", Toast.LENGTH_SHORT).show();
                }
            }
        });

        sbBase.setOnProgressChangeListener(new DiscreteSeekBar.OnProgressChangeListener () {
            int progressValue = 0;

            public void onProgressChanged(DiscreteSeekBar seekBar, int progress, boolean fromUser) {
                progressValue = progress;
            }

            public void onStartTrackingTouch(DiscreteSeekBar seekBar) {
            }

            public void onStopTrackingTouch(DiscreteSeekBar seekBar) {
                if(!APIClient.postData("Base", Integer.toString(progressValue))){
                    Toast.makeText(MainActivity.this, "Something went wrong. Check the connection.", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }

    public void btnRecord_onClick(View view) {

    }

    public void btnReset_onClick(View view) {

    }

    public void btnRun_onClick(View view) {

    }

    @Override
    public void onBackPressed() {
        if (doubleBackToExitPressedOnce) {
            super.onBackPressed();
            return;
        }

        this.doubleBackToExitPressedOnce = true;
        Toast.makeText(this, "Press again to exit", Toast.LENGTH_SHORT).show();

        new Handler().postDelayed(new Runnable() {

            @Override
            public void run() {
                doubleBackToExitPressedOnce = false;
            }
        }, 2000);
    }
}
