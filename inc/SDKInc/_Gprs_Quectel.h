#ifndef __GPRS_QUECTEL_H_
#define __GPRS_QUECTEL_H_




#define GPRS_LINK_STATUS_ON					1
#define GPRS_LINK_STATUS_CONNING			2
#define GPRS_LINK_STATUS_BREAK				3

/*
 * function	:	��GPRSģ��
 * return		:	ģ����
 */
int GPRS_Open();
int GPRS_Quectel_init();

/*
*function	:	��������
*
*/
int GPRS_Quectel_ConfigNet1();

/*
 * function	:	GPRSģ���ʼ��
 * param1	:	ģ����
 * param2	:	�û���(����ΪNULL)
 * param3	:	����(����ΪNULL)
 * param4	:	APN(����ΪNULL)
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
void GPRS_SetNet1(char *user, char *pwd, char *apn, char *ip, char *port, int flag);
void GPRS_SetNet2(char *user, char *pwd, char *apn, char *ip, char *port, int flag);

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
int GPRS_Quectel_Reset();

/*
 * function	:	���ӷ�����
 * param1	:	ģ����
 * param2	:	��������ַ
 * param3	:	�������˿�
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
int GPRS_Quectel_ConnectNet1();
int GPRS_Quectel_ConnectNet2();

/*
 * function	:	��������
 * param1	:	ģ����
 * param2	:	�������ݻ�����
 * param3	:	�������ݳ���
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
int GPRS_Quectel_Send(unsigned char *pucData, int uiLen);
int GPRS_Quectel_SendEx(unsigned char *pucData, int uiLen);

/*
 * function	:	��������
 * param1	:	ģ����
 * param2	:	�������ݻ�����
 * param3	:	�������ݳ���
 * param4	:	��ʱʱ��(��λ:��)
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */

int GPRS_Quectel_Recv(char *pucData, int *puiLen, ULONG ulTimeOut,int flag);


/*
 * function	:	�ر�GPRS���
 * param1	:	ģ����
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
int GPRS_Quectel_Close();

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



//http ���� 
int GPRS_Quectel_HTTP_Connect();
int GPRS_Quectel_HTTP_Send(char *Pucdata,int uilen);
int GPRS_Quectel_HTTP_Recv(char *pucData,int timeout);








#endif


