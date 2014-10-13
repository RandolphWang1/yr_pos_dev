#ifndef __GPRS_H_
#define __GPRS_H_




#define GPRS_LINK_STATUS_ON					1
#define GPRS_LINK_STATUS_CONNING			2
#define GPRS_LINK_STATUS_BREAK				3

/*
 * function	:	��GPRSģ��
 * return		:	ģ����
 */
int GPRS_Open();
int GPRS_init();

void GPRS_SetNet1(char *user, char *pwd, char *apn, char *ip, char *port, int flag);
void GPRS_SetNet2(char *user, char *pwd, char *apn, char *ip, char *port, int flag);

/*
 * function	:	GPRSģ���ʼ��
 * param1	:	ģ����
 * param2	:	�û���(����ΪNULL)
 * param3	:	����(����ΪNULL)
 * param4	:	APN(����ΪNULL)
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
int GPRS_ConfigNet1();
int GPRS_ConfigNet2();
int GPRS_ConfigHttp1();
int GPRS_ConfigHttp2();

int GPRS_GetOper(char *name);
int DistingOper(char * name);

int GPRS_SimReady();
int GPRSAttach();

/*
 * function	:	GPRSģ������
 * param1	:	ģ����
 * param2	:	�û���(����ΪNULL)
 * param3	:	����(����ΪNULL)
 * param4	:	APN(����ΪNULL)
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 *///�Ѹ���
int GPRS_Reset();

/*
 * function	:	���ӷ�����
 * param1	:	ģ����
 * param2	:	��������ַ
 * param3	:	�������˿�
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
int GPRS_ConnectNet1();
int GPRS_ConnectNet2();
int GPRS_ConnectHttp1();
int GPRS_ConnectHttp2();

/*
 * function	:	��������
 * param1	:	ģ����
 * param2	:	�������ݻ�����
 * param3	:	�������ݳ���
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
int GPRS_Send(unsigned char *pucData, int uiLen);
int GPRS_SendEx(unsigned char *pucData, int uiLen);

int GPRS_Send_Http(unsigned char *pucData, int uiLen);
/*
 * function	:	��������
 * param1	:	ģ����
 * param2	:	�������ݻ�����
 * param3	:	�������ݳ���
 * param4	:	��ʱʱ��(��λ:��)
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
#ifdef _GPRS_RECV_OLD
int GPRS_Recv(char *pucData, int puiLen, ULONG ulTimeOut,int flag);
#else
int GPRS_Recv(char *pucData, int *puiLen, ULONG ulTimeOut,int flag);
#endif
int GPRS_Recv_Http(char *pucData, int *puiLen, ULONG ulTimeOut,int flag);

/*
 * function	:	�ر�GPRS���
 * param1	:	ģ����
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
int GPRS_Close();

/*
 * function	:	��ȡģ���ź�ֵ
 * param1	:	ģ����
 * param2	:	�ź�ֵ������
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
int GetSignal(int *nSignal);

/*
 * function	:	�����ź�
 * param1	:	ģ����
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
int SearchSignal();

/*
 * function	:	��ʾ�ź�
 * param1	:	��ʾλ��x����
 * param2	:	��ʾλ��y����
 * param3	:	�ź�ֵ
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
void ShowSignal(int x, int y, int nSignal);


/*
 * function	:	�򿪴���
 * return		:	�ɹ�:	���ھ��
 *				ʧ��:	ERROR
 */
int OpenUart();

/*
 * function		:	��ȡ����״̬
 * return		:	��ǰ����״̬
 */
int GPRS_GetLinkStatus();

int M35_power_on();



#endif


