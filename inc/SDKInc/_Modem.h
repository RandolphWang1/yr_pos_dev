/***************************************************************************
    Li,Hengbo
    2009-03-10
***************************************************************************/
#ifndef __MODEM_H_
#define __MODEM_H_


#define DIALER_OK						OK
#define DIALER_ERROR					ERROR 



extern int			iModemHandle;
extern char		*p_map;



/*
 * function	:	Ԥ����
 * param1	:	�Ƿ�����
 * param2	:	���ߺ���
 * param3	:	��һ���绰����
 * param4	:	�ڶ����绰����
 * param5	:	�������绰����
 * return		:	��
 */
void PreDial(BOOL is_out, char out_no, char *phone1,
	char *phone2, char *phone3);

/*
 * function	:	�һ�(�ر�modem)
 * return		:	��
 * info		:	������ģʽ�ر�modem
 */
void DialOff();

/*
 * function	:	�һ�(�ر�modem)
 * return		:	��
 * info		:	����ģʽ�ر�modem
 */
void DialOff_Block();

/*
 * function	:	��������
 * param1	:	�Ƿ�����
 * param2	:	���ߺ���
 * param3	:	��һ���绰����
 * param4	:	�ڶ����绰����
 * param5	:	�������绰����
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
int Modem_Connect(BOOL is_out, char out_no, int delay_times,
	char *phone1, char *phone2, char *phone3);

/*
 * function	:	��������
 * param1	:	�������ݻ�����
 * param2	:	�������ݳ���
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
int Modem_Send(char *data, int len);

/*
 * function	:	��������
 * param1	:	�������ݻ�����
 * param2	:	�������ݳ���
 * return		:	�ɹ�:	OK
 *				ʧ��:	ERROR
 */
int Modem_Recv(char *data, int *len);



#endif

