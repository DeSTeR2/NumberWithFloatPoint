#include <iostream>
using namespace std;

#include "Double.h";


#define _WIN32_WINNT 0x0600

#include <stdio.h>
#include <windows.h>
#include <fileapi.h>


#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

/**
 * Check if STD_OUTPUT_HANDLE or STD_ERROR_HANDLE is redirected to a file.
 */
BOOL IsRedirectedToFile(DWORD stdHandle) {
	BOOL result = FALSE;

	HANDLE hStd = GetStdHandle(stdHandle);
	if (hStd != INVALID_HANDLE_VALUE) {
		if (GetFinalPathNameByHandle(hStd, NULL, 0, 0) != 0 || GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
			result = TRUE;
		}
	}

	return result;
}

/**
 * Check if the current console supports ANSI colors.
 */
BOOL HaveColorSupport() {
	static BOOL result = 2;
	if (result == 2) {
		const DWORD MINV_MAJOR = 10, MINV_MINOR = 0, MINV_BUILD = 10586;
		result = FALSE;
		HMODULE hMod = GetModuleHandle(TEXT("ntdll.dll"));
		if (hMod) {
			RtlGetVersionPtr fn = (RtlGetVersionPtr)GetProcAddress(hMod, "RtlGetVersion");
			if (fn != NULL) {
				RTL_OSVERSIONINFOW rovi = { 0 };
				rovi.dwOSVersionInfoSize = sizeof(rovi);
				if (fn(&rovi) == 0) {
					if (
						rovi.dwMajorVersion > MINV_MAJOR
						||
						(
							rovi.dwMajorVersion == MINV_MAJOR
							&&
							(
								rovi.dwMinorVersion > MINV_MINOR
								||
								(
									rovi.dwMinorVersion == MINV_MINOR
									&& rovi.dwBuildNumber >= MINV_BUILD
									)
								)
							)
						) {
						result = TRUE;
					}
				}
			}
		}
	}
	return result;
}

/**
 * Check if the current console has ANSI colors enabled.
 */
BOOL ColorSupportEnabled() {
	BOOL result = FALSE;
	if (HaveColorSupport()) {
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hStdOut != INVALID_HANDLE_VALUE) {
			DWORD mode;
			if (GetConsoleMode(hStdOut, &mode)) {
				if (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) {
					result = TRUE;
				}
			}
		}
	}

	return result;
}

int main()
{
	
	printf((ColorSupportEnabled() && !IsRedirectedToFile(STD_OUTPUT_HANDLE)) ? "\x1b[92mMax possible number:\n\x1b[0m" : "<skipped>");
    Double MAX (0, "11111111110", "1111111111111");
	printf((ColorSupportEnabled() && !IsRedirectedToFile(STD_OUTPUT_HANDLE)) ? "\x1b[92mMin possible number:\n\x1b[0m" : "<skipped>");
	Double MIN (1, "11111111110", "0000000000000");
	printf((ColorSupportEnabled() && !IsRedirectedToFile(STD_OUTPUT_HANDLE)) ? "\x1b[92mMinimal greater 0:\n\x1b[0m" : "<skipped>");
	Double minGZ(0, "00000000001", "000000000000"); 
	printf((ColorSupportEnabled() && !IsRedirectedToFile(STD_OUTPUT_HANDLE)) ? "\x1b[92m+1,0E0:\n\x1b[0m" : "<skipped>");
	Double null = 0;
	printf((ColorSupportEnabled() && !IsRedirectedToFile(STD_OUTPUT_HANDLE)) ? "\x1b[92m+INFINITY:\n\x1b[0m" : "<skipped>");
	Double pInf = INFINITY;
	printf((ColorSupportEnabled() && !IsRedirectedToFile(STD_OUTPUT_HANDLE)) ? "\x1b[92m-INFINITY:\n\x1b[0m" : "<skipped>");
	Double nInf = -INFINITY;
	printf((ColorSupportEnabled() && !IsRedirectedToFile(STD_OUTPUT_HANDLE)) ? "\x1b[92mNon normalaze:\n\x1b[0m" : "<skipped>");
	Double nNormalize(0, "00000000000", "00000000000000");
	printf((ColorSupportEnabled() && !IsRedirectedToFile(STD_OUTPUT_HANDLE)) ? "\x1b[92mNaN number:\n\x1b[0m" : "<skipped>");
	Double NaN;
	
	printf((ColorSupportEnabled() && !IsRedirectedToFile(STD_OUTPUT_HANDLE)) ? "\x1b[92mEnter the number:\n\x1b[0m" : "<skipped>");
	double num;
	cin >> num;
	Double myNum = num;
}
