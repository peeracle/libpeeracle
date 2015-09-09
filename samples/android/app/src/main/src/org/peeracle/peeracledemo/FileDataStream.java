package org.peeracle.peeracledemo;

import android.content.res.Resources;
import android.os.Environment;
import android.util.Log;

import org.peeracle.DataStream;
import org.peeracle.WebSocketsClient;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;
import java.util.Arrays;

public class FileDataStream extends DataStream {
    private RandomAccessFile file;

    public FileDataStream(File f) {
        super();

        try {
            file = new RandomAccessFile(f, "rw");
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return;
        }
    }

    @Override
    public long length() {
        try {
            return file.length();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return -1;
    }

    @Override
    public long seek(long position) {
        try {
            file.seek(position);
            return file.getFilePointer();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return -1;
    }

    @Override
    public long tell() {
        try {
            return file.getFilePointer();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return -1;
    }

    @Override
    public long read(byte[] buffer, long length) {
        try {
            if (file.getFilePointer() + length > file.length()) {
                return -1;
            }
            file.read(buffer);
            return length;
        } catch (IOException e) {
            e.printStackTrace();
        }

        return -1;
    }

    @Override
    public long peek(byte[] buffer, long length) {
        try {
            if (file.getFilePointer() + length > file.length()) {
                return -1;
            }
            file.readFully(buffer, (int) file.getFilePointer(), (int) length);
            return length;
        } catch (IOException e) {
            e.printStackTrace();
        }

        return -1;
    }

    @Override
    public long write(byte[] buffer, long length) {
        return 0;
    }
}
