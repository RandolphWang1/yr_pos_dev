#ifndef __LCD_H_
#define __LCD_H_

#define	BLACK		0x0000		//��ɫ
#define	BLUE		0x001F		//��ɫ
#define	RED			0xF800		//��ɫ
#define	GREEN		0x07E0		//��ɫ
#define CYAN		0x07FF		//ǳ��ɫ
#define MAGENTA		0xF81F		//��ɫ
#define YELLOW		0xFFE0		//��ɫ
#define WHITE		0XFFFF		//��ɫ


#define FONT12		12
#define FONT16		16
#define FONT20		20
#define FONT24		24

#define SCREEN_LEFT					0
#define SCREEN_RIGHT				319
#define SCREEN_TOP					0
#define SCREEN_BOTTOM				239


#define SCREEN_WIDTH				320
#define SCREEN_HEIGHT				240

#define ALIGN_LEFT			0
#define ALIGN_CENTER		1
#define ALIGN_RIGHT		2


/*
 * function	:	��ʼ��LCD
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int InitLcd();

/*
 * function	:	�趨��Ļ�����С��������ɫ
 * param1	:	�����С(12,16,20,24)
 * param2	:	������ɫ
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
void SetScrFont(int font_size, int font_color);

/*
 * function	:	��ȡ��Ļ�����С��������ɫ
 * param1	:	�����С
 * param2	:	������ɫ
 */
void GetScrFont(int *font_size, int *font_color);

/*
 * function	:	�ָ���һ���趨����Ļ�����С��������ɫ
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
void ReStoreScrFont();

/*
 * function	:	��ʾ�ı�
 * param1	:	x����(������Ϊ��λ)
 * param2	:	y����(������Ϊ��λ)
 * param3	:	���뷽ʽ
 * param4	:	�ı�������
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int TextOut(int x, int y, int align_type, char *string);

/*
 * function	:	���ģʽ��ʾ�ı�
 * param1	:	x����(������Ϊ��λ)
 * param2	:	y����(������Ϊ��λ)
 * param3	:	��䱳����ɫ
 * param4	:	������ɫ
 * param5	:	�ı�������
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int TextOutFill(int x, int y, int align_type, int bk_color, int font_color, char *string);

/*
 * function	:	��ʾ�ı�
 * param1	:	x����(�����ص�Ϊ��λ)
 * param2	:	y����(�����ص�Ϊ��λ)
 * param3	:	�ı�������
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int TextOutByPixel(int x, int y, char *string);

/*
 * function	:	���ģʽ��ʾ�ı�
 * param1	:	x����(0-319)
 * param2	:	y����(1-239)
 * param3	:	��䱳����ɫ
 * param4	:	������ɫ
 * param5	:	�ı�������
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int TextOutFillByPixel(int x, int y, int bk_color, int font_color, char *string);

/*
 * function	:	��ʾ�ı�(֧�ֶ���)
 * param1	:	x����(������Ϊ��λ)
 * param2	:	y����(������Ϊ��λ)
 * param3	:	�ı�������
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int TextOutMultiLine(int x, int y, char *string);

/*
 * function	:	���ȫ��
 */
void Clear();

/*
 * function	:	���������Ļ����
 * param1	:	������ߺ�����
 * param2	:	�����ұߺ�����
 * param3	:	�������������
 * param4	:	�����ұ�������
 */
void ClearRect(int x1, int x2, int y1, int y2);

/*
 * function	:	���ָ����
 * param1	:	��ʼ��
 * param2	:	����
 */
void ClearLine(int start_line, int line_num);

/*
 * function	:	�����趨ǽֽģʽ
 * param1	:	ģʽ���� 1-���� 0-�˳�
 * return	;
 */
void SetWallPaper(int mode);

/*
 * function	:	��ָ����ɫ��ʾ����
 * param1	:	��ɫ
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int ShowBkGround(int color);

/*
 * function	:	��ָ����ɫ��ʾ���ص�
 * param1	:	x����
 * param2	:	y����
 * param3	:	��ɫ
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int ShowPixel(int x, int y, int color);

/*
 * function	:	��ʾ������ʽͼƬ
 * param1	:	x����
 * param2	:	y����
 * param3	:	�г���
 * param4	:	�г���
 * param5	:	ͼƬ��������
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int ShowBmpData(int x, int y, int x_size, int y_size, const unsigned char *pic);

/*
 * function	:	��ʾFLASH�ϵ�ͼƬ
 * param1	:	x����
 * param2	:	y����
 * param3	:	ͼƬ�ļ���(ȫ��)
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int ShowBmpFile(int x, int y, char *bmp_file);

/*
 * function	:	���ƾ���
 * param1	:	������ߺ�����
 * param2	:	�����ұߺ�����
 * param3	:	�������������
 * param4	:	�����ұ�������
 * param5	:	��ɫ
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int DrawRect(int x1, int x2, int y1, int y2, int color);

/*
 * function	:	������
 * param1	:	������ߺ�����
 * param2	:	�����ұߺ�����
 * param3	:	�������������
 * param4	:	�����ұ�������
 * param5	:	��ɫ
 * return	:	0	-	ִ������
 				-1	-	ִ�д���
 */
int FillRect(int x1, int x2, int y1, int y2, int color);
//
int TextOut1(int x, int y, char *string, int align_type);

int PutsXY(int x, int y, char *string);

void ClearDynamic();
#endif
