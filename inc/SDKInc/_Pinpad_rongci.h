#ifndef __PINPAD_RONGCI_H_
#define __PINPAD_RONGCI_H_


#define PINPAD_DEVICE					"/dev/ttyS0"

#define PINPAD_TIMEOUT					1000

#define PINPAD_MODE_DES					1		//DES����ģʽ
#define PINPAD_MODE_3DES				2		//3DES����ģʽ

#define SUCCESS_PINPAD					0		//�ɹ�
#define ERROR_PINPAD					-1		//����
#define ERROR_PINPAD_OPEN				-2		//���豸ʧ��
#define ERROR_PINPAD_TIMEOUT			-3		//��ʱ
#define ERROR_PINPAD_WRITE				-4		//д�豸ʧ��
#define ERROR_PINPAD_READ				-5		//���豸ʧ��
#define ERROR_PINPAD_PARAM				-6		//��������


/*
 * function	:	���������
 * return	:	>0	=	�ɹ�
 *				����			=	ʧ��
 */
int PinpadOpen();

/*
 * function	:	�ر��������
 * param1	:	�豸���
 * return	:	SUCCESS_PINPAD	=	�ɹ�
 *				����			=	ʧ��
 */
int PinpadClose(int handle);

/*
 * function	:	��ȡ�������ID
 * param1	:	�豸���
 * param2	:	�������
 * return	:	SUCCESS_PINPAD	=	�ɹ�
 *				����			=	ʧ��
 */
int PinpadGetID(int handle, char *out_buff);

/*
 * function	:	�����������Ļ����ʾ����
 * param1	:	�豸���
 * param2	:	��
 * param3	:	��ʾ���ı�
 * return	:	SUCCESS_PINPAD	=	�ɹ�
 *				����			=	ʧ��
 */
int PinpadShowText(int handle, int row, char *text_buff);

/*
 * function	:	���LCD
 * param1	:	�豸���
 * return	:	SUCCESS_PINPAD	=	�ɹ�
 *				����			=	ʧ��
 */
int PinpadClearLCD(int handle);

/*
 * function	:	���ü���ģʽ
 * param1	:	�豸���
 * param2	:	����ģʽ   1-des 2-3des
 * return	:	SUCCESS_PINPAD	=	�ɹ�
 *				����			=	ʧ��
 */
int PinpadSetMode(int handle, int mode);

/*
 * function	:	��������Կ
 * param1	:	�豸���
 * param2	:	����Կ�� 0-15
 * param3	:	����Կ
 * return	:	SUCCESS_PINPAD	=	�ɹ�
 *				����			=	ʧ��
 */
int PinpadSetPriKey(int handle, UINT key_id, UCHAR *key_buff);

/*
 * function	:	���ù�����Կ
 * param1	:	�豸���
 * param2	:	����Կ��   0-15
 * param3	:	������Կ�� 0-3
 * param4	:	����Կ
 * return	:	SUCCESS_PINPAD	=	�ɹ�
 *				����			=	ʧ��
 */
int PinpadSetWorkKey(int handle, UINT prikey_id, UINT workkey_id, UCHAR *key_buff);

/*
 * function	:	�������Կ
 * param1	:	�豸���
 * param2	:	����Կ��   0-15
 * param3	:	������Կ�� 0-3
 * return	:	SUCCESS_PINPAD	=	�ɹ�
 *				����			=	ʧ��
 */
int PinpadActiveWorkKey(int handle, UINT prikey_id, UINT workkey_id);

/*
 * function	:	��������
 * param1	:	�豸���
 * param2	:	����ģʽ1
 *				0-����������   ������ ����������ʾ*
 *				1-��������һ�� ������ ����������ʾ*
 *				2-����������   ������ ����������ʾ*
 *				3-��������һ�� ������ ����������ʾ*
 * param3	:	����ģʽ2
 *				0-��ȷ�ϼ��򵽴�ָ���ĳ���
 *				1-��ȷ�ϼ�
 *				2-����ָ���ĳ���
 *				3-����ָ���ĳ��Ȳ���ȷ�ϼ�
 * param4	:	12λ����
 * param5	:	�������
 * return	:	SUCCESS_PINPAD	=	�ɹ�
 *				����			=	ʧ��
 */
int PinpadInputPwd(int handle, UINT mode1, UINT mode2, char *card_no, char *out_buff);

/*
 * function	:	����MAC
 * param1	:	�豸���
 * param2	:	���������ַ���
 * param3	:	���������ַ�������
 * param4	:	�������MAC
 * return	:	SUCCESS_PINPAD	=	�ɹ�
 *				����			=	ʧ��
 */
int PinpadCalcMac(int handle, char *in, UINT length, char *out);

/*
 * function	:	���ݼӽ���
 * param1	:	�豸���
 * param2	:	���������ַ���
 * param3	:	������Ľ��
 * param4	:	����/����    0/1
 * return	:	SUCCESS_PINPAD	=	�ɹ�
 *				����			=	ʧ��
 */
int PinpadEncrypt(int handle, char *in, char *out, int mode);



#endif
