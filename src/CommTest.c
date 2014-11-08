#include "Main.h"
#include "aliqr.h"
#include "qrgenerator.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t prmutex;
#define ALIPAY_QUERY
int SetMoney();
extern int socket_fd;
extern struct sockaddr_un address;

extern void showVersion(void);
extern void Update_YRJT_Image(void);
extern upload_debug_log(void);
#ifdef ALIPAY_FIFO
extern int pipe_fd;
#endif


void refund(void);
void qrexchange(void);
int qrexchangedorder(void);
void querySingle(void);
void *thr_fn(void* arg);
void printTail(char* price, char* out_trade_no);
char* Moneyformat(char* buf);
char* serial2date(char* serialNo);
unsigned int Money2int(char* buf);
void print_logo();
void query24h(void);
char result24h[QRRESULT] = {0};
int SetReceiptInfo();
#ifdef ALIPAY_QUERY
extern unsigned long long query_number; 
extern char qrout_trade_no[];

static struct payInfo commTestIn;
static struct qr_result commTestOut;

int SplitStr(char *buff, char *parr[], char *token) 
{
        char *pc = strtok(buff, token); 
        int i;  

        for(i=0; pc != NULL; i++)
        {       
                parr[i] = pc;
                pc = strtok(NULL, token); 
        }       
        
        return i;
}
#endif
#if 0
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
#endif



void SetCommParam()
{
	UCHAR ucKey;
	char sKeyName[20];
	int ret;
    int err;
    pthread_t ntid;
    pthread_mutex_init(&prmutex, NULL);
    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if(err != 0)
        printf("!!!! query thread create failure-----\n");
    ClearKbd();
    printf("---------SetCommParam() outside the while loop----\n");
    while(1)
    {
		Clear();

        printf("---------SetCommParam() inside the while loop----\n");
		SetScrFont(FONT20, WHITE);


		//����
		//ShowBmpFile(0, 25, "pic/title.bmp");
		//TextOutByPixel(95, 30, "ӯ���ͨ");
		TextOutByPixel(115, 30, "ӯ���ͨ");

        ShowBmpFile(30, 75, "pic/button.bmp");
        TextOutByPixel(45, 80, "0.�ػ�");

        ShowBmpFile(30, 110, "pic/button.bmp");
        TextOutByPixel(45, 115, "1.֧����");

        ShowBmpFile(30, 145, "pic/button.bmp");
        TextOutByPixel(45, 150, "2.�𵥲�ѯ");

        ShowBmpFile(30, 180, "pic/button.bmp");
        TextOutByPixel(45, 185, "3.�ս�");

        ShowBmpFile(170, 75, "pic/button.bmp");
        TextOutByPixel(185, 80, "4.ǩ��");

        ShowBmpFile(170, 110, "pic/button.bmp");
        TextOutByPixel(185, 115, "5.����ǩ��");

#ifdef REFUND_EN
        ShowBmpFile(170, 145, "pic/button.bmp");
        TextOutByPixel(185, 150, "6.�˻�");
#endif

        printf("go before SetCommParam WaitLimitKey\n");
#ifdef REFUND_EN
        ucKey = WaitLimitKey("\x00\x01\x02\x03\x04\x05\x06\x0a\x12", 9, 0);
#else
        ucKey = WaitLimitKey("\x00\x01\x02\x03\x04\x05\x0a\x12", 8, 0);
#endif
        printf("go after SetCommParam WaitLimitKey\n");
        memset(sKeyName, 0, sizeof(sKeyName));
        GetKeyName(ucKey, sKeyName);
        DebugOut("press key: %s\n", sKeyName);

		switch(ucKey)
		{
			case KEY_CANCEL:
				return;
				break;
                        case KEY_0:
                               Clear();
                               TextOut(0, 3, ALIGN_CENTER, "�Ƿ�ػ�?");
                               TextOut(0, 4, ALIGN_CENTER, "1.��   ������.��"); 
                               if(WaitKey(0) == KEY_1)
                                           ShutDown(); 
                               break;
            case KEY_1:
                //this part should think about more
                if (system("ifconfig eth0") != 0) 
                    if (system("ifconfig ppp0") != 0) {
                        Clear(); 
                        TextOut(0, 5, ALIGN_CENTER, "�Եȣ����ڳ�ʼ���ƶ�����...");
                        Wait(2000);
                        return;
                    }
                Clear();
                //TextOut(0, 0, ALIGN_CENTER, "IP ��ȡ��ʽ");
                TextOut(0, 0, ALIGN_CENTER, "��ӭʹ��֧����Ǯ��֧��");

				TextOut(0, 4, ALIGN_CENTER, "�밴OK��������");
				TextOut(0, 5, ALIGN_CENTER, "��CANCEL������BACK������");
				ucKey = WaitLimitKey("\x12\x0E\x0F", 3, 0);
				if(ucKey == KEY_ENTER)
					SetMoney();
				else if(ucKey == KEY_CANCEL || ucKey == KEY_BACKSPACE)
					return ;
				break;
            case KEY_2:
                querySingle();
                break;	
            case KEY_3:
                query24h();
                break;
			case KEY_4:
                qrexchange();
                break;
            case KEY_5:
                qrexchangedorder();
				break;	
			case KEY_6:
                refund();
				break;	
            case KEY_F1:
                Clear();
                //TextOut(0, 0, ALIGN_CENTER, "IP ��ȡ��ʽ");
                TextOut(0, 0, ALIGN_CENTER, "�����ʹ�����߸��·���");
                TextOut(0, 1, ALIGN_CENTER, "ӯ���֧ͨ�ֵ绰��4008190900");

				TextOut(0, 4, ALIGN_CENTER, "�밴OK������");
				TextOut(0, 5, ALIGN_CENTER, "��CANCEL������BACK������");
				ucKey = WaitLimitKey("\x12\x0E\x0F", 3, 0);
                if(ucKey == KEY_ENTER)
                {
                    Clear();	
                    TextOutByPixel(105, 60, "1.��ǰ�汾");
                    TextOutByPixel(105, 80, "2.Զ������");
                    TextOutByPixel(105, 100, "3.�ϴ�������Ϣ");
                    TextOutByPixel(105, 140, "5.����ʱ��");
#ifdef RECEIPT_CONF
                    TextOutByPixel(105, 120, "4.����̧ͷ");
                    ucKey = WaitLimitKey("\x01\x02\x03\x04\x05\x12", 6, 0);
#else
                    ucKey = WaitLimitKey("\x01\x02\x03\x05\x12", 5, 0);
#endif
                    if ('\x01' == ucKey)
                        showVersion();

                    if ('\x02' == ucKey)
                        Update_YRJT_Image();

                    if ('\x03' == ucKey)
                        upload_debug_log();
#ifdef RECEIPT_CONF
                    if ('\x04' == ucKey) {
                        SetReceiptInfo();
                    } 
#endif
                    if ('\x05' == ucKey) {
                        JingZhenTest();
                    } 
                } else if(ucKey == KEY_CANCEL || ucKey == KEY_BACKSPACE)
                    return; 
                break;
		}
	}
}

int CommTest()
{
	UCHAR ucKey;
	char sKeyName[20];

	ClearKbd();
        printf("+++++++CommTest() outside while loop+++\n");
	while(1)
	{
		Clear();

        printf("+++++++CommTest() inside while loop+++\n");
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


int SetMoney()
{
    int ret;
    char buff[128] = "";
    char buffshow[128] = "";
    int tempDataNum;

    memset(buff, 0, sizeof(buff));
    Clear();
    SetScrFont(FONT20, WHITE);
    TextOut(0, 2, ALIGN_CENTER, "��������");
    TextOut(0, 8, ALIGN_CENTER, "��������밴OK��");
    SetScrFont(FONT20, RED);
    ret = InputMoney(8, 5, buff,20); 
    if(ret < 0)
    	goto FAILED;

	printf("\nbefore:%s\n", buff);
    Moneyformat(buff);
    printf("\nafter:%s\n", buff);
    pthread_mutex_lock(&prmutex);
    print_logo();
    //strcpy(commTestIn.order_subject,gRCP.rcp_title_company);
    //strcpy(commTestIn.order_subject,"��������������޹�˾�����ó��");
    //strcpy(commTestIn.order_subject,"%E5%88%86%E8%B4%A6%E6%B5%8B%E8%AF%95-sky");
    //strcpy(commTestIn.order_subject,"AliPay");
    ret = generator_qrcode_to_bmp((void*)&commTestOut,buff,(void*)&commTestIn);
	//system(buff);	 

    OkBeep();
    Clear();
    SetScrFont(FONT20, WHITE);
    if(ret == 1)
        TextOut(2, 4, ALIGN_CENTER, "����֧����ʧ�ܣ���������");
    else {
        //TextOut(2, 4, ALIGN_CENTER, "input money OK!");
        TextOut(2, 4, ALIGN_CENTER, "�Եȣ����������ά��...");
        printTail(buff,commTestOut.out_trade_no);
    }
    pthread_mutex_unlock(&prmutex);
    /* send trigger to query_server to start timer */
#ifdef ALIPAY_FIFO
    write(pipe_fd, "START", 6);
#endif
    WaitKey(1000);
    return OK;

FAILED:

	SetScrFont(FONT20, WHITE);
    if(ret == -1)
        TextOut(2, 6, ALIGN_CENTER, "error input");
    else if (ret == -3) {
        //TextOut(2, 6, ALIGN_CENTER, "cancel");
        return ERROR;
    }
    else 
        TextOut(2, 6, ALIGN_CENTER, "unknow");
	WaitKey(2000);
	printf("SetMoney failed ret;%d\n", ret);
	return ERROR;
}

char* Moneyformat(char* buf)
{   
    int len = strlen(buf);
    if(len > 2) {  // RMB >1.00
    memmove(buf+len-1, buf+len-2,2);
    buf[len-2] = '.';
    } else if (len ==2 ) { //0.09 RMB < 0.99
    memmove(buf+2,buf,2);
    buf[1] = '.';
    buf[0] = '0';
    } else if (len ==1)  {
    memmove(buf+3,buf,1);
    buf[2] = '0';
    buf[1] = '.';
    buf[0] = '0';
    }
    return buf;
}

unsigned int Money2int(char* buf)
{
    char fee[18] = {0};
    int len = strlen(buf);
    int feeint = 0;
    printf("Money2int buf:%s, strlen(buf):%d\n", buf, len);
    if(buf[len-3] == '.'){ //for these have fen like 1.01 or 0.01
        memcpy(fee,buf,len-3);  
        memcpy(fee+len-3,buf+len-2,2);
    } else if(buf[len-2] == '.'){ //for these have jiao like 1.1 or 0.1
        memcpy(fee,buf,len-2);  
        fee[len-2] = buf[len-1];
        fee[len-1] = '0';     //for we must make 1.1 to 110
    } else {
        memcpy(fee,buf,len);
        fee[len] = '0';   
        fee[len + 1]  = '0';  
    }
    feeint = (unsigned int)atoi(fee);
    printf("Money2int fee:%s, feeint:%d\n", fee, feeint);
    return feeint;
}

void printAD()
{
	int ret;

    Clear();
	TextOut(0, 4, ALIGN_CENTER, "���ڴ�ӡ...");

	ret = PrintBMP(0, "pic/print.bmp");
	printf("PrintBMP ret:[%d]\n", ret);
    if(ret != OK)
    {
        FailBeep();
        ClearClient();
        TextOut(0, 4, ALIGN_CENTER, "��ӡʧ��");
        WaitKey(2000);
    }
}
void printTail(char* price, char* out_trade_no)
{
    int ret = 0;
    char printBuff[50];
START_PRINT:
    if(CheckPrinter() != TRUE) {
        printf("the printer is not working well!\n");
        goto end1;
    }
    ClearPrintBuff();
    SetPrintIndent(0);
    SetPrintFont(32);
    sprintf(printBuff,"���к�:%lld",query_number);
    FillPrintBuff(printBuff);
    if(strlen(out_trade_no) > 0) {
        strcpy(printBuff,"�̻�������:");
        strcat(printBuff,out_trade_no);
        FillPrintBuff(printBuff);
        memset(out_trade_no,0, 65);
    }
    PrintEmptyLine(1);
    SetPrintIndent(0);
    SetPrintFont(32);
    strcpy(printBuff,"���������ѽ��: ");
    strcat(printBuff,price);
    FillPrintBuff(printBuff);
    PrintEmptyLine(1);
    SetPrintFont(24);
    strcpy(printBuff," ����Ʒ��ӯ���ͨ�ṩ����֧��");
    FillPrintBuff(printBuff);
    SetPrintFont(24);
    strcpy(printBuff,"     ��ϵ�绰��4008190900");
    FillPrintBuff(printBuff);
    strcpy(printBuff,"-----------------------------------");
    FillPrintBuff(printBuff);
    strcpy(printBuff,"���¹��λ���̵绰��4008190900");
    FillPrintBuff(printBuff);
    PrintEmptyLine(1);

    



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
    printAD();

    ClearPrintBuff();
    PrintEmptyLine(3);
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
    return;
}
void print_logo()
{
    char PrintBuff[40];
    int ret = 0;
START_PRINT:
    if(CheckPrinter() != TRUE) {
        printf("the printer is not working well!\n");
        goto end1;
    }
    ClearPrintBuff();

    PrintEmptyLine(2);
#if 1
#if 1
    memset(PrintBuff,0,sizeof(PrintBuff));
    SetPrintIndent(0);
    SetPrintFont(48);
#ifdef RECEIPT_CONF
    strcpy(PrintBuff,gRCP.rcp_title_line1);
    FillPrintBuff(PrintBuff);
    SetPrintFont(48);
    strcpy(PrintBuff,gRCP.rcp_title_line2);
    FillPrintBuff(PrintBuff);
    SetPrintFont(24);
    strcpy(PrintBuff,gRCP.rcp_title_address);
    FillPrintBuff(PrintBuff);
    strcpy(PrintBuff,gRCP.rcp_title_number);
    FillPrintBuff(PrintBuff);
#else
    strcpy(PrintBuff,"   ��������");
    FillPrintBuff(PrintBuff);
    SetPrintFont(48);
    strcpy(PrintBuff,"    GL Cafe");
    FillPrintBuff(PrintBuff);
    SetPrintFont(24);
    strcpy(PrintBuff,"  ��������·36�Ż�ó����D��1��");
    FillPrintBuff(PrintBuff);
    strcpy(PrintBuff,"      ���͵绰��58257262");
    FillPrintBuff(PrintBuff);
#endif
    
#else
    strcpy(PrintBuff,"  ��������·36�Ż�ó����D��1��");
    printf("PrintBuff:%d,��������·36�Ż�ó����D��1��:%d",strlen(PrintBuff), strlen("��������·36�Ż�ó����D��1��"));
    parseXML("/usr/local/logo.xml");
#endif
    strcpy(PrintBuff,"-----------------------------------");
    FillPrintBuff(PrintBuff);
    PrintEmptyLine(2);
    SetPrintFont(32);
    strcpy(PrintBuff,"    ֧����Ǯ��֧��");
    FillPrintBuff(PrintBuff);
#else
    SetPrintFont(32);
    strcpy(PrintBuff,"     ֧������Լ�̻�");
    FillPrintBuff(PrintBuff);
    strcpy(PrintBuff,"   �����ֻ�֧���³���");
    FillPrintBuff(PrintBuff);
    strcpy(PrintBuff,"-----------------------------------");
    FillPrintBuff(PrintBuff);
#endif



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
    return;
}

#ifdef ALIPAY_JIUYI
void print_logo()
{
    char PrintBuff[40];
    int ret = 0;
START_PRINT:
    if(CheckPrinter() != TRUE) {
        printf("the printer is not working well!\n");
        goto end1;
    }
    ClearPrintBuff();
    PrintEmptyLine(2);
    memset(PrintBuff,0,sizeof(PrintBuff));
    SetPrintIndent(0);
    SetPrintFont(48);
    strcpy(PrintBuff,"   ���������");
    FillPrintBuff(PrintBuff);
    SetPrintFont(48);
    strcpy(PrintBuff,"     JIU YI");
    FillPrintBuff(PrintBuff);
    SetPrintFont(24);
    strcpy(PrintBuff,"  ������ʯ��ɽ��ʵ�˴��5��");
    FillPrintBuff(PrintBuff);
    strcpy(PrintBuff,"      ���͵绰��88939699");
    FillPrintBuff(PrintBuff);
    strcpy(PrintBuff,"-----------------------------------");
    FillPrintBuff(PrintBuff);
    PrintEmptyLine(2);
    SetPrintFont(32);
    strcpy(PrintBuff,"    ֧����Ǯ��֧��");
    FillPrintBuff(PrintBuff);
 



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
    return;
}
#endif

//move Query print to a thread. to avoid missing key issue.
#ifdef ALIPAY_QUERY
void *thr_fn(void* arg)
{
    int ret = 0;
#ifdef ALIPAY_QUERY
    fd_set rset;
    struct timeval tv;
    int retval;
    int i;
#endif
#ifdef ALIPAY_QUERY
    int connection_fd;
    socklen_t address_length;
    int nbytes; 
    char buffer[1024];
    int trade_num;
    char *trade_ptr[100] = {NULL}; 
    char *trade_detail[5] = {NULL}; 
    struct receipt_info pos_receipt;
    char PrintBuff[30];
    T_DATETIME tTime;
    char pos_date[12];
    char pos_time[12];
#endif

#ifdef ALIPAY_QUERY
    int maxfd = 0;
    if(socket_fd != 0)
        maxfd = max(maxfd,socket_fd);
#endif
    while(1) {
        FD_ZERO(&rset);
        FD_SET(socket_fd, &rset);
        address_length = sizeof(address);

        /* Wait up to one seconds. */
        tv.tv_sec = 1;
        tv.tv_usec = 0; 
        retval = select(maxfd+1, &rset, NULL, NULL, &tv);
        //retval = select(maxfd+1, &rset, NULL, NULL, NULL);
        printf("select got return,go before FD_ISSET-----\n");
        if(FD_ISSET(socket_fd, &rset)) {
            if ((connection_fd = accept(socket_fd,
                            (struct sockaddr *) &address,
                            &address_length)) > -1)
            {

                nbytes = read(connection_fd, buffer, 1024);
                buffer[nbytes] = 0;

                printf("MESSAGE FROM ALIPAY: %s\n", buffer);
                //nbytes = snprintf(buffer, 256, "hello from the server");
                //write(connection_fd, buffer, nbytes);
                /* start print out the payment query result */

                trade_num = SplitStr(buffer,trade_ptr,"|");

                //write(tty_data.posfd,alipay_receipt,sizeof(alipay_receipt));
                ///write(tty_data.posfd,"\n",1);
                /* get system time */
                //time(&td);
                //ptr = localtime(&td);
                //strftime(pos_date,sizeof(pos_date),"%Y-%m-%d",ptr);
                //strftime(pos_time,sizeof(pos_time),"%H:%M:%S",ptr);
                GetDateTime(&tTime);
                sprintf(pos_date,"%s%s-%s-%s",tTime.century,tTime.year,tTime.month,tTime.day);
                sprintf(pos_time,"%s:%s:%s",tTime.hour,tTime.minute,tTime.second);

                for (i=0; i<trade_num; i++){
                    printf("number %d trade:%s\n",i,trade_ptr[i]);
                    SplitStr(trade_ptr[i],trade_detail,",");
                    memset(pos_receipt.serial_number,0,24);
                    memset(pos_receipt.out_trade_no,0,16);
                    memset(pos_receipt.trade_no,0,32);
                    memset(pos_receipt.total_fee,0,16);

                    strcpy(pos_receipt.serial_number,trade_detail[0]);
                    strcpy(pos_receipt.out_trade_no,trade_detail[1]);
                    strcpy(pos_receipt.trade_no,trade_detail[2]);
                    strcpy(pos_receipt.total_fee,trade_detail[3]);
                    ///WritePayment(1, &pos_receipt);
                    /// write(tty_data.posfd,"\n",1);
                    ///write(tty_data.posfd,"\n",1);
                    pthread_mutex_lock(&prmutex);
START_PRINT:
                    if(CheckPrinter() != TRUE) {
                        printf("the printer is not working well!\n");
                        pthread_mutex_unlock(&prmutex);
                        goto end1;
                    }
                    ClearPrintBuff();
                    memset(PrintBuff,0,30);
                    SetPrintIndent(100);
                    SetPrintFont(32);
                    strcpy(PrintBuff,"֧��������ƾ��");
                    FillPrintBuff(PrintBuff);
                    PrintEmptyLine(2);
                    SetPrintIndent(0);
                    SetPrintFont(32);
                    strcpy(PrintBuff,"���кţ�");
                    FillPrintBuff(PrintBuff);
                    FillPrintBuff(pos_receipt.serial_number);

                    strcpy(PrintBuff,"�̻������ţ�");
                    FillPrintBuff(PrintBuff);
                    FillPrintBuff(pos_receipt.out_trade_no);

                    strcpy(PrintBuff,"���ڣ�");
                    FillPrintBuff(PrintBuff);
                    FillPrintBuff(pos_date);

                    strcpy(PrintBuff,"ʱ�䣺");
                    FillPrintBuff(PrintBuff);
                    FillPrintBuff(pos_time);

                    strcpy(PrintBuff,"-------------------");
                    FillPrintBuff(PrintBuff);	   

                    strcpy(PrintBuff,"֧�������渶");
                    FillPrintBuff(PrintBuff);	   

                    strcpy(PrintBuff,"���׺ţ�");
                    FillPrintBuff(PrintBuff);
                    FillPrintBuff(pos_receipt.trade_no);

                    strcpy(PrintBuff,"��");
                    FillPrintBuff(PrintBuff);
                    FillPrintBuff(pos_receipt.total_fee);

                    strcpy(PrintBuff,"ǩ�� ");
                    FillPrintBuff(PrintBuff);

                    strcpy(PrintBuff,"����ͬ����������");
                    FillPrintBuff(PrintBuff);

                    PrintEmptyLine(3);	 

                    //��ʼ��ӡ    
                    ret =StartPrint();
                    pthread_mutex_unlock(&prmutex);
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
                    goto normal;
end1:  

                    FailBeep(); 
                    ClearLine(1, 9);
                    TextOut(0, 3, ALIGN_CENTER, "�����ӡ��"); 
                    TextOut(0, 4, ALIGN_CENTER, "��ӡʧ��");
                    WaitKey(2000);


                    goto normal;
end2:  

                    FailBeep(); 
                    ClearLine(1, 9);
                    TextOut(0, 3, ALIGN_CENTER, "��������"); 
                    TextOut(0, 4, ALIGN_CENTER, "�޷�ִ�д�ӡ");
                    WaitKey(2000);

normal:
                }
                close(connection_fd);
            }
        }
    }
    return NULL;
}
#endif


void querySingle(void)
{
    char prefix[12] = {0};
    unsigned long long prefixint;
    char hmno[7] = {0};
    char queryNo[18] = {0};
    int ret = 0;
    Clear();
    TextOut(0, 2, ALIGN_LEFT, "�����뽻�׵������кŵĺ�6λ");
    TextOut(0, 3, ALIGN_LEFT, "��ѯ���ս���");
    getSNoPre(prefix);
    printf("queryNO prefixint:\n");   
    printf("queryNO prefix:%s \n", prefix);   
    //sprintf(prefix, "%lld\0", prefixint);
    //TextOut(0, 5, ALIGN_LEFT, prefix);
    memcpy(queryNo,prefix,11);
    ret = Input(0,5,queryNo,17,IME_NUMBER,WHITE, RED,FALSE,TRUE,FALSE);
    if(ret != OK)
        return;
    //memcpy(queryNo,prefix,11);
    //memcpy(queryNo+11,hmno,6);
    printf("queryNo:%s\n",queryNo);
    //ret = alipay_query_single((unsigned long long)atoll(queryNo));
    
    ret = viewsingle((void*)&commTestOut, queryNo);
    if(ret)
    {
        char PrintBuff[30];
        Clear();
        TextOut(0, 2, ALIGN_CENTER, "�õ������ѳɹ�");
        TextOut(0, 3, ALIGN_CENTER, queryNo); 
START_PRINT:
        pthread_mutex_lock(&prmutex);
        if(CheckPrinter() != TRUE) {
            printf("the printer is not working well!\n");
            pthread_mutex_unlock(&prmutex);
            goto end1;
        }
        ClearPrintBuff();
        memset(PrintBuff,0,30);
        SetPrintIndent(100);
        SetPrintFont(32);
        strcpy(PrintBuff,"���½���ȷ�ѳɹ�");
        FillPrintBuff(PrintBuff);

        strcpy(PrintBuff,"���к�:");
        strcat(PrintBuff,queryNo);
        FillPrintBuff(PrintBuff);
        strcpy(PrintBuff,"����ʱ��:");
        strcat(PrintBuff, serial2date(queryNo));
        FillPrintBuff(PrintBuff);	   
        strcpy(PrintBuff,"�̻�������:");
        strcat(PrintBuff,commTestOut.out_trade_no);
        FillPrintBuff(PrintBuff);	   
        strcpy(PrintBuff,"��");
        strcat(PrintBuff, commTestOut.total_fee);
        FillPrintBuff(PrintBuff);

        PrintEmptyLine(3);	 
        ret =StartPrint();
        pthread_mutex_unlock(&prmutex);
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
        goto normal;
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

normal:
    } else {
        Clear();
        TextOut(0, 2, ALIGN_CENTER, "�õ�����ʧ��");
        WaitKey(2000);
    }

}

void refund(void)
{
    int ret = 0, i;
    T_DATETIME tTime;
    char PrintBuff[100];
    char order_time[13] = {0};
    char queryNo[18] = {0};
    char prefix[12] = {0};
    Clear();
    TextOut(0, 2, ALIGN_LEFT, "�����뽻�׵������кŵĺ�6λ");
    TextOut(0, 3, ALIGN_LEFT, "�˿�");
    getSNoPre(prefix);
    printf("queryNO prefixint:\n");   
    printf("queryNO prefix:%s \n", prefix);   
    //sprintf(prefix, "%lld\0", prefixint);
    //TextOut(0, 5, ALIGN_LEFT, prefix);
    memcpy(queryNo,prefix,11);
    ret = Input(0,5,queryNo,17,IME_NUMBER,WHITE, RED,FALSE,TRUE,FALSE);
    if(ret != OK)
        return;
    //memcpy(queryNo,prefix,11);
    //memcpy(queryNo+11,hmno,6);
    printf("queryNo:%s\n",queryNo);
    ret = createrefund((void*)&commTestOut,queryNo,"0"); //refund all
    
START_PRINT:
        pthread_mutex_lock(&prmutex);
        if(CheckPrinter() != TRUE) {
            printf("the printer is not working well!\n");
            pthread_mutex_unlock(&prmutex);
            goto end1;
        }
        ClearPrintBuff();
        memset(PrintBuff,0,30);
        SetPrintIndent(100);
        SetPrintFont(32);
        strcpy(PrintBuff,"�˿�ɹ�");
        FillPrintBuff(PrintBuff);
        strcpy(PrintBuff,"���к�:");
        strcat(PrintBuff,queryNo);
        strcpy(PrintBuff,"����ʱ�䣺");
        strcat(PrintBuff, serial2date(queryNo));
        FillPrintBuff(PrintBuff);	   
        strcpy(PrintBuff,"�̻�������:");
        strcat(PrintBuff,commTestOut.out_trade_no);
        FillPrintBuff(PrintBuff);	   
        strcpy(PrintBuff,"��");
        strcat(PrintBuff, commTestOut.total_fee);
        FillPrintBuff(PrintBuff);
        PrintEmptyLine(2);	 
        ret =StartPrint();
        pthread_mutex_unlock(&prmutex);
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
        goto normal;
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
normal:
}

int getSWmd5(char* md5sum, char* version)
{
    
    int ret = 0;
    printf("enter getSWmd5\n");
    memset((void*)&commTestOut, 0, sizeof(commTestOut));
    ret = preImsi((void*)&commTestOut,ALI_LASTESTMD5);
    printf("after preImsi\n");
    strcpy(md5sum,commTestOut.md5sum);
    strcpy(version,commTestOut.version);
    printf("md5sum:%s, version:%s\n",md5sum, version);
    return 0;
}

void qrexchange(void)
{
    int ret = 0, i;
    T_DATETIME tTime;
    char PrintBuff[100];
    char order_time[23] = {0};
    GetDateTime(&tTime);
    sprintf(order_time, "%s%s-%s-%s|%s:%s:%s", 
            tTime.century, tTime.year, tTime.month, tTime.day,
            tTime.hour, tTime.minute, tTime.second);
    Clear();
    TextOut(0, 3, ALIGN_LEFT, "ǩ��");
    ret = preImsi((void*)&commTestOut,ALI_EXCHANGE);
    printf("return qrexchange preImsi\n");
    
START_PRINT:
        pthread_mutex_lock(&prmutex);
        if(CheckPrinter() != TRUE) {
            printf("the printer is not working well!\n");
            pthread_mutex_unlock(&prmutex);
            goto end1;
        }
        ClearPrintBuff();
        memset(PrintBuff,0,30);
        SetPrintIndent(100);
        SetPrintFont(32);
        strcpy(PrintBuff,"ǩ���ɹ�");
        FillPrintBuff(PrintBuff);
        strcpy(PrintBuff,"��ʼʱ��:");
        FillPrintBuff(PrintBuff);
        strcpy(PrintBuff,order_time);
        FillPrintBuff(PrintBuff);
        PrintEmptyLine(3);	 
        ret =StartPrint();
        pthread_mutex_unlock(&prmutex);
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
        goto normal;
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
normal:
}

int qrexchangedorder(void)
{
    int ret = 0, i;
    int trade_num;
    char trade_numstr[64] = {0};
    char *trade_ptr[2000] = {NULL}; 
    char *trade_detail[5] = {NULL}; 
    char pos_date[12];
    char pos_time[12];
    T_DATETIME tTime;
    struct receipt_info pos_receipt;
    char PrintBuff[100];
    unsigned int total24h_fee = 0;
    char total24h_feestr[16] = {0};
    Clear();
    TextOut(0, 3, ALIGN_LEFT, "���㣨ǩ�ˣ�");
    //ret = alipay_query_24h(result24h);
    memset(result24h, 0, sizeof(result24h));
    memset(commTestOut.order, 0, sizeof(commTestOut.order));
    ret = preImsi((void*)&commTestOut,ALI_EXCHANGEORDER);
    strcpy(result24h,commTestOut.order);

    trade_num = SplitStr(result24h,trade_ptr,"|");

    pthread_mutex_lock(&prmutex);
START_PRINT:
    if(CheckPrinter() != TRUE) {
        printf("the printer is not working well!\n");
        pthread_mutex_unlock(&prmutex);
        goto end1;
    }
    ClearPrintBuff();
    memset(PrintBuff,0,sizeof(PrintBuff));
    SetPrintIndent(0);
    SetPrintFont(24);

#ifdef RECEIPT_CONF
    strcpy(PrintBuff,gRCP.rcp_title_company);
#else
    strcpy(PrintBuff,"��������������޹�˾�����ó��");
#endif
 //   strcpy(PrintBuff,"��ѯ��24Сʱ�ɹ�����");

    FillPrintBuff(PrintBuff);	   

    strcpy(PrintBuff,"ǩ��ʱ�䣺");
    strcat(PrintBuff,commTestOut.exchange_start_time);
    FillPrintBuff(PrintBuff);
    strcpy(PrintBuff,"ǩ��ʱ�䣺");
    strcat(PrintBuff,commTestOut.exchange_end_time);
    FillPrintBuff(PrintBuff);
    PrintEmptyLine(1);	 
    strcpy(PrintBuff,"------------------");
    FillPrintBuff(PrintBuff);

    ret = StartPrint();
    DebugOut("print error code:[%d]\n", ret);
    if(ret != 0) {   
        if(ret == -1)
            goto START_PRINT;
        else if(ret == -2)
            goto end2;
        else if(ret == -3)
            goto end1;
    }
    ClearPrintBuff();
    memset(PrintBuff,0,sizeof(PrintBuff));
    SetPrintIndent(0);
    SetPrintFont(24);

    for (i=0; i<trade_num; i++){
        printf("number %d trade:%s\n",i,trade_ptr[i]);
        SplitStr(trade_ptr[i],trade_detail,",");
        memset(pos_receipt.serial_number,0,24);
        memset(pos_receipt.out_trade_no,0,16);
        memset(pos_receipt.trade_no,0,32);
        memset(pos_receipt.total_fee,0,16);

        strcpy(pos_receipt.serial_number,trade_detail[0]);
        strcpy(pos_receipt.out_trade_no,trade_detail[1]);
        strcpy(pos_receipt.trade_no,trade_detail[2]);
        strcpy(pos_receipt.total_fee,trade_detail[3]);

        total24h_fee += Money2int(trade_detail[3]);

        printf("total24h_fee:%d", total24h_fee);
        strcpy(PrintBuff,"ʱ�䣺");
        strcat(PrintBuff, serial2date(pos_receipt.serial_number));
        FillPrintBuff(PrintBuff);	   
        strcpy(PrintBuff,"���кţ�");
        strcat(PrintBuff, pos_receipt.serial_number);
        FillPrintBuff(PrintBuff);	   
        strcpy(PrintBuff,"�̻������ţ�");
        strcat(PrintBuff, pos_receipt.out_trade_no);
        FillPrintBuff(PrintBuff);	   
        strcpy(PrintBuff,"���׺ţ�");
        strcat(PrintBuff,  pos_receipt.trade_no);
        FillPrintBuff(PrintBuff);	   
        strcpy(PrintBuff,"��");
        strcat(PrintBuff, pos_receipt.total_fee);
        FillPrintBuff(PrintBuff);	   
        strcpy(PrintBuff,"------------------");
        FillPrintBuff(PrintBuff);
        if(i%5 == 0)  {
            //because of FillPrintBuff may overflow so print segmentlly
            ret = StartPrint();
            DebugOut("print error code:[%d]\n", ret);
            if(ret != 0) {   
                if(ret == -1) 
                    goto START_PRINT;
                else if(ret == -2)
                    goto end2;
                else if(ret == -3)
                    goto end1;
            }
            ClearPrintBuff();
            memset(PrintBuff,0,sizeof(PrintBuff));
            SetPrintIndent(0);
            SetPrintFont(24);
        }
    }
    
    strcpy(PrintBuff,"=====================");
    FillPrintBuff(PrintBuff);
    ret = StartPrint();
    DebugOut("print error code:[%d]\n", ret);
    printf("print error code:[%d]\n", ret);
    if(ret != 0) {   
        if(ret == -1)
            goto START_PRINT;
        else if(ret == -2)
             goto end2;
        else if(ret == -3)
             goto end1;
    }
    ClearPrintBuff();
    memset(PrintBuff,0,sizeof(PrintBuff));
    SetPrintIndent(0);
    SetPrintFont(32);

    sprintf(total24h_feestr,"%d", total24h_fee);
    printf("\nbefore:%s\n", total24h_feestr);
    Moneyformat(total24h_feestr);
    printf("\nafter:%s\n", total24h_feestr);
    printf("total24h_feestr:%s", total24h_feestr);
    strcpy(PrintBuff,"�ܽ�");
    strcat(PrintBuff, total24h_feestr);
    FillPrintBuff(PrintBuff);	   
    //memset(PrintBuff,0,sizeof(PrintBuff));
    sprintf(trade_numstr, "�ܵ���:%d", trade_num);
    strcpy(PrintBuff, trade_numstr);
    FillPrintBuff(PrintBuff);	   
    PrintEmptyLine(3);	 
    ret = StartPrint();
    pthread_mutex_unlock(&prmutex);
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
    goto normal;
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

normal:
}

void query24h(void)
{
    int ret = 0, i;
    int trade_num;
    char trade_numstr[64] = {0};
    char *trade_ptr[2000] = {NULL}; 
    char *trade_detail[5] = {NULL}; 
    char pos_date[12];
    char pos_time[12];
    T_DATETIME tTime;
    struct receipt_info pos_receipt;
    char PrintBuff[100];
    unsigned int total24h_fee = 0;
    char total24h_feestr[16] = {0};
    Clear();
    TextOut(0, 3, ALIGN_LEFT, "��ѯ��24Сʱ�ɹ�����");
    //ret = alipay_query_24h(result24h);
    memset(result24h, 0, sizeof(result24h));
    memset((void*)&commTestOut, 0, sizeof(commTestOut));
    ret = preImsi((void*)&commTestOut,ALI_QUERY_24H);
    strcpy(result24h,commTestOut.order);

    trade_num = SplitStr(result24h,trade_ptr,"|");

    pthread_mutex_lock(&prmutex);
START_PRINT:
    if(CheckPrinter() != TRUE) {
        printf("the printer is not working well!\n");
        pthread_mutex_unlock(&prmutex);
        goto end1;
    }
    ClearPrintBuff();
    memset(PrintBuff,0,sizeof(PrintBuff));
    SetPrintIndent(0);
    SetPrintFont(24);

#ifdef RECEIPT_CONF
    strcpy(PrintBuff,gRCP.rcp_title_company);
#else
    strcpy(PrintBuff,"��������������޹�˾�����ó��");
#endif
 //   strcpy(PrintBuff,"��ѯ��24Сʱ�ɹ�����");
#ifdef ALIPAY_JIUYI
    strcpy(PrintBuff,"�����������Բ����������޹�˾");
#endif

    FillPrintBuff(PrintBuff);	   
    GetDateTime(&tTime);
    sprintf(pos_date,"%s%s-%s-%s",tTime.century,tTime.year,tTime.month,tTime.day);
    sprintf(pos_time,"%s:%s:%s",tTime.hour,tTime.minute,tTime.second);
    strcpy(PrintBuff,"����ʱ�䣺");
    strcat(PrintBuff,pos_date);
    strcat(PrintBuff," ");
    strcat(PrintBuff,pos_time);
    FillPrintBuff(PrintBuff);
    PrintEmptyLine(1);	 
    strcpy(PrintBuff,"------------------");
    FillPrintBuff(PrintBuff);

    ret = StartPrint();
    DebugOut("print error code:[%d]\n", ret);
    if(ret != 0) {   
        if(ret == -1)
            goto START_PRINT;
        else if(ret == -2)
            goto end2;
        else if(ret == -3)
            goto end1;
    }
    ClearPrintBuff();
    memset(PrintBuff,0,sizeof(PrintBuff));
    SetPrintIndent(0);
    SetPrintFont(24);

    for (i=0; i<trade_num; i++){
        printf("number %d trade:%s\n",i,trade_ptr[i]);
        SplitStr(trade_ptr[i],trade_detail,",");
        memset(pos_receipt.serial_number,0,24);
        memset(pos_receipt.out_trade_no,0,16);
        memset(pos_receipt.trade_no,0,32);
        memset(pos_receipt.total_fee,0,16);

        strcpy(pos_receipt.serial_number,trade_detail[0]);
        strcpy(pos_receipt.out_trade_no,trade_detail[1]);
        strcpy(pos_receipt.trade_no,trade_detail[2]);
        strcpy(pos_receipt.total_fee,trade_detail[3]);

        total24h_fee += Money2int(trade_detail[3]);

        printf("total24h_fee:%d", total24h_fee);
        strcpy(PrintBuff,"ʱ�䣺");
        strcat(PrintBuff, serial2date(pos_receipt.serial_number));
        FillPrintBuff(PrintBuff);	   
        strcpy(PrintBuff,"���кţ�");
        strcat(PrintBuff, pos_receipt.serial_number);
        FillPrintBuff(PrintBuff);	   
        strcpy(PrintBuff,"�̻������ţ�");
        strcat(PrintBuff, pos_receipt.out_trade_no);
        FillPrintBuff(PrintBuff);	   
        strcpy(PrintBuff,"���׺ţ�");
        strcat(PrintBuff,  pos_receipt.trade_no);
        FillPrintBuff(PrintBuff);	   
        strcpy(PrintBuff,"��");
        strcat(PrintBuff, pos_receipt.total_fee);
        FillPrintBuff(PrintBuff);	   
        strcpy(PrintBuff,"------------------");
        FillPrintBuff(PrintBuff);
        if(i%5 == 0)  {
            //because of FillPrintBuff may overflow so print segmentlly
            ret = StartPrint();
            DebugOut("print error code:[%d]\n", ret);
            if(ret != 0) {   
                if(ret == -1) 
                    goto START_PRINT;
                else if(ret == -2)
                    goto end2;
                else if(ret == -3)
                    goto end1;
            }
            ClearPrintBuff();
            memset(PrintBuff,0,sizeof(PrintBuff));
            SetPrintIndent(0);
            SetPrintFont(24);
        }
    }
    
    strcpy(PrintBuff,"=====================");
    FillPrintBuff(PrintBuff);
    ret = StartPrint();
    DebugOut("print error code:[%d]\n", ret);
    printf("print error code:[%d]\n", ret);
    if(ret != 0) {   
        if(ret == -1)
            goto START_PRINT;
        else if(ret == -2)
             goto end2;
        else if(ret == -3)
             goto end1;
    }
    ClearPrintBuff();
    memset(PrintBuff,0,sizeof(PrintBuff));
    SetPrintIndent(0);
    SetPrintFont(32);

#if 1
    sprintf(total24h_feestr,"%d", total24h_fee);
    printf("\nbefore:%s\n", total24h_feestr);
    Moneyformat(total24h_feestr);
    printf("\nafter:%s\n", total24h_feestr);
    printf("total24h_feestr:%s", total24h_feestr);
    strcpy(PrintBuff,"�ܽ�");
    strcat(PrintBuff, total24h_feestr);
    FillPrintBuff(PrintBuff);	   
    //memset(PrintBuff,0,sizeof(PrintBuff));
    sprintf(trade_numstr, "�ܵ���:%d", trade_num);
    strcpy(PrintBuff, trade_numstr);
    FillPrintBuff(PrintBuff);	   
//#else
    strcpy(PrintBuff,"�ܽ�");
    strcat(PrintBuff, commTestOut.amount_total);
    FillPrintBuff(PrintBuff);
    strcpy(PrintBuff,"���˿��");
    strcat(PrintBuff, commTestOut.refund_amount);
    FillPrintBuff(PrintBuff);
    strcpy(PrintBuff,"��ʣ���");
    strcat(PrintBuff, commTestOut.remain_amount);
    FillPrintBuff(PrintBuff);
    sprintf(trade_numstr, "�ܵ���:%d", commTestOut.order_total);
    strcpy(PrintBuff, trade_numstr);
    FillPrintBuff(PrintBuff);
#endif
    PrintEmptyLine(3);	 
    ret = StartPrint();
    pthread_mutex_unlock(&prmutex);
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
    goto normal;
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

normal:
}

static char Defualtdata[] = "yy-mm-dd/hh:mm";
char* serial2date(char* serialNo)
{
    char* ret = &Defualtdata[0];
    Defualtdata[0] = serialNo[5];
    Defualtdata[1] = serialNo[6];

    Defualtdata[3] = serialNo[7];
    Defualtdata[4] = serialNo[8];

    Defualtdata[6] = serialNo[9];
    Defualtdata[7] = serialNo[10];

    Defualtdata[9] = serialNo[11];
    Defualtdata[10] = serialNo[12];

    Defualtdata[12] = serialNo[13];
    Defualtdata[13] = serialNo[14];
    return ret;
}

#ifdef RECEIPT_CONF
int SetReceiptInfo()
{
        int ret;
        char buff[200];
        int ucKey;

        while(1)
        {

        Clear();
        SetScrFont(FONT20, WHITE);
        TextOut(0, 1, ALIGN_CENTER, "СƱ����");

        ShowBmpFile(90, 60, "pic/button.bmp");
        TextOutByPixel(100, 65, "1.����1");

        ShowBmpFile(90, 95, "pic/button.bmp");
        TextOutByPixel(100, 100, "2.����2");

        ShowBmpFile(90, 130, "pic/button.bmp");
        TextOutByPixel(100, 135, "3.��ַ��Ϣ");

        ShowBmpFile(90, 165, "pic/button.bmp");
        TextOutByPixel(100, 170, "4.�绰��Ϣ");

        ShowBmpFile(90, 200, "pic/button.bmp");
        TextOutByPixel(100, 205, "5.��˾����");

        ucKey=WaitLimitKey("\x01\x02\x03\x04\x05\x12\x0E",7,0);

        switch(ucKey)
        {
        case KEY_CANCEL:
        case KEY_BACKSPACE:
              return OK;
              break;
        
        case 1:  
        while(1)
        {
             Clear();
             SetScrFont(FONT20, WHITE);
             TextOut(0, 1, ALIGN_CENTER, "������СƱ�����һ��:");
             SetScrFont(FONT12, WHITE);
             TextOut(0, 5, ALIGN_CENTER, "�������8�����ֻ���16��Ӣ���ַ��ͷ���");
             TextOut(0, 6, ALIGN_CENTER, "��F1���л����뷨��#���ڷ��������뷨�д���ո�");
             TextOut(0, 7, ALIGN_CENTER, "0���л���Сд������ƴ��ʱ����*��#��������ѡ��");
             memset(buff, 0, sizeof(buff));

             TextOut(4, 9, ALIGN_LEFT, "ԭСƱ���⣺");
             TextOut(14, 9, ALIGN_LEFT, gRCP.rcp_title_line1);
             //sprintf(buff, "%s", gRCP.rcp_title_line1);
             //memcpy(buff,gRCP.rcp_title_line1,10);
             SetScrFont(FONT20, RED);
             //sprintf(buff, "%s", "12345");
             //ret = Input(2, 5, buff, 50, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, TRUE);
             ret = Input(4,6, buff,16, IME_CHINESE, BLACK, GREEN, FALSE, FALSE, TRUE);
             if(ret != OK)
             {
                DebugOut("ret=[%d]\n", ret); 
                break;
             }     
             if(strlen(buff) == 0){
                 SetScrFont(FONT20, WHITE);
                 TextOut(0,8, ALIGN_CENTER,"���벻��Ϊ��");
                 Wait(1000);
                 continue;
             }

             ClearClient();
             TextOut(0, 1, ALIGN_LEFT, "������������:");
             TextOut(0, 3, ALIGN_LEFT, buff);
             strcpy(gRCP.rcp_title_line1,buff);

             WaitKey(0);
                if(WriteData("test-receipt.dat", &gRCP, sizeof(T_RECEIPT), 0) == FALSE)
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
                TextOut(2, 4, ALIGN_CENTER, "���óɹ�!");
                WaitKey(2000);
                break;
              
        }
        break;
        
        case 2:
        while(1)
        {
             Clear();
             SetScrFont(FONT20, WHITE);
             TextOut(0, 1, ALIGN_CENTER, "������СƱ����ڶ���:");
             SetScrFont(FONT12, WHITE);
             TextOut(0, 5, ALIGN_CENTER, "�������8�����ֻ���16��Ӣ���ַ��ͷ���");
             TextOut(0, 6, ALIGN_CENTER, "��F1���л����뷨��#���ڷ��������뷨�д���ո�");
             TextOut(0, 7, ALIGN_CENTER, "0���л���Сд������ƴ��ʱ����*��#��������ѡ��");
             memset(buff, 0, sizeof(buff));
             TextOut(4, 9, ALIGN_LEFT, "ԭСƱ���⣺");
             TextOut(14, 9, ALIGN_LEFT, gRCP.rcp_title_line2);
             SetScrFont(FONT20, RED);
             ret = Input(4,6, buff,16, IME_CHINESE, BLACK, GREEN, FALSE, FALSE, TRUE);
             if(ret != OK)
             {
                DebugOut("ret=[%d]\n", ret); 
                break;
             }     
             if(strlen(buff) == 0){
                 SetScrFont(FONT20, WHITE);
                 TextOut(0,8, ALIGN_CENTER,"���벻��Ϊ��");
                 Wait(1000);
                 continue;
             }

             ClearClient();
             TextOut(0, 1, ALIGN_LEFT, "������������:");
             TextOut(0, 3, ALIGN_LEFT, buff);
             strcpy(gRCP.rcp_title_line2,buff);

             WaitKey(0);
                if(WriteData("test-receipt.dat", &gRCP, sizeof(T_RECEIPT), 0) == FALSE)
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
                TextOut(2, 4, ALIGN_CENTER, "���óɹ�!");
                WaitKey(2000);
                break;
              
        }
        break;
        

        case 3:
        while(1)
        {
             Clear();
             SetScrFont(FONT20, WHITE);
             TextOut(0, 1, ALIGN_CENTER, "������СƱ�ϵ�ַ��Ϣ:");
             SetScrFont(FONT12, WHITE);
             TextOut(0, 5, ALIGN_CENTER, "�������16�����ֻ���32��Ӣ���ַ��ͷ���");
             TextOut(0, 6, ALIGN_CENTER, "��F1���л����뷨��#���ڷ��������뷨�д���ո�");
             TextOut(0, 7, ALIGN_CENTER, "0���л���Сд������ƴ��ʱ����*��#��������ѡ��");
             memset(buff, 0, sizeof(buff));
             TextOut(4, 9, ALIGN_LEFT, "ԭСƱ��ַ��");
             TextOut(14, 9, ALIGN_LEFT, gRCP.rcp_title_address);
             SetScrFont(FONT20, RED);
             ret = Input(4, 6, buff, 32, IME_CHINESE, BLACK, GREEN, FALSE, FALSE, TRUE);
             if(ret != OK)
             {
                DebugOut("ret=[%d]\n", ret); 
                break;
             }     
             if(strlen(buff) == 0){
                 SetScrFont(FONT20, WHITE);
                 TextOut(0,8, ALIGN_CENTER,"���벻��Ϊ��");
                 Wait(1000);
                 continue;
             }

             ClearClient();
             TextOut(0, 1, ALIGN_LEFT, "������������:");
             TextOut(0, 3, ALIGN_LEFT, buff);
             strcpy(gRCP.rcp_title_address,buff);

             WaitKey(0);
                if(WriteData("test-receipt.dat", &gRCP, sizeof(T_RECEIPT), 0) == FALSE)
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
                TextOut(2, 4, ALIGN_CENTER, "���óɹ�!");
                WaitKey(2000);
                break;
              
        }
        break;
        
        case 4:
        while(1)
        {
             Clear();
             SetScrFont(FONT20, WHITE);
             TextOut(0, 1, ALIGN_CENTER, "������СƱ�ϵ绰��Ϣ:");
             SetScrFont(FONT12, WHITE);
             TextOut(0, 5, ALIGN_CENTER, "�������16�����ֻ���32��Ӣ���ַ��ͷ���");
             TextOut(0, 6, ALIGN_CENTER, "��F2��������ַ���:+,-,:��");
             TextOut(0, 7, ALIGN_CENTER, "0���л���Сд������ƴ��ʱ����*��#��������ѡ��");
             memset(buff, 0, sizeof(buff));
             TextOut(4, 9, ALIGN_LEFT, "ԭСƱ�绰��Ϣ:");
             TextOut(14, 9, ALIGN_LEFT, gRCP.rcp_title_number);
             SetScrFont(FONT20, RED);
             ret = Input(4, 6, buff, 32, IME_CHINESE, BLACK, GREEN, FALSE, FALSE, TRUE);
             if(ret != OK)
             {
                DebugOut("ret=[%d]\n", ret); 
                break;
             }     
             if(strlen(buff) == 0){
                 SetScrFont(FONT20, WHITE);
                 TextOut(0,8, ALIGN_CENTER,"���벻��Ϊ��");
                 Wait(1000);
                 continue;
             }

             ClearClient();
             TextOut(0, 1, ALIGN_LEFT, "������������:");
             TextOut(0, 3, ALIGN_LEFT, buff);
             strcpy(gRCP.rcp_title_number,buff);

             WaitKey(0);
                if(WriteData("test-receipt.dat", &gRCP, sizeof(T_RECEIPT), 0) == FALSE)
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
                TextOut(2, 4, ALIGN_CENTER, "���óɹ�!");
                WaitKey(2000);
                break;
              
        }
        break; 

       
        case 5:  
        while(1)
        {
             Clear();
             SetScrFont(FONT20, WHITE);
             TextOut(0, 1, ALIGN_CENTER, "�������սᵥ�Ϲ�˾����:");
             SetScrFont(FONT12, WHITE);
             TextOut(0, 5, ALIGN_CENTER, "�������16�����ֻ���32��Ӣ���ַ��ͷ���");
             TextOut(0, 6, ALIGN_CENTER, "��F1���л����뷨��#���ڷ��������뷨�д���ո�");
             TextOut(0, 7, ALIGN_CENTER, "0���л���Сд������ƴ��ʱ����*��#��������ѡ��");
             memset(buff, 0, sizeof(buff));
             TextOut(4, 9, ALIGN_LEFT, "ԭ��˾���ƣ�");
             TextOut(14, 9, ALIGN_LEFT, gRCP.rcp_title_company);
             SetScrFont(FONT20, RED);
             ret = Input(4, 6, buff, 32, IME_CHINESE, BLACK, GREEN, FALSE, FALSE, TRUE);
             if(ret != OK)
             {
                DebugOut("ret=[%d]\n", ret); 
                break;
             }     
             if(strlen(buff) == 0){
                 SetScrFont(FONT20, WHITE);
                 TextOut(0,8, ALIGN_CENTER,"���벻��Ϊ��");
                 Wait(1000);
                 continue;
             }

             ClearClient();
             TextOut(0, 1, ALIGN_LEFT, "������������:");
             TextOut(0, 3, ALIGN_LEFT, buff);
             strcpy(gRCP.rcp_title_company,buff);

             WaitKey(0);
                if(WriteData("test-receipt.dat", &gRCP, sizeof(T_RECEIPT), 0) == FALSE)
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
                TextOut(2, 4, ALIGN_CENTER, "���óɹ�!");
                WaitKey(2000);
                break;
              
        }
        break; 
 FAILED:
        memset(&gRCP, 0, sizeof(T_RECEIPT));
        ReadData("test-receipt.dat", &gRCP,sizeof(T_RECEIPT), 0);
        break;
        } //switch

        } //while
}
#endif


