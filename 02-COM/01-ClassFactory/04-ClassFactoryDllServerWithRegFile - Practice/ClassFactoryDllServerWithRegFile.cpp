#include<stdio.h>
#include<Windows.h>
#include "ClassFactoryDllServerWithRegFile.h"

//GLobal variables
long glNumberOfActiveComponents;
long glNumberOfServerLocks;

//CoClass
class CSumSubstract : public ISum, ISubstract{
private:
	long m_cRef;
public:
	//Constructor
	CSumSubstract(void);

	//Destructor
	~CSumSubstract(void);

	//IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);

	ULONG __stdcall AddRef(void);

	ULONG __stdcall Release(void);
	
	//ISum method
	HRESULT __stdcall SumOfTwoIntergers(int, int, int*);

	//ISubstract method
	HRESULT __stdcall SubstractionOfTwoIntegers(int, int, int*);
};

//ClassFactory class
class CSumSubstractClassFactory : public IClassFactory {
private:
	long m_cRef;
public:
	//Constructor
	CSumSubstractClassFactory(void);

	//Destructor
	~CSumSubstractClassFactory(void);

	//IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);

	ULONG __stdcall AddRef(void);

	ULONG __stdcall Release(void);

	//IClassFactory methods
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);

	HRESULT __stdcall LockServer(BOOL);
};

//DllMain
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	//Code
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
		default:
			break;
	}
	return TRUE;
}

//CSumSubstract implementation
//Constructor
CSumSubstract::CSumSubstract(void) {
	//Code
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

//Destructor
CSumSubstract::~CSumSubstract(void) {
	//Code
	InterlockedDecrement(&glNumberOfActiveComponents);
}

//IUnknown methods implementation
HRESULT CSumSubstract::QueryInterface(REFIID riid, void** ppv) {
	//Code
	if (riid == IID_IUnknown) {
		*ppv = static_cast<ISum*>(this); //Templatisze -> making standardize, in this case ISum*
	}
	else if (riid == IID_ISum) {
		*ppv = static_cast<ISum*>(this);
	}
	else if (riid == IID_ISubstract) {
		*ppv = static_cast<ISubstract*>(this);
	}
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CSumSubstract::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CSumSubstract::Release(void) {
	//Code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return 0;
	}
	return m_cRef;
}

//ISum method implementation
HRESULT CSumSubstract::SumOfTwoIntergers(int num1, int num2, int* pSum) {
	*pSum = num1 + num2;
	return S_OK;
}

//ISubstract method implementation
HRESULT CSumSubstract::SubstractionOfTwoIntegers(int num1, int num2, int* pSubstract) {
	//Code
	*pSubstract = num1 - num2;
	return S_OK;
}

//CSumSubstractClassFactory implementation
//Constructor
CSumSubstractClassFactory::CSumSubstractClassFactory(void) {
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubstractClassFactory::~CSumSubstractClassFactory(void) {
	InterlockedDecrement(&glNumberOfActiveComponents);
}

//IUnknown methods implementation
HRESULT CSumSubstractClassFactory::QueryInterface(REFIID riid, void** ppv) {
	//Code
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if (riid == IID_IClassFactory) {
		*ppv = static_cast<IClassFactory*>(this);
	}
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CSumSubstractClassFactory::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CSumSubstractClassFactory::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete this;
		return 0;
	}
	return m_cRef;
}

//IClassFactory method implementation
HRESULT CSumSubstractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv) {
	//Variable declarations
	CSumSubstract* pCSumSubstract = NULL;
	HRESULT hr;
	//Code
	if (pUnkOuter != NULL) {
		return CLASS_E_NOAGGREGATION;
	}
	pCSumSubstract = new CSumSubstract;
	if (pCSumSubstract == NULL) {
		return E_OUTOFMEMORY;
	}
	hr = pCSumSubstract->QueryInterface(riid, ppv);
	pCSumSubstract->Release();
	return hr;
}

HRESULT CSumSubstractClassFactory::LockServer(BOOL fLock) {
	if (fLock) {
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else {
		InterlockedDecrement(&glNumberOfServerLocks);
	}
	return S_OK;
}

//Exportable COM DLL methods
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) {
	//Variable declarations
	CSumSubstractClassFactory* pCSumSubstractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubstract) {
		return CLASS_E_CLASSNOTAVAILABLE;
	}
	pCSumSubstractClassFactory = new CSumSubstractClassFactory;
	if (pCSumSubstractClassFactory == NULL) {
		return E_OUTOFMEMORY;
	}
	hr = pCSumSubstractClassFactory->QueryInterface(riid, ppv);
	pCSumSubstractClassFactory->Release();
	return hr;
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void) {
	//Code
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0) {
		return S_OK;
	}
	else {
		return S_FALSE;
	}
}
