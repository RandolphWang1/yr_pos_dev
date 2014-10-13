#ifndef __PROC_8583_
#define __PROC_8583_

/* ISO 8583 Message Structure Definitions */
struct  ISO_8583 
{
	int    len;             /* data element max length */
	unsigned char    type;  /* bit 0--x, bit 1--n�����, bit 2--z bit 3--b*/
	unsigned char    flag;  /* length field length: 1--LLVAR�� 2--LLLVAR��*/
};

struct data_element_flag 
{
	short bitf;
	short len;
	int   dbuf_addr;
};

typedef struct  
{
	struct  data_element_flag f[128];
	short   off;
	char    dbuf[1024];
	char    message_id[10];
} ISO_data;

extern ISO_data    Iso, Iso1;
extern struct ISO_8583 iso8583[128];


/*
 * function	:	����ͨ�ַ���ת����ISO8583��ʽ�Ľṹ��
 * param1		:	��ͨ�ַ���������
 * param2		:	ISO8583�ṹ��ָ��
 * return		:	0		- �ɹ�
 *				����	- ʧ��
 */
int StrToIso(UCHAR *, ISO_data *);

/*
 * function	:	��ISO8583��ʽ�Ľṹ��ת������ͨ�ַ���
 * param1		:	��ͨ�ַ���������
 * param2		:	ISO8583�ṹ��ָ��
 * return		:	0		- �ɹ�
 *				����	- ʧ��
 */
int IsoToStr(UCHAR *, ISO_data *);

/*
 * function	:	���ISO8583�ṹ��ָ��������
 * param1		:	ISO8583�ṹ��ָ��
 * param2		:	Ҫ�������
 * param3		:	��������������
 * return		:	����������ݵĳ���
 */
int GetBit(ISO_data *, int, UCHAR *);

/*
 * function	:	���ISO8583�ṹָ������ͬʱ����Bitmap��Ӧλ
 * param1		:	ISO8583�ṹ��ָ��
 * param2		:	Ҫ�������
 * param3		:	��������������
 * param4		:	Ҫ������ݵĳ���
 * return		:	����������ݵĳ���
 */
int SetBit(ISO_data *, int, UCHAR *, int);

/*
 * function	:	���ISO8583�ṹȫ��������ݣ�ͬʱ���Bitmap��Ӧλ
 * param1		:	ISO8583���ݵ�ָ��
 * return		:	��
 */
void ClearBit(ISO_data *);

/*
 * function	:	���ISO8583�ṹBitmapָ��λ
 * param1		:	ISO8583�ṹ��ָ��
 * param2		:	ָ����
 * return		:	��
 */
void ClearBit1(ISO_data *,int);

/*
 * function	:	��ASC����ת��ΪBCD����
 * param1		:	ASC���ݴ�
 * param2		:	BCD���ݻ���
 * param3		:	ASC���ݴ��ĳ���
 * param4		:	ת��ģʽ
 * return		:	��
 */
void AscToBcd(UCHAR *, UCHAR *, int, UCHAR);

/*
 * function	:	��BCD����ת��ΪASC����
 * param1		:	ASC���ݴ�
 * param2		:	BCD���ݻ���
 * param3		:	ASC���ݴ��ĳ���
 * param4		:	ת��ģʽ
 * return		:	��
 */
void BcdToAsc(UCHAR *, UCHAR *, int, UCHAR);

/*
 * function	:	ʹ��65-128λ
 * param1		:	ISO8583�ṹ��ָ��
 * return		:	��
 */
void EnableSecBitmap(ISO_data *iso);


int SetIso(int bit, int len, unsigned char type, unsigned char flag);
/*
 * ������convert
 * ���ܣ�ת��ʮ���ַ�Ϊʮ��������
 * ��ڣ�ch:     ��Ҫת�����ַ�
 * ���ڣ� ת�����ʮ������
 * ���أ�-1 ʧ��
 */
int convert(char   ch);
#endif


