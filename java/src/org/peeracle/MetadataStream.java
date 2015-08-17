/*
 * Copyright (c) 2015 peeracle contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package org.peeracle;

import java.lang.String;
import java.util.ArrayList;

public class MetadataStream {
  static {
    System.loadLibrary("peeracle");
  }

  public MetadataStream(long nativeMetadataStream) {
    this.nativeMetadataStream = nativeMetadataStream;
  }

  public native char getType();
  public native String getMimeType();
  public native long getBandwidth();
  public native int getWidth();
  public native int getHeight();
  public native int getNumChannels();
  public native int getSamplingFrequency();
  public native long getChunkSize();
  public native byte[] getInitSegment();
  public native long getInitSegmentLength();
  public native ArrayList<MetadataMediaSegment> getMediaSegments();
  public native boolean unserialize(DataStream dataStream,
                                    String hashName, Hash hash);

  public final long nativeMetadataStream;
}
