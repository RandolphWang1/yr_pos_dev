#ifndef _SMS_H_
#define _SMS_H_

// �û���Ϣ���뷽ʽ
#define GSM_7BIT		0
#define GSM_8BIT		4
#define GSM_UCS2		8

// Ӧ��״̬
#define GSM_WAIT		0		// �ȴ�����ȷ��
#define GSM_OK			1		// OK
#define GSM_ERR			-1		// ERROR

#define CP_ACP          0      // default to ANSI code page


// ����Ϣ�����ṹ������/���빲��
// ���У��ַ�����'\0'��β
typedef struct {
	char SCA[16];			// ����Ϣ�������ĺ���(SMSC��ַ)
	char TPA[16];			// Ŀ������ظ�����(TP-DA��TP-RA)
	char TP_PID;			// �û���ϢЭ���ʶ(TP-PID)
	char TP_DCS;			// �û���Ϣ���뷽ʽ(TP-DCS)
	char TP_SCTS[16];		// ����ʱ����ַ���(TP_SCTS), ����ʱ�õ�
	char TP_UD[160];		// ԭʼ�û���Ϣ(����ǰ�������TP-UD)
	short index;			// ����Ϣ��ţ��ڶ�ȡʱ�õ�
} SM_PARAM;

// ��ȡӦ��Ļ�����
typedef struct {
	int len;
	char data[16384];
} SM_BUFF;

int gsmBytes2String(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmString2Bytes(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmEncode7bit(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmDecode7bit(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmEncodeUcs2(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmDecodeUcs2(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmInvertNumbers(const char* pSrc, char* pDst, int nSrcLength);
int gsmSerializeNumbers(const char* pSrc, char* pDst, int nSrcLength);
int gsmEncodePdu(const SM_PARAM* pSrc, char* pDst);
int gsmDecodePdu(const char* pSrc, SM_PARAM* pDst);

BOOL gsmInit();

int gsmSendMessage(SM_PARAM* pSrc);
int gsmReadMessageList();
int gsmDeleteMessage(int index);

int gsmGetResponse(SM_BUFF* pBuff);

int gsmParseMessageList(SM_PARAM* pMsg, SM_BUFF* pBuff);

char GSM_RecString_Comp(char ans[], int length);

BOOL Init_Gprs();				//��ʼ��GPRS����
BOOL Open_GPGS_Mode();			//��GPRSģʽ
BOOL Close_GPGS_Mode();			//�ر�GPRSģʽ
BOOL Read_GPRS_Data();			//��ȡGPRS�������ĵ�����
BOOL Write_GPRS_Data(char a[],int length);		//����������д����

BOOL AT_Command(char *cmd, char length, char code, int time);
int ReadComm(void* pData, int nLength);
int WriteComm(void* pData, int nLength);
int MultiByteToWideChar(const unsigned short * lpMultiByteStr,int cchMultiByte,unsigned short * lpWideCharStr);
int WideCharToMultiByte(const unsigned short *  lpWideCharStr,int  cchWideChar,LPSTR  lpMultiByteStr);

#endif

