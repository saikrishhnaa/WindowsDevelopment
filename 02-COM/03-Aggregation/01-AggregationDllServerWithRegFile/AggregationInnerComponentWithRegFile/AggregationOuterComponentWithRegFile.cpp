#include<windows.h>
#include "AggregationInnerComponentWithRegFile.h"
#include "AggregationOuterComponentWithRegFile.h"

// Class declarations
class CSumSubtract :public ISum, ISubtract
{
private:
	long m_cRef;
	IUnknown* m_pIUnknownInner;
	IMultiplication* m_pIMultiplication;
	IDivision* m_pIDivision;
public:
	// Constructor method declarations
	CSumSubtract(void);
	// Destructor method declarations
	~CSumSubtract(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// ISum specific method declarations
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	// ISubtract specific method declarations
	HRESULT __stdcall SubtractionsOfTwoIntegers(int, int, int*);

	// Custom method for inner component initialization
	HRESULT __stdcall InitializeInnerComponent(void);
}

class CSumSubtractClassFactory :public IClassFactory
{
	long m_cRef;
public:
	// Constructor method declarations
	CSumSubtractClassFactory(void);

	// Destructor method declarations
	~CSumSubtractClassFactory(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// global variable declarations
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

CSumSubtract::CSumSubtract(void)
{
	// Initialization of private data members
	m_pIUnknownInner = NULL;
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1; // Hardcoded initialization to anticipate possible failure of QueryInterface()

	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract(void)
{
	if (m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}

	if (m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}

	if (m_pIUnknownInner)
	{
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
	}
}

HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if(riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return(S_OK);
}

ULONG CSumSubtract::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtract::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}

	return(m_cRef);
}

// Implementation Of ISum's Methods
HRESULT __stdcall SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	*pSum = num1 + num2;
	return(S_OK);
}

// Implemenation Of ISubtract's Methods
HRESULT __stdcall SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	*pSubtract = num1 - num2;
	return(S_OK);
}

HRESULT CSumSubtract::InitializeInnerComponent(void)
{
	// Variable declarations
	HRESULT hr;

	hr = CoCreateInstace(CLSID_MultiplicationDivision, reinterpret_cast<IUnknown*>(this), CLSCTX_INPROC_SERVER, IID_IUnknown, m_pIUnknownInner);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IUnknown Interface Can Not Be Obtained From Inner Component."), TEXT("Error"), MB_OK);

		return(E_FAIL);
	}

	hr = m_pIUnknownInner->QueryInterface(IID_IMultiplication, (void**)&m_pIMultiplication);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultiplication Interface Can Not Be Obtained From Inner Component."), TEXT("Error"), MB_OK);

		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;

		return(E_FAIL);
	}

	hr = m_pIUnknownInner->QueryInterface(IID_IDivision, &m_pIDivision);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision Interface Can Not Be Obtained From Inner Component,"), TEXT("Error"), MB_OK);

		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;

		return(E_FAIL);
	}

	return(S_OK);
}

