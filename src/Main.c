/****************************************************************************
                            D620D���Գ���
****************************************************************************/
#include "Main.h"

#include <stdarg.h>

BOOL iScanHandle;
#define ALIPAY_QUERY 1
#ifdef ALIPAY_QUERY
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include "aliqr.h"
int socket_fd;
struct sockaddr_un address;
#endif


int _strcmp(char *str1,char *str2)
{
        int len1,len2;
        int len;
        int i;

        len1=strlen(str1);
        len2=strlen(str2);

        //ȫ���л�Ϊ��д
        for(i=0;i<len1;i++)
        {
                if(str1[i]>='a'&&str1[i]<='z')
                        str1[i]-='a'-'A';
        }
        for(i=0;i<len2;i++)
        {
                if(str2[i]>='a'&&str2[i]<='z')
                        str2[i]-='a'-'A';
        }

        len=len1<len2?len1:len2;

        for(i=0;i<len;i++)
        {
                if(str1[i]==str2[i])
                        continue;
                if(str1[i]>str2[i])
                        return 1;
                if(str1[i]<str2[i])
                        return -1;
        }

        return len1-len2;
}

int main()
{
	int     i;
	int ucKey;
	//int ucKeyT;
	char sKeyName[20];
	int nRet;
	int display_y;
	char    GprsFlag;
        char    szBuff[128];
        char    szTmp[128];
        int ret;
        int mobile_flag=0;
        int j = 0;
        int nRetAttach = 0;
	//int k = 10;

	//��ʼ��Ӳ��
    	if(InitPOS() != OK)  
		return 0;

	DebugOut("D620D_01���ܲ��Գ���\n");

	Clear();
#if 0
	TextOut(0, 3, ALIGN_CENTER, "POS���ܲ���");
	TextOut(0, 5, ALIGN_CENTER, "test app for D620D_01");
	TextOut(0, 7, ALIGN_CENTER, APP_VERSION);

	WaitKey(2000);

	Clear(); 
	TextOut(0, 3, ALIGN_CENTER, "1.����������GPRS");
	TextOut(0, 4, ALIGN_CENTER, "2.������ԶGPRS  ");
	TextOut(0, 5, ALIGN_CENTER, "3.����CDMA      ");
	TextOut(0, 6, ALIGN_CENTER, "4.����WIFI      ");
    	ucKey=WaitKey(0);
    	if(ucKey== KEY_1)
    	{
 		GprsFlag = 1;
START_SIEMENS_GPRS_INIT:
        	Clear();
	 	TextOut(0, 3, ALIGN_CENTER, "���ڳ�ʼ��G��...");
        
	    	if(SwitchCom0_MC55()!=0)
	    	{
	        	printf("switch com0 fail.\n");
			TextOut(0, 3, ALIGN_CENTER, "GPRS����ʧ��");
			goto FUNC;
	    	}
		//Wait(1000);
		//MC55Reset();
		//Wait(1000);
    		iGprsHandle=GPRS_Open();
		printf("---------------------%d-------------------\n", iGprsHandle);
                Clear();
                TextOut(0, 2, ALIGN_CENTER, "��ʼ��GPRS..");

                //init param.
                if(GPRS_init()!=OK)
                {
                    	ClearLine(1, 9);
                        FailBeep();
                	TextOut(0, 2, ALIGN_CENTER, "��ʼ��GPRSģ��ʧ��");
                        //GetKeyInTime(2000);
                        WaitKey(2000);
                        return -1;
                }
                OkBeep();
                ClearLine(2,8);
               	TextOut(0, 2, ALIGN_CENTER, "��ʼ��GPRS�ɹ�");

               	TextOut(0, 3, ALIGN_CENTER, "���SIM��..");
                //check sim.
                while(1)
                {
                        //if(GetKeyInTime(300)==KEY_ESC)
                        if(WaitKey(300)==KEY_CANCEL)
                                break;
                        if(GPRS_SimReady()==0)
                        {
                                ClearLine(3,7);
               			TextOut(0, 3, ALIGN_CENTER, "���SIM���ɹ�");
                                OkBeep();
                                break;
                        }
                    	ClearLine(3, 7);
                        FailBeep();
               		TextOut(0, 3, ALIGN_CENTER, "δ��SIM��");
               		TextOut(0, 4, ALIGN_CENTER, "���SIM���� OK ��");
                }

                ClearLine(4,6);
               	TextOut(0, 4, ALIGN_CENTER, "ע������..");

                i=0;
                while(1)
                {
                        j++;
                        printf("======================ymm:%d===============\n", j);
                        nRetAttach = GPRSAttach();
                        if (nRetAttach != 0)
                        {
                                if (j >= 15)
                                {
                                        ClearLine(4,6);
                                        TextOut(0,4,ALIGN_CENTER, "����״̬�ϲ�");
                                        Wait(3000);
					GPRS_Reset();
                                }
                        }
                        else
                        {
                                ClearLine(4,6);
                                TextOut(0,4,ALIGN_CENTER, "ע������ɹ�");
                                OkBeep();
                        }

                        ClearLine(5,5);
                        TextOut(0, 5, ALIGN_CENTER, "��Ѱ����..");
                        if(WaitKey(100)==KEY_CANCEL)
                                break;
                        memset(szBuff,0,sizeof(szBuff));
                        memcpy(szBuff,">>>>>>>>>>>>>>>>>>>>",i+2);
                        memcpy(szBuff+i+2,"                    ",20-i-2);
                        ClearLine(6,1);
                        TextOut(0,6,ALIGN_CENTER, szBuff);
                        if (nRetAttach == 0)
                        {
                                memset(szTmp,0,sizeof(szTmp));
                                if(GPRS_GetOper(szTmp)==0)
                                {
                                        ClearLine(5,5);
                                        OkBeep();
                                        break;
                                }
                        }
                        Wait(500);
                        i++;
                        if(i>=19)
                                i=0;
                }
                if(_strcmp(szTmp,"CHN-CUGSM")==0||_strcmp(szTmp,"CHINA UNICOM")==0||_strcmp(szTmp,"CHN-UNICOM")==0)
                {
                        mobile_flag=1;
                        TextOut(0, 5, ALIGN_CENTER, "�й���ͨ");
                }
                else if(_strcmp(szTmp,"CHINA MOBILE")==0)
                {
                        mobile_flag=0;
                        TextOut(0, 5, ALIGN_CENTER, "�й��ƶ�");
                }
                else
                {
                        mobile_flag=0;
                        TextOut(0, 5, ALIGN_CENTER, "δ֪����");
                }
		strcpy(gTerm.szGprsApn, "internet");
		strcpy(gTerm.szGprsUser, "mtnuser");
		strcpy(gTerm.szGprsPwd, "");
                GPRS_SetNet1(gTerm.szGprsUser, gTerm.szGprsPwd, gTerm.szGprsApn, gTerm.szGprsServerIP, gTerm.szGprsServerPort,mobile_flag);
                GPRS_SetNet2(gTerm.szGprsUser, gTerm.szGprsPwd, gTerm.szGprsApn, gTerm.szGprsServerIP, gTerm.szGprsServerPort,mobile_flag);

                ClearLine(6,4); 
                TextOut(0, 6, ALIGN_CENTER, "��������..");
                ret=GPRS_ConfigNet1();
                if(ret!=OK)
                {
                        ClearLine(6,4);
                	TextOut(0, 6, ALIGN_CENTER, "��������ʧ��");
                        MC55_reset();
                        MC55_power_on();
                        goto START_SIEMENS_GPRS_INIT;
                }
                ret=GPRS_ConfigNet2();
                if(ret!=OK)
                {
                        ClearLine(6,4);
                	TextOut(0, 6, ALIGN_CENTER, "��������ʧ��");
                        MC55_reset();
                        MC55_power_on();
                        goto START_SIEMENS_GPRS_INIT;
                }

                ClearLine(6,4);
                TextOut(0, 6, ALIGN_CENTER, "��������ɹ�");
                OkBeep();

                WaitKey(1000);

            //GetSignal(&iSig);
            //memset(szSig, 0, sizeof(szSig));
                //sprintf(szSig, "%d", iSig);

		Init_SMS(0,gSMS.SCA);
    }
   if(ucKey==KEY_2)
 	{
 		GprsFlag = 1;
START_QUECTEL_GPRS_INIT:
        	Clear();
	 	TextOut(0, 3, ALIGN_CENTER, "���ڳ�ʼ��G��...");
        
	    	if(SwitchCom0_MC55()!=0)
	    	{
	        	printf("switch com0 fail.\n");
			TextOut(0, 3, ALIGN_CENTER, "GPRS����ʧ��");
			goto FUNC;
	    	}
		//	M35_power_on();
		//Wait(1000);
		//MC55Reset();
		//Wait(1000);
    		iGprsHandle=GPRS_Open();
		printf("---------------------%d-------------------\n", iGprsHandle);
                Clear();
                TextOut(0, 2, ALIGN_CENTER, "��ʼ��GPRS..");

                //init param.
                if(GPRS_Quectel_init()!=OK)
                {
                    	ClearLine(1, 9);
                        FailBeep();
                	TextOut(0, 2, ALIGN_CENTER, "��ʼ��GPRSģ��ʧ��");
                        //GetKeyInTime(2000);
                        WaitKey(2000);
                        return -1;
                }
                OkBeep();
                ClearLine(2,8);
               	TextOut(0, 2, ALIGN_CENTER, "��ʼ��GPRS�ɹ�");

               	TextOut(0, 3, ALIGN_CENTER, "���SIM��..");
                //check sim.
                while(1)
                {
                        //if(GetKeyInTime(300)==KEY_ESC)
                        if(WaitKey(300)==KEY_CANCEL)
                                break;
                        if(GPRS_SimReady()==0)
                        {
                                ClearLine(3,7);
               			TextOut(0, 3, ALIGN_CENTER, "���SIM���ɹ�");
                                OkBeep();
                                break;
                        }
                    	ClearLine(3, 7);
                        FailBeep();
               		TextOut(0, 3, ALIGN_CENTER, "δ��SIM��");
               		TextOut(0, 4, ALIGN_CENTER, "���SIM���� OK ��");
                }

                ClearLine(4,6);
               	TextOut(0, 4, ALIGN_CENTER, "ע������..");

                i=0;
                while(1)
                {
                        j++;
                        printf("======================ymm:%d===============\n", j);
						Wait(500);
                        nRetAttach = GPRSAttach();
                        if (nRetAttach != 0)
                        {
                                if (j >= 15)
                                {
                                        ClearLine(4,6);
                                        TextOut(0,4,ALIGN_CENTER, "����״̬�ϲ�");
                                        Wait(3000);
										GPRS_Quectel_Reset();
										j = 0;
					 					goto START_QUECTEL_GPRS_INIT;
                                }
                        }
                        else
                        {
                                ClearLine(4,6);
                                TextOut(0,4,ALIGN_CENTER, "ע������ɹ�");
                                OkBeep();
                        }

                        ClearLine(5,5);
                        TextOut(0, 5, ALIGN_CENTER, "��Ѱ����..");
                        if(WaitKey(100)==KEY_CANCEL)
                                break;
                        memset(szBuff,0,sizeof(szBuff));
                        memcpy(szBuff,">>>>>>>>>>>>>>>>>>>>",i+2);
                        memcpy(szBuff+i+2,"                    ",20-i-2);
                        ClearLine(6,1);
                        TextOut(0,6,ALIGN_CENTER, szBuff);
                        if (nRetAttach == 0)
                        {
                                memset(szTmp,0,sizeof(szTmp));
                                if(GPRS_GetOper(szTmp)==0)
                                {
                                        ClearLine(5,5);
                                        OkBeep();
                                        break;
                                }
                        }
                        Wait(500);
                        i++;
                        if(i>=19)
                                i=0;
                }
                if(_strcmp(szTmp,"CHINA UNICOM GSM")==0||_strcmp(szTmp,"CHINA UNICOM")==0||_strcmp(szTmp,"CHN-UNICOM")==0)
                {
                        mobile_flag=1;
                        TextOut(0, 5, ALIGN_CENTER, "�й���ͨ");
                }
                else if(_strcmp(szTmp,"CHINA MOBILE")==0)
                {
                        mobile_flag=0;
                        TextOut(0, 5, ALIGN_CENTER, "�й��ƶ�");
                }
                else
                {
                        mobile_flag=0;
                        TextOut(0, 5, ALIGN_CENTER, "δ֪����");
                }
		strcpy(gTerm.szGprsApn, "internet");
		strcpy(gTerm.szGprsUser, "mtnuser");
		strcpy(gTerm.szGprsPwd, "");
                GPRS_SetNet1(gTerm.szGprsUser, gTerm.szGprsPwd, gTerm.szGprsApn, gTerm.szGprsServerIP, gTerm.szGprsServerPort,mobile_flag);
                GPRS_SetNet2(gTerm.szGprsUser, gTerm.szGprsPwd, gTerm.szGprsApn, gTerm.szGprsServerIP, gTerm.szGprsServerPort,mobile_flag);

                ClearLine(6,4); 
                TextOut(0, 6, ALIGN_CENTER, "��������..");
                ret=GPRS_Quectel_ConfigNet1();
                if(ret!=OK)
                {
                        ClearLine(6,4);
                	TextOut(0, 6, ALIGN_CENTER, "��������ʧ��");
                        MC55_reset();
                        M35_power_on();
                        goto START_QUECTEL_GPRS_INIT;
                }
               /* ret=GPRS_ConfigNet2();
                if(ret!=OK)
                {
                        ClearLine(6,4);
                	TextOut(0, 6, ALIGN_CENTER, "��������ʧ��");
                        MC55_reset();
                        M35_power_on();
                        goto START_QUECTEL_GPRS_INIT;
                }
				*/
                ClearLine(6,4);
                TextOut(0, 6, ALIGN_CENTER, "��������ɹ�");
                OkBeep();

                WaitKey(1000);

            //GetSignal(&iSig);
            //memset(szSig, 0, sizeof(szSig));
                //sprintf(szSig, "%d", iSig);

		Init_SMS(0,gSMS.SCA);
    }
   if(ucKey== KEY_3)
    {
        Clear();
	 	TextOut(0, 3, ALIGN_CENTER, "���ڳ�ʼ��C��...");
        
	    if(SwitchCom0_MC55()!=0)
	    {
	        printf("switch com0 fail.\n");
			TextOut(0, 3, ALIGN_CENTER, "CDMA����ʧ��");
			goto FUNC;
	    }
          Wait(1000);
	    if(PowerOnMC55() != 0)
	    {
	        printf("switch com0 fail.\n");
			TextOut(0, 3, ALIGN_CENTER, "CDMA����ʧ��");
			goto FUNC;
	    }

		//MC55Reset();

    	 iGprsHandle=GPRS_Open();
        nRet = CDMA_Init(iGprsHandle, "card","card"); 
        if(nRet != OK)
        {
        	if(nRet==CANCEL)
        	{
        		Beep(); 
				Clear();
	        	printf( "��ʼ��CDMAʧ��\n");     
				TextOut(0, 3, ALIGN_CENTER, "CDMA��ʼ��ʧ��");
				TextOut(0, 4, ALIGN_CENTER, "����UIM��");
				WaitKey(0);
				goto FUNC;
        	}
        	Beep(); 
        	printf( "��ʼ��CDMAʧ��\n");     
			TextOut(0, 3, ALIGN_CENTER, "CDMA��ʼ��ʧ��");
			goto FUNC;
        }
    }
   if(ucKey== KEY_4)
        {
                if (OK != HardWareInit())
                {
                        Clear();
                        printf( "��ʼ��WIFIʧ��\n");
                        TextOut(0, 3, ALIGN_CENTER, "WIFI��ʼ��ʧ��");
                        WaitKey(0);
                        goto FUNC;
                }
                Clear();
                printf( "��ʼ��WIFI...\n");
                TextOut(0, 3, ALIGN_CENTER, "WIFI��ʼ��...");
                WaitKey(1000);
				if(gTerm.bAutoWifi == FALSE)
				{
	                if (ERROR == Wifi_Para_set(gTerm.t_Wifi))
	                {
	                        Clear();
	                        Beep();
	                        printf( "��ʼ��WIFIʧ��\n");
	                        TextOut(0, 3, ALIGN_CENTER, "WIFI��ʼ��ʧ��");
	                        WaitKey(0);
	                        goto FUNC;

	                }
				}
				else
				{
					 if (ERROR == Wifi_Para_set_Auto(gTerm.t_Wifi))
	                {
	                        Clear();
	                        Beep();
	                        printf( "��ʼ��WIFIʧ��\n");
	                        TextOut(0, 3, ALIGN_CENTER, "WIFI��ʼ��ʧ��");
	                        WaitKey(0);
	                        goto FUNC;

	                }
				}
        }

#endif
	//����״̬��
	CreateStatusBar(WHITE);
	OpenStatusBar();

FUNC:
#ifdef ALIPAY_QUERY
    socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        printf("socket() failed\n");
        return 1;
    }

    unlink("/tmp/demo_socket");

    /* start from a clean socket structure */
    memset(&address, 0, sizeof(struct sockaddr_un));

    address.sun_family = AF_UNIX;
    snprintf(address.sun_path, 20/*UNIX_PATH_MAX*/, "/tmp/demo_socket");

    if(bind(socket_fd,
         (struct sockaddr *) &address,
         sizeof(struct sockaddr_un)) != 0)
    {
        printf("bind() failed\n");
        return 1;
    }

    if(listen(socket_fd, 5) != 0)
    {
        printf("listen() failed\n");
        return 1;
    }
#endif

	ClearKbd();
	display_y = 10;
        while(1)
        {
                printf("$$$$Main inside while loop$$$\n");
                                SetCommParam();
#if 0
		Clear();

		SetScrFont(FONT20, WHITE);
		//����
		//ShowBmpFile(0, 25, "pic/title.bmp");
		TextOutByPixel(90, display_y, "ӯ���ͨ");

		ShowBmpFile(175, display_y+65, "pic/button.bmp");
		TextOutByPixel(185, display_y+70, "4.ͨѶ");

		// 1,2,3,4,5,6,7,8,9,0,F1,F2
		//ucKey = WaitLimitKey("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0D", 12, 0);
		ucKey = WaitLimitKey("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0D", 12, 0);
		if(ucKey < 0)
			continue;
		memset(sKeyName, 0, sizeof(sKeyName));
		GetKeyName(ucKey, sKeyName);
		DebugOut("press key: %s\n", sKeyName);
		switch(ucKey)
		{
			case KEY_0:
			    Clear(); 
				TextOut(0, 3, ALIGN_CENTER, "�Ƿ�ػ�?");
				TextOut(0, 4, ALIGN_CENTER, "1.��   ������.��");
			    if(WaitKey(0) == KEY_1)
					ShutDown();
				break;
			case KEY_4:
				//CommTest();
                                SetCommParam();
				break;
                }
#endif
        }
#if 0
	while(1)
	{
                printf("$$$$Main inside while loop$$$\n");
		Clear();

		SetScrFont(FONT20, WHITE);
		//����
		//ShowBmpFile(0, 25, "pic/title.bmp");
		TextOutByPixel(90, display_y, "D620D���ܲ���");

		//�˵�
		ShowBmpFile(30, display_y+30, "pic/button.bmp");
		TextOutByPixel(40, display_y+35, "1.����");

		ShowBmpFile(175, display_y+30, "pic/button.bmp");
		TextOutByPixel(185, display_y+35, "2.��ʾ��");

		ShowBmpFile(30, display_y+65, "pic/button.bmp");
		TextOutByPixel(40, display_y+70, "3.������");

		ShowBmpFile(175, display_y+65, "pic/button.bmp");
		TextOutByPixel(185, display_y+70, "4.ͨѶ");

		ShowBmpFile(30, display_y+100, "pic/button.bmp");
		TextOutByPixel(40, display_y+105, "5.��ӡ��");

		ShowBmpFile(175, display_y+100, "pic/button.bmp");
		TextOutByPixel(185, display_y+105, "6.����");

		ShowBmpFile(30, display_y+135, "pic/button.bmp");
		TextOutByPixel(40, display_y+140, "7.�������");

		ShowBmpFile(175, display_y+135, "pic/button.bmp");
		TextOutByPixel(185, display_y+140, "8.����");

		ShowBmpFile(30, display_y+170, "pic/button.bmp");
		TextOutByPixel(40, display_y+175, "9.�˳�");

		ShowBmpFile(175, display_y+170, "pic/button.bmp");
		TextOutByPixel(185, display_y+175, "0.�ػ�");


		// 1,2,3,4,5,6,7,8,9,0,F1,F2
		//ucKey = WaitLimitKey("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0D", 12, 0);
		ucKey = WaitLimitKey("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0D", 12, 0);
		if(ucKey < 0)
			continue;
		memset(sKeyName, 0, sizeof(sKeyName));
		GetKeyName(ucKey, sKeyName);
		DebugOut("press key: %s\n", sKeyName);

		switch(ucKey)
		{
			case KEY_0:
			    Clear(); 
				TextOut(0, 3, ALIGN_CENTER, "�Ƿ�ػ�?");
				TextOut(0, 4, ALIGN_CENTER, "1.��   ������.��");
			    if(WaitKey(0) == KEY_1)
					ShutDown();
				break;
			case KEY_1:
				SetScrFont(FONT20, WHITE);
				KbdTest();
				break;
			case KEY_2:
				LcdTest();
				break;
			case KEY_3:
				CardReaderTest();
				break;
			case KEY_4:
				CommTest();
				break;
			case KEY_5:
				PrinterTest();
				break;
			case KEY_6:
				JingZhenTest();
				break;
			case KEY_7:
				//PinpadTest();
				//PinpadN20Test();
				PinpadHYTest();
				break;
			case KEY_8:
				OtherFunc();
				break;
			case KEY_9:
				Clear();
				system("kill -9 $(pidof D620D)");
				return 0;
				break;
			case KEY_F1:
				while(1)
                   {
					Clear(); 
					TextOut(0, 3, ALIGN_CENTER, "��ѡ����·�ʽ");
					TextOut(0, 4, ALIGN_CENTER, "1.U�̸���");
					TextOut(0, 5, ALIGN_CENTER, "2.Զ�̸���");

	                ucKey = WaitLimitKey("\x01\x02\x12", 8, 0);
	                if ('\x01' == ucKey)
	                     	UpdateAppFromU();
	                if ('\x02' == ucKey)
	                     	UpdateTms();
	                if ('\x12' == ucKey)
                            break;
				}
				break;
			case KEY_ENTER:
				OtherTest();
				break;
			case KEY_F2:
				ScanBarCode();
				break;
		}
	}
#endif
}




