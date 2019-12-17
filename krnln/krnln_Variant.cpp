#include "stdafx.h"
#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"oleaut32.lib")

#define		DTC_COM_OBJECT  		48
#define     DTC_VARIANT             49
#define		DTP_COM_OBJECT      MAKELONG (DTC_COM_OBJECT, 1)
#define     DTP_VARIANT         MAKELONG (DTC_VARIANT, 1)

BOOL E_GetVariantElement(PMDATA_INF pArgInf,VARIANTARG * pvargDest)
{
	memcpy(pvargDest,pArgInf[0].m_pCompoundData,sizeof(VARIANTARG));
	if(V_ISARRAY(pvargDest))
	{
		SAFEARRAY* psa = NULL;
		if(V_ISBYREF(pvargDest))
			psa = *pvargDest->pparray;
		else
			psa = pvargDest->parray;

		LONG lLb,lUb;
		UINT nDim = SafeArrayGetDim(psa);
		INT nCount=1;
		for(UINT i=1;i<=nDim;i++)
		{
			SafeArrayGetLBound(psa,i,&lLb);
			SafeArrayGetUBound(psa,i,&lUb);
			nCount*=(lUb - lLb +1);
			
		}
		if(pArgInf[1].m_int > nCount)
			return FALSE;

	//long lLbound = psa->rgsabound[0].lLbound;
		
		long nIdx;//���ܰ����忪ʼ����ֵ
		if(pArgInf[1].m_dtDataType == _SDT_NULL)
		{
			nIdx = 0;

		}else{
			nIdx = pArgInf[1].m_int-1;
			if(nIdx < 0)
				nIdx = 0;		
		}

		if((VT_VARIANT & pvargDest->vt)==VT_VARIANT){
		/*char ErrorString [255];
  		wsprintf(ErrorString, "pvargDest->vt%d.  %d", pvargDest->vt,SafeArrayGetDim(psa));
			HRESULT hr = SafeArrayGetElement(psa,&nIdx,pvargDest);

  		MessageBox(0, ErrorString, "pvargDest->vt", MB_ICONERROR);*/

			VARIANTARG *pBuf = NULL; 
			HRESULT hr = SafeArrayAccessData(psa,(void **)&pBuf);
			if(FAILED(hr))
				return FALSE;
			pBuf+=nIdx;
			*pvargDest = *pBuf;
			
			SafeArrayUnaccessData (psa);
		
//			if(FAILED(hr))
//				return FALSE;
			
			if((VT_VARIANT|VT_BYREF) == pvargDest->vt){
		/*				char ErrorString [255];
  		wsprintf(ErrorString, "pvargDest->vt%d.", pvargDest->vt);
  		MessageBox(0, ErrorString, "pvargDest->vt", MB_ICONERROR);	*/

				VARIANT* pvt=pvargDest->pvarVal;
				memcpy(pvargDest,pvt,sizeof(VARIANTARG));

			}




		}else{
			/*HRESULT hr = SafeArrayGetElement(psa,&nIdx,&pvargDest->intVal);

			if(FAILED(hr))
				return FALSE;*/
			LPBYTE pBuf = NULL; 
			HRESULT hr = SafeArrayAccessData(psa,(void **)&pBuf);
			if(FAILED(hr))
				return FALSE;
			DWORD dwSize = SafeArrayGetElemsize(psa);
			pBuf+=(nIdx*dwSize);
			memcpy(&pvargDest->intVal,pBuf,dwSize);
			//pvargDest->intVal = *pBuf;

			SafeArrayUnaccessData (psa);
			pvargDest->vt = (~VT_ARRAY & pvargDest->vt);
		}
	}
	return TRUE;

}
LPOLESTR E_ASCII2Unicode(LPSTR pAsciiText)
{
	if(pAsciiText==NULL)// || IsBadReadPtr(pBStrText,8)
		return NULL;

	DWORD dwMinSize;
    dwMinSize = MultiByteToWideChar (CP_ACP, 0, pAsciiText, -1, NULL, 0);
	
    if(dwMinSize==0)
		return NULL;
    LPOLESTR lpwszStr = new USHORT [dwMinSize];
    // Convert headers from ASCII to Unicode.
    MultiByteToWideChar (CP_ACP, 0, pAsciiText, -1, lpwszStr, dwMinSize);  
	return lpwszStr;
}

LPSTR E_Unicode2ASCII(LPOLESTR pBStrText)
{
	if(pBStrText==NULL)// || IsBadReadPtr(pBStrText,8)
		return NULL;
	//��Ҫת�����ַ��� 
	DWORD dwLen=WideCharToMultiByte (CP_ACP, 0, pBStrText, -1, NULL,0, NULL, NULL) ; 
	//����ת�����ַ���
    if(dwLen==0)
		return NULL;
	LPSTR pText =(char*)E_MAlloc (dwLen);
	WideCharToMultiByte (CP_ACP, 0, pBStrText, -1, pText,dwLen, NULL, NULL);
	return pText;
}

BOOL EDataLetToVariant(VARIANTARG * pvargDest,PMDATA_INF pArgInf)
{
	VARIANTARG pArg;
	memset(&pArg,0,sizeof(VARIANTARG));
	switch(pArgInf->m_dtDataType)
	{
	case SDT_BYTE:
		pArg.vt = VT_UI1;
		pArg.intVal = pArgInf->m_int;
		break;
	case SDT_SHORT:
		pArg.vt = VT_I2;
		pArg.intVal = pArgInf->m_int;
		break;
	case SDT_INT:
		pArg.vt = VT_I4;
		pArg.intVal = pArgInf->m_int;
		break;
	case SDT_SUB_PTR:
		pArg.vt = VT_UI4;
		pArg.intVal = pArgInf->m_int;
		break;
	case SDT_INT64:
		pArg.vt = VT_I8;
		pArg.date = pArgInf->m_date;
		break;
	case SDT_FLOAT:
		pArg.vt = VT_R4;
		pArg.fltVal= pArgInf->m_float;
		break;
	case SDT_DOUBLE:
		pArg.vt = VT_R8;
		pArg.date = pArgInf->m_date;
		break;
	case SDT_BOOL:
		pArg.vt = VT_BOOL;
		pArg.boolVal = pArgInf->m_bool?-1:0;
		break;
	case SDT_DATE_TIME:
		pArg.vt = VT_DATE;
		pArg.date = pArgInf->m_date;
		break;
	case SDT_TEXT:
		{
			pArg.vt = VT_BSTR;
			LPOLESTR lpsz = E_ASCII2Unicode(pArgInf->m_pText);
			pArg.bstrVal = ::SysAllocString(lpsz);
			delete [] lpsz;
		}
		break;
	
	case DTP_VARIANT:
		if(FAILED(VariantCopy(&pArg,(VARIANTARG *)pArgInf->m_pCompoundData)))
			return FALSE;
		break;
	case DTP_COM_OBJECT:
		{
			pArg.vt = VT_UNKNOWN;//��VT_DISPATCH�����
			PEYDISPATCH pDest = (PEYDISPATCH)pArgInf->m_pCompoundData;
			pArg.pdispVal = pDest->pDisp;
			if(pArg.pdispVal)
				pArg.pdispVal->AddRef();
		}
		break;
	default:
		return FALSE;
		break;
	}

	VariantClear(pvargDest);
	memcpy(pvargDest,&pArg,sizeof(VARIANTARG));

	return TRUE;

}

BOOL EAryDataToVariant(VARIANTARG * pvargDest,PMDATA_INF pArgInf)
{
	INT nDataType = pArgInf->m_dtDataType;
	INT nVtype,nDataSize;

	DWORD dwSize=0;
	void* pData = GetAryElementInf(pArgInf->m_pAryData,dwSize);
	if(pData==NULL || dwSize==0)
		return FALSE;

	if(nDataType == SDT_BIN)
	{
		nVtype =  VT_UI1;
		nDataSize = sizeof (BYTE);

	}else{

		nDataType = ~DT_IS_ARY & nDataType;
		switch(nDataType)
		{
		case SDT_BYTE:
			nVtype = VT_UI1;
			nDataSize = sizeof (BYTE);
			break;
		case SDT_SHORT:
			nVtype = VT_I2;
			nDataSize = sizeof (SHORT);
			break;
		case SDT_INT:
			nVtype = VT_I4;
			nDataSize = sizeof (INT);
			break;
		case SDT_SUB_PTR:
			nVtype = VT_UI4;
			nDataSize = sizeof (DWORD);
			break;
		case SDT_INT64:
			nVtype = VT_I8;
			nDataSize = sizeof (INT64);
			break;
		case SDT_FLOAT:
			nVtype = VT_R4;
			nDataSize = sizeof (FLOAT);
			break;
		case SDT_DOUBLE:
			nVtype = VT_R8;
			nDataSize = sizeof (DOUBLE);
			break;
		case SDT_BOOL:
			nVtype = VT_BOOL;
			nDataSize = sizeof (BOOL);
			break;
		case SDT_DATE_TIME:
			nVtype = VT_DATE;
			nDataSize = sizeof (DATE);
			break;
		case SDT_TEXT:
			nVtype = VT_BSTR;
			nDataSize = sizeof (DWORD);
			break;
		default:
			return FALSE;
			break;
		}
	}

	SAFEARRAY* pArray=NULL;
	HRESULT hr=SafeArrayAllocDescriptor(1,&pArray);//����SAFEARRAY�ṹ�Ķ���
	if(FAILED(hr))
		return FALSE;
	pArray->cbElements=nDataSize;
	pArray->rgsabound[0].cElements=dwSize;
	pArray->rgsabound[0].lLbound=0;
	SafeArrayAllocData(pArray);
	void * pDest =NULL;
	hr = SafeArrayAccessData(pArray,(void**)&pDest);
	if(FAILED(hr))
	{
		SafeArrayDestroy(pArray);
		return FALSE;
	}

	if(nVtype == VT_BSTR)
	{
		LPSTR* pArySrc = (LPSTR*)pData;
		LPOLESTR* pAryDest = (LPOLESTR*)pDest;
			
					
		for(INT i=0;i<(INT)dwSize;i++)
		{
			LPOLESTR lpsz = E_ASCII2Unicode(pArySrc[i]);
			pAryDest[i] = ::SysAllocString(lpsz);
			delete [] lpsz;
		}

	}else if(nVtype == VT_BOOL){
		LPINT pArySrc = (LPINT)pData;
		LPINT pAryDest = (LPINT)pDest;
		for(INT i=0;i<(INT)dwSize;i++)
		{
			if(pArySrc[i])
				pAryDest[i] = -1;
			else
				pAryDest[i] = 0;
		}

	}else{
		memcpy(pDest,pData,dwSize*nDataSize);
	}
	SafeArrayUnaccessData(pArray);
	VariantClear(pvargDest);
	pvargDest->vt = nVtype | VT_ARRAY;
	pvargDest->parray = pArray;
	return TRUE;

}
extern "C" 
{
	/*
	���Ʊ�����
	
	*/
	void _cdecl krnln_VariantCopy (INT nArgCount,MDATA_INF ArgInf,...)
	{
		PMDATA_INF pArgInf = &ArgInf;
		VARIANTARG * pvargDest = (VARIANTARG *)pArgInf[0].m_pCompoundData;
		if(pvargDest==NULL)return;
		VariantClear(pvargDest);
		VARIANTARG * pvargSrc = (VARIANTARG *)pArgInf[1].m_pCompoundData;
		if(pvargSrc)
			VariantCopy(pvargDest,pvargSrc);
	}

	/*
    ���ø�ʽ�� ���޷���ֵ�� ������� ���� - ϵͳ����֧�ֿ�->������
    Ӣ�����ƣ�Clear
    ��������������ͷŲ���ա���������ñ���������������˳�����������ʱ���Զ����ͷš����磺�������������ӳ���ֲ������У����ӳ�������˳�ʱ���ö���ᱻ�Զ��ͷš�������Ϊ���������Ա���
	
	*/
	void _cdecl krnln_VariantClear (INT nArgCount,MDATA_INF ArgInf,...)
	{
		VARIANTARG * pvargDest = (VARIANTARG *)ArgInf.m_pCompoundData;
		VariantClear(pvargDest);
		VariantInit(pvargDest);

	}

	/*
    ���ø�ʽ�� ���������͡� ����ȡ���� ���� - ϵͳ����֧�ֿ�->������
    Ӣ�����ƣ�GetType
    ȡ�ص�ǰ�����Ͷ�����������͡�������Ϊ���������Ա���
    �����������ƣ���������    Ӣ�����ƣ�VariantType
    ����������Ϊö�ٳ����������ͣ������� 15 ��ö�ٳ���ֵ��
    ����ϵͳ���� Windows
    �ṩ�����������ܹ������������͵�ö��ֵ��
    ö�ٳ���ֵ<1>����������Ϊ��δ֪����Ӣ������Ϊ��Unknown����ֵΪ-1��
    ö�ٳ���ֵ<2>����������Ϊ���ա���Ӣ������Ϊ��Empty����ֵΪ0��
    ö�ٳ���ֵ<3>����������Ϊ����ֵ�͡���Ӣ������Ϊ��Number����ֵΪ1��
    ö�ٳ���ֵ<4>����������Ϊ���ı��͡���Ӣ������Ϊ��Text����ֵΪ2��
    ö�ٳ���ֵ<5>����������Ϊ���߼��͡���Ӣ������Ϊ��Bool����ֵΪ3��
    ö�ٳ���ֵ<6>����������Ϊ�������͡���Ӣ������Ϊ��Date����ֵΪ4��
    ö�ٳ���ֵ<7>����������Ϊ�������͡���Ӣ������Ϊ��Object����ֵΪ5��
    ö�ٳ���ֵ<8>����������Ϊ������ֵ�͡���Ӣ������Ϊ��Error����ֵΪ6��
    ö�ٳ���ֵ<9>����������Ϊ����ֵ�����顱��Ӣ������Ϊ��NumberArray����ֵΪ7��
    ö�ٳ���ֵ<10>����������Ϊ���ı������顱��Ӣ������Ϊ��TextArray����ֵΪ8��
    ö�ٳ���ֵ<11>����������Ϊ���߼������顱��Ӣ������Ϊ��BoolArray����ֵΪ9��
    ö�ٳ���ֵ<12>����������Ϊ�����������顱��Ӣ������Ϊ��DateArray����ֵΪ10��
    ö�ٳ���ֵ<13>����������Ϊ�����������顱��Ӣ������Ϊ��ObjectArray����ֵΪ11��
    ö�ٳ���ֵ<14>����������Ϊ������ֵ�����顱��Ӣ������Ϊ��ErrorArray����ֵΪ12��
    ö�ٳ���ֵ<15>����������Ϊ�����������顱��Ӣ������Ϊ��VariantArray����ֵΪ13��	
	*/
	int _cdecl krnln_VariantGetType (INT nArgCount,MDATA_INF ArgInf,...)
	{
		VARIANTARG * pvargDest = (VARIANTARG *)ArgInf.m_pCompoundData;
		VARTYPE vt = pvargDest->vt;
		BOOL bIsArray = FALSE;
		if(vt & VT_ARRAY)
		{
			vt &=(~VT_ARRAY);//ȥ�������־
			bIsArray = TRUE;
		}
		int nType = -1;
		switch(vt)
		{
		case VT_UI1:
		case VT_UI2:
		case VT_UI4:
		case VT_UI8:
		case VT_I1:
		case VT_I2:
		case VT_I4:
		case VT_I8:
		case VT_R4:
		case VT_R8:
		case VT_INT:
		case VT_UINT:
		case VT_CY:
		case VT_DECIMAL:
			nType = 1;
			break;
		case VT_BSTR:
			nType = 2;
			break;
		case VT_BOOL:
			nType = 3;
			break;
		case VT_DATE:
			nType = 4;
			break;
		case VT_DISPATCH://�����Ƿ��д�ַ��־?
			nType = 5;
			break;
		case VT_ERROR:
			nType = 6;
			break;
		case VT_EMPTY:
		case VT_NULL:
			nType = 0;
			break;			
		}
		if(bIsArray)
		{
			if(nType==-1 && vt==VT_VARIANT)
				nType = 13;
			else if(1 <= nType && nType <=6)
				nType +=6;
		}

		return nType;
	}

	/*
    ���ø�ʽ�� �������͡� ����ȡ�����Ա�� ���� - ϵͳ����֧�ֿ�->������
    Ӣ�����ƣ�GetElementCount
    ����������д�ŵ����������ݣ�ִ�б��������������Ա��Ŀ����������������ݣ�ִ�б����������� -1 ��������Ϊ���������Ա���

	
	*/
	int _cdecl krnln_VariantGetElementCount (INT nArgCount,MDATA_INF ArgInf,...)
	{
		VARIANTARG * pvargDest = (VARIANTARG *)ArgInf.m_pCompoundData;
		if(V_ISARRAY(pvargDest))
		{
			SAFEARRAY* psa = NULL;
			if(V_ISBYREF(pvargDest))
				psa = *pvargDest->pparray;
			else
				psa = pvargDest->parray;
			LONG lLb,lUb;
			UINT nDim = SafeArrayGetDim(psa);
			INT nCount=1;
			for(UINT i=1;i<=nDim;i++)
			{
				SafeArrayGetLBound(psa,i,&lLb);
				SafeArrayGetUBound(psa,i,&lUb);
				nCount*=(lUb - lLb +1);

			}
			return nCount;
		}
		return -1;
	}

	/*
    ���ø�ʽ�� ���ı��͡� ����ȡ�ı� ���������� ��Ա�����ݣ� - ϵͳ����֧�ֿ�->������
    Ӣ�����ƣ�GetText
    ���ر������л򱾶��������Ա�е��ı����ݣ������ǰ���ݵ��������Ͳ�Ϊ�ı��ͣ����Զ�����ת�������ת��ʧ�ܽ����ؿ��ı���������Ϊ���������Ա���
    ����<1>������Ϊ����Ա������������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������ǰ������Ϊ���������ݣ������������ڵ�ĳ����Ա���в�����������ڴ˲�����ָ������������ֵ��������ֵ�� 1 ��ʼ��������������⣬��ʡ�Ա�������

	
	*/
	char* _cdecl krnln_VariantGetText (INT nArgCount,MDATA_INF ArgInf,...)
	{
		VARIANTARG vargSrc;
		if(E_GetVariantElement(&ArgInf,&vargSrc)==FALSE)
			return NULL;

		LPSTR pText = NULL;
		if(vargSrc.vt == VT_BOOL)
		{
			if(vargSrc.boolVal != 0)
				pText = CloneTextData("��",2);
			else
				pText = CloneTextData("��",2);
			return pText;
		}
		BOOL bIsFromChg = FALSE;
		if(vargSrc.vt != VT_BSTR)
		{
			VARIANTARG vargDest;
			memcpy(&vargDest,&vargSrc,sizeof(VARIANTARG));
			memset(&vargSrc,0,sizeof(VARIANTARG));
			HRESULT hr = VariantChangeType(&vargSrc,&vargDest,0,VT_BSTR);
			if(FAILED(hr))
				return NULL;
			bIsFromChg = TRUE;
		}
		pText = E_Unicode2ASCII(vargSrc.bstrVal);
		if(bIsFromChg)
			VariantClear(&vargSrc);
		return pText;
	}

	/*
    ���ø�ʽ�� ��˫����С���͡� ����ȡ��ֵ ���������� ��Ա�����ݣ� - ϵͳ����֧�ֿ�->������
    Ӣ�����ƣ�GetNum
    ���ر������л򱾶��������Ա�е���ֵ���ݣ������ǰ���ݵ��������Ͳ�Ϊ��ֵ�����ֵ�ͣ����Զ�����ת�������ת��ʧ�ܽ����� 0 ��������Ϊ���������Ա���
    ����<1>������Ϊ����Ա������������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������ǰ������Ϊ���������ݣ������������ڵ�ĳ����Ա���в�����������ڴ˲�����ָ������������ֵ��������ֵ�� 1 ��ʼ��������������⣬��ʡ�Ա�������	
	*/
	void _cdecl krnln_VariantGetNum (INT nArgCount,MDATA_INF ArgInf,...)
	{
		VARIANTARG vargSrc;
		MDATA_INF RetVal;
		if(E_GetVariantElement(&ArgInf,&vargSrc))
		{
			if(vargSrc.vt != VT_R8)
			{
				VARIANTARG vargDest;
				memcpy(&vargDest,&vargSrc,sizeof(VARIANTARG));
				memset(&vargSrc,0,sizeof(VARIANTARG));
				VariantChangeType(&vargSrc,&vargDest,0,VT_R8);
			}
			RetVal.m_double = vargSrc.dblVal;
		}
		else
			RetVal.m_double = 0;
		__asm
		{
			mov eax,RetVal.m_unit.m_dwFormID;
			mov edx,RetVal.m_unit.m_dwUnitID;
		}
	}

	/*
    ���ø�ʽ�� ���߼��͡� ����ȡ�߼�ֵ ���������� ��Ա�����ݣ� - ϵͳ����֧�ֿ�->������
    Ӣ�����ƣ�GetBool
    ���ر������л򱾶��������Ա�е��߼�ֵ���ݣ������ǰ���ݵ��������Ͳ�Ϊ�߼��ͣ����Զ�����ת�������ת��ʧ�ܽ����ؼ١�������Ϊ���������Ա���
    ����<1>������Ϊ����Ա������������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������ǰ������Ϊ���������ݣ������������ڵ�ĳ����Ա���в�����������ڴ˲�����ָ������������ֵ��������ֵ�� 1 ��ʼ��������������⣬��ʡ�Ա�������
	*/
	BOOL _cdecl krnln_VariantGetBool (INT nArgCount,MDATA_INF ArgInf,...)
	{
		VARIANTARG vargSrc;
		BOOL bRet = FALSE;

		if(E_GetVariantElement(&ArgInf,&vargSrc))
		{
			if(vargSrc.vt != VT_BOOL)
			{
				VARIANTARG vargDest;
				memcpy(&vargDest,&vargSrc,sizeof(VARIANTARG));
				memset(&vargSrc,0,sizeof(VARIANTARG));
				HRESULT hr = VariantChangeType(&vargSrc,&vargDest,0,VT_BSTR);
				if(FAILED(hr))
					return bRet;
			}
			bRet = (vargSrc.boolVal !=0 ?1:0);
		}
		return bRet;

	}
	/*
    ���ø�ʽ�� ������ʱ���͡� ����ȡ���� ���������� ��Ա�����ݣ� - ϵͳ����֧�ֿ�->������
    Ӣ�����ƣ�GetDateTime
    ���ر������л򱾶��������Ա�е�����ʱ��ֵ���ݣ������ǰ���ݵ��������Ͳ�Ϊ����ʱ���ͣ����Զ�����ת�������ת��ʧ�ܽ�����100��1��1�ա�������Ϊ���������Ա���
    ����<1>������Ϊ����Ա������������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������ǰ������Ϊ���������ݣ������������ڵ�ĳ����Ա���в�����������ڴ˲�����ָ������������ֵ��������ֵ�� 1 ��ʼ��������������⣬��ʡ�Ա�������
	*/
	void _cdecl krnln_VariantGetDateTime (INT nArgCount,MDATA_INF ArgInf,...)
	{
		VARIANTARG vargSrc;
		MDATA_INF RetVal;
		if(E_GetVariantElement(&ArgInf,&vargSrc))
		{
			if(vargSrc.vt != VT_DATE)
			{
				VARIANTARG vargDest;
				memcpy(&vargDest,&vargSrc,sizeof(VARIANTARG));
				memset(&vargSrc,0,sizeof(VARIANTARG));
				HRESULT hr = VariantChangeType(&vargSrc,&vargDest,0,VT_DATE);
				if(FAILED(hr))
					vargSrc.date = -657434;//100��1��1��;
			}
			RetVal.m_date = vargSrc.date;
		}
		else
			RetVal.m_date = -657434;//100��1��1��;
		__asm
		{
			mov eax,RetVal.m_unit.m_dwFormID;
			mov edx,RetVal.m_unit.m_dwUnitID;
		}
	}
	/*
    ���ø�ʽ�� ������ ����ȡ���� ���������� ��Ա�����ݣ� - ϵͳ����֧�ֿ�->������
    Ӣ�����ƣ�GetObject
    ���ر������л򱾶��������Ա�е�COM���������ݣ������ǰ���ݵ��������Ͳ�ΪCOM�����ͣ������ؿ�COM���󡣱�����Ϊ���������Ա���
    ����<1>������Ϊ����Ա������������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������ǰ������Ϊ���������ݣ������������ڵ�ĳ����Ա���в�����������ڴ˲�����ָ������������ֵ��������ֵ�� 1 ��ʼ��������������⣬��ʡ�Ա�������
	*/
	void* _cdecl krnln_VariantGetObject (INT nArgCount,MDATA_INF ArgInf,...)
	{
		VARIANTARG vargSrc;
		PEYDISPATCH pdispRet = (PEYDISPATCH)E_MAlloc(sizeof(EYDISPATCH));

		if(E_GetVariantElement(&ArgInf,&vargSrc))
		{
			switch (vargSrc.vt)
			{
			case VT_DISPATCH:
				pdispRet->pDisp = vargSrc.pdispVal;
				if(pdispRet->pDisp)
					pdispRet->pDisp->AddRef();
				break;
			case VT_UNKNOWN:
				pdispRet->pDisp = (LPDISPATCH)vargSrc.punkVal;
				if(pdispRet->pDisp)
					pdispRet->pDisp->AddRef();
				break;
			case VT_DISPATCH|VT_BYREF:
				pdispRet->pDisp = *vargSrc.ppdispVal;
				if(pdispRet->pDisp)
					pdispRet->pDisp->AddRef();
				break;
			case VT_UNKNOWN|VT_BYREF:
				pdispRet->pDisp = *(LPDISPATCH*)vargSrc.ppunkVal;
				if(pdispRet->pDisp)
					pdispRet->pDisp->AddRef();
				break;
			}
		}
		return pdispRet;

	}

	/*
    ���ø�ʽ�� �������͡� ����ȡ������ ���������� ��Ա�����ݣ� - ϵͳ����֧�ֿ�->������
    Ӣ�����ƣ�GetVariant
    ���ر������л򱾶��������Ա�еı����������������ݣ������ǰ���ݵ��������Ͳ�Ϊ�����ͣ����Զ�����ת����������Ϊ���������Ա���
    ����<1>������Ϊ����Ա������������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������ǰ������Ϊ���������ݣ������������ڵ�ĳ����Ա���в�����������ڴ˲�����ָ������������ֵ��������ֵ�� 1 ��ʼ��������������⣬��ʡ�Ա�������
	*/
	void* _cdecl krnln_VariantGetVariant (INT nArgCount,MDATA_INF ArgInf,...)
	{
		VARIANTARG vargSrc;
		VARIANT* pVarRet = (VARIANT*)E_MAlloc(sizeof(VARIANT));

		if(E_GetVariantElement(&ArgInf,&vargSrc))
			VariantCopy(pVarRet,&vargSrc);
		return pVarRet;

	}
	/*
    ���ø�ʽ�� ���߼��͡� ���󣮸�ֵ ����ͨ��������/������ ��д�����ݣݣ��������� ��Ա�����ݣ� - ϵͳ����֧�ֿ�->������
    Ӣ�����ƣ�set
    ���ñ���������ݣ��ɹ������棬ʧ�ܷ��ؼ١�������Ϊ���������Ա���
    ����<1>������Ϊ����д�����ݡ�������Ϊ��ͨ���ͣ�all���������Ա�ʡ�ԣ��ṩ��������ʱ����ͬʱ�ṩ�������������ݡ�����ֵ����Ϊ�ı�����ֵ���߼�ֵ������ʱ��ֵ��COM�������������ͻ�����Щ�������ͼ��������͡��������ͱ����������ʽ�������������ʡ�ԣ��򽫶�����ա�
    ����<2>������Ϊ����Ա������������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������ǰ������Ϊ���������ݣ������������ڵ�ĳ����Ա���в�����������ڴ˲�����ָ������������ֵ��������ֵ�� 1 ��ʼ��������������⣬��ʡ�Ա�������
	*/
	BOOL _cdecl krnln_Variantset (INT nArgCount,MDATA_INF ArgInf,...)
	{
		PMDATA_INF pArgInf = &ArgInf;
		VARIANTARG * pvargDest = (VARIANTARG *)pArgInf[0].m_pCompoundData;
		if(pArgInf[1].m_dtDataType == _SDT_NULL)
		{
			VariantClear(pvargDest);
			VariantInit(pvargDest);
			return TRUE;
		}


		BOOL bRet;

		if((pArgInf[1].m_dtDataType & DT_IS_ARY) == DT_IS_ARY || pArgInf[1].m_dtDataType == SDT_BIN)
			bRet = EAryDataToVariant(pvargDest,&pArgInf[1]);
		else
		{
			if(V_ISARRAY(pvargDest))
			{
				SAFEARRAY* psa = pvargDest->parray;
				LONG lLb,lUb;
				UINT nDim = SafeArrayGetDim(psa);
				INT nCount=1;
				for(UINT i=1;i<=nDim;i++)
				{
					SafeArrayGetLBound(psa,i,&lLb);
					SafeArrayGetUBound(psa,i,&lUb);
					nCount*=(lUb - lLb +1);
					
				}
				if(pArgInf[2].m_int > nCount)
					return FALSE;

				VARIANTARG vargSrc;
				VariantInit(&vargSrc);
				
				if(EDataLetToVariant(&vargSrc,&pArgInf[1])==FALSE)
					return FALSE;
				


				//long lLbound = //psa->rgsabound[0].lLbound;
				long nIdx;//���ܰ����忪ʼ����ֵ
				if(pArgInf[2].m_dtDataType == _SDT_NULL)
				{
					nIdx = 0;//lLbound;
					
				}else{
					nIdx = pArgInf[2].m_int-1;//+lLbound;
					if(nIdx < 0)
						nIdx = 0;//lLbound;
				}
				INT nVarType = ~VT_ARRAY & pvargDest->vt;
		
				HRESULT hr;


				if((VT_VARIANT & nVarType)==VT_VARIANT){
					//hr = SafeArrayPutElement(psa,&nIdx,&vargSrc);
					VARIANTARG *pBuf = NULL; 
					HRESULT hr = SafeArrayAccessData(psa,(void **)&pBuf);
					if(!FAILED(hr)){
						pBuf+=nIdx;
						VariantClear(pBuf);
						*pBuf=vargSrc;
					
						SafeArrayUnaccessData (psa);
					}
				}else{
					if(nVarType != vargSrc.vt)
					{
						VARIANTARG vargDest;
						memcpy(&vargDest,&vargSrc,sizeof(VARIANTARG));
						memset(&vargSrc,0,sizeof(VARIANTARG));
						hr = VariantChangeType(&vargSrc,&vargDest,0,nVarType);
						if(FAILED(hr))
						{
							VariantClear(&vargDest);
							return FALSE;
						}
					}
					//hr = SafeArrayPutElement(psa,&nIdx,&vargSrc.intVal);
					LPBYTE pBuf = NULL;
					HRESULT hr = SafeArrayAccessData(psa,(void **)&pBuf);
					if(!FAILED(hr)){
						DWORD dwSize = SafeArrayGetElemsize(psa);
						pBuf+=(nIdx*dwSize);
						if(nVarType==VT_BSTR)
							::SysFreeString (*(BSTR*)pBuf);
						memcpy(pBuf,&vargSrc.intVal,dwSize);
					
						SafeArrayUnaccessData (psa);
					}
				}

				if(FAILED(hr))
				{
					VariantClear(&vargSrc);
					return FALSE;
				}
				
				return TRUE;
				
			}else
				bRet = EDataLetToVariant(pvargDest,&pArgInf[1]);
		}

		return bRet;
	}
	/*
    ���ø�ʽ�� ���߼��͡� ���󣮴������� �������� ��Ա���ͣ������� ��Ա��Ŀ�� - ϵͳ����֧�ֿ�->������
    Ӣ�����ƣ�CreateArray
    ����ָ�����ͺ�ָ����Ա���Ŀհ����飬�����е�ԭ�����ݽ�����գ��ɹ������棬ʧ�ܷ��ؼ١�������Ϊ���������Ա���
    ����<1>������Ϊ����Ա���͡�������Ϊ�������ͣ�int������ָ�������������Ա���������ͣ�Ϊ������ֵ֮һ��
	1: �ֽ��ͣ� 2: �������ͣ� 3: �����ͣ� 4: С���ͣ� 5: ˫����С���ͣ� 6: �ı��ͣ� 7: �߼��ͣ� 8: �����ͣ� 9: �����ͣ� 10: �����͡�
    ����<2>������Ϊ����Ա��Ŀ��������Ϊ�������ͣ�int������ָ�������������Ա����Ŀ��
	*/
	BOOL _cdecl krnln_VariantCreateArray (INT nArgCount,MDATA_INF ArgInf,...)
	{
		PMDATA_INF pArgInf = &ArgInf;
		VARIANTARG * pvargDest = (VARIANTARG *)pArgInf[0].m_pCompoundData;
		VariantClear(pvargDest);
		VariantInit(pvargDest);

		INT nDataType = pArgInf[1].m_int;
		INT nDataSize,nVtype;
		switch(nDataType)
		{
		case 1://�ֽ���
			nVtype = VT_UI1;
			nDataSize = sizeof (BYTE);
			break;
		case 2://��������
			nVtype = VT_I2;
			nDataSize = sizeof (SHORT);
			break;
		case 3://������
			nVtype = VT_I4;
			nDataSize = sizeof (INT);
			break;
		case 4://С����
			nVtype = VT_R4;
			nDataSize = sizeof (FLOAT);
			break;
		case 5://˫����С����
			nVtype = VT_R8;
			nDataSize = sizeof (DOUBLE);
			break;
		case 7://�߼���
			nVtype = VT_BOOL;
			nDataSize = sizeof (BOOL);
			break;
		case 8://������
			nVtype = VT_DATE;
			nDataSize = sizeof (DATE);
			break;
		case 6://�ı���
			nVtype = VT_BSTR;
			nDataSize = sizeof (DWORD);
			break;
		case 9://������
			nVtype = VT_DISPATCH;
			nDataSize = sizeof (DWORD);
			break;
		case 10://������
			nVtype = VT_VARIANT;
			nDataSize = sizeof (VARIANT);
			break;
		default:
			return FALSE;
			break;
		}

		

		SAFEARRAY* pArray=NULL;
		HRESULT hr=SafeArrayAllocDescriptor(1,&pArray);//����SAFEARRAY�ṹ�Ķ���
		if(FAILED(hr))
			return FALSE;
		pArray->cbElements=nDataSize;
		pArray->rgsabound[0].cElements=pArgInf[2].m_int;
		pArray->rgsabound[0].lLbound=0;
		hr = SafeArrayAllocData(pArray);
		if(FAILED(hr))
		{
			SafeArrayDestroyDescriptor(pArray);
			return FALSE;
		}
		
		pvargDest->vt = nVtype | VT_ARRAY;
		pvargDest->parray = pArray;
		return TRUE;

	}
	/*
    ���ø�ʽ�� ���߼��͡� ���������� ���������� �����õ����ͣ� - ϵͳ����֧�ֿ�->������
    Ӣ�����ƣ�SetType
    �����ǰ�����Ͷ����е�ԭ�����ݣ����ı������������ͣ��ɹ������棬ʧ�ܷ��ؼ١�������Ϊ���������Ա���
    ����<1>������Ϊ�������õ����͡�������Ϊ���������ͣ�VariantType����������ֵ�ṩ�����õı������͡�
    ö�ٳ���ֵ<2>����������Ϊ���ա���Ӣ������Ϊ��Empty����ֵΪ0��
    ö�ٳ���ֵ<3>����������Ϊ����ֵ�͡���Ӣ������Ϊ��Number����ֵΪ1��
    ö�ٳ���ֵ<4>����������Ϊ���ı��͡���Ӣ������Ϊ��Text����ֵΪ2��
    ö�ٳ���ֵ<5>����������Ϊ���߼��͡���Ӣ������Ϊ��Bool����ֵΪ3��
    ö�ٳ���ֵ<6>����������Ϊ�������͡���Ӣ������Ϊ��Date����ֵΪ4��
    ö�ٳ���ֵ<7>����������Ϊ�������͡���Ӣ������Ϊ��Object����ֵΪ5��
    ö�ٳ���ֵ<8>����������Ϊ������ֵ�͡���Ӣ������Ϊ��Error����ֵΪ6��
    ö�ٳ���ֵ<9>����������Ϊ����ֵ�����顱��Ӣ������Ϊ��NumberArray����ֵΪ7��
    ö�ٳ���ֵ<10>����������Ϊ���ı������顱��Ӣ������Ϊ��TextArray����ֵΪ8��
    ö�ٳ���ֵ<11>����������Ϊ���߼������顱��Ӣ������Ϊ��BoolArray����ֵΪ9��
    ö�ٳ���ֵ<12>����������Ϊ�����������顱��Ӣ������Ϊ��DateArray����ֵΪ10��
    ö�ٳ���ֵ<13>����������Ϊ�����������顱��Ӣ������Ϊ��ObjectArray����ֵΪ11��
    ö�ٳ���ֵ<14>����������Ϊ������ֵ�����顱��Ӣ������Ϊ��ErrorArray����ֵΪ12��
    ö�ٳ���ֵ<15>����������Ϊ�����������顱��Ӣ������Ϊ��VariantArray����ֵΪ13��	
	*/
	BOOL _cdecl krnln_VariantSetType (INT nArgCount,MDATA_INF ArgInf,...)
	{
		PMDATA_INF pArgInf = &ArgInf;
		VARIANTARG * pvargDest = (VARIANTARG *)pArgInf[0].m_pCompoundData;
	

		INT nVtype;
		switch(pArgInf[1].m_int)
		{
		case 0:
			nVtype = VT_EMPTY;
			break;
		case 1:
			nVtype = VT_R8;
			break;
		case 2:
			nVtype = VT_BSTR;
			break;
		case 3:
			nVtype = VT_BOOL;
			break;
		case 4:
			nVtype = VT_DATE;
			break;
		case 5:
			nVtype = VT_DISPATCH;
			break;
		case 6:
			nVtype = VT_ERROR;
			break;
		case 7:
			nVtype = VT_R8|VT_ARRAY;
			break;
		case 8:
			nVtype = VT_BSTR|VT_ARRAY;
			break;
		case 9:
			nVtype = VT_BOOL|VT_ARRAY;
			break;
		case 10:
			nVtype = VT_DATE|VT_ARRAY;
			break;
		case 11:
			nVtype = VT_DISPATCH|VT_ARRAY;
			break;
		case 12:
			nVtype = VT_ERROR|VT_ARRAY;
			break;
		case 13:
			nVtype = VT_VARIANT|VT_ARRAY;
			break;
		default:
			VariantClear(pvargDest);
			VariantInit(pvargDest);
			return FALSE;
			break;
		}
		if(nVtype == VT_EMPTY)
		{
			VariantClear(pvargDest);
			VariantInit(pvargDest);
		}
		else
		{
			VARIANTARG vargDest;
			memset(&vargDest,0,sizeof(VARIANTARG));
			HRESULT hr = VariantChangeType(&vargDest,pvargDest,0,nVtype);
			VariantClear(pvargDest);
			if(FAILED(hr))
			{
				VariantInit(pvargDest);
				return FALSE;
			}
			memcpy(pvargDest,&vargDest,sizeof(VARIANTARG));


		}
		return TRUE;
	
	}
	/*
    ���ø�ʽ�� ���ֽڼ��� ����ȡ�ֽڼ� ���������� ��Ա�����ݣ� - ϵͳ����֧�ֿ�->������
    Ӣ�����ƣ�GetBin
    ���ر������л򱾶��������Ա�е��ֽڼ����ݣ������ǰ���ݵ��������Ͳ�Ϊ�ֽڼ��ͣ����Զ�����ת�������ת��ʧ�ܽ����ؿ��ֽڼ���������Ϊ���������Ա���
    ����<1>������Ϊ����Ա������������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������ǰ������Ϊ���������ݣ������������ڵ�ĳ����Ա���в�����������ڴ˲�����ָ������������ֵ��������ֵ�� 1 ��ʼ��������������⣬��ʡ�Ա�������
	*/
	void* _cdecl krnln_VariantGetBin (INT nArgCount,MDATA_INF ArgInf,...)
	{
		
		LPBYTE pData = NULL;
		VARIANTARG vargSrc;
		BOOL bIsFromChg = FALSE;
		PMDATA_INF pArgInf = &ArgInf;
		SAFEARRAY* psa;
		VARIANTARG * pvargDest = (VARIANTARG *)pArgInf[0].m_pCompoundData;
		if(pvargDest->vt != (VT_ARRAY | VT_UI1) && pvargDest->vt != (VT_ARRAY | VT_I1))
		{
			
			if(E_GetVariantElement(&ArgInf,&vargSrc)==FALSE)
				return pData;
			VARIANTARG vargDest;
			memcpy(&vargDest,&vargSrc,sizeof(VARIANTARG));
			memset(&vargSrc,0,sizeof(VARIANTARG));
			HRESULT hr = VariantChangeType(&vargSrc,&vargDest,0,VT_ARRAY | VT_UI1);
			if(FAILED(hr))
				return pData;
			psa = vargSrc.parray;
			bIsFromChg = TRUE;

		}else
			psa = pvargDest->parray;

		LONG lLb,lUb;
		UINT nDim = SafeArrayGetDim(psa);
		INT nCount=1;
		for(UINT i=1;i<=nDim;i++)
		{
			SafeArrayGetLBound(psa,i,&lLb);
			SafeArrayGetUBound(psa,i,&lUb);
			nCount*=(lUb - lLb +1);
			
		}
		BYTE *pBuf = NULL; 
		SafeArrayAccessData(psa,(void **)&pBuf);
		pData = CloneBinData (pBuf, nCount);
		SafeArrayUnaccessData (psa);
		if(bIsFromChg)
			VariantClear(&vargSrc);
		return pData;

	}
}