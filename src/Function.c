#include "Main.h"
#include <sys/wait.h>
#include <sys/mman.h>
#include "qrgenerator.h"


void UpdateTms()
{
	char ckey;
	system("cd /usr/local/D620D/;./tms");
	Clear();
	PutsXY(0, 4, "���ֶ�����POS...");
	PutsXY(0, 8, "��ʾԶ�̸��º�������POS");
	ckey =GetKey("\x12\x0f");
        if (ckey == KEY_CANCEL)
        	return ;
	ClearLine(1,9);
	while(1)
	{
		PutsXY(0, 4, "���ֶ�����POS...");
	}
}


void UpdateAppFromU()
{
	char cKey;

	Clear();
	TextOut(0, 3, ALIGN_CENTER, "����Ӧ�ó���");
	TextOut(0, 5, ALIGN_CENTER, "��ȷ����/��ȡ����");

	cKey = WaitLimitKey("\x12\x0F", 2, 0);
	if(cKey == KEY_CANCEL)
		return;

	system("rm D620D.tar.gz");
	Clear();
	TextOut(0, 4, ALIGN_CENTER, "���ڸ���...");
	if(GetFileFromU("/usr/local/", "D620D.tar.gz") == OK)
		system("tar zxvf /usr/local/D620D.tar.gz");
	else
	{
		FailBeep();
		Clear();
		TextOut(0, 4, ALIGN_CENTER, "û��usb�̻���usb��û���ú�!");
		WaitKey(0);
		return;
	}

	OkBeep();
	Clear();
	TextOut(0, 3, ALIGN_CENTER, "���³ɹ�");
	TextOut(0, 4, ALIGN_CENTER, "����������POS");
	while(1);
	return;
}

int OtherFunc()
{
	UCHAR ucKey;
	ClearKbd();
	while(1)
	{
		Clear();

		SetScrFont(FONT20, WHITE);

		//�˵�
		ShowBmpFile(90, 60, "pic/button.bmp");
		TextOutByPixel(100, 65, "1.����汾");

		ShowBmpFile(90, 95, "pic/button.bmp");
		TextOutByPixel(100, 100, "2.�������");

		ShowBmpFile(90, 130, "pic/button.bmp");
		TextOutByPixel(100, 135, "3.����");



		ucKey = WaitLimitKey("\x01\x02\x12\x03",4, 0);

		switch(ucKey)
		{
			case KEY_CANCEL:
			case 0:
				return OK;
				break;
			case 1:
				Clear();
				SetScrFont(FONT20, WHITE);
				TextOut(0, 4, ALIGN_CENTER, "D620D���ܲ��Գ���");
				TextOut(0, 6, ALIGN_CENTER, APP_VERSION);
				WaitKey(0);
				break;
			case 2:
				UpdateAppFromU();
				break;
			case 3:
				//SMS_Demo();
                                generator_qrcode_to_bmp(1,"1.00"); 
				break;

		}
	}
	return OK;
}

void ClearClient()
{
	Clear();
	FillRect(0, 319, 0, 227, BLACK);
	DrawRect(0, 319, 0, 227, GREEN);
}

void ScanBarCode()
{
	char code_type[2];
	char code_data[500];
	char buff[500];
	int ret;

	if(!iScanHandle)
	{
		Clear();
		TextOut(0, 3, ALIGN_CENTER, "û�а�װɨ��ͷ,���߳�ʼ��ʧ��");
		WaitKey(5000);
		return;
	}
	switch_COM2(0);
	//switch_CTSRTS(0);
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

	while(1)
	{
	    Clear(); 
		TextOut(0, 3, ALIGN_CENTER, "��ɨ��...");
		memset(buff, 0, sizeof(buff));
		if(se955_scan(buff, 50) <= 0)
		{
		       Clear(); 
			TextOut(0, 3, ALIGN_CENTER, "ɨ�賬ʱ");
			WaitKey(1000);
			goto SELECT;
		}
	    Clear();
		code_type[0] = buff[0];

		memset(code_data, 0, sizeof(code_data));
		strcpy(code_data, buff+1);

		memset(buff, 0, sizeof(buff));
		sprintf(buff, "  ��������: %02x", code_type[0]);
		TextOut(0, 3, ALIGN_LEFT, buff);

		memset(buff, 0, sizeof(buff));
		sprintf(buff, "  ��������: %s", code_data);
		DebugOut("%s\n",buff);
		TextOut(0,4, ALIGN_LEFT, buff);
SELECT:
		TextOut(0, 8, ALIGN_CENTER, "��OK��������ɨ��");
		TextOut(0, 9, ALIGN_CENTER, "��CANCEL�����˳�");
		if(WaitLimitKey("\x0F\x12", 2, 0) == KEY_CANCEL)
			break;
	}
}


int SMS_Demo()
{
	UCHAR ucKey;
	int i;
	ClearKbd();
	while(1)
	{
		Clear();
		TextOut(0,0,ALIGN_CENTER,"����");
		SetScrFont(FONT20, WHITE);
		
		//�˵�
		ShowBmpFile(90, 60, "pic/button.bmp");
		TextOutByPixel(100, 65, "1.д����");

		ShowBmpFile(90, 95, "pic/button.bmp");
		TextOutByPixel(100, 100, "2.�¶���");

		ShowBmpFile(90, 130, "pic/button.bmp");
		TextOutByPixel(100, 135, "3.�ռ���");

		ShowBmpFile(90, 165, "pic/button.bmp");
		TextOutByPixel(100, 170, "4.����");

		ShowBmpFile(90, 200, "pic/button.bmp");
		TextOutByPixel(100, 205, "5.���Ź���");

		ucKey = WaitLimitKey("\x01\x02\x12\x03\x04\x05",6, 0);

		switch(ucKey)
		{
			case KEY_CANCEL:
			case 0:
				return OK;
				break;
			case 1:
				demo_SMS_send();
				break;
			case 2:
				demo_SMS_recv();
				break;
			case 3:
				for(i=1;i<=gSMS.uiMax;i++)
				{
					demo_SMS_read(i);
					ClearLine(1,9);
					TextOut(0,9,ALIGN_CENTER,"���鿴��һ��");
					ucKey =WaitLimitKey("\x12\x0c",2,0);
					if(ucKey==KEY_CANCEL)
						break;
					
				}
				break;
			case 4:
				SMS_Setting();
				break;
			case 5:
				//SMS_Setting();
				break;
		}
	}
	return OK;
}




