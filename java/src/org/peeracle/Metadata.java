package org.peeracle;

public class Metadata {
    public Metadata(long nativeMetadata) {
        this.nativeMetadata = nativeMetadata;
    }

    public native void unserialize(DataStream dataStream);

    public native void dispose();

    public final long nativeMetadata;
}
