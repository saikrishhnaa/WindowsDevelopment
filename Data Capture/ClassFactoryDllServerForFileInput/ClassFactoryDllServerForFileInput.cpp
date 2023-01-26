#include<stdio.h>
#include<Windows.h>
#include<fstream>
#include<string>
#include "ClassFactoryDllServerForFileInput.h"

using namespace std;

// Global variables
long glNumberOfActiveComponents;
long glNumberOfServerLocks;

// CoClass
class CFileInput : public IFileInput 
{
private:
	long m_cRef;
public:
	// Constructor
	CFileInput(void);
	
	// Destructor
	~CFileInput(void);

	// IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);

	ULONG __stdcall AddRef(void);

	ULONG __stdcall Release(void);

	// IFileInput method
	HRESULT __stdcall ReadDataFromFile(string, string &);
};

// ClassFactory class
class CFileInputClassFactory : public IClassFactory
{
private: 
	long m_cRef;
public:
	// Constructor
	CFileInputClassFactory(void);

	// Destructor
	~CFileInputClassFactory(void);

	// IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);

	ULONG __stdcall AddRef(void);

	ULONG __stdcall Release(void);

	// IClassFactory methods
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);

	HRESULT __stdcall LockServer(BOOL);
};

// DllMain
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	// Code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

// CFileInput implementation

// Constructor
CFileInput::CFileInput(void)
{
	// Code
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

// Destructor
CFileInput::~CFileInput(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

// IUnknown methods implementation
HRESULT CFileInput::QueryInterface(REFIID riid, void** ppv)
{
	// Code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IFileInput*>(this);
	}
	else if (riid == IID_IFileInput)
	{
		*ppv = static_cast<IFileInput*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CFileInput::AddRef(void)
{
	// Code
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CFileInput::Release(void)
{
	// Code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return 0;
	}
	return m_cRef;
}

HRESULT CFileInput::ReadDataFromFile(string filePath, string& fileData)
{
	// Code
	ifstream rFile(filePath);
	if (rFile.is_open())
	{
		string singleLineData;
		while (getline(rFile, singleLineData))
		{
			fileData += singleLineData + "\n";
		}
	} 
	else
	{
		MessageBox(NULL, TEXT("Unable to open file for reading..."), TEXT("IO Error"), MB_OK);
	}
	return S_OK;
}

// CFileInputClassFactory implementation

// Constructor
CFileInputClassFactory::CFileInputClassFactory(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CFileInputClassFactory::~CFileInputClassFactory(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

// IUnknown methods implementation
HRESULT CFileInputClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	// Code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if(riid == IID_IClassFactory)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CFileInputClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CFileInputClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete this;
		return 0;
	}
	return m_cRef;
}

// IClassFactory methods implementation
HRESULT CFileInputClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// Variable declarations
	CFileInput* pCFileInput = NULL;
	HRESULT hr;
	// Code
	if (pUnkOuter != NULL)
	{
		return CLASS_E_NOAGGREGATION;
	}
	pCFileInput = new CFileInput;
	if (pCFileInput == NULL)
	{
		return E_OUTOFMEMORY;
	}
	hr = pCFileInput->QueryInterface(riid, ppv);
	pCFileInput->Release();
	return hr;
}

HRESULT CFileInputClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
	{
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else
	{
		InterlockedDecrement(&glNumberOfServerLocks);
	}
	return S_OK;
}

// Exportable COM DLL methods
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// Variable declarations
	CFileInputClassFactory* pCFileInputClassFactory = NULL;
	HRESULT hr;

	// Code
	if (rclsid != CLSID_FileInput)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}
	pCFileInputClassFactory = new CFileInputClassFactory;
	if (pCFileInputClassFactory == NULL)
	{
		return E_OUTOFMEMORY;
	}
	hr = pCFileInputClassFactory->QueryInterface(riid, ppv);
	pCFileInputClassFactory->Release();
	return hr;
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	// Code
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
	{
		return S_OK;
	}
	else
	{
		return S_FALSE;
	}
}
