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

package org.peeracle.DataSource;

import com.sun.net.httpserver.Headers;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.*;
import java.net.InetSocketAddress;
import java.util.Random;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class HttpDataSourceTest {

  class MyHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange t) throws IOException {
      if (!t.getRequestMethod().equals("GET")) {
        t.sendResponseHeaders(404, 0);
        OutputStream os = t.getResponseBody();
        os.close();
        return;
      }

      Headers h = t.getRequestHeaders();
      if (!h.containsKey("Range")) {
        OutputStream os = t.getResponseBody();
        t.sendResponseHeaders(200, bytes_.length);
        os.write(bytes_);
        os.close();
        return;
      }

      String range = h.get("Range").get(0);
      if (!range.matches("bytes=\\d+-\\d+")) {
        OutputStream os = t.getResponseBody();
        t.sendResponseHeaders(200, bytes_.length);
        os.write(bytes_);
        os.close();
        return;
      }

      String ranges[] = range.split("-");
      int first = Integer.parseInt(ranges[0]);
      int last = Integer.parseInt(ranges[1]);

      if (first < 0 || last > bytes_.length) {
        OutputStream os = t.getResponseBody();
        t.sendResponseHeaders(416, bytes_.length);
        return;
      }

      t.sendResponseHeaders(200, ((last + 1) - first));
      OutputStream os = t.getResponseBody();
      os.write(bytes_, first, last + 1);
      os.close();
    }
  }

  private HttpServer server_;
  private MyHandler handler_;
  private byte[] bytes_;

  @Before
  public void setUp() throws Exception {
    Random rand = new Random();

    bytes_ = new byte[64];
    rand.nextBytes(bytes_);

    handler_ = new MyHandler();
    server_ = HttpServer.create(new InetSocketAddress(8000), 0);
    server_.createContext("/test", handler_);
    server_.setExecutor(null); // creates a default executor
    server_.start();
  }

  @After
  public void tearDown() throws Exception {
    server_.removeContext("/test");
    server_.stop(1);
  }

  @Test
  public void testInvalidCalls() throws Exception {
    long result;
    byte[] bytes = new byte[64];
    String url = "http://some_invalid_url";
    HttpDataSource ds = new HttpDataSource(url);

    result = ds.read(null, 0);
    assertEquals(0, result);

    ds.close();
    ds.open();
  }

  @Test
  public void testReadFullBuffer() throws Exception {
    long result;
    byte[] bytes = new byte[64];
    String url = "http://127.0.0.1:8000/test";
    HttpDataSource ds = new HttpDataSource(url);

    /* Open the stream, should be equal to the stream's length */
    result = ds.open();
    assertEquals(bytes_.length, result);

    /* Read 0 bytes in a null buffer, should return 0 */
    result = ds.read(null, 0);
    assertEquals(0, result);

    /* Read 0 bytes in a valid buffer, should return 0, buffer unchanged */
    bytes[0] = 0;
    result = ds.read(bytes, 0);
    assertEquals(0, result);
    assertEquals(0, bytes[0]);

    /* Close and read, should return 0, buffer unchanged */
    ds.close();
    result = ds.read(bytes, 0);
    assertEquals(0, result);
    assertEquals(0, bytes[0]);

    /* Open the stream, should be equal to the stream's length */
    result = ds.open();
    assertEquals(bytes_.length, result);

    /* Read the entire buffer, should act normally */
    result = ds.read(bytes, bytes_.length);
    assertEquals(bytes_.length, result);
    assertEquals(bytes_, bytes);

    /* Read the entire buffer a second time, should return 0, same buffer */
    bytes[0] = 0;
    result = ds.read(bytes, bytes_.length);
    assertEquals(0, result);
    assertEquals(0, bytes[0]);

    /* Close and read, should return 0, buffer unchanged */
    ds.close();
    result = ds.read(null, 0);
    assertEquals(0, result);
    assertEquals(bytes_[0], bytes[0]);

    /* Read 0 bytes in a valid buffer, should return 0, buffer unchanged */
    result = ds.read(bytes, 0);
    assertEquals(0, result);
    assertEquals(bytes_[0], bytes[0]);

    bytes[0] = 0;
    /* Open the stream, should be equal to the stream's length */
    result = ds.open();
    assertEquals(bytes_.length, result);

    /* Read 0 bytes in a valid buffer, should return 0, buffer unchanged */
    result = ds.read(bytes, 0);
    assertEquals(0, result);
    assertEquals(0, bytes[0]);

    /* Read the entire buffer, should act normally */
    result = ds.read(bytes, bytes_.length);
    assertEquals(bytes_.length, result);
    assertEquals(bytes_, bytes);

    ds.close();
  }

  @Test
  public void testReadPartialBuffer() throws Exception {
    long result;
    byte[] bytes = new byte[64];
    byte[] sample = new byte[4];
    String url = "http://127.0.0.1:8000/test";
    HttpDataSource ds = new HttpDataSource(url);

    /* Open the stream, should be equal to the stream's length */
    result = ds.open();
    assertEquals(bytes_.length, result);

    /* Read 4 bytes in a valid buffer */
    result = ds.read(bytes, 4);
    assertEquals(4, result);
    assertEquals(bytes_[0], bytes[0]);
    assertEquals(bytes_[1], bytes[1]);
    assertEquals(bytes_[2], bytes[2]);
    assertEquals(bytes_[3], bytes[3]);

    /* Read 4 bytes in a valid buffer */
    result = ds.read(bytes, 4);
    assertEquals(4, result);
    assertEquals(bytes_[4], bytes[0]);
    assertEquals(bytes_[5], bytes[1]);
    assertEquals(bytes_[6], bytes[2]);
    assertEquals(bytes_[7], bytes[3]);

    /* Read 0 bytes in a valid buffer, should return 0, buffer unchanged */
    result = ds.read(bytes, 0);
    assertEquals(0, result);
    assertEquals(bytes_[4], bytes[0]);

    /* Read 4 bytes in a valid buffer */
    result = ds.read(bytes, 4);
    assertEquals(4, result);
    assertEquals(bytes_[8], bytes[0]);
    assertEquals(bytes_[9], bytes[1]);
    assertEquals(bytes_[10], bytes[2]);
    assertEquals(bytes_[11], bytes[3]);

    /* Read twice the bytes' length in a valid buffer */
    result = ds.read(bytes, bytes_.length * 2);
    assertEquals(bytes_.length - 12, result);
    assertEquals(bytes_[12], bytes[0]);
    assertEquals(bytes_[13], bytes[1]);
    assertEquals(bytes_[14], bytes[2]);
    assertEquals(bytes_[15], bytes[3]);

    ds.close();

    /* Open the stream, should be equal to the stream's length */
    result = ds.open();
    assertEquals(bytes_.length, result);

    /* Read 4 bytes in a valid buffer */
    result = ds.read(bytes, 4);
    assertEquals(4, result);
    assertEquals(bytes_[0], bytes[0]);
    assertEquals(bytes_[1], bytes[1]);
    assertEquals(bytes_[2], bytes[2]);
    assertEquals(bytes_[3], bytes[3]);

    ds.close();
  }
}