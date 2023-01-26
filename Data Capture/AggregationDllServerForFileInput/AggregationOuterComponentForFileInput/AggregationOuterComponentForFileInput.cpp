#include<Windows.h>
#include "AggregationInnerComponentForFileInput.h"
#include "AggregationOuterComponentForFileInput.h"

// Class declaration
class CFileInputOuter: public IUnknown
{
private:
	long m_cRef;
	IUnknown* m_pIUnknownInner;
public:
	// Constructor method declaration
	CFileInputOuter(void);
	// Destructor method declaration
	~CFileInputOuter(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// Custom method for inner component initialization
	HRESULT __stdcall InitializeInnerComponent(void);
};

// ClassFactoryClass declaration
class CFileInputOuterClassFactory : public  IClassFactory
{
private:
	long m_cRef;
public:
	// Constructor method declaration
	CFileInputOuterClassFactory(void);
	// Destructor method declaration
	~CFileInputOuterClassFactory(void);

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

// Constructor implementation
CFileInputOuter::CFileInputOuter(void)
{
	m_pIUnknownInner = NULL;
	m_cRef = 1; // Hardcoded initialization to anticipate possibe failure of QueryInterface()

	InterlockedIncrement(&glNumberOfActiveComponents);
}

// Destructor implementation
CFileInputOuter::~CFileInputOuter(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);

	if (m_pIUnknownInner)
	{
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
	}
}

// Implementation of IUnknown's method
HRESULT CFileInputOuter::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IUnknown*>(this);
	else if (riid == IID_IFileReader)
		return(m_pIUnknownInner->QueryInterface(riid, ppv));
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CFileInputOuter::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CFileInputOuter::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

// Implementation of custom method to initialize inner component
HRESULT __stdcall CFileInputOuter::InitializeInnerComponent()
{
	// Variable declarations
	HRESULT hr;

	hr = CoCreateInstance(CLSID_FileInputInner, reinterpret_cast<IUnknown*>(this), CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&m_pIUnknownInner);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IUnknown interface can not be obtained from inner component."), TEXT("Error"), MB_OK);
		return(E_FAIL);
	}

	return(S_OK);
}

// Implmentation of CFileInputOuterClassFactory's constructor method
CFileInputOuterClassFactory::CFileInputOuterClassFactory(void)
{
	m_cRef = 1;
}

// Implmentation of CFileInputOuterClassFactory's destructor method
CFileInputOuterClassFactory::~CFileInputOuterClassFactory(void)
{
	// No code
}

// Implmentation of CFileInputOuterClassFactory's IClassFactory's IUnknown's methods
HRESULT CFileInputOuterClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CFileInputOuterClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CFileInputOuterClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CFileInputOuterClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	CFileInputOuter* pCFileInputOuter = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCFileInputOuter = new CFileInputOuter;

	if (pCFileInputOuter == NULL)
		return(E_OUTOFMEMORY);

	hr = pCFileInputOuter->InitializeInnerComponent();

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed to initialize inner component."), TEXT("Error"), MB_OK);
		pCFileInputOuter->Release();
		return(hr);
	}

	hr = pCFileInputOuter->QueryInterface(riid, ppv);
	
	pCFileInputOuter->Release(); // Anticipate possible failure of QueryInterface()
	return(hr);
}

HRESULT CFileInputOuterClassFactory::LockServer(BOOL fLock)
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
	CFileInputOuterClassFactory* pCFileInputOuterClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_FileReader)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCFileInputOuterClassFactory = new CFileInputOuterClassFactory;

	if (pCFileInputOuterClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCFileInputOuterClassFactory->QueryInterface(riid, ppv);
	pCFileInputOuterClassFactory->Release();

	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow()
{
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return(S_OK);
	else
		return(S_FALSE);
}
