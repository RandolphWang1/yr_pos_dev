#include "Main.h"



void TestInput()
{
	int ret;
	char buff[200];

	Clear();
	TextOut(0, 1, ALIGN_LEFT, "   ������:");
	memset(buff, 0, sizeof(buff));
	ret = Input(2, 3, buff, 50, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, TRUE);
	if(ret != OK)
    {
    	DebugOut("ret=[%d]\n", ret);
		return;
	}

	ClearClient();
	TextOut(0, 1, ALIGN_LEFT, "������������:");
	TextOut(0, 3, ALIGN_LEFT, buff);

	WaitKey(0);
}

void TestInputMoney()
{
	int ret;
	char buff[200];

	ClearClient();
	TextOut(0, 1, ALIGN_LEFT, "   ������:");
	memset(buff, 0, sizeof(buff));
	ret = InputMoney(2, 3, buff, 50);
	if(ret != OK)
    {
    	DebugOut("ret=[%d]\n", ret);
		return;
	}

	ClearClient();
	TextOut(0, 1, ALIGN_LEFT, "������������:");
	TextOut(0, 3, ALIGN_LEFT, buff);

	WaitKey(0);
}

void TestInputDate()
{
	int ret;
	char buff[200];
	int len;

	ClearClient();
	TextOut(0, 1, ALIGN_LEFT, "   ������:");
	memset(buff, 0, sizeof(buff));
	ret = InputDate(2, 3, buff, &len, 0, BLACK, GREEN, FONT24);
	if(ret != OK)
    {
    	DebugOut("ret=[%d]\n", ret);
		return;
	}

	ClearClient();
	TextOut(0, 1, ALIGN_LEFT, "������������:");
	TextOut(0, 3, ALIGN_LEFT, buff);

	WaitKey(0);
}

void PrintIMG()
{
	int ret;
	int i;

	ClearClient();
	TextOut(0, 4, ALIGN_CENTER, "���ڴ�ӡ...");

	for(i = 0; i < 3; i ++)
	{
		ret = PrintBMP(0, "pic/print.bmp");
		DebugOut("PrintBMP ret:[%d]\n", ret);
		if(ret != OK)
		{
			FailBeep();
			ClearClient();
			TextOut(0, 4, ALIGN_CENTER, "��ӡʧ��");
			WaitKey(2000);
		}
	}
}

void CopyData()
{
	Clear();
	TextOut(0, 4, ALIGN_CENTER, "����ѹ��...");
	system("cd /usr/local/; tar zcvf sys.tar.gz *");
	Clear();
	TextOut(0, 4, ALIGN_CENTER, "���ڿ���...");
	if(CopyFile2U("/usr/local/sys.tar.gz", "/") != OK)
	{
		FailBeep();
		Clear();
		TextOut(0, 4, ALIGN_CENTER, "û��usb�̻���usb��û���ú�!");
		WaitKey(0);
		return;
	}

	system("cd /usr/local/; rm sys.tar.gz; cd /usr/local/D620D/");

	OkBeep();
	Clear();
	TextOut(0, 3, ALIGN_CENTER, "�����ɹ�");
	WaitKey(3000);
}

void OtherTest()
{
	char cKey;
	char pwd[6+1] = "";
	int ret;
	T_IDENTIFY_INFO identify_info;
	char buff[100];
	int i;

	Clear();
	TextOut(0, 2, ALIGN_LEFT, "   ����������:");
	SetScrFont(FONT20, RED);
	memset(pwd, 0, sizeof(pwd));
	ret = Input(18, 2, pwd, 6, IME_NUMBER, BLACK, GREEN, TRUE, FALSE, TRUE);
	ReStoreScrFont();
	if(ret != OK)
    {
    	DebugOut("ret=[%d]\n", ret);
		return;
	}

	if(strcmp(pwd, "0"))
	{
    	DebugOut("password error!\n");
		Clear();
		TextOut(0, 3, ALIGN_CENTER, "�������");
		FailBeep();
		WaitKey(2000);
		return;
	}

	while(1)
	{
		ClearClient();
		SetScrFont(FONT20, GREEN);
		TextOut(0, 0, ALIGN_CENTER, "��������");
		TextOut(0, 2, ALIGN_LEFT, " 1.��׼���뷨����");
		TextOut(0, 3, ALIGN_LEFT, " 2.������뷨����");
		TextOut(0, 4, ALIGN_LEFT, " 3.�������뷨����");
		TextOut(0, 5, ALIGN_LEFT, " 4.��˼���֤�Ķ���");
		TextOut(0, 6, ALIGN_LEFT, " 5.DES���ܲ���");
		TextOut(0, 7, ALIGN_LEFT, " 6.��ӡͼƬ����");
		TextOut(0, 8, ALIGN_LEFT, " 7.��������");	//����/usr/local/Ŀ¼������ѹ������U��
		TextOut(0, 9, ALIGN_LEFT, " 8.��ӡQR��ά��");	
		

		cKey = WaitKey(0);

		switch(cKey)
		{
			case KEY_CANCEL:
				ReStoreScrFont();
				return;
				break;
			case KEY_1:
				TestInput();
				break;
			case KEY_2:
				TestInputMoney();
				break;
			case KEY_3:
				TestInputDate();
				break;
			case KEY_4:
				ReadIdentify(&identify_info);
				break;
			case KEY_5:
				memset(buff, 0, sizeof(buff));
				function_des(1, "\x12\x34\x56\x78", "12345678", buff);
				printf("DES result:\n");
				for(i = 0; i < 8; i ++)
					printf("%02x ", buff[i]);
				printf("\n");
				break;
			case KEY_6:
				PrintIMG();
				break;
			case KEY_7:
				CopyData();
				break;
			case KEY_8:
				PrinterQRTest();
				break;
		}
	}

}



