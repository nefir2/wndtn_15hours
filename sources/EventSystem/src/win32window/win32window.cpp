#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <cstdio>
// video: https://www.youtube.com/watch?v=891Fi1kEZxo
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_MOUSEMOVE:
			POINT p;
			GetCursorPos(&p);
			std::cout << "Mouse pos event, x" << p.x << " y" << p.y << std::endl;
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default: return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

#ifdef _MSC_VER //если запущено через visual studio.
int WINAPI WinMain(_IN_ HINSTANCE hInstance, _in_opt_ HINSTANCE hprevIntance, _In_ LPSTR lpCmdLine, _in_ int nShowCmd) {
	AllocConsole();
	HANDLE stdHandle;
	int hConsole;
	FILE* fp;
	stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsole = _open_osfhandle((long)stdHandle, _O_TEXT);
	fp = _fdopen(hConsole, "w");

	freopen_s(&fp, "CONOUT&", "w", stdout);


	WNDCLASSEX wc = {};
	HWND hwnd;
	MSG msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = "window";

	RegisterClassEx(&wc);

	hwnd = CreateWindowEx(0, wc.lpszClassName, "Win32 window", WS_OVERLAPPEDWINDOW, 0, 0, 1920, 1080, NULL, NULL, hInstance, NULL);

	if (!hwnd) { __asm__ ( "int $3" ); }

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevIntance, LPSTR lpCmdLine, int nShowCmd) {
	//не рекомендуется это запускать через g++.
	AllocConsole();
	HANDLE stdHandle;
	int hConsole;
	FILE* fp;
	stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsole = _open_osfhandle((long)stdHandle, _O_TEXT);
	fp = fdopen(hConsole, "w");

	freopen("CONOUT&", "w", stdout);

	WNDCLASSEX wc = {};
	HWND hwnd;
	MSG msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = "window";

	RegisterClassEx(&wc);

	hwnd = CreateWindowEx(0, wc.lpszClassName, "Win32 window", WS_OVERLAPPEDWINDOW, 0, 0, 1920, 1080, NULL, NULL, hInstance, NULL);

	if (!hwnd) { __asm__ ( "int $3" ); }

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
#endif