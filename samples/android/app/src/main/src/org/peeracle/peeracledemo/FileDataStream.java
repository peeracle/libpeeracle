package org.peeracle.peeracledemo;

import android.content.res.Resources;

import org.peeracle.DataStream;

import java.io.IOException;
import java.io.InputStream;
import java.util.Arrays;

public class FileDataStream extends DataStream {
    long cursor = 0;
    byte[] bytes;

    public FileDataStream(Resources resources) {
        super();
        InputStream in_s = resources.openRawResource(R.raw.text);
        try {
            bytes = new byte[in_s.available()];
            in_s.read(bytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("FileDataStream: constructor: " + bytes.length);
    }

    @Override
    public long length() {
        System.out.println("FileDataStream: length");
        return bytes.length;
    }

    @Override
    public long seek(long position) {
        System.out.println("FileDataStream: seek position: " + position );
        /*if (position < 0 || cursor + position > bytes.length)
            return -1;*/
        cursor = position;
        return cursor;
    }

    @Override
    public long tell() {
        System.out.println("FileDataStream: tell");
        return cursor;
    }

    @Override
    public long read(byte[] buffer, long length) {
        System.out.println(buffer[0]);
        buffer[0] = 64;
        return 0;
    }
    @Override
    public long peek(byte[] buffer, long length) {return 0;}
    @Override
    public long write(byte[] buffer, long length) {return 0;}
}
