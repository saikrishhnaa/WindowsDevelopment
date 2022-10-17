

//Header files
#include<windows.h>
/*
 Calling convention (CALLBACK):
 1. Where to keep this function in memory
 2. Order of passing parameters in function if more than one parameters present (Left to Right Or Right to Left)
 3. 
*/
//Compiler is always CPU/machine specific/dependent and Linker is OS specific/dependent
//Global functions declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //HWND -> HANDLE -> UINT, UINT -> unsigned int, WPARAM -> WORD -> UINT, LPARAM, LRESULT -> LONG -> long #define STRICT, #pragma argused in windows.h
//Global variable declarations

//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) //HINSTANCE -> HANDLE, LPSTR -> Far(Long) Char*
{
	//Local variables declarations

	WNDCLASSEX wndclass; //struct //WNDCLASS - 10 members, WNDCLASSEX - 12 members
	HWND hwnd;
	MSG msg; //struct
	TCHAR szAppName[] = TEXT("WINDEV");
	
	//Code
	//WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX); //new , count of bytes - cb
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc; //subclassing -> one callback assignment to os at a time, long pointer to function window procedure
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //return type HGDIOBJ -> H Graphics device interfacep
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //IDI_APPLICATION -> MACROS
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); //ID cursor_application
	wndclass.lpszClassName = szAppName; //to don't use predefined window
	wndclass.lpszMenuName = NULL; //lpsz -> long pointer to null/zero terminated string
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); //new , sm = small (Windows explorer)

	//Registration of WNDCLASSEX
	RegisterClassEx(&wndclass);//return - Unique stream immutable - Atom 

	//Creating the window
	hwnd = CreateWindow(
		szAppName, //lpctstr -> long pointer to constantly terminated string
		TEXT("Saikrishna:Window"),
		WS_OVERLAPPEDWINDOW, //WS->Window style , dword -> double word - 32 bit
		CW_USEDEFAULT, //x , CW->create window, int
		CW_USEDEFAULT, //y
		CW_USEDEFAULT, //width
		CW_USEDEFAULT, //height
		NULL, //parent window, HWMND
		NULL, //menu, HMWNU
		hInstance, //HINSTANCE
		NULL //lpvoid -> void far *
	);

	//Show the window
	ShowWindow(hwnd, iCmdShow);

	//Update window
	UpdateWindow(hwnd);

	//Message loop
	while (GetMessage(&msg, NULL, 0, 0)) //Bool -> True -> int(1), Bool -> False -> int(0) //All messages are unique 32 bit unsigned int & are macro WM_
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMSG, WPARAM wParam, LPARAM lParam) //CALLBACK -> Re-entrant function
{
	//Local variables declarations
	TCHAR str[255];
	int num1, num2, num3;

	//Code
	switch (iMSG)
	{
		case WM_CREATE:
			num1 = 25;
			num2 = 75;
			num3 = num1 + num2;
			wsprintf(str, TEXT("Sum of %d and %d is %d"), num1, num2, num3); //TEXT() - convertes ANCI to unicode
			MessageBox(hwnd, str, TEXT("Message"), MB_OK); //MB-MessageBox
			break;
		case WM_KEYDOWN:
			wsprintf(str, TEXT("WM_KEYDOWN message is received"));
			MessageBox(hwnd, str, TEXT("Message"), MB_OK);
			break;
		case WM_LBUTTONDOWN:
			wsprintf(str, TEXT("WM_LBUTTONDOWN message is received"));
			MessageBox(hwnd, str, TEXT("Message"), MB_OK);
			break;
		case WM_RBUTTONDOWN:
			wsprintf(str, TEXT("WM_RBUTTONDOWN message is received"));
			MessageBox(hwnd, str, TEXT("Message"), MB_OK);
			break;
		case WM_DESTROY:
			wsprintf(str, TEXT("WM_DESTROY message is received"));
			MessageBox(hwnd, str, TEXT("Message"), MB_OK);
			//PostQuitMessage(0);
			PostMessage(hwnd, WM_QUIT, 0, 0L);
			break;
		default:
			break;
	}
	return(DefWindowProc(hwnd, iMSG, wParam, lParam));
}
