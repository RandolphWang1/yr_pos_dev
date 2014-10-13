#ifndef __CDMA_H_
#define __CDMA_H_




#define CDMA_LINK_STATUS_ON					1
#define CDMA_LINK_STATUS_CONNING			2
#define CDMA_LINK_STATUS_BREAK				3

/*
 * function		:	��CDMAģ��
 * return		:	ģ����
 */
int CDMA_Open();

/*
 * function		:	CDMAģ���ʼ��
 * param1		:	ģ����
 * param2		:	�û���(����ΪNULL)
 * param3		:	����(����ΪNULL)
 * param4		:	APN(����ΪNULL)
 * return		:	�ɹ�:	OK
 *					ʧ��:	ERROR
 */
int CDMA_Init(int iHandle, char *user, char *pwd);

/*
 * function		:	CDMAģ���ȡIP
 * param1		:	ģ����
 * param2		:	�û���(����ΪNULL)
 * param3		:	����(����ΪNULL)
 * param4		:	APN(����ΪNULL)
 * return		:	�ɹ�:	OK
 *					ʧ��:	ERROR
 */
int CDMA_DHCP(int iHandle, char *user, char *pwd);

/*
 * function		:	���ӷ�����
 * param1		:	ģ����
 * param2		:	��������ַ
 * param3		:	�������˿�
 * return		:	�ɹ�:	OK
 *					ʧ��:	ERROR
 */
int CDMA_Connect(int iHandle, char *ip, char *port);

/*
 * function		:	���ӷ�����
 * param1		:	ģ����
 * param2		:	��������ַ
 * param3		:	�������˿�
 * return		:	�ɹ�:	OK
 *					ʧ��:	ERROR
 */
int CDMA_ConnectEx(int iHandle, char *ip, char *port);

/*
 * function		:	��������
 * param1		:	ģ����
 * param2		:	�������ݻ�����
 * param3		:	�������ݳ���
 * return		:	�ɹ�:	OK
 *					ʧ��:	ERROR
 */
int CDMA_Send(int iHandle, unsigned char *pucData, int uiLen);

/*
 * function		:	��������
 * param1		:	ģ����
 * param2		:	�������ݻ�����
 * param3		:	�������ݳ���
 * param4		:	��ʱʱ��(��λ:��)
 * return		:	�ɹ�:	OK
 *					ʧ��:	ERROR
 */
int CDMA_Recv(int iHandle, char *pucData, int *puiLen, ULONG ulTimeOut);

/*
 * function		:	�ر�CDMA���
 * param1		:	ģ����
 * return		:	�ɹ�:	OK
 *					ʧ��:	ERROR
 */
int CDMA_Close(int iHandle);

/*
 * function		:	����CDMAģ��
 * param1		:	ģ����
 * return		:	�ɹ�:	OK
 *					ʧ��:	ERROR
 */
int CDMA_Reset(int iHandle);

/*
 * function		:	��ȡ����״̬
 * return			:	��ǰ����״̬
 */
int CDMA_GetLinkStatus();



#endif

