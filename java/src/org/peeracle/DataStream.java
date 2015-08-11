package org.peeracle;

public class DataStream {
    static {
        System.loadLibrary("peeracle");
    }

    public DataStream() {
        this.nativeCreateDataStream();
    }

    public native void nativeCreateDataStream();

    public void setNativeDataStream(long nativeDataStream) {
        this.nativeDataStream = nativeDataStream;
    }

    public long length() {return 0;}
    public long seek(long position) {return 0;}
    public long tell() {return 0;}
    public long read(byte[] buffer, long length) {return 0;}
    public long peek(byte[] buffer, long length) {return 0;}
    public long write(byte[] buffer, long length) {return 0;}

    private long nativeDataStream;
}