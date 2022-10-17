//Header files
#include<windows.h>
#include "Window.h"

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
	HMODULE hDll = NULL; //HMODULE - HINSTANCE are same
	typedef int (*MakeCubeFunctionPointer)(int);
	MakeCubeFunctionPointer pfnMakeCube = NULL;
	int iNum = 5;
	int iCube;
	TCHAR str[255];

	//Code
	switch (iMSG)
	{
		case WM_CREATE:
			hDll = LoadLibrary(TEXT("MyMathTwo.dll")); //Unsigned 32 bit log int - starting address of the DLL loaded in the caller process address space //LoadLibraryEx()
			if (hDll == NULL) 
			{
				MessageBox(hwnd, TEXT("Load Library Failed"), TEXT("Error"), MB_OK);
				DestroyWindow(hwnd);
			}
			pfnMakeCube = (MakeCubeFunctionPointer)GetProcAddress(hDll, "MakeCube"); //string without TEXT, network competency BSD socket
			if (pfnMakeCube == NULL)
			{
				MessageBox(hwnd, TEXT("GetProcAddress Failed"), TEXT("Error"), MB_OK);
				FreeLibrary(hDll);
				DestroyWindow(hwnd);
			}
			iCube = pfnMakeCube(iNum);
			wsprintf(str, TEXT("Cube of %d is %d"), iNum, iCube);
			MessageBox(hwnd, str, TEXT("Cube"), MB_OK);
			FreeLibrary(hDll);
			hDll = NULL;
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
	}
	return(DefWindowProc(hwnd, iMSG, wParam, lParam));
}
