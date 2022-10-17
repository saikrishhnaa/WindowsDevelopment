//Header files
#include<windows.h>
#include "Window.h"
#include "AutomationServer.h"

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
	HRESULT hr;
	
	//Code
	// COM Library Initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Initialization Failed"), TEXT("Error"), MB_OK);
		exit(0);
	}

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
	IMyMath *pIMyMath = NULL;
	HRESULT hr;
	int num1, num2, sum, subtract;
	TCHAR str[255];

	//Code
	switch (iMSG)
	{
		case WM_CREATE:

			hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IMyMath, (void**)&pIMyMath);
			if (FAILED(hr))
			{
				MessageBox(hwnd, TEXT("CoCreateInstance Failed"), TEXT("Error"), MB_OK);
				DestroyWindow(hwnd);
			}

			num1 = 175;
			num2 = 125;

			pIMyMath->SumOfTwoIntegers(num1, num2, &sum);

			wsprintf(str, TEXT("Sum of %d and %d is %d."), num1, num2, sum);
			MessageBox(hwnd, str, TEXT("Sum"), MB_OK);

			pIMyMath->SubtractionOfTwoIntegers(num1, num2, &subtract);
			wsprintf(str, TEXT("Subtraction of %d and %d is %d."), num1, num2, subtract);
			MessageBox(hwnd, str, TEXT("Subtract"), MB_OK);

			pIMyMath->Release();
			pIMyMath = NULL;

			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			CoUninitialize();
			PostQuitMessage(0);
			break;
		default:
			break;
	}
	return(DefWindowProc(hwnd, iMSG, wParam, lParam));
}
