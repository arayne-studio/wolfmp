#include <windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include "mem.h"
#include <windef.h>
#include <stdlib.h>


enum LOG_TYPE {
  LOG_INFO,
  LOG_ERROR,
  LOG_SUCCESS,
  LOG_DEBUG
};

const int byteCodesToInt(BYTE data[]) {
  int value;
  memcpy(&value, data, sizeof(int));
  return value;
}

const std::string currentDateTime() {
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
  return buf;
}

void logger(LOG_TYPE logType, std::string message, ...) {
  std::cout << "[" << currentDateTime() << " ";
  switch(logType) {
    case LOG_INFO:
      std::cout << "\033[93;1m" << "   info";
      break;
    case LOG_ERROR:
      std::cout << "\033[91;1m" << "  error";
      break;
    case LOG_SUCCESS:
      std::cout << "\033[92;1m" << "success";
      break;
    case LOG_DEBUG:
      std::cout << "\033[35;1m" << "  debug";
      break;
  }
  std::cout << "\033[0m] ";
  va_list args;
  va_start(args, message);
  std::vfprintf(stdout, message.c_str(), args);
  std::cout << std::endl;
}

DWORD WINAPI WolfMP(HMODULE hModule) {
  AllocConsole();
  FILE* f = new FILE;
  freopen_s(&f, "CONOUT$", "w", stdout);
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD dwMode = 0;
  GetConsoleMode(hConsole, &dwMode);
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hConsole, dwMode);
  
  logger(LOG_INFO, "Starting client WIP !");
  
  while(true) {
    if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
      break;
    }

    Sleep(5);
  }

  fclose(f);
  FreeConsole();
  FreeLibraryAndExitThread(hModule, 0);
  return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
  case DLL_PROCESS_ATTACH:
    CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)WolfMP, hModule, 0, NULL));
  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}
