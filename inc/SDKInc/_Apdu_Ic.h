#include <math.h>

//////////////////////////////////////////////////////////////////////////////

#define MAC_LEN		4
#define PASSWD		8
#define PRIINFO		8
#define FILENAME_LEN	5
#define MAC_DATA_LEN	8

//////////////////////////////////////////////////////////////////////////////
// 
struct Status_map 
{
	char SWA[2+1];			// SWA
	char SWB[2+1];			// SWB
	char Err_Desc[30+1];		// ��������
};

BYTE str_To_Dec(BYTE_PTR pStr);

//////////////////////////////////////////////////////////////////////////////
//MACע��ʹ�õ��˺�����Ӧ�ò����ȷ���MAC�ռ��ʼ��Ϊ0x000x000x00x00
int APDU_S_Mac(APDU_SEND* pApduSend, BYTE_PTR pMak, INT Des);
// �ͷŷ������ݿռ�
int APDU_S_Free(APDU_SEND *pApduSend);
// ��������õ�������, �����Լ�����
int APDU_R_Malloc(APDU_RESP * ApduResp, UINT  le);
// �ͷŷ������ݿռ�
int APDU_R_Free(APDU_RESP *pApduResp);
int APDU_R_Length(APDU_RESP * pApduResp, UINT * pLen);
// ����Ϊ3,SW  �ַ���
int APDU_R_SW1(APDU_RESP * pApduResp, CHAR * pSW1);
// ����Ϊ3,SW  �ַ���
int APDU_R_SW2(APDU_RESP * pApduResp, CHAR * pSW2);
// �ռ�ɸ���APDU_R_Length�ĳ��ȷ���
int APDU_R_Data(APDU_RESP * pApduResp, CHAR * data);
//============================================================================
// Ӧ������
int AppBlock(APDU_SEND * pApduSend, BYTE p1, BYTE p2, UINT lc, BYTE_PTR data);
// Ӧ�ý���
int AppUnBlock(APDU_SEND * pApduSend, BYTE p1, BYTE p2, UINT lc, BYTE_PTR data);
// ������
int CardBlock(APDU_SEND * pApduSend, BYTE p1, BYTE p2, UINT lc, BYTE_PTR data);
// �ⲿ��֤
int ExAuth(APDU_SEND * pApduSend, UINT lc, BYTE_PTR data);
// ���������
int GetChallenge(APDU_SEND * pApduSend, UINT le);
// ������Ӧ
int GetResponse(APDU_SEND * pApduSend, UINT le);
// �ڲ���֤
int InAuth(APDU_SEND * pApduSend, UINT lc, BYTE_PTR data);
// PIN����
int PinUnBlock(APDU_SEND * pApduSend, UINT lc, BYTE_PTR data);
// ������������00
int ReadBinary(APDU_SEND * pApduSend, BYTE p1, BYTE p2);
// ������������04
int ReadBinaryMac(APDU_SEND * pApduSend, BYTE p1, BYTE p2, UINT lc, BYTE_PTR data);
// ����¼00
int ReadRecord(APDU_SEND * pApduSend, BYTE p1, BYTE p2);
// ����¼04
int ReadRecordMac(APDU_SEND * pApduSend, BYTE p1, BYTE p2, UINT lc, BYTE_PTR data);
// SELECT���Ʋ���04
int Select(APDU_SEND * pApduSend, BYTE p1, BYTE p2, UINT lc, BYTE_PTR data);
// ���¶���������00
int UpdateBinary(APDU_SEND * pApduSend, BYTE p1, BYTE p2, UINT lc, BYTE_PTR data);
// ���¶���������04
int UpdateBinaryMac(APDU_SEND * pApduSend, BYTE p1, BYTE p2, UINT lc, BYTE_PTR data);
// ���¼�¼00
int UpdateRecord(APDU_SEND * pApduSend, BYTE p1, BYTE p2, UINT lc, BYTE_PTR data);
// ���¼�¼04
int UpdateRecordMac(APDU_SEND * pApduSend, BYTE p1, BYTE p2, UINT lc, BYTE_PTR data);
// У��PIN
int Verify(APDU_SEND * pApduSend, UINT lc, BYTE_PTR data);
//============================================================================
// �޸ĸ���ʶ����
int ChangePin(APDU_SEND * pApduSend, UINT lc, BYTE_PTR data);
// Ȧ��
int CreditForLoad(APDU_SEND * pApduSend, BYTE_PTR data);
// ����
int DebitForPur(APDU_SEND * pApduSend, BYTE_PTR data);
// ȡ��
int CashWithdraw(APDU_SEND * pApduSend, BYTE_PTR data);
// Ȧ��
int DebitForUnload(APDU_SEND * pApduSend, BYTE_PTR data);
// ��ѯ���
int GetBalance(APDU_SEND * pApduSend, BYTE p2);
// ȡ������֤
int GetTransProve(APDU_SEND * pApduSend, BYTE p2, BYTE_PTR data);
// ��ʼ��ȡ��
int InitForCashWD(APDU_SEND * pApduSend, BYTE p2, BYTE_PTR data);
// ��ʼ��Ȧ��
int InitForLoad(APDU_SEND * pApduSend, BYTE p2, BYTE_PTR data);
// ��ʼ������
int InitForPur(APDU_SEND * pApduSend, BYTE p2, BYTE_PTR data);
// ��ʼ��Ȧ��
int InitForUnload(APDU_SEND * pApduSend, BYTE p2, BYTE_PTR data);
// �޸ĳ�ʼ��
int InitForUpdate(APDU_SEND * pApduSend, BYTE_PTR data);
// ��װ����ʶ����
int ReloadPin(APDU_SEND * pApduSend, BYTE lc, BYTE_PTR data);
// �޸�͸֧�޶�
int UpdateLimit(APDU_SEND * pApduSend, BYTE_PTR data);

//////////////////////////////////////////////////////////////////////////////

