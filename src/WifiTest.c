//////////////////////////////////////////////////////////////////////////////

#include "Main.h"

//////////////////////////////////////////////////////////////////////////////
// �ն�����

int Set_Wifi_Auto()
{
	char buff[1024+1]={0};
	char ssid1[32+1]={0};//SSID
	char ssid2[32+1]={0};//SSID
	char ssid3[32+1]={0};//SSID
	char ssid4[32+1]={0};//SSID
	char ssid5[32+1]={0};//SSID
	char ssid6[32+1]={0};//SSID
	char ssid7[32+1]={0};//SSID
	char ssid8[32+1]={0};//SSID
	char ssid9[32+1]={0};//SSID
	int ret;
	char ch;

    if (OK != HardWareInit())
    {
      Clear();
      printf( "��WIFI�˿�ʧ��\n");
      TextOut(0, 3, ALIGN_CENTER, "W��WIFI�˿�ʧ��");
      WaitKey(0);
    }
	switch_COM2(1);
	//�ŵ���

	Clear();
	
	TextOut(0, 3, ALIGN_CENTER, "����ɨ���������");
	Wifi_Auto_Init(ssid1, ssid2, ssid3, ssid4, ssid5, ssid6, ssid7, ssid8, ssid9);
    Clear();
   	TextOut(2, 2, ALIGN_LEFT,ssid1);
	TextOut(2, 3, ALIGN_LEFT,ssid2);
	TextOut(2, 4, ALIGN_LEFT,ssid3);
	TextOut(2, 5, ALIGN_LEFT,ssid4);
	TextOut(2, 6, ALIGN_LEFT,ssid5);
	TextOut(2, 7, ALIGN_LEFT,ssid6);
	TextOut(2, 8, ALIGN_LEFT,ssid7);
	TextOut(2, 9, ALIGN_LEFT,ssid8);
    TextOut(2, 10,ALIGN_LEFT,ssid9);
	ch = WaitLimitKey("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x12\x0F", 11, 0);
			
	while(1)
	{
		gTerm.t_Wifi.nEncrypType = 4;
		gTerm.t_Wifi.key_wep.KeyIndex = 0;
		
		if(ch == KEY_1)
		{
			//��������
			Clear();
			
			 memcpy(gTerm.t_Wifi.szSsid, ssid1, 32);		
			break;
		}
		else if(ch == KEY_2)
		{
			Clear();
			
			memcpy(gTerm.t_Wifi.szSsid, ssid2, 32);
			break;
		}
		else if(ch == KEY_3)
		{
			Clear();
			
			memcpy(gTerm.t_Wifi.szSsid, ssid3, 32);
			break;
		}
		else if(ch == KEY_4)
		{
			Clear();
			
			memcpy(gTerm.t_Wifi.szSsid, ssid4, 32);
			break;
		}
		else if(ch == KEY_5)
		{
			Clear();
			
			memcpy(gTerm.t_Wifi.szSsid, ssid5, 32);
			break;
		}
		else if(ch == KEY_6)
		{
			Clear();
			
			memcpy(gTerm.t_Wifi.szSsid, ssid6, 32);
			break;
		}
		else if(ch == KEY_7)
		{
			Clear();
			
			memcpy(gTerm.t_Wifi.szSsid, ssid7, 32);
			break;
		}
		else if(ch == KEY_8)
		{
			Clear();
			
			memcpy(gTerm.t_Wifi.szSsid, ssid8, 32);
			break;
		}
		else if(ch == KEY_9)
		{
			Clear();
			
			memcpy(gTerm.t_Wifi.szSsid, ssid9, 32);
			break;
		}
		else if(ch == KEY_CANCEL)
			goto FAILED;
		else if(ch == KEY_ENTER)
			break;
		else
			continue;		
	}
	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(2, 2, ALIGN_LEFT, "��������");
	TextOut(2, 3, ALIGN_LEFT, "Ŀǰ��ʽ: WPA-PSK(CCMP/AES)");
	TextOut(2, 4, ALIGN_LEFT, "������Կ");
	TextOut(2, 5, ALIGN_LEFT, "��: ");
	ret=Input(2,6,gTerm.t_Wifi.key_wep.Group[0], 14,IME_NUMBER, WHITE,RED,FALSE, FALSE, TRUE);
	if(ret != OK)
		goto FAILED;
		
	printf("=======%s================\n", gTerm.t_Wifi.key_wep.Group[0]);
	
	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "������IP��ַ");
	TextOut(0, 3, ALIGN_LEFT, "��: ");
	TextOut(0, 4, ALIGN_CENTER, gTerm.t_Wifi.szServerIP);
	TextOut(0, 5, ALIGN_LEFT, "��: ");
	SetScrFont(FONT20, RED);
	if(InputIP(10, 6,gTerm.t_Wifi.szServerIP) != OK)
	    	goto FAILED;
	    	
	printf("=======%s================\n", gTerm.t_Wifi.szServerIP);
		 
	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "����˿�");
	TextOut(0, 3, ALIGN_LEFT, "��: ");
	TextOut(3, 4, ALIGN_CENTER, gTerm.t_Wifi.szEquipmentPort);
	TextOut(0, 5, ALIGN_LEFT, "��: ");
	SetScrFont(FONT20, RED);
	memset(buff, 0, sizeof(buff));
	ret=Input(10,6,buff, 5,IME_NUMBER, WHITE,RED,FALSE, FALSE, FALSE);
	if(ret != OK)
	    	goto FAILED;
	if (strlen(buff) >= 4)
	{
		memcpy(gTerm.t_Wifi.szEquipmentPort, buff, 5);
	}
	printf("=======%s================\n", gTerm.t_Wifi.szEquipmentPort);

	if(WriteData("test-term.dat", &gTerm, sizeof(T_TERM), 0) == FALSE)
	{
		printf("�������\n");
		FailBeep();
		WaitKey(2000);
	 	return ERROR; 
	}
	SetScrFont(FONT20, WHITE);
	Clear();
    TextOut(2, 3, ALIGN_CENTER, "WIFI���ڳ�ʼ��...");
	printf("-----------------------���ڳ�ʼ��----------------\n");
	printf("-----------------------ymm---WIFIReset()----------------\n");
	if (0 > WIFIReset())
	{
		goto FAILED;
	}
	printf("-----------------------ymm---ProcessWIFIData()----------------\n");
	if (0 > ProcessWIFIData())
	{
		goto FAILED;
	}	
	printf("-----------------------ymm---Wifi_Para_set()----------------\n");
	
	ret = Wifi_Para_set_Auto(gTerm.t_Wifi);
	if(ret == ERROR_CONN)
	{
		Clear();
		OkBeep();
		TextOut(0, 3, ALIGN_CENTER, "WIFIͨѶ��Ϣ���óɹ�!");
		TextOut(0, 4, ALIGN_CENTER, "������POS��");
		WaitKey(4000);
		return OK;
	}
	else if(ret != OK)
	{
		goto FAILED;
	}
	
	Wait(1000);
	Clear();
	TextOut(0, 3, ALIGN_CENTER, "WIFI��ʼ���ɹ�");
	
	OkBeep();
	Clear();
	TextOut(0, 3, ALIGN_CENTER, "WIFIͨѶ��Ϣ���óɹ�!");
	WaitKey(4000);
	return OK;
	
FAILED:
	Beep();
	Clear();
	printf( "��ʼ��WIFIʧ��\n");
	TextOut(0, 3, ALIGN_CENTER, "WIFI��ʼ��ʧ��");
	WaitKey(3000);
	
	return ERROR;
	
}

int Set_Wifi()
{
	char buff[1024+1];
	int ret;
	char ch;

        if (OK != HardWareInit())
        {
               	Clear();
                printf( "��ʼ��WIFIʧ��\n");
                TextOut(0, 3, ALIGN_CENTER, "WIFI��ʼ��ʧ��");
                WaitKey(0);
        }
	switch_COM2(1);
	//�ŵ���
	Clear();
    	SetScrFont(FONT20, WHITE);
  	TextOut(0, 2, ALIGN_CENTER, "�ŵ���");
    	TextOut(0, 3, ALIGN_LEFT, "��ǰ�ŵ���: ");
	memset(buff, 0, sizeof(buff));
	sprintf(buff, "%d", gTerm.t_Wifi.nChannelNum);
    	TextOut(7, 4, ALIGN_CENTER, buff);
	TextOut(0, 5, ALIGN_LEFT, "���ŵ���: ");
	memset(buff, 0, sizeof(buff));
	ret=Input(7,6,buff,2,IME_NUMBER,WHITE,RED,FALSE, FALSE, TRUE);
	if(ret != OK)
    		goto FAILED;
	if (atoi(buff) > 0 && atoi(buff) < 15)
	{
		gTerm.t_Wifi.nChannelNum = atoi(buff);
	}else
    	{
		Clear();
		TextOut(0, 5, ALIGN_CENTER, "�ŵ��Ų��ڷ�Χ֮�� ");
		WaitKey(3000);
		goto FAILED;
	}
	printf("=======%d================\n", gTerm.t_Wifi.nChannelNum);
	
	
	//BSSID
	Clear();
    	SetScrFont(FONT20, WHITE);
  	TextOut(0, 2, ALIGN_CENTER, "BSSID");
    	TextOut(0, 3, ALIGN_LEFT, "��: ");
    	TextOut(0, 4, ALIGN_CENTER, gTerm.t_Wifi.szBssid);
	TextOut(0, 5, ALIGN_LEFT, "��: ");
	memset(buff, 0, sizeof(buff));
	ret=Input(0,6,buff,12 ,IME_NUMBER,WHITE,RED,FALSE, FALSE, TRUE);
	if(ret != OK)
    	goto FAILED;
	if (strlen(buff) > 0)
	{
		memcpy(gTerm.t_Wifi.szBssid, buff, 12);
	}
	printf("=======%s================\n", gTerm.t_Wifi.szBssid);

	//SSID
	Clear();
    	SetScrFont(FONT20, WHITE);
  	TextOut(0, 2, ALIGN_CENTER, "SSID");
    	TextOut(0, 3, ALIGN_LEFT, "��: ");
    	TextOut(0, 4, ALIGN_CENTER, gTerm.t_Wifi.szSsid);
	TextOut(0, 5, ALIGN_LEFT, "��: ");
	memset(buff, 0, sizeof(buff));
	ret=Input(0,6,buff,32,IME_NUMBER,WHITE,RED,FALSE, FALSE, TRUE);
	if(ret != OK)
    	goto FAILED;
	if (strlen(buff) > 0)
	{
		memcpy(gTerm.t_Wifi.szSsid, buff, 32);
	}
	printf("=======%s================\n", gTerm.t_Wifi.szSsid);

	//��·�����ݸ�ʽ
	Clear();
	TextOut(0, 1, ALIGN_CENTER, "��·�����ݸ�ʽ");
	if(gTerm.t_Wifi.nDatalink == 0)
		TextOut(0, 2, ALIGN_CENTER, "Ŀǰ��ʽ: RAW");
	else if(gTerm.t_Wifi.nDatalink == 1)
		TextOut(0, 2, ALIGN_CENTER, "Ŀǰ��ʽ: UDP");
	else if(gTerm.t_Wifi.nDatalink == 2)
		TextOut(0, 2, ALIGN_CENTER, "Ŀǰ��ʽ: TCP");
	else
		TextOut(0, 2, ALIGN_CENTER, "Ŀǰ��ʽ: δ֪");
	TextOut(0, 3, ALIGN_CENTER, " 1.RAW");
	TextOut(0, 4, ALIGN_CENTER, " 2.UDP");
	TextOut(0, 5, ALIGN_CENTER, " 3.TCP");

	ch = WaitLimitKey("\x01\x02\x03\x12\x0F", 5, 0);
			
	while(1)
	{
		
		if(ch == KEY_1)
		{
			gTerm.t_Wifi.nDatalink =0;
			break;
		}
		else if(ch == KEY_2)
		{
			gTerm.t_Wifi.nDatalink =1;
			break;
		}
		else if(ch == KEY_3)
		{
			gTerm.t_Wifi.nDatalink =2;
			break;
		}
		else if(ch == KEY_CANCEL)
			goto FAILED;
		else if(ch == KEY_ENTER)
			break;
		else
			continue;		
	}
	printf("=======%d================\n", gTerm.t_Wifi.nDatalink);
	Clear();
    	SetScrFont(FONT20, WHITE);
    	TextOut(0, 2, ALIGN_CENTER, "�豸IP��ַ");
    	TextOut(0, 3, ALIGN_LEFT, "��: ");
	TextOut(0, 4, ALIGN_CENTER, gTerm.t_Wifi.szEquipmentIP);
	TextOut(0, 5, ALIGN_LEFT, "��: ");
	SetScrFont(FONT20, RED);
	//memset(buff, 0, sizeof(buff));
	if(InputIP(10, 6, gTerm.t_Wifi.szEquipmentIP) != OK)
		goto FAILED;
	/*if (strlen(buff) > 12)
	{
		memcpy(gTerm.t_Wifi.szEquipmentIP, buff, 15);
	}*/
	printf("=======%s================\n", gTerm.t_Wifi.szEquipmentIP);
	Clear();
    	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "��������");
	TextOut(0, 3, ALIGN_LEFT, "��: ");
	TextOut(3, 4, ALIGN_LEFT, gTerm.t_Wifi.szServerMask);
	TextOut(0, 5, ALIGN_LEFT, "��: ");
	SetScrFont(FONT20, RED);
	//memset(buff, 0, sizeof(buff));
	if(InputIP(10, 6, gTerm.t_Wifi.szServerMask) != OK)
	    	goto FAILED;
	/*if (strlen(buff) > 12)
	{
		memcpy(gTerm.t_Wifi.szServerMask, buff, 15);
	}*/
	printf("=======%s================\n", gTerm.t_Wifi.szServerMask);
			
	Clear();
    	SetScrFont(FONT20, WHITE);
    	TextOut(0, 2, ALIGN_CENTER, "����IP��ַ");
	TextOut(0, 3, ALIGN_LEFT, "��: ");
	TextOut(3, 4, ALIGN_LEFT, gTerm.t_Wifi.szServerGateway);
	TextOut(0, 5, ALIGN_LEFT, "��: ");
	//memset(buff, 0, sizeof(buff));
	SetScrFont(FONT20, RED);
	if(InputIP(10, 6, gTerm.t_Wifi.szServerGateway) != OK)
		goto FAILED;
	/*if (strlen(buff) > 12)
	{
		memcpy(gTerm.t_Wifi.szServerGateway, buff, 15);
	}*/
	printf("=======%s================\n", gTerm.t_Wifi.szServerGateway);
	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "������IP��ַ");
	TextOut(0, 3, ALIGN_LEFT, "��: ");
	TextOut(0, 4, ALIGN_CENTER, gTerm.t_Wifi.szServerIP);
	TextOut(0, 5, ALIGN_LEFT, "��: ");
	SetScrFont(FONT20, RED);
	//memset(buff, 0, sizeof(buff));
	if(InputIP(10, 6,gTerm.t_Wifi.szServerIP) != OK)
	    	goto FAILED;
	/*if (strlen(buff) > 12)
	{
		memcpy(gTerm.t_Wifi.szServerIP, buff, 15);
	}*/
	printf("=======%s================\n", gTerm.t_Wifi.szServerIP);
		 
	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "����˿�");
	TextOut(0, 3, ALIGN_LEFT, "��: ");
	TextOut(3, 4, ALIGN_CENTER, gTerm.t_Wifi.szEquipmentPort);
	TextOut(0, 5, ALIGN_LEFT, "��: ");
	SetScrFont(FONT20, RED);
	memset(buff, 0, sizeof(buff));
	ret=Input(10,6,buff, 5,IME_NUMBER, WHITE,RED,FALSE, FALSE, FALSE);
	if(ret != OK)
	    	goto FAILED;
	if (strlen(buff) >= 4)
	{
		memcpy(gTerm.t_Wifi.szEquipmentPort, buff, 5);
	}
	printf("=======%s================\n", gTerm.t_Wifi.szEquipmentPort);
	//��������
	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 1, ALIGN_CENTER, "��������");
	if(gTerm.t_Wifi.nEncrypType == 0)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ��ʽ: OPEN");
	else if(gTerm.t_Wifi.nEncrypType == 1)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ��ʽ: WEP64");
	else if(gTerm.t_Wifi.nEncrypType == 2)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ��ʽ: WEP128");
	else if(gTerm.t_Wifi.nEncrypType == 3)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ��ʽ: WPA-PSK(TKIP)");
	else if(gTerm.t_Wifi.nEncrypType == 4)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ��ʽ: WPA-PSK(CCMP/AES)");
	else if(gTerm.t_Wifi.nEncrypType == 5)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ��ʽ: WPA2-PSK(TKIP)");
	else if(gTerm.t_Wifi.nEncrypType == 6)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ��ʽ: WPA2-PSK(CCMP/AES)");
	else
		TextOut(0, 2, ALIGN_CENTER, "Ŀǰ��ʽ: δ֪");
	TextOut(0, 3, ALIGN_LEFT, " 1.OPEN");
	TextOut(0, 4, ALIGN_LEFT, " 2.WEP64 ");
	TextOut(0, 5, ALIGN_LEFT, " 3.WEP128 ");
	TextOut(0, 6, ALIGN_LEFT, " 4.WPA-PSK(TKIP) ");
	TextOut(0, 7, ALIGN_LEFT, " 5.WPA-PSK(CCMP/AES)");
	TextOut(0, 8, ALIGN_LEFT, " 6.WPA2-PSK(TKIP) ");
	TextOut(0, 9, ALIGN_LEFT, " 7.WPA2-PSK(CCMP/AES)");

	ch = WaitLimitKey("\x01\x02\x03\x04\x05\x06\x07\x12\x0F", 9, 0);
		
	while(1)
	{
		if(ch == KEY_1)
		{
			gTerm.t_Wifi.nEncrypType =0;
			break;
		}
		else if(ch == KEY_2)
		{
			gTerm.t_Wifi.nEncrypType =1;
			break;
		}
		else if(ch == KEY_3)
		{
			gTerm.t_Wifi.nEncrypType =2;
			break;
		}
		else if(ch == KEY_4)
		{
			gTerm.t_Wifi.nEncrypType =3;
			break;
		}
		else if(ch == KEY_5)
		{
			gTerm.t_Wifi.nEncrypType =4;
			break;
		}
		else if(ch == KEY_6)
		{
			gTerm.t_Wifi.nEncrypType =5;
			break;
		}
		else if(ch == KEY_7)
		{
			gTerm.t_Wifi.nEncrypType =6;
			break;
		}
		else if(ch == KEY_CANCEL)
			goto FAILED;
		else if(ch == KEY_ENTER)
			break;
		else
			continue;		
	}
	printf("=======%d================\n", gTerm.t_Wifi.nEncrypType);

	if (gTerm.t_Wifi.nEncrypType == 1)
	{
		// ѡ����Կ��
		Clear();
    		SetScrFont(FONT20, WHITE);
  		TextOut(0, 1, ALIGN_CENTER, "��Կ����");
		if(gTerm.t_Wifi.key_wep.KeyIndex == 0)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ����: ��һ��");
		else if(gTerm.t_Wifi.key_wep.KeyIndex == 1)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ����: �ڶ���");
		else if(gTerm.t_Wifi.key_wep.KeyIndex == 2)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ����: ������");
		else if(gTerm.t_Wifi.key_wep.KeyIndex == 3)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ����: ������");
		else
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ����: δ֪");
		TextOut(0, 3, ALIGN_CENTER, "1.��һ��");
		TextOut(0, 4, ALIGN_CENTER, "2.�ڶ���");
		TextOut(0, 5, ALIGN_CENTER, "3.������");
		TextOut(0, 6, ALIGN_CENTER, "4.������");

		ch = WaitLimitKey("\x01\x02\x03\x04\x12\x0F", 4, 0);
			
		while(1)
		{
			if(ch == KEY_1)
			{
				gTerm.t_Wifi.key_wep.KeyIndex =0;
				break;
			}
			else if(ch == KEY_2)
			{
				gTerm.t_Wifi.key_wep.KeyIndex =1;
				break;
			}
			else if(ch == KEY_3)
			{
				gTerm.t_Wifi.key_wep.KeyIndex =2;
				break;
			}
			else if(ch == KEY_4)
			{
				gTerm.t_Wifi.key_wep.KeyIndex =3;
				break;
			}
			else if(ch == KEY_CANCEL)
				goto FAILED;
			else if(ch == KEY_ENTER)
				break;
			else
				continue;		
		}
		printf("=======%d================\n", gTerm.t_Wifi.key_wep.KeyIndex);
		Clear();
		TextOut(0, 5, ALIGN_LEFT, "��: ");
		SetScrFont(FONT20, RED);
		memset(buff, 0, sizeof(buff));
		ret=Input(3,6,buff, 10,IME_NUMBER, WHITE,RED,FALSE, FALSE, TRUE);
		if(ret != OK)
			goto FAILED;
		printf("=======%s================\n", buff);
		memset(gTerm.t_Wifi.key_wep.Group[gTerm.t_Wifi.key_wep.KeyIndex], 0x00, 13);
		memcpy(buff,gTerm.t_Wifi.key_wep.Group[gTerm.t_Wifi.key_wep.KeyIndex], 13);

	}
	else if (gTerm.t_Wifi.nEncrypType == 2)
	{
		// ѡ����Կ��
		Clear();
    		SetScrFont(FONT20, WHITE);
  		TextOut(0, 1, ALIGN_CENTER, "��Կ����");
		if(gTerm.t_Wifi.key_wep.KeyIndex == 0)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ����: ��һ��");
		else if(gTerm.t_Wifi.key_wep.KeyIndex == 1)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ����: �ڶ���");
		else if(gTerm.t_Wifi.key_wep.KeyIndex == 2)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ����: ������");
		else if(gTerm.t_Wifi.key_wep.KeyIndex == 3)
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ����: ������");
		else
			TextOut(0, 2, ALIGN_CENTER, "Ŀǰ����: δ֪");
		TextOut(0, 3, ALIGN_CENTER, "1.��һ��");
		TextOut(0, 4, ALIGN_CENTER, "2.�ڶ���");
		TextOut(0, 5, ALIGN_CENTER, "3.������");
		TextOut(0, 6, ALIGN_CENTER, "4.������");

		ch = WaitLimitKey("\x01\x02\x03\x04\x12\x0F", 4, 0);
			
		while(1)
		{
			if(ch == KEY_1)
			{
				gTerm.t_Wifi.key_wep.KeyIndex =0;
				break;
			}
			else if(ch == KEY_2)
			{
				gTerm.t_Wifi.key_wep.KeyIndex =1;
				break;
			}
			else if(ch == KEY_3)
			{
				gTerm.t_Wifi.key_wep.KeyIndex =2;
				break;
			}
			else if(ch == KEY_4)
			{
				gTerm.t_Wifi.key_wep.KeyIndex =3;
				break;
			}
			else if(ch == KEY_CANCEL)
				goto FAILED;
			else if(ch == KEY_ENTER)
				break;
			else
				continue;		
		}
		printf("=======%d================\n", gTerm.t_Wifi.key_wep.KeyIndex);
		Clear();
		TextOut(0, 5, ALIGN_LEFT, "��: ");
		SetScrFont(FONT20, RED);
		memset(buff, 0, sizeof(buff));
		ret=Input(3,6,buff, 13,IME_NUMBER, WHITE,RED,FALSE, FALSE, TRUE);
		if(ret != OK)
			goto FAILED;
		printf("=======%s================\n", buff);
		memset(gTerm.t_Wifi.key_wep.Group[gTerm.t_Wifi.key_wep.KeyIndex], 0x00, 13);
		memcpy(buff,gTerm.t_Wifi.key_wep.Group[gTerm.t_Wifi.key_wep.KeyIndex], 13);
	}
	else if (gTerm.t_Wifi.nEncrypType == 3)
	{
		//memcpy(gTerm.t_Wifi.key_wep.KeyIndex, "0", 1);
		gTerm.t_Wifi.key_wep.KeyIndex = '0';
		Clear();
    		SetScrFont(FONT20, WHITE);
		TextOut(0, 2, ALIGN_CENTER, "������Կ");
		TextOut(0, 3, ALIGN_LEFT, "��: ");
		ret=Input(3,4,gTerm.t_Wifi.key_wep.Group[0], 13,IME_NUMBER, WHITE,RED,FALSE, FALSE, TRUE);
		if(ret != OK)
			goto FAILED;
		printf("=======%s================\n", gTerm.t_Wifi.key_wep.Group[0]);
	}
	else if (gTerm.t_Wifi.nEncrypType == 4)
	{
		gTerm.t_Wifi.key_wep.KeyIndex = 0;;
		Clear();
    		SetScrFont(FONT20, WHITE);
		TextOut(0, 2, ALIGN_CENTER, "������Կ");
		TextOut(0, 3, ALIGN_LEFT, "��: ");
		ret=Input(3,4,gTerm.t_Wifi.key_wep.Group[0], 13,IME_NUMBER, WHITE,RED,FALSE, FALSE, TRUE);
		if(ret != OK)
			goto FAILED;
		printf("=======%s================\n", gTerm.t_Wifi.key_wep.Group[0]);
	}
	else if (gTerm.t_Wifi.nEncrypType == 5)
	{

		gTerm.t_Wifi.key_wep.KeyIndex = 0;;
		Clear();
    		SetScrFont(FONT20, WHITE);
		TextOut(0, 2, ALIGN_CENTER, "������Կ");
		TextOut(0, 3, ALIGN_LEFT, "��: ");
		ret=Input(3,4,gTerm.t_Wifi.key_wep.Group[0], 13,IME_NUMBER, WHITE,RED,FALSE, FALSE, TRUE);
		if(ret != OK)
			goto FAILED;
		printf("=======%s================\n", gTerm.t_Wifi.key_wep.Group[0]);
	}
	else if (gTerm.t_Wifi.nEncrypType == 6)
	{
		gTerm.t_Wifi.key_wep.KeyIndex = 0;;
		Clear();
    		SetScrFont(FONT20, WHITE);
		TextOut(0, 2, ALIGN_CENTER, "������Կ");
		TextOut(0, 3, ALIGN_LEFT, "��: ");
		ret=Input(3,4,gTerm.t_Wifi.key_wep.Group[0], 13,IME_NUMBER, WHITE,RED,FALSE, FALSE, TRUE);
		if(ret != OK)
			goto FAILED;
		printf("=======%s================\n", gTerm.t_Wifi.key_wep.Group[0]);
	}
	//�����ļ�
	if(WriteData("test-term.dat", &gTerm, sizeof(T_TERM), 0) == FALSE)
	{
		Clear();                      
		TextOut(0, 2, ALIGN_CENTER, "�����ļ�����"); 
		TextOut(0, 3, ALIGN_CENTER, "���Ժ�����");
		FailBeep();
		WaitKey(2000);
    		goto FAILED;
	}

	Clear();
    TextOut(0, 3, ALIGN_CENTER, "WIFI���ڳ�ʼ��...");
	printf("-----------------------ymm---WIFIReset()----------------\n");
	if (0 > WIFIReset())
	{
		goto FAILED;
	}
	printf("-----------------------ymm---ProcessWIFIData()----------------\n");
	if (0 > ProcessWIFIData())
	{
		goto FAILED;
	}	
	printf("-----------------------ymm---Wifi_Para_set()----------------\n");
    ret = Wifi_Para_set(gTerm.t_Wifi);
    if(ret == ERROR_CONN)
    {
		Clear();
		OkBeep();
		TextOut(0, 3, ALIGN_CENTER, "WIFIͨѶ��Ϣ���óɹ�!");
		TextOut(0, 4, ALIGN_CENTER, "������POS��");
		WaitKey(4000);
		return OK;
    }else if(ret != OK)
    {
		goto FAILED;
	}

	Wait(1000);
	Clear();
	TextOut(0, 3, ALIGN_CENTER, "WIFI��ʼ���ɹ�");

	OkBeep();
	Clear();
	TextOut(0, 3, ALIGN_CENTER, "WIFIͨѶ��Ϣ���óɹ�!");
	WaitKey(4000);
	return OK;

FAILED:
    Beep();
	Clear();
    printf( "��ʼ��WIFIʧ��\n");
    TextOut(0, 3, ALIGN_CENTER, "WIFI��ʼ��ʧ��");
	WaitKey(3000);

	return ERROR;
}

void WifiCommTest()
{ 
	char    szBuff[1024];
	char    szDataSnd[1024];
	int     ret, nSndLen;  
	char    buff[30], buff1[30];
	unsigned long ulTrace;
	int     i, num;
	char    szTmpBuff[100];
	UINT tempNum = gTerm.uiWifiDataNum; 
	char *pNum = (char *)&tempNum;

	switch_COM2(1);
        if (OK != HardWareInit())
        {
               	Clear();
                printf( "��ʼ��WIFIʧ��\n");
                TextOut(0, 3, ALIGN_CENTER, "WIFI��ʼ��ʧ��");
                WaitKey(0);
        }

	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "WIFI����");

	TextOut(2, 4, ALIGN_LEFT, "������ͨѶ����:");
	memset(buff, 0, sizeof(buff));
	SetScrFont(FONT20, RED);
	ret = Input(18, 4, buff, 4, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
	if(ret == CANCEL)
		return;
	else if(ret != OK)
	{
		Clear();
		SetScrFont(FONT20, WHITE);
		TextOut(0, 4, ALIGN_CENTER, "����ʧ��"); 
		FailBeep();
		WaitKey(2000);
		return;
	}
	num = atoi(buff);
	DebugOut("ͨѶ����:[%d]\n", num);


	//ETHER
	SetScrFont(FONT20, WHITE);	
	memset(szDataSnd, 0, sizeof(szDataSnd));  
	tempNum += 5;
	szDataSnd[0] = pNum[1];
	szDataSnd[1] = pNum[0];
	memcpy(szDataSnd+2, "\x60\x01\x80\x00\x00\x45\x54\x48\x45\x52\x00\x00\xc0\x00\x10\x91\x00\x00\x00\x00\x00\x31\x32\x33\x34\x35\x36\x37\x39\x31\x32\x33\x34\x35\x36\x37\x38\x39\x30\x31\x32\x33\x34\x35\x01\x45\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x44\x2d\x30\x38\x30\x34\x31\x36\x2d\x46\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x31",
	gTerm.uiWifiDataNum+5);
	nSndLen = gTerm.uiWifiDataNum+7;

	for (i = 0; i < num; i ++)
	{   
		Clear();
		TextOut(0, 4, ALIGN_CENTER, "��������....");
		ret = WIFI_Connect();
		if(ret < 0)
		{
			Clear();
			TextOut(0, 4, ALIGN_CENTER, "��������ʧ��!");
			FailBeep(); 
			sprintf(szTmpBuff, "--WIFI������-%d--", i+1);
			PrintLog(szTmpBuff, "��������ʧ��!!!!!!!!");         
			if(WaitKey(100) == KEY_CANCEL)
				return;
			else
				continue;  
		}
		printf("--------------------���ӳɹ�----------------\n");

		Clear();
		TextOut(0, 4, ALIGN_CENTER, "��������....");
		memset(buff, 0, sizeof(buff));
		sprintf(buff, "��[%d]��ͨѶ", i+1);
		TextOut(0, 5, ALIGN_CENTER, buff);

		memset(buff, 0, sizeof(buff));
		BcdToAsc(buff, szDataSnd+20, 6, 0);    
		ulTrace = atol(buff);
		ulTrace ++;
		if(ulTrace >= 999999L)
			ulTrace = 1;
		memset(buff, 0, sizeof(buff));
		sprintf(buff, "%06ld", ulTrace); 
		memset(buff1, 0, sizeof(buff1));
		AscToBcd(buff1, buff, 6, 0);
		memcpy(szDataSnd+20, buff1, 3);

		DebugOut("��������[%d]:\n", nSndLen);
		printf_x("", szDataSnd, nSndLen);

		ret = WIFI_Send(szDataSnd, nSndLen);
		if(ret < 0)
		{
			WIFI_Close();
			Clear();
			TextOut(0, 4, ALIGN_CENTER, "��������ʧ��!");
			FailBeep();
			sprintf(szTmpBuff, "--WIFI������-%d--", i+1);
			PrintLog(szTmpBuff, "��������ʧ��!!!!!!!!");                     
			if(WaitKey(100) == KEY_CANCEL)
				return;
			else
				continue;
		}
		printf("--------------------���ͳɹ�----------------\n");

		Clear();
		TextOut(0, 4, ALIGN_CENTER, "��������....");
		memset(buff, 0, sizeof(buff));
		sprintf(buff, "��[%d]��ͨѶ", i+1);
		TextOut(0, 5, ALIGN_CENTER, buff);
		memset(szBuff, 0, sizeof(szBuff)); 
		ret = WIFI_Recv(szBuff, &nSndLen);
		if(ret < 0) 
		{
			WIFI_Close();
			Clear();
			TextOut(0, 4, ALIGN_CENTER, "��������ʧ��!");
			FailBeep(); 
			sprintf(szTmpBuff, "--WIFI������-%d--", i+1);
			PrintLog(szTmpBuff, "��������ʧ��!!!!!!!!");                       
			if(WaitKey(100) == KEY_CANCEL)
				return;
			else
				continue;  
		}
		printf("--------------------���ճɹ�----------------\n");
		WIFI_Close();

		DebugOut("��������[%d]:\n", nSndLen);
		printf_x("", szBuff, nSndLen);

		memset(buff, 0, sizeof(buff)); 
		memcpy(buff, szBuff+7, 5); 
		if(memcmp(buff, "ETHER", 5) != 0)
		{
			DebugOut("get=[%s]\n", buff);
			FailBeep();
			Clear();
			TextOut(0, 4, ALIGN_CENTER, "�������ݰ�����!");
			sprintf(szTmpBuff, "--WIFI������-%d--", i+1);
			PrintLog(szTmpBuff, "�������ݰ�����!");     
			if(WaitKey(100) == KEY_CANCEL)
				return;
			else
				continue; 
		}

		OkBeep();
		Clear();
		TextOut(0, 4, ALIGN_CENTER, "WIFI��ͨѶ�ɹ�!");
		sprintf(szTmpBuff, "--WIFI������-%d--", i+1);
		PrintLog(szTmpBuff, "WIFI��ͨѶ�ɹ�");     
		if(WaitKey(1000) == KEY_CANCEL)
			return;
		else
			continue; 
	}

	return;
}






