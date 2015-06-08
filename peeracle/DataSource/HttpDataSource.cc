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

#include <string>
#ifdef USE_CURL
#include "third_party/curl/include/curl/curl.h"
#endif
#include "peeracle/DataSource/HttpDataSource.h"

namespace peeracle {

HttpDataSource::HttpDataSource(const std::string &url) {
#ifdef USE_CURL
  curl_easy_init();
#endif
  HttpDataSource::HttpDataSource(const std::string &url) : url_(url) {
  this->cursor_ = 0;
  curl_global_init(CURL_GLOBAL_ALL);
  this->curl_handle_ = curl_easy_init();
}

static size_t WriteMemoryCallback(void *contents, size_t size,
size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = reinterpret_cast<char*>
    (realloc(mem->memory, mem->size + realsize + 1));
  if (mem->memory == NULL) {
    std::cerr << "not enough memory (realloc returned NULL)" << std::endl;
    return 0;
  }
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

bool HttpDataSource::open() {
  CURLcode res;
  this->chunk_.memory = reinterpret_cast<char*>(malloc(1));
  this->chunk_.size = 0;
  curl_easy_setopt(this->curl_handle_, CURLOPT_URL, this->url_.c_str());
  curl_easy_setopt(curl_handle_, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(this->curl_handle_, CURLOPT_WRITEDATA,
reinterpret_cast<void *>(&this->chunk_));
  curl_easy_setopt(this->curl_handle_, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  res = curl_easy_perform(this->curl_handle_);
  if (res != CURLE_OK)
    return false;
  return true;
}

void HttpDataSource::close() {
  curl_easy_cleanup(this->curl_handle_);
  curl_global_cleanup();
}

std::streamsize HttpDataSource::length() const {
  return static_cast<__int64_t>(this->chunk_.size);
}

std::streamsize HttpDataSource::read(unsigned char *buffer,
                                     std::streamsize length) {
  if (this->cursor_ + length > this->length())
    length = this->length() - this->cursor_;
  strncpy(reinterpret_cast<char*>(buffer),
this->chunk_.memory+this->cursor_, length);
  buffer[length] = '\0';
  return length;
}

std::streamsize HttpDataSource::seek(std::streamsize offset) {
  if (offset <= this->length())
    this->cursor_ = offset;
  else
    this->cursor_ = this->length();
  return this->cursor_;
}

}  // namespace peeracle
