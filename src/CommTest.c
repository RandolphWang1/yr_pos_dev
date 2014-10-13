#include "Main.h"


static int SetModem()
{
	int ret;
	char tempbuff[40];
	char buff[128];
	int tempDataNum;

	Clear();;

	SetScrFont(FONT20, WHITE);

	TextOut(0, 2, ALIGN_CENTER, "���ŷ�ʽ");
	if(gTerm.bOut)
	{
		ShowBmpFile(80, 70, "pic/select.bmp");
		ShowBmpFile(80, 110, "pic/select_bk.bmp");
	}
	else
	{
		ShowBmpFile(80, 70, "pic/select_bk.bmp");
		ShowBmpFile(80, 110, "pic/select.bmp");
	}
	TextOutByPixel(130, 80, "1.����");
 	TextOutByPixel(130, 120, "2.ֱ��");

   TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");

	ret = WaitLimitKey("\x01\x02\x12\x0F", 4, 0);

	if(ret == KEY_CANCEL)
		goto FAILED;
	else if(ret == KEY_1)
		gTerm.bOut = TRUE;
	else if(ret == KEY_2)
		gTerm.bOut = FALSE;

	//ѡ������,�������ߺ���
	if(gTerm.bOut)
	{
		Clear();
		SetScrFont(FONT20, WHITE);
		TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
		TextOut(2, 3, ALIGN_LEFT, "���ߺ���:");
		memset(tempbuff, 0, sizeof(tempbuff));
		tempbuff[0] = gTerm.szOutNo;
		SetScrFont(FONT20, RED);
		ret = Input(13, 3, tempbuff, 1, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
		if(ret != OK)
	    	goto FAILED;
		else
		{
			if(tempbuff[0] == 0)
				gTerm.szOutNo = '0';
			else	
				gTerm.szOutNo = tempbuff[0];
		}

		Clear();
		SetScrFont(FONT20, WHITE);
		TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
		TextOut(2, 3, ALIGN_LEFT, "��ʱ����:");
		memset(tempbuff, 0, sizeof(tempbuff));
		tempbuff[0] = gTerm.delay_times+0x30;
		SetScrFont(FONT20, RED);
		ret = Input(13, 3, tempbuff, 1, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
		if(ret != OK)
	    		goto FAILED;
		else
		{
			if(tempbuff[0] == 0)
				gTerm.delay_times = 0;
			else	
				gTerm.delay_times = tempbuff[0]-0x30;
		}
	}

	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 3, ALIGN_CENTER, "�����绰");
	TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
	SetScrFont(FONT20, RED);
	ret = Input(5, 5, gTerm.szTelNo, SIZE_TEL_NO, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
	if(ret != OK)
    		goto FAILED;

	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 3, ALIGN_CENTER, "TPDU");
	TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
	SetScrFont(FONT20, RED);
	ret = Input(14, 5, gTerm.szTPDU, SIZE_TPDU, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
	if(ret != OK)
    		goto FAILED;

	while(1)
	{
		Clear();
		SetScrFont(FONT20, WHITE);
		TextOut(0, 3, ALIGN_CENTER, "������������С");
		TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
		memset(buff, 0, sizeof(buff));
		sprintf(buff, "%d", gTerm.uiModemDataNum);
		SetScrFont(FONT20, RED);
		ret = Input(11, 5, buff, 4, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
		if(ret != OK)
	    	goto FAILED;
		if(ret == OK)
		{
			tempDataNum = atoi(buff);
			if(tempDataNum <= 0 || tempDataNum > 9999)
			{
				Clear();
				SetScrFont(FONT20, WHITE);
				TextOut(0, 6, ALIGN_CENTER, "�������ݷǷ�");
				WaitKey(2000);
				continue;
			}
			gTerm.uiModemDataNum = tempDataNum;
		}
		break;
	}

	//�����ļ�
	if(WriteData("test-term.dat", &gTerm, sizeof(T_TERM), 0) == FALSE)
	{
		Clear();                      
		SetScrFont(FONT20, WHITE);
		TextOut(0, 3, ALIGN_CENTER, "�����ļ�����"); 
		TextOut(0, 4, ALIGN_CENTER, "���Ժ�����"); 
		FailBeep();
		WaitKey(2000);
    	goto FAILED;
	}

	OkBeep();

	ClearLine(1, 9);
	SetScrFont(FONT20, WHITE);
	TextOut(0, 4, ALIGN_CENTER, "ͨѶ��Ϣ���óɹ�!");
	WaitKey(2000);
	return OK;

FAILED:
	memset(&gTerm, 0, sizeof(T_TERM));
	ReadData("test-term.dat", &gTerm,sizeof(T_TERM), 0);

	return ERROR;
}

static int SetGPRS()
{
	int ret;
	char buff[128];
	int tempDataNum;

	Clear();;
	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "����IP");
	TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
	SetScrFont(FONT20, RED);
	if(InputIP(8, 5, gTerm.szGprsServerIP) != OK)
    	goto FAILED;
 
	Clear();;
	SetScrFont(FONT20, WHITE);
	TextOut(0, 3, ALIGN_CENTER, "�����˿�");
	TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
	SetScrFont(FONT20, RED);
	ret = Input(7, 5, gTerm.szGprsServerPort, 5, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
	if(ret != OK)
    	goto FAILED;

	while(1)
	{
		Clear();
		SetScrFont(FONT20, WHITE);
		TextOut(2, 4, ALIGN_LEFT, "������������С:");
		TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");

		memset(buff, 0, sizeof(buff));
		sprintf(buff, "%d", gTerm.uiGprsDataNum);
		SetScrFont(FONT20, RED);
		ret = Input(18, 4, buff, 4, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
		if(ret != OK)
	    	goto FAILED;
		tempDataNum = atoi(buff);
		if(tempDataNum <= 0 || tempDataNum > 9999)
		{
			Clear();
			SetScrFont(FONT20, WHITE);
			TextOut(0, 4, ALIGN_CENTER, "�������ݷǷ�");
			WaitKey(2000);
			continue;
		}
		gTerm.uiGprsDataNum = tempDataNum;
		DebugOut("test data num:%d\n", gTerm.uiGprsDataNum);
		break;
	}

	//�����ļ�
	if(WriteData("test-term.dat", &gTerm, sizeof(T_TERM), 0) == FALSE)
	{
		Clear();                      
		SetScrFont(FONT20, WHITE);
		TextOut(0, 3, ALIGN_CENTER, "�����ļ�����"); 
		TextOut(0, 4, ALIGN_CENTER, "���Ժ�����"); 
		FailBeep();
		WaitKey(2000);
    	goto FAILED;
	}

	OkBeep();
	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(2, 4, ALIGN_CENTER, "G�����óɹ�!");
	WaitKey(2000);
	return OK;

FAILED:
	memset(&gTerm, 0, sizeof(T_TERM));
	ReadData("test-term.dat", &gTerm,sizeof(T_TERM), 0);

	return ERROR;
}
static int SetCDMA()
{
	int ret;
	char buff[128];
	int tempDataNum;

	Clear();;
	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "����IP");
	TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
	SetScrFont(FONT20, RED);
	if(InputIP(8, 5, gTerm.szGprsServerIP) != OK)
    	goto FAILED;
 
	Clear();;
	SetScrFont(FONT20, WHITE);
	TextOut(0, 3, ALIGN_CENTER, "�����˿�");
	TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
	SetScrFont(FONT20, RED);
	ret = Input(7, 5, gTerm.szGprsServerPort, 5, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
	if(ret != OK)
    	goto FAILED;

	while(1)
	{
		Clear();
		SetScrFont(FONT20, WHITE);
		TextOut(2, 4, ALIGN_LEFT, "������������С:");
		TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");

		memset(buff, 0, sizeof(buff));
		sprintf(buff, "%d", gTerm.uiGprsDataNum);
		SetScrFont(FONT20, RED);
		ret = Input(18, 4, buff, 4, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
		if(ret != OK)
	    	goto FAILED;
		tempDataNum = atoi(buff);
		if(tempDataNum <= 0 || tempDataNum > 9999)
		{
			Clear();
			SetScrFont(FONT20, WHITE);
			TextOut(0, 4, ALIGN_CENTER, "�������ݷǷ�");
			WaitKey(2000);
			continue;
		}
		gTerm.uiGprsDataNum = tempDataNum;
		DebugOut("test data num:%d\n", gTerm.uiGprsDataNum);
		break;
	}

	//�����ļ�
	if(WriteData("test-term.dat", &gTerm, sizeof(T_TERM), 0) == FALSE)
	{
		Clear();                      
		SetScrFont(FONT20, WHITE);
		TextOut(0, 3, ALIGN_CENTER, "�����ļ�����"); 
		TextOut(0, 4, ALIGN_CENTER, "���Ժ�����"); 
		FailBeep();
		WaitKey(2000);
    	goto FAILED;
	}

	OkBeep();
	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(2, 4, ALIGN_CENTER, "C�����óɹ�!");
	WaitKey(2000);
	return OK;

FAILED:
	memset(&gTerm, 0, sizeof(T_TERM));
	ReadData("test-term.dat", &gTerm,sizeof(T_TERM), 0);

	return ERROR;
}
static int SetEthernet()
{
	int ret;
	char buff[128] = "";
	int tempDataNum;

	Clear();;
	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "����IP");
	TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
	SetScrFont(FONT20, RED);
	if(InputIP(8, 5, gTerm.tEthernet.szServerIP) != OK)
    	goto FAILED;

	Clear();;
	SetScrFont(FONT20, WHITE);
	TextOut(0, 3, ALIGN_CENTER, "�����˿�");
	TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
	SetScrFont(FONT20, RED);
	ret = Input(7, 5, gTerm.tEthernet.szServerPort, 5, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
	if(ret != OK)
    	goto FAILED;

	Clear();;
	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "����IP");
	TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
	SetScrFont(FONT20, RED);
	if(InputIP(8, 5, gTerm.tEthernet.szLocalIP) != OK)
    	goto FAILED;

	Clear();;
	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "��������");
	TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
	SetScrFont(FONT20, RED);
	if(InputIP(8, 5, gTerm.tEthernet.szMask) != OK)
    	goto FAILED;

	Clear();;
	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "����");
	TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
	SetScrFont(FONT20, RED);
	if(InputIP(8, 5, gTerm.tEthernet.szGateway) != OK)
    	goto FAILED;

	while(1)
	{
		Clear();
		SetScrFont(FONT20, WHITE);
		TextOut(2, 4, ALIGN_LEFT, "������������С:");
		TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");

		memset(buff, 0, sizeof(buff));
		sprintf(buff, "%d", gTerm.uiEthDataNum);
		SetScrFont(FONT20, RED);
		ret = Input(18, 4, buff, 4, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
		if(ret != OK)
	    	goto FAILED;
		tempDataNum = atoi(buff);
		if(tempDataNum <= 0 || tempDataNum > 9999)
		{
			Clear();
			SetScrFont(FONT20, WHITE);
			TextOut(0, 4, ALIGN_CENTER, "�������ݷǷ�");
			WaitKey(2000);
			continue;
		}
		gTerm.uiEthDataNum = tempDataNum;
		break;
	}

	Clear();;
	SetScrFont(FONT20, WHITE);
	TextOut(2, 4, ALIGN_CENTER, "��ʼ����̫��...");

	//���ñ���IP��ַ   
	memset(buff, 0, sizeof(buff));	
	strcat(buff, "ifconfig eth0 ");
	strcat(buff, gTerm.tEthernet.szLocalIP);
	strcat(buff, " netmask ");
	strcat(buff, gTerm.tEthernet.szMask);
	strcat(buff, " up");	
	printf("\n%s\n", buff);
	system(buff);	 

	memset(buff, 0, sizeof(buff));	
	strcat(buff, "route del default gw ");
	strcat(buff, gTerm.tEthernet.szGateway);
	printf("\n%s\n", buff);
	system(buff);  

	memset(buff, 0, sizeof(buff));	
	strcat(buff, "route add default gw ");
	strcat(buff, gTerm.tEthernet.szGateway);
	printf("\n%s\n", buff);
	system(buff);

	//�����ļ�
	if(WriteData("test-term.dat", &gTerm, sizeof(T_TERM), 0) == FALSE)
	{
		Clear();                      
		SetScrFont(FONT20, WHITE);
		TextOut(0, 3, ALIGN_CENTER, "�����ļ�����"); 
		TextOut(0, 4, ALIGN_CENTER, "���Ժ�����"); 
		FailBeep();
		WaitKey(2000);
    	goto FAILED;
	}

	OkBeep();
	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(2, 4, ALIGN_CENTER, "��̫�����óɹ�!");
	WaitKey(2000);
	return OK;

FAILED:
	memset(&gTerm, 0, sizeof(T_TERM));
	ReadData("test-term.dat", &gTerm,sizeof(T_TERM), 0);

	return ERROR;
}


// �鿴��ǰip����
int ViewIpSet()
{
	UCHAR ucKey;
	char sKeyName[20];

	ClearKbd();
	while(1)
	{
		Clear();
		SetScrFont(FONT20, WHITE);

		//����
		//ShowBmpFile(0, 25, "pic/title.bmp");
		TextOutByPixel(100, 30, "��ǰIP������Ϣ");

		if (gTerm.bAutoIP== TRUE) {
			TextOutByPixel(45, 65, "��ǰIPģʽ���Զ���ȡ");
		} else {
			TextOutByPixel(45, 65, "��ǰIPģʽ���̶�IP");
			TextOutByPixel(45, 100, "IP��ַ��");
			TextOutByPixel(150, 100, gTerm.tEthernet.szLocalIP);
			TextOutByPixel(45, 135, "�������룺");
			TextOutByPixel(150, 135, gTerm.tEthernet.szMask);
			TextOutByPixel(45, 170, "���أ�");
			TextOutByPixel(150, 170, gTerm.tEthernet.szGateway);
		}
		ucKey = WaitLimitKey("\x12", 1, 0);
		memset(sKeyName, 0, sizeof(sKeyName));
		GetKeyName(ucKey, sKeyName);
		DebugOut("press key: %s\n", sKeyName);

		switch(ucKey)
		{
			case KEY_CANCEL:
				return OK;
				break;
		}
	}
	return OK;
}



void SetCommParam()
{
	UCHAR ucKey;
	char sKeyName[20];
	int ret;

	ClearKbd();
	while(1)
	{
		Clear();

		SetScrFont(FONT20, WHITE);

		//����
		//ShowBmpFile(0, 25, "pic/title.bmp");
		TextOutByPixel(95, 30, "ͨѶ��������");

		//�˵�
		ShowBmpFile(90, 60, "pic/button.bmp");
		TextOutByPixel(105, 65, "1.����");

		ShowBmpFile(90, 95, "pic/button.bmp");
		TextOutByPixel(105, 100, "2.G��");

		ShowBmpFile(90, 130, "pic/button.bmp");
		TextOutByPixel(105, 135, "3.��̫��");

        ShowBmpFile(90, 165, "pic/button.bmp");
		TextOutByPixel(105, 170, "4.C��");
		
        ShowBmpFile(90, 200, "pic/button.bmp");
        TextOutByPixel(105, 205, "5.wifi��");

                ucKey = WaitLimitKey("\x01\x02\x03\x04\x05\x12", 6, 0);
		memset(sKeyName, 0, sizeof(sKeyName));
		GetKeyName(ucKey, sKeyName);
		DebugOut("press key: %s\n", sKeyName);

		switch(ucKey)
		{
			case KEY_CANCEL:
				return;
				break;
			case KEY_1:
				SetModem();
				break;
			case KEY_2:
				SetGPRS();
				break;
			case KEY_3:
				Clear();
				TextOut(0, 0, ALIGN_CENTER, "IP ��ȡ��ʽ");
				
				TextOut(0, 4, ALIGN_LEFT, "  1.�Զ���ȡIP");
				TextOut(0, 5, ALIGN_LEFT, "  2.�̶�����IP");
				TextOut(0, 6, ALIGN_LEFT, "  3.�鿴��ǰip����");
				ucKey = WaitLimitKey("\x12\x01\x02\x03", 4, 0);
				if(ucKey == KEY_1)
				{
					gTerm.bAutoIP = TRUE;
					if(WriteData("test-term.dat", &gTerm, sizeof(T_TERM), 0) == FALSE)
					{
						Clear();                      
						SetScrFont(FONT20, WHITE);
						TextOut(0, 3, ALIGN_CENTER, "�����ļ�����"); 
						TextOut(0, 4, ALIGN_CENTER, "���Ժ�����"); 
						FailBeep();
						WaitKey(2000);
				    	//goto FAILED;
					}
					Clear();;
					SetScrFont(FONT20, WHITE);
					TextOut(0, 2, ALIGN_CENTER, "����IP");
					TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
					SetScrFont(FONT20, RED);
					if(InputIP(8, 5, gTerm.tEthernet.szServerIP) != OK)
						return ;
					
					Clear();;
					SetScrFont(FONT20, WHITE);
					TextOut(0, 3, ALIGN_CENTER, "�����˿�");
					TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
					SetScrFont(FONT20, RED);
					ret = Input(7, 5, gTerm.tEthernet.szServerPort, 5, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
					if(ret != OK)
						return ;

					
					system("/usr/udhcp/udhcpc");
					Clear();
					TextOut(0, 5, ALIGN_CENTER, "���óɹ�");
					WaitKey(3000);
				}
				else if(ucKey == KEY_2)
				{
					gTerm.bAutoIP = FALSE;
					if(WriteData("test-term.dat", &gTerm, sizeof(T_TERM), 0) == FALSE)
					{
						Clear();                      
						SetScrFont(FONT20, WHITE);
						TextOut(0, 3, ALIGN_CENTER, "�����ļ�����"); 
						TextOut(0, 4, ALIGN_CENTER, "���Ժ�����"); 
						FailBeep();
						WaitKey(2000);
				    	//goto FAILED;
					}
					SetEthernet();
				}
				else if(ucKey == KEY_3)
					ViewIpSet();
				else if(ucKey == KEY_CANCEL)
					return ;
				break;
			case KEY_4:
				SetCDMA();
				break;	
            case KEY_5:
                while(1)
                   {
					Clear(); 
					TextOut(0, 3, ALIGN_CENTER, "��ѡ��WiFi���ӷ�ʽ");
					TextOut(0, 4, ALIGN_CENTER, "1.�ֶ�����");
					TextOut(0, 5, ALIGN_CENTER, "2.�Զ�����");

	                ucKey = WaitLimitKey("\x01\x02\x12", 8, 0);
	                if ('\x01' == ucKey)
	                	{
							gTerm.bAutoWifi = FALSE;
	                     	Set_Wifi();	
	                	}
	                if ('\x02' == ucKey)
	                	{
							gTerm.bAutoWifi = TRUE;
	                     	Set_Wifi_Auto();	
	                	}
	                if ('\x12' == ucKey)
                            break;
				}
                break;

		}
	}
}

int CommTest()
{
	UCHAR ucKey;
	char sKeyName[20];

	ClearKbd();
	while(1)
	{
		Clear();

		SetScrFont(FONT20, WHITE);

		//����
		//ShowBmpFile(0, 25, "pic/title.bmp");
		TextOutByPixel(100, 30, "ͨѶ����");

		//�˵�
		ShowBmpFile(30, 60, "pic/button.bmp");
		TextOutByPixel(45, 65, "1.���Ų���");

		ShowBmpFile(30, 95, "pic/button.bmp");
		TextOutByPixel(45, 100, "2.G������");

		ShowBmpFile(30, 130, "pic/button.bmp");
		TextOutByPixel(45, 135, "3.��̫��");
		
		ShowBmpFile(30, 165, "pic/button.bmp");
		TextOutByPixel(45, 170, "4.C������");
		
        ShowBmpFile(30, 200, "pic/button.bmp");
        TextOutByPixel(45, 205, "5.wifi����");

        ShowBmpFile(170, 60, "pic/button.bmp");
        TextOutByPixel(185, 65, "6.��������");

		ucKey = WaitLimitKey("\x01\x02\x03\x04\x05\x06\x12", 7, 0);
		memset(sKeyName, 0, sizeof(sKeyName));
		GetKeyName(ucKey, sKeyName);
		DebugOut("press key: %s\n", sKeyName);

		switch(ucKey)
		{
			case KEY_CANCEL:
				return OK;
				break;
			case KEY_1:
				ModemTest();
				break;
			case KEY_2:
				GprsTest();
				break;
			case KEY_3:
				EthernetTest();
				break;
			case KEY_4:
				CDMACommTest();
				break;	
            case KEY_5:
                WifiCommTest();
                break;
            case KEY_6:
                SetCommParam();
                break;

		}
	}
	return OK;
}


