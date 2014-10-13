#ifndef __INPUT_METHOD_H_
#define __INPUT_METHOD_H_


#define IME_TOTAL					3

#define IME_ENGLISH				0
#define IME_NUMBER					1
#define IME_CHINESE				2


#define IME_MAX					100		//�������������ַ���



extern char *input_method_map;


/*
 * function	:	�����
 * param1	:	��Ļ����x����
 * param2	:	��Ļ����y����
 * param3	:	���뻺����
 * param4	:	���뻺��������
 * param5	:	���뷨
 * param6	:	������ɫ
 * param7	:	������ɫ
 * param8	:	�Ƿ������
 * param9	:	�Ƿ��������ָ�����Ȳ��ܷ���
 * param10	:	�Ƿ������л����뷨
 * return	:	�ɹ�	:	OK
 *				ʧ��	:	ERROR
 */
int Input(int x, int y, char *buff, int buff_len, int input_method, int bk_color, int font_color,
	BOOL is_secret, BOOL is_full_len, BOOL is_change);

/*
 * function	:	��ȡ��ǰ���뷨
 * return	:	��ǰ���뷨
 */
int GetInputMethod();

#endif
