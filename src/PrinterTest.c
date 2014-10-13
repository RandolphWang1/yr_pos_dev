#include "Main.h"
 
void PrintLog(char *Title, char *Msg)
{ 
    int ret;
    char PrintBuff[1024];

START_PRINT:
	if(CheckPrinter() != TRUE)
		goto end1;

	//��մ�ӡ������
	ClearPrintBuff();

    SetPrintFont(24);

    ret = FillPrintBuff("PL");
    if(ret < 0)
		goto end1;
    memset(PrintBuff, 0x00, sizeof(PrintBuff));
    strcpy(PrintBuff, Title);
    ret = FillPrintBuff(PrintBuff);
    if(ret < 0)
		goto end1;             
    ret = FillPrintBuff("PL");
    if(ret < 0)
		goto end1;
    SetPrintIndent(0); 
      
    memset(PrintBuff, 0, sizeof(PrintBuff));
    strcpy(PrintBuff, Msg);
    ret = FillPrintBuff(PrintBuff);
    if(ret < 0)
		goto end1;
    ret = FillPrintBuff("PL"); 
    if(ret < 0)
		goto end1;    
     
	//��ʼ��ӡ    
	ret =StartPrint();
	DebugOut("print error code:[%d]\n", ret);
	if(ret != 0)
	{
		if(ret == -1)
			goto START_PRINT;
		else if(ret == -2)
			goto end2;
		else if(ret == -3)
			goto end1;
	}

    return;

end1:  

	FailBeep(); 
	ClearLine(1, 9);
	TextOut(0, 3, ALIGN_CENTER, "�����ӡ��"); 
	TextOut(0, 4, ALIGN_CENTER, "��ӡʧ��");
	WaitKey(2000);

	return;

end2:  

	FailBeep(); 
	ClearLine(1, 9);
	TextOut(0, 3, ALIGN_CENTER, "��������"); 
	TextOut(0, 4, ALIGN_CENTER, "�޷�ִ�д�ӡ");
	WaitKey(2000);
}
 
void PrintMsg(char *Msg)
{ 
    int ret;
    char PrintBuff[1024];

START_PRINT:
	if(CheckPrinter() != TRUE)
		goto end1;

	//��մ�ӡ������
	ClearPrintBuff();

    SetPrintFont(24);

    memset(PrintBuff, 0, sizeof(PrintBuff));
    strcpy(PrintBuff, Msg);
    ret = FillPrintBuff(PrintBuff);
    if(ret < 0)
		goto end1;
    ret = FillPrintBuff("PL"); 
    if(ret < 0)
		goto end1;    
     
	//��ʼ��ӡ    
	ret =StartPrint();
	DebugOut("print error code:[%d]\n", ret);
	if(ret != 0)
	{
		if(ret == -1)
			goto START_PRINT;
		else if(ret == -2)
			goto end2;
		else if(ret == -3)
			goto end1;
	}

    return;

end1:  

	FailBeep(); 
	ClearLine(1, 9);
	TextOut(0, 3, ALIGN_CENTER, "�����ӡ��"); 
	TextOut(0, 4, ALIGN_CENTER, "��ӡʧ��");
	WaitKey(2000);

	return;

end2:  

	FailBeep(); 
	ClearLine(1, 9);
	TextOut(0, 3, ALIGN_CENTER, "��������"); 
	TextOut(0, 4, ALIGN_CENTER, "�޷�ִ�д�ӡ");
	WaitKey(2000);
}

int PrinterQRTest()
{
	int j = 0,i = 0, ret = 0;
	j = 10;
	i = 5;
	while(j > 5)
	{
		
	
		ret = PrintQR(10+i*2, 1, 1, "123456789abcdefgh", j*2, 3);
		if (0 > ret)
		{
			DebugOut("print QR error code:[%d]\n", ret);
		}
		j--;
		i--;
		
		WaitKey(1000);
	}

	return ret;
}
int PrinterBLTest()
{
	int   i, ret=0;  
	CHAR  PrintBuff[100]; 
	char  buff[64];  
	int   num;

	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "��ӡ����");
	TextOut(0, 4, ALIGN_LEFT, "�������ӡ����:(1-999)");

	memset(buff, 0, sizeof(buff));
	SetScrFont(FONT20, RED);
	ret = Input(22, 4, buff, 3, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
	if(ret != OK)
	{
		FailBeep(); 
		ClearLine(1, 9);
		SetScrFont(FONT20, WHITE);
		TextOut(0, 4, ALIGN_CENTER, "��ӡʧ��");
		WaitKey(2000);

		return ERROR;
	}
	num = atoi(buff);
	DebugOut("��ӡ����:[%d]\n", num);

	for (i = 0; i < num; i ++)
	{
START_PRINT:
		if(CheckPrinter() != TRUE)
			goto end1;

		printf("�����ڱ��ӡ����\n");
		ret =  BmSwitch(1);
		printf("ret = %d\n", ret);
		if (0 != ret)
		{
			printf("����ʧ��\n");
			return 0;
		}
		MoveDotLine(4000);
		// ����ֱ�������ڱ�֮��ľ���

		//��մ�ӡ������
		ClearPrintBuff();
		//���ô�ӡ�����С

		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "ABCDEFGHIJKLMNOPQRSTUVWX");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "123456789012345678");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
		ret = FillPrintBuff("PL");
		if(ret < 0)
			goto end1;
		SetPrintIndent(0); 

		//��ʼ��ӡ    
		ret =StartPrint();
		DebugOut("print error code:[%d]\n", ret);
		if(ret != 0)
		{
			if(ret == -1)
				goto START_PRINT;
			else if(ret == -2)
				goto end2;
			else if(ret == -3)
				goto end1;
		}
		
		
	}
	if(ret==0)
	{
		ClearLine(1,  9);
		TextOut(0,  4, ALIGN_CENTER,  "��ӡ�ɹ�");
		WaitKey(1000);
	}
	else
	{
		ClearLine(1,  9);
		TextOut(0,  4, ALIGN_CENTER,  "��ӡʧ��");
		WaitKey(1000);
	}

	OkBeep();
	return OK;

end1:  

	FailBeep(); 
	ClearLine(1, 9);
	TextOut(0, 3, ALIGN_CENTER, "�����ӡ��"); 
	TextOut(0, 4, ALIGN_CENTER, "��ӡʧ��");
	WaitKey(2000);

	return ERROR;

end2:  

	FailBeep(); 
	ClearLine(1, 9);
	TextOut(0, 3, ALIGN_CENTER, "��������"); 
	TextOut(0, 4, ALIGN_CENTER, "�޷�ִ�д�ӡ");
	WaitKey(2000);

	return ERROR;
}




int PrinterNormalTest()
{
	int   i, ret=0;  
	CHAR  PrintBuff[100]; 
	char  buff[64];  
	int   num;

	Clear();
	SetScrFont(FONT20, WHITE);
	TextOut(0, 2, ALIGN_CENTER, "��ӡ����");
	TextOut(0, 4, ALIGN_LEFT, "�������ӡ����:(1-999)");

	memset(buff, 0, sizeof(buff));
	SetScrFont(FONT20, RED);
	ret = Input(22, 4, buff, 3, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
	if(ret != OK)
	{
		FailBeep(); 
		ClearLine(1, 9);
		SetScrFont(FONT20, WHITE);
		TextOut(0, 4, ALIGN_CENTER, "��ӡʧ��");
		WaitKey(2000);

		return ERROR;
	}
	num = atoi(buff);
	DebugOut("��ӡ����:[%d]\n", num);

	for (i = 0; i < num; i ++)
	{
START_PRINT:
		if(CheckPrinter() != TRUE)
			goto end1;

		//��մ�ӡ������
		ClearPrintBuff();
		//���ô�ӡ�����С

//		ret = FillPrintBuff("PL");
//		if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);    

		//SetPrintFont(64);  
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "************");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintIndent(0);   
		//SetPrintFont(16);  
		SetPrintFont(24);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "<TYPE24>");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		//SetPrintFont(16);  
		SetPrintFont(24);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUV");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0); 

		//SetPrintFont(16);  
		SetPrintFont(24);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "123456789012345678901234567890123456789012345678");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;     
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		//SetPrintFont(16);  
		SetPrintFont(24);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "���Գ���, ��ǰ�����Ի���TYPE :D620D");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0); 
		////////////////////
		//SetPrintFont(64);  
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "************");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintIndent(0);   
		SetPrintFont(24);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "<TYPE24>");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintFont(24);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEF");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0); 

		SetPrintIndent(0);   
		SetPrintFont(24);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "abcdefghijklmnopqrstuvwxyzabcde");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintFont(24);
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "12345678901234567890123456789012");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;     
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintFont(24);
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "1234.5678.9012.3456.7890.1234.56");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;     
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintFont(24);
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "~!@#$%^&*()_+-=/|,.?<>;:'{}[]-��");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;     
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintFont(24);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "���Գ��� TYPE: D620D");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0); 

		//SetPrintFont(64);  
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "************");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0); 

		SetPrintIndent(0);   
		SetPrintFont(32);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "<TYPE32>");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintFont(32);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "ABCDEFGHIJKLMNOPQRSTUVWX");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0); 

		SetPrintIndent(0);   
		SetPrintFont(32);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "abcdefghijklmnopqrstuvwx");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintFont(32);
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "123456789012345678901234");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;     
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintFont(32);
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "1234.5678.9012.3456.7890");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;     
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintFont(32);
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "~!@#$%^&*()_+-=/|,.?<>;");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;     
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintFont(32);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "���Գ���D620D");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);  

		//��ʼ��ӡ    
		ret =StartPrint();
		if(ret != 0)
		{
			if(ret == -1)
				goto START_PRINT;
			else if(ret == -2)
				goto end2;
			else if(ret == -3)
				goto end1;
		}

		//��մ�ӡ������
		ClearPrintBuff();

		//SetPrintFont(64);
		SetPrintIndent(0);  
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "************");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	///	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;

		SetPrintIndent(0);   
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "<TYPE48>");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
		//ret = FillPrintBuff("PL");
		//if(ret<0)goto end1;
		SetPrintIndent(0);

		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "ABCDEFGHIJKLMNOPQRSTUVWX");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
		//ret = FillPrintBuff("PL");
	//	if(ret < 0)
		//	goto end1;
		SetPrintIndent(0); 

		SetPrintIndent(0);   
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "abcdefghijklmnop");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
		//	goto end1;
		SetPrintIndent(0);

		SetPrintFont(48);
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "1234567890123456");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;     
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintFont(48);
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "1234.5678.9012.3");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;     
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintFont(48);
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "~!@#$%^&*()_+-=/");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;     
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "���Գ���D620D");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0); 

		//SetPrintFont(64);  
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "************");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		SetPrintIndent(0);   
		//SetPrintFont(64);  
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "<TYPE48>");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		//SetPrintFont(64);  
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "ABCDEFGHIJKLMNOPQRSTUVWX");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0); 

		SetPrintIndent(0);   
		//SetPrintFont(64);  
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "abcdefghijkl");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		//SetPrintFont(64);  
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "123456789012");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;     
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		//SetPrintFont(64);  
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "1234.5678.90");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;     
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0);

		//SetPrintFont(64);  
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "���Գ���");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             
	//	ret = FillPrintBuff("PL");
	//	if(ret < 0)
	//		goto end1;
		SetPrintIndent(0); 

		//SetPrintFont(64);  
		SetPrintFont(48);  
		memset(PrintBuff, 0x00, sizeof(PrintBuff));
		strcpy(PrintBuff, "************");
		ret = FillPrintBuff(PrintBuff);
		if(ret < 0)
			goto end1;             

		//���ô�ӡ�����С
		//SetPrintFont(64);  
		SetPrintFont(48);  

		ret = FillPrintBuff("PL");
		if(ret < 0)
			goto end1;
		ret = FillPrintBuff("PL");
		if(ret < 0)
			goto end1;
		ret = FillPrintBuff("PL");
		if(ret < 0)
			goto end1;
		ret = FillPrintBuff("PL");
		if(ret < 0)
			goto end1;
		SetPrintIndent(0);

		//��ʼ��ӡ    
		ret =StartPrint();
		DebugOut("print error code:[%d]\n", ret);
		if(ret != 0)
		{
			if(ret == -1)
				goto START_PRINT;
			else if(ret == -2)
				goto end2;
			else if(ret == -3)
				goto end1;
		}
		
		
	}
	if(ret==0)
	{
		ClearLine(1,  9);
		TextOut(0,  4, ALIGN_CENTER,  "��ӡ�ɹ�");
		WaitKey(1000);
	}
	else
	{
		ClearLine(1,  9);
		TextOut(0,  4, ALIGN_CENTER,  "��ӡʧ��");
		WaitKey(1000);
	}

	OkBeep();
	return OK;

end1:  

	FailBeep(); 
	ClearLine(1, 9);
	TextOut(0, 3, ALIGN_CENTER, "�����ӡ��"); 
	TextOut(0, 4, ALIGN_CENTER, "��ӡʧ��");
	WaitKey(2000);

	return ERROR;

end2:  

	FailBeep(); 
	ClearLine(1, 9);
	TextOut(0, 3, ALIGN_CENTER, "��������"); 
	TextOut(0, 4, ALIGN_CENTER, "�޷�ִ�д�ӡ");
	WaitKey(2000);

	return ERROR;
}


int PrinterTest()
{
        UCHAR ucKey;
        //int i;
        ClearKbd();
        while(1)
        {
                Clear();
                TextOut(0,0,ALIGN_CENTER,"��ӡ����");
                SetScrFont(FONT20, WHITE);

                //�˵�
                ShowBmpFile(90, 60, "pic/button.bmp");
                TextOutByPixel(100, 65, "1.��ͨ��ӡ");

                ShowBmpFile(90, 95, "pic/button.bmp");
                TextOutByPixel(100, 100, "2.��ӡ��ά��");

                ShowBmpFile(90, 130, "pic/button.bmp");
                TextOutByPixel(100, 135, "3.�ڱ��ӡ");

                ucKey = WaitLimitKey("\x01\x02\x12\x03",4, 0);

                switch(ucKey)
                {
                        case KEY_CANCEL:
                        case 0:
                                return OK;
                                break;
                        case 1:
                                PrinterNormalTest();
                                break;
                        case 2:
                                PrinterQRTest();
                                break;
                        case 3:
                                PrinterBLTest();
                               break;
                }
        }
        return OK;
}
