//Header files
#include<windows.h>
#include "Window.h"

//Global functions declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI ThreadProcOne(LPVOID);

DWORD WINAPI ThreadProcTwo(LPVOID);

//Global variable declarations


//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Local variables declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WINDEV");
	
	//Code
	//WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	//Registration of WNDCLASSEX
	RegisterClassEx(&wndclass);

	//Creating the window
	hwnd = CreateWindow(
		szAppName,
		TEXT("Saikrishna:Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//Show the window
	ShowWindow(hwnd, iCmdShow);

	//Update window
	UpdateWindow(hwnd);

	//Message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMSG, WPARAM wParam, LPARAM lParam)
{
	//Local variables declarations
	HANDLE hThread1 = NULL;
	HANDLE hThread2 = NULL;

	//Code
	switch (iMSG)
	{
		case WM_CREATE:

			hThread1 = CreateThread( //kernel32.lib function
				NULL,
				0,
				(LPTHREAD_START_ROUTINE)ThreadProcOne,
				(LPVOID)hwnd,
				0,
				NULL
			);

			hThread1 = CreateThread(
				NULL,
				0,
				(LPTHREAD_START_ROUTINE)ThreadProcTwo,
				(LPVOID)hwnd,
				0,
				NULL
			);
			break;
		case WM_LBUTTONDOWN:
			MessageBox(hwnd, TEXT("This is my messagebox."), TEXT("Message"), MB_OK);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
	}
	return(DefWindowProc(hwnd, iMSG, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param)
{
	//Variable declarations
	HDC hdc;
	TCHAR str[256];
	int i;

	//Code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 0));
	for (i = 0; i < 32767; i++)
	{
		wsprintf(str, TEXT("Numbers in incrementing order: %d"), i); // "/d" while compiling is required for wsprintf() function
		TextOut(hdc, 5, 5, str, wcslen(str)); 
	}
	ReleaseDC((HWND)param, hdc);

	return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID param)
{
	//Variable declarations
	HDC hdc;
	TCHAR str[256];
	int i;

	//Code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 255));
	for (i = 32767; i >= 0; i--)
	{
		wsprintf(str, TEXT("Numbers in decrementing order: %d"), i);
		TextOut(hdc, 5, 20, str, wcslen(str));
	}
	ReleaseDC((HWND)param, hdc);

	return 0;
}
