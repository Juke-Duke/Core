#pragma once

#include <core/Core.h>
#include <stdio.h>
#include <stdlib.h>

#if defined __APPLE__ || defined __linux__ || defined __unix__
#include <dlfcn.h>
#include <execinfo.h>
#include <unistd.h>
#if defined __APPLE__
#include <mach-o/dyld.h>
#endif
#elif defined _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
#endif

static inline void __PrintBacktrace() {
#ifdef _WIN32
  auto process = GetCurrentProcess();
  SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
  auto symbolsReady   = SymInitialize(process, null, true);

  auto addresses      = (void* [64]){0};
  auto addressesCount = CaptureStackBackTrace(0, 64, addresses, null);

  for (auto i = (WORD)0; i < addressesCount; ++i) {
    auto address    = addresses[i];
    auto modulePath = (char[MAX_PATH]){"<unknown module>"};
    auto offset     = (unsigned long long)0;

    auto memory     = (MEMORY_BASIC_INFORMATION){};
    if (VirtualQuery(address, &memory, sizeof(memory)) == sizeof(memory)) {
      auto module = (HMODULE)memory.AllocationBase;
      if (GetModuleFileNameA(module, modulePath, MAX_PATH) == 0) {
        strcpy_s(modulePath, sizeof(modulePath), "<unknown module>");
      }
      offset = (unsigned long long)((size_t)address - (size_t)module);
    }

    char moduleStem[260] = {0};
    {
      auto moduleName = strrchr(modulePath, '\\');
      moduleName      = moduleName ? moduleName + 1 : modulePath;
      strcpy_s(moduleStem, sizeof(moduleStem), moduleName);
      auto dot = strrchr(moduleStem, '.');
      if (dot) {
        *dot = '\0';
      }
    }

    char function[1024] = "???";
    char path[2048]     = "";
    auto line           = (unsigned long)0;

    if (symbolsReady) {
      auto symbolBuffer    = (unsigned char[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(char) + 7) / 8]){0};
      auto symbol          = (PSYMBOL_INFO)symbolBuffer;
      symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
      symbol->MaxNameLen   = MAX_SYM_NAME;

      auto displacement    = (DWORD64)0;
      if (SymFromAddr(process, (DWORD64)(size_t)address, &displacement, symbol) && symbol->Name[0] != '\0') {
        strcpy_s(function, sizeof(function), symbol->Name);
      }
    }

    char command[4096] = {0};
    snprintf(
      command,
      sizeof(command),
      "llvm-symbolizer --relative-address --obj=\"%s\" 0x%llx 2>nul",
      modulePath,
      offset
    );

    auto fp = _popen(command, "r");
    if (fp) {
      char functionLine[1024] = {0};
      char locationLine[2048] = {0};

      if (fgets(functionLine, (int)sizeof(functionLine), fp)) {
        functionLine[strcspn(functionLine, "\r\n")] = '\0';
        if (functionLine[0] != '\0' && strcmp(functionLine, "??") != 0) {
          strcpy_s(function, sizeof(function), functionLine);
        }
      }

      if (fgets(locationLine, (int)sizeof(locationLine), fp)) {
        locationLine[strcspn(locationLine, "\r\n")] = '\0';
        if (locationLine[0] != '\0' && strcmp(locationLine, "??") != 0) {
          auto lastColon = strrchr(locationLine, ':');
          if (lastColon) {
            *lastColon     = '\0';
            auto lineColon = strrchr(locationLine, ':');
            if (lineColon) {
              *lineColon      = '\0';
              auto parsedLine = strtoul(lineColon + 1, null, 10);
              if (parsedLine > 0) {
                line = parsedLine;
              }
            }
          }
          strcpy_s(path, sizeof(path), locationLine);
        }
      }

      _pclose(fp);
    }

    if (function[0] == '?' || function[0] == '\0') {
      strcpy_s(function, sizeof(function), moduleStem);
    }

    if (path[0] == '\0') {
      strcpy_s(path, sizeof(path), moduleStem);
    }

    if (strcmp(function, "snprintf") == 0 || strcmp(function, "_snprintf") == 0 || strcmp(function, "__PrintBacktrace") == 0) {
      continue;
    }

    if (line > 0 && strcmp(path, moduleStem) != 0) {
      fprintf(stderr, "  at %s in %s:%lu\n", function, path, line);
    }
    else {
      fprintf(stderr, "  at %s in %s\n", function, moduleStem);
    }
  }

  if (symbolsReady) {
    SymCleanup(process);
  }

  if (addressesCount == 0) {
    fprintf(stderr, "  at <unavailable> in <unavailable>:0\n");
  }
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
    __PrintBacktrace();                                           \
    abort();                                                      \
  } while (false)
