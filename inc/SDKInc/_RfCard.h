#ifndef __RF_CARD_H_
#define __PRINTER_H_



/*
 * function	:	�򿪶����豸
 * return	:	>0	-	ִ������
 			<=0	-	ִ�д���
 */
 int M1Open(int port);

/*
 * function	:	�رն����豸
 */
void M1Close(int iHandle);

/*
 * function	:	Ѱ��
 * param3	:	��ʱʱ��
 * return	:	0	-	ִ������
 				<0	-	ִ�д���
 */
int M1Detect(int iHandle, char *szID, ULONG ulTimeOut);

/*
 * function	:	��֤������Կ
 * param1	:	���
 * param2	:	��Կ
 * param3	:	��ʱʱ��
 * return	:	0	-	ִ������
 				<0	-	ִ�д���
 */
int M1AuthorReadKey(int iHandle, BYTE block_no, char *szID, char *key);

/*
 * function	:	��ȡM1��
 * param1	:	�����豸���
 * param2	:	���
 * param3	:	��������-16�ֽ�
 * return	:	0	-	ִ������
 				<0	-	ִ�д���
 */
int M1Read(int iHandle, BYTE block_no, char *out_buff);

/*
 * function	:	��֤д����Կ
 * param1	:	���
 * param2	:	��Կ
 * param3	:	��ʱʱ��
 * return	:	0	-	ִ������
 				<0	-	ִ�д���
 */
int M1AuthorWriteKey(int iHandle, BYTE block_no, char *szID, char *key);

/*
 * function	:	дM1��
 * param1	:	д���豸���
 * param2	:	���
 * param3	:	д������-16�ֽ�
 * return	:	0	-	ִ������
 				<0	-	ִ�д���
 */
int M1Write(int iHandle, BYTE block_no, char *in_buff);

/*
 *port            :Ĭ��ʹ��port=1;
 * function	:	���ԷǽӴ�CPU��
 * return	:	0	-	ִ������
 				<0	-	ִ�д���
 */
int RFCardCPUTest(int port);


#endif

