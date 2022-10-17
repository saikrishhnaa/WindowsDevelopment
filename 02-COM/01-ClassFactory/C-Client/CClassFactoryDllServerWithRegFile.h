#pragma once
#undef Interface
#define Interface ISum
DECLARE_INTERFACE_(ISum, IUnknown)
{
	//IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID, void**) PURE; //STDMETHOD means it's return value is HRESULT and __stdcall used and THIS_ means there are some other parameters are after THIS_.
	STDMETHOD_(ULONG, AddRef)(THIS) PURE; //STDMETHOD_ means it's return value is other than HRESULT but __stdcall used and only THIS means there are no other parameters are after THIS.
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	//ISum methods
	STDMETHOD(SumOfTwoIntegers)(THIS_ int, int, int*) PURE;
};

#undef Interface
#define Interface ISubstract
DECLARE_INTERFACE_(ISubstract, IUnknown)
{
	//IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID, void**) PURE; //STDMETHOD means it's return value is HRESULT and __stdcall used and THIS_ means there are some other parameters are after THIS_
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	//ISubstract methods
	STDMETHOD(SubstractionOfTwoIntegers)(THIS_ int, int, int*) PURE;
};

// {7D01FD02-BBFA-4542-8997-DE42ECFE5659}
const CLSID CLSID_SumSubstract = { 0x7d01fd02, 0xbbfa, 0x4542, 0x89, 0x97, 0xde, 0x42, 0xec, 0xfe, 0x56, 0x59 }; //CLSID, IID typedef of GUID which is type of UUID

// {BE4590E1-AF87-4adb-BDD3-41C02DF2113F}
const IID IID_ISum = { 0xbe4590e1, 0xaf87, 0x4adb, 0xbd, 0xd3, 0x41, 0xc0, 0x2d, 0xf2, 0x11, 0x3f };

// {345C9503-8F39-4c41-8A51-847485D76BBD}
const IID IID_ISubstract = { 0x345c9503, 0x8f39, 0x4c41, 0x8a, 0x51, 0x84, 0x74, 0x85, 0xd7, 0x6b, 0xbd };
