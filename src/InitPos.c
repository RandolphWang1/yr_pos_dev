#include "Main.h"

//��POS�ؼ�ģ����г�ʼ�����
INT InitPOS(void)
{
	int ret;
	char buff[100];
	char ckey;
	char szBuff[100];
	//int handle = 0;
	
	InitSDK();
	Clear();

	memset(buff, 0, sizeof(buff));
	GetSDKVersion(buff);
	printf("SDK VERSION: [%s]\n", buff);
	printf("APP VERSION: [%s]\n", APP_VERSION);

	SetScrFont(FONT20, WHITE);

	//��ʼ��������
	DebugOut("��ʼ��control...\n");
	ret = InitControl();
	//���������
	if(ret == -2)
	{
		DebugOut("��ʼ��ʱ��...\n");
		if(InitRTC() != OK)
		{
			SetScrFont(FONT24, RED);
			TextOut(0, 1, ALIGN_LEFT, "   Ŧ�۵���쳣!");
			DebugOut("��ʼ��control-Ŧ�۵���쳣!\n");
			Wait(1000);
			return ERROR;
		}
	}
	else if(ret != OK)
	{
		SetScrFont(FONT24, RED);
		TextOut(0, 1, ALIGN_LEFT, "   ��ʼ��control����!");
		DebugOut("��ʼ��control����!\n");
		Wait(1000);
		return ERROR;
	}
	else
		DebugOut("��ʼ��control�ɹ�!\n");

	//PowerOnMC55();
	M35_power_on();

	DebugOut("��ʼ��LCD...\n");
	//��ʼ��LCD
	if(InitLcd() != OK)
	{
		FailBeep();
		SetScrFont(FONT24, RED);
		TextOut(0, 1, ALIGN_LEFT, "    LCD��ʼ������!");
		DebugOut("LCD��ʼ������!\n");
		Wait(1000);
		return ERROR;
	}

	//�趨��ֽ
	SetWallPaper(1);
	//ShowBmpFile(0, 0, "pic/wallpaper1.bmp");
	ShowBmpFile(0, 0, "pic/main_bk.bmp");
	SetWallPaper(0);

	TextOut(0, 1, ALIGN_LEFT, "    ��ʼ��LCD...");
	Wait(500);
	TextOut(0, 2, ALIGN_LEFT, "    LCD��ʼ���ɹ�!");
	DebugOut("LCD��ʼ���ɹ�!\n");

	TextOut(0, 3, ALIGN_LEFT, "    ��ʼ������...");
	//��ʼ������
	DebugOut("��ʼ������...\n");
	Wait(500);
	if(InitKbd() != OK)
	{
		FailBeep();
		SetScrFont(FONT24, RED);
		TextOut(0, 4, ALIGN_LEFT, "    ���̳�ʼ������!");
		DebugOut("���̳�ʼ������!\n");
		return ERROR;
	}

	//ʹ�ܷ�����
	//EnableBeep(TRUE);

	TextOut(0, 4, ALIGN_LEFT, "    ���̳�ʼ���ɹ�!");
	DebugOut("���̳�ʼ���ɹ�!\n");

	//�趨LCD����
	SetLcdLight(3);
	SetShutBkLightTime(0);

	TextOut(0, 5, ALIGN_LEFT, "    ��ʼ����ӡ��...");
	//��ʼ����ӡ��
	DebugOut("��ʼ����ӡ��...\n");
	Wait(500);
	ret = InitPrinter();
	DebugOut("InitPrinter ret:[%d]\n", ret);
	if(ret < 0)
	{ 
		FailBeep();
		SetScrFont(FONT24, RED);
		TextOut(0, 6, ALIGN_LEFT, "    ��ӡ����ʼ������!");
		DebugOut("��ӡ����ʼ������!\n");
	}
	else
	{
		TextOut(0, 6, ALIGN_LEFT, "    ��ӡ����ʼ���ɹ�!");
		DebugOut("��ӡ����ʼ���ɹ�!\n");
	}
/*
	SwitchCom2_Rf(1);
	TextOut(0, 7, ALIGN_LEFT, "    ��ʼ���ǽ�...");
	DebugOut("��ʼ���ǽ�...\n");
	if(-1 == FM17dcInit(2, 19200))
	{
     		FM17dcExit(iM1Handle);
            gTerm.bIsDC = TRUE;
			TextOut(0, 8, ALIGN_LEFT, "    �ǽӳ�ʼ���ɹ�!");
			DebugOut("�ǽӳ�ʼ���ɹ�!\n");
	}else if (OK != FM17dcInit(2, 19200))
    {
        gTerm.bIsDC = FALSE;
		TextOut(0, 8, ALIGN_LEFT, "   �ǽӳ�ʼ���ɹ�!");
		DebugOut("�ǽӳ�ʼ���ɹ�!\n");
	}
	*/
	//��ʼ��ɨ��ͷ
	switch_CTSRTS(0);   //CTS/RTS���ޱ��ģ��ʹ��.��ʼ��ִ��һ�μ���.
	
	Clear(); 
	TextOut(0, 4, ALIGN_CENTER, "�Ƿ��ʼ��ɨ��ͷ?");
    	ckey=WaitKey(0);
	
    	//ckey= KEY_ENTER;
    	if(ckey== KEY_ENTER)
    	{
    		switch_COM2(0);     //���������廪�ǽ�ģ���ɨ��ѭ������,��ÿ��ɨ��ǰ��ִ�иþ�.

	    	Clear();
///////////////////////////////////////////////////////////////////////
		/*memset(buff, 0, sizeof(buff));
		handle = SERIAL_Open("/dev/ttyS2", 9600);
		SERIAL_Read(handle, buff,100);
		*/
///////////////////////////////////////////////////////////////////////
		ret=se955_init() ;
		if(ret<0)
		{
		    FailBeep();
			SetScrFont(FONT24, RED);
			TextOut(0, 4, ALIGN_LEFT, "ɨ��ͷû�а�װ,����ͨ��1��ռ��");
			DebugOut("error code:[%d]\n",ret);
			iScanHandle=FALSE;
			WaitKey(2000);
		}
		else
		{
			iScanHandle=TRUE;
			DebugOut("error code:[%d]\n",ret);
		}
    	}
	else
	{
		iScanHandle=FALSE;
	}
	SetScrFont(FONT20, WHITE);
	Clear();
	//��ȡ�����ļ�
	TextOut(0, 7, ALIGN_LEFT, "    ��ȡ�����ļ�...");
	DebugOut("��ȡ�����ļ�\n");
	Wait(500);
   	memset(&gTerm, 0,sizeof(gTerm));
	if(!ReadData("test-term.dat", &gTerm,sizeof(T_TERM), 0))
	{
		TextOut(0, 8, ALIGN_LEFT, "    ��ʼ�������ļ�..."); 
		DebugOut("��ʼ�������ļ�...\n");
		InitTerm();
		Wait(1000);
		TextOut(0, 9, ALIGN_LEFT, "    ��ʼ�������ļ��ɹ�!"); 
		DebugOut("��ʼ�������ļ��ɹ�!\n");
	}
	else
	{
		TextOut(0, 8, ALIGN_LEFT, "    ��ȡ�����ļ��ɹ�!"); 
		DebugOut("��ȡ�����ļ��ɹ�!\n");
	}

	memset(&gSMS, 0,sizeof(T_SMS));
	if(!ReadData("test-sms.dat", &gSMS,sizeof(T_SMS), 0))
	{
		TextOut(0, 8, ALIGN_LEFT, "    ��ʼ�������ļ�..."); 
		DebugOut("��ʼ�������ļ�...\n");
		InitSMS();
		Wait(1000);
		TextOut(0, 9, ALIGN_LEFT, "    ��ʼ�������ļ��ɹ�!"); 
		DebugOut("��ʼ�������ļ��ɹ�!\n");
	}
	else
	{
		DebugOut("��ȡ�����ļ��ɹ�!\n");
	}
	

	if(gTerm.bAutoIP == TRUE)
	{
		system("/usr/udhcp/udhcpc");
	} 
	else 
	{
	
		//TextOutByPixel(45, 65, "��ǰIPģʽ���̶�IP");
		memset(szBuff, 0, sizeof(szBuff));
		strcat(szBuff, "ifconfig eth0 ");
		strcat(szBuff, gTerm.tEthernet.szLocalIP);
		strcat(szBuff, " netmask ");
		strcat(szBuff, gTerm.tEthernet.szMask);
		//strcat(szBuff, " up");	
		DebugOut("\n%s\n", szBuff);
		system(szBuff);	

		//�ر�����
		memset(szBuff, 0, sizeof(szBuff));
		strcat(szBuff, "route del default gw ");
		strcat(szBuff, gTerm.tEthernet.szGateway);
		DebugOut("\n%s\n", szBuff);
		system(szBuff);

		//��������
		memset(szBuff, 0, sizeof(szBuff));
		strcat(szBuff, "route add default gw ");
		strcat(szBuff, gTerm.tEthernet.szGateway);
		DebugOut("\n%s\n", szBuff);
		system(szBuff);  

		memset(szBuff, 0, sizeof(szBuff));
		strcat(szBuff, "ifconfig eth0 down && ifconfig eth0 up ");
		DebugOut("\n%s\n", szBuff);
		system(szBuff);	 
	}
	TextOut(0, 8, ALIGN_CENTER, "��̫���������!");


	return OK;
}

