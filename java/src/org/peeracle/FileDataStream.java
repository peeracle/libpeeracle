package org.peeracle;

public class FileDataStream extends DataStream {
    public FileDataStream(String path) {
        super();
    }

    @Override
    public boolean open() {
        System.out.println("The C++ lib called the open method");
        return true;
    }

    @Override
    public void close() {
        System.out.println("The C++ lib called the close method");
    }

    @Override
    public long length() {
        System.out.println("The C++ lib called the length method");
        return 0;
    }

    @Override
    public long seek(long position) {
        System.out.println("The C++ lib called the seek method");
        return 0;
    }

    @Override
    public long read(char buffer, long length) {
        System.out.println("The C++ lib called the read method");
        return 0;
    }

    @Override
    public long readByte() {
        System.out.println("The C++ lib called the readByte method");
        return 0;
    }

    @Override
    public long readChar() {
        System.out.println("The C++ lib called the readChar method");
        return 0;
    }

    @Override
    public long readShort() {
        System.out.println("The C++ lib called the readShort method");
        return 0;
    }

    @Override
    public long readUShort() {
        System.out.println("The C++ lib called the readUShort method");
        return 0;
    }

    @Override
    public long readInt() {
        System.out.println("The C++ lib called the readInt method");
        return 0;
    }

    @Override
    public long readUInt() {
        System.out.println("The C++ lib called the readUInt method");
        return 0;
    }

    @Override
    public float readFloat() {
        System.out.println("The C++ lib called the readFloat method");
        return 0.0f;
    }

    @Override
    public double readDouble() {
        System.out.println("The C++ lib called the readDouble method");
        return 0;
    }

    @Override
    public String readString() {
        System.out.println("The C++ lib called the readString method");
        return "";
    }

    @Override
    public long peek(short buffer, long length) {
        System.out.println("The C++ lib called the peek method");
        return 0;
    }

    @Override
    public long peekByte() {
        System.out.println("The C++ lib called the peekByte method");
        return 247;
    }

    @Override
    public long peekChar() {
        System.out.println("The C++ lib called the peekChar method");
        return 0;
    }

    @Override
    public long peekShort() {
        System.out.println("The C++ lib called the peekShort method");
        return 0;
    }

    @Override
    public long peekUShort() {
        System.out.println("The C++ lib called the peekUShort method");
        return 0;
    }

    @Override
    public long peekInt() {
        System.out.println("The C++ lib called the peekInt method");
        return 0;
    }

    @Override
    public long peekUInt() {
        System.out.println("The C++ lib called the peekUInt method");
        return 0;
    }

    @Override
    public float peekFloat() {
        System.out.println("The C++ lib called the peekFloat method");
        return 0;
    }

    @Override
    public double peekDouble() {
        System.out.println("The C++ lib called the peekDouble method");
        return 0;
    }

    @Override
    public String peekString() {
        System.out.println("The C++ lib called the peekString method");
        return "";
    }

    @Override
    public long write(char buffer, long length) {
        System.out.println("The C++ lib called the write method");
        return 0;
    }

    @Override
    public long writeByte(byte value) {
        System.out.println("The C++ lib called the writeByte method");
        return 0;
    }

    @Override
    public long writeChar(char value) {
        System.out.println("The C++ lib called the writeChar method");
        return 0;
    }

    @Override
    public long writeShort(short value) {
        System.out.println("The C++ lib called the writeShort method");
        return 0;
    }

    @Override
    public long writeUShort(long value) {
        System.out.println("The C++ lib called the writeUShort method");
        return 0;
    }

    @Override
    public long writeInt(int value) {
        System.out.println("The C++ lib called the writeInt method");
        return 0;
    }

    @Override
    public long writeUInt(long value) {
        System.out.println("The C++ lib called the writeUInt method");
        return 0;
    }

    @Override
    public long writeFloat(float value) {
        System.out.println("The C++ lib called the writeFloat method");
        return 0;
    }

    @Override
    public long writeDouble(double value) {
        System.out.println("The C++ lib called the writeDouble method");
        return 0;
    }

    @Override
    public long writeString(String value) {
        System.out.println("The C++ lib called the writeString method");
        return 0;
    }
}
