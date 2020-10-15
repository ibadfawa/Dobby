#ifndef PLATFORM_INTERFACE_COMMON_PLATFORM_H
#define PLATFORM_INTERFACE_COMMON_PLATFORM_H

#include <stdarg.h>

#include "PlatformUnifiedInterface/StdMemory.h"

namespace base {

// ================================================================
// base :: ThreadLocalStorageInterface

class ThreadLocalStorageInterface {
  using LocalStorageKey = int32_t;

  // Thread-local storage.
  static LocalStorageKey CreateThreadLocalKey();
  static void            DeleteThreadLocalKey(LocalStorageKey key);
  static void *          GetThreadLocal(LocalStorageKey key);
  static int             GetThreadLocalInt(LocalStorageKey key) {
    return static_cast<int>(reinterpret_cast<intptr_t>(GetThreadLocal(key)));
  }
  static void SetThreadLocal(LocalStorageKey key, void *value);
  static void SetThreadLocalInt(LocalStorageKey key, int value) {
    SetThreadLocal(key, reinterpret_cast<void *>(static_cast<intptr_t>(value)));
  }
  static bool HasThreadLocal(LocalStorageKey key) {
    return GetThreadLocal(key) != nullptr;
  }
};

// ================================================================
// base :: Thread

class Thread {
public:
  // Thread(dispatch_function_t func, void *ctx) : func_(func), ctx_(ctx)

  Thread(const char *name);

  ~Thread() {
  }

public:
  // void dispatch_handler() {
  //   func_(ctx_);
  // }

  void Start();

  virtual void Run() = 0;

  const char *name() const {
    return thread_name_;
  }

private:
  char thread_name_[FILENAME_MAX];

  void *thread_package_;
};
} // namespace base

// ================================================================
// base :: OSMemory

class OSMemory {
public:
  static int PageSize();

  static void *Allocate(void *address, int size, MemoryPermission access);

  static bool Free(void *address, const int size);

  static bool Release(void *address, int size);

  static bool SetPermission(void *address, int size, MemoryPermission access);
};

// ================================================================
// base :: OSPrint

class OSPrint {
public:
  // Print output to console. This is mostly used for debugging output.
  // On platforms that has standard terminal output, the output
  // should go to stdout.
  static void Print(const char *format, ...);

  static void VPrint(const char *format, va_list args);

  // Print error output to console. This is mostly used for error message
  // output. On platforms that has standard terminal output, the output
  // should go to stderr.
  static void PrintError(const char *format, ...);

  static void VPrintError(const char *format, va_list args);
};

#endif