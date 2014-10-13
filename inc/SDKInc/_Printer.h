#ifndef __PRINTER_H_
#define __PRINTER_H_


#define FONT32	32
#define FONT48	48
#define FONT64	64

//QR�����ȼ�
#define QR_ECLEVEL_L    0   //7%
#define QR_ECLEVEL_M    1   //15%
#define QR_ECLEVEL_Q    2   //25%
#define QR_ECLEVEL_H    3   //30%

//QR�����ģʽ
#define QR_MODE_NUM     0   //����ģʽ
#define QR_MODE_AN      1   //��ĸ-����ģʽ
#define QR_MODE_8       2   //8λ����ģʽ
#define QR_MODE_HANZI   3   //����ģʽ


/*
 * function	:	��ʼ����ӡ��
 * param1	:	
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int InitPrinter();

/*
 * function	:	���ô�ӡ����
 * param1	:	����(16,24,32,48,64)
 */
void SetPrintFont(int font);

/*
 * function	:	���ô�ӡ����
 * param1	:	�м��
 * param2	:	�м��
 */
void SetPrintSpace(int row, int col);

/*
 * function	:	���ô�ӡ����
 * return	:	0	-	����״̬
 				-1	-	��ֽ״̬
 */
int GetPrinterStatus();

/*
 * function	:	���ô�ӡ������߽�(�����ص�Ϊ��λ)
 * param1	:	��������
 */
void SetPrintIndent(int indent);

/*
 * function	:	������ǰ�����õ����塢������߽�ֵ��֧�ָ�ʽ���ַ����Ĵ�ӡ
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int FillPrintBuff(char *format,...);

/*
 * function	:	��ӡ����������
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int StartPrint();

/*
 * function	:	��մ�ӡ������������
 */
void ClearPrintBuff();

/*
 * function	:	����ӡ��
 * return		:	����		:	TRUE
 *				������	:	FALSE
 */
BOOL CheckPrinter();

/*
 * function	:	��ӡ����
 * param1	:	����
 * return		:	�ɹ�:	TRUE
 *				ʧ��:	FALSE
 */
BOOL PrintEmptyLine(int row);

/*
 * function	:	��ӡBMPͼƬ
 * param1	:	x���꣬0-47��ͼƬ������λ�ã�0Ϊ����࣬47Ϊ���Ҳ࣬��λ�Ǻ��ס�
 * param2	:	ָ��BMP�ļ�·�����ļ�����
 * return		:0:ok
	-1:no paper.
	-2:invalid bmp position
	-3:can't find bmp file
	-4,-5,-6,-8:open bmp file error
	-7:oversize
	-9,-10:system error
	-11:print fail.
	-12:invalid mode.
	��ע:	1.������ֱ�Ӵ�ӡ��ɫBMPͼƬ����Ҫ��ִ��PrnStart��
			2.���ͼƬ�ߴ��޶�Ϊ��384X��200�㡣
 */
int PrintBMP(unsigned x,char *bmp_file);

//
/**********************************************************
������	PrintQR
˵����	��ӡQR����������(for test).Ŀǰ��֧�ְ汾10.����ȼ�M.
���룺  QR_version  :QR��汾.1-40.
        ec_level    :����ȼ�,�ο�app_printer.h����:
                        QR_ECLEVEL_L    0   //7%
                        QR_ECLEVEL_M    1   //15%
                        QR_ECLEVEL_Q    2   //25%
                        QR_ECLEVEL_H    3   //30%
        enc_mode    :���뷽ʽ,�ο�app_printer.h:
                        QR_MODE_NUM     0   //����ģʽ
                        QR_MODE_AN      1   //��ĸ-����ģʽ
                        QR_MODE_8       2   //8λ����ģʽ
                        QR_MODE_HANZI   3   //����ģʽ
        *str        :��������
        
        x           :ˮƽƫ�Ƶĵ���.��1����(0.125mm)Ϊ��λ����ƫ��.ƫ��������ʹ��ʣ��ռ�������ɶ�ά��.
                        ���㷽��:x+QR��߳�<=384.
       scale       :�Ŵ���,ȡֵ2-8,=�Ŵ�2-8��.�Ƽ��Ŵ�3-5��.
���أ�  -1:��ֽ
        -2:�����QR��汾�����ȼ�
        -3:����ķŴ���
        -4:QR������/QR���С����Χ
        -5:��Чbat_level
        -6:��ӡʧ��
        0:ok.
***********************************************************/
int PrintQR(int QR_version,int ec_level,int enc_mode,char *str,int x,int scale);

/**********************************************************
*������	MoveDotLine
*˵���� ��ӡ����ֽpixel�����ص�,ÿdot=0.0625mm(1mm=16 pixels).��������ڱ�,Խ���ڱ���ֹͣ��ֽ.
*���룺 nStep:�����ֽ��Χ
*���أ� 0:��ֽ����(����趨�˼��ڱ�,Ϊ��⵽�ڱ꣬���Ѿ�Խ���ڱ�).
*       -1:��ֽ(�����Ƿ����ü��ڱ�)
*       -2:��ֽ,�����˺ڱ깦�ܵ�û�ҵ��ڱ�
*       -3:��ֽ,�����˺ڱ깦�ܵ��ڱ����,û����20mm���߳��ڱ�.
*       -4:������
***********************************************************/
int MoveDotLine(int nStep);

/**********************************************************
*������	BmSwitch
*˵����	
*���룺	nBm:0=��ֹ�ڱ��ӡ.1=�����ڱ��ӡ.
*���أ� -1:ִ��ʧ�ܡ�
*       0:ִ�гɹ���
***********************************************************/
int BmSwitch(int nBm);

#endif

