package org.peeracle;

public class DataStream {
    public DataStream() {
        this.nativeCreateDataStream();
    }

    public native void nativeCreateDataStream();

    public void setNativeDataStream(long nativeDataStream) {
        this.nativeDataStream = nativeDataStream;
    }

    public boolean open() {
        return false;
    }

    public void close() {
    }

    public long length() {return 0;}
    public long seek(long position) {return 0;}

    public long read(char buffer, long length) {return 0;}
    public long readByte() {return 0;}
    public long readChar() {return 0;}
    public long readShort() {return 0;}
    public long readUShort() {return 0;}
    public long readInt() {return 0;}
    public long readUInt() {return 0;}
    public float readFloat() {return 0;}
    public double readDouble() {return 0;}
    public String readString() {return "";}

    public long peek(short buffer, long length) {return 0;}
    public long peekByte() {return 0;}
    public long peekChar() {return 0;}
    public long peekShort() {return 0;}
    public long peekUShort() {return 0;}
    public long peekInt() {return 0;}
    public long peekUInt() {return 0;}
    public float peekFloat() {return 0;}
    public double peekDouble() {return 0;}
    public String peekString() {return "";}

    public long write(char buffer, long length) {return 0;}
    public long writeByte(byte value) {return 0;}
    public long writeChar(char value) {return 0;}
    public long writeShort(short value) {return 0;}
    public long writeUShort(long value) {return 0;}
    public long writeInt(int value) {return 0;}
    public long writeUInt(long value) {return 0;}
    public long writeFloat(float value) {return 0;}
    public long writeDouble(double value) {return 0;}
    public long writeString(String value) {return 0;}

    private long nativeDataStream;
}