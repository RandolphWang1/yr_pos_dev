#ifndef __KBD_H_
#define __KBD_H_


#define KEY_0       	0x00
#define KEY_1       	0x01
#define KEY_2       	0x02
#define KEY_3       	0x03
#define KEY_4       	0x04
#define KEY_5       	0x05
#define KEY_6       	0x06
#define KEY_7       	0x07
#define KEY_8       	0x08
#define KEY_9       	0x09
#define KEY_F1			0x0A
#define KEY_UP			0x0B
#define KEY_DOWN		0x0C
#define KEY_F2			0x0D
#define KEY_BACKSPACE	0x0E
#define KEY_ENTER		0x0F
#define KEY_ASTERISK	0x10		//*
#define KEY_POUND		0x11		//#
#define KEY_CANCEL		0x12


/*
 * function	:	��ʼ��LCD
 * param1	:	
 * return	:	0	-	��ʼ���ɹ�
 				-1	-	��ʼ������
 				-2	-	̽�ⲻ��������
 */
int InitKbd();

#define KEY_LIGHT_LEVEL1		1
#define KEY_LIGHT_LEVEL2		2
#define KEY_LIGHT_LEVEL3		3
/*
 * function	:	�趨LCD����
 * param1	:	��������
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int SetLcdLight(UCHAR bright_level);

/*
 * function	:	�趨�Զ��رձ���ʱ��
 * param1	:	ʱ��(��λ-��)
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int SetShutBkLightTime(UCHAR auto_time);

/*
 * function	:	����һ��
 * param1	:	
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int Beep();

/*
 * function	:	����/��ֹ ����������
 * param1	:	����
 *				TRUE	-	����
 *				FALSE	-	��ֹ
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int EnableBeep(BOOL on_off);

/*
 * function	:	�ɹ�������
 * param1	:	
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
void OkBeep();

/*
 * function	:	ʧ�ܷ�����
 * param1	:	
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
void FailBeep();

/*
 * function	:	ָ��ʱ������Ӧ����
 * param1	:	ָ����ʱ��(��λ:����)(ʱ��Ϊ0��ʾһֱ�ȴ�)
 * return	:	0	-	ִ������
 				-1	-	����
 				-2	-	��ʱ
 */
int WaitKey(ULONG lTimeOut);

/*
 * function	:	��ȡָ������
 * param1	:	ָ���İ���ֵ
 * param2	:	ָ����ʱ��(��λ:����)(ʱ��Ϊ0��ʾһֱ�ȴ�)
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
char WaitLimitKey(char *buff, int len, ULONG ulTimeOut);

/*
 * function	:	����Ƿ��а���
 * param1	:	
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
BOOL KbdHit();

/*
 * function	:	�����¼�֮���ȡ��ֵ(�˺�������KbdHit���óɹ��󷽿�ʹ��)
 * param1	:	
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
UCHAR GetKey();

/*
 * function	:	��ȡ��������
 * param1	:	��ֵ
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int GetKeyName(UCHAR KeyValue, char *KeyName);

/*
 * function	:	����/��ֹ ����
 * param1	:	����
 *				TRUE	-	����
 *				FALSE	-	��ֹ
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
void EnableKbd(BOOL on_off);

/*
 * function	:	��ռ��̻�����
 * param1	:
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int ClearKbd();

/*
 * function	:	ǿ�ƹػ�
 * param1	:
 * return	:	0	-	ִ������
 				����-	ִ�д���
 */
int PowerOff();


#endif
