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

import de.tavendo.autobahn.WebSocket.WebSocketConnectionObserver;
import de.tavendo.autobahn.WebSocketConnection;
import de.tavendo.autobahn.WebSocketException;

public class WebSocketsClient {
  static {
    System.loadLibrary("peeracle");
  }

  public class Observer {
    public Observer(long nativeObserver) {
      nativeWebSocketConnectionObserver = nativeObserver;
    }

    public native void onConnect();
    public native void onMessage(byte[] buffer, long length);
    public native void onDisconnect();
    public native void onError();

    private final long nativeWebSocketConnectionObserver;
  }

  public WebSocketsClient(String url, long nativeObserver) {
    observer = new Observer(nativeObserver);
    ws = new WebSocketConnection();

    System.out.println("wooohooo");
  }

  public boolean Init() {
    return false;
  }

  public boolean Connect() {
    return false;
  }

  public boolean Update() {
    return false;
  }

  public boolean Send() {
    return false;
  }

  public boolean Disconnect() {
    return false;
  }

  private final Observer observer;
  private WebSocketConnection ws;
}
