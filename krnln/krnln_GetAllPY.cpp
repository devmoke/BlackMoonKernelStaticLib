#include <StdAfx.h>
#include "mem.h"
#include "Myfunctions.h"

extern char * FindPY(BYTE a1);
extern WORD s_wPYTab [];
extern WORD s_wManyPYTab [];
//ƴ������ - ȡ���з���
/*
���ø�ʽ�� ���ı������页 ȡ���з��� ���ı��� ��ȡ��ƴ���ĺ��֣� - ϵͳ����֧�ֿ�->ƴ������
Ӣ�����ƣ�GetAllPY
���ذ���ָ����������ƴ��������ı����飨֧�ֶ����֣���Ŀǰ��֧�ֹ��꺺�֡����ص������������á��������顱����浽ͬ�������������������Ϊ�������
����<1>������Ϊ����ȡ��ƴ���ĺ��֡�������Ϊ���ı��ͣ�text������ֻȡ���ı��ײ��ĵ�һ�����֣�������ı��ײ���Ϊ���꺺�֣��������һ����Ա��ĿΪ 0 �Ŀ��ı����顣
*/
LIBAPI(LPBYTE, krnln_GetAllPY)
{
	const char *v3; // edx@1
	char v4; // al@3
	WORD v5; // bx@7
	signed int v6; // ecx@10
	char *v7; // edi@10
	char v8; // zf@12
	signed int v9; // ecx@14
	signed int v10; // ecx@14
	unsigned int v11; // ebp@14
	char *v12; // edi@14
	const void *v13; // esi@14
	char v14; // zf@16
	__int16 v15; // bx@19
	signed int v16; // ecx@20
	char *v17; // edi@20
	char v18; // zf@22
	signed int v19; // ecx@24
	signed int v20; // ecx@24
	unsigned int v21; // ebx@24
	char *v22; // edi@24
	const void *v23; // esi@24
	char v24; // zf@26
	char *v25; // eax@29
	int v26; // eax@30
	int v27; // ebx@30
	signed int v28; // ebp@30
	unsigned __int16 v29; // bx@31
	signed int v30; // ecx@33
	char *v31; // edi@33
	char v32; // zf@35
	unsigned int v33; // edx@37
	signed int v34; // ecx@37
	signed int v35; // ecx@37
	char *v36; // edi@37
	const void *v37; // esi@37
	char v38; // zf@39
	__int16 v39; // bx@42
	signed int v40; // ecx@43
	char *v41; // edi@43
	char v42; // zf@45
	signed int v43; // ecx@47
	signed int v44; // ecx@47
	unsigned int v45; // ebx@47
	char *v46; // edi@47
	const void *v47; // esi@47
	char v48; // zf@49
	char *v49; // eax@52
	//unsigned int v51; // edi@53
	//int v52; // eax@53
	char *v53; // [sp+10h] [bp-80h]@30
	CMyDWordArray v54; // [sp+18h] [bp-78h]@1
    //unsigned int v56; // [sp+28h] [bp-68h]@53
	char v57; // [sp+2Ch] [bp-64h]@9
	
	
	
	v3 = ArgInf.m_pText;
	
	if ( v3 )
	{
		
		if ( mystrlen(v3) >= 2 )
		{
			v4 = v3[0];
			//LOBYTE(v3) = v3[1];
			INT ii = v3[1];
			//ii = (ii & 0xFF) | (0xFF & v3[1]);
			//v3 = (char *)ii;
			
			if ( (BYTE)v4 >= 0xB0u )
			{
				if ( (BYTE)v4 <= 0xF7u )
				{
					if ( (BYTE)ii >= 0xA1u )
					{
						if ( (BYTE)ii <= 0xFEu )
						{
							//v3 = (const char *)(unsigned __int8)v3;
							v5 = *((WORD *)&s_wPYTab + (BYTE)ii + 94 * (BYTE)v4 - 16705);
							if ( v5 )
							{
								ii = v5>>8;
								if ( ii & 0x80 )
								{
									v27 = v5 & 0x7FFF;
									v28 = 0;
									v26 = (int)((char *)&s_wManyPYTab + 6 * v27);
									v53 = (char *)&s_wManyPYTab + 6 * v27;
									
									do
									{
										v29 = *(WORD *)v26;
										if ( !*(WORD *)v26 )
											break;
										v57 = 0;
										if ( (BYTE)v29 )
										{
											v31 = FindPY((BYTE)v29);
											v30 = -1;
											do
											{
												if ( !v30 )
													break;
												v32 = *v31++ == 0;
												--v30;
											}
											while ( !v32 );
											v35 = ~v30;
											v37 = &v31[-v35];
											v36 = &v57;
											v33 = v35;
											v34 = -1;
											do
											{
												if ( !v34 )
													break;
												v38 = *v36++ == 0;
												--v34;
											}
											while ( !v38 );
											memcpy(v36 - 1, v37, v33);
										}
										v39 = v29 >> 8;
										if ( (BYTE)v39 )
										{
											v41 = FindPY((BYTE)v39);
											v40 = -1;
											do
											{
												if ( !v40 )
													break;
												v42 = *v41++ == 0;
												--v40;
											}
											while ( !v42 );
											v44 = ~v40;
											v47 = &v41[-v44];
											v45 = v44;
											v46 = &v57;
											v43 = -1;
											do
											{
												if ( !v43 )
													break;
												v48 = *v46++ == 0;
												--v43;
											}
											while ( !v48 );
											memcpy(v46 - 1, v47, v45);
										}
										v49 = CloneTextData(&v57);
										//CFreqMem__AddDWord(&v54, v49);
										v54.AddDWord((DWORD)v49);
										++v28;
										v26 = (int)(v53 + 2);
										v53 += 2;
									}
									while ( v28 < 3 );
								}
								else
								{
									v57 = 0;
									if ( (BYTE)v5 )
									{
										v7 = FindPY((BYTE)v5);
										v6 = -1;
										do
										{
											if ( !v6 )
												break;
											v8 = *v7++ == 0;
											--v6;
										}
										while ( !v8 );
										v10 = ~v6;
										v13 = &v7[-v10];
										v11 = v10;
										v12 = &v57;
										v9 = -1;
										do
										{
											if ( !v9 )
												break;
											v14 = *v12++ == 0;
											--v9;
										}
										while ( !v14 );
										memcpy(v12 - 1, v13, v11);
									}
									v15 = v5 >> 8;
									if ( (BYTE)v15 )
									{
										v17 = FindPY((BYTE)v15);
										v16 = -1;
										do
										{
											if ( !v16 )
												break;
											v18 = *v17++ == 0;
											--v16;
										}
										while ( !v18 );
										v20 = ~v16;
										v23 = &v17[-v20];
										v21 = v20;
										v22 = &v57;
										v19 = -1;
										do
										{
											if ( !v19 )
												break;
											v24 = *v22++ == 0;
											--v19;
										}
										while ( !v24 );
										memcpy(v22 - 1, v23, v21);
									}
									v25 = CloneTextData(&v57);
									//CFreqMem__AddDWord(&v54, v25);
									v54.AddDWord((DWORD)v25);
								}
              }
            }
          }
        }
      }
    }
  }
  /*
  v51 = 4 * (v56 >> 2);
  v52 = krnl_MMalloc(v51 + 8, v3);
  *(DWORD *)v52 = 1;
  *(DWORD *)(v52 + 4) = v56 >> 2;
  memcpy((void *)(v52 + 8), (const void *)(v56 != 0 ? v55 : 0), v51);*/
  //v54 = &CFreqMem___vftable_;
  // �����±����������ݡ�
  
  INT nSize = v54.GetDWordCount () * sizeof (DWORD);
  LPBYTE p = (LPBYTE)E_MAlloc_Nzero (sizeof (INT) * 2 + nSize);
  *(LPINT)p = 1;  // ����ά����
  *(LPINT)(p + sizeof (INT)) = v54.GetDWordCount ();
  memcpy (p + sizeof (INT) * 2, v54.GetPtr (), nSize);
  
  //*(DWORD *)a1 = v52;
  return p;
  
}

//ƴ������ - ȡ���з���
/*
���ø�ʽ�� �������͡� ȡ������Ŀ ���ı��� ��ȡ�䷢����Ŀ�ĺ��֣� - ϵͳ����֧�ֿ�->ƴ������
Ӣ�����ƣ�GetPYCount
����ָ�����ֵķ�����Ŀ��������Ϊ�������
����<1>������Ϊ����ȡ�䷢����Ŀ�ĺ��֡�������Ϊ���ı��ͣ�text������ֻȡ���ı��ײ��ĵ�һ�����֣�������ı��ײ���Ϊ���꺺�֣�������� 0��
*/
LIBAPI(int, krnln_GetPYCount)
{
	int v3; // eax@1
	int v4; // edx@1
	int v5; // esi@1
	unsigned __int8 v6; // dl@3
	unsigned __int8 v8; // [sp+8h] [bp+4h]@3
	unsigned __int8 v9; // [sp+10h] [bp+Ch]@3
	
	PMDATA_INF a3 = &ArgInf;
	//  LOBYTE(v3) = a3;
	v5 = 0;
	v4 = (INT)a3->m_pText;
	if ( v4 )
	{
		//    LOBYTE(v3) = 0;
		if ( mystrlen((const char *)v4) >= 2 )
		{
			//LOBYTE(v3) = *(BYTE *)v4;
			v3 = *(BYTE *)v4;
			v6 = *(BYTE *)(v4 + 1);
			v8 = v3;
			v9 = v6;
			if ( (BYTE)v3 >= 0xB0u )
			{
				if ( (BYTE)v3 <= 0xF7u )
				{
					if ( v6 >= 0xA1u )
					{
						if ( v6 <= 0xFEu )
						{
							//LOWORD(v3) = *((WORD *)&s_wPYTab + v9 + 94 * v8 - 16705);
							v3 =  *((WORD *)&s_wPYTab + v9 + 94 * v8 - 16705);
							if (v3 )
							{
								INT ii = v3>>8;
								if ( ii & 0x80 )
								{
									v3 &= 0x7FFFu;
									v5 = (*((WORD *)&s_wManyPYTab + 3 * v3 + 2) != 0) + 2;
								}
								else
								{
									v5 = 1;
								}
							}
						}
					}
				}
			}
		}
	}
	return v5;
}

char *__cdecl GetPY(PMDATA_INF a1, int a2, const char **a3, int a4)
{
	const char *v4; // edx@1
	PMDATA_INF v5; // esi@1
	char v6; // al@3
	char v7; // dl@3
	int v8; // ecx@7
	unsigned __int16 v9; // bx@7
	signed int v10; // ecx@16
	char *v11; // edi@16
	char v12; // zf@18
	unsigned int v13; // edx@20
	signed int v14; // ecx@20
	signed int v15; // ecx@20
	char *v16; // edi@20
	const void *v17; // esi@20
	char v18; // zf@22
	__int16 v19; // bx@25
	signed int v20; // ecx@27
	char *v21; // edi@27
	char v22; // zf@29
	signed int v23; // ecx@31
	signed int v24; // ecx@31
	unsigned int v25; // ebx@31
	char *v26; // edi@31
	const void *v27; // esi@31
	char v28; // zf@33
	char *result; // eax@36
	char v30[128]; // [sp+14h] [bp-64h]@1//����������ջ�ڴ���ܴ�
	char v31; // [sp+84h] [bp+Ch]@3
	
	v5 = (PMDATA_INF )a3;
	v30[0] = 0;//��
	v4 = *a3;
	if ( *a3 )
	{
		if ( mystrlen(*a3) >= 2 )
		{
			v6 = *v4;
			v7 = v4[1];
			v31 = v6;
			if ( (unsigned __int8)v6 >= 0xB0u )
			{
				if ( (unsigned __int8)v6 <= 0xF7u )
				{
					if ( (unsigned __int8)v7 >= 0xA1u )
					{
						if ( (unsigned __int8)v7 <= 0xFEu )
						{
							v8 = (*((DWORD *)v5 + 3) - 1) & ((*((DWORD *)v5 + 3) - 1 < 0) - 1);
							v9 = *((WORD *)&s_wPYTab + (unsigned __int8)v7 + 94 * (unsigned __int8)v31 - 16705);
							if ( v9 )
							{
								INT ii = v9 >> 8;
								if ( ii & 0x80 )
								{
									if ( v8 >= 3 )
										goto LABEL_36;
									v9 = *((WORD *)&s_wManyPYTab + v8 + 2 * (v9 & 0x7FFF) + (v9 & 0x7FFF));
								}
								else
								{
									if ( v8 )
										goto LABEL_36;
								}
								if ( v9 )
								{
									if ( (BYTE)v9 )
									{
										if ( a4 != 2 )
										{
											v11 = FindPY((BYTE)v9);
											v10 = -1;
											do
											{
												if ( !v10 )
													break;
												v12 = *v11++ == 0;
												--v10;
											}
											while ( !v12 );
											v15 = ~v10;
											v17 = &v11[-v15];
											v16 = v30;//��
											v13 = v15;
											v14 = -1;
											do
											{
												if ( !v14 )
													break;
												v18 = *v16++ == 0;
												--v14;
											}
											while ( !v18 );
											memcpy(v16 - 1, v17, v13);
										}
									}
									v19 = v9 >> 8;
									if ( (BYTE)v19 )
									{
										if ( a4 != 1 )
										{
											v21 = FindPY((BYTE)v19);
											v20 = -1;
											do
											{
												if ( !v20 )
													break;
												v22 = *v21++ == 0;
												--v20;
											}
											while ( !v22 );
											v24 = ~v20;
											v27 = &v21[-v24];
											v25 = v24;
											v26 = v30;//��
											v23 = -1;
											do
											{
												if ( !v23 )
													break;
												v28 = *v26++ == 0;
												--v23;
											}
											while ( !v28 );
											memcpy(v26 - 1, v27, v25);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
LABEL_36:
	result = CloneTextData(v30);//��
	a1->m_pText = result;
	return result;
}
//ƴ������ - ȡƴ��
/*
���ø�ʽ�� ���ı��͡� ȡƴ�� ���ı��� ��ȡ��ƴ������ĺ��֣������� ��ȡƴ������������� - ϵͳ����֧�ֿ�->ƴ������
Ӣ�����ƣ�GetPY
���ذ���ָ�����ֵ�ָ��ƴ��������ı��������ָ��ƴ�����벻���ڣ������ؿ��ı���Ŀǰ��֧�ֹ��꺺�֡������ֵĵ�һ������Ϊ��������������Ϊ�������
����<1>������Ϊ����ȡ��ƴ������ĺ��֡�������Ϊ���ı��ͣ�text������ֻȡ���ı��ײ��ĵ�һ�����֣�������ı��ײ���Ϊ���꺺�֣��������һ�����ı���
����<2>������Ϊ����ȡƴ�������������������Ϊ�������ͣ�int��������ʼֵΪ��1����Ӧ���� 1 ���ú��ֵķ�����Ŀ֮�䡣���ֵķ�����Ŀ����ʹ�á�ȡ������Ŀ������ȡ�á�
*/
LIBAPI(char*, krnln_GetPY)
{
	MDATA_INF ret;
	return GetPY(&ret, nArgCount, (const char **)&ArgInf, 0);
	
}
//ƴ������ - ȡ��ĸ
/*
���ø�ʽ�� ���ı��͡� ȡ��ĸ ���ı��� ��ȡ��ƴ������ĺ��֣������� ��ȡƴ������������� - ϵͳ����֧�ֿ�->ƴ������
Ӣ�����ƣ�GetSM
���ذ���ָ������ָ��ƴ���������ĸ�����ı������ָ��ƴ�����벻���ڻ�ú��ִ˷�������ĸ�������ؿ��ı���Ŀǰ��֧�ֹ��꺺�֡�������Ϊ�������
����<1>������Ϊ����ȡ��ƴ������ĺ��֡�������Ϊ���ı��ͣ�text������ֻȡ���ı��ײ��ĵ�һ�����֣�������ı��ײ���Ϊ���꺺�֣��������һ�����ı���
����<2>������Ϊ����ȡƴ�������������������Ϊ�������ͣ�int��������ʼֵΪ��1����Ӧ���� 1 ���ú��ֵķ�����Ŀ֮�䡣���ֵķ�����Ŀ����ʹ�á�ȡ������Ŀ������ȡ�á�
*/
LIBAPI(char*, krnln_GetSM)
{
	MDATA_INF ret;
	return GetPY(&ret, nArgCount, (const char **)&ArgInf, 1);
	
}
//ƴ������ - ȡ��ĸ
/*
���ø�ʽ�� ���ı��͡� ȡ��ĸ ���ı��� ��ȡ��ƴ������ĺ��֣������� ��ȡƴ������������� - ϵͳ����֧�ֿ�->ƴ������
Ӣ�����ƣ�GetYM
���ذ���ָ������ָ��ƴ���������ĸ�����ı������ָ��ƴ�����벻���ڣ������ؿ��ı���Ŀǰ��֧�ֹ��꺺�֡�������Ϊ�������
����<1>������Ϊ����ȡ��ƴ������ĺ��֡�������Ϊ���ı��ͣ�text������ֻȡ���ı��ײ��ĵ�һ�����֣�������ı��ײ���Ϊ���꺺�֣��������һ�����ı���
����<2>������Ϊ����ȡƴ�������������������Ϊ�������ͣ�int��������ʼֵΪ��1����Ӧ���� 1 ���ú��ֵķ�����Ŀ֮�䡣���ֵķ�����Ŀ����ʹ�á�ȡ������Ŀ������ȡ�á�
*/
LIBAPI(char*, krnln_GetYM)
{
	MDATA_INF ret;
	return GetPY(&ret, nArgCount, (const char **)&ArgInf, 2);
	
}

unsigned char __cdecl ConvertNanFangPY(unsigned char a1, unsigned char a2, int a);
//ƴ������ - �����Ƚ�
/*
���ø�ʽ�� ���߼��͡� �����Ƚ� ���ı��� ���Ƚ��ı�һ���ı��� ���Ƚ��ı������߼��� �Ƿ�֧���Ϸ��������߼��� �Ƿ�Ϊģ���Ƚϣݣ� - ϵͳ����֧�ֿ�->ƴ������
Ӣ�����ƣ�CompPY
�Ƚ������ı��ķ��������������ͬ�����棬���򷵻ؼ١������ı��еķǹ��꺺�ֲ��֣��������м򵥵�ֵ�Ƚϡ�������Ϊ�������
����<1>������Ϊ�����Ƚ��ı�һ��������Ϊ���ı��ͣ�text������
����<2>������Ϊ�����Ƚ��ı�����������Ϊ���ı��ͣ�text������
����<3>������Ϊ���Ƿ�֧���Ϸ�����������Ϊ���߼��ͣ�bool��������ʼֵΪ���桱��Ϊ����֧���Ϸ��������֧���Ϸ������Ƚ�ʱ����Ϊ��������ķ�������ͬ���磺 n �� l�� z �� zh�� ie �� ue �ȵȡ�
����<4>������Ϊ���Ƿ�Ϊģ���Ƚϡ�������Ϊ���߼��ͣ�bool���������Ա�ʡ�ԡ�������Ϊ��ʱ�������Ƚ��ı�һ�ķ����ڴ��Ƚ��ı������ײ�������ʱ����Ϊ�Ƚ�ͨ���������ʡ�ԣ�Ĭ��ֵΪ�١�
*/
LIBAPI(BOOL, krnln_CompPY)
{
	int v3; // ebx@1
	int v4; // ebp@1
	int v5; // esi@2
	int v6; // eax@4
	unsigned int v7; // edx@4
	unsigned int v8; // ecx@4
	char v9; // cl@10
	unsigned __int8 v10; // dl@14
	unsigned __int8 v11; // cl@15
	signed int v12; // ebp@26
	signed int v13; // edi@27
	unsigned __int8 v14; // al@28
	int v15; // edx@28
	__int16 v16; // bx@30
	unsigned __int16 v17; // cx@32
	unsigned __int16 v18; // si@32
	unsigned __int8 v19; // al@32
	int v20; // edx@34
	int *v21; // ecx@35
	char *v22; // eax@40
	int v23; // ebx@40
	unsigned int v24; // ebp@41
	int *v25; // esi@41
	__int16 v26; // bx@42
	__int16 v27; // dx@43
	signed int v28; // ebx@45
	char *v29; // edi@45
	__int16 v30; // si@46
	int v31; // edx@47
	__int16 v32; // ax@48
	int *v33; // ecx@48
	int v35; // [sp+10h] [bp-2Ch]@8
	int v36; // [sp+14h] [bp-28h]@9
	int v37; // [sp+18h] [bp-24h]@1
	char v38; // [sp+1Ch] [bp-20h]@10
	signed int v39; // [sp+20h] [bp-1Ch]@26
	signed int v40; // [sp+24h] [bp-18h]@26
	char v41; // [sp+28h] [bp-14h]@10
	unsigned __int8 v42; // [sp+2Ch] [bp-10h]@18
	unsigned __int8 v43; // [sp+30h] [bp-Ch]@18
	int v44[20]; // [sp+34h] [bp-8h]@33
	unsigned __int8 v45; // [sp+48h] [bp+Ch]@32 ջ��ܴ�
	unsigned __int8 v46; // [sp+48h] [bp+Ch]@43
	
	INT a2 = nArgCount;
	PMDATA_INF a3 = &ArgInf;
	v4 = a3->m_int;
	v3 = a3[1].m_int;
	v37 = a3[2].m_int;
	if ( a3[3].m_dtDataType )
		v5 = a3[3].m_bool;
	else
		v5 = 0;
	v6 = 0;
	v7 = mystrlen((const char *)v4)-1;
	v8 = mystrlen((const char *)v3)-1;
	if ( v5 == 1 )
		//LOBYTE(v6) = (signed int)v7 <= (signed int)v8;
		v6 =(BYTE)(signed int)v7 <= (signed int)v8;
	else
		v6 = v7 == v8;
	if ( v6 )
	{
		v35 =  a3->m_int;
		
		while ( 1 )
		{
			v6 =(BYTE) *(BYTE *)v4;
			v36 = v3;
			if ( !*(BYTE *)v4 )
				break;
			v9 = *(BYTE *)v3;
			v41 = *(BYTE *)v4;
			v38 = *(BYTE *)v3;
			if ( v6 & 0x80 )
			{
				if ( !(v9 & 0x80) || (v10 = *(BYTE *)(v4 + 1), !v10) || (v11 = *(BYTE *)(v3 + 1), !v11) )
					return v6;
				
				if ( *(WORD *)v4 == *(WORD *)v3 )
				{
					v4 += 2;
					v3 += 2;
					v35 = v4;
				}
				else
				{
					v42 = *(BYTE *)(v4 + 1);
					v43 = *(BYTE *)(v3 + 1);
					if ( (BYTE)v6 < 0xB0u
						|| (BYTE)v6 > 0xF7u
						|| v10 < 0xA1u
						|| v10 > 0xFEu
						|| (v6 = *(BYTE *)v3, (unsigned __int8)v38 < 0xB0u)
						|| (unsigned __int8)v38 > 0xF7u
						|| v11 < 0xA1u
						|| v11 > 0xFEu )
						return v6;
					
					v12 = 0;
					v40 = 0;
					v39 = 0;
					do
					{
						v13 = 0;
						if ( v12 )
						{
							v15 = 47 * (unsigned __int8)v38;
							v14 = v43;
						}
						else
						{
							v15 = 47 * (unsigned __int8)v41;
							v14 = v42;
						}
						v16 = *((WORD *)&s_wPYTab + v14 + 2 * v15 - 16705);
						if ( !v16 )
							break;
						INT ii = v16>>8;
						if ( ii & 0x80 )
						{
							v23 = v16 & 0x7FFF;
							v22 = (char *)&s_wManyPYTab + 6 * v23;
							if ( v12 )
							{
								v28 = 0;
								v29 = v22;
								while ( 1 )
								{
									v30 = *(WORD *)v29;
									if ( !*(WORD *)v29 )
										break;
									v31 = 0;
									if ( (WORD)v44[0] )
									{
										v32 = v44[0];//��
										v33 = v44;//��
										do
										{
											if ( v32 == v30 )
												break;
											v32 = *((WORD *)v33 + 1);
											v33 = (int *)((char *)v33 + 2);
											++v31;
										}
										while ( v32 );
									}
									if ( *((WORD *)v44 + v31) != v30 )//��&V44
									{
										++v28;
										v29 += 2;
										if ( v28 < 3 )
											continue;
									}
									goto LABEL_55;
								}
								v40 = 1;
							}
							else
							{
								v25 = v44;//��
								v24 = (UINT)((char *)&s_wManyPYTab + 6 * v23) - (UINT)v44;//��&V44
								do
								{
									v26 = *(WORD *)((char *)v25 + v24);
									if ( !v26 )
										break;
									v46 = ConvertNanFangPY(v26, 0, v37);
									//HIBYTE(v27) = ConvertNanFangPY(HIBYTE(v26), v46, v37);
									//++v13;
									//LOBYTE(v27) = v46; //�˴�������
									
									ii = v26 >>8;
									ii = ConvertNanFangPY(ii, v46, v37);
									++v13;
									v27 = MAKEWORD(v46,ii);
									
									*(WORD *)v25 = v27;
									v25 = (int *)((char *)v25 + 2);
								}
								while ( v13 < 3 );
								v12 = v39;
								*((WORD *)v44 + v13) = 0;//��&V44
							}
						}
						else
						{
							v19 = ConvertNanFangPY(v16, 0, v37);
							v45 = v19;
							//LOBYTE(v6) = ConvertNanFangPY(HIBYTE(v16), v19, v37);
							//HIBYTE(v17) = v6;
							// LOBYTE(v17) = v45;//�˴�������
							ii = v16 >>8;
							v6 = (BYTE)ConvertNanFangPY(ii, v19, v37);
							v17 = MAKEWORD(v45,v6);
							v18 = v17;
							if ( v12 )
							{
								v20 = 0;
								if ( (WORD)v44[0] )//��&V44
								{
									v6 = (WORD)v44[0];//��&V44
									v21 = v44;//��
									do
									{
										if ( v6 == v18 )
											break;
										v6 = *((WORD *)v21 + 1);
										v21 = (int *)((char *)v21 + 2);
										++v20;
									}
									while ( v6 );
								}
								if ( *((WORD *)v44 + v20) != v18 )//��&V44
									return v6;
							}
							else
							{
								v44[0] = v17;//��
							}
						}
LABEL_55:
						++v12;
						v39 = v12;
          }
          while ( v12 <= 1 );
          v6 = (BYTE)v40;
          if ( v40 )
			  return v6;
          v4 = v35 + 2;
          v3 = v36 + 2;
          v35 += 2;
        }
      }
      else
      {
		  if ( v6 != v9 )
			  return v6;
		  ++v4;
		  ++v3;
		  v35 = v4;
      }
    }
    //v6 = (BYTE)a1;
    //*(DWORD *)a1 = 1;
	
	v6=1;
  }
  return v6;
  
}
//int ComparePYQuickStr(char *,CMyDWordArray &,int,int);
extern "C" {
	int __stdcall ComparePYQuickStr(char *a1, CMyDWordArray* a2, int a3);

	int __stdcall PrepareComparePYQuickStr(char *a1, CMyDWordArray* a2, int a3, int a4);
}
//int PrepareComparePYQuickStr(char *,CMyDWordArray &,CFreqMem *,int,unsigned char,int);
//ƴ������ - �����ֱȽ� 
/*
���ø�ʽ�� ���߼��͡� �����ֱȽ� ���ı��� ���Ƚ�ƴ�������֣��ı��� ���Ƚ���ͨ�ı����߼��� �Ƿ�֧���Ϸ������������� ƴ�����������ݣ� - ϵͳ����֧�ֿ�->ƴ������
Ӣ�����ƣ�CompPYCode
��һ��ƴ���������ı�������һ����ͨ�ı��Ƚϣ������������������棬���򷵻ؼ١�������Ϊ�������
����<1>������Ϊ�����Ƚ�ƴ�������֡�������Ϊ���ı��ͣ�text������ƴ�����������������ࣺ
һ����ƴ��ȫƴ�ࣺ �磺��jsj��ƥ�䡰���������ͬʱ��jisuanji��Ҳƥ�䡰���������ϵͳ�Զ��б�������־�������ƴ��ʽ����ȫƴ��ʽ��
����˫ƴ�ࣺ �磺��jisrji��ƥ�䡰���������˫ƴ����ķ����� Windows ϵͳ�µ�˫ƴ���뷨һ�£�
�����Զ��б��ࣺ ʹ�ô��������ƴ�������ֵ��ײ���һ������ַ������б𣺷ֺ� (��;��) ������ƴ��ȫƴ�࣬ð�� (��:��) ����˫ƴ�࣬��Ȳ�Ϊ�ֺ�Ҳ��Ϊð�ţ���Ĭ��Ϊ��ƴ��ȫƴ�ࡣ�硰jsj������;jsj������;jisuanji������:jisrji����ƥ�䡰���������
����дƴ��������ʱ��һЩ����
һ��Ϊ��ƥ��Ŀ���ı��еĴ�СдӢ����ĸ��������Ӧλ�ô�ʹ�ö�Ӧ�Ĵ�дӢ����ĸ���磺��jsjA��ƥ�䡰�����a�����������A����
����Ϊ��ƥ��Ŀ���ı��еİ�����֣�������Ӧλ�ô�ʹ�ø����֡��磺��jsj1��ƥ�䡰�����1����
����Ϊ��ƥ��Ŀ���ı��еĺ��ַ��Ż�֪�������ĺ��֣�������Ӧλ�ô�ʹ�øú��֡��磺��j��j1��ƥ�䡰�����1����
�ġ�ƴ���������ڲ��ܰ������ˡ�_�����������������Ƿ��š�
����<2>������Ϊ�����Ƚ���ͨ�ı���������Ϊ���ı��ͣ�text������
����<3>������Ϊ���Ƿ�֧���Ϸ�����������Ϊ���߼��ͣ�bool��������ʼֵΪ���桱��Ϊ����֧���Ϸ��������֧���Ϸ������Ƚ�ʱ����Ϊ��������ķ�������ͬ���磺 n �� l�� z �� zh�� ie �� ue �ȵȡ�
����<4>������Ϊ��ƴ����������𡱣�����Ϊ�������ͣ�int���������Ա�ʡ�ԡ�����ֵ����Ϊ���³���֮һ�� 1��#��ƴ��ȫƴ�� 2��#˫ƴ�� 3��#�Զ��б� ���ʡ�Ա�������Ĭ��Ϊ��#�Զ��б𡱡�
*/
LIBAPI(BOOL, krnln_CompPYCode)
{
	int v3; // eax@1
	int v4; // ecx@1
	int v5; // ebx@1
	int v6; // edi@1
	int v7; // edx@1
	signed int v8; // esi@2
	signed int v9; // eax@3
	char result; // al@9
	unsigned int v11; // esi@16
	int v12; // eax@16
	signed int i; // edi@19
	int v14; // ecx@20
	CMyDWordArray* v15; // [sp+10h] [bp-14h]@16
	int v16; // [sp+18h] [bp-Ch]@20
	unsigned int v17; // [sp+20h] [bp-4h]@16
	int v18; // [sp+30h] [bp+Ch]@1
	int a1 = 0;
	int a3 =(int)&ArgInf;
	
	v3 = a3;
	v7 = *(DWORD *)(a3 + 44);
	v4 = *(DWORD *)(a3 + 12);
	v5 = *(DWORD *)(a3 + 24);
	v6 = *(DWORD *)a3;
	v18 = *(DWORD *)(a3 + 12);
	
	if ( !v7 )
	{
		v8 = 3;
		goto LABEL_9;
	}
	v9 = *(DWORD *)(v3 + 36);
	if ( v9 > 3 )
		goto LABEL_29;
	if ( v9 < 1 )
	{
		v8 = 1;
		goto LABEL_9;
	}
	if ( v9 <= 3 )
		v8 = v9;
	else
LABEL_29:
	v8 = 3;
LABEL_9:
	a1 = 0;
	result = *(BYTE *)v6;
	if ( *(BYTE *)v6 )
	{
		if ( *(BYTE *)v4 )
		{
			if ( v8 == 3 )
			{
				v8 = 1;
				if ( result == 59 )
				{
					++v6;
				}
				else
				{
					if ( result == 58 )
					{
						++v6;
						v8 = 2;
					}
				}
			}
			//v12 = CFreqMem__CFreqMem(&v15);
			v15 = new CMyDWordArray();
			
			//LOBYTE(v12) = v8 == 1;
			//v15 = &CMyDWordArray___vftable_;
			
			v12 = v8 == 1;
			PrepareComparePYQuickStr((char*)v6, v15, v12 + 58, v5);
			DWORD* pv15 =(DWORD*)v15;
			v16 =(INT)pv15[2];
			v17 =pv15[4];
			v11 = (v17 >> 2) - 1;
			if ( (signed int)((v17 >> 2) - 1) >= 0 )
			{
				if ( ComparePYQuickStr((char*)v18, v15, v5) == 1 )
					a1 = 1;
			}
			//char txt [50];


			for ( i = 0; i <= (int)v11; ++i )
			{
				
				v14 = *(DWORD *)(v16 + 4 * i);
	
				//DWORD dwAddrr = *(DWORD*)v15->GetAt(i);
				//itoa(dwAddrr,txt,16);
				//if(::IsBadCodePtr ((int (__stdcall *)(void))dwAddrr))
					//MessageBox(NULL,txt,"Arr",MB_OK);

				if ( v14 ){
					_asm {
						push ecx;
						push edx;
						mov ecx,v14;
						mov edx, [ecx]
						push 1;
						call [edx];
						pop edx;
						pop ecx;
					}
					/*_asm mov ecx,eax;//һ��ҪECX��ֵ
					(**(void (__stdcall ***)(DWORD))v14)(1);*/
				}

			}
			v15->Free();
			delete v15;
			return a1;
		}
		if ( result )
			return result;
	}
	if ( !*(BYTE *)v4 )
		a1 = 1;
	return a1;
	
	
}