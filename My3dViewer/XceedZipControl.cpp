#include "stdafx.h"
#include "XceedZipControl.h"
#include "tinyxml2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CXceedZipControl::CXceedZipControl(void)
{
	m_pArSelectionLayerName = NULL;
}

CXceedZipControl::~CXceedZipControl(void)
{
}
BOOL CXceedZipControl::SetZipFolders(CStringArray *strArrFiles,CString strDestFilePath)
{
	CString strXceedSorFilePaths,strPath;
	int nNumOfFile;

	CoInitialize( NULL );
	long xRet;
	IXceedZipPtr piXceedZip( CLSID_XceedZip );
#ifdef _WIN64
	piXceedZip->License( _bstr_t( L"ZIX65-G3RCL-4AKBP-AC4A" ) );
#else
	piXceedZip->License( _bstr_t( L"ZIP65-LMWLB-EAYAD-ACAAA" ) );
#endif

	piXceedZip->CompressionLevel=xclLow;
	piXceedZip->PreservePaths = TRUE;
	piXceedZip->BackgroundProcessing = FALSE;
	piXceedZip->ZipFilename = strDestFilePath.GetBuffer(0); 

	nNumOfFile = strArrFiles->GetSize();
	for(int i=0; i<nNumOfFile;i++)
	{
		strPath = strArrFiles->GetAt(i);
		piXceedZip->AddFilesToProcess(strPath.GetBuffer(0));
	}
	xRet = piXceedZip->Zip();
	piXceedZip->Release();
	piXceedZip.Detach();
	CoUninitialize();
	if(xRet != 0)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CXceedZipControl::SetZipFolders(CString strSrcFolderPath,CString strDestFilePath,CStringArray *pArSelectionLayerName)
{
	m_pArSelectionLayerName = pArSelectionLayerName;
	CString strXceedSorFilePaths,strMsg, strBasePath, strTemp;
	CFileFind finder;
	CString strPath;
	CString strFilePath;
	BOOL bfound;
	int nFolderType;

	CoInitialize( NULL );
	long xRet;

	IXceedZipPtr piXceedZip( CLSID_XceedZip );
#ifdef _WIN64
	piXceedZip->License( _bstr_t( L"ZIX65-G3RCL-4AKBP-AC4A" ) );
#else
	piXceedZip->License( _bstr_t( L"ZIP65-LMWLB-EAYAD-ACAAA" ) );
#endif	

	piXceedZip->CompressionLevel=xclLow;
	piXceedZip->PreservePaths = TRUE;
	piXceedZip->BackgroundProcessing = FALSE;
	piXceedZip->ZipFilename = strDestFilePath.GetBuffer(0);
//	piXceedZip->BasePath = (_bstr_t)strBasePath;

	if(strSrcFolderPath.Right(1)!= _T("\\"))
		strPath = strSrcFolderPath + _T("\\");
	else
		strPath = strSrcFolderPath;	

//	AfxMessageBox(strPath);

	nFolderType = GetFolderType(strPath);
	if(nFolderType == XCEEDZIP_INCLUDE_FILE_FOLDER || nFolderType == XCEEDZIP_EXCLUDE_FOLDER )
	{
		AddZipFiles(piXceedZip,strPath);
	}
	strPath += _T("*.*");
	bfound = finder.FindFile(strPath);
	while(bfound)
	{
		bfound = finder.FindNextFile();
		strFilePath = finder.GetFilePath();
		if(finder.IsDots() ) 
		{
			continue;
		}
		else if(finder.IsDirectory() && strSrcFolderPath.CompareNoCase(strFilePath) != 0)
		{
			AddSubFolders(piXceedZip, strFilePath);
		}
	}
	finder.Close();

	xRet = piXceedZip->Zip();
	piXceedZip->Release();
	piXceedZip.Detach();

//	AfxMessageBox(_T("Zip OK!!!"));

	CoUninitialize();
	if(xRet != xerSuccess)
	{
		strMsg.Format(_T("%s %d"), _T("Fail"),xRet);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	return TRUE;
}
int	CXceedZipControl::GetFolderType(CString strFolderPath)
{
	CFileFind finder;
	CString strPath,strFilePath, strMsg;
	BOOL bfound;
	if(strFolderPath.Right(1)!= _T("\\"))
		strFolderPath += _T("\\");
	strPath = strFolderPath + _T("*.*");
	bfound = finder.FindFile(strPath);
	int nCountOfFolder = 0,nCountOfFile = 0;
	while(bfound)
	{
		bfound = finder.FindNextFile();
		strFilePath = finder.GetFilePath();
		if(finder.IsDots() ) 
		{
			continue;
		}
		else if(finder.IsDirectory())
		{
			nCountOfFolder++;
		}
		else
		{
			nCountOfFile++;
		}
	}
	finder.Close();
	if(nCountOfFile >0 && nCountOfFolder >0 )
	{
		return XCEEDZIP_INCLUDE_FILE_FOLDER;
	}
	else if(nCountOfFile >0)
	{
		return XCEEDZIP_EXCLUDE_FOLDER;
	}
	else if(nCountOfFolder >0)
	{
		return XCEEDZIP_EXCLUDE_FILE;
	}
	return XCEEDZIP_EMPTY_FOLDER;
}
BOOL CXceedZipControl::UnZipFolders(CString strZipFilePath,CString strDestFolderPath)
{
	CFileFind finder;
	long xRet;
	CString strMsg;

	CoInitialize( NULL );
	IXceedZipPtr piXceedZip( CLSID_XceedZip );

#ifdef _WIN64
	piXceedZip->License( _bstr_t( L"ZIX65-G3RCL-4AKBP-AC4A" ) );
#else
	piXceedZip->License( _bstr_t( L"ZIP65-LMWLB-EAYAD-ACAAA" ) );
#endif
	piXceedZip->CompressionLevel=xclLow;
	piXceedZip->PreservePaths = TRUE;
	piXceedZip->BackgroundProcessing = FALSE;

	if(!finder.FindFile(strZipFilePath))
	{
		strMsg.Format(_T("%s (%s)!!!"),_T("Fail"), strZipFilePath);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	finder.Close();

	piXceedZip->ZipFilename = _bstr_t(strZipFilePath);
	piXceedZip->UnzipToFolder = _bstr_t(strDestFolderPath);
	xRet = piXceedZip->Unzip();

	piXceedZip->Release();
	piXceedZip.Detach();
	CoUninitialize();

	if(xRet != xerSuccess)
	{
		return FALSE;
	}
	return TRUE;
}
void CXceedZipControl::AddZipFiles(IXceedZipPtr piXceedZip, CString strForderPath)
{
	CString strPath;
	if(strForderPath.Right(1)!= _T("\\"))
		strPath = strForderPath + _T("\\");
	else
		strPath = strForderPath;
	strPath += _T("*");
	piXceedZip->AddFilesToProcess(strPath.GetBuffer(0));
}
void CXceedZipControl::AddSubFolders(IXceedZipPtr piXceedZip, CString strForderPath)
{

	CFileFind finder;
	CString strPath,strBuf;
	CString strFilePath;
	BOOL bfound;
	int nFolderType;
	BOOL bLayers = FALSE;
	BOOL bPass = FALSE;
	if(m_pArSelectionLayerName != NULL)
	{
		strPath = strForderPath;
		strBuf = ExtractLastWord(strPath,_T('\\'));
		if(strBuf.CompareNoCase(_T("Layers")) == 0)
		{
			bLayers = TRUE;
		}
	}
	if(strForderPath.Right(1)!= _T("\\"))
		strPath = strForderPath + _T("\\");
	else
		strPath = strForderPath;
	
	nFolderType = GetFolderType(strPath);
	if(nFolderType == XCEEDZIP_INCLUDE_FILE_FOLDER || nFolderType == XCEEDZIP_EXCLUDE_FOLDER )
	{
		AddZipFiles(piXceedZip,strPath);
	}
	strPath += _T("*.*");
	bfound = finder.FindFile(strPath);
	while(bfound)
	{
		bfound = finder.FindNextFile();
		strFilePath = finder.GetFilePath();
		if(finder.IsDots() ) 
		{
			continue;
		}
		else if(finder.IsDirectory() && strForderPath.CompareNoCase(strFilePath) != 0)
		{
			if(bLayers)
			{
				strPath = strFilePath;
				strBuf = ExtractLastWord(strPath,_T('\\'));
				bPass = TRUE;
				for(int i=0;i<m_pArSelectionLayerName->GetSize();i++)
				{
					if(strBuf.CompareNoCase(m_pArSelectionLayerName->GetAt(i)) == 0)
					{
						bPass = FALSE;
					}
				}
				if(bPass)
				{
					continue;
				}
			}
			int nFolderType = GetFolderType(strFilePath);
			switch(nFolderType)
			{
			case XCEEDZIP_EMPTY_FOLDER:
				break;
			case XCEEDZIP_INCLUDE_FILE_FOLDER:
				AddSubFolders(piXceedZip, strFilePath);
				break;
			case XCEEDZIP_EXCLUDE_FILE:
				AddSubFolders(piXceedZip, strFilePath);
				break;
			case XCEEDZIP_EXCLUDE_FOLDER:
				AddZipFiles(piXceedZip,strFilePath);
				break;
			default:
				AfxMessageBox(_T("default"));
				break;

			}
		}
	}
	finder.Close();
}
CString CXceedZipControl::ImgCompressToCString(cv::Mat IMG, BOOL bType8uc1)
{
	xcdCompressionError error;
	VARIANT dataToCompress;
	VARIANT compressedData;
	SAFEARRAY * safeArray;
	unsigned char * safeArrayData;
	size_t size;
	unsigned char * Imgdata;


	Imgdata = IMG.data;

	int nDataCount;
	int count = IMG.cols * IMG.rows;
	if (bType8uc1)
	{
		size = count * sizeof(unsigned char);
	}
	else
	{
		size = count * sizeof(float);
	}

	// Create a one-dimensional array of unsigned bytes
	safeArray = SafeArrayCreateVector(VT_UI1, 0, size);

	// Access the array data and copy the data to the array
	SafeArrayAccessData(safeArray, (void **)&safeArrayData);// 1차원 배열을 만듬 안전한 
	CopyMemory(safeArrayData, Imgdata, size);
	SafeArrayUnaccessData(safeArray);

	IXceedCompressionPtr piXceedcompress(CLSID_XceedCompression);


#ifdef _WIN64
	piXceedcompress->License(_bstr_t(L"ZIX65-G3RCL-4AKBP-AC4A"));
#else
	piXceedcompress->License(_bstr_t(L"ZIP65-LMWLB-EAYAD-ACAAA"));
#endif
	/* The VARIANT structure doesn't support straight unicode strings. But it does
	support something close to it. Something called BSTR.
	A BSTR, known as basic string or binary string, is a pointer to a wide
	character string used by Automation data manipulation functions.
	We will use the COM _bstr_t helper class to build the BSTR out of the
	supplied unicode string. */

	// Copy the supplied unicode string data to the BSTR object


	// Initialize the variants we will use
	VariantInit(&dataToCompress);
	VariantInit(&compressedData);



	// Set the data type to BSTR
	dataToCompress.vt = VT_ARRAY | VT_UI1;

	// Assign the safe array to the VARIANT. Responsability is transfered
	dataToCompress.parray = safeArray;

	// Compress the data
	error = piXceedcompress->Compress(&dataToCompress, &compressedData, VARIANT_TRUE);

	// We no longer need the data to compress
	CString strResult;
	if (error != xceSuccess)
	{
		strResult.Format(_T(" "));
	}
	else
	{
		strResult = PrintByteArrayVariant< unsigned char >(&compressedData);
	}



	/* compressedData now contains an array of bytes. This is not a string. It is the
	compressed data and is not in a specific form.

	In this example, we will display each byte in the array as an hexadecimal value.
	In a real application, the data in the array could be saved in a file, sent to another
	computer, whatever. */

	// Clear the compressed data
	VariantClear(&dataToCompress);
	VariantClear(&compressedData);

	return strResult;
}
cv::Mat CXceedZipControl::ImgUnCompressToMat(const char *pData, int nHight, int nWidth, BOOL bType8UC1)
{
	xcdCompressionError error;
	VARIANT compressdData;
	VARIANT uncompressedData;
	size_t size;
	IXceedCompressionPtr piXceedcompress(CLSID_XceedCompression);

#ifdef _WIN64
	piXceedcompress->License(_bstr_t(L"ZIX65-G3RCL-4AKBP-AC4A"));
#else
	piXceedcompress->License(_bstr_t(L"ZIP65-LMWLB-EAYAD-ACAAA"));
#endif

	VariantInit(&compressdData);
	VariantInit(&uncompressedData);

	CString strPath, strElement, strElementValue, strAttr, strAttrValue;
	strPath.Format(_T("D:\\savedimage3D\\Test.xml"));

	tinyxml2::XMLDocument XMLDoc;
	tinyxml2::XMLElement *pRootElement, *pSubElement;
	const tinyxml2::XMLAttribute *pAttr;

	SAFEARRAY * arrayDescriptor;
	CString str = CharToString(pData);
	//SafeArrayUnaccessData(arrayDescriptor);

	size = str.GetLength() / 2;
	compressdData.vt = VT_ARRAY | VT_UI1;

	// Assign the safe array to the VARIANT. Responsability is transfered

	BYTE* charArray;
	unsigned char *charData = new unsigned char[size];
	for (int i = 0; i < size; i++)
	{
		charData[i] = 16 * StringToHex(pData[i * 2]) + StringToHex(pData[i * 2 + 1]);
	}

	arrayDescriptor = SafeArrayCreateVector(VT_UI1, 0, size);


	// Access the array data and copy the data to the array
	SafeArrayAccessData(arrayDescriptor, (void **)&charArray);// 1차원 배열을 만듬 안전한 
	CopyMemory(charArray, charData, size);
	SafeArrayUnaccessData(arrayDescriptor);
	compressdData.parray = arrayDescriptor;
	delete[] charData;
	charData = NULL;




	error = piXceedcompress->Uncompress(&compressdData, &uncompressedData, VARIANT_TRUE);

	// We no longer need the compressed data
	cv::Mat matResult;
	unsigned char *Data = OutPutMat< unsigned char >(&uncompressedData);
	if (error != xceSuccess)
	{
		if (bType8UC1)
		{
			matResult = cv::Mat(nHight, nWidth, CV_8UC1);
		}
		else
		{
			matResult = cv::Mat(nHight, nWidth, CV_32FC1);
		}
	}
	else
	{
		if (bType8UC1)
		{
			matResult = cv::Mat(nHight, nWidth, CV_8UC1, (void*)Data);
		}
		else
		{
			matResult = cv::Mat(nHight, nWidth, CV_32FC1, (void*)Data);
		}
	}
	cv::Mat ResultCopy;
	if (bType8UC1)
	{
		ResultCopy = cv::Mat(nHight, nWidth, CV_8UC1);
	}
	else
	{
		ResultCopy = cv::Mat(nHight, nWidth, CV_32FC1);
	}
	ResultCopy = matResult.clone();
	VariantClear(&uncompressedData);
	VariantClear(&compressdData);

	return ResultCopy;
}
template< class DataType > CString  CXceedZipControl::PrintByteArrayVariant(VARIANT * variant)
{
	DataType * data;
	SAFEARRAY * arrayDescriptor;
	int i, count;

	// Get the array descriptor from the variant
	arrayDescriptor = variant->parray;

	// Gain access to the array data
	SafeArrayAccessData(arrayDescriptor, (void **)&data);

	// Get the number of elements in the first dimension of the array

	count = arrayDescriptor->rgsabound[0].cElements / sizeof(DataType);


	CString str, strByte;

	for (i = 0; i < count; i++)
	{
		str = _T(" ");
		// If we need to change line
		// If we need to seperate a group of data
		// Access the current index as we would a normal array
		str.Format(_T("%.2X"), data[i]);
		strByte += str;

	}
	// Release access to the array data

	SafeArrayUnaccessData(arrayDescriptor);

	return strByte;
}
template< class DataType > unsigned char * CXceedZipControl::OutPutMat(VARIANT * variant)
{
	DataType * data;
	SAFEARRAY * arrayDescriptor;

	// Get the array descriptor from the variant
	arrayDescriptor = variant->parray;

	// Gain access to the array data
	SafeArrayAccessData(arrayDescriptor, (void **)&data);

	// Get the number of elements in the first dimension of the array
	SafeArrayUnaccessData(arrayDescriptor);

	return data;
}


//////////////////////////////////////////////////////////////////
// Function name    : ExtractLastWord
// Description      : 입력된 문자열중 마지막 워드를 제거한다.
// Return type      : CString  입력된 문자열중 제거된 마지막 워드
// Argument         : CString *str, CString sep,BOOL bTrim
// 
// 1. str : Source String
// 2. sep : Delimiter
// 3. bTrim : 좌우 Space의 제거 Option
CString CXceedZipControl::ExtractLastWord(CString *str, TCHAR sep, BOOL bTrim)
{
	CString csRtn;
	int nDelPos = str->ReverseFind(sep);
	if (nDelPos < 0)
	{
		csRtn = *str;
		*str = _T("");
	}
	else
	{
		csRtn = str->Right(str->GetLength() - nDelPos - 1);
		*str = str->Left(nDelPos);
	}

	if (bTrim)
	{
		csRtn.TrimLeft(VK_SPACE); csRtn.TrimLeft(VK_TAB);
		csRtn.TrimRight(VK_SPACE); csRtn.TrimRight(VK_TAB);
	}

	return csRtn;
}

CString CXceedZipControl::ExtractLastWord(CString& str, TCHAR sep, BOOL bTrim)
{
	CString csRtn;
	int nDelPos = str.ReverseFind(sep);
	if (nDelPos < 0)
	{
		csRtn = str;
		str = _T("");
	}
	else
	{
		csRtn = str.Right(str.GetLength() - nDelPos - 1);
		str = str.Left(nDelPos);
	}

	if (bTrim)
	{
		csRtn.TrimLeft(VK_SPACE); csRtn.TrimLeft(VK_TAB);
		csRtn.TrimRight(VK_SPACE); csRtn.TrimRight(VK_TAB);
	}
	return csRtn;
}

CString CXceedZipControl::CharToString(const char *szStr)
{
	CString strRet;

	int nLen = strlen(szStr) + sizeof(char);
	wchar_t *tszTemp = NULL;
	tszTemp = new WCHAR[nLen];

	MultiByteToWideChar(CP_ACP, 0, szStr, -1, tszTemp, nLen * sizeof(WCHAR));

	strRet.Format(_T("%s"), (CString)tszTemp);
	if (tszTemp)
	{
		delete[] tszTemp;
		tszTemp = NULL;
	}
	return strRet;
}

int CXceedZipControl::StringToHex(char ch)
{
	int nNum = atoi(&ch);

	if (nNum > 0)
	{
		return nNum;
	}
	else
	{
		switch (ch)
		{
		case 'A': 	nNum = 10; break;
		case 'B': 	nNum = 11; break;
		case 'C': 	nNum = 12; break;
		case 'D': 	nNum = 13; break;
		case 'E': 	nNum = 14; break;
		case 'F': 	nNum = 15; break;
		}
	}

	return nNum;

}
