#ifndef __TIMER_H_
#define __TIMER_H_


#define YYYY_MM						1	//��-��
#define YYYY_MM_DD						2	//��-��-��
#define MM_DD							3	//��-��
#define HH_MM							4	//ʱ-��
#define HH_MM_SS						5	//ʱ-��-��
#define YYYY_MM_DD_HH_MM_SS			6	//��-��-��-ʱ-��-��



/*
 * ʱ��ṹ
 */
typedef struct
{
	char century[2+1];							//����
	char year[2+1];							//��
	char month[2+1];							//��
	char day[2+1];								//��
	char hour[2+1];							//ʱ
	char minute[2+1];							//��
	char second[2+1];							//��
	char week[1+1];							//��
}T_DATETIME;




/*
 * function	:	����ʱ��
 * param1	:	ʱ��ṹָ��
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int SetDateTime(T_DATETIME ptTime);

/*
 * function	:	��ȡʱ��
 * param1	:	ʱ��ṹָ��
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int GetDateTime(T_DATETIME *ptTime);

/*
 * function	:	�Ƚ�����
 * param1	:	��һ��ʱ��ṹָ��
 * param2	:	�ڶ���ʱ��ṹָ��
 * return		:	<0,=0,>0
 */
int DateCmp(T_DATETIME *time1, T_DATETIME *time2);

/*
 * function	:	��ʼ��ʵʱʱ��
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int InitRTC();

/*
 * function	:	�ȴ���ʱ
 * param1	:	�ȴ�ʱ��-��λ:����
 */
void Wait(ULONG millisecond);

/*
 * function	:	����ʱ��
 * param1	:	ʱ�仺����
 * param1	:	��������(����:YYYY_MM_DD_HH_MM_SS)
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int InputTime(int x, int y, T_DATETIME *tTime, int style);

/*
 * function	:	��ʽ������
 * param1	:	ʱ��ṹָ��
 * param2	:	�����
 * param3	:	ԭʼʱ���ַ���
 * return		:	��
 */
void FormatDate(T_DATETIME *ptTime, char space, char *data);

/*
 * function	:	��ʽ��ʱ��
 * param1	:	ʱ��ṹָ��
 * param2	:	�����
 * param3	:	ԭʼʱ���ַ���
 * return		:	��
 */
void FormatTime(T_DATETIME *ptTime, char space, char *data);


#endif


