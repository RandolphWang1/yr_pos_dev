#ifndef __FILE_H_
#define __FILE_H_



/*
 * function	:	�������ݵ�ָ���ļ�
 * param1	:	�ļ���
 * param2	:	Ҫ��������ݴ�
 * param3	:	Ҫ��������ݴ�С
 * param4	:	Ҫ����ļ�¼����
 * return		:	��
 * Info:		:	���������¼ʱ��ÿ����¼��СӦһ��
 */
BOOL WriteData(char *file, void* Buff, int size, int index);

/*
 * function	:	��ָ���ļ�������
 * param1	:	�ļ���
 * param2	:	����������ݵĻ�����
 * param3	:	Ҫ�������ݴ�С
 * param4	:	Ҫ���ļ�¼����
 * return		:	��
 */
BOOL ReadData(char *file, void* Buff, int size, int Index);


#endif
