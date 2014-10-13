#include "Main.h"


void ModemTest()
{ 
	char szTmp[50], szTpdu[12];
	char szTmpBuff[50];
	char szDataSnd[1024+1], szDataRcv[1024+1];
	int  nSndLen, nRcvLen;
	int  i, nRet, CommCount;
	char buff[50];
	int ret;

	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "���Ų���");

	memcpy(szTmp, "6000080000", 10);
	memcpy(szTmp+2, gTerm.szTPDU, 4);
	memset(szTpdu,0,sizeof(szTpdu));  	
	AscToBcd(szTpdu, szTmp, 10, 0);

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
	CommCount = atoi(buff);
	DebugOut("ͨѶ����:[%d]\n", CommCount);

	//if(SwitchCom0_Modem()!=0)
	if(SwitchCom2_Modem()!=0)
		printf("switch com0 fail.\n");
    Wait(10);
	//��modem
    PowerModem(1);
    Wait(10);
    ModemReset();

	for(i = 0; i < CommCount; i ++)
	{  
		//����ͨѶ��·
		ClearLine(1, 10);  
		SetScrFont(FONT20, WHITE);
		TextOut(0, 4, ALIGN_CENTER, "���ڲ���...");
		nRet = Modem_Connect(gTerm.bOut, gTerm.szOutNo, gTerm.delay_times, gTerm.szTelNo, NULL, NULL);
		if(nRet != 0)
		{
			ClearLine(1, 10);  
			TextOut(0, 4, ALIGN_CENTER, "����ʧ��!");
			PrintLog("MODEM����:", "����ʧ��");
			DialOff();
			if(WaitLimitKey("\x0F\x12", 2, 1000) == KEY_CANCEL)
				break;
			continue;
		}
		PrintLog("----MODEM����:----", "���ųɹ�");

		memset(szDataSnd, 0, sizeof(szDataSnd));
		memcpy(szDataSnd, szTpdu, 5);
		nSndLen = 5;

		//MODEM
		memcpy(szDataSnd+5, "\x4D\x4F\x44\x45\x4D\x00\x00\xc0\x00\x10\x91\x00\x00\x00\x00\x00\x31\x32\x33\x34\x35\x36\x37\x39\x31\x32\x33\x34\x35\x36\x37\x38\x39\x30\x31\x32\x33\x34\x35\x01\x45\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x44\x2d\x30\x38\x30\x34\x31\x36\x2d\x46\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x31",  186 );
		nSndLen += gTerm.uiModemDataNum;

		//��������
		ClearLine(1, 10);
		TextOut(0, 4, ALIGN_CENTER, "��������...");
		memset(buff, 0, sizeof(buff));
		sprintf(buff, "��[%d]��ͨѶ", i+1);
		TextOut(0, 5, ALIGN_CENTER, buff);

		nRet = Modem_Send(szDataSnd, nSndLen);
		if(nRet != 0)
		{
			FailBeep();
			ClearLine(1, 10);  
			TextOut(0, 4, ALIGN_CENTER, "��������ʧ��");
			sprintf(szTmpBuff, "--���Ų���-%d--", i+1);
			PrintLog(szTmpBuff, "��������ʧ��!!!!!!!!!");

			if(WaitKey(100) == KEY_CANCEL)
				break;

			DialOff_Block();
			continue; 
		}

		ClearLine(1, 10);  

		//���շ�������
		TextOut(0, 4, ALIGN_CENTER, "��������...");
		memset(buff, 0, sizeof(buff));
		sprintf(buff, "��[%d]��ͨѶ", i+1);
		TextOut(0, 5, ALIGN_CENTER, buff);
		memset(szDataRcv,   0,   sizeof(szDataRcv));  
		nRcvLen = 0;  
		nRet = Modem_Recv(szDataRcv, &nRcvLen);  
		if(nRet != 0)
		{        
			FailBeep(); 
			ClearLine(1, 10);  
			TextOut(0, 4, ALIGN_CENTER, "��������ʧ��");
			sprintf(szTmpBuff, "--���Ų���-%d--", i+1);
			PrintLog(szTmpBuff, "��������ʧ��!!!!!!!!!");

			if(WaitKey(2000) == KEY_CANCEL)
				break; 

			DialOff_Block();
			continue; 
		} 

		if(nRcvLen < 5)
		{	      
			FailBeep(); 
			ClearLine(1, 10);  
			TextOut(0, 4, ALIGN_CENTER, "�������ݳ���<5��");
			sprintf(szTmpBuff, "--���Ų���-%d--", i+1);
			PrintLog(szTmpBuff, "�������ݳ���<5��");
			if(WaitKey(100) == KEY_CANCEL)
				break;
			DialOff_Block();
			continue; 
		}   

		memset(buff, 0, sizeof(buff)); 
		memcpy(buff, szDataRcv+5, 5); 
		if(memcmp(buff, "MODEM", 5) != 0)
		{ 
			FailBeep();
			ClearLine(1, 10);  
			TextOut(0, 4, ALIGN_CENTER, "�������ݰ�����!");
			sprintf(szTmpBuff, "--���Ų���-%d--", i+1);
			PrintLog(szTmpBuff, "�������ݰ�����!");     
			if(WaitKey(2000) == KEY_CANCEL)
				return;
			else
			{
				DialOff_Block();
				continue; 
			}
		}

		OkBeep();
		ClearLine(1, 10);  
		TextOut(0, 4, ALIGN_CENTER, "����ͨѶ�ɹ�!");
		sprintf(szTmpBuff, "--���Ų���-%d--", i+1);
		PrintLog(szTmpBuff, "����ͨѶ�ɹ�");

		DialOff_Block();

		if(WaitKey(1000) == KEY_CANCEL)
			break;

		continue;  
	}
	//�ر�modem
    PowerModem(0);

	return;	
}



