#include "stdafx.h"
#include <math.h>
//ȡʱ�䲿��,����1Ϊֻ��ʱ�䲿�ֵ�DATE����
void GetTimePart(DATE dt,INT& nHour,INT& nMinute,INT& nSecond)
{
	INT nSecCount =DATE( 86400 * fabs(dt)+0.5);//������
	nHour = nSecCount / 3600;
	nSecCount %= 3600;
	nMinute = nSecCount / 60;
	nSecond = nSecCount % 60;
}