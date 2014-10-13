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
	char TP_SCTS[20];		// ����ʱ����ַ���(TP_SCTS), ����ʱ�õ�
	char TP_UD[255];		// ԭʼ�û���Ϣ(����ǰ�������TP-UD)
	int index;				// ����Ϣ��ţ��ڶ�ȡʱ�õ�
} SM_PARAM;

// ��ȡӦ��Ļ�����
typedef struct 
{
	int len;
	char data[16384];
} SM_BUFF;

int gsmBytes2String(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmString2Bytes(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmEncode7bit(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmDecode7bit(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmEncodeUcs2(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmDecodeUcs2(unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmInvertNumbers(const char* pSrc, char* pDst, int nSrcLength);
int gsmSerializeNumbers(const char* pSrc, char* pDst, int nSrcLength);
int gsmEncodePdu(const SM_PARAM* pSrc, char* pDst);
int gsmDecodePdu(const char* pSrc, SM_PARAM* pDst);
int gsmSendMessage(SM_PARAM* pSrc);
int gsmReadMessageList();
int gsmDeleteMessage(int index);

int gsmGetResponse(SM_BUFF* pBuff);

int gsmParseMessageList(SM_PARAM* pMsg, SM_BUFF* pBuff);

char GSM_RecString_Comp(char ans[], int length);

int Init_SMS(int model,char *CSCA);
int Open_GPGS_Mode();			//��GPRSģʽ
int Close_GPGS_Mode();			//�ر�GPRSģʽ
int Read_GPRS_Data();			//��ȡGPRS�������ĵ�����
int Write_GPRS_Data(char a[],int length);		//����������д����

int AT_Command(char *cmd, char length, char code, int time);
int ReadComm(void* pData, int nLength);
int WriteComm(void* pData, int nLength,int flg);
int MultiByteToWideChar(const char* lpMultiByteStr,int cchMultiByte,unsigned short * lpWideCharStr);
int WideCharToMultiByte(unsigned char*  lpWideCharStr,int  cchWideChar,char*  lpMultiByteStr);
void Hex2Asc(char *dest_asc, unsigned char *src_bcd, char src_len);
unsigned short exchange(unsigned short source);

int demo_SMS_send();
int demo_SMS_recv();

void PutRecvMessage(SM_PARAM* pparam, int nCount);
int SMS_Setting();
int gsmDecode8bit(unsigned char* pSrc, char* pDst, int nSrcLength);
int demo_SMS_read(int index);
int gsmReadMessage(int index);
int gsmParseMessage(SM_PARAM* pMsg, SM_BUFF* pBuff);

#endif
