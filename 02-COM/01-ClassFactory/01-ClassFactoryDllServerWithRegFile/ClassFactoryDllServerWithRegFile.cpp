#include<windows.h>
#include<stdio.h>
#include "ClassFactoryDllServerWithRegFile.h"

//Global variables
long glNumberOfActiveComponents; //1. Why global
long glNumberOfServerLocks;

FILE* filepntr;

//Coclass
class CSumSubstract : public ISum, public ISubstract {
	private:
		long m_cRef;
	public:
		//Constructor
		CSumSubstract(void); //void - for older compiler compatibility

		//Destructor
		~CSumSubstract(void);

		//IUnknown methods
		HRESULT __stdcall QueryInterface(REFIID, void**);

		ULONG __stdcall AddRef(void);

		ULONG __stdcall Release(void);

		//ISum method
		HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

		//ISubstract method
		HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

}; 

//Class factory class
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
	FILE* fptr;

	// use appropriate location if you are using MacOS or Linux
	fptr = fopen("C:\\WinDev2022\\02-COM\\01-ClassFactory\\02-ClientOfClassFactoryDllServerWithRegFile\\program1.txt", "w");

	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}

	fprintf(fptr, "DLL.cpp");
	fclose(fptr);
	MessageBox(NULL, TEXT("DllGetClassObject"), TEXT("Dll"), MB_OK);
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

//CSubSubstract Implementation

//Constructor
CSumSubstract :: CSumSubstract(void) {
	//Code
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

//Destructor
CSumSubstract :: ~CSumSubstract(void) {
	InterlockedDecrement(&glNumberOfActiveComponents);
}	

//hidden in class this, vptr, typeinfo

//IUnknown methods implementation
HRESULT CSumSubstract::QueryInterface(REFIID riid, void** ppv) {
	//Code
	/*
	'==' overloaded by function => inline Bool operator==(const GUID& guidOne, const GUID& guidTwo) {
								      return IsEqualGuid(guid1, guid2);
								   }
	*/

	if(riid == IID_IUnknown) //2. How equating struct's  //Adjuster Thunk -> mircrosoft follow
		*ppv = static_cast<ISum*>(this); //templatize means doing standardize of something
	else if(riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubstract)
		*ppv = static_cast<ISubstract*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*> (*ppv)->AddRef();
	return (S_OK);
} //Adjustor Thunk , (Dummy function)Stub function -> _PureCall(), polymorphic call despatching, MIT method implementation table, VPTR - (method virtual fun table)VTBL - interfaces - array of semantic functions

ULONG CSumSubstract::AddRef(void) {
	//Code
	InterlockedIncrement(&m_cRef);

	return (m_cRef); //3. m_cRef should be ULONG ?
}

ULONG CSumSubstract::Release(void) {
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
HRESULT CSumSubstract::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	//Code
	*pSum = num1 + num2;
	return (S_OK);
}

HRESULT CSumSubstract::SubtractionOfTwoIntegers(int num1, int num2, int* pSum)
{
	//Code
	*pSum = num1 - num2;
	return (S_OK);
}

//CSumSubstractClassFactory Implementation

//Constructor
CSumSubstractClassFactory::CSumSubstractClassFactory(void)
{
	m_cRef = 1;
}

//Destructor
CSumSubstractClassFactory::~CSumSubstractClassFactory(void)
{

}

//IUnknown methods implementation
HRESULT CSumSubstractClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	//Code
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		fprintf(filepntr, "CSumSubstractClassFactory QueryInterface method, null");
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*> (*ppv)->AddRef();
	return (S_OK);
}

ULONG CSumSubstractClassFactory::AddRef(void) {
	//Code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubstractClassFactory::Release(void) {
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
HRESULT CSumSubstractClassFactory::CreateInstance(IUnknown* pUnkOuter/*It is NULL*/, REFIID riid, void** ppv)
{
	//Variable declaration
	CSumSubstract* pCSumSubstract = NULL;
	HRESULT hr;

	//Code
	if (pUnkOuter != NULL)
	{
		return (CLASS_E_NOAGGREGATION);
	}

	pCSumSubstract = new CSumSubstract;

	if (pCSumSubstract == NULL)
	{
		return (E_OUTOFMEMORY);
	}

	hr = pCSumSubstract->QueryInterface(riid, ppv);

	pCSumSubstract->Release();


	return (hr);
}

HRESULT CSumSubstractClassFactory::LockServer(BOOL fLock)
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

//Exportable COM DLL methods
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	MessageBox(NULL, TEXT("DllGetClassObject"), TEXT("Dll"), MB_OK);
	//Variable Declarations
	CSumSubstractClassFactory* pCSumSubstractClassFactory = NULL;
	HRESULT hr;

	//Code
	if (rclsid != CLSID_SumSubstract)
	{
		return (CLASS_E_CLASSNOTAVAILABLE);
	}

	pCSumSubstractClassFactory = new CSumSubstractClassFactory;
	if (pCSumSubstractClassFactory == NULL)
	{
		return (E_OUTOFMEMORY);
	}
	hr = pCSumSubstractClassFactory->QueryInterface(riid, ppv);

	pCSumSubstractClassFactory->Release();
	return (hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow() {
	//Code
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return (S_OK);
	else
		return (S_FALSE);
} //then CoFreeLibrary(DLL handle) -> FreeLibrary(DLL handle)

//CoFreeUnusedLibraries

