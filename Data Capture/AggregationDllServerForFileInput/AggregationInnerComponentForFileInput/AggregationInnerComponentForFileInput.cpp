#include<Windows.h>
#include "AggregationInnerComponentForFileInput.h"

// Interface declaration ( For internal use only. i.e. not to be included in the .h file )
interface INoAggregationIUnknown
{
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**) = 0;
	virtual ULONG __stdcall AddRef_NoAggregation(void) = 0;
	virtual ULONG __stdcall Release_NoAggregation(void) = 0;
};

// Class declarations
class CFileInputInner : public INoAggregationIUnknown, IFileReader
{
private:
	long m_cRef;
	IUnknown* m_pIUnknownOuter;
public:
	// Constructor method declaration
	CFileInputInner(IUnknown*); 

	// Destructor method declaration
	~CFileInputInner(void);

	// Aggregation supported IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// Aggregation Non-supported IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**);
	ULONG __stdcall AddRef_NoAggregation(void);
	ULONG __stdcall Release_NoAggregation(void);

	// IFileInput specific method declarations (inherited)
	HRESULT __stdcall ReadFromFile(char[], char[]);
};

class CFileInputInnerClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	// Constructor method declaration
	CFileInputInnerClassFactory(void);

	// Destructor method declaration
	~CFileInputInnerClassFactory(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// Global variable declarations
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	// Code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

// Implementation of CFileInputInner's Constructor method
CFileInputInner::CFileInputInner(IUnknown* pIUnknownOuter)
{
	m_cRef = 1; // Harcoded initialization to anticipate possible failure of QueryInterface()

	InterlockedIncrement(&glNumberOfActiveComponents);

	if (pIUnknownOuter != NULL)
		m_pIUnknownOuter = pIUnknownOuter;
	else
		m_pIUnknownOuter = reinterpret_cast<IUnknown*>(static_cast<INoAggregationIUnknown*>(this));
}

// Implementation of CFileInputInner's Destructor method
CFileInputInner::~CFileInputInner(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

// Implementation of IUnknown's methods
HRESULT CFileInputInner::QueryInterface(REFIID riid, void** ppv)
{
	return(m_pIUnknownOuter->QueryInterface(riid, ppv));
}

ULONG CFileInputInner::AddRef(void)
{
	return(m_pIUnknownOuter->AddRef());
}

ULONG CFileInputInner::Release(void)
{
	return(m_pIUnknownOuter->Release());
}

// Implementation of INoAggregationIUnknown's methods
HRESULT CFileInputInner::QueryInterface_NoAggregation(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<INoAggregationIUnknown*>(this);
	else if (riid == IID_IFileReader)
		*ppv = static_cast<IFileReader*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CFileInputInner::AddRef_NoAggregation(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CFileInputInner::Release_NoAggregation(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

// Implementation of IFileInput's methods
HRESULT CFileInputInner::ReadFromFile(char path[], char data[])
{
	HANDLE hFile;
	DWORD dwBytesRead;
	hFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, TEXT("Unable to open file for reading."), TEXT("File IO Error"), MB_OK);
		return(S_FALSE);
	}

	if (FALSE == ReadFile(hFile, data, 4096, &dwBytesRead, NULL))
	{
		MessageBox(NULL, TEXT("Unable to read from file."), TEXT("File IO Error"), MB_OK);
		return(S_FALSE);
	}

	CloseHandle(hFile);
	return(S_OK);
}

// Implementation of CFileInputInnerClassFactory's Constructor method
CFileInputInnerClassFactory::CFileInputInnerClassFactory(void)
{
	m_cRef = 1;
}

// Implementation of CFileInputInnerClassFactory's Destructor method
CFileInputInnerClassFactory::~CFileInputInnerClassFactory(void)
{
	// No code
}

// Implementation of CFileInputInnerClassFactory's IClassFactory's IUnknown's methods
HRESULT CFileInputInnerClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CFileInputInnerClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CFileInputInnerClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

// Implementation of CFileInputInnerClassFactory's ClassFactory's methods
HRESULT CFileInputInnerClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// Variable declarations
	CFileInputInner* pCFileInputInner = NULL;
	HRESULT hr;

	if ((pUnkOuter != NULL) && (riid != IID_IUnknown))
		return(CLASS_E_NOAGGREGATION);

	pCFileInputInner = new CFileInputInner(pUnkOuter);

	if (pCFileInputInner == NULL)
		return(E_OUTOFMEMORY);

	hr = pCFileInputInner->QueryInterface_NoAggregation(riid, ppv);

	//Anticipate possible failure of QueryInterface
	pCFileInputInner->Release_NoAggregation();

	return(hr);
}

HRESULT CFileInputInnerClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);

	return(S_OK);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// Variable declarations
	CFileInputInnerClassFactory* pCFileInputInnerClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_FileInputInner)
		return(CLASS_E_CLASSNOTAVAILABLE);
	
	// Create class factory
	pCFileInputInnerClassFactory = new CFileInputInnerClassFactory;

	if (pCFileInputInnerClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCFileInputInnerClassFactory->QueryInterface(riid, ppv);

	// Anticipate possible failure of QueryInterface
	pCFileInputInnerClassFactory->Release();

	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(TRUE);
	else
		return(FALSE);
}
