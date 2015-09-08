package org.peeracle.peeracledemo;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.view.Menu;
import android.view.MenuItem;

import org.peeracle.Metadata;
import org.peeracle.MetadataStream;
import org.peeracle.Session;
import org.peeracle.SessionHandle;

import java.io.File;
import java.util.ArrayList;

public class MainActivity extends Activity {
    FileDataStream fileDataStream;
    Metadata m;

    private class MySessionObserver implements Session.Observer {
    }

    private class MySessionHandleObserver implements SessionHandle.Observer {
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        File f = new File(Environment.getExternalStorageDirectory() + "tears_of_steel_1920x856_4000K.peeracle");
        fileDataStream = new FileDataStream(f);
        m = new Metadata();
        m.unserialize(fileDataStream);

        String id = m.getId();
        ArrayList<String> astr = m.getTrackerUrls();
        ArrayList<MetadataStream> mstr = m.getStreams();

        byte initSegment[] = mstr.get(0).getInitSegment();

        final MySessionObserver sessObserver = new MySessionObserver();
        Session sess = new Session(sessObserver);

        final MySessionHandleObserver sessHandleObserver = new MySessionHandleObserver();
        SessionHandle handle = sess.addMetadata(m, sessHandleObserver);
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
