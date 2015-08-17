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
        InputStream in_s = resources.openRawResource(R.raw.tears);
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
        if (position < 0 || cursor + position > bytes.length)
            return -1;
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
        if (cursor + length > bytes.length) {
            return -1;
        }
        System.arraycopy(bytes, (int) cursor, buffer, 0, (int) length);
        cursor += length;
        return length;
    }

    @Override
    public long peek(byte[] buffer, long length) {
        if (cursor + length > bytes.length) {
        return -1;
        }
        System.arraycopy(bytes, (int) cursor, buffer, 0, (int) length);
        return length;
    }

    @Override
    public long write(byte[] buffer, long length) {
        System.arraycopy(buffer, 0, bytes, (int) cursor, (int) length);
        cursor += length;
        return length;
    }
}
