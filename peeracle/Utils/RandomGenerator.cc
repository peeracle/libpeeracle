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

#include "third_party/webrtc/webrtc/base/sslconfig.h"

#if defined(SSL_USE_OPENSSL)
# include <openssl/rand.h>
#elif defined(SSL_USE_NSS_RNG)
# include "pk11func.h"
#elif defined(WEBRTC_WIN)
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  include <Wincrypt.h>
#endif  // WEBRTC_WIN

#include "peeracle/Utils/RandomGenerator.h"

namespace peeracle {

#ifdef WEBRTC_WIN
RandomGenerator::RandomGenerator() : _provider(0) {
#else
RandomGenerator::RandomGenerator() {
#endif
}

#ifdef WEBRTC_WIN
RandomGenerator::~RandomGenerator() {
  if (_provider) {
    ::CryptReleaseContext(_provider, 0);
  }
#else
RandomGenerator::~RandomGenerator() {
#endif
}

bool RandomGenerator::Init(unsigned int seed) {
#if defined(SSL_USE_OPENSSL) || defined(SSL_USE_NSS_RNG)
  return true;
#elif defined(WEBRTC_WIN)
  if (_provider) {
    return true;
  }

  return ::CryptAcquireContextW(&hProvider, 0, 0, PROV_RSA_FULL,
                                CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
#else
  _seed = seed;
  return true;
#endif
}

bool RandomGenerator::Generate(void *buf, size_t len) {
#if defined(SSL_USE_OPENSSL)
  return (RAND_bytes(reinterpret_cast<unsigned char*>(buf), len) > 0);
#elif defined(SSL_USE_NSS_RNG)
  return (PK11_GenerateRandom(reinterpret_cast<unsigned char*>(buf),
                              static_cast<int>(len)) == SECSuccess);
#elif defined(WEBRTC_WIN)
  if (!::CryptGenRandom(_provider, len, buf)) {
    ::CryptReleaseContext(_provider, 0);
    return false;
  }
#else
  char* bytes = reinterpret_cast<char*>(buf);
  for (size_t i = 0; i < len; ++i) {
    bytes[i] = static_cast<char>(rand_r(&_seed));
  }
  return true;
#endif
}

}  // namespace peeracle
