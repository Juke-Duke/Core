#pragma once

#include <core/Core.h>

#if defined __APPLE__ || defined __linux__ || defined __unix__
#include <dlfcn.h>
#include <execinfo.h>
#include <unistd.h>
#if defined __APPLE__
#include <mach-o/dyld.h>
#endif
#elif defined _WIN32 || defined _WIN64
#define WIN32_LEAN_AND_MEAN
#include <dbghelp.h>
#include <windows.h>
#endif

static inline void __PrintBacktrace() {
#ifdef _WIN32
  HANDLE process       = GetCurrentProcess();
  HANDLE thread        = GetCurrentThread();
  CONTEXT context      = {0};
  context.ContextFlags = CONTEXT_FULL;
  RtlCaptureContext(&context);

  SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
  if (!SymInitialize(process, NULL, TRUE)) {
    return;
  }

  STACKFRAME64 frame = {0};
#ifdef _M_X64
  frame.AddrPC.Offset    = context.Rip;
  frame.AddrStack.Offset = context.Rsp;
  frame.AddrFrame.Offset = context.Rbp;
  frame.AddrPC.Mode      = AddrModeFlat;
  frame.AddrStack.Mode   = AddrModeFlat;
  frame.AddrFrame.Mode   = AddrModeFlat;
#else
  frame.AddrPC.Offset    = context.Eip;
  frame.AddrStack.Offset = context.Esp;
  frame.AddrFrame.Offset = context.Ebp;
  frame.AddrPC.Mode      = AddrModeFlat;
  frame.AddrStack.Mode   = AddrModeFlat;
  frame.AddrFrame.Mode   = AddrModeFlat;
#endif

  Bool skip_first = true;
  while (StackWalk64(
#ifdef _M_X64
    IMAGE_FILE_MACHINE_AMD64,
#else
    IMAGE_FILE_MACHINE_I386,
#endif
    process,
    thread,
    &frame,
    &context,
    NULL,
    SymFunctionTableAccess64,
    SymGetModuleBase64,
    NULL
  )) {
    if (skip_first) {
      skip_first = false;
      continue;
    }

    char symbol_buffer[sizeof(SYMBOL_INFO) + 256] = {0};
    SYMBOL_INFO* symbol                           = (SYMBOL_INFO*)symbol_buffer;
    symbol->SizeOfStruct                          = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen                            = 256;

    DWORD64 address                               = frame.AddrPC.Offset;
    if (!SymFromAddr(process, address, NULL, symbol)) {
      fprintf(stderr, "  at 0x%llx\n", (unsigned long long)address);
      continue;
    }

    IMAGEHLP_LINE64 lineInfo = {0};
    lineInfo.SizeOfStruct    = sizeof(lineInfo);
    DWORD lineDisplacement   = 0;
    if (SymGetLineFromAddr64(process, address, &lineDisplacement, &lineInfo) && lineInfo.FileName) {
      auto path = strdup(lineInfo.FileName);
      if (path) {
        auto segment = path;
        while (*segment) {
          if (*segment == '\\') {
            *segment = '/';
          }
          ++segment;
        }

        fprintf(stderr, "  at %s in %s:%lu\n", symbol->Name, path, (unsigned long)lineInfo.LineNumber);
        free(path);
        continue;
      }
    }

    IMAGEHLP_MODULE64 moduleInfo = {0};
    moduleInfo.SizeOfStruct      = sizeof(moduleInfo);
    if (SymGetModuleInfo64(process, address, &moduleInfo) && moduleInfo.ImageName) {
      auto path = strdup(moduleInfo.ImageName);
      if (path) {
        auto segment = path;
        while (*segment) {
          if (*segment == '\\') {
            *segment = '/';
          }
          ++segment;
        }

        fprintf(stderr, "  at %s in %s\n", symbol->Name, path);
        free(path);
        continue;
      }
    }

    fprintf(stderr, "  at %s\n", symbol->Name);
  }

  SymCleanup(process);
#else
  auto capacity       = 64;
  auto addressesCount = 0;
  auto addresses      = (void**)null;

  while (true) {
    addresses      = realloc(addresses, capacity * sizeof(void*));
    addressesCount = (Int)backtrace(addresses, (int)capacity);
    if (addressesCount < capacity) {
      break;
    }
    capacity *= 2;
  }

  auto symbols = backtrace_symbols(addresses, (int)addressesCount);

  for (auto i = 1; i < addressesCount; ++i) {
    auto info = (Dl_info){};
    if (!dladdr(addresses[i], &info)) {
      continue;
    }

    auto command = (char*)null;
#if defined __APPLE__
    if (asprintf(&command, "atos --fullPath -o %s -l %p %p 2>/dev/null", info.dli_fname, info.dli_fbase, addresses[i]) == -1) {
      command = null;
    }
#else
    if (asprintf(&command, "addr2line -e %s -fp %p 2>/dev/null", info.dli_fname, addresses[i]) == -1) {
      command = null;
    }
#endif
    auto fp = command ? popen(command, "r") : null;
    free(command);
    if (!fp) {
      continue;
    }

    auto line      = (char*)null;
    auto lineCount = (size_t)0;
    if (getline(&line, &lineCount, fp) == -1) {
      free(line);
      pclose(fp);
      continue;
    }

    auto function      = line;
    auto functionEnd   = strstr(function, " (in ");
    *functionEnd       = '\0';

    auto path          = strstr(functionEnd + 1, " (");
    path               = path ? path + 2 : functionEnd + 5;
    *strstr(path, ")") = '\0';

    auto segment       = strstr(path, "/./");
    while (segment) {
      memmove(segment + 1, segment + 3, strlen(segment + 3) + 1);
      segment = strstr(segment + 1, "/./");
    }

    fprintf(stderr, "  at %s in %s\n", function, path);

    free(line);
    pclose(fp);
  }

  free(symbols);
  free(addresses);
#endif
}

#define Error(format, ...)                                        \
  do {                                                            \
    fflush(null);                                                 \
    fprintf(stderr, "\n" format "\n" __VA_OPT__(, ) __VA_ARGS__); \
    __PrintBacktrace();                                            \
    abort();                                                      \
  } while (false)
