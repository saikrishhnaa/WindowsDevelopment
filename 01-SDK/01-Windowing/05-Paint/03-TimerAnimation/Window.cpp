//Header files
#include<windows.h>
#include "Window.h"

//Macros
#define ID_NUMBER 501

//Global functions declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
	UpdateWindow(hwnd); //SEND WM_PAINT

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
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	HBRUSH hbrush;
	static int iPaintFlag = 0; 

	//Code
	switch (iMSG)
	{
		case WM_CREATE:
			SetTimer(hwnd, ID_NUMBER, 1000, NULL);
			break;
		case WM_TIMER:
			KillTimer(hwnd, ID_NUMBER);
			iPaintFlag++;
			iPaintFlag %= 9;
			InvalidateRect(hwnd, NULL, true); //POST WM_PAINT
			SetTimer(hwnd, ID_NUMBER, 1000, NULL);
			break;
		case WM_PAINT:
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			if (iPaintFlag == 1)
				hbrush = CreateSolidBrush(RGB(255, 0, 0));
			else if (iPaintFlag == 2)
				hbrush = CreateSolidBrush(RGB(0, 255, 0));
			else if (iPaintFlag == 3)
				hbrush = CreateSolidBrush(RGB(0, 0, 255));
			else if (iPaintFlag == 4)
				hbrush = CreateSolidBrush(RGB(0, 255, 255));
			else if (iPaintFlag == 5)
				hbrush = CreateSolidBrush(RGB(255, 0, 255));
			else if (iPaintFlag == 6)
				hbrush = CreateSolidBrush(RGB(255, 255, 0));
			else if (iPaintFlag == 7)
				hbrush = CreateSolidBrush(RGB(0, 0, 0));
			else if (iPaintFlag == 8)
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
			else
				hbrush = CreateSolidBrush(RGB(128, 128, 128)); //Medium Grey
			FillRect(hdc, &rc, hbrush);
			DeleteObject(hbrush);
			EndPaint(hwnd, &ps);
			break;
		case WM_DESTROY:
			KillTimer(hwnd, ID_NUMBER);
			PostQuitMessage(0);
			break;
		default:
			break;
	}
	return(DefWindowProc(hwnd, iMSG, wParam, lParam));
}
