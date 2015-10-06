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

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.util.Random;

import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TestName;

import static org.junit.Assert.*;

public class FileDataSourceTest {
  @Rule
  public TestName name = new TestName();

  private File temp_;
  private String filename_;
  private byte[] bytes_;

  @Before
  public void setUp() throws Exception {
    Random rand = new Random();
    bytes_ = new byte[64];
    rand.nextBytes(bytes_);

    temp_ = File.createTempFile(name.getMethodName(), ".bin");
    filename_ = name.getMethodName() + ".bin";
    FileOutputStream output = new FileOutputStream(temp_);

    output.write(bytes_);
    output.close();
  }

  @After
  public void tearDown() throws Exception {
    temp_.delete();
  }

  @Test
  public void testInvalidCalls() throws Exception {
    long result;
    byte[] bytes = new byte[64];
    String url = "http://some_invalid_url";
    FileDataSource ds = new FileDataSource(filename_);

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
    FileDataSource ds = new FileDataSource(filename_);

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
    FileDataSource ds = new FileDataSource(filename_);

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