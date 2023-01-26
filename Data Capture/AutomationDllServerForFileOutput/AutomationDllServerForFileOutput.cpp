#define UNICODE

// Header files
#include<Windows.h>
#include<stdio.h>
#include<string>
#include "AutomationDllServerForFileOutput.h"
#include <msclr\marshal.h>

using namespace msclr::interop;

using namespace System;
using namespace System::IO;

using namespace std;

// CoClass class declaration
class CAutomationFileWriter : public IAutomationFileWriter
{
private:
	long m_cRef;
	ITypeInfo* m_pITypeInfo = NULL;
public:
	// Constructor method declaration
	CAutomationFileWriter(void);

	// Destructor method declaration
	~CAutomationFileWriter(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IDispatch specific method declarations (inherited)
	HRESULT __stdcall GetTypeInfoCount(UINT*);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);

	// IAutomationFileWriter specific method declaration (inherited)
	HRESULT __stdcall WriteIntoFile(char[], char[]);

	// Custom methods
	HRESULT InitInstance(void);
};

// Class factory declaration
class CAutomationFileWriterClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	// Constructor method declaration
	CAutomationFileWriterClassFactory();

	// Destructor method declaration
	~CAutomationFileWriterClassFactory();

	// IUnknown specific method declaration (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory specific method declaration (inherited)
	HRESULT __stdcall CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv);
	HRESULT __stdcall LockServer(BOOL);
};

// Global variable declarations
long glNumberOfActiveComponents;
long glNumberOfServerLocks;

// GUID of Automation Server Library - {6EB2D557-8EEF-4cb9-A8C5-D5A48670A6C0}
const GUID LIBID_AutomationServer = { 0x6eb2d557, 0x8eef, 0x4cb9, 0xa8, 0xc5, 0xd5, 0xa4, 0x86, 0x70, 0xa6, 0xc0 };

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

// Implementation
// Constructor
CAutomationFileWriter::CAutomationFileWriter(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
	m_pITypeInfo = NULL;
}

CAutomationFileWriter::~CAutomationFileWriter(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
	if (m_pITypeInfo)
	{
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
	}
}

// IUnknown methods implementation
HRESULT CAutomationFileWriter::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IAutomationFileWriter*>(this);
	else if (riid == IID_IDispatch)
		*ppv = static_cast<IAutomationFileWriter*>(this);
	else if (riid == IID_IAutomationFileWriter)
		*ppv = static_cast<IAutomationFileWriter*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CAutomationFileWriter::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CAutomationFileWriter::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

// IAutomationFileWriter methods implementation
HRESULT CAutomationFileWriter::WriteIntoFile(char* data, char* path)
{
	TCHAR filePath[50];
	TCHAR fileContent[500];
	wsprintf(filePath, TEXT("%s"), path);
	wsprintf(fileContent, TEXT("%s"), data);
	StreamWriter^ sw = gcnew StreamWriter(gcnew String(filePath));
	String^ clrString = marshal_as<String^>(fileContent);
	sw->Write(clrString);
	MessageBox(NULL, TEXT("Entered data successfully submitted."), TEXT("Success"), MB_OK);
	sw->Close();
	return(S_OK);
}

HRESULT CAutomationFileWriter::InitInstance(void)
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
			1, 0,
			0x00,
			&pITypeLib);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			return(hr);
		}

		hr = pITypeLib->GetTypeInfoOfGuid(IID_IAutomationFileWriter, &m_pITypeInfo);

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

// CAutomationFileWriterClassFactory's Implementation
// Constructor
CAutomationFileWriterClassFactory::CAutomationFileWriterClassFactory(void)
{
	m_cRef = 1; // Hardcoded initialization to anticipate possible failure in QueryInterface
}

// Destructor
CAutomationFileWriterClassFactory::~CAutomationFileWriterClassFactory(void)
{
	// No code
}

HRESULT CAutomationFileWriterClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CAutomationFileWriterClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CAutomationFileWriterClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CAutomationFileWriterClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// Variable declarations
	CAutomationFileWriter* pCAutomationFileWriter = NULL;
	HRESULT hr;

	// Code
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCAutomationFileWriter = new CAutomationFileWriter;

	if (pCAutomationFileWriter == NULL)
		return(E_OUTOFMEMORY);

	// Call automation related init method
	pCAutomationFileWriter->InitInstance();

	hr = pCAutomationFileWriter->QueryInterface(riid, ppv);

	pCAutomationFileWriter->Release(); // To anticipate possible failure in QueryInterface

	return(hr);
}

HRESULT CAutomationFileWriterClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

// Implementation of IDispatch's methods
HRESULT CAutomationFileWriter::GetTypeInfoCount(UINT* pCountTypeInfo)
{
	*pCountTypeInfo = 1;
	return(S_OK);
}

HRESULT CAutomationFileWriter::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo)
{
	*ppITypeInfo = NULL;
	if (iTypeInfo != 0)
		return(DISP_E_BADINDEX);

	m_pITypeInfo->AddRef();
	*ppITypeInfo = m_pITypeInfo;
	return(S_OK);
}

HRESULT CAutomationFileWriter::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId)
{
	return(DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispId));
}

HRESULT CAutomationFileWriter::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
	// Variable declarations
	HRESULT hr;

	// Code
	hr = DispInvoke(this, m_pITypeInfo, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
	return(hr);
}

// Exportable COM DLL methods
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// Variable declarations
	CAutomationFileWriterClassFactory* pCAutomationFileWriterClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_AutomationFileWriter)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCAutomationFileWriterClassFactory = new CAutomationFileWriterClassFactory;
	if (pCAutomationFileWriterClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCAutomationFileWriterClassFactory->QueryInterface(riid, ppv);
	pCAutomationFileWriterClassFactory->Release();
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow()
{
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return(S_OK);
	else
		return(S_FALSE);
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
