#include "Main.h"



int JingZhenTest()
{
	int ret;
	T_DATETIME tTime;
	char buff[100];
	int len = 30;

	while(1)
	{
		Clear();

		SetScrFont(FONT20, WHITE);

		//����
		//ShowBmpFile(0, 25, "pic/title.bmp");
		TextOutByPixel(100, 30, "�������");

		TextOut(0, 3, ALIGN_LEFT, "����ʱ��:");
		memset(&tTime, 0, sizeof(T_DATETIME));
		GetDateTime(&tTime);
		memset(buff, 0, sizeof(buff));
		sprintf(buff, "%s%s��%s��%s��%sʱ%s��%s��", tTime.century, tTime.year, tTime.month, tTime.day,
			tTime.hour, tTime.minute, tTime.second);
		TextOut(0, 4, ALIGN_CENTER, buff);

		//����������
		TextOut(1, 6, ALIGN_LEFT, "��������ʱ��:");
		SetScrFont(FONT20, RED);
        	memset(buff, 0, sizeof(buff));
        	ret = InputDate(0, 7, buff, &len, 0, BLACK, GREEN, FONT24);
		if(ret == OK)
		{
			printf("%d\n", len);
			printf("%s\n", buff);
			memset(&tTime, 0, sizeof(T_DATETIME));
			memcpy(tTime.century, buff, 2);
			memcpy(tTime.year, buff+2, 2);
			memcpy(tTime.month, buff+4, 2);
			memcpy(tTime.day, buff+6, 2);
			memcpy(tTime.hour, buff+8, 2);
			memcpy(tTime.minute, buff+10, 2);
			memcpy(tTime.second, buff+12, 2);
			SetDateTime(tTime);
			OkBeep();
			Clear();
			TextOut(0, 4, ALIGN_CENTER, "���óɹ�");
			WaitKey(1000);
		}
		else if (ret == KEY_CANCEL)
			return KEY_CANCEL;
	}
	return OK;
}



