//Header files
#include<stdio.h>
#include<windows.h>
#include "Window.h"
#include "ClassFactoryDllServerWithRegFile.h"

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
	//COM Library Initialization
	hr = CoInitialize(NULL); //Previously it was OleInitialize
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


	//COM Uninitialization
	CoUninitialize();

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMSG, WPARAM wParam, LPARAM lParam)
{
	//Local variables declarations
	ISum* pISum = NULL;
	ISubstract* pISubstract = NULL;
	HRESULT hr;
	int n1, n2, sum, sub;
	TCHAR str[255];

	//Code
	switch (iMSG)
	{
		case WM_CREATE:
			hr = CoCreateInstance(CLSID_SumSubstract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
			if (FAILED(hr))
			{
				MessageBox(hwnd, TEXT("ISum Interface can not be obtained"), TEXT("Error"), MB_OK);
				DestroyWindow(hwnd);
			}
			n1 = 55;
			n2 = 45;
			pISum->SumOfTwoIntergers(n1, n2, &sum);
			wsprintf(str, TEXT("Sum of %d and %d is %d"), n1, n2, sum);
			MessageBox(hwnd, str, TEXT("Sum"), MB_OK);

			pISum->QueryInterface(IID_ISubstract, (void**)&pISubstract);
			pISubstract->SubstractionOfTwoIntegers(n1, n2, &sub);
			wsprintf(str, TEXT("Substraction of %d and %d is %d"), n1, n2, sub);
			MessageBox(hwnd, str, TEXT("Substract"), MB_OK);

			//Safe Release
			if (pISubstract)
			{
				pISubstract->Release();
				pISubstract = NULL;
			}

			if (pISum)
			{
				pISum->Release();
				pISum = NULL;
			}

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
