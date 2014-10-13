#ifndef __SERIAL_H__
#define __SERIAL_H__

extern char pinpad_device[20];



/*
 * function	:	�򿪴���
 * param1	:	���ں�
 * param2	:	������
 * return		:	�ɹ�:	���ھ��
 *				ʧ��:	-1
 */
int SERIAL_Open(char *pcPort,int iSpeed);

/*
 * function	:	�Ӵ��ڶ�����
 * param1	:	���ھ��
 * param2	:	�����ݻ�����
 * param3	:	����������
 * return		:	�����ĳ���
 */
int SERIAL_Read(int iHandle,unsigned char *pucOutData,unsigned short uiOutLen);

/*
 * function	:	�򴮿�д����
 * param1	:	���ھ��
 * param2	:	��Ҫд������
 * param3	:	����������
 * return		:	�ɹ�:	д�볤��
 *				ʧ��:	-1
 */
int SERIAL_Write(int iHandle,unsigned char *pucInData,unsigned short uiInLen);

/*
 * function	:	�رմ���
 * param1	:	���ھ��
 * return		:	0
 */
int SERIAL_Close(int iHandle);


#endif

