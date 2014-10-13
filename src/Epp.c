/***************************************************************************
* Copyright (c) 2007-2010, NEW POS Technology.
* All rights reserved.
*
* �ļ����ƣ�Epp.c
* ����������   ������NEW8110�ϵ�N20 EPPӦ��API�ӿڣ���Ҫʵ��������̵Ļ����ӽ��ܹ���
               // ������ϸ˵���˳����ļ���ɵ���Ҫ���ܣ�������ģ������Ľ�
*              // �ڣ����ֵ��ȡֵ��Χ�����弰������Ŀ��ơ�˳�򡢶���������
*              // �ȹ�ϵ
* ��������:    // �����������ݵ�˵��
*
* �� �ߣ�
* �汾��1.0
* ������ڣ�200x��xx��xx��
*
* �汾�޸���ʷ��Ϣ
*
* ���� ���ƿ���
* �汾��1.0
* �޸����� ��1������
* ������ڣ�2010��05��17��
****************************************************************************/
#include "Main.h"
#define _PRINT_DEBUG_
#define EPP_PORT PORT_COM1

#define EPP_RECV_PACKET_MAX_LEN 5050

#define  EPP_SEND_BUFFLEN      (8*1024)

#define CMD_CLEAR_ALL_APP_KEY    0x010c
#define CMD_CLEAR_IDLE_LOGO      0x0115

#define CMD_GET_RANDOM_NUMBER        0x0000
#define CMD_GET_SYSTEM_INFO          0x0001
#define CMD_BEEP                     0x0002
#define CMD_LIGHT                    0x0003

#define CMD_DISPLAY_LOGO             0x0100
#define CMD_CLEAR_SCREEN             0x0101
#define CMD_DISPLAY_STRING           0x0102
#define CMD_LOAD_IDLE_LOGO           0x0103
#define CMD_RESTORE_IDLE_LOGO        0x0104

#define CMD_KB_GET_STRING            0x0200

#define CMD_DOWNLOAD_LCK_MTEK        0x0300
#define CMD_DOWNLOAD_AIK_AUTH1       0x0301
#define CMD_DOWNLOAD_AIK_AUTH2       0x0302
#define CMD_DOWNLOAD_APP_INIT_KEY    0x0303
#define CMD_DKEY_AUTH_STEP1          0x0304
#define CMD_DKEY_AUTH_STEP2          0x0305
#define CMD_DOWNLOAD_KEY             0x0306
#define CMD_DOWNLOAD_DUKPT_KEY       0x0307

#define CMD_FORMAT_PED               0x0340
#define CMD_CLEAR_ALL_ONE_KEY        0x0341
#define CMD_CLEAR_ONE_KEY            0x0342

#define CMD_UKEY_AUTH_STEP1          0x0380
#define CMD_UKEY_AUTH_STEP2          0x0381
#define CMD_GET_MAC                  0x0382
#define CMD_GET_PIN                  0x0383
#define CMD_GET_FIXED_MAC            0x0384
#define CMD_GET_FIXED_PIN            0x0385
#define CMD_GET_DUKPT_MAC            0x0386
#define CMD_GET_DUKPT_PIN            0x0387
#define CMD_SET_PIN_TIMEOUT          0x0388
#define CMD_GET_TDEA                 0x0389
#define CMD_SET_TDES_IV              0x038a
// for factory
#define CMD_ENTER_FACTORY_TEST       0xf100
#define CMD_SET_PED_SN               0xf101
#define CMD_DOWNLOAD_UBSK            0xf102
#define CMD_CLEAR_EEPROM             0xf103

#define RET_MODULE_SYSTEM_INFO      0x00
#define RET_MODULE_KEY_BOARD        0x00
#define RET_MODULE_LCD_SCREEN       0x00
#define RET_MODULE_PED              0x00
#define RET_MODULE_COMMUNICATION    0x00
#define RET_MODULE_IC_CARD          0x00
#define RET_MODULE_MAGIC_CARD       0x00
#define RET_MODULE_FACTORY          0x00

#define KEY_INDEX_NUMBER        100

typedef struct _EPP_CONFIGURE_
{
    BYTE abyLck[16];
    BYTE abyMtek[24];
    BYTE abyAppName[32];
    BYTE abyAKDAK[16];
    BYTE abyAKUAK[16];
    BYTE abyMDTEK[24];
    BYTE abyMUTEK[24];
    BYTE byFlag;
    BYTE abyRev[3];
    int  iPort;
    BYTE abyMac[4];
}EPP_CONFIGURE;   // 164 bytes

static BYTE g_EppSendBuff[EPP_SEND_BUFFLEN];
static BYTE g_EppRecvBuff[EPP_SEND_BUFFLEN];

static const WORD g_awEpphalfCrc16CCITT[16]={ /* CRC ���ֽ���ʽ�� */
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef
};

static const BYTE g_abyEppDefaultLck[16] = {0xde,0x21,0xcb,0x34,0xb6,0x25,0x34,0x33,0x87,0x98,
    0x9b,0xb5,0x39,0x81,0x42,0x49};

static const BYTE g_abyEppDefaultMtek[24] = {0x1a,0xc4,0xb9,0xc8,0x7b,0xde,0x8c,0x27,0x9b,0x4d,
    0xfe,0x3a,0x64,0x8b,0xcf,0x3f,0x93,0xca,0x02,0x2b,0x02,0x56,0x06,0x12};

static const BYTE g_abyEppDefaultAkdak[16]={0x26,0x90,0x77,0xa3,0x33,0x4d,0x32,0xb1,0x14,0xdb,0x04,0x2d,0x1d,0xa0,0x44,0xdb};

static const BYTE g_abyEppDefaultAkuak[16]={0x98,0xa4,0x9f,0xca,0x31,0x2b,0xcc,0x7e,0xa8,0x01,0x66,0xe1,0x8b,0x2b,0x0c,0xa6};

static const BYTE g_abyEppDefaultMdtek[24]={0x75,0x72,0x4d,0xb9,0x3a,0x73,0xe0,0x44,0x6e,0xf6,
    0xb1,0x7c,0xe8,0x1c,0x5d,0x97,0x0b,0xa4,0x4a,0x79,0x8f,0xc8,0xeb,0x18};

static const BYTE g_abyEppDefaultMutek[24]={0xef,0x02,0xb7,0x68,0x8e,0xe1,0x88,0x24,0x0c,0x50,
    0xa8,0xf0,0x22,0x2d,0xaf,0xe5,0x07,0xdd,0xd9,0x97,0x54,0xa8,0xe0,0x2c};

static const BYTE g_abyDefaultAppName[12] = {0x4e,0x45,0x57,0x20,0x50,0x4f,0x53,0x20,0x41,0x50,0x50,0x00};

static const BYTE g_abyEppMainKey[8] = {0x39, 0xc2, 0xb4, 0xf7, 0xd1, 0xb0, 0xe4, 0x84};

static EPP_CONFIGURE g_sEppConfigure;
static int g_iEppReadConfigureFlag = 0;

static int g_iEppPortNum = 0;
//static int g_iEppPortOpenFlag = 0;

//static BYTE g_byRetError = 0;

static const BYTE g_abySecuryPassword[8] = {0xab,0x87,0x98,0x56,0xcf,0xde,0xa3,0x19};

static const BYTE g_abyIdleLogoFileHead[62] =
{
    0x42, 0x4D, 0x3E, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x28, 0x00,
    0x00, 0x00, 0x7A, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00
};

static const BYTE g_abyNormalLogoFileHead[62] =
{
    0x42, 0x4D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x28, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00
};

static int s_EppSends(const BYTE *SendBuf, DWORD SendLen)
{
    //return portSends(g_iEppPortNum, (BYTE*)SendBuf, SendLen);
    return WriteUart(g_iEppPortNum, (BYTE*)SendBuf, SendLen);
}

static int s_EppRecv(BYTE *RecvBuf, DWORD TimeOutMs, int nRecvLen)
{
    	int nRet = 0;
    	nRet = ReadUart(g_iEppPortNum, (BYTE*)RecvBuf, nRecvLen, TimeOutMs);
	if (nRet <= 0)
	{
		return EPP_RECV_TIMEOUT;
	}
	return nRet;
}

#define _PRINT_DEBUG_
#ifdef  _PRINT_DEBUG_
BYTE g_abySendBuffPrint[10240];
BYTE g_abyRecvBuffPrint[10240];
int g_iSendPrintLen = 0;
int g_iRecvPrintLen = 0;
#endif

/****************************************************************************
  ������     :  void Crc16CCITT(BYTE *pbyDataIn, DWORD dwDataLen, BYTE abyCrcOut[2])
  ����       :  ����λ�ķ�������һ�����ֵ�16λCRC-CCITTУ��ֵ
  �������   :  1��BYTE *pbyDataIn : Ҫ����16λCRC-CCITT�������
                2��WORD dwDataLen : pbyDataIn����ĳ������ֵ65535
  �������   :  1��BYTE abyCrcOut[2] : 16λCRC-CCITT����Ľ��
  ����ֵ     :  ��
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-03-30  V1.0         ����
****************************************************************************/
static void s_EppCrc16CCITT(const BYTE *pbyDataIn, DWORD dwDataLen, BYTE abyCrcOut[2])
{
    WORD wCrc = 0;
    BYTE byTemp;
    while (dwDataLen-- != 0)
    {
        byTemp = ((BYTE)(wCrc>>8))>>4;
        wCrc <<= 4;
        wCrc ^= g_awEpphalfCrc16CCITT[byTemp^(*pbyDataIn/16)];
        byTemp = ((BYTE)(wCrc>>8))>>4;
        wCrc <<= 4;
        wCrc ^= g_awEpphalfCrc16CCITT[byTemp^(*pbyDataIn&0x0f)];
        pbyDataIn++;
    }
    abyCrcOut[0] = wCrc/256;
    abyCrcOut[1] = wCrc%256;
}

/****************************************************************************
  ������     :  int Crc16SendPacket(BYTE *pbySendData, WORD wDataLen, BYTE byCmd)
  ����       :  ���ݰ����ͺ�������CRC16-CCITTУ��
  �������   :  1��BYTE *pbySendData��Ҫ���͵����ݰ�
                2��WORD wDataLen�����ݰ�����
                3��BYTE byCmd��������
  �������   :  ��
  ����ֵ     :  SUCCESS�����ͳɹ� / SEND_PACKET_ERROR�����ʹ���
                / PACKET_LEN_TOO_LONG
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-03-30  V1.0         ����
****************************************************************************/
static int s_EppCrc16SendPacket(WORD wDataLen, WORD wCmd)
{
    int iRet;
    int i = 0;

    if (wDataLen > 8900)
    {
        return EPP_PACKET_LEN_TOO_LONG;
    }
    g_EppSendBuff[0] = 0x02;
    g_EppSendBuff[1] = (BYTE)(wCmd>>8);
    g_EppSendBuff[2] = (BYTE)(wCmd);
    g_EppSendBuff[3] = wDataLen/256;
    g_EppSendBuff[4] = wDataLen%256;
    s_EppCrc16CCITT(&g_EppSendBuff[1], wDataLen+4, &g_EppSendBuff[wDataLen+5]);

	printf("\n");
    for (i = 0; i < wDataLen + 7; i++)
	{
		printf("%02x", g_EppSendBuff[i]);
	}
	printf("\n");
    iRet = s_EppSends(g_EppSendBuff, wDataLen+7);
    if (-1 == iRet || 0 == iRet)
    {
        return EPP_SEND_PACKET_ERROR;
    }
	
#ifdef  _PRINT_DEBUG_
    memcpy(&g_abySendBuffPrint[g_iSendPrintLen], g_EppSendBuff, wDataLen+7);
    g_iSendPrintLen += wDataLen+7;
    memset(&g_abySendBuffPrint[g_iSendPrintLen], 0xff, 4);
    g_iSendPrintLen += 4;
#endif

    return EPP_SUCCESS;
}


/****************************************************************************
  ������     :  int Crc16RecvPacket(BYTE *pbyRecvData, WORD *pwPacketetLen, DWORD dwTimeoutMs)
  ����       :  ���ݰ����պ�������CRC16-CCITTУ��
  �������   :  1��DWORD dwTimeoutMs�����ճ�ʱʱ�䣬ʱ�䵥λ�Ǻ���
  �������   :  1��BYTE *pbyRecvData�����յ����������ݣ�������ͷ��У�飬����
                   ��pbyRecvDataָ����ڴ治��С��256�ֽ�
                2��WORD *pwPacketetLen�����յ����������ݵĳ���
  ����ֵ     :  EPP_SUCCESS�����ճɹ� / EPP_CRC_CHECK_ERROR�����ݰ�CRCУ�����
                / EPP_PACKET_LEN_ERROR�����ݰ����ȴ��� / EPP_RECV_TIMEOUT����ʱ
                / EPP_RECV_PACKET_ERROR�����մ��� /EPP_USER_PRESS_CANCEL
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-03-30  V1.0         ����
****************************************************************************/
static int s_EppCrc16RecvPacket(BYTE *pbyRecvData, WORD *pwPacketetLen, DWORD dwTimeoutMs)
{
    BYTE abyCrc[2];
    int i, iRet;
    WORD wPacketLen = 0;

    	iRet = s_EppRecv(pbyRecvData, 3, 1); // timeout = 3ms
	if (EPP_RECV_TIMEOUT == iRet || 0x02 != pbyRecvData[0])
	{
		return EPP_RECV_TIMEOUT;
	}
    	for (i=0; i<4; i++)
    	{
        	iRet = s_EppRecv(&pbyRecvData[i+1], 3, 1);
        	if (EPP_RECV_TIMEOUT == iRet)
		{
            		return EPP_RECV_PACKET_ERROR;
        	}
    	}
    	wPacketLen = pbyRecvData[3]*256 + pbyRecvData[4];
    	*pwPacketetLen = wPacketLen + 7;
    	if (wPacketLen > EPP_RECV_PACKET_MAX_LEN)
	{
        	return EPP_PACKET_LEN_ERROR;
    	}
    	for (i=0; i<wPacketLen+2; i++)
    	{
        	iRet = s_EppRecv(&pbyRecvData[i+5], 3, 1);
        	if (EPP_RECV_TIMEOUT == iRet)
        	{
            		return EPP_RECV_PACKET_ERROR;
        	}
    	}
    	s_EppCrc16CCITT(&pbyRecvData[1], wPacketLen+4, abyCrc);
    	if (0 != memcmp(abyCrc, &pbyRecvData[5+wPacketLen], 2))
	{
        	return EPP_CRC_CHECK_ERROR;
    	}

#ifdef  _PRINT_DEBUG_
        memcpy(&g_abyRecvBuffPrint[g_iRecvPrintLen], pbyRecvData, *pwPacketetLen);
        g_iRecvPrintLen += *pwPacketetLen;
        memset(&g_abyRecvBuffPrint[g_iRecvPrintLen], 0xff, 4);
        g_iRecvPrintLen += 4;
#endif

    return EPP_SUCCESS;
}

/*void s_EppMultiDes(const BYTE *inData, int iMulti, BYTE *outData,
         const BYTE *key, BYTE byKeyLen, BYTE mode)
{
    int i, j;

    for (i=0; i<iMulti; i++)
    {
        j = i<<3;
        TDEA((BYTE*)&inData[j], &outData[j], (BYTE*)key, byKeyLen, mode);
    }
}*/

/*static void s_EppComputeMacCBC(const BYTE *pbyDataIn, int iDataLen,
    const BYTE *pbyKeyIn, BYTE byKeyLen, BYTE *pbyMacOut)
{
    BYTE abyTemp[10];
    int i;

    memset(abyTemp, 0, sizeof(abyTemp));
    for (i=0; i<iDataLen; i++)
    {
        abyTemp[i&0x07] ^= pbyDataIn[i];
        if (0 == ((i+1)&0x07))
        {
            TDEA(abyTemp, pbyMacOut, (BYTE*)pbyKeyIn, byKeyLen, TDEA_ENCRYPT);
            memcpy(abyTemp, pbyMacOut, 8);
        }
    }
    if (0 != (i&0x07))
    {
        TDEA(abyTemp, pbyMacOut, (BYTE*)pbyKeyIn, byKeyLen, TDEA_ENCRYPT);
    }
}
*/
static void s_EppSetDefaultConfig(EPP_CONFIGURE *psCfg)
{
    memcpy(psCfg->abyLck, g_abyEppDefaultLck, 16);
    memcpy(psCfg->abyMtek, g_abyEppDefaultMtek, 24);
    memset(psCfg->abyAppName, 0, 32);
    memcpy(psCfg->abyAppName, g_abyDefaultAppName, 12);
    memcpy(psCfg->abyAKDAK, g_abyEppDefaultAkdak, 16);
    memcpy(psCfg->abyAKUAK, g_abyEppDefaultAkuak, 16);
    memcpy(psCfg->abyMDTEK, g_abyEppDefaultMdtek, 24);
    memcpy(psCfg->abyMUTEK, g_abyEppDefaultMutek, 24);
    psCfg->byFlag = 0x03;
    g_iEppReadConfigureFlag = 1;
}
/*

static int s_EppGetConfig(EPP_CONFIGURE *psCfg)
{
    if (0 == g_iEppReadConfigureFlag)
    {
        s_EppSetDefaultConfig(&g_sEppConfigure);
    }
    memcpy(psCfg, &g_sEppConfigure, sizeof(EPP_CONFIGURE));
    return EPP_SUCCESS;
}

static void s_EppLoadKeyInitial(const BYTE *pbyKsnIn, BYTE byKsnLen,
                      const BYTE *pbyBdkIn, BYTE *pbyKeyOut, BYTE *abyCurKSNOut)
{
    BYTE abyTemp[16], abyCurBdk[16];
    int i;

    memcpy(abyCurBdk, (BYTE*)pbyBdkIn, 16);
    memset(abyCurKSNOut, 0xff, 10);
    memcpy(&abyCurKSNOut[10-byKsnLen], (BYTE*)pbyKsnIn, byKsnLen);
    memset(&abyCurKSNOut[8], 0, 2);
    abyCurKSNOut[7] &= 0xe0;
    TDEA(abyCurKSNOut, pbyKeyOut, abyCurBdk, 16, TDEA_ENCRYPT);
    for (i=0; i<4; i++)
    {
        abyTemp[i] = abyCurBdk[i]^0xc0;
        abyTemp[i+4] = abyCurBdk[i+4];
        abyTemp[i+8] = abyCurBdk[i+8]^0xc0;
        abyTemp[i+12] = abyCurBdk[i+12];
    }
    TDEA(abyCurKSNOut, &pbyKeyOut[8], abyTemp, 16, TDEA_ENCRYPT);
}
*/
static void s_EppPortClear(void)
{
    char szBuff[10240];
    DWORD dwLen = 0;
    //portReset(g_iEppPortNum);
    ReadUart(g_iEppPortNum, szBuff, dwLen, 1);
}

static void s_EppCheckCfg(void)
{
    if (0 == g_iEppReadConfigureFlag)
    {
        s_EppSetDefaultConfig(&g_sEppConfigure);
    }
}


int EppClose(void)
{
    //if (0 != g_iEppPortOpenFlag)
    {
       // g_iEppPortOpenFlag = 0;
        return SERIAL_Close(g_iEppPortNum);
    }
    return 0;
}

int EppOpen(void)
{
    int iHandle = 0;

    SwitchCom0_Pinpad();
    //g_iEppPortOpenFlag = 0;
    if((iHandle = SERIAL_Open("/dev/ttyS0", 115200)) < 0)
    {
        //g_iEppPortOpenFlag = 0;
        printf("Open Pinpad RS232 error!");
        FailBeep();
        TextOut(0, 3, ALIGN_CENTER, "���ڴ򲻿�!");
        Wait(2000);
        return ERROR;
    }
    //g_iEppPortOpenFlag = 1;
    printf("�򿪴��ڳɹ�\n");
    g_iEppPortNum = iHandle;
    return iHandle;
}

/****************************************************************************
  ������     :  int EppInit(const BYTE *pbyLck, const BYTE *pbyMtek, const BYTE *pbyAppName,
                      const BYTE *pbyAkdak, const BYTE *pbyAkuak, const BYTE *pbyMdtek,
                      const BYTE *pbyMutek)
  ����       :  �޸ĵ�ǰ��Կ���ã������ʹ��Ĭ�����ã�ÿ���豸������Ҫ��ʼ������
  �������   :  1��const BYTE *pbyLck ��16�ֽ���Կ
                2��const BYTE *pbyMtek ��24�ֽ���Կ
                3��const BYTE *pbyAppName ���16�ֽڵ�Ӧ����
                4��const BYTE *pbyAkdak ��16�ֽ���Կ
                5��const BYTE *pbyAkuak ��16�ֽ���Կ
                6��const BYTE *pbyMdtek ��24�ֽ���Կ
                7��const BYTE *pbyMutek ��24�ֽ���Կ
  �������   :  ��
  ����ֵ     :  EPP_SUCCESS
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
int EppInit(const BYTE *pbyLck, const BYTE *pbyMtek, const BYTE *pbyAppName, const BYTE *pbyAkdak,
    const BYTE *pbyAkuak, const BYTE *pbyMdtek, const BYTE *pbyMutek)
{
    memcpy(g_sEppConfigure.abyLck, pbyLck, 16);
    memcpy(g_sEppConfigure.abyMtek, pbyMtek, 24);
    memset(g_sEppConfigure.abyAppName, 0, 32);
    strcpy((char*)g_sEppConfigure.abyAppName, (char*)pbyAppName);
    memcpy(g_sEppConfigure.abyAKDAK, pbyAkdak, 16);
    memcpy(g_sEppConfigure.abyAKUAK, pbyAkuak, 16);
    memcpy(g_sEppConfigure.abyMDTEK, pbyMdtek, 24);
    memcpy(g_sEppConfigure.abyMUTEK, pbyMutek, 24);
    g_iEppReadConfigureFlag = 1;
    return EPP_SUCCESS;
}

/****************************************************************************
  ������     :  int EppDownloadLckMtek(void)
  ����       :  ����ǰ�����е�LCK��MTEK���ص�N20��
  �������   :  ��
  �������   :  ��
  ����ֵ     :  EPP_SUCCESS / EPP_CRC_CHECK_ERROR / EPP_SEND_CMD_ERROR
                / EPP_PACKET_LEN_ERROR / EPP_RECV_TIMEOUT
                / EPP_RECV_PACKET_ERROR / EPP_USER_PRESS_CANCEL
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
int EppDownloadLckMtek(void)
{
    int iRet;
    WORD wRecvLen;

    s_EppPortClear();
    s_EppCheckCfg();

    memcpy(&g_EppSendBuff[5], g_sEppConfigure.abyLck, 16);
    memcpy(&g_EppSendBuff[21], g_sEppConfigure.abyMtek, 24);
    iRet = s_EppCrc16SendPacket(40, CMD_DOWNLOAD_LCK_MTEK);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as011"); GetKey();
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 100000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as012"); GetKey();
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    return EPP_SUCCESS;
}


/****************************************************************************
  ������     :  int EppDownloadAik(void)
  ����       :  ����ǰ������AIK���ص�N20�ϡ�AIK����AppName��AKDAK/AKUAK/MDTEK/MUTEK��4����Կ��
  �������   :  ��
  �������   :  ��
  ����ֵ     :  EPP_SUCCESS / EPP_CRC_CHECK_ERROR / EPP_SEND_CMD_ERROR
                / EPP_PACKET_LEN_ERROR / EPP_RECV_TIMEOUT / EPP_RECV_LEN_ERROR
                / EPP_RECV_PACKET_ERROR / EPP_USER_PRESS_CANCEL / EPP_AUTHEN_FAILED
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
/*int EppDownloadAik(void)
{
    int iRet;
    WORD wRecvLen;
    BYTE abyRand[10], abyTek[64], abyMac[8];

    s_EppPortClear();
    s_EppCheckCfg();

    PedGetRandom(&g_EppSendBuff[5]);
    memcpy(abyRand, &g_EppSendBuff[5], 8);
    iRet = s_EppCrc16SendPacket(8, CMD_DOWNLOAD_AIK_AUTH1);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (75 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }
    TDEA(&g_EppRecvBuff[9], &g_EppSendBuff[20], g_sEppConfigure.abyLck, 16, TDEA_DECRYPT);
    if (0 != memcmp(abyRand,&g_EppSendBuff[20],8))
    {
        return EPP_AUTHEN_FAILED;
    }

    s_EppMultiDes(&g_EppRecvBuff[25], 6, abyTek, g_sEppConfigure.abyMtek, 24, TDEA_DECRYPT);

    TDEA(&g_EppRecvBuff[17], &g_EppSendBuff[9], g_sEppConfigure.abyLck, 16, TDEA_ENCRYPT);
    g_EppSendBuff[5] = 0;
    g_EppSendBuff[6] = 0;
    g_EppSendBuff[7] = RET_MODULE_PED;
    g_EppSendBuff[8] = 0;
    iRet = s_EppCrc16SendPacket(12, CMD_DOWNLOAD_AIK_AUTH2);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }

    memset(g_EppRecvBuff, 0, 1024);
    memcpy(g_EppRecvBuff, g_sEppConfigure.abyAppName, 16);
    memcpy(&g_EppRecvBuff[32], g_sEppConfigure.abyAKDAK, 16);
    TDEA(&g_EppRecvBuff[500], &g_EppRecvBuff[48], g_sEppConfigure.abyAKDAK, 16, TDEA_ENCRYPT);
    memcpy(&g_EppRecvBuff[50], g_sEppConfigure.abyAKUAK, 16);
    TDEA(&g_EppRecvBuff[500], &g_EppRecvBuff[66], g_sEppConfigure.abyAKUAK, 16, TDEA_ENCRYPT);
    memcpy(&g_EppRecvBuff[68], g_sEppConfigure.abyMDTEK, 24);
    TDEA(&g_EppRecvBuff[500], &g_EppRecvBuff[92], g_sEppConfigure.abyMDTEK, 24, TDEA_ENCRYPT);
    memcpy(&g_EppRecvBuff[94], g_sEppConfigure.abyMUTEK, 24);
    TDEA(&g_EppRecvBuff[500], &g_EppRecvBuff[118], g_sEppConfigure.abyMUTEK, 24, TDEA_ENCRYPT);
    s_EppMultiDes(g_EppRecvBuff, 15, &g_EppSendBuff[5], abyTek, 24, TDEA_ENCRYPT);

    s_EppComputeMacCBC(&g_EppSendBuff[5], 120, &abyTek[24], 24, &g_EppSendBuff[125]);
    memcpy(abyMac, &g_EppSendBuff[125], 8);

    iRet = s_EppCrc16SendPacket(124, CMD_DOWNLOAD_APP_INIT_KEY);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }

    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 13000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }
    return EPP_SUCCESS;
}
*/

/****************************************************************************
  ������     :  int EppDownloadAppKey(BYTE byKeyType, BYTE byMode, BYTE byKeyIndex,
                     const BYTE *pbyKeyDataIn, BYTE byKeyLen, BYTE byMasterKeyIndex)
  ����       :  Ӧ����Կ����
  �������   :  1��BYTE byKeyType ����Կ����
                            0x01������Կ��
                            0x02��MAC��Կ��
                            0x03��PIN��Կ��
                            0x10��Fixed MAC��Կ��
                            0x11��Fixed PIN��Կ��
                2��BYTE byKeyIndex ����Կ����[1��100]
                3��BYTE byMode ��
                         Bit0~3  TDEA_DECRYPT    0x00    ���ý��ܷ����õ�����Ŀ��Key
                                 TDEA_NONE       0x02    ֱ��д������Ŀ��Key(��MAC key��PIN key��Ч)
                         Bit4~7  PARITY_NONE     0x00    ��(���ܺ��)Key������У��
                                 PARITY_ODD      0x10    ��(���ܺ��)Key���Ľ�����У��
                                 PARITY_EVEN     0x20    ��(���ܺ��)Key���Ľ���żУ��
                4��const BYTE *pbyKeyDataIn ����Կ����
                5��BYTE byKeyLen ����Կ���ȣ���ȡֵ8/16/24
                6��BYTE byMasterKeyIndex ������Կ����[1��100]��ֻ����Կ������MAC��Կ����
                        PIN��Կ��ʱ�򣬸ò�������Ч
  �������   :  ��
  ����ֵ     :  EPP_SUCCESS / EPP_CRC_CHECK_ERROR / EPP_SEND_CMD_ERROR / EPP_KEY_TYPE_ERROR
                / EPP_PACKET_LEN_ERROR / EPP_RECV_TIMEOUT / EPP_RECV_LEN_ERROR
                / EPP_RECV_PACKET_ERROR / EPP_USER_PRESS_CANCEL
                / EPP_MASTER_KEY_INDEX_ERROR / EPP_KEY_INDEX_ERROR / EPP_INPUT_DATA_LEN_ERROR
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
/*int EppDownloadAppKey(BYTE byKeyType, BYTE byMode, BYTE byKeyIndex,
    const BYTE *pbyKeyDataIn, BYTE byKeyLen, BYTE byMasterKeyIndex)
{
    int iRet, k;
    BYTE abyRand[10], abyTek[64];
    WORD wRecvLen;

    if ((KEY_TYPE_MASTER!=byKeyType) && (KEY_TYPE_MAC!=byKeyType)
        && (KEY_TYPE_PIN!=byKeyType) && (KEY_TYPE_FIXED_MAC!=byKeyType)
        && (KEY_TYPE_FIXED_PIN!=byKeyType))
    {
        return EPP_KEY_TYPE_ERROR;
    }
    if ((KEY_TYPE_MASTER!=byKeyType) && ((byMasterKeyIndex>KEY_INDEX_NUMBER)||(0==byMasterKeyIndex)))
    {
        return EPP_MASTER_KEY_INDEX_ERROR;
    }
    if ((byKeyIndex>KEY_INDEX_NUMBER) || (0==byKeyIndex))
    {
        return EPP_KEY_INDEX_ERROR;
    }
    if ((byKeyLen!=8) && (byKeyLen!=16) && (byKeyLen!=24))
    {
        return EPP_INPUT_DATA_LEN_ERROR;
    }

    s_EppPortClear();
    s_EppCheckCfg();

    memset(g_EppSendBuff, 0, 1024);
    memcpy(&g_EppSendBuff[5], g_sEppConfigure.abyAppName, 16);
    PedGetRandom(&g_EppSendBuff[37]);
//    memset(&g_EppSendBuff[37], 0x31, 8);
    memcpy(abyRand, &g_EppSendBuff[37], 8);
    iRet = s_EppCrc16SendPacket(40, CMD_DKEY_AUTH_STEP1);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as031"); GetKey();
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as032=%s,",g_sEppConfigure.abyAppName); GetKey();
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {//lcdPrintf("as033"); GetKey();
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (75 != wRecvLen)
    {//lcdPrintf("as034"); GetKey();
        return EPP_RECV_LEN_ERROR;
    }
    TDEA(&g_EppRecvBuff[9], &g_EppSendBuff[20], g_sEppConfigure.abyAKDAK, 16, TDEA_DECRYPT);
    if (0 != memcmp(abyRand,&g_EppSendBuff[20],8))
    {
*//*    lcdCls();
    lcdDisplay(0,0,0,"as035=%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x,",
        abyRand[0], abyRand[1], abyRand[2], abyRand[3], abyRand[4], abyRand[5],
        abyRand[6], abyRand[7]);
    lcdDisplay(0,2,0,"%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x,",
        g_EppSendBuff[20], g_EppSendBuff[21], g_EppSendBuff[22], g_EppSendBuff[23],
        g_EppSendBuff[24], g_EppSendBuff[25], g_EppSendBuff[26], g_EppSendBuff[27]);
    lcdDisplay(0,4,0,"%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x,",
        g_EppRecvBuff[9], g_EppRecvBuff[10], g_EppRecvBuff[11], g_EppRecvBuff[12],
        g_EppRecvBuff[13], g_EppRecvBuff[14],
        g_EppRecvBuff[15], g_EppRecvBuff[16]);
    GetKey();*/
  /*      return EPP_AUTHEN_FAILED;
    }

    s_EppMultiDes(&g_EppRecvBuff[25], 6, abyTek, g_sEppConfigure.abyMDTEK, 24, TDEA_DECRYPT);

    TDEA(&g_EppRecvBuff[17], &g_EppSendBuff[9], g_sEppConfigure.abyAKDAK, 16, TDEA_ENCRYPT);
    g_EppSendBuff[5] = 0;
    g_EppSendBuff[6] = 0;
    g_EppSendBuff[7] = RET_MODULE_PED;
    g_EppSendBuff[8] = 0;
    iRet = s_EppCrc16SendPacket(12, CMD_DKEY_AUTH_STEP2);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as036"); GetKey();
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as037"); GetKey();
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {//lcdPrintf("as038"); GetKey();
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {//lcdPrintf("as039"); GetKey();
        return EPP_RECV_LEN_ERROR;
    }

    memset(g_EppRecvBuff, 0, 1024);
    g_EppRecvBuff[0] = byKeyType;  // Key type = fixed mac key
    g_EppRecvBuff[1] = byMode;  //
    g_EppRecvBuff[2] = byMasterKeyIndex;  //
    g_EppRecvBuff[3] = byKeyIndex;  // Key Index = 1;
    g_EppRecvBuff[4] = byKeyLen;  // Key Length=16
    memset(&g_EppRecvBuff[5], 0x13, byKeyLen+4);
    memcpy(&g_EppRecvBuff[5], pbyKeyDataIn, byKeyLen);
    k = byKeyLen/8;
    k++;
    s_EppMultiDes(g_EppRecvBuff, k, &g_EppSendBuff[5], abyTek, 24, TDEA_ENCRYPT);

    s_EppComputeMacCBC(&g_EppSendBuff[5], byKeyLen+8, &abyTek[24], 24, &g_EppSendBuff[byKeyLen+13]);

    iRet = s_EppCrc16SendPacket(byKeyLen+12, CMD_DOWNLOAD_KEY);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as03a"); GetKey();
        return EPP_SEND_CMD_ERROR;
    }

    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 30000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as03b"); GetKey();
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {//lcdPrintf("as03c"); GetKey();
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {//lcdPrintf("as03d"); GetKey();
        return EPP_RECV_LEN_ERROR;
    }
    return EPP_SUCCESS;
}
*/
/****************************************************************************
  ������     :  int EppDownloadDukptKey(BYTE byKeyIndex,  BYTE *pbyBDK, BYTE *pbyKSN,
                    BYTE byKSNLen)
  ����       :  Ӧ����Կ����
  �������   :  1��BYTE byKeyIndex ����Կ������ȡֵ��Χ[1,32]
                2��BYTE *pbyBDK ��16�ֽ�BDK���룬δ����ɢ��BDK
                3��BYTE *pbyKSN ��KSN����
                4��BYTE byKSNLen ��KSN����[1,10]
  �������   :  ��
  ����ֵ     :  EPP_SUCCESS/EPP_OPEN_FILE_ERROR/EPP_SEEK_FILE_ERROR/EPP_READ_FILE_ERROR/
                EPP_CONFIGURE_INVALID/EPP_CONFIGURE_MAC_ERROR/EPP_SEND_CMD_ERROR/
                EPP_RECV_CMD_ERROR/EPP_RECV_RET_ERROR/EPP_RECV_LEN_ERROR/EPP_AUTHEN_FAILED
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
/*int EppDownloadDukptKey(BYTE byKeyIndex,  BYTE *pbyBDK, BYTE *pbyKSN,
       BYTE byKSNLen)
{
    int iRet;
    BYTE abyRand[10], abyTek[64], abyInitKey[24], abyCurKsn[16];
    WORD wRecvLen;

    s_EppPortClear();

    s_EppCheckCfg();


    memset(g_EppSendBuff, 0, 1024);
    memcpy(&g_EppSendBuff[5], g_sEppConfigure.abyAppName, 16);
    PedGetRandom(&g_EppSendBuff[37]);
    memcpy(abyRand, &g_EppSendBuff[37], 8);
    iRet = s_EppCrc16SendPacket(40, CMD_DKEY_AUTH_STEP1);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[5])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[5]);
    }
    if ((72!=wRecvLen) && (48!=wRecvLen))
    {
        return EPP_RECV_LEN_ERROR;
    }
    TDEA(&g_EppRecvBuff[6], &g_EppSendBuff[20], g_sEppConfigure.abyAKDAK, 16, TDEA_DECRYPT);
    if (0 != memcmp(abyRand,&g_EppSendBuff[20],8))
    {
        return EPP_AUTHEN_FAILED;
    }

	if (72 == wRecvLen)
    {
	    s_EppMultiDes(&g_EppRecvBuff[22], 6, abyTek, g_sEppConfigure.abyMDTEK, 24, TDEA_DECRYPT);
    }
	else
    {
	    s_EppMultiDes(&g_EppRecvBuff[22], 3, abyTek, g_sEppConfigure.abyMDTEK, 24, TDEA_DECRYPT);
		memcpy(&abyTek[24], abyTek, 24);
    }

    TDEA(&g_EppRecvBuff[14], &g_EppSendBuff[6], g_sEppConfigure.abyAKDAK, 16, TDEA_ENCRYPT);
    g_EppSendBuff[5] = 0;
    iRet = s_EppCrc16SendPacket(9, CMD_DKEY_AUTH_STEP2);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[5])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[5]);
    }
    if (8 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }

    s_EppLoadKeyInitial(pbyKSN, byKSNLen, pbyBDK, abyInitKey, abyCurKsn);
    memset(g_EppRecvBuff, 0, 1024);
    g_EppRecvBuff[0] = byKeyIndex-1;
    g_EppRecvBuff[1] = 8;  //
    memcpy(&g_EppRecvBuff[2], abyCurKsn, 8);
    s_EppCrc16CCITT(&g_EppRecvBuff[2], 10, &g_EppRecvBuff[12]);
	g_EppRecvBuff[14] = 16;
    memcpy(&g_EppRecvBuff[15], abyInitKey, 16);

    s_EppMultiDes(g_EppRecvBuff, 5, &g_EppSendBuff[5], abyTek, 24, TDEA_ENCRYPT);

    s_EppComputeMacCBC(&g_EppSendBuff[5], 40, &abyTek[24], 24, &g_EppSendBuff[45]);

    iRet = s_EppCrc16SendPacket(44, CMD_DOWNLOAD_DUKPT_KEY);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }

    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 30000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[5])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[5]);
    }
    if (8 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }
    return EPP_SUCCESS;
}
*/


/****************************************************************************
  ������     :  int EppGetMac(BYTE byKeyType, BYTE byKeyIndex, const BYTE *pbyMacDataIn,
                        WORD wMacLen, BYTE byMode, BYTE *pbyMacOut)
  ����       :  MAC����API
  �������   :  1��BYTE byKeyType ����Կ���͡�KEY_TYPE_MAC/KEY_TYPE_FIXED_MAC/KEY_TYPE_DUKPT
                2��BYTE byKeyIndex ��MAC��Կ�����������MAC����Fixed MAC��ȡֵ[1,100]��
                                     �����DUKPT MAC���ȡֵ[1,32]
                3��const BYTE *pbyMacDataIn �����������MAC����
                4��WORD wMacLen ��MAC���ݳ��ȣ�������8������������СֵΪ8�����ֵΪ2024
                5��BYTE byMode �������㷨ѡ��
                                     0x00	�㷨1
                                     0x01	�㷨2
                                     0x02	EMV2000�㷨
                                     0x03	�й������㷨
  �������   :  1��BYTE *pbyMacOut ��8�ֽ�MAC�������������������DUKPT_MAC_KEY����ǰ8���ֽ�
                   ��MAC����������10���ֽ��ǵ�ǰKSN��
  ����ֵ     :  EPP_SUCCESS/EPP_SEND_CMD_ERROR/EPP_RECV_CMD_ERROR/EPP_RECV_RET_ERROR/
                EPP_RECV_LEN_ERROR/EPP_AUTHEN_FAILED/
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
// INT32  PedGetMac(UINT16 MacKeyID, UINT8 *DataIn, UINT16 InLen, INT32 Mode, UINT8 *MacOut)
/*int EppGetMac(BYTE byKeyType, BYTE byKeyIndex, const BYTE *pbyMacDataIn,
                        WORD wMacLen, BYTE byMode, BYTE *pbyMacOut)
{
    int iRet, i;
    BYTE abyRand[10], abyTek[64], abyTemp[8];
    WORD wRecvLen;

    s_EppPortClear();
    if ((KEY_TYPE_MAC!=byKeyType) && (KEY_TYPE_FIXED_MAC!=byKeyType) && (KEY_TYPE_DUKPT_MAC!=byKeyType))
    {
        return EPP_INPUT_CMD_ERROR;
    }
    if ((0==byKeyIndex) || (byKeyIndex>100))
    {
        return EPP_INPUT_KEY_INDEX_ERROR;
    }

    if ((0!=(wMacLen%8)) || (0==wMacLen) || (wMacLen>2024))
    {
        return EPP_INPUT_MAC_LEN_ERROR;
    }
    if (byMode > 0x03)
    {
        return EPP_INPUT_MODE_ERROR;
    }
    if ((NULL==pbyMacDataIn) || (NULL==pbyMacOut))
    {
        return EPP_INPUT_PARAM_ERROR;
    }

    s_EppCheckCfg();


    memset(g_EppSendBuff, 0, 1024);
    memcpy(&g_EppSendBuff[5], g_sEppConfigure.abyAppName, 16);
    PedGetRandom(&g_EppSendBuff[37]);
    memcpy(abyRand, &g_EppSendBuff[37], 8);
    iRet = s_EppCrc16SendPacket(40, CMD_UKEY_AUTH_STEP1);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as021"); GetKey();
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as022"); GetKey();
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {//lcdPrintf("as023"); GetKey();
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (75 != wRecvLen)
    {//lcdPrintf("as024"); GetKey();
        return EPP_RECV_LEN_ERROR;
    }
    TDEA(&g_EppRecvBuff[9], &g_EppSendBuff[20], g_sEppConfigure.abyAKUAK, 16, TDEA_DECRYPT);
    if (0 != memcmp(abyRand,&g_EppSendBuff[20],8))
    {//lcdPrintf("as025"); GetKey();
        return EPP_AUTHEN_FAILED;
    }

	s_EppMultiDes(&g_EppRecvBuff[25], 6, abyTek, g_sEppConfigure.abyMUTEK, 24, TDEA_DECRYPT);

    TDEA(&g_EppRecvBuff[17], &g_EppSendBuff[9], g_sEppConfigure.abyAKUAK, 16, TDEA_ENCRYPT);
    g_EppSendBuff[5] = 0;
    g_EppSendBuff[6] = 0;
    g_EppSendBuff[7] = RET_MODULE_PED;
    g_EppSendBuff[8] = 0;
    iRet = s_EppCrc16SendPacket(12, CMD_UKEY_AUTH_STEP2);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as026"); GetKey();
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as027=%d,", iRet); GetKey();
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {//lcdPrintf("as028"); GetKey();
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {//lcdPrintf("as029"); GetKey();
        return EPP_RECV_LEN_ERROR;
    }

    memset(g_EppRecvBuff, 0, 1024);

    g_EppRecvBuff[0] = byKeyIndex;
    g_EppRecvBuff[1] = byMode;  //abyTemp

    // 20110412 0935 �ƿ��� ���ӣ�Ϊ������  begin
    if ((MAC_MODE_2==byMode) || (MAC_MODE_CUP==byMode))
    {
        memset(abyTemp, 0, 8);
        for (i=0; i<wMacLen; i++)
        {
            abyTemp[i&0x07] ^= pbyMacDataIn[i];
        }
        memcpy(&g_EppRecvBuff[2], abyTemp, 8);
        wMacLen = 8;
    }
    else
    {
    // 20110412 0935 �ƿ��� ����  end

        memcpy(&g_EppRecvBuff[2], pbyMacDataIn, wMacLen);
    }
//    memset(&g_EppRecvBuff[wMacLen+2], 0x33, 8);
    PedGetRandom(&g_EppRecvBuff[wMacLen+2]);
    s_EppMultiDes(g_EppRecvBuff, (wMacLen+8)/8, &g_EppSendBuff[5], abyTek, 24, TDEA_ENCRYPT);
    s_EppComputeMacCBC(&g_EppSendBuff[5], wMacLen+8, &abyTek[24], 24, &g_EppSendBuff[wMacLen+13]);
    switch (byKeyType)
    {
    case KEY_TYPE_MAC:
        iRet = s_EppCrc16SendPacket(wMacLen+12, CMD_GET_MAC);
        break;
    case KEY_TYPE_FIXED_MAC:
        iRet = s_EppCrc16SendPacket(wMacLen+12, CMD_GET_FIXED_MAC);
        break;
    case KEY_TYPE_DUKPT_MAC:
        iRet = s_EppCrc16SendPacket(wMacLen+12, CMD_GET_DUKPT_MAC);
        break;
    }
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as02a"); GetKey();
        return EPP_SEND_CMD_ERROR;
    }

    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 30000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as02b"); GetKey();
        return iRet;
    }
    if (KEY_TYPE_DUKPT_MAC == byKeyType)
    {
        if (35 != wRecvLen)
        {//lcdPrintf("as02f"); GetKey();
            return EPP_RECV_LEN_ERROR;
        }
        s_EppComputeMacCBC(&g_EppRecvBuff[5], 24, &abyTek[24], 24, &g_EppSendBuff[200]);
        if (0 != memcmp(&g_EppSendBuff[200],&g_EppRecvBuff[29],4))
        {//lcdPrintf("as02g"); GetKey();
            return EPP_MAC_CHECK_ERROR;
        }
        s_EppMultiDes(&g_EppRecvBuff[5], 3, &g_EppSendBuff[200], abyTek, 24, TDEA_DECRYPT);
        if (0 != g_EppSendBuff[203])
        {//lcdPrintf("as02h"); GetKey();
            return (RET_ERROR_BASE+g_EppSendBuff[203]);
        }
        memcpy(pbyMacOut, &g_EppSendBuff[204], 18);
        return EPP_SUCCESS;
    }
    else
    {
        if (27 != wRecvLen)
        {//lcdPrintf("as02c=%d,%d,", wRecvLen, g_EppRecvBuff[5]); GetKey();
            return EPP_RECV_LEN_ERROR;
        }
        s_EppComputeMacCBC(&g_EppRecvBuff[5], 16, &abyTek[24], 24, &g_EppSendBuff[200]);
        if (0 != memcmp(&g_EppSendBuff[200],&g_EppRecvBuff[21],4))
        {//lcdPrintf("as02d"); GetKey();
            return EPP_MAC_CHECK_ERROR;
        }
        s_EppMultiDes(&g_EppRecvBuff[5], 2, &g_EppSendBuff[200], abyTek, 24, TDEA_DECRYPT);
        if (0 != g_EppSendBuff[203])
        {//lcdPrintf("as02e=%02x",g_EppSendBuff[203]); GetKey();
            return (RET_ERROR_BASE+g_EppSendBuff[203]);
        }
        memcpy(pbyMacOut, &g_EppSendBuff[204], 8);
        return EPP_SUCCESS;
    }
}
*/
/*#ifdef   TEST_VERSION
int EppGetMacExt(BYTE byKeyType, BYTE byKeyIndex, const BYTE *pbyMacDataIn,
                        WORD wMacLen, BYTE byMode, BYTE *pbyMacOut, DWORD *pdwOut)
{
    int iRet;
    BYTE abyRand[10], abyTek[64];
    WORD wRecvLen;

    s_EppPortClear();

    sysTimerSet(1, 20000);
    if ((KEY_TYPE_MAC!=byKeyType) && (KEY_TYPE_FIXED_MAC!=byKeyType) && (KEY_TYPE_DUKPT_MAC!=byKeyType))
    {
        return EPP_INPUT_CMD_ERROR;
    }
    if ((0==byKeyIndex) || (byKeyIndex>100))
    {
        return EPP_INPUT_KEY_INDEX_ERROR;
    }
    if ((0!=(wMacLen%8)) || (0==wMacLen) || (wMacLen>2024))
    {
        return EPP_INPUT_MAC_LEN_ERROR;
    }
    if (byMode > 0x03)
    {
        return EPP_INPUT_MODE_ERROR;
    }
    if ((NULL==pbyMacDataIn) || (NULL==pbyMacOut))
    {
        return EPP_INPUT_PARAM_ERROR;
    }

    s_EppCheckCfg();


    memset(g_EppSendBuff, 0, 1024);
    memcpy(&g_EppSendBuff[5], g_sEppConfigure.abyAppName, 16);
    PedGetRandom(&g_EppSendBuff[37]);
    memcpy(abyRand, &g_EppSendBuff[37], 8);
    iRet = s_EppCrc16SendPacket(40, CMD_UKEY_AUTH_STEP1);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as021"); GetKeyBlockMs(12000);
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as022=%x,", iRet); GetKeyBlockMs(12000);
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {//lcdPrintf("as023=%x,",g_EppRecvBuff[5]); GetKeyBlockMs(12000);
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (75 != wRecvLen)
    {//lcdPrintf("as024"); GetKeyBlockMs(12000);
        return EPP_RECV_LEN_ERROR;
    }
    TDEA(&g_EppRecvBuff[9], &g_EppSendBuff[20], g_sEppConfigure.abyAKUAK, 16, TDEA_DECRYPT);
    if (0 != memcmp(abyRand,&g_EppSendBuff[20],8))
    {//lcdPrintf("as025"); GetKeyBlockMs(12000);
        return EPP_AUTHEN_FAILED;
    }


    s_EppMultiDes(&g_EppRecvBuff[25], 6, abyTek, g_sEppConfigure.abyMUTEK, 24, TDEA_DECRYPT);


    TDEA(&g_EppRecvBuff[17], &g_EppSendBuff[9], g_sEppConfigure.abyAKUAK, 16, TDEA_ENCRYPT);
    g_EppSendBuff[5] = 0;
    g_EppSendBuff[6] = 0;
    g_EppSendBuff[7] = RET_MODULE_PED;
    g_EppSendBuff[8] = 0;
    iRet = s_EppCrc16SendPacket(12, CMD_UKEY_AUTH_STEP2);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as026"); GetKeyBlockMs(12000);
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as027=%d,", iRet); GetKeyBlockMs(12000);
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {//lcdPrintf("as028"); GetKeyBlockMs(12000);
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {//lcdPrintf("as029"); GetKeyBlockMs(12000);
        return EPP_RECV_LEN_ERROR;
    }

    pdwOut[0] = 20000 - sysTimerCheck(1);
    sysTimerSet(1, 20000);

    memset(g_EppRecvBuff, 0, 1024);

    g_EppRecvBuff[0] = byKeyIndex;
    g_EppRecvBuff[1] = byMode;  //
    memcpy(&g_EppRecvBuff[2], pbyMacDataIn, wMacLen);
//    memset(&g_EppRecvBuff[wMacLen+2], 0x33, 8);
    PedGetRandom(&g_EppRecvBuff[wMacLen+2]);
    s_EppMultiDes(g_EppRecvBuff, (wMacLen+8)/8, &g_EppSendBuff[5], abyTek, 24, TDEA_ENCRYPT);
    s_EppComputeMacCBC(&g_EppSendBuff[5], wMacLen+8, &abyTek[24], 24, &g_EppSendBuff[wMacLen+13]);
    switch (byKeyType)
    {
    case KEY_TYPE_MAC:
        iRet = s_EppCrc16SendPacket(wMacLen+12, CMD_GET_MAC);
        break;
    case KEY_TYPE_FIXED_MAC:
        iRet = s_EppCrc16SendPacket(wMacLen+12, CMD_GET_FIXED_MAC);
        break;
    case KEY_TYPE_DUKPT_MAC:
        iRet = s_EppCrc16SendPacket(wMacLen+12, CMD_GET_DUKPT_MAC);
        break;
    }
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as02a"); GetKeyBlockMs(12000);
        return EPP_SEND_CMD_ERROR;
    }

    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 30000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as02b"); GetKeyBlockMs(12000);
        return iRet;
    }
    if (KEY_TYPE_DUKPT_MAC == byKeyType)
    {
        if (35 != wRecvLen)
        {//lcdPrintf("as02f"); GetKeyBlockMs(12000);
            return EPP_RECV_LEN_ERROR;
        }
        s_EppComputeMacCBC(&g_EppRecvBuff[5], 24, &abyTek[24], 24, &g_EppSendBuff[200]);
        if (0 != memcmp(&g_EppSendBuff[200],&g_EppRecvBuff[29],4))
        {//lcdPrintf("as02g"); GetKeyBlockMs(12000);
            return EPP_MAC_CHECK_ERROR;
        }
        s_EppMultiDes(&g_EppRecvBuff[5], 3, &g_EppSendBuff[200], abyTek, 24, TDEA_DECRYPT);
        if (0 != g_EppSendBuff[203])
        {//lcdPrintf("as02h=%02x,",g_EppSendBuff[200]); GetKeyBlockMs(12000);
            return (RET_ERROR_BASE+g_EppSendBuff[203]);
        }
        memcpy(pbyMacOut, &g_EppSendBuff[204], 18);
        pdwOut[1] = 20000 - sysTimerCheck(1);
        return EPP_SUCCESS;
    }
    else
    {
        if (27 != wRecvLen)
        {//lcdPrintf("as02c=%d,%d,", wRecvLen, g_EppRecvBuff[5]); GetKeyBlockMs(12000);
            return EPP_RECV_LEN_ERROR;
        }
        s_EppComputeMacCBC(&g_EppRecvBuff[5], 16, &abyTek[24], 24, &g_EppSendBuff[200]);
        if (0 != memcmp(&g_EppSendBuff[200],&g_EppRecvBuff[21],4))
        {//lcdPrintf("as02d"); GetKeyBlockMs(12000);
            return EPP_MAC_CHECK_ERROR;
        }
        s_EppMultiDes(&g_EppRecvBuff[5], 2, &g_EppSendBuff[200], abyTek, 24, TDEA_DECRYPT);
        if (0 != g_EppSendBuff[203])
        {//lcdPrintf("as02e=%02x",g_EppSendBuff[203]); GetKeyBlockMs(12000);
            return (RET_ERROR_BASE+g_EppSendBuff[203]);
        }
        memcpy(pbyMacOut, &g_EppSendBuff[204], 8);
        pdwOut[1] = 20000 - sysTimerCheck(1);
        return EPP_SUCCESS;
    }
}
#endif
*/
/****************************************************************************
  ������     :  int EppGetPin(BYTE byKeyType, BYTE byKeyIndex, BYTE byDisplayMode,
            BYTE byMode, const BYTE *pbyCardInfo, const BYTE *pbyLenInfo, BYTE *pbyPinBlockOut)
  ����       :  MAC����API
  �������   :  1��BYTE byKeyType ����Կ���͡�KEY_TYPE_PIN/KEY_TYPE_FIXED_PIN/KEY_TYPE_DUKPT
                2��BYTE byKeyIndex ����Կ�����������PIN����Fixed PIN��ȡֵ[1,100]��
                                     �����DUKPT PIN���ȡֵ[1,32]
                3��BYTE byDisplayMode ��PIN��ʾģʽ��0��ʾ�����ң�1��ʾ���ҵ���2��ʾ���С�
                4��BYTE byMode �������㷨ѡ��
                                        0x00��ʾѡ��Format 0ģʽ���㷨��
                                        0x01��ʾѡ��Format EMVģʽ���㷨��
                                        0x0a��ʾѡ��Format EPSģʽ���㷨��
                5��const BYTE *pbyCardInfo ��16������Ϣ�����峤�ȱ��벻С��16�ֽ�
                6��const BYTE *pbyLenInfo �����������PIN��Կ����ö��ֵ�ַ��������ȿ�ȡֵ0,4~12����
                            �����ַ�'0'��'4'��������'9'��'a'��'b'��'c'��ʾ��������������
                            "0456a\0\0\0\0\0\0\0\0"�����ʾ֧�ֳ���Ϊ0��4��5��6��10��PIN���롣
                            ���峤�Ȳ�С��13�ֽڡ�
  �������   :  1��BYTE *pbyPinBlockOut �����峤����СΪ19�ֽڣ�ǰ8�ֽ���PIN���������ھŸ�
                   �ֽڱ�ʾ�û��Ƿ�����PIN�������0���ʾû����PIN��1��ʾ������PIN��
                   �����DUKPT���������9~18�ֽ��ǵ�ǰKSN
  ����ֵ     :  EPP_SUCCESS/EPP_SEND_CMD_ERROR/EPP_RECV_CMD_ERROR/EPP_RECV_RET_ERROR/
                EPP_RECV_LEN_ERROR/EPP_AUTHEN_FAILED/0x0d:No PIN
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
// INT32  PedGetPin(UINT16 PinKeyID, UINT8 *ExpectPinLen, UINT8 *CardNo, INT32 Mode, UINT8 *PinBlock)
/*int EppGetPin(BYTE byKeyType, BYTE byKeyIndex, BYTE byDisplayMode,
            BYTE byMode, const BYTE *pbyCardInfo, const BYTE *pbyLenInfo, BYTE *pbyPinBlockOut)
{
    int iRet;
    BYTE abyRand[10], abyTek[64];
    WORD wRecvLen, wCmd = 0;

    s_EppPortClear();

    if ((KEY_TYPE_PIN!=byKeyType) && (KEY_TYPE_FIXED_PIN!=byKeyType) && (KEY_TYPE_DUKPT_PIN!=byKeyType))
    {
        return EPP_INPUT_CMD_ERROR;
    }
    if ((0==byKeyIndex) || (byKeyIndex>100))
    {
        return EPP_INPUT_KEY_INDEX_ERROR;
    }

    if ((0x00!=byMode) && (0x0a!=byMode) && (0x01!=byMode))
    {//lcdPrintf("cs00o   "); GetKey();
        return EPP_INPUT_MODE_ERROR;
    }
    if ((NULL==pbyCardInfo) || (NULL==pbyLenInfo) || (NULL==pbyPinBlockOut))
    {//lcdPrintf("cs00n   "); GetKey();
        return EPP_INPUT_PARAM_ERROR;
    }
    if ((pbyLenInfo[0]<'0') || ((pbyLenInfo[0]>'9')&&(pbyLenInfo[0]<'a')) || (pbyLenInfo[0]>'c'))
    {//lcdPrintf("cs00n   "); GetKey();
        return EPP_INPUT_PARAM_ERROR;
    }

    s_EppCheckCfg();


    memset(g_EppSendBuff, 0, 1024);
    memcpy(&g_EppSendBuff[5], g_sEppConfigure.abyAppName, 16);
    PedGetRandom(&g_EppSendBuff[37]);
    memcpy(abyRand, &g_EppSendBuff[37], 8);
    iRet = s_EppCrc16SendPacket(40, CMD_UKEY_AUTH_STEP1);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("cs00l   "); GetKey();
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("cs00k   "); GetKey();
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {//lcdPrintf("cs00j   "); GetKey();
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (75 != wRecvLen)
    {//lcdPrintf("cs00i   "); GetKey();
        return EPP_RECV_LEN_ERROR;
    }
    TDEA(&g_EppRecvBuff[9], &g_EppSendBuff[20], g_sEppConfigure.abyAKUAK, 16, TDEA_DECRYPT);
    if (0 != memcmp(abyRand,&g_EppSendBuff[20],8))
    {//lcdPrintf("cs00f   "); GetKey();
        return EPP_AUTHEN_FAILED;
    }

    s_EppMultiDes(&g_EppRecvBuff[25], 6, abyTek, g_sEppConfigure.abyMUTEK, 24, TDEA_DECRYPT);

    TDEA(&g_EppRecvBuff[17], &g_EppSendBuff[9], g_sEppConfigure.abyAKUAK, 16, TDEA_ENCRYPT);
    g_EppSendBuff[5] = 0;
    g_EppSendBuff[6] = 0;
    g_EppSendBuff[7] = RET_MODULE_PED;
    g_EppSendBuff[8] = 0;
    iRet = s_EppCrc16SendPacket(12, CMD_UKEY_AUTH_STEP2);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("cs00e   "); GetKey();
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("cs00c   "); GetKey();
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {//lcdPrintf("cs00d=%d   ", g_EppRecvBuff[5]); GetKey();
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {//lcdPrintf("cs00b   "); GetKey();
        return EPP_RECV_LEN_ERROR;
    }

    memset(g_EppRecvBuff, 0, 1024);
    g_EppRecvBuff[0] = byKeyIndex;
    g_EppRecvBuff[1] = byMode;  //
    memcpy(&g_EppRecvBuff[2], pbyCardInfo, 16);
    memcpy(&g_EppRecvBuff[18], pbyLenInfo, 13);
    g_EppRecvBuff[31] = byDisplayMode;
    PedGetRandom(&g_EppRecvBuff[32]);
    s_EppMultiDes(g_EppRecvBuff, 5, &g_EppSendBuff[5], abyTek, 24, TDEA_ENCRYPT);
    s_EppComputeMacCBC(&g_EppSendBuff[5], 40, &abyTek[24], 24, &g_EppSendBuff[45]);

    switch (byKeyType)
    {
    case KEY_TYPE_PIN:
        wCmd = CMD_GET_PIN;
        break;
    case KEY_TYPE_FIXED_PIN:
        wCmd = CMD_GET_FIXED_PIN;
        break;
    case KEY_TYPE_DUKPT_PIN:
        wCmd = CMD_GET_DUKPT_PIN;
        break;
    }
    iRet = s_EppCrc16SendPacket(44, wCmd);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("cs00a   "); GetKey();
        return EPP_SEND_CMD_ERROR;
    }

    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 300000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("cs008   "); GetKey();
        return iRet;
    }

    if (KEY_TYPE_DUKPT_PIN == byKeyType)
    {
        if (35 != wRecvLen)
        {//lcdPrintf("cs008   "); GetKey();
            return EPP_RECV_LEN_ERROR;
        }
        s_EppComputeMacCBC(&g_EppRecvBuff[5], 24, &abyTek[24], 24, &g_EppSendBuff[200]);
        if (0 != memcmp(&g_EppSendBuff[200],&g_EppRecvBuff[29],4))
        {//lcdPrintf("cs007   "); GetKey();
            return EPP_MAC_CHECK_ERROR;
        }
        s_EppMultiDes(&g_EppRecvBuff[5], 3, &g_EppSendBuff[200], abyTek, 24, TDEA_DECRYPT);
        if (0 != g_EppSendBuff[203])
        {//lcdPrintf("cs006=%d,", g_EppSendBuff[200]); GetKey();
            return (RET_ERROR_BASE+g_EppSendBuff[203]);
        }
        if (0 == g_EppSendBuff[212])
        {//lcdPrintf("cs005   "); GetKey();
            return EPP_NO_PIN;
        }
        memcpy(pbyPinBlockOut, &g_EppSendBuff[204], 8);
        memcpy(&pbyPinBlockOut[8], &g_EppSendBuff[213], 10);
    }
    else
    {
        if (27 != wRecvLen)
        {//lcdPrintf("cs004   "); GetKey();
            return EPP_RECV_LEN_ERROR;
        }
        s_EppComputeMacCBC(&g_EppRecvBuff[5], 16, &abyTek[24], 24, &g_EppSendBuff[200]);
        if (0 != memcmp(&g_EppSendBuff[200],&g_EppRecvBuff[21],4))
        {//lcdPrintf("cs003   "); GetKey();
            return EPP_MAC_CHECK_ERROR;
        }
        s_EppMultiDes(&g_EppRecvBuff[5], 2, &g_EppSendBuff[200], abyTek, 24, TDEA_DECRYPT);
        if (0 != g_EppSendBuff[203])
        {//lcdPrintf("cs002=%d,   ", g_EppSendBuff[200]); GetKey();
            return (RET_ERROR_BASE+g_EppSendBuff[203]);
        }
        if (0 == g_EppSendBuff[212])
        {//lcdPrintf("cs001   "); GetKey();
            return EPP_NO_PIN;
        }
        memcpy(pbyPinBlockOut, &g_EppSendBuff[204], 8);
    }
    return EPP_SUCCESS;
}
*/
/****************************************************************************
  ������     :  int EppGetTdea(WORD wMode, BYTE byKeyType, BYTE  byKeyIndex, WORD wDataLen,
                   const BYTE *pbyDataIn, BYTE *pbyDataOut)
  ����       :  TDEA����API
  �������   :  1��WORD wMode  ���㷨ģʽ
                                TDEA_ENCRYPT  ��������
                                TDEA_DECRYPT  ��������
                                TDEA_MODE_ECB---ʹ��ECBģʽ
                                TDEA_MODE_CBC---ʹ��CBCģʽ
                                ��ο�8110��SDK�궨��
                2��BYTE byKeyType ����Կ���͡�
                                0x01������Կ��
                                0x02��MAC��Կ��
                                0x03��PIN��Կ��
                                0x04��DUKPT MAC��Կ���ݲ�֧��
                                0x05��DUKPT PIN��Կ���ݲ�֧��
                                0x10��Fixed MAC��Կ��
                                0x11��Fixed PIN��Կ��
                3��BYTE byKeyIndex ����Կ��������ȡֵ[1,100]
                4��WORD wDataLen �����ݳ��ȣ�������8������������СֵΪ8�����ֵΪ96
                5��const BYTE *pbyDataIn ���������������
  �������   :  1��BYTE *pbyDataOut ��������
  ����ֵ     :  EPP_SUCCESS/EPP_SEND_CMD_ERROR/EPP_RECV_CMD_ERROR/EPP_RECV_RET_ERROR/
                EPP_RECV_LEN_ERROR/EPP_AUTHEN_FAILED/
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
/*int EppGetTdea(WORD wMode, BYTE byKeyType, BYTE  byKeyIndex, WORD wDataLen,
                   const BYTE *pbyDataIn, BYTE *pbyDataOut)
{
    int iRet;
    BYTE abyRand[10], abyTek[64];
    WORD wRecvLen;

    s_EppPortClear();
    if (   (KEY_TYPE_MAC!=byKeyType)       && (KEY_TYPE_PIN!=byKeyType)
        && (KEY_TYPE_FIXED_MAC!=byKeyType) && (KEY_TYPE_FIXED_PIN!=byKeyType)
//        && (KEY_TYPE_DUKPT_MAC!=byKeyType) && (KEY_TYPE_DUKPT_PIN!=byKeyType)
        && (KEY_TYPE_MASTER!=byKeyType))
    {
        return EPP_INPUT_CMD_ERROR;
    }
    if ((0==byKeyIndex) || (byKeyIndex>100))
    {
        return EPP_INPUT_KEY_INDEX_ERROR;
    }

    if ((0!=(wDataLen%8)) || (0==wDataLen) || (wDataLen>96))
    {
        return EPP_INPUT_DATA_LEN_ERROR;
    }

    s_EppCheckCfg();

    memset(g_EppSendBuff, 0, 1024);
    memcpy(&g_EppSendBuff[5], g_sEppConfigure.abyAppName, 16);
    PedGetRandom(&g_EppSendBuff[37]);
    memcpy(abyRand, &g_EppSendBuff[37], 8);
    iRet = s_EppCrc16SendPacket(40, CMD_UKEY_AUTH_STEP1);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as121"); GetKey();
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as122"); GetKey();
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {//lcdPrintf("as123"); GetKey();
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (75 != wRecvLen)
    {//lcdPrintf("as124"); GetKey();
        return EPP_RECV_LEN_ERROR;
    }
    TDEA(&g_EppRecvBuff[9], &g_EppSendBuff[20], g_sEppConfigure.abyAKUAK, 16, TDEA_DECRYPT);
    if (0 != memcmp(abyRand,&g_EppSendBuff[20],8))
    {//lcdPrintf("as125"); GetKey();
        return EPP_AUTHEN_FAILED;
    }

	s_EppMultiDes(&g_EppRecvBuff[25], 6, abyTek, g_sEppConfigure.abyMUTEK, 24, TDEA_DECRYPT);

    TDEA(&g_EppRecvBuff[17], &g_EppSendBuff[9], g_sEppConfigure.abyAKUAK, 16, TDEA_ENCRYPT);
    g_EppSendBuff[5] = 0;
    g_EppSendBuff[6] = 0;
    g_EppSendBuff[7] = RET_MODULE_PED;
    g_EppSendBuff[8] = 0;
    iRet = s_EppCrc16SendPacket(12, CMD_UKEY_AUTH_STEP2);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as126"); GetKey();
        return EPP_SEND_CMD_ERROR;
    }
    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as127=%d,", iRet); GetKey();
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {//lcdPrintf("as128"); GetKey();
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {//lcdPrintf("as129"); GetKey();
        return EPP_RECV_LEN_ERROR;
    }

    memset(g_EppRecvBuff, 0, 1024);

    g_EppRecvBuff[0] = byKeyType;
    g_EppRecvBuff[1] = wMode>>8;
    g_EppRecvBuff[2] = wMode;
    g_EppRecvBuff[3] = byKeyIndex;
    g_EppRecvBuff[4] = 0;
    memcpy(&g_EppRecvBuff[5], pbyDataIn, wDataLen);
//    memset(&g_EppRecvBuff[5+wDataLen], 0x33, 8);
    PedGetRandom(&g_EppRecvBuff[5+wDataLen]);
    s_EppMultiDes(g_EppRecvBuff, (wDataLen+8)/8, &g_EppSendBuff[5], abyTek, 24, TDEA_ENCRYPT);
    s_EppComputeMacCBC(&g_EppSendBuff[5], wDataLen+8, &abyTek[24], 24, &g_EppSendBuff[wDataLen+13]);

    iRet = s_EppCrc16SendPacket(wDataLen+12, CMD_GET_TDEA);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as12a"); GetKey();
        return EPP_SEND_CMD_ERROR;
    }

    memset(g_EppRecvBuff, 0x0, 100);
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 30000);
    if (EPP_SUCCESS != iRet)
    {//lcdPrintf("as12b"); GetKey();
        return iRet;
    }

    s_EppComputeMacCBC(&g_EppRecvBuff[5], wRecvLen-11, &abyTek[24], 24, &g_EppSendBuff[200]);
    if (0 != memcmp(&g_EppSendBuff[200],&g_EppRecvBuff[wRecvLen-6],4))
    {//lcdPrintf("as12d"); GetKey();
        return EPP_MAC_CHECK_ERROR;
    }
    s_EppMultiDes(&g_EppRecvBuff[5], (wRecvLen-11)/8, &g_EppSendBuff[200], abyTek, 24, TDEA_DECRYPT);
    if (0 != g_EppSendBuff[203])
    {//lcdPrintf("as12e=%02x, %d,",g_EppSendBuff[203], wRecvLen); GetKey();
        return (RET_ERROR_BASE+g_EppSendBuff[203]);
    }
    memcpy(pbyDataOut, &g_EppSendBuff[204], wDataLen);
    return EPP_SUCCESS;
}
*/
/****************************************************************************
  ������     :  int EppSetPinInputTimeout(WORD wTimeout100Ms)
  ����       :  ����PIN���볬ʱʱ�䳤��
  �������   :  1��WORD wTimeout100Ms : ��ʱʱ�䣬��λ100���룬���ֵ1200��120�룩��
                   ���ȡֵ0�����ʾʹ��Ĭ��ֵ120�롣
  �������   :  ��
  ����ֵ     :
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
int EppSetPinInputTimeout(WORD wTimeout100Ms)
{
    int iRet;
    WORD wRecvLen;

    s_EppPortClear();
    if (wTimeout100Ms > 1200)
    {
        return EPP_INPUT_PARAM_ERROR;
    }

    g_EppSendBuff[5] = (BYTE)(wTimeout100Ms>>8);
    g_EppSendBuff[6] = (BYTE)(wTimeout100Ms);

    iRet = s_EppCrc16SendPacket(2, CMD_SET_PIN_TIMEOUT);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 1000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }
    return EPP_SUCCESS;
}

/****************************************************************************
  ������     :  int EppSetTdesIv(const BYTE *pbyIvData)
  ����       :  ����Tdes��ʼ������������ֻ��CBC�㷨��Ч
  �������   :  1��const BYTE *pbyIvData : ��ʼ������8�ֽڡ�
  �������   :  ��
  ����ֵ     :
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
int EppSetTdesIv(const BYTE *pbyIvData)
{
    int iRet;
    WORD wRecvLen;

    s_EppPortClear();
    memcpy(&g_EppSendBuff[5], pbyIvData, 8);
    iRet = s_EppCrc16SendPacket(8, CMD_SET_TDES_IV);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 1000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }
    return EPP_SUCCESS;
}

/****************************************************************************
  ������     :  int EppGetRand(BYTE *pbyRandOut)
  ����       :  ��ȡ�����
  �������   :  ��
  �������   :  1��BYTE *pbyRandOut ���������8�ֽ�
  ����ֵ     :
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
int EppGetRand(BYTE *pbyRandOut)
{
    int iRet;
    WORD wRecvLen;
    s_EppPortClear();

    if (NULL == pbyRandOut)
    {
        return EPP_INPUT_PARAM_ERROR;
    }

    iRet = s_EppCrc16SendPacket(0, CMD_GET_RANDOM_NUMBER);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (19 != wRecvLen)
    {
        return EPP_RECV_RET_ERROR;
    }
    memcpy(pbyRandOut, &g_EppRecvBuff[9], 8);
    return EPP_SUCCESS;
}

/****************************************************************************
  ������     :  int EppClearAKey(BYTE byKeyType, BYTE byKeyIndex)
  ����       :  ���ĳ����Կ
  �������   :  1��BYTE byKeyType ����Կ����
                                0x01������Կ��
                                0x02��MAC��Կ��
                                0x03��PIN��Կ��
                                0x10��Fixed MAC��Կ��
                                0x11��Fixed PIN��Կ��
                2��BYTE byKeyIndex ����Կ����
  �������   :  ��
  ����ֵ     :
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
int EppClearAKey(BYTE byKeyType, BYTE byKeyIndex)
{
    int iRet;
    WORD wRecvLen;

    if (   (KEY_TYPE_MAC!=byKeyType)       && (KEY_TYPE_PIN!=byKeyType)
        && (KEY_TYPE_FIXED_MAC!=byKeyType) && (KEY_TYPE_FIXED_PIN!=byKeyType)
//        && (KEY_TYPE_DUKPT_MAC!=byKeyType) && (KEY_TYPE_DUKPT_PIN!=byKeyType)
        && (KEY_TYPE_MASTER!=byKeyType))
    {
        return EPP_INPUT_CMD_ERROR;
    }
    if ((byKeyIndex>KEY_INDEX_NUMBER)||(0==byKeyIndex))
    {
        return EPP_KEY_INDEX_ERROR;
    }

    s_EppPortClear();
    memset(g_EppSendBuff, 0, 1024);
    g_sEppConfigure.abyAppName[31] = 0;
    strcpy((char*)(&g_EppSendBuff[5]), (char*)g_sEppConfigure.abyAppName);
    switch (byKeyType)
    {
    case KEY_TYPE_MAC:
        g_EppSendBuff[37] = 1;
        break;
    case KEY_TYPE_PIN:
        g_EppSendBuff[37] = 2;
        break;
    case KEY_TYPE_FIXED_MAC:
        g_EppSendBuff[37] = 3;
        break;
    case KEY_TYPE_FIXED_PIN:
        g_EppSendBuff[37] = 4;
        break;
    case KEY_TYPE_MASTER:
        g_EppSendBuff[37] = 0;
        break;
    }
    g_EppSendBuff[38] = byKeyIndex;

    iRet = s_EppCrc16SendPacket(34, CMD_CLEAR_ONE_KEY);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 1000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }
    return EPP_SUCCESS;
}

/****************************************************************************
  ������     :  int EppClearOneAppKey(void)
  ����       :  �����ǰӦ�õ�������Կ
  �������   :  ��
  �������   :  ��
  ����ֵ     :
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
int EppClearOneAppKey(void)
{
    int iRet;
    WORD wRecvLen;

    s_EppPortClear();
    memset(g_EppSendBuff, 0, 1024);
    g_sEppConfigure.abyAppName[31] = 0;
    strcpy((char*)(&g_EppSendBuff[5]), (char*)g_sEppConfigure.abyAppName);
//    memcpy(&g_EppSendBuff[37], g_abySecuryPassword, 8);

    iRet = s_EppCrc16SendPacket(32, CMD_CLEAR_ALL_ONE_KEY);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 10000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }
    return EPP_SUCCESS;
}

/****************************************************************************
  ������     :  int EppFormatPed(void)
  ����       :  �����������ڵ�����PED�������ݣ�SIEK����
  �������   :  ��
  �������   :  ��
  ����ֵ     :
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
int EppFormatPed(void)
{
    int iRet;
    WORD wRecvLen;

    s_EppPortClear();

    iRet = s_EppCrc16SendPacket(0, CMD_FORMAT_PED);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 20000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }
    return EPP_SUCCESS;
}

/****************************************************************************
  ������     :  int EppSetIdleLogo(BYTE *pbyBmpIdleLogoIn)
  ����       :  ����IDLE LOGO
  �������   :  1��BYTE *pbyBmpIdleLogoIn ���ֱ���Ϊ122*32�ĵ�ɫBMP�ļ�����������
  �������   :  ��
  ����ֵ     :
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
int EppSetIdleLogo(const BYTE *pbyBmpIdleLogoIn)
{
    int iRet;
    WORD wRecvLen;

    if (0 != memcmp(pbyBmpIdleLogoIn,g_abyIdleLogoFileHead,62))
    {
        return EPP_BMP_ERROR;
    }
    s_EppPortClear();

    memcpy(&g_EppSendBuff[5], pbyBmpIdleLogoIn, 574);

    iRet = s_EppCrc16SendPacket(574, CMD_LOAD_IDLE_LOGO);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 1000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }
    return EPP_SUCCESS;
}

/****************************************************************************
  ������     :  int EppRestoreDefaultIdleLogo(void)
  ����       :  �������IDLE LOGO���ָ�Ĭ��IDLE LOGO
  �������   :  ��
  �������   :  ��
  ����ֵ     :
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
int EppRestoreDefaultIdleLogo(void)
{
    int iRet;
    WORD wRecvLen;

    s_EppPortClear();
    g_EppSendBuff[5] = 0x3e;

    iRet = s_EppCrc16SendPacket(1, CMD_RESTORE_IDLE_LOGO);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 1000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }
    return EPP_SUCCESS;
}


/****************************************************************************
  ������     :  int EppDisplayLogo(BYTE *pbyBmpIdleLogoIn)
  ����       :  ��Һ��������ʾͼ����Ϣ
  �������   :  1��BYTE *pbyBmpIdleLogoIn ��
  �������   :  ��
  ����ֵ     :
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
int EppDisplayLogo(const BYTE *pbyBmpIdleLogoIn)
{
    int iRet;
    WORD wRecvLen, wSendLength;
    BYTE abyBuff[64];

    memcpy(abyBuff, pbyBmpIdleLogoIn, 62);
    wSendLength = abyBuff[3];
    wSendLength <<= 8;
    wSendLength += abyBuff[2];
    abyBuff[2] = 0;
    abyBuff[3] = 0;
    if (wSendLength > 574)
    {
        return EPP_BMP_ERROR;
    }
    if ((0==abyBuff[18])||(abyBuff[18]>122))
    {
        return EPP_BMP_ERROR;
    }
    abyBuff[18] = 0;
    if ((8!=abyBuff[22])&&(16!=abyBuff[22])&&(24!=abyBuff[22])&&(32!=abyBuff[22]))
    {
        return EPP_BMP_ERROR;
    }
    abyBuff[22] = 0;

    wRecvLen = pbyBmpIdleLogoIn[35];
    wRecvLen <<= 8;
    wRecvLen += pbyBmpIdleLogoIn[34];
    if (wRecvLen > 512)
    {
        return EPP_BMP_ERROR;
    }
    abyBuff[34] = 0;
    abyBuff[35] = 0;
    if (0 != memcmp(abyBuff,g_abyNormalLogoFileHead,62))
    {
        return EPP_BMP_ERROR;
    }
    s_EppPortClear();
    g_EppSendBuff[5] = 0;
    g_EppSendBuff[6] = 0;
    g_EppSendBuff[7] = 0;
    g_EppSendBuff[8] = 0;
    memcpy(&g_EppSendBuff[9], pbyBmpIdleLogoIn, wSendLength);

    iRet = s_EppCrc16SendPacket(wSendLength+4, CMD_DISPLAY_LOGO);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 1000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }
    return EPP_SUCCESS;
}

/****************************************************************************
  ������     :  int EppDisplayString(int X, int Y, int iMode, const void *str, int iStrLen)
  ����       :  ����Ļ����ʾ�ַ�����Ŀǰn20ֻ����ʾASCII�ַ�
  �������   :  1��int X ����ʾλ��x
                2��int Y ����ʾλ��y
                3��int iMode ����ʾ�ַ��Ĵ�С8:6x8;16:8x16
                4��const void *str ����ʾ���ַ���
                5��int iStrLen ���ַ����ĳ���
  �������   :  ��
  ����ֵ     :
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-15  V1.0         ����
****************************************************************************/
int EppDisplayString(int X, int Y, int iMode, const void *str, int iStrLen)
{
    int iRet;
    WORD wRecvLen;

    s_EppPortClear();

    if (NULL == str)
    {
        return EPP_INPUT_PARAM_ERROR;
    }
    g_EppSendBuff[5] = (BYTE)(X>>8);
    g_EppSendBuff[6] = (BYTE)X;
    g_EppSendBuff[7] = (BYTE)(Y>>8);
    g_EppSendBuff[8] = (BYTE)Y;
    g_EppSendBuff[9] = (BYTE)(iMode>>8);
    g_EppSendBuff[10] = (BYTE)iMode;
    memcpy(&g_EppSendBuff[11], str, iStrLen);

    iRet = s_EppCrc16SendPacket(6+iStrLen, CMD_DISPLAY_STRING);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {
        return EPP_RECV_RET_ERROR;
    }
    return EPP_SUCCESS;
}

/****************************************************************************
  ������     :  int EppClearScreen(void)
  ����       :  �����Ļ��ʾ��
  �������   :  ��
  �������   :  ��
  ����ֵ     :
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-15  V1.0         ����
****************************************************************************/
int EppClearScreen(void)
{
    int iRet;
    WORD wRecvLen;

    s_EppPortClear();


    iRet = s_EppCrc16SendPacket(0, CMD_CLEAR_SCREEN);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 3000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {
        return EPP_RECV_RET_ERROR;
    }
    return EPP_SUCCESS;
}

int EppEnterFactoryTest(BYTE bySpeed)
{
    int iRet;

    s_EppPortClear();
    g_EppSendBuff[5] = bySpeed;

    memcpy(&g_EppSendBuff[6], "\xab\x87\x98\x56\xcf\xde\xa3\x19", 8);

    iRet = s_EppCrc16SendPacket(9, CMD_ENTER_FACTORY_TEST);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    return EPP_SUCCESS;
}


/****************************************************************************
  ������     :  int EppGetSystemInfo(BYTE byType, void *pvInfoOut)
  ����       :  ��ȡEppϵͳ��Ϣ
  �������   :  1��BYTE byType ��
                          ��ѯ���
                          0x00��Ʒ���ƣ�
                          0x01Ӳ���汾��
                          0x02Ӳ�����ã�
                          0x03 �������кţ�
                          0x04 CPU SN��
                          0x10 boot�汾��
                          0x11 Kernel�汾��
                          0x20 ��ѯЭ��汾��
  �������   :  1��void *pvInfoOut ��16�ֽڵ������Ϣ�����岻��С��17�ֽ�
  ����ֵ     :
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
int EppGetSystemInfo(BYTE byType, void *pvInfoOut)
{
    int iRet;
    WORD wRecvLen;

    s_EppPortClear();
    g_EppSendBuff[5] = byType;

    iRet = s_EppCrc16SendPacket(1, CMD_GET_SYSTEM_INFO);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 1000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (27 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }
    memcpy(pvInfoOut, &g_EppRecvBuff[9], 16);
    memset(pvInfoOut+16, 0, 1);
    return EPP_SUCCESS;
}

/****************************************************************************
  ������     :  int EppBeep(DWORD dwFrequency, DWORD dwTimeMs)
  ����       :  ��Epp����������
  �������   :  1��DWORD dwFrequency ��
                        Ƶ�ʿ��Ʋ�����
                        (1)���ȡֵ��0��6�����ӦƵ����1680, 1834, 2020, 2127, 2380, 2700, 2900��
                        (2)���ȡֵ���ڵ���7���򰴸�ֵ������Ƶ�ʣ������ֵ��1500����Ƶ����1500��
                        ˵�����ò�������N20�����壬N20��֧�̶ֹ���2500hz��Ƶ�ʡ�
                  2��DWORD dwTimeMs ������ʱ�䳤�ȣ���λ����
  �������   :  ��
  ����ֵ     :
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
int EppBeep(DWORD dwFrequency, DWORD dwTimeMs)
{
    int iRet;
    WORD wRecvLen;

    s_EppPortClear();
    g_EppSendBuff[5]  = (BYTE)(dwFrequency>>24);
    g_EppSendBuff[6]  = (BYTE)(dwFrequency>>16);
    g_EppSendBuff[7]  = (BYTE)(dwFrequency>>8);
    g_EppSendBuff[8]  = (BYTE) dwFrequency;
    g_EppSendBuff[9]  = (BYTE)(dwTimeMs>>24);
    g_EppSendBuff[10] = (BYTE)(dwTimeMs>>16);
    g_EppSendBuff[11] = (BYTE)(dwTimeMs>>8);
    g_EppSendBuff[12] = (BYTE) dwTimeMs;

    iRet = s_EppCrc16SendPacket(8, CMD_BEEP);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 1000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }
    return EPP_SUCCESS;
}

/****************************************************************************
  ������     :  int EppLight(DWORD dwMode, DWORD dwTimeMs)
  ����       :  Epp�������
  �������   :  1��DWORD dwMode �����⣨ָʾ�ƣ�����ģʽ
                            1  ���⣨ָʾ�ƣ���ʱ����ָ����ʱ�䳤�����ţ�ģʽ
                            2  ���⣨ָʾ�ƣ�������һֱ�򿪣�ģʽ
                            3  ���⣨ָʾ�ƣ����أ�һֱ�رգ�ģʽ
                2��DWORD dwTimeMs ��
                              �������ʱ�䳤�ȣ���λΪ���롣
                              �ò���ֻ����ģʽ1��ʱ�����Ч��
  �������   :  ��
  ����ֵ     :
  �޸���ʷ   :
      �޸���     �޸�ʱ��    �޸İ汾��   �޸�ԭ��
  1�� �ƿ���     2010-12-11  V1.0         ����
****************************************************************************/
int EppLight(DWORD dwMode, DWORD dwTimeMs)
{
    int iRet;
    WORD wRecvLen;

    s_EppPortClear();
    g_EppSendBuff[5]  = (BYTE)(dwMode>>24);
    g_EppSendBuff[6]  = (BYTE)(dwMode>>16);
    g_EppSendBuff[7]  = (BYTE)(dwMode>>8);
    g_EppSendBuff[8]  = (BYTE) dwMode;
    g_EppSendBuff[9]  = (BYTE)(dwTimeMs>>24);
    g_EppSendBuff[10] = (BYTE)(dwTimeMs>>16);
    g_EppSendBuff[11] = (BYTE)(dwTimeMs>>8);
    g_EppSendBuff[12] = (BYTE) dwTimeMs;

    iRet = s_EppCrc16SendPacket(8, CMD_LIGHT);
    if (EPP_SUCCESS != iRet)
    {
        return EPP_SEND_CMD_ERROR;
    }
    iRet = s_EppCrc16RecvPacket(g_EppRecvBuff, &wRecvLen, 1000);
    if (EPP_SUCCESS != iRet)
    {
        return iRet;
    }
    if (0 != g_EppRecvBuff[8])
    {
        return (RET_ERROR_BASE+g_EppRecvBuff[8]);
    }
    if (11 != wRecvLen)
    {
        return EPP_RECV_LEN_ERROR;
    }
    return EPP_SUCCESS;
}





