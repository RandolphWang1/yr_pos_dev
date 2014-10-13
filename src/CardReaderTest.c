#include "Main.h"

 
static void PrintLogMagic(char *Msg1, char *Msg2, char *Msg3)
{ 
	int ret;
	char PrintBuff[1024];

	if(CheckPrinter() != TRUE)
		goto end;

	//��մ�ӡ������
	ClearPrintBuff();
	//���ô�ӡ�����С
    SetPrintFont(24);

    SetPrintIndent(0); 

    ret = FillPrintBuff("PL");
    if(ret < 0)
		goto end;

	if (Msg1[0] != 0x00)    
	{        
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "һ�ŵ�����:");
		ret = FillPrintBuff(PrintBuff);
		if(ret<0)
			goto end;             
		ret = FillPrintBuff("PL");
		if(ret<0)
			goto end;
		SetPrintIndent(0); 

		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, Msg1);
		ret = FillPrintBuff(PrintBuff);
		if (ret<0)
			goto end;            
		ret = FillPrintBuff("PL");
		if(ret<0)
			goto end;
		SetPrintIndent(0); 
	}

	if (Msg2[0] != 0x00)    
	{        
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "���ŵ�����:");
		ret = FillPrintBuff(PrintBuff);
		if(ret<0)
			goto end;             
		ret = FillPrintBuff("PL");
		if(ret<0)
			goto end;
		SetPrintIndent(0); 

		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, Msg2);
		ret = FillPrintBuff(PrintBuff);
		if (ret<0)
			goto end;            
		ret = FillPrintBuff("PL");
		if(ret<0)
			goto end;
		SetPrintIndent(0); 
	}

	if (Msg3[0] != 0x00)    
	{        
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "���ŵ�����:");
		ret = FillPrintBuff(PrintBuff);
		if(ret<0)
			goto end;             
		ret = FillPrintBuff("PL");
		if(ret<0)
			goto end;
		SetPrintIndent(0); 

		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, Msg3);
		ret = FillPrintBuff(PrintBuff);
		if (ret<0)
			goto end;            
		ret = FillPrintBuff("PL");
		if(ret<0)
			goto end;
		SetPrintIndent(0); 
	}

	ret = FillPrintBuff("         ˢ���ɹ�");
	if(ret<0)
		goto end;             
	ret = FillPrintBuff("PL");
	if(ret<0)
		goto end;
	SetPrintIndent(0); 
	ret = FillPrintBuff("PL");
	if(ret<0)
		goto end;
	ret = FillPrintBuff("PL");
	if(ret<0)
		goto end;
	ret = FillPrintBuff("PL");
	if(ret<0)
		goto end;

	SetPrintIndent(0);  

	//��ʼ��ӡ    
	ret =StartPrint();
	if(ret != 0)
		goto end;

	return;

end:  
	OkBeep(); 
	Clear();
	TextOut(0, 3, ALIGN_CENTER, "�����ӡ��");
	TextOut(0, 4, ALIGN_CENTER, "��ӡʧ��");
	WaitKey(3000);

	return;
}

void MagCardTest()
{
	int  nRet;
	char Track1[200], Track2[200], Track3[200];
	int track1_len, track2_len, track3_len;
	int  printflg;

	#define	TRACK1_OK		0x0001
	#define	TRACK2_OK		0x0002
	#define	TRACK3_OK		0x0004

	Clear();

	if(MagOpen() != 0)
	{
		DebugOut("open mgc error\n");
		Clear();
		TextOut(0, 4, ALIGN_CENTER, "�򿪴�ͷʧ��!");
		WaitKey(2000);
		return;
	} 

	TextOut(0, 2, ALIGN_CENTER, "��������������");
	TextOut(0, 4, ALIGN_CENTER, "��ˢ�ſ� ---->");
	TextOut(0, 7, ALIGN_CENTER, "ȡ�����˳�");

	while(1)
	{ 
		memset(Track1, 0x00, sizeof(Track1)); 
		memset(Track2, 0x00, sizeof(Track2)); 
		memset(Track3, 0x00, sizeof(Track3)); 
		printflg = 0;
		nRet = MagRead(&track1_len, Track1, &track2_len, Track2, &track3_len, Track3);
		if(nRet > 0)
		{
			OkBeep();
			Clear();
			if(nRet & TRACK1_OK)   //�е�һ�ŵ�
			{
				TextOut(0, 2, ALIGN_CENTER, "һ�ŵ�����:");
				if (track1_len > 32)
				{
					TextOut(0, 3, ALIGN_CENTER, "���ݹ���,������ʾ");
					Track1[32] = '\x00';
					TextOut(0, 4, ALIGN_CENTER, Track1);
				}
				else
				{
					TextOut(0, 3, ALIGN_CENTER, Track1);
				}
				printf("track1 data:\n%s\n", Track1);
				printflg = 1;
			}
			if(nRet & TRACK2_OK)
			{
				TextOut(0, 5, ALIGN_CENTER, "���ŵ�����:");
				if (track2_len > 32)
				{
					TextOut(0, 6, ALIGN_CENTER, "���ݹ���,������ʾ");
					Track2[32] = '\x00';
					TextOut(0, 7, ALIGN_CENTER, Track2);
				}
				else
				{
					TextOut(0, 6, ALIGN_CENTER, Track2);
				}
				printf("track2 data:\n%s\n", Track2);
				printflg = 1;
			}
			if(nRet & TRACK3_OK)
			{
				TextOut(0, 8, ALIGN_CENTER, "���ŵ�����:");
				if (track3_len > 32)
				{
					TextOut(0, 9, ALIGN_CENTER, "���ݹ���,������ʾ");
					Track3[32] = '\x00';
					TextOut(0, 10, ALIGN_CENTER, Track3);
				}
				else
				{
					TextOut(0, 9, ALIGN_CENTER, Track3);
				}
				printf("track3 data:\n%s\n", Track3);
				printflg = 1;
			} 

			Wait(500);

			if(printflg != 0)
				PrintLogMagic(Track1, Track2, Track3);
			else
			{
				Clear();
				TextOut(0, 4, ALIGN_CENTER, "ˢ��ʧ��!");
				WaitKey(0);
			}

			Clear();
			TextOut(0, 5, ALIGN_CENTER, "�����ɹ�");
			WaitKey(1000);

			Clear();
			TextOut(0, 2, ALIGN_CENTER, "��������������");
			TextOut(0, 4, ALIGN_CENTER, "��ˢ�ſ� ---->");
			TextOut(0, 9, ALIGN_CENTER, "ȡ�����˳�");
		} 

		if(KbdHit())
		{
			if(GetKey() == KEY_CANCEL)
			{
				MagClose();
				return;
			}
		}
	}

	MagClose();
}

void MEMRead()
{
    UCHAR  atr[4];
	UCHAR  szBuff[500]; 
	char   szTmp[1024];
	UCHAR  ucKey;
	int    i, j, nRet = 0; 
	static int slot = CARD_USER;
	
	while(1)
	{  
    	//��ռ��̻���
    	ClearKbd();
    	
    	Clear();
		SetScrFont(FONT20, WHITE);
    	TextOut(5, 3, ALIGN_LEFT, "�����IC��");
    	TextOut(0, 9, ALIGN_LEFT, "�� [ȡ��] ���˳�");
    	
    	nRet = IccOpen(slot);
        if(nRet != 0)
        {
            FailBeep();
        	Clear();
        	TextOut(2, 3, ALIGN_LEFT, "�����豸��ʧ��");
        	IccClose(slot);
    		PrintLog("�Ӵ�MEM������:", "ERROR���豸����");
        	return;
        }
        printf("IC Card Open OK!\n");
        
    	while(1)
    	{
    	    if(KbdHit())
    	    {
    	        ucKey = GetKey();
    	        if(ucKey == KEY_CANCEL)
    	            return ;
    	    }
    	    
    	    //���IC���Ƿ�λ
    	    nRet = IccDetect(slot);
    		if(nRet != 0)
    		{
    	        printf("Detected No Card! \n"); 
    	        
    	        //�ر�IC����
    			IccClose(slot);
    			Wait(100);

    			//��IC����
    			IccOpen(slot);
    			continue;
    		}
    		Wait(100);
    		break;
    	}
    	printf("Card Detected OK! \n");
    	
    	//��ʼ��Memory IC����
        nRet = IccMemCardInit(slot);
        if(nRet != 0)
        {
        	FailBeep();
        	Clear();
        	TextOut(0, 3, ALIGN_LEFT, "��ʼ����Ƭʧ��");   	
        	IccClose(slot);
    		PrintLog("�Ӵ�MEM������:", "ERROR��ʼ������");
        	return ;
        }
        printf("Init Memory Card OK! \n"); 
    					
        //Memory IC����λ
    	nRet = sle4442_reset(atr);
    	if(nRet == 1)
    	{
        	IccClose(slot);
    		FailBeep();
        	Clear();
    		TextOut(6, 3, ALIGN_LEFT, "��λ����");
    		PrintLog("�Ӵ�MEM������:", "ERROR��λ����");
    		return ;
    	}	
    	printf("Reset OK!\n");
       memset(szBuff, 0, sizeof(szBuff));
        //��ȡIC�����ݣ�sle_read_mm()
        //              ����1-��Ƭ�ڴ���ʼλ�ƣ�
        //              ����2-���ݻ��棻
        //              ����3-����ȡ�����ݳ��ȣ�
        
//        void sle_read_mm(unsigned char addr, unsigned char *buf, int length)
//        ԭ���޶�Ϊ:
//        int sle_read_mm(unsigned char addr,unsigned char *buf,int length)
//        ���ӱ����ء����ȡ���̷����쳣�������ظ�ֵ����

    	sle_read_mm(0, szBuff, 256);
    	
    	//
    	for(i = 0, j = 0; i < 256; i ++)
    	{
    	    if(szBuff[i] == 0xff)
    	        j ++;
    	}
    	if(j == 256)
    	{
    	    Clear();
    	    TextOut(0, 3, ALIGN_LEFT, "   ����ȫ��FF!"); 
    	    printf("j = [%d]\n", j);
    	    FailBeep();
    	    WaitKey(1000);
    	    return;
    	}
    	
    	for(i = 0, j = 0; i < 256; i ++)
    	{
    	    if(szBuff[i] == 0x00)
    	        j ++;
    	}
    	if(j == 256)
    	{
    	    Clear();
    	    TextOut(0, 3, ALIGN_LEFT, "   ����ȫ��00!"); 
    	    printf("j = [%d]\n", j);
    	    FailBeep();
    	    WaitKey(1000);
			return;
    	}
    	
        //======================================================//
    	printf("\nIC Info:\n");	
    	for(i=0; i<256; i++)
        { 
    		printf("%02x ", szBuff[i]);
    		if( !((1+i) % 8) )
    		{
    			printf("\n");
    		}
        }
    	printf("\n");
        //======================================================//
        IccClose(slot);
    	Clear();
    	TextOut(0, 3, ALIGN_LEFT, "      �����ɹ�!");
		memset(szTmp, 0, sizeof(szTmp));
    	BcdToAsc(szTmp, szBuff+64, 12, 0);
    	//memcpy(szTmp,szBuff+64,12);
		printf("%s",szTmp);
    	TextOut(0, 4, ALIGN_LEFT, szTmp); 
		WaitKey(0);
        PrintLog("�Ӵ�MEM������:", szTmp);
		return;
    }
	
    return ;
}

void MEMWrite()
{
    UCHAR  atr[4];
	char  szBuff[100]; 
	UCHAR  ucKey;
	int nRet = 0;
	static int slot = CARD_USER;
	char key_bcd[3+1] = "";

	//ת����Կ
	AscToBcd(key_bcd, gTerm.szMemKey, 6, 0);

	//д�������
	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 4, ALIGN_LEFT, "д������:");
	memset(szBuff, 0, sizeof(szBuff));
	SetScrFont(FONT20, BLUE);
	nRet = Input(1, 5, szBuff, 15, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
	if(nRet != OK)
    	return;

	SetScrFont(FONT20, WHITE);
	while(1)
	{  
    	//��ռ��̻���
    	ClearKbd();
    	Clear();
    	TextOut(5, 3, ALIGN_LEFT, "�����IC��");
    	TextOut(0, 9, ALIGN_LEFT, "�� [ȡ��] ���˳�");
    	nRet = IccOpen(slot);
        if(nRet != 0)
        {
            FailBeep();
        	Clear();
        	TextOut(2, 3, ALIGN_LEFT, "�����豸��ʧ��");
        	IccClose(slot);
    		PrintLog("�Ӵ�MEM������:", "ERROR���豸����");
        	return;
        }
        printf("IC Card Open OK!\n");

    	while(1)
    	{
    	    if(KbdHit())
    	    {
    	        ucKey = GetKey();
    	        if(ucKey == KEY_CANCEL)
    	            return ;
    	    }

    	    //���IC���Ƿ�λ
    	    nRet = IccDetect(slot);
    		if(nRet != 0)
    		{
    	        printf("Detected No Card! \n"); 

    	        //�ر�IC����
    			IccClose(slot);
    			Wait(100);

    			//��IC����
    			IccOpen(slot);
    			continue;
    		}
    		Wait(100);
    		break;
    	}
    	printf("Card Detected OK! \n");
    	
    	//��ʼ��Memory IC����
        nRet = IccMemCardInit(slot);
        if(nRet != 0)
        {
        	FailBeep();
        	Clear();
        	TextOut(0, 3, ALIGN_LEFT, "��ʼ����Ƭʧ��");   	
        	IccClose(slot);
    		PrintLog("�Ӵ�MEM������:", "ERROR��ʼ������");
        	return ;
        }
        printf("Init Memory Card OK! \n"); 
    					
        //Memory IC����λ
    	nRet = sle4442_reset(atr);
    	if(nRet == 1)
    	{
        	IccClose(slot);
    		FailBeep();
        	Clear();
    		TextOut(6, 3, ALIGN_LEFT, "��λ����");
    		PrintLog("�Ӵ�MEM������:", "ERROR��λ����");
    		return ;
    	}	
    		printf("Reset OK!\n");		 
		//�Ƚ�����
		printf("[%02x %02x %02x]\n", key_bcd[0], key_bcd[1], key_bcd[2]);
		nRet=sle_verify_EC(key_bcd,0);
		if(nRet!=0)
		{
			Clear();
			IccClose(slot);
			TextOut(6, 3, ALIGN_LEFT, "��Կ����");
			printf("verify fail  ret=%d \n",nRet);
			WaitKey(1000);
			return;
		}
		else
			printf("verify ok \n");

		//д����
		if(sle_update_mm(64,szBuff,strlen(szBuff))!=0)
			printf("write card error\n");

        //======================================================//
       IccClose(slot);
    	Clear();
    	TextOut(0, 3, ALIGN_CENTER, "д���ɹ�!"); 
		WaitKey(1000);
		PrintLog("�Ӵ�MEM������:", szBuff);
		return;
    }
	
    return ;
}


void AT24Read()
{

	UCHAR  szBuff[500]; 

	UCHAR  ucKey;

	static int slot = CARD_USER;
	int nRet;
	int err;
	char test[3];
	
	while(1)
	{  
    	//��ռ��̻���
    	ClearKbd();
    	Clear();
		SetScrFont(FONT20, WHITE);
    	TextOut(5, 3, ALIGN_LEFT, "�����IC��");
    	TextOut(0, 9, ALIGN_LEFT, "�� [ȡ��] ���˳�");
    	
    	nRet = IccOpen(slot);
        if(nRet != 0)
        {
            FailBeep();
        	Clear();
        	TextOut(2, 3, ALIGN_LEFT, "�����豸��ʧ��");
        	IccClose(slot);
    		PrintLog("�Ӵ�MEM������:", "ERROR���豸����");
        	return;
        }
        printf("IC Card Open OK!\n");
        
    	while(1)
    	{
    	    if(KbdHit())
    	    {
    	        ucKey = GetKey();
    	        if(ucKey == KEY_CANCEL)
    	            return ;
    	    }
    	    
    	    //���IC���Ƿ�λ
    	    nRet = IccDetect(slot);
    		if(nRet != 0)
    		{
    	        printf("Detected No Card! \n"); 
    	        
    	        //�ر�IC����
    			IccClose(slot);
    			Wait(100);

    			//��IC����
    			IccOpen(slot);
    			continue;
    		}
    		Wait(100);
    		break;
    	}
    	printf("Card Detected OK! \n");
    	
    	//��ʼ��Memory IC����
        nRet =at24c_init();
		printf("AT24=%d\n",nRet);
        if(nRet != 0)
        {
        	FailBeep();
        	Clear();
        	TextOut(0, 3, ALIGN_LEFT, "��ʼ����Ƭʧ��");   	
        	IccClose(slot);
    		PrintLog("�Ӵ�MEM������:", "ERROR��ʼ������");
        	return ;
        }
        printf("Init Memory Card OK! \n"); 
			
  
        memset(szBuff, 0, sizeof(szBuff));
		err=0;
	    test[0]=0XAA;
	    if(at24c_write_sub(AT24C04_PAGE0,0xfe,1,test))
	        printf("at24c write fail 1.\n");
	    test[0]=0x00;
	    if(at24c_read_sub(AT24C04_PAGE0,0xfe,1,test))
	        printf("at24c read fail 1:%#02x.\n",test[0]);
	    if(test[0]!=0XAA)
	    {
	        printf("read byte:%#02x.\n",test[0]);
	        err--;
	    }
       
        IccClose(slot);
    	Clear();
    	TextOut(0, 3, ALIGN_LEFT, "      �����ɹ�!");
		OkBeep();
		PrintLog("AT24������:", "��д���ɹ�!!!");
		Wait(1000);
		return;
    }
	
    return ;
}

void MEMCardSet()
{
	int nRet = 0; 

	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 3, ALIGN_LEFT, "  д����Կ:");
	SetScrFont(FONT20, BLUE);
	nRet = Input(11, 4, gTerm.szMemKey, 6, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, TRUE);
	if(nRet != OK)
	if(nRet != OK)
    	return;

	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 3, ALIGN_CENTER, "��Կ���óɹ�");
	WaitKey(2000);
}

/*
 * Memory IC�洢�����Ժ���
 */
 void MEMTest()
{
	UCHAR ucKey;
	char sKeyName[20];

	ClearKbd();
	while(1)
	{
		Clear();

		SetScrFont(FONT20, WHITE);

		//�˵�
		ShowBmpFile(90, 60, "pic/button.bmp");
		TextOutByPixel(100, 65, "1.����");

		ShowBmpFile(90, 95, "pic/button.bmp");
		TextOutByPixel(100, 100, "2.д��");

		ShowBmpFile(90, 130, "pic/button.bmp");
		TextOutByPixel(100, 135, "3.����");

		ShowBmpFile(90, 130, "pic/button.bmp");
		TextOutByPixel(100, 135, "0.�˳�");

		ucKey = WaitLimitKey("\x00\x01\x02\x03\x12", 5, 0);
		memset(sKeyName, 0, sizeof(sKeyName));
		GetKeyName(ucKey, sKeyName);
		DebugOut("press key: %s\n", sKeyName);

		switch(ucKey)
		{
			case KEY_CANCEL:
			case 0:
				return;
				break;
			case 1:
				MEMRead();
				break;
			case 2:
				MEMWrite();
			case 3:
				MEMCardSet();
				break;
		}
	}
	return;
}


/*
 * AT24�洢�����Ժ���
 */
 void AT24Test()
{
	UCHAR ucKey;
	char sKeyName[20];

	ClearKbd();
	while(1)
	{
		Clear();

		SetScrFont(FONT20, WHITE);

		//�˵�
		ShowBmpFile(90, 60, "pic/button.bmp");
		TextOutByPixel(100, 65, "1.����");

		ShowBmpFile(90, 95, "pic/button.bmp");
		TextOutByPixel(100, 100, "2.д��");

		ShowBmpFile(90, 130, "pic/button.bmp");
		TextOutByPixel(100, 135, "0.�˳�");

		ucKey = WaitLimitKey("\x00\x01\x02\x12", 4, 0);
		memset(sKeyName, 0, sizeof(sKeyName));
		GetKeyName(ucKey, sKeyName);
		DebugOut("press key: %s\n", sKeyName);

		switch(ucKey)
		{
			case KEY_CANCEL:
			case 0:
				return;
				break;
			case 1:
				AT24Read();
				break;
			case 2:
				break;
		}
	}
	return;
}


/*************************************************************************/ 
///////////////////////// ��һԪ�����̴������ /////////////////////////
/*
 * ��ȡ��ƵIC���������Ϣ
 */
int TestRfic(void)
{
    	int nRet;
    	int iM1Handle;
	APDU_SEND ApduSend;
	APDU_RESP ApduRecv;
	int  i = 0;
	char szBuff[128] = {0};

    	//��ʼ����Ƶģ��
    	nRet=RficInit(&iM1Handle);
    	if(nRet!=0)
    	{
        	ClearLine(1,9);
        	PutsXY(0,3,"��ʼ��m1ʧ��");
        	WaitKey(2000);
        	return(-1);
    	}

   	//�����Ƶ���Ƿ�λ
    	nRet=RficDetect(iM1Handle);
    	if(nRet!=0)
        	return(-1);
	
    	nRet=RficResetCpu(iM1Handle);
    	if(nRet!=0)
        	return(-1);

	nRet = GetChallenge(&ApduSend, 8);
	if (nRet == ERROR)
	{
		return ERROR;
	}
	nRet = APDU_R_Malloc(&ApduRecv, 8);	
    	nRet = RficOperateCpu(iM1Handle, &ApduSend, &ApduRecv);
	APDU_S_Free(&ApduSend);
	printf("ret=[%d]\n", nRet);
	printf("\nApduRecv.SWA=%02X\n", ApduRecv.SWA );
	printf("ApduRecv.SWB=%02X\n", ApduRecv.SWB );
	if(nRet == 0)
	{ 
		printf("ApduRecv.LenOut=%d\n", ApduRecv.LenOut );
		
		for(i=0; i<ApduRecv.LenOut; i++)
			printf("%02X ", ApduRecv.DataOut[i] );

		if(ApduRecv.SWA != 0x90 || ApduRecv.SWB != 0x00)
		{
	        	printf("Select MF Failed!\n");
	        	TextOut(0, 4, ALIGN_LEFT, "    IC������ʧ��!"); 
	    		RficClose(iM1Handle); 
			WaitKey(1000);
	        	return(-1);
	    	} 
	}
	else 
	{
	    	TextOut(0, 4, ALIGN_LEFT, "    IC������ʧ��!"); 
	    	printf("ѡ�����ļ�ʧ��!\n"); 
	    	RficClose(iM1Handle); 
		FailBeep(); 
		return(-1);
	}
	
	Clear();
	Bcd_To_Ascii(ApduRecv.DataOut, szBuff, ApduRecv.LenOut);	
	TextOut(0, 3, ALIGN_CENTER, szBuff); 
	APDU_R_Free(&ApduRecv);
	printf( "Select MF OK!\n\n\n"); 
	TextOut(0, 4, ALIGN_CENTER, "�ǽӴ�ʽIC�����Գɹ�!"); 

	OkBeep();
	
	//�ر��豸, �ϵ�
	RficClose(iM1Handle); 
	WaitKey(1000);


    return(0);
}
/*************************************************************************/ 
//CPU�������������ݽṹ��	
//typedef struct {
//        unsigned char Command[4];
//        unsigned int Lc;
//        unsigned char * DataIn;
//        int Le;
//}APDU_SEND;
//
//typedef struct {
//        unsigned int LenOut;
//        unsigned char *DataOut;
//        unsigned char SWA;
//        unsigned char SWB;
//}APDU_RESP;
/*
 * �Ӵ�ʽCPU IC�����Ժ���
 */
/*int DoCpuTest(int nSlot)	
{ 
    int slot = CARD_USER;
	char ATR[33]={0};
	int atr_len=0; 
	int ret=0; 
    	int nRet;
	int i;
	APDU_SEND ApduSend;
	APDU_RESP ApduRecv;
	WORK_MODE workMode;		//����ģʽ
	char szBuff[128] = {0};
	
	slot = nSlot; 
	printf("slot=%d.\n",slot);
	workMode.icc_style = 0x01; 	//ST_EMV
	workMode.wk_vol = 2;
	workMode.show_info = 1;
	workMode.wait_time = 0;   	//0��ʾʹ��Ĭ��ֵ
	workMode.reserved = 0x02;    	//�Զ�����PPS
	
	Clear();
	//IccUserPower(1);	
	//���豸�ļ�
	if( (ret=IccOpen( slot  )) !=0 ){
		TextOut(0, 1, ALIGN_LEFT, "��IC����ʧ��!" );
		FailBeep();
		WaitKey(1000);
		return -1;
	}
	printf( "Open Icc OK!\n");
	
	//����Ƿ��п�����
	if( IccDetect(slot) != 0 ){
		TextOut(0, 2, ALIGN_LEFT, "û�м�⵽IC��");
		FailBeep();
	    IccClose(slot); 
		WaitKey(1000);
		return -1;
	}
	printf("IccDetect Icc OK!\n"); 
	 
	//��ʼ����Ƭ
	if( (ret=IccInitEx( slot, ATR, &atr_len, workMode)) !=0 )
	{
		TextOut(0, 3, ALIGN_LEFT, "��Ƭ��ʼ��ʧ��!" );
		FailBeep();
		WaitKey(1000);
		WaitKey(1000);
		return(-1);
	}
	else 
	{
		for( i=0; i<atr_len; i++ )
			 printf("%02X ", ATR[i] );
		printf("\n");
	}
	printf( "Init Icc OK!\n"); 

        nRet = GetChallenge(&ApduSend, 8);
        if (nRet == ERROR)
        {
                return ERROR;
        }
        nRet = APDU_R_Malloc(&ApduRecv, 8);
	ret = IccIsoCommand(slot, &ApduSend, &ApduRecv);
	APDU_S_Free(&ApduSend);
	printf("ret=[%d]\n", nRet);
	printf("\nApduRecv.SWA=%02X\n", ApduRecv.SWA );
	printf("ApduRecv.SWB=%02X\n", ApduRecv.SWB );
	if(nRet == 0)
	{ 
		printf("ApduRecv.LenOut=%d\n", ApduRecv.LenOut );
		
		for(i=0; i<ApduRecv.LenOut; i++)
			printf("%02X ", ApduRecv.DataOut[i] );

		if(ApduRecv.SWA != 0x90 || ApduRecv.SWB != 0x00)
		{
	        	printf("Select MF Failed!\n");
	        	TextOut(0, 4, ALIGN_LEFT, "    IC������ʧ��!"); 
			IccClose(slot);
			WaitKey(1000);
	        	return(-1);
	    	} 
	}
	else 
	{
	    	TextOut(0, 4, ALIGN_LEFT, "    IC������ʧ��!"); 
	    	printf("ѡ�����ļ�ʧ��!\n"); 
		IccClose(slot);
		FailBeep(); 
		return(-1);
	}
	
	Clear();
	Bcd_To_Ascii(ApduRecv.DataOut, szBuff, ApduRecv.LenOut);	
	TextOut(0, 3, ALIGN_CENTER, szBuff); 
	APDU_R_Free(&ApduRecv);
	printf( "Select MF OK!\n\n\n"); 

*/
/* �廪ͬ���û������� */	
	//ѡ�����ļ�
	/*memcpy(ApduSend.Command, "\x00\xA4\x02\x00", 4); 	//Ҫ���͵�����:
	ApduSend.Lc = 2;					//���ߵײ�Ҫ���͵����ݳ���=2;
	ApduSend.Le = 0;					//���ߵײ������󳤶�
	memcpy(sendbuf, "\xEF\x05", 2); 			//�趨2���ֽڵķ��ͻ���
	ApduSend.DataIn = (char *)&sendbuf;			//ָ��Ҫ���͵����ݻ���

	
	if( IccIsoCommand(slot, &ApduSend, &ApduRecv) == 0)
	{ 
		printf("ApduRecv.LenOut=%d\n", ApduRecv.LenOut );
		
		for(i=0; i<ApduRecv.LenOut; i++)
			printf("%02X ", ApduRecv.DataOut[i] );
			
		printf("\nApduRecv.SWA=%02X\n", ApduRecv.SWA );
		printf("ApduRecv.SWB=%02X\n", ApduRecv.SWB );
		
		if(ApduRecv.SWA != 0x90 || ApduRecv.SWB != 0x00)
		{
	        printf("Select EF05 Failed!\n");
	    IccClose(slot); 
	        return(-1);
	    } 
	}
	else 
	{
	    TextOut(0, 4, ALIGN_LEFT, "    IC������ʧ��!"); 
	    printf("ѡ�����ļ�ʧ��!\n"); 
	    IccClose(slot); 
		FailBeep(); 
		return(-1);
	}
	printf( "Select EF05 OK!\n\n\n"); 

    ///////////////////////д���� 00 D6 00 00-- 05 01 02 03 04 05
    ///////////////////////������ 00 B0 00 00-- 05(Le)
    //���Ͷ�����,��������ͬʱ���Զ����ա�
	memcpy(ApduSend.Command, "\x00\xB0\x00\x00", 4);  	//Ҫ���͵�����:00 B0 00 00
	ApduSend.Lc = 0; 					//���ߵײ�Ҫ���͵����ݳ���=0,����������Զ���ʼ����
	ApduSend.Le = 5; 					//�����������ݳ���(0 = ���; -1 = ������)

	if(IccIsoCommand(slot, &ApduSend, &ApduRecv) == 0)
	{ 
		printf("ApduRecv.LenOut=%d\n", ApduRecv.LenOut );
		
		for(i=0; i<ApduRecv.LenOut; i++)
		{
			printf("%02X ",recvbuf[i]);
		}
		
		printf("\nApduRecv.SWA=%02X\n", ApduRecv.SWA );
		printf("ApduRecv.SWB=%02X\n", ApduRecv.SWB );
        
        if(ApduRecv.SWA != 0x90 || ApduRecv.SWB != 0x00) 
		{
	        printf("Get Response failed!\n");
	        IccClose(slot); 
	        return(-1);
	    }  
	}
	else
	{
	    TextOut(0, 4, ALIGN_LEFT, "    IC������ʧ��!"); 
	    printf("ѡ�����ļ�ʧ��!\n"); 
	    IccClose(slot); 
		FailBeep(); 
		return(-1);
	}
	printf( "Read EF05 OK!\n\n\n"); */
/* End */

/*	TextOut(0, 4, ALIGN_LEFT, "  �Ӵ�IC�����Գɹ�!"); 

	OkBeep();
	
	//�ر��豸, �ϵ�
	IccClose(slot); 
	WaitKey(1000);

	return 0;
}*/
/*************************************************************************/ 
int DoCpuTest(int nSlot)	
{ 
    int slot = CARD_USER;
	char ATR[33]={0};
	int atr_len=0; 
	int ret=0; 
	int i;
	WORK_MODE workMode;		//����ģʽ
	
	slot = nSlot; 
	printf("slot=%d.\n",slot);
	workMode.icc_style = 0x01; 	//ST_EMV
	workMode.wk_vol = 2;
	workMode.show_info = 1;
	workMode.wait_time = 0;   	//0��ʾʹ��Ĭ��ֵ
	workMode.reserved = 0x01;    	//�Զ�����PPS
	
	Clear();
	//IccUserPower(1);	
	//���豸�ļ�
	if( (ret=IccOpen( slot  )) !=0 ){
		TextOut(0, 1, ALIGN_LEFT, "��IC����ʧ��!" );
		FailBeep();
		WaitKey(1000);
		return -1;
	}
	printf( "Open Icc OK!\n");
	
	//����Ƿ��п�����
	if( IccDetect(slot) != 0 ){
		TextOut(0, 2, ALIGN_LEFT, "û�м�⵽IC��");
		FailBeep();
	    IccClose(slot); 
		WaitKey(1000);
		return -1;
	}
	printf("IccDetect Icc OK!\n"); 
	 
	//��ʼ����Ƭ
	if( (ret=IccInitEx( slot, ATR, &atr_len, workMode)) !=0 )
	{
		TextOut(0, 3, ALIGN_LEFT, "��Ƭ��ʼ��ʧ��!" );
		FailBeep();
		WaitKey(1000);
		WaitKey(1000);
		return(-1);
	}
	else 
	{
		for( i=0; i<atr_len; i++ )
			 printf("%02X ", ATR[i] );
		printf("\n");
	}
	printf( "Init Icc OK!\n"); 

	ReadCardNo(slot);
	TextOut(0, 4, ALIGN_LEFT, "  �Ӵ�IC�����Գɹ�!"); 

	OkBeep();
	
	//�ر��豸, �ϵ�
	IccClose(slot); 
	WaitKey(1000);

	return 0;
}
/*************************************************************************/ 

void CPUTest()
{ 
	char ch; 
	int nSel;

	while(1)
	{
    	Clear(); 
    	TextOut(0, 2, ALIGN_LEFT, "      ѡ��IC����     ");
    	TextOut(0, 3, ALIGN_LEFT, "�Ƚ���������Ӧ�Ŀ���");
    	TextOut(0, 4, ALIGN_LEFT, "1. �û���");
    	TextOut(0, 5, ALIGN_LEFT, "2. SAM��1");
    	TextOut(0, 6, ALIGN_LEFT, "3. SAM��2");
    	TextOut(0, 7, ALIGN_LEFT, "4. SAM��3");     //3
    	TextOut(0, 8, ALIGN_LEFT, "5. PCD-SAM");
    	TextOut(0, 9, ALIGN_LEFT, "0. �˳�");
    	
    	while(1)
    	{
        	ch = WaitKey(0);   
    	    if(ch == KEY_0 || ch == KEY_CANCEL)
    	        return; 
    	        
    	    if(ch >= KEY_1 && ch <= KEY_4) 
    	    {
        	    nSel = ch-1;
        	    break;
       	    } 
    	    if(ch == KEY_5)
    	    {
    	        nSel = 9;
        	    Clear(); 
	            TextOut(0, 3, ALIGN_LEFT, "   �ݲ�֧�ִ˿���!");
	            FailBeep();
        	    WaitKey(2000);
        	    break;
            }
        }
        if(nSel != 9)
		DoCpuTest(nSel);
    }
}

void M1Set()
{
	int nRet = 0; 

	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 3, ALIGN_LEFT, "  ������Կ:");
	SetScrFont(FONT20, BLUE);
	nRet = Input(8, 4, gTerm.szM1KeyA, 12, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, TRUE);
	if(nRet != OK)
    	return;

	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 3, ALIGN_LEFT, "  д����Կ:");
	SetScrFont(FONT20, BLUE);
	nRet = Input(8, 4, gTerm.szM1KeyB, 12, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, TRUE);
	if(nRet != OK)
    	return;

	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 3, ALIGN_CENTER, "��Կ���óɹ�");
	WaitKey(2000);
}

int M1TestCard()
{
	UCHAR UCKey;
	Clear();
	SetScrFont(FONT20, WHITE);

	//�˵�
	ShowBmpFile(90, 60, "pic/button.bmp");
	TextOutByPixel(100, 65, "1.����");

	ShowBmpFile(90, 95, "pic/button.bmp");
	TextOutByPixel(100, 100, "2.д��");

	ShowBmpFile(90, 130, "pic/button.bmp");
	TextOutByPixel(100, 135, "3.����");

	ShowBmpFile(90, 165, "pic/button.bmp");
	TextOutByPixel(100, 170, "0.�˳�");


	UCKey = WaitLimitKey("\x01\x02\x03\x00",4, 0);
	switch(UCKey)
	
	{
		case KEY_CANCEL:
		case 0:
				return OK;
				break;
		case 1:
		  		RficTest();
		   		break;
		case 2:
		  		RficWirte();
		   		break;
		case 3:
		  		SetKeyM1();
		   		break;
	}

	return 0;
}
int CardReaderTest()
{
	
	UCHAR ucKey;
 	int ucKeyT;
	char sKeyName[20];
	//int  iHandle;
	//int handle;
	
	ClearKbd();
	while(1)
	{
		Clear();

		SetScrFont(FONT20, WHITE);

		//�˵�
		ShowBmpFile(30, 60, "pic/button.bmp");
		TextOutByPixel(40, 65, "1.������");

		ShowBmpFile(175, 60, "pic/button.bmp");
		TextOutByPixel(185, 65, "2.�߼�����");

		ShowBmpFile(30, 95, "pic/button.bmp");
		TextOutByPixel(40, 100, "3.�Ӵ�CPU");

		ShowBmpFile(175, 95, "pic/button.bmp");
		TextOutByPixel(185, 100, "4.�ǽӴ�CPU");

		ShowBmpFile(30, 130, "pic/button.bmp");
		TextOutByPixel(40, 135, "5.M1��");

		ShowBmpFile(175, 130, "pic/button.bmp");
		TextOutByPixel(185, 135, "6.AT�洢��");

		ShowBmpFile(30, 165, "pic/button.bmp");
		TextOutByPixel(40, 170, "7.����M1��");

		ShowBmpFile(175, 165, "pic/button.bmp");
		TextOutByPixel(185, 170, "0.�˳�");

		ucKey = WaitLimitKey("\x00\x01\x02\x03\x04\x05\x06\x07\x12\x0A\x0D",11, 0);
		memset(sKeyName, 0, sizeof(sKeyName));
		GetKeyName(ucKey, sKeyName);
		DebugOut("press key: %s\n", sKeyName);

		switch(ucKey)
		{
			case KEY_CANCEL:
			case 0:
				return OK;
				break;
			case 1:
				// ������ 
				MagCardTest();
				break;
			case 2:
				// �߼����ܿ�
				MEMTest();
				break;
			case 3:
				// �Ӵ�CPU
				CPUTest();
				break;
			case 4:
				FM17CPU();
				// �¿�
				//TestRfic();
				//ReadCard();
				// �ǽ�ͬ��
				//RFCardCPUTest(1);
				break;
			case 5:
				//if(iScanHandle)
				{
				//	switch_COM2(1);
				}
				switch_COM2(1);
				// �¿�
				M1TestCard();
				//handle = SERIAL_Open("/dev/ttyS2", 115200);
				//printf("----------------------------%d--------\n", handle);
				
				break;
			case 6:
				AT24Test();
				break;	
			case 7:
                        	while(1)
                        	{
                                	Clear();
                                	TextOut(0, 3, ALIGN_LEFT, "  1.��һ��");
                                	TextOut(0, 4, ALIGN_LEFT, "  2.дһ��");
                                	TextOut(0, 5, ALIGN_LEFT, "  3.��ʼ����ֵ��");
                                	TextOut(0, 6, ALIGN_LEFT, "  4.��ֵ");
                                	TextOut(0, 7, ALIGN_LEFT, "  5.��ֵ");
                                	TextOut(0, 8, ALIGN_LEFT, "  6.�����п�");
                                	TextOut(0, 9, ALIGN_LEFT, "  7.CPU��");
                                	ucKeyT = WaitLimitKey("\x01\x02\x03\x04\x05\x06\x07\x12", 8, 0);
                                	if ('\x01' == ucKeyT)
                                        	FM17TestRead();
                                	if ('\x02' == ucKeyT)
                                        	FM17TestWrite();
                                	if ('\x03' == ucKeyT)
                                        	FM17TestInit();
                                	if ('\x04' == ucKeyT)
                                        	FM17TestAddValue();
                                	if ('\x05' == ucKeyT)
                                        	FM17TestDecValue();
                                	if ('\x06' == ucKeyT)
                                        	FM17TestReadAllValue();
                                	if ('\x07' == ucKeyT)
                                        	FM17CPU();
                                	if ('\x12' == ucKeyT)
                                        	break;
				}
				break;
			case KEY_F1:
				// �¿�
				//TestRfic();
				ReadCardNO();
				break;
			case KEY_F2:
				break;
		}
	}
	return OK;
}



