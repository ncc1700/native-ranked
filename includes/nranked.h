#ifndef NRANKED_H_INCLUDED
#define NRANKED_H_INCLUDED




// OS abstration and raylib stuff


#define USERNAME_SIZE 16
#include <raylib/raylib.h>
#include <stdint.h>

#ifdef _WIN32
#include <stdio.h>
#define safe_sprintf sprintf_s
#include <raylib/raylib_win32.h>
#include <Windows.h>
#define REST() Sleep(100)
#else
#include <unistd.h>
#define REST() sleep(1)
#include <stdio.h>
#define safe_sprintf snprintf
#endif


#define DEBUG_FAIL(message, ...) printf("[-] %s(): " message, __FUNCTION__, ##__VA_ARGS__)
#define DEBUG_PASS(message, ...) printf("[+] %s(): " message, __FUNCTION__, ##__VA_ARGS__)
#define DEBUG_INFO(message, ...) printf("[!] %s(): " message, __FUNCTION__, ##__VA_ARGS__)










#endif