package org.peeracle.peeracledemo;

import org.peeracle.DataStream;

public class FileDataStream extends DataStream {
    long cursor = 0;
    byte[] bytes = new byte[32];

    public FileDataStream() {
        super();
        System.out.println("FileDataStream: constructor");
    }

    @Override
    public long length() {
        System.out.println("FileDataStream: length");
        return bytes.length;
    }

    @Override
    public long seek(long position) {
        System.out.println("FileDataStream: seek position: " + position);
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
    public long read(byte[] buffer, long length) {return 0;}
    @Override
    public long peek(byte[] buffer, long length) {return 0;}
    @Override
    public long write(byte[] buffer, long length) {return 0;}
}
