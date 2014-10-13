#include "Main.h"


static int ColorTest(int color, char *text)
{
	Clear();

	if(FillRect(0, 319, 0, 239, color) != OK)
		return ERROR;

	SetScrFont(0, BLACK);
	if(TextOut(0, 2, ALIGN_CENTER, text) != OK)
		return ERROR;

	SetScrFont(0, BLUE);
	if(TextOut(0, 3, ALIGN_CENTER, text) != OK)
		return ERROR;

	SetScrFont(0, RED);
	if(TextOut(0, 4, ALIGN_CENTER, text) != OK)
		return ERROR;

	SetScrFont(0, GREEN);
	if(TextOut(0, 5, ALIGN_CENTER, text) != OK)
		return ERROR;

	SetScrFont(0, CYAN);
	if(TextOut(0, 6, ALIGN_CENTER, text) != OK)
		return ERROR;

	SetScrFont(0, MAGENTA);
	if(TextOut(0, 7, ALIGN_CENTER, text) != OK)
		return ERROR;

	SetScrFont(0, YELLOW);
	if(TextOut(0, 8, ALIGN_CENTER, text) != OK)
		return ERROR;

	SetScrFont(0, WHITE);
	if(TextOut(0, 9, ALIGN_CENTER, text) != OK)
		return ERROR;

	WaitKey(0);

	return OK;
}

void LcdTest()
{
	//��ɫ����
	if(ColorTest(BLACK, "��ɫ") != OK)
		goto TEST_FAIL;
	//��ɫ����
	if(ColorTest(BLUE, "��ɫ") != OK)
		goto TEST_FAIL;
	//��ɫ����
	if(ColorTest(RED, "��ɫ") != OK)
		goto TEST_FAIL;
	//��ɫ����
	if(ColorTest(GREEN, "��ɫ") != OK)
		goto TEST_FAIL;
	//ǳ��ɫ����
	if(ColorTest(CYAN, "ǳ��ɫ") != OK)
		goto TEST_FAIL;
	//��ɫ����
	if(ColorTest(MAGENTA, "��ɫ") != OK)
		goto TEST_FAIL;
	//��ɫ����
	if(ColorTest(YELLOW, "��ɫ") != OK)
		goto TEST_FAIL;
	//��ɫ����
	if(ColorTest(WHITE, "��ɫ") != OK)
		goto TEST_FAIL;

	//�����С��ͼƬ����
	Clear();

	if(FillRect(0, 319, 0, 239, BLACK) != OK)
		goto TEST_FAIL;

	SetScrFont(FONT12, WHITE);
	if(TextOutByPixel(20, 20, "12������ 12345 abcde") != OK)
		goto TEST_FAIL;

	SetScrFont(FONT16, WHITE);
	if(TextOutByPixel(20, 40, "16������ 12345 abcde") != OK)
		goto TEST_FAIL;

	SetScrFont(FONT20, WHITE);
	if(TextOutByPixel(20, 70, "20������ 12345 abcde") != OK)
		goto TEST_FAIL;

	SetScrFont(FONT24, WHITE);
	if(TextOutByPixel(20, 100, "24������ 12345 abcde")!= OK)
		goto TEST_FAIL;

	//��ʾ����ͼƬ
	ShowBmpFile(80, 140, "pic/test.bmp");

	WaitKey(0);
	return;

TEST_FAIL:
	Clear();
	TextOut(5, 5, ALIGN_CENTER, "��ʾ������ʧ��");
	GetKey(0);
}



