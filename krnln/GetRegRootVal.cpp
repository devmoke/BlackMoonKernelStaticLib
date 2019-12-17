#include "stdafx.h"
// 1��#���ࣻ 2��#�������ã� 3��#�����û��� 4��#���ػ����� 5��#�����û���
HKEY GetRegRootVal(INT nVal)
{
	HKEY hkey = NULL;
	switch(nVal)
	{
	case 1:
		hkey = HKEY_CLASSES_ROOT;
		break;
	case 2:
		hkey = HKEY_CURRENT_CONFIG;
		break;
	case 3:
		hkey = HKEY_CURRENT_USER;
		break;
	case 4:
		hkey = HKEY_LOCAL_MACHINE;
		break;
	case 5:
		hkey = HKEY_USERS;
		break;
	}
	return hkey;
}