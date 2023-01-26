#include<Windows.h>
#include<iostream>
#include<string>
#include "ContainmentInnerComponentForFileOutput.h"

using namespace std;

// Class declarations
class CFileOutput : public IFileOutput {
private:
	long m_cRef;
public:
	// Constructor
	CFileOutput();

	// Destructor
	~CFileOutput();

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	// IFileOutput specific method declarations
	HRESULT __stdcall WriteIntoFile(char[], char[]);
};

class CFileOutputClassFactory : public IClassFactory {
private:
	long m_cRef;
public:
	// Constructor
	CFileOutputClassFactory();

	// Destructor
	~CFileOutputClassFactory();

	// IUnknown specific methods declaration
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	// IClassFactory specific methods declaration
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// Global variable declarations
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID reserved)
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


// Constructor
CFileOutput::CFileOutput(void) 
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

// Destructor
CFileOutput::~CFileOutput(void) 
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

// IUnknown methods implementation
HRESULT CFileOutput::QueryInterface(REFIID riid, void** ppv)
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

ULONG CFileOutput::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CFileOutput::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

// IFileOutput methods implementation
HRESULT CFileOutput::WriteIntoFile(char path[], char data[])
{
	// Code
	HANDLE hWriteFile;	
	DWORD dwBytesToWrite = (DWORD)strlen(data);
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;
	TCHAR str[255];

	// Open the existing file, or if the file does not exist, create a new file.
	hWriteFile = CreateFile(path, GENERIC_WRITE, 0, NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hWriteFile == INVALID_HANDLE_VALUE)
	{
		wsprintf(str, TEXT("Could not open file database.txt 0x%08x"), GetLastError());
		MessageBox(NULL, str, TEXT("File IO Error"), MB_OK);
		return(S_FALSE);
	}

	bErrorFlag = WriteFile(hWriteFile, data, dwBytesToWrite, &dwBytesWritten, NULL);

	if (bErrorFlag == FALSE)
	{
		MessageBox(NULL, TEXT("Unable to write to file database.txt"), TEXT("File IO Error"), MB_OK);
		return(S_FALSE);
	}
	else
	{
		if (dwBytesWritten != dwBytesToWrite)
		{
			MessageBox(NULL, TEXT("Unable to write all the data into the database.txt"), TEXT("File IO Error"), MB_OK);
		}
		else
		{
			MessageBox(NULL, TEXT("Entered data successfully submitted."), TEXT("Success"), MB_OK);
		}
	}
	CloseHandle(hWriteFile);
	return(S_OK);
}

// CFileOutputClassFactory implementation

// Constructor
CFileOutputClassFactory::CFileOutputClassFactory() 
{
	m_cRef = 1;
}

CFileOutputClassFactory::~CFileOutputClassFactory() 
{

}

HRESULT CFileOutputClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CFileOutputClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CFileOutputClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

// IClassFactory's methods
HRESULT CFileOutputClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	// Variable declarations
	CFileOutput* pCFileOutput = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCFileOutput = new CFileOutput;

	if (pCFileOutput == NULL)
		return(E_OUTOFMEMORY);

	hr = pCFileOutput->QueryInterface(riid, ppv);
	return(hr);
}

HRESULT CFileOutputClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

// Implementations of Exported functions from this dll
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CFileOutputClassFactory* pCFileOutputClassFactory;
	HRESULT hr;

	if (rclsid != CLSID_FileOutput)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCFileOutputClassFactory = new CFileOutputClassFactory;

	if (pCFileOutputClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCFileOutputClassFactory->QueryInterface(riid, ppv);

	// Anticipate possible failure of QueryInterface()
	pCFileOutputClassFactory->Release();
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return(S_OK);
	else
		return(S_FALSE);
}
