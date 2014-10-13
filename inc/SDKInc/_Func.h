#ifndef __FUNC_H_
#define __FUNC_H_



/*
 * function	:	����Ϊ����ģʽ(���򲻴�ӡ������Ϣ)
 * param1	:	ģʽ(TRUE/FALSE)
 * return		:	��
 */
void SetDebug(BOOL debug);

/*
 * function	:	��ӡ������Ϣ
 * return		:	��
 */
void sdkPrintf(const char *format, ...);

/*
 * function	:	��ӡ������Ϣ-��ʱ��ǰ׺
 * return		:	��
 */
void DebugOut(const char *format, ...);

/*
 * function	:	��ӡ������Ϣ(ʮ������)
 * param1	:	����
 * param2	:	����
 * return		:	��
 */
void printf_x(char *title, char *data, int len);

/*
 * function	:	��ӡ������Ϣ(ԭʼ�ַ���)
 * param1	:	����
 * param2	:	����
 * param3	:	����
 * return		:	��
 */
void printf_s(char *title, char *data, int len);

/*
 * function	:	�˵�
 * param1	:	����
 * param2	:	�˵�����
 * param3	:	�Ӳ˵���Ŀ
 * param4	:	�Ӳ˵�����
 */
int MenuDlg(char *title, char **menu, int item_count, char *indent);

/*
 * function	:	��ȡSDK�汾��
 * param1	:	���ذ汾�ŵĻ�����
 */
void GetSDKVersion(char *version);

/*
 * function	:	��ʼ��SDK
 */
void InitSDK();

/*
 * function	:	���˵�ָ���ַ���ĳ���
 * param1	:	�ַ���
 * param1	:	ָ���ַ�
 * return	:	����
 */
int strlen_filt(char *buff, char filt_ch);

/*
 * function	:	���˵�IP��ַ�еĿո��0
 * param1	:	IP��ַ
 */
void FiltIP(char *buff);

/*
 * function	:	����IP
 * param1	:	x����
 * param2	:	y����
 * param3	:	������
 */
int InputIP(int x, int y, char *buff);

/*
 * function	:	��ѯ���ַ���
 * param1	:	ĸ��
 * param2	:	ĸ������
 * param3	:	Ŀ���Ӵ�
 * param4	:	�Ӵ�����
 * return		:	�ַ�����ʼλ��
 */
int FindStr(char *Buffer, int BufLen, char *Target, int TargetLen);

int OpenUart();
int ReadUart(int iHandle, unsigned char * pucOutData, unsigned short uiOutLen, ULONG ulTimeOut);
int WriteUart(int iHandle,unsigned char * pucInData,unsigned short uiInLen);

/*
 * function	:	����״̬��
 * param1	:	
 * return		:	��
 */
int CreateStatusBar(int font_color);

/*
 * function	:	����״̬��
 * param1	:	
 * return		:	��
 */
void OpenStatusBar();

/*
 * function	:	�ر�״̬��
 * param1	:	
 * return		:	��
 */
void CloseStatusBar();

void ShutDown();

/*
 * function	:	�޸Ĳ���
 * param1	:	Ҫ�޸ĵĲ���
 * param2	:	����
 * param3	:	ǰ׺����
 * return		:	��
 */
void ModifyData(char *value, int value_len, char *title);

/*
 * function	:	��ʽ������ַ���
 * param1	:	ǰ׺
 * param2	:	����ַ���
 * param3	:	��׺
 * param4	:	��ʽ����Ľ��
 * return		:	��
 */
void FormatMoney(char *prefix, char *money, char *suffix, char *result);

/*
 * function	:	���������Ƿ���ĳ����֮��
 * param1	:	����
 * param2	:	��ʼ����
 * param3	:	��������
 * return		:	�ڴ�������		:	TURE
 *				���ڸ�������	:	FALSE
 */
BOOL CheckTime(T_DATETIME time, char *start, char *end);

/*
 * function	:	������
 * param1	:	��Ļ����X����
 * param2	:	��Ļ����Y����
 * param3	:	���뻺����
 * param4	:	��������С
 * return	:	�ɹ�			:	���볤��
 *				����			:	-1
 *				ȡ��			:	-3
*/
int InputMoney(int x, int y, char* buff, int size);

/*
 * function	:	�ַ��������ת��Ϊ�Ҷ���(��0)
 * param1	:	�ַ���
 * param2	:	�ַ�������
 * return		:	��
 */
void ChangeLeftToRight(char *data, int len);

/*
 * function	:	��U�̿����ļ�
 * param1	:	POS·��
 * param2	:	U��·��
 * return		:	��
 */
int GetFileFromU(char *pos_path, char *u_path);

/*
 * function	:	�����ļ���U��
 * param1	:	POS·��
 * param2	:	U��·��
 * return		:	��
 */
int CopyFile2U(char *pos_path, char *u_path);

void Fit_Length_by_LeadChar(CHAR *src,   INT maxlen,   CHAR cPadChr);


/*
Buffer:Ŀ�괮
BufLen:Ŀ�괮����
Target:���Ҵ�
TargetLen:���Ҵ�����
*/
int FindString(char *Buffer, int BufLen, char *Target, int TargetLen);

#endif
