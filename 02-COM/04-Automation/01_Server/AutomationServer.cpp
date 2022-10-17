#define UNICODE

// Header files
#include<windows.h>
#include<stdio.h>
#include "AutomationServer.h"

// CoClass class declaration
class CMyMath :public IMyMath
{
private:
	long m_cRef;
	ITypeInfo* m_pITypeInfo = NULL;
public:
	// Constructor method declarations
	CMyMath(void);

	// Destructor metod declarations
	~CMyMath(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IDispatch specific method declarations (inherited)
	HRESULT __stdcall GetTypeInfoCount(UINT*);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);

	// ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	// ISubtract specific method declarations (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	// Custom methods
	HRESULT InitInstance(void);
};

// Class factory declaration
class CMyMathClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	// Constructor method declarations
	CMyMathClassFactory(void);

	// Destructory method declarations
	~CMyMathClassFactory(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// Global variable declarations
long glNumberOfActiveComponents;
long glNumberOfServerLocks;

// GUID of Automation Server Library - {CEE4A9B4-AD42-403a-AF85-C142E3909843}
const GUID LIBID_AutomationServer = { 0xcee4a9b4, 0xad42, 0x403a, 0xaf, 0x85, 0xc1, 0x42, 0xe3, 0x90, 0x98, 0x43 };

// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	return(TRUE);
}

//Constructor
CMyMath::CMyMath(void) {
	//Code
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
	m_pITypeInfo = NULL;
}

//Destructor
CMyMath :: ~CMyMath(void) {
	InterlockedDecrement(&glNumberOfActiveComponents);
	if (m_pITypeInfo)
	{
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
	}
}

//IUnknown methods implementation
HRESULT CMyMath::QueryInterface(REFIID riid, void** ppv) {
	//Code
	if (riid == IID_IUnknown) 
		*ppv = static_cast<IMyMath*>(this); 
	else if (riid == IID_IDispatch)
		*ppv = static_cast<IMyMath*>(this);
	else if (riid == IID_IMyMath)
		*ppv = static_cast<IMyMath*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*> (*ppv)->AddRef();
	return (S_OK);
} 

ULONG CMyMath::AddRef(void) {
	//Code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMyMath::Release(void) {
	//Code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}
	else
		return (m_cRef);
}

//ISumImplementation
HRESULT CMyMath::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	//Code
	*pSum = num1 + num2;
	return (S_OK);
}

HRESULT CMyMath::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	//Code
	*pSubtract = num1 - num2;
	return (S_OK);
}

HRESULT CMyMath::InitInstance(void)
{
	// Function declarations
	void ComErrorDescriptionString(HWND, HRESULT);

	// Variable declarations
	HRESULT hr;
	ITypeLib* pITypeLib = NULL;

	// Code
	if (m_pITypeInfo == NULL)
	{
		hr = LoadRegTypeLib(LIBID_AutomationServer,
			1, 0, // major/minor version numbers
			0x00, // LANG_NEUTRAL
			&pITypeLib);
		
		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			return(hr);
		}

		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			return(hr);
		}
		
		pITypeLib->Release();
	}
	return(S_OK);
}

//CMyMathClassFactory's Implementation

//Constructor
CMyMathClassFactory::CMyMathClassFactory(void)
{
	m_cRef = 1;
}

//Destructor
CMyMathClassFactory::~CMyMathClassFactory(void)
{

}

//IUnknown methods implementation
HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	//Code
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*> (*ppv)->AddRef();
	return (S_OK);
}

ULONG CMyMathClassFactory::AddRef(void) {
	//Code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMyMathClassFactory::Release(void) {
	//Code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}
	else
		return (m_cRef);
}

//IClassFactory method implementation
HRESULT CMyMathClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//Variable declaration
	CMyMath* pCMyMath = NULL;
	HRESULT hr;

	//Code
	if (pUnkOuter != NULL)
	{
		return (CLASS_E_NOAGGREGATION);
	}

	pCMyMath = new CMyMath;

	if (pCMyMath == NULL)
	{
		return (E_OUTOFMEMORY);
	}

	// Call automation related init method
	pCMyMath->InitInstance();

	hr = pCMyMath->QueryInterface(riid, ppv);

	pCMyMath->Release();

	return (hr);
}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock)
{
	//Code
	if (fLock)
	{
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else
	{
		InterlockedDecrement(&glNumberOfServerLocks);
	}

	return (S_OK);
}

// Implementation of IDispatch's methods
HRESULT CMyMath::GetTypeInfoCount(UINT* pCountTypeInfo)
{
	// As we have type library it is 1, else 0
	*pCountTypeInfo = 1;

	return(S_OK);
}

HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo)
{
	*ppITypeInfo = NULL;

	if (iTypeInfo != 0)
		return(DISP_E_BADINDEX);

	m_pITypeInfo->AddRef();

	*ppITypeInfo = m_pITypeInfo;

	return(S_OK);
}

HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId)
{
	return(DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispId));
}

HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
	// Variable declarations
	HRESULT hr;

	hr = DispInvoke(this,
		m_pITypeInfo,
		dispIdMember,
		wFlags,
		pDispParams,
		pVarResult,
		pExcepInfo,
		puArgErr);

	return(hr);
}

//Exportable COM DLL methods
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	//Variable Declarations
	CMyMathClassFactory* pCMyMathClassFactory = NULL;
	HRESULT hr;

	//Code
	if (rclsid != CLSID_MyMath)
		return (CLASS_E_CLASSNOTAVAILABLE);

	pCMyMathClassFactory = new CMyMathClassFactory;
	if (pCMyMathClassFactory == NULL)
	{
		return (E_OUTOFMEMORY);
	}
	hr = pCMyMathClassFactory->QueryInterface(riid, ppv);

	pCMyMathClassFactory->Release();
	return (hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow() {
	//Code
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return (S_OK);
	else
		return (S_FALSE);
}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	// Variable declarations
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0)
	{
		swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
		swprintf_s(str, TEXT("[Could not find a description for error # %#x.]\n"), hr);

	MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}
