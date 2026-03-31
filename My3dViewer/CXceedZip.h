// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

#import "C:\\Windows\\System32\\XceedZipX64.dll" no_namespace
// CXceedZip 래퍼 클래스

class CXceedZip : public COleDispatchDriver
{
public:
	CXceedZip() {} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXceedZip(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXceedZip(const CXceedZip& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXceedZip 메서드
public:
	BOOL get_Abort()
	{
		BOOL result;
		InvokeHelper(0xb54, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Abort(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xb54, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_BasePath()
	{
		CString result;
		InvokeHelper(0xc8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_BasePath(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xc8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_CompressionLevel()
	{
		long result;
		InvokeHelper(0x190, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_CompressionLevel(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x190, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_EncryptionPassword()
	{
		CString result;
		InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_EncryptionPassword(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_RequiredFileAttributes()
	{
		long result;
		InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_RequiredFileAttributes(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x132, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ExcludedFileAttributes()
	{
		long result;
		InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ExcludedFileAttributes(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x133, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_FilesToProcess()
	{
		CString result;
		InvokeHelper(0x12c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_FilesToProcess(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x12c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_FilesToExclude()
	{
		CString result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_FilesToExclude(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	DATE get_MinDateToProcess()
	{
		DATE result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
		return result;
	}
	void put_MinDateToProcess(DATE newValue)
	{
		static BYTE parms[] = VTS_DATE;
		InvokeHelper(0x12e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	DATE get_MaxDateToProcess()
	{
		DATE result;
		InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
		return result;
	}
	void put_MaxDateToProcess(DATE newValue)
	{
		static BYTE parms[] = VTS_DATE;
		InvokeHelper(0x12f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MinSizeToProcess()
	{
		long result;
		InvokeHelper(0x130, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MinSizeToProcess(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x130, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MaxSizeToProcess()
	{
		long result;
		InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MaxSizeToProcess(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x131, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SplitSize()
	{
		long result;
		InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SplitSize(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_PreservePaths()
	{
		BOOL result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_PreservePaths(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ProcessSubfolders()
	{
		BOOL result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ProcessSubfolders(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_SkipIfExisting()
	{
		BOOL result;
		InvokeHelper(0x134, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_SkipIfExisting(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x134, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_SkipIfNotExisting()
	{
		BOOL result;
		InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_SkipIfNotExisting(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x135, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_SkipIfOlderDate()
	{
		BOOL result;
		InvokeHelper(0x136, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_SkipIfOlderDate(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x136, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_SkipIfOlderVersion()
	{
		BOOL result;
		InvokeHelper(0x137, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_SkipIfOlderVersion(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x137, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_TempFolder()
	{
		CString result;
		InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_TempFolder(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_UseTempFile()
	{
		BOOL result;
		InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_UseTempFile(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_UnzipToFolder()
	{
		CString result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_UnzipToFolder(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_ZipFilename()
	{
		CString result;
		InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_ZipFilename(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_CurrentOperation()
	{
		long result;
		InvokeHelper(0xb55, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_SpanMultipleDisks()
	{
		long result;
		InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SpanMultipleDisks(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ExtraHeaders()
	{
		long result;
		InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ExtraHeaders(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ZipOpenedFiles()
	{
		BOOL result;
		InvokeHelper(0x193, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ZipOpenedFiles(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x193, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_BackgroundProcessing()
	{
		BOOL result;
		InvokeHelper(0x194, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_BackgroundProcessing(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x194, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SfxBinaryModule()
	{
		CString result;
		InvokeHelper(0x1f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SfxBinaryModule(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SfxButtons(long xIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, xIndex);
		return result;
	}
	void put_SfxButtons(long xIndex, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR;
		InvokeHelper(0x1f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, xIndex, newValue);
	}
	CString get_SfxMessages(long xIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1f7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, xIndex);
		return result;
	}
	void put_SfxMessages(long xIndex, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR;
		InvokeHelper(0x1f7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, xIndex, newValue);
	}
	CString get_SfxStrings(long xIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1f8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, xIndex);
		return result;
	}
	void put_SfxStrings(long xIndex, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR;
		InvokeHelper(0x1f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, xIndex, newValue);
	}
	CString get_SfxDefaultPassword()
	{
		CString result;
		InvokeHelper(0x1f9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SfxDefaultPassword(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1f9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SfxDefaultUnzipToFolder()
	{
		CString result;
		InvokeHelper(0x1fa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SfxDefaultUnzipToFolder(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1fa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SfxExistingFileBehavior()
	{
		long result;
		InvokeHelper(0x1fb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SfxExistingFileBehavior(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1fb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SfxReadmeFile()
	{
		CString result;
		InvokeHelper(0x1fc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SfxReadmeFile(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1fc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SfxExecuteAfter()
	{
		CString result;
		InvokeHelper(0x1fd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SfxExecuteAfter(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1fd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_SfxInstallMode()
	{
		BOOL result;
		InvokeHelper(0x1fe, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_SfxInstallMode(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x1fe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SfxProgramGroup()
	{
		CString result;
		InvokeHelper(0x1ff, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SfxProgramGroup(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1ff, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SfxProgramGroupItems()
	{
		CString result;
		InvokeHelper(0x200, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SfxProgramGroupItems(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x200, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SfxExtensionsToAssociate()
	{
		CString result;
		InvokeHelper(0x201, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SfxExtensionsToAssociate(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x201, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SfxIconFilename()
	{
		CString result;
		InvokeHelper(0x202, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SfxIconFilename(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x202, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void AddFilesToProcess(LPCTSTR sFileMask)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xbb8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sFileMask);
	}
	void AddFilesToExclude(LPCTSTR sFileMask)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xbb9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sFileMask);
	}
	long PreviewFiles(BOOL bCalcCompSize)
	{
		long result;
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc1c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bCalcCompSize);
		return result;
	}
	long ListZipContents()
	{
		long result;
		InvokeHelper(0xc1d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long Zip()
	{
		long result;
		InvokeHelper(0xc1f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long Unzip()
	{
		long result;
		InvokeHelper(0xc20, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long RemoveFiles()
	{
		long result;
		InvokeHelper(0xc21, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long TestZipFile(BOOL bCheckCompressedData)
	{
		long result;
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc22, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bCheckCompressedData);
		return result;
	}
	long GetZipFileInformation(long * lNbFiles, long * lCompressedSize, long * lUncompressedSize, short * nCompressionRatio, BOOL * bSpanned)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI2 VTS_PBOOL;
		InvokeHelper(0xc1e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lNbFiles, lCompressedSize, lUncompressedSize, nCompressionRatio, bSpanned);
		return result;
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SfxAddProgramGroupItem(LPCTSTR sApplication, LPCTSTR sDescription)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0xc80, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sApplication, sDescription);
	}
	void SfxAddExtensionToAssociate(LPCTSTR sExtension, LPCTSTR sApplication, LPCTSTR sDescription)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0xc81, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sExtension, sApplication, sDescription);
	}
	void SfxResetButtons()
	{
		InvokeHelper(0xc82, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SfxResetMessages()
	{
		InvokeHelper(0xc83, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SfxResetStrings()
	{
		InvokeHelper(0xc84, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SfxClearButtons()
	{
		InvokeHelper(0xc85, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SfxClearMessages()
	{
		InvokeHelper(0xc86, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SfxClearStrings()
	{
		InvokeHelper(0xc87, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long Convert(LPCTSTR sDestFilename)
	{
		long result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xc88, DISPATCH_METHOD, VT_I4, (void*)&result, parms, sDestFilename);
		return result;
	}
	BOOL License(LPCTSTR sLicense)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x176f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, sLicense);
		return result;
	}
	BOOL SfxLoadConfig(LPCTSTR sConfigFilename)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x203, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, sConfigFilename);
		return result;
	}
	BOOL SfxSaveConfig(LPCTSTR sConfigFilename)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x204, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, sConfigFilename);
		return result;
	}
	CString GetErrorDescription(long xType, long lValue)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x1388, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, xType, lValue);
		return result;
	}
	long GetZipContents(LPDISPATCH * xContents, long xFormat)
	{
		long result;
		static BYTE parms[] = VTS_PDISPATCH VTS_I4;
		InvokeHelper(0xc23, DISPATCH_METHOD, VT_I4, (void*)&result, parms, xContents, xFormat);
		return result;
	}
	CString get_SfxFilesToCopy()
	{
		CString result;
		InvokeHelper(0x205, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SfxFilesToCopy(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x205, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SfxFilesToRegister()
	{
		CString result;
		InvokeHelper(0x206, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SfxFilesToRegister(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x206, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SfxRegistryKeys()
	{
		CString result;
		InvokeHelper(0x207, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SfxRegistryKeys(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x207, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_DeleteZippedFiles()
	{
		BOOL result;
		InvokeHelper(0x195, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_DeleteZippedFiles(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x195, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_FirstDiskFreeSpace()
	{
		long result;
		InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_FirstDiskFreeSpace(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MinDiskFreeSpace()
	{
		long result;
		InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MinDiskFreeSpace(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_EventsToTrigger()
	{
		long result;
		InvokeHelper(0x138, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_EventsToTrigger(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x138, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void SfxAddExecuteAfter(LPCTSTR sApplication, LPCTSTR sParameters)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0xc89, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sApplication, sParameters);
	}
	void SfxAddFileToCopy(LPCTSTR sSource, LPCTSTR sDestination)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0xc8a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sSource, sDestination);
	}
	void SfxAddFileToRegister(LPCTSTR sDllServer)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xc8b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sDllServer);
	}
	void SfxAddRegistryKey(LPCTSTR sKey, LPCTSTR sValueName, VARIANT& vaValue)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_VARIANT;
		InvokeHelper(0xc8c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sKey, sValueName, &vaValue);
	}
	long GetZipContentsEx(VARIANT * xContents, long xFormat)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_I4;
		InvokeHelper(0xc24, DISPATCH_METHOD, VT_I4, (void*)&result, parms, xContents, xFormat);
		return result;
	}
	long get_CompressionMethod()
	{
		long result;
		InvokeHelper(0x196, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_CompressionMethod(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x196, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Use64BitEvents()
	{
		BOOL result;
		InvokeHelper(0x139, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Use64BitEvents(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x139, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long GetZipFileInformation64(VARIANT * vaNbFiles, VARIANT * vaCompressedSizeLow, VARIANT * vaCompressedSizeHigh, VARIANT * vaUncompressedSizeLow, VARIANT * vaUncompressedSizeHigh, VARIANT * vaCompressionRatio, VARIANT * vaIsSpanned)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
		InvokeHelper(0xc25, DISPATCH_METHOD, VT_I4, (void*)&result, parms, vaNbFiles, vaCompressedSizeLow, vaCompressedSizeHigh, vaUncompressedSizeLow, vaUncompressedSizeHigh, vaCompressionRatio, vaIsSpanned);
		return result;
	}
	long UpdateZipDate(long xOptions)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc26, DISPATCH_METHOD, VT_I4, (void*)&result, parms, xOptions);
		return result;
	}
	long get_EncryptionMethod()
	{
		long result;
		InvokeHelper(0x197, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_EncryptionMethod(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x197, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_EncryptionStrength()
	{
		short result;
		InvokeHelper(0x198, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_EncryptionStrength(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x198, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_IgnoredExtraHeaders()
	{
		long result;
		InvokeHelper(0x199, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_IgnoredExtraHeaders(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x199, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SplitSizeHigh()
	{
		long result;
		InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SplitSizeHigh(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	__int64 get_SplitSize64()
	{
		__int64 result;
		InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I8, (void*)&result, NULL);
		return result;
	}
	void put_SplitSize64(__int64 newValue)
	{
		static BYTE parms[] = VTS_I8;
		InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_TextEncoding()
	{
		long result;
		InvokeHelper(0x19a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_TextEncoding(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x19a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_UnicodeUsagePolicy()
	{
		long result;
		InvokeHelper(0x19b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_UnicodeUsagePolicy(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x19b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

	// IXceedZip 속성
public:

};
