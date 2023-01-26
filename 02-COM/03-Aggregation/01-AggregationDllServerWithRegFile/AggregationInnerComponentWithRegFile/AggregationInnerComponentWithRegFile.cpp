#include<windows.h>
#include "AggregationInnerComponentWithRegFile.h"

// interface declaration ( for internal use only. i.e. not to be included in .h file )
interface INoAggregationIUnknown // new
{
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**) = 0;
	virtual ULONG __stdcall AddRef_NoAggregation() = 0;
	virtual ULONG __stdcall Release_NoAggregation() = 0;
};

// class declarations
class CMultiplicationDivision :public INoAggregationIUnknown, IMultiplication, IDivision
{
private:
	long m_cRef;
	IUnknown* m_pIUnknownOuter;
public:
	CMultiplicationDivision(IUnknown *); // constructor method declarations

	~CMultiplicationDivision(void); // destructor method declarations

	// Aggregation Supported IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// Aggregation Nonsupported IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**); // new
	ULONG __stdcall AddRef_NoAggregation(void); // new
	ULONG __stdcall Release_NoAggregation(void); // new

	// IMultiplication specific method declarations (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	// IDivision specific method declarations (inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CMultiplicationDivisionClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CMultiplicationDivisionClassFactory(void);

	// destructor method declarations
	~CMultiplicationDivisionClassFactory(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG  __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// global variable declarations
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	// code
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
	}
	return(TRUE);
}

// Implementation Of CMultiplicationDivision's Constructor Method
CMultiplicationDivision::CMultiplicationDivision(IUnknown *pIUnknownOuter)
{
	m_cRef = 1; // Hardcoded initialization to anticipate possible failure of QueryInterface()

	InterlockedIncrement(&glNumberOfActiveComponents); // Increment global counter

	if (pIUnknownOuter != NULL)
		m_pIUnknownOuter = pIUnknownOuter;
	else
		m_pIUnknownOuter = reinterpret_cast<IUnknown*>(static_cast<INoAggregationIUnknown*>(this));
}

// Implementation Of CMultiplicationDivision's Destructor Method
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); // Decrement global counter
}

// Implementation Of CMultiplicationDivision's Aggregation Supporting IUnknown's Methods
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
{
	return(m_pIUnknownOuter->QueryInterface(riid, ppv));
}

ULONG CMultiplicationDivision::AddRef(void)
{
	return(m_pIUnknownOuter->AddRef());
}

ULONG CMultiplicationDivision::Release(void)
{
	return(m_pIUnknownOuter->Release());
}

HRESULT CMultiplicationDivision::QueryInterface_NoAggregation(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<INoAggregationIUnknown*>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMultiplicationDivision::AddRef_NoAggregation(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivision::Release_NoAggregation(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);
		return 0;
	}

	return(m_cRef);
}

// Implementation Of IMultiplication's Methods
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
	*pMultiplication = num1 * num2;
	return(S_OK);
}

// Implementation Of IDivision's Methods
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int* pDivision)
{
	*pDivision = num1 / num2;
	return(S_OK);
}

// Implementation Of CMultiplicationDivisionClassFactory's Constructor Method
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	m_cRef = 1;
}

CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
	// no code
}

// Implementation Of CMultiplicationDivisionClassFactory's IClassFactory's IUnknown's Methods
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if (riid == IID_IClassFactory)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

// Implementation Of CMultiplicationDivisionClassFactory's ClassFactory's Methods
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// Variable declarations
	CMultiplicationDivision* pCMultiplicationDivision = NULL;
	HRESULT hr;

	if ((pUnkOuter != NULL) && (riid != IID_IUnknown))
		return(CLASS_E_NOAGGREGATION);

	// Create the instance of component i.e. of CMultiplicationDivision class
	pCMultiplicationDivision = new CMultiplicationDivision(pUnkOuter);

	if (pCMultiplicationDivision == NULL)
		return(E_OUTOFMEMORY);

	// Get the requested interface
	hr = pCMultiplicationDivision->QueryInterface_NoAggregation(riid, ppv);
	
	// Anticipate possible failure of QueryInterface
	pCMultiplicationDivision->Release_NoAggregation();

	return(hr);
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);

	return(S_OK);
}

// Implementation Of Exported Functions From This Dll
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// Variable Declarations
	CMultiplicationDivisionClassFactory* pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MultiplicationDivision)
		return(CLASS_E_CLASSNOTAVAILABLE);

	// Create class factory
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;

	if (pCMultiplicationDivisionClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);

	// Anticipate possible failure of QueryInterface()
	pCMultiplicationDivisionClassFactory->Release();

	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(TRUE);
	else
		return(FALSE);
}
