//Header files
#include<windows.h>
#include "Window.h"
#include "HeaderForClientOfComponentWithRegFile.h"

//Global functions declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global variable declarations
ISum* pISum = NULL;
ISubtract* pISubtract = NULL;
IMultiplication* pIMultiplication = NULL;
IDivision* pIDivision = NULL;

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
	// COM Initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM library can not be initialized.\nProgram will now exit."), TEXT("Error"), MB_OK);
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

	CoUninitialize();

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMSG, WPARAM wParam, LPARAM lParam)
{
	// function declarations
	void SafeInterfaceRelease(void);

	//Local variables declarations
	HRESULT hr;
	int iNum1, iNum2, iSum, iSubstraction, iMultiplication, iDivision;
	TCHAR str[255];

	//Code
	switch (iMSG)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum interface can not be obtained."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		// Initialize arguments hardcoded
		iNum1 = 65;
		iNum2 = 45;
		
		// Call SumOfTwoIntegers() of ISum to get the sum
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);

		// Display the result 
		wsprintf(str, TEXT("Sum Of %d and %d is %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		// Call QueryInterface() on ISum, to get ISubtract's pointer
		hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract interface can not be obtained."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		// As ISum is now not needed onwards, release it
		pISum->Release();
		pISum = NULL; // Make released interface NULL

		// Again initialize arguments hardcoded
		iNum1 = 155;
		iNum2 = 55;

		// Call SubtractionOfTwoIntegers() of ISubtract to get the subtraction
		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubstraction);

		// Display the result
		wsprintf(str, TEXT("Subtraction of %d and %d is %d."), iNum1, iNum2, iSubstraction);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		// Call QueryInterface() on IMultiplication, to get ISubtract's pointer
		hr = pISubtract->QueryInterface(IID_IMultiplication, (void**)&pIMultiplication);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication interface can not be obtained."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		// As ISum is now not needed onwards, release it
		pISubtract->Release();
		pISubtract = NULL; // Make released interface NULL

		// Again initialize arguments hardcoded
		iNum1 = 155;
		iNum2 = 55;

		// Call SubtractionOfTwoIntegers() of ISubtract to get the subtraction
		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iMultiplication);

		// Display the result
		wsprintf(str, TEXT("Multiplication of %d and %d is %d."), iNum1, iNum2, iMultiplication);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		// Call QueryInterface() on ISum, to get ISubtract's pointer
		hr = pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision interface can not be obtained."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		// As ISum is now not needed onwards, release it
		pIMultiplication->Release();
		pIMultiplication = NULL; // Make released interface NULL

		// Again initialize arguments hardcoded
		iNum1 = 155;
		iNum2 = 55;

		// Call SubtractionOfTwoIntegers() of ISubtract to get the subtraction
		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iDivision);

		// Display the result
		wsprintf(str, TEXT("Division of %d and %d is %d."), iNum1, iNum2, iDivision);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		// Finally release IDivision
		pIDivision->Release();
		pIDivision = NULL; // Make released interface NULL

		// Exit the application
		DestroyWindow(hwnd);

		break;
	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMSG, wParam, lParam));
}

void SafeInterfaceRelease()
{
	// Code
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}

	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}

	if (pIMultiplication)
	{
		pIMultiplication->Release();
		pIMultiplication = NULL;
	}

	if (pIDivision)
	{
		pIDivision->Release();
		pIDivision = NULL;
	}
}
