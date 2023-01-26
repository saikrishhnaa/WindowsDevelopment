/*
 * Command to compile : cl.exe /c /EHsc DataEntryScreen.cpp
   Command to link and create .exe : link.exe DataEntryScreen.obj user32.lib gdi32.lib kernel32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS
 */

// Header files
#include<windows.h>
#include<iostream>
#include<fstream>
#include "DataEntryScreen.h"
#include "DataEntryDialog.h"
#include "ClassFactoryDllServerForFileInput.h"
#include "HeaderForClientOfContainmentForFileOutput.h"
#include "HeaderForClientOfAggregationForFileInput.h"
#include "AutomationDllServerForFileOutput.h"

using namespace std;

// Splash screen status messages
#define SZ_INIT TEXT("Initializing application...")
#define SZ_LOAD TEXT("Loading required resources...")
#define SZ_CLOSE TEXT("Launching application in a moment...")
#define SZ_SPLASH TEXT("Data Capture")

// Splash screen timer ids
#define ID_TIMER_CLOSE 0x1111
#define ID_TIMER_INIT 0x1112
#define ID_TIMER_LOAD 0x1113
#define ID_TIMER_DONE 0x1114

#import "DotNetServerForFileInput.tlb" no_namespace named_guids raw_interfaces_only

// Global structure declarations
struct UserInput
{
	char name[50], education[50], company[50];
	int birthday, birthmonth, birthyear;
};

// Global functions declarations
LRESULT CALLBACK SplashWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DataEntryDialogProc(HWND, UINT, WPARAM, LPARAM);

// Global variable declarations
static HBRUSH hBrush;

// Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Local variable declarations
	WNDCLASSEX mainWndClass;
	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WINDEV");
	TCHAR SplashWndClass[] = TEXT("SplashWindow");
	HRESULT hr;

	// Code
	// COM Library Initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Initialization Failed"), TEXT("Error"), MB_OK);
		exit(0);
	}

	// Splash Window
	//WNDCLASSEX initialization
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = (WNDPROC)SplashWndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(DataCaptureIcon));
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = SplashWndClass;
	wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(DataCaptureIcon));

	// Registration of WNDCLASSEX
	RegisterClassEx(&wndClass);

	RECT rect;
	int splashwidth = 600;
	int splashheight = 400;

	SystemParametersInfo(SPI_GETWORKAREA, 0, (LPVOID)&rect, 0);

	// Create the window
	hwnd = CreateWindowEx(WS_EX_TOOLWINDOW,
		SplashWndClass,
		NULL,
		WS_OVERLAPPED,
		(rect.right - rect.left - splashwidth) / 2,
		(rect.bottom - rect.top - splashheight) / 2,
		splashwidth,
		splashheight,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hwnd)
	{
		return FALSE;
	}

	// Show the window
	ShowWindow(hwnd, iCmdShow);

	// Update the window
	UpdateWindow(hwnd);

	// Message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// COM Uninitialization
	CoUninitialize();

	return((int)msg.wParam);
}

LRESULT CALLBACK SplashWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Local variables declarations

	//Code
	switch (message)
	{
		case WM_NCCALCSIZE: // Capture this message and return null
			return NULL;
		case WM_CREATE:		
			SetTimer(hWnd, ID_TIMER_INIT, 1000, NULL);
			SetTimer(hWnd, ID_TIMER_LOAD, 2000, NULL);
			SetTimer(hWnd, ID_TIMER_DONE, 4000, NULL);
			SetTimer(hWnd, ID_TIMER_CLOSE, 5000, NULL);
			break;
		case WM_PAINT:
		{
			// Paint background to the splash screen
			PAINTSTRUCT ps = { 0 };
			HDC hDC = BeginPaint(hWnd, &ps);
			hBrush = CreateSolidBrush(RGB(204, 204, 255));
			FillRect(hDC, &(ps.rcPaint), hBrush);

			// Draw application title text on splash screen
			RECT rect;
			GetClientRect(hWnd, &rect);
			SetTextColor(hDC, 0x00000000);
			SetBkMode(hDC, TRANSPARENT);
			rect.left = 90;
			rect.top = 180;
			HFONT hFont = CreateFontA(-40, -30, 0, 0, 600, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Arial"));
			HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
			DrawText(hDC, SZ_SPLASH, -1, &rect, DT_SINGLELINE | DT_NOCLIP | DT_WORDBREAK);
			SelectObject(hDC, hOldFont);
			DeleteDC(hDC);

			EndPaint(hWnd, &ps);
			break;
		}
		break;
		case WM_DESTROY:
			DialogBox(NULL, "DATAENTRY", NULL, (DLGPROC)DataEntryDialogProc);
			PostQuitMessage(0);
			break;
		case WM_TIMER:
		{
			HDC hDC = GetDC(hWnd);
			RECT rect = { 0 };
			GetClientRect(hWnd, &rect);
			SetBkColor(hDC, RGB(204, 204, 255));
			KillTimer(hWnd, wParam);

			// Changing application status texts in splash screen on timer
			switch (wParam)
			{
			case ID_TIMER_CLOSE:
				DestroyWindow(hWnd);
				break;
			case ID_TIMER_INIT:
				TextOut(hDC, rect.right - 160, rect.bottom - 20, SZ_INIT, lstrlen(SZ_INIT));
				break;
			case ID_TIMER_LOAD:
				TextOut(hDC, rect.right - 200, rect.bottom - 20, SZ_LOAD, lstrlen(SZ_LOAD));
				break;
			case ID_TIMER_DONE:
				TextOut(hDC, rect.right - 250, rect.bottom - 20, SZ_CLOSE, lstrlen(SZ_CLOSE));
				break;
			}
			ReleaseDC(hWnd, hDC);
		}
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Toogle read or write mode in EditText
void toggleDataEntryDlgEditTextVisibility(HWND hDlg, UINT visibility)
{
	SendDlgItemMessage(hDlg, ID_ETNAME, EM_SETREADONLY, visibility, 0);
	SendDlgItemMessage(hDlg, ID_ETBIRTHDAY, EM_SETREADONLY, visibility, 0);
	SendDlgItemMessage(hDlg, ID_ETBIRTHMONTH, EM_SETREADONLY, visibility, 0);
	SendDlgItemMessage(hDlg, ID_ETBIRTHYEAR, EM_SETREADONLY, visibility, 0);
	SendDlgItemMessage(hDlg, ID_ETEDUCATION, EM_SETREADONLY, visibility, 0);
	SendDlgItemMessage(hDlg, ID_ETCOMPANY, EM_SETREADONLY, visibility, 0);
}

// Split string on dash(-) and next line
void splitStr(string str, string splittedString[6])
{
	TCHAR s[300];
	int i = 0;
	int begin = 0;
	int end = 0;
	while (str[end] != '\0')
	{
		if (str[end] == '\n' || str[end] == '-')
		{
			splittedString[i] = str.substr(begin, end - begin);
			i++;
			begin = end + 1;
		}
		end++;
	}
}

// Convert BSTR type to string
string convertBstrToStr(BSTR source) {
	_bstr_t wrapped_bstr = _bstr_t(source);
	int length = wrapped_bstr.length();
	char* char_array = new char[length];
	strcpy_s(char_array, length + 1, wrapped_bstr);
	return char_array;
}

// Check is birthdate valid or not 
bool isBirthDateValid(int day, int month, int year)
{
	if (year >= 1985 && year <= 2000)
	{
		if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 0 && day <= 31)
			return true;

		if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 0 && day <= 30)
			return true;
		if (month == 2)
		{
			if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) && day > 0 && day <= 29)
				return true;
			if (day > 0 && day <= 28)
				return true;
			return false;
		}
		return false;
	}
	return false;
}

// Check validity and get user entered data
bool GetAndValidateUserEnteredData(HWND hDlg, struct UserInput* in)
{
	bool isEnteredDataValid = true;
	LPCSTR fieldData;

	// Get the user-entered name
	GetDlgItemText(hDlg, ID_ETNAME, in->name, 50);
	if (strlen(in->name) == 0)
	{
		fieldData = "Name field should not be empty.";
		isEnteredDataValid = false;
	}
	else
		fieldData = "";
	SetDlgItemText(hDlg, ID_TNAMEVALIDATOR, fieldData);

	// Get the user-entered education
	GetDlgItemText(hDlg, ID_ETEDUCATION, in->education, 50);
	if (strlen(in->education) == 0)
	{
		fieldData = "Education field should not be empty.";
		isEnteredDataValid = false;
	}
	else
		fieldData = "";
	SetDlgItemText(hDlg, ID_TEDUCATIONVALIDATOR, fieldData);

	// Get the user-entered company
	GetDlgItemText(hDlg, ID_ETCOMPANY, in->company, 50);
	if (strlen(in->company) == 0)
	{
		fieldData = "Company field should not be empty.";
		isEnteredDataValid = false;
	}
	else
		fieldData = "";
	SetDlgItemText(hDlg, ID_TCOMPANYVALIDATOR, fieldData);

	// Get the user-entered birthday
	in->birthday = GetDlgItemInt(hDlg, ID_ETBIRTHDAY, NULL, TRUE);
	// Get the user-entered month
	in->birthmonth = GetDlgItemInt(hDlg, ID_ETBIRTHMONTH, NULL, TRUE);
	// Get the user-entered year
	in->birthyear = GetDlgItemInt(hDlg, ID_ETBIRTHYEAR, NULL, TRUE);
	bool isDobValid = isBirthDateValid(in->birthday, in->birthmonth, in->birthyear);
	if (!isDobValid)
	{
		fieldData = "Entered birthdate is not valid.";
		isEnteredDataValid = false;
	}
	else
		fieldData = "";
	SetDlgItemText(hDlg, ID_TBIRTHDATEVALIDATOR, fieldData);
	return isEnteredDataValid;
}

// Clear validation text
void ResetFieldsValidationText(HWND hDlg)
{
	SetDlgItemText(hDlg, ID_TNAMEVALIDATOR, "");
	SetDlgItemText(hDlg, ID_TBIRTHDATEVALIDATOR, "");
	SetDlgItemText(hDlg, ID_TEDUCATIONVALIDATOR, "");
	SetDlgItemText(hDlg, ID_TCOMPANYVALIDATOR, "");
}

// Dialog Box Procedure
BOOL CALLBACK DataEntryDialogProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Local variables declarations
	static HBRUSH hValidationTextBrush;
	IFileInput* pIFileInput = NULL;
	IFileOutput* pIFileOutput = NULL;
	IFileReader* pIFileReader = NULL;
	UserInput in;
	HRESULT hr;
	string fileData;
	string lines[6];
	char fileDataBuffer[4096];
	OLECHAR* szAutomationFunctionName = L"WriteIntoFile";
	OLECHAR* szDotNetFunctionName = L"ReadFromFile";
	VARIANT vArg[2];
	VARIANT vArgVal[1];
	VARIANT vResult;
	IDispatch* pIDispatch = NULL;
	DISPID dispid;
	DISPPARAMS params;
	TCHAR str[400];
	BSTR filePath;
	bool isEnteredDataValid;

	switch (iMsg)
	{
		case WM_INITDIALOG:
			// Set focus in name edit box
			SetFocus(GetDlgItem(hDlg, ID_ETNAME));
			return(TRUE);

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDCONTINUE:
					// Code
					EndDialog(hDlg, 0);
					break;
				case IDCANCEL:
					// Code
					EndDialog(hDlg, 0);
					break;
				case ID_BTNWIN32:
					// Code
					toggleDataEntryDlgEditTextVisibility(hDlg, 0);

					isEnteredDataValid = GetAndValidateUserEnteredData(hDlg, &in);
					if (isEnteredDataValid)
					{
						ofstream wFile(".//Database//database.txt");

						// Write user entered data in file
						wFile << in.name << "\n" << in.birthday << "-" << in.birthmonth << "-" << in.birthyear << "\n" << in.education << "\n" << in.company << "\n";
						MessageBox(hDlg, TEXT("Entered data successfully submitted."), TEXT("Success"), MB_OK);
						wFile.close();
					}
					break;
				case ID_BTNCLASSFACTORY:
					// Code
					ResetFieldsValidationText(hDlg);
					toggleDataEntryDlgEditTextVisibility(hDlg, 1);

					hr = CoCreateInstance(CLSID_FileInput, NULL, CLSCTX_INPROC_SERVER, IID_IFileInput, (void**)&pIFileInput);
					if (FAILED(hr))
					{
						MessageBox(hDlg, TEXT("IFileInput interface can not be obtained"), TEXT("Error"), MB_OK);
					}

					// Read data from file
					pIFileInput->ReadDataFromFile(".//Database//database.txt", fileData);

					if (!fileData.empty())
					{
						splitStr(fileData, lines);

						// Set file data into dialog edit fields
						SetDlgItemText(hDlg, ID_ETNAME, lines[0].c_str());
						SetDlgItemInt(hDlg, ID_ETBIRTHDAY, static_cast<uint32_t>(stoul(lines[1])), true);
						SetDlgItemInt(hDlg, ID_ETBIRTHMONTH, static_cast<uint32_t>(stoul(lines[2])), true);
						SetDlgItemInt(hDlg, ID_ETBIRTHYEAR, static_cast<uint32_t>(stoul(lines[3])), true);
						SetDlgItemText(hDlg, ID_ETEDUCATION, lines[4].c_str());
						SetDlgItemText(hDlg, ID_ETCOMPANY, lines[5].c_str());
					}

					// Safe Release
					if (pIFileInput)
					{
						pIFileInput->Release();
						pIFileInput = NULL;
					}
					break;
				case ID_BTNCONTAINMENT:
					// Code
					toggleDataEntryDlgEditTextVisibility(hDlg, 0);

					isEnteredDataValid = GetAndValidateUserEnteredData(hDlg, &in);
					if (isEnteredDataValid)
					{

						hr = CoCreateInstance(CLSID_FileWriter, NULL, CLSCTX_INPROC_SERVER, IID_IFileOutput, (void**)&pIFileOutput);
						if (FAILED(hr))
						{
							MessageBox(hDlg, TEXT("IFileOutput interface can not be obtained"), TEXT("Error"), MB_OK);
						}

						char userInput[500];
						sprintf(userInput, "%s\n%d-%d-%d\n%s\n%s\n", in.name, in.birthday, in.birthmonth, in.birthyear, in.education, in.company);

						// // Write user entered data in file
						pIFileOutput->WriteIntoFile(".//Database//database.txt", userInput);

						// Safe Release
						if (pIFileOutput)
						{
							pIFileOutput->Release();
							pIFileOutput = NULL;
						}
					}
					break;
				case ID_BTNAGGREGATION:
					// Code
					ResetFieldsValidationText(hDlg);
					toggleDataEntryDlgEditTextVisibility(hDlg, 1);

					hr = CoCreateInstance(CLSID_FileReader, NULL, CLSCTX_INPROC_SERVER, IID_IFileReader, (void**)&pIFileReader);

					if (FAILED(hr))
					{
						MessageBox(hDlg, TEXT("IFileInput interface can not be obtained."), TEXT("File IO Error"), MB_OK);
					}

					// Read data from file
					hr = pIFileReader->ReadFromFile(".//Database//database.txt", fileDataBuffer);
					
					if (FAILED(hr))
					{
						MessageBox(hDlg, TEXT("Failed reading data from file."), TEXT("File IO Error"), MB_OK);
					}

					fileData = fileDataBuffer;

					splitStr(fileData, lines);

					// Set file data into dialog edit fields
					SetDlgItemText(hDlg, ID_ETNAME, lines[0].c_str());
					SetDlgItemInt(hDlg, ID_ETBIRTHDAY, static_cast<uint32_t>(stoul(lines[1])), true);
					SetDlgItemInt(hDlg, ID_ETBIRTHMONTH, static_cast<uint32_t>(stoul(lines[2])), true);
					SetDlgItemInt(hDlg, ID_ETBIRTHYEAR, static_cast<uint32_t>(stoul(lines[3])), true);
					SetDlgItemText(hDlg, ID_ETEDUCATION, lines[4].c_str());
					SetDlgItemText(hDlg, ID_ETCOMPANY, lines[5].c_str());

					// Safe Release
					if (pIFileReader)
					{
						pIFileReader->Release();
						pIFileReader = NULL;
					}
					break;
				case ID_BTNAUTOMATION:
					// Code
					toggleDataEntryDlgEditTextVisibility(hDlg, 0);

					isEnteredDataValid = GetAndValidateUserEnteredData(hDlg, &in);
					if (isEnteredDataValid)
					{
						hr = CoCreateInstance(CLSID_AutomationFileWriter, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&pIDispatch);

						if (FAILED(hr))
						{
							MessageBox(hDlg, TEXT("CoCreateInstance() failed to give IDispatch."), TEXT("Error"), MB_OK);
						}

						char userInput[500];
						sprintf(userInput, "%s\n%d-%d-%d\n%s\n%s\n", in.name, in.birthday, in.birthmonth, in.birthyear, in.education, in.company);
						// Get id of WriteIntoFile() function
						hr = pIDispatch->GetIDsOfNames(IID_NULL, &szAutomationFunctionName, 1, GetUserDefaultLCID(), &dispid);
						if (FAILED(hr))
						{
							MessageBox(hDlg, TEXT("GetIDsOfNames() failed to give IDs of WriteIntoFile()."), TEXT("Error"), MB_OK);
							pIDispatch->Release();
							pIDispatch = NULL;
						}
						// Call WriteIntoFile() function by passing it's ID to invoke() to write user entered data into file
						VariantInit(vArg);
						vArg[0].vt = VT_BSTR;
						filePath = SysAllocString(L".//Database//database.txt");
						vArg[0].bstrVal = filePath;
						vArg[1].vt = VT_BSTR;
						vArg[1].bstrVal = bstr_t(userInput);

						VariantInit(&vResult);
						params.rgvarg = vArg;
						params.cArgs = 2;
						params.rgdispidNamedArgs = NULL;
						params.cNamedArgs = 0;
						hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &params, &vResult, NULL, NULL);
						if (FAILED(hr))
						{
							MessageBox(hDlg, TEXT("Invoke() failed to invoke method WriteIntoFile()."), TEXT("Error"), MB_OK);
							pIDispatch->Release();
							pIDispatch = NULL;
						}
						SysFreeString(filePath);
						VariantClear(&vResult);
						VariantClear(vArg);
						pIDispatch->Release();
						pIDispatch = NULL;
					}
					break;
				case ID_BTNDOTNET:
					// Code
					ResetFieldsValidationText(hDlg);
					toggleDataEntryDlgEditTextVisibility(hDlg, 1);

					hr = CoCreateInstance(CLSID_DotNetServerForInput, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&pIDispatch);

					if (FAILED(hr))
					{
						MessageBox(hDlg, TEXT("CoCreateInstance() failed to give IDispatch."), TEXT("Error"), MB_OK);
					}

					// Get id of ReadFromFile() function
					hr = pIDispatch->GetIDsOfNames(IID_NULL, &szDotNetFunctionName, 1, GetUserDefaultLCID(), &dispid);
					if (FAILED(hr))
					{
						MessageBox(hDlg, TEXT("GetIDsOfNames Failed to give IDs Of SumOfTwoIntegers()."), TEXT("Error"), MB_OK);
						pIDispatch->Release();
						pIDispatch = NULL;
					}

					VariantInit(vArgVal);
					vArgVal[0].vt = VT_BSTR;
					filePath = SysAllocString(L".//Database//database.txt");
					vArgVal[0].bstrVal = filePath;
					VariantInit(&vResult);
					params.rgvarg = vArgVal;
					params.cArgs = 1;
					params.rgdispidNamedArgs = NULL;
					params.cNamedArgs = 0;

					// Call ReadFromFile() function by passing it's ID to invoke()
					hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &params, &vResult, NULL, NULL);
					if (FAILED(hr))
					{
						wsprintf(str, TEXT("Invoke() Failed to invoke ReadFromFile() : %d"), hr);
						MessageBox(hDlg, str, TEXT("Error"), MB_OK);
						pIDispatch->Release();
						pIDispatch = NULL;
					}
					fileData = convertBstrToStr(vResult.bstrVal);
					splitStr(fileData, lines);

					// Set file data into dialog edit fields 
					SetDlgItemText(hDlg, ID_ETNAME, lines[0].c_str());
					SetDlgItemInt(hDlg, ID_ETBIRTHDAY, static_cast<uint32_t>(stoul(lines[1])), true);
					SetDlgItemInt(hDlg, ID_ETBIRTHMONTH, static_cast<uint32_t>(stoul(lines[2])), true);
					SetDlgItemInt(hDlg, ID_ETBIRTHYEAR, static_cast<uint32_t>(stoul(lines[3])), true);
					SetDlgItemText(hDlg, ID_ETEDUCATION, lines[4].c_str());
					SetDlgItemText(hDlg, ID_ETCOMPANY, lines[5].c_str());

					SysFreeString(filePath);
					VariantClear(&vResult);
					VariantClear(vArgVal);
					pIDispatch->Release();
					pIDispatch = NULL;
					break;
			}
			return(TRUE);
		case WM_CTLCOLORDLG:
			// Paint background color of the data entry dialog
			hBrush = CreateSolidBrush(RGB(204, 204, 255));
			return((BOOL)hBrush);
		case WM_CTLCOLORSTATIC:
			// Paint background color of the static text in the dialog
			hBrush = CreateSolidBrush(RGB(204, 204, 255));
			SetBkColor((HDC)wParam, RGB(204, 204, 255));
			// Color dialog's validation texts to red
			if ((HWND)lParam == GetDlgItem(hDlg, ID_TNAMEVALIDATOR) || (HWND)lParam == GetDlgItem(hDlg, ID_TBIRTHDATEVALIDATOR) || (HWND)lParam == GetDlgItem(hDlg, ID_TEDUCATIONVALIDATOR) || (HWND)lParam == GetDlgItem(hDlg, ID_TCOMPANYVALIDATOR))
				SetTextColor((HDC)wParam, RGB(255, 0, 0));
			return((BOOL)hBrush);
		case WM_CTLCOLOREDIT:
			// Paint background color of the edit text fields in dialog
			hBrush = CreateSolidBrush(RGB(245, 255, 250));
			SetBkColor((HDC)wParam, RGB(245, 255, 250));
			return((BOOL)hBrush);
	}
	return(FALSE);
}
// End of dialog procedure
