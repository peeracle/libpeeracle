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

#import "Metadata+Internal.h"

#include "peeracle/Metadata/Metadata.h"

@implementation Metadata {
  peeracle::MetadataInterface *_metadata;
}

/*@property(nonatomic, readonly) NSString* hash;
@property(nonatomic, readonly) NSUInteger magic;
@property(nonatomic, readonly) NSUInteger version;
@property(nonatomic) NSString* hashAlgorithm;
@property(nonatomic) NSUInteger timecodeScale;
@property(nonatomic) double duration;
@property(nonatomic) NSArray* trackerUrls;
@property(nonatomic, readonly) NSArray* streams;*/

- (NSString*) hash {
  return [NSString stringWithCString:_metadata->getId().c_str()
                            encoding:[NSString defaultCStringEncoding]];
}

- (void) setHashAlgorithm:(NSString*)value {
  _metadata->setHashAlgorithm([value UTF8String]);
}

- (void) setTimecodeScale:(NSUInteger)value {
  _metadata->setTimecodeScale(value);
}

- (void) setDuration:(double)value {
  _metadata->setDuration(value);
}

- (id) init {
  _metadata = new peeracle::Metadata();
}

- (void) dealloc {
  delete _metadata;
}

@end

@implementation Metadata (Internal)

- (peeracle::MetadataInterface*) metadata {
  return _metadata;
}

@end
