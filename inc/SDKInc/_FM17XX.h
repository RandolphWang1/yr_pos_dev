//////////////////////////////////////////////////////////////////////////////
#ifndef __FM17XX_H_
#define __FM17XX_H_
//////////////////////////////////////////////////////////////////////////////
#define Baud_VALUE_110		0
#define Baud_VALUE_300		1
#define Baud_VALUE_600		2
#define Baud_VALUE_1200		3
#define Baud_VALUE_2400		4
#define Baud_VALUE_4800		5
#define Baud_VALUE_9600		6
#define Baud_VALUE_14400	7
#define Baud_VALUE_19200	8
#define Baud_VALUE_38400	9
#define Baud_VALUE_57600	10
#define Baud_VALUE_115200	11
#define Baud_VALUE_230400	12
#define Baud_VALUE_380400	13
#define Baud_VALUE_460800	14	
#define Baud_VALUE_921600	15
//////////////////////////////////////////////////////////////////////////////
#define ERR_CONNECT_NAME        -2
//==========================================================================
#define ERR_ACTIVE_ATQA         -2
#define ERR_ACTIVE_UID          -3
#define ERR_ACTIVE_SAK          -4
//==========================================================================
#define ERR_RESET_NOTAG         -2
//==========================================================================
#define ERR_VERIFY_LOADKEY      -2
#define ERR_VERIFY_AUTHKEY      -3
//==========================================================================
#define ERR_READ_LENGTH         -2
//==========================================================================
#define ERR_WRITE_DATA          -2
//==========================================================================
#define ERR_HALT_NOCARD         -2
//==========================================================================
#define ERR_INIT_NOCARD         -2
//==========================================================================
#define ERR_ADD_VALUE           -2
//==========================================================================
#define ERR_DEC_VALUE           -2
//==========================================================================
#define ERR_READ_VALUE          -2
//==========================================================================
#define ERR_TRANSFER_ERR        -2
//==========================================================================
#define ERR_RESTORE_ERR         -2
//==========================================================================
#define ERR_TYPEA_NOCARD        -2
//==========================================================================
#define ERR_CPURESET_RATS       -2
//==========================================================================
#define ERR_CPUPPS_PPS          -2
//==========================================================================
#define ERR_CPUBPS_BPS          -2
//==========================================================================
//////////////////////////////////////////////////////////////////////////////
// ��ʼ������
int FM17Init(int * pnHandle, int nCom, int nBaud, void * pAddr);
int FM17dcInit(int nCom, int nBaud);
void SerialClear();
void SerialClose();
void FM17Close(int * pnHandle, void * pAddr);
void FM17dcExit(int icdev);
//////////////////////////////////////////////////////////////////////////////
// ����
// ���FM1702 FW1.0 �������汾�ͺ� 
int FM17Connect(int * pnHandle, char *szName, void * pAddr);
// ��λ
int FM17Reset(int * pnHandle, void * pAddr);
int FM17dcReset(int icdev, unsigned short int _Msec);
// CardActive
int FM17CardActive(int * pnHandle, int nMode, char *szSAK, char *szUID, char *szATQA, void * pAddr);
int FM17dcRequest(int icdev, unsigned char _Mode, unsigned int *TagType);
int FM17dcAnticoll(int icdev, unsigned char _Bcnt, unsigned long *_Snr);
int FM17dcSelect(int icdev, unsigned long _Snr, unsigned char *_Size);
// ��֤
//ASCII12λ
int FM17Verify(int *pnHandle, int nSector, char * szPriKey, void * pAddr);
int FM17dcAuth(int icdev, unsigned int _Mode, unsigned char _SecNr);
// ����
int FM17ReadBlock(int *pnHandle, int nSector, int nBlock, char *szReadData, void * pAddr);
int FM17dcRead(int icdev, unsigned char _Adr, unsigned char *_Data);
// д��
int FM17WriteBlock(int *pnHandle, int nSector, int nBlock, char * szWriteData, void * pAddr);
int FM17dcWrite(int icdev, unsigned char _Adr, unsigned char *_Data);
// ��ֵ
int FM17AddValue(int *pnHandle, int nSector, int nBlock, char *pszAddValue, void *pAddr);
// ��ֵ
int FM17DecValue(int * pnHandle, int nSector, int nBlock, char *pszDecValue, void * pAddr);
// ��ֵ
int FM17ReadBlockValue(int *pnHandle, int nSector, int nBlock, char * szWriteData, void * pAddr);
// Transfer
int FM17Transfer(int *pnHandle, int nSector, int nBlock, void * pAddr);
// Restore
int FM17Restore(int * pnHandle, void * pAddr);
// ��ֹ
int FM17Halt(int * pnHandle, void * pAddr);
int FM17dcHalt(int icdev);
// ��ʼ����
int FM17InitBlock(int *pnHandle, int nSector, int nBlock, char *pszDecValue, void *pAddr);
//////////////////////////////////////////////////////////////////////////////
// cpuTYPEAINIT
int FM17TYPEA(int * pnHandle, void * pAddr);
// cpuCardReset
int FM17CardReset(int *pnHandle, char * szData, void *pAddr);
//////////////////////////////////////////////////////////////////////////////
int OperCpuAPDU(int *pnHandle, APDU_SEND *pSend, APDU_RESP *pResp, BOOL bTransparent, void *pAddr);

int FM17Loadkey(int icdev, unsigned char _Mode, unsigned char _SecNr, unsigned char *_NKey);
#endif //__FM17XX_H_
//////////////////////////////////////////////////////////////////////////////

