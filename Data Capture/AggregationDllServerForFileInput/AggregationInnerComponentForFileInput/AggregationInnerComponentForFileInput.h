class IFileReader : public IUnknown
{
public:
	// IFileInput specific method declaration pure virtual
	virtual HRESULT __stdcall ReadFromFile(char path[], char data[]) = 0;
};

// {76A681F5-60EE-4ea6-8A2B-1A312A745C9F}
const CLSID CLSID_FileInputInner = { 0x76a681f5, 0x60ee, 0x4ea6, 0x8a, 0x2b, 0x1a, 0x31, 0x2a, 0x74, 0x5c, 0x9f };

// {0E728716-C829-4eb3-BE55-625E327C503B}
const IID IID_IFileReader = { 0xe728716, 0xc829, 0x4eb3, 0xbe, 0x55, 0x62, 0x5e, 0x32, 0x7c, 0x50, 0x3b };
