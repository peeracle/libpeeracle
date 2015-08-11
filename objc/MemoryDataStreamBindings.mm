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

#include <cstring>
#include <sstream>
#include "MemoryDataStreamBindings.h"


MemoryDataStream::MemoryDataStream(const DataStreamInit &dsInit) :
    _bigEndian(dsInit.bigEndian) {
    }
    
MemoryDataStream::~MemoryDataStream() {
        this->_buffer.clear();
}
    
bool MemoryDataStream::open() {
    return [this->_memoryDataStream open];
}
    
void MemoryDataStream::close() {
}
    
std::streamsize MemoryDataStream::length() const {
    return [this->_memoryDataStream size];
}
    
std::streamsize MemoryDataStream::seek(std::streamsize position) {
    return [this->memoryDataStream seek]
}
    
std::streamsize MemoryDataStream::tell() const {
    return [this->_memoryDataStream tell];
}
    
std::streamsize MemoryDataStream::read(char *buffer,
                                           std::streamsize length) {
    std::streamsize result = 0;
        
    for (int i = 0; i < length; i++) {
        result += this->_read(buffer++);
    }
        
    return result;
}
    
std::streamsize MemoryDataStream::read(int8_t *buffer) {
    return this->_read(buffer);
}
    
std::streamsize MemoryDataStream::read(uint8_t *buffer) {
    return this->_read(buffer);
}
    
std::streamsize MemoryDataStream::read(int16_t *buffer) {
    return this->_read(buffer);
}
    
std::streamsize MemoryDataStream::read(uint16_t *buffer) {
    return this->_read(buffer);
}
    
std::streamsize MemoryDataStream::read(int32_t *buffer) {
    return this->_read(buffer);
}
    
std::streamsize MemoryDataStream::read(uint32_t *buffer) {
    return this->_read(buffer);
}
    
std::streamsize MemoryDataStream::read(float *buffer) {
    return this->_read(buffer);
}
    
std::streamsize MemoryDataStream::read(double *buffer) {
    return this->_read(buffer);
}
    
std::streamsize MemoryDataStream::read(std::string *buffer) {
 
}
    
std::streamsize MemoryDataStream::peek(uint8_t *buffer,
                                        std::streamsize length) {

}
    
std::streamsize MemoryDataStream::peek(int8_t *buffer) {
    return this->_peek(buffer);
}
    
std::streamsize MemoryDataStream::peek(uint8_t *buffer) {
    return this->_peek(buffer);
}
    
std::streamsize MemoryDataStream::peek(int16_t *buffer) {
    return this->_peek(buffer);
}
    
std::streamsize MemoryDataStream::peek(uint16_t *buffer) {
    return this->_peek(buffer);
}
    
std::streamsize MemoryDataStream::peek(int32_t *buffer) {
    return this->_peek(buffer);
}
    
std::streamsize MemoryDataStream::peek(uint32_t *buffer) {
    return this->_peek(buffer);
}
    
std::streamsize MemoryDataStream::peek(float *buffer) {
    return this->_peek(buffer);
}
    
std::streamsize MemoryDataStream::peek(double *buffer) {
    return this->_peek(buffer);
}
    
std::streamsize MemoryDataStream::peek(std::string *value) {
    }
    
template <typename T>
std::streamsize MemoryDataStream::_peek(T *buffer) {

}
    
std::streamsize MemoryDataStream::write(const char *buffer,
                                        std::streamsize length) {
    return this->_write(buffer, length);
}
    
std::streamsize MemoryDataStream::write(int8_t value) {
    return this->_write(value);
}
    
std::streamsize MemoryDataStream::write(uint8_t value) {
    return this->_write(value);
}
    
std::streamsize MemoryDataStream::write(int16_t value) {
    return this->_write(value);
}
    
std::streamsize MemoryDataStream::write(uint16_t value) {
    return this->_write(value);
}
    
std::streamsize MemoryDataStream::write(int32_t value) {
    return this->_write(value);
}
    
std::streamsize MemoryDataStream::write(uint32_t value) {
    return this->_write(value);
}
    
std::streamsize MemoryDataStream::write(float value) {
    return this->_write(value);
}
    
std::streamsize MemoryDataStream::write(double value) {
    return this->_write(value);
}
    
std::streamsize MemoryDataStream::write(const std::string &value) {
    return this->_write(value.c_str(), strlen(value.c_str()) + 1);
}
    
template <typename T>
std::streamsize MemoryDataStream::_write(T buffer,
                                            std::streamsize length) {

}
    
template <typename T>
std::streamsize MemoryDataStream::_write(T value) {
 
}
    