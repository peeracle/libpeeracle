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

#if defined(WEBRTC_WIN)
#include <crtdbg.h>
#include <windows.h>
#endif

#include "test/unittest_main.h"
#include "third_party/googletest/gtest/include/gtest/gtest.h"

/*#include "webrtc/base/flags.h"
#include "webrtc/base/fileutils.h"
#include "webrtc/base/gunit.h"
#include "webrtc/base/logging.h"
#include "webrtc/base/ssladapter.h"*/

#if defined(WEBRTC_WIN)
void TestInvalidParameterHandler(const wchar_t* expression,
                                 const wchar_t* function,
                                 const wchar_t* file,
                                 unsigned int line,
                                 uintptr_t pReserved) {
  std::cerr << "InvalidParameter Handler called.  Exiting.";
  std::cerr << expression << std::endl << function << std::endl << file
                << std::endl << line;
  exit(1);
}
void TestPureCallHandler() {
  std::cerr << "Purecall Handler called.  Exiting.";
  exit(1);
}
int TestCrtReportHandler(int report_type, char* msg, int* retval) {
    std::cerr << "CrtReport Handler called...";
    std::cerr << msg;
  if (report_type == _CRT_ASSERT) {
    exit(1);
  } else {
    *retval = 0;
    return TRUE;
  }
}
#endif  // WEBRTC_WIN

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

#if defined(WEBRTC_WIN)
    // Make sure any errors don't throw dialogs hanging the test run.
  _set_invalid_parameter_handler(TestInvalidParameterHandler);
  _set_purecall_handler(TestPureCallHandler);
  _CrtSetReportHook2(_CRT_RPTHOOK_INSTALL, TestCrtReportHandler);

#ifdef _DEBUG  // Turn on memory leak checking on Windows.
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |_CRTDBG_LEAK_CHECK_DF);
  // if (FLAG_crt_break_alloc >= 0) {
  _crtBreakAlloc = FLAG_crt_break_alloc;
  // }
#endif  // _DEBUG
#endif  // WEBRTC_WIN

#if defined(WEBRTC_WIN)
  // Unhook crt function so that we don't ever log after statics have been
  // uninitialized.
  // if (!FLAG_default_error_handlers)
  _CrtSetReportHook2(_CRT_RPTHOOK_REMOVE, TestCrtReportHandler);
#endif

  int res = RUN_ALL_TESTS();

  return res;
}
