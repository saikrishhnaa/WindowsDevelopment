class IMultiplication :public IUnknown
{
public:
	// IMultiplication specific method declaration pure virtual
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision :public IUnknown
{
public:
	//Division specific method declarations pure virtual - {249477C9-92A4-4559-BDA3-55D7F5E7E15A}
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

// CLSID of MultiplicationDivision Component - {249477C9-92A4-4559-BDA3-55D7F5E7E15A}
const CLSID CLSID_MultiplicationDivision = { 0x249477c9, 0x92a4, 0x4559, 0xbd, 0xa3, 0x55, 0xd7, 0xf5, 0xe7, 0xe1, 0x5a };

// IID of IMultiplication Interface - {B8290B44-0470-4aa3-84AF-1126ED4A2D49}
const IID IID_IMultiplication = { 0xb8290b44, 0x470, 0x4aa3, 0x84, 0xaf, 0x11, 0x26, 0xed, 0x4a, 0x2d, 0x49 };

// IID of IDivision Interface - {67A6093F-9450-4970-80E5-406D4DED2E0B}
const IID IID_IDivision = { 0x67a6093f, 0x9450, 0x4970, 0x80, 0xe5, 0x40, 0x6d, 0x4d, 0xed, 0x2e, 0xb };

// {BA478B39-6DAC-4099-8A38-D78571A799DC}
//DEFINE_GUID(<< name >> ,
//	0xba478b39, 0x6dac, 0x4099, 0x8a, 0x38, 0xd7, 0x85, 0x71, 0xa7, 0x99, 0xdc);
