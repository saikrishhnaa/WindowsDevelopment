//Header files
#include<windows.h>
#include "Window.h"
#import "DotNetServer.tlb" no_namespace named_guids raw_interfaces_only

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
	// OLECHAR - Binary string
	OLECHAR* szFunctionName1 = L"SumOfTwoIntegers";
	OLECHAR* szFunctionName2 = L"SubtractionOfTwoIntegers";
	VARIANT vArg[2];
	VARIANT vResult;
	IDispatch *pIDispatch = NULL;
	DISPID dispid;
	DISPPARAMS params;
	HRESULT hr;
	int num1, num2, sum, subtract;
	TCHAR str[255];

	//Code
	switch (iMSG)
	{
		case WM_CREATE:
			hr = CoCreateInstance(CLSID_DotNetServer, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&pIDispatch);
			if (FAILED(hr))
			{
				MessageBox(hwnd, TEXT("CoCreateInstance Failed to give IDispatch."), TEXT("Error"), MB_OK);
				DestroyWindow(hwnd);
			}

			num1 = 275;
			num2 = 225;

			// Get id of SumOfTwoIntegers()
			hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionName1, 1, GetUserDefaultLCID(), &dispid);
			if (FAILED(hr))
			{
				MessageBox(hwnd, TEXT("GetIDsOfNames Failed to give IDs Of SumOfTwoIntegers()."), TEXT("Error"), MB_OK);
				pIDispatch->Release();
				pIDispatch = NULL;
				DestroyWindow(hwnd);
			}


			// Call SumOfTwoIntegers() by passing it's ID to invoke()
			VariantInit(vArg);
			vArg[0].vt = VT_INT;
			vArg[0].intVal = num2; // According to PASCAL Calling convention - right to left argument passing
			vArg[1].vt = VT_INT;
			vArg[1].intVal = num1;
			VariantInit(&vResult);
			params.rgvarg = vArg;
			params.cArgs = 2;
			params.rgdispidNamedArgs = NULL;
			params.cNamedArgs = 0;
			hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &params, &vResult, NULL, NULL);

			sum = vResult.lVal;

			wsprintf(str, TEXT("Sum of %d and %d is %d."), num1, num2, sum);
			MessageBox(hwnd, str, TEXT("Sum"), MB_OK);

			// Get id of SubtractionOfTwoIntegers()
			hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionName2, 1, GetUserDefaultLCID(), &dispid);
			if (FAILED(hr))
			{
				MessageBox(hwnd, TEXT("GetIDsOfNames Failed to give IDs Of SubtractionOfTwoIntegers()."), TEXT("Error"), MB_OK);
				pIDispatch->Release();
				pIDispatch = NULL;
				DestroyWindow(hwnd);
			}


			// Call SubtractionOfTwoIntegers() by passing it's ID to invoke()
			VariantInit(vArg);
			vArg[0].vt = VT_INT;
			vArg[0].intVal = num2; // According to PASCAL Calling convention - right to left argument passing
			vArg[1].vt = VT_INT;
			vArg[1].intVal = num1;
			VariantInit(&vResult);
			params.rgvarg = vArg;
			params.cArgs = 2;
			params.rgdispidNamedArgs = NULL;
			params.cNamedArgs = 0;
			hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &params, &vResult, NULL, NULL);

			subtract = vResult.lVal;

			wsprintf(str, TEXT("Subtraction of %d and %d is %d."), num1, num2, subtract);
			MessageBox(hwnd, str, TEXT("Subtract"), MB_OK);

			VariantClear(&vResult);
			VariantClear(vArg);
			pIDispatch->Release();
			pIDispatch = NULL;

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
