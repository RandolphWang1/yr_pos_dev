#ifndef __TF_CARD_H_
#define __TF_CARD_H_



//����������
void ClearComChanel(int iHandle);

/*
 * function	:	�򿪶����豸
 * return	:	>0	-	ִ������
 			<=0	-	ִ�д���
 */
 int FM1Open(int port);

/*
 * function	:	�رն����豸
 */
void FM1Close(int iHandle);

/*
 * function	:	Ѱ��
 * param3	:	��ʱʱ��
 * return	:	0	-	ִ������
 				<0	-	ִ�д���
 */
int FM1Detect(int iHandle, char *szID, ULONG ulTimeOut);

/*
 * function	:	��֤������Կ
 * param1	:	���
 * param2	:	��Կ
 * param3	:	��ʱʱ��
 * return	:	0	-	ִ������
 				<0	-	ִ�д���
 */
int FM1AuthorReadKey(int iHandle, BYTE block_no, char *szID, char *key);

/*
 * function	:	��ȡM1��
 * param1	:	�����豸���
 * param2	:	���
 * param3	:	��������-16�ֽ�
 * return	:	0	-	ִ������
 				<0	-	ִ�д���
 */
int FM1Read(int iHandle, BYTE block_no, char *out_buff);

/*
 * function	:	��֤д����Կ
 * param1	:	���
 * param2	:	��Կ
 * param3	:	��ʱʱ��
 * return	:	0	-	ִ������
 				<0	-	ִ�д���
 */
int FM1AuthorWriteKey(int iHandle, BYTE block_no, char *szID, char *key);

/*
 * function	:	дM1��
 * param1	:	д���豸���
 * param2	:	���
 * param3	:	д������-16�ֽ�
 * return	:	0	-	ִ������
 				<0	-	ִ�д���
 */
int FM1Write(int iHandle, BYTE block_no, char *in_buff);

/*
 *port            :Ĭ��ʹ��port=1;
 * function	:	���ԷǽӴ�CPU��
 * return	:	0	-	ִ������
 				<0	-	ִ�д���
 */
int FFCardCPUTest(int port);


#endif

