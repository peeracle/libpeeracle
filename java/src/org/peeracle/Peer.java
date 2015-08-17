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

public class Peer {
  static {
    System.loadLibrary("peeracle");
  }

  public static interface Observer {
  }

  public static interface CreateSDPObserver {
  }

  public static interface SetSDPObserver {
  }

  public Peer(String id, TrackerClient tracker, Observer observer) {
    nativePeer = this.nativeCreatePeer(id, tracker, observer);
  }

  public native void CreateOffer(CreateSDPObserver observer);
  public native void CreateAnswer(String sdp, CreateSDPObserver observer);
  public native void SetAnswer(String sdp, SetSDPObserver observer);
  public native void AddICECandidate(String sdpMid, int sdpMLineIndex,
                                     String candidate);

  public native String getId();

  public native long nativeCreatePeer(String id, TrackerClient tracker,
                                      Observer observer);
  private long nativePeer;
}
