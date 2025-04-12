#include <windows.h>
#include <stdlib.h>
#include <iostream>
// video: https://www.youtube.com/watch?v=891Fi1kEZxo
int WINAPI WinMain(_IN_ HINSTANCE hInstance, _in_opt_ HINSTANCE hprevIntance, _In_ LPSTR lpCmdLine, _in_ int nShowCmd) {
	WNDCLASSEX wc = {};
	HWND hwnd;
	MSG msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = ;
	wc.hInstance = hInstance;
	wc.lpszClassName = "window";

	hwnd = CreateWindowEx(0, wc.lpszClassName, "Win32 window", WS_OVERLAPPEDWINDOW, 0, 0, 1920, 1080, NULL, NULL, HINSTANCE, NULL);

	if (!hwnd) { __asm__ ( "int $3" ); }

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}