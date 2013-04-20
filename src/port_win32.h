// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
//
// See port_example.h for documentation for the following types/functions.

#pragma once

#if defined(OS_MACOSX) || defined(OS_FREEBSD)
#include <machine/endian.h>
#else
//#include <endian.h>
#define LITTLE_ENDIAN
#endif

#ifdef SNAPPY
#include <snappy.h>
#endif
#include <stdint.h>
#include <string>
#include "atomic_pointer.h"

#ifdef LITTLE_ENDIAN
#define IS_LITTLE_ENDIAN true
#else
#define IS_LITTLE_ENDIAN (__BYTE_ORDER == __LITTLE_ENDIAN)
#endif

#if defined(OS_MACOSX) || defined(OS_SOLARIS) || defined(OS_FREEBSD)
#define fread_unlocked fread
#define fwrite_unlocked fwrite
#define fflush_unlocked fflush
#endif

#if defined(OS_MACOSX) || defined(OS_FREEBSD)
#define fdatasync fsync
#endif

namespace slib {
namespace port {

static const bool kLittleEndian = IS_LITTLE_ENDIAN;

class CondVar;

class Mutex {
 public:
  Mutex();
  ~Mutex();

  void Lock();
  void Unlock();
  void AssertHeld() {}

 private:
  friend class CondVar;

  CRITICAL_SECTION cs;
  // No copying
  Mutex(const Mutex&);
  void operator=(const Mutex&);
};

class CondVar {
 public:
  explicit CondVar(Mutex* mu);
  ~CondVar();
  void Wait();
  void Signal();
  void SignalAll();

 private:
  CONDITION_VARIABLE cond;
  Mutex* mu_;
};

inline bool GetHeapProfile(void (*func)(void*, const char*, int), void* arg) {
  return false;
}

}  // namespace port
}  // namespace slib
