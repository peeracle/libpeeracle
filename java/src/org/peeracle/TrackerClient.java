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

public class TrackerClient {
  static {
    System.loadLibrary("peeracle");
  }

  public static interface Observer {
    public void onConnect();
    public void onPeerConnect(String hash, String peerId, long got,
                              boolean poke);
    public void onDisconnect();
    public void onError();
  }

  public TrackerClient(String url, Observer observer) {
    nativeTrackerClient = this.nativeCreateTrackerClient(url, observer);
  }

  public native boolean Init();
  public native boolean Connect();
  public native boolean Update();
  public native String getUrl();
  public native void announce(String id, long got);

  public native long nativeCreateTrackerClient(String url, Observer observer);
  private long nativeTrackerClient;
}
