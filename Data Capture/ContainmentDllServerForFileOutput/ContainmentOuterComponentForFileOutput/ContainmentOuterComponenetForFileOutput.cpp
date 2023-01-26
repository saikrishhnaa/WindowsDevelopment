#include<Windows.h>
#include<string>
#include "ContainmentInnerComponentForFileOutput.h"
#include "ContainmentOuterComponenetForFileOutput.h"

using namespace std;

// CoClass declaration
class CFileWriter: public IFileOutput
{
private:
	long m_cRef;
	IFileOutput* m_pIFileOutput;
public:
	// Constructor
	CFileWriter(void);
	// Destructor
	~CFileWriter(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IFileOutput specific method declaration (inherited)
	HRESULT __stdcall WriteIntoFile(char[], char[]);

	// Custom method for inner component creation
	HRESULT __stdcall InitializeInnerComponent(void);
};

// ClassFactory class declaration
class CFileWriterClassFactory: public IClassFactory
{
private:
	long m_cRef;
public:
	// Constructor
	CFileWriterClassFactory(void);
	// Destructor
	~CFileWriterClassFactory(void);

	// IUnknown specific methods declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory specific methods declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// Global variables declarations
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

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

// CoClass Implementation

// Constructor
CFileWriter::CFileWriter(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

// Destructor
CFileWriter::~CFileWriter(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

// Implementation of IUnknown's methods
HRESULT CFileWriter::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IFileOutput*>(this);
	else if (riid == IID_IFileOutput)
		*ppv = static_cast<IFileOutput*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CFileWriter::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CFileWriter::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return 0;
	}
	return(m_cRef);
}

// Implementation of IFileOutput's method
HRESULT CFileWriter::WriteIntoFile(char path[], char data[])
{
	m_pIFileOutput->WriteIntoFile(path, data);
	return(S_OK);
}

// Implementation to initialize inner component
HRESULT CFileWriter::InitializeInnerComponent(void)
{
	HRESULT hr;

	hr = CoCreateInstance(CLSID_FileOutput, NULL, CLSCTX_INPROC_SERVER, IID_IFileOutput, (void**)&m_pIFileOutput);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IFileOutput Interface Can Not Be Obtained From Inner Component."), TEXT("Error"), MB_OK);
		return(E_FAIL);
	}
	return(S_OK);
}

// ClassFactory class implementation

// Constructor
CFileWriterClassFactory::CFileWriterClassFactory(void)
{
	// Hardcoded initialization to anticipate possible failure of QueryInterface
	m_cRef = 1;
}

CFileWriterClassFactory::~CFileWriterClassFactory(void)
{
	// No code
}

// Implementation of IUnknown's methods
HRESULT CFileWriterClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CFileWriterClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CFileWriterClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

// Implementation of IClassFactory's methods
HRESULT CFileWriterClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	CFileWriter* pCFileWriter;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCFileWriter = new CFileWriter;

	if (pCFileWriter == NULL)
		return(E_OUTOFMEMORY);

	// Initialize the inner component
	hr = pCFileWriter->InitializeInnerComponent();

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed To Initialize Inner Component"), TEXT("Error"), MB_OK);
		pCFileWriter->Release();
		return(hr);
	}

	hr = pCFileWriter->QueryInterface(riid, ppv);
	pCFileWriter->Release();
	return(hr);
}

HRESULT CFileWriterClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	
	return(S_OK);
}

// Dll exported functions
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// Variable declarations
	CFileWriterClassFactory* pCFileWriterClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_FileWriter)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCFileWriterClassFactory = new CFileWriterClassFactory;

	if (pCFileWriterClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCFileWriterClassFactory->QueryInterface(riid, ppv);
	pCFileWriterClassFactory->Release(); // Anticipate possible failure of QueryInterface
	
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return(S_OK);
	else
		return(S_FALSE);
}
