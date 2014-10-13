#ifndef __PINPAD_H_
#define __PINPAD_H_


extern int iPinpadHandle;

/*
 * �������ܣ������û���Կ:��������Կ��ΪMKIndex�û���Կ��ΪWKIndex���û���Կ
 * ��ڣ�        
 *              MKIndex - ����Կ������0~9����
 *              WKIndex - �û���Կ������0~1����
 *              DesMode - DES���ܷ�ʽ��1-��DES��2-3DES; 
 * ���ڣ�       �ޣ�
 * ��������ֵ�� -1 - ʧ�ܣ�
 *              0  - �ɹ��� 
 */
int PINPAD_ActiateKey(int MKIndex, int WKIndex, int DesMode);

/*
 * �������ܣ�   ��������������״̬
 * ��ڣ�       �ޣ�
 * ���ڣ�       �ޣ�
 * ��������ֵ�� -1 - ʧ�ܣ�
 *              0  - �ɹ��� 
 */
int PINPAD_ChkStatus(void);

/*
 * �������ܣ�   ͨ�����������ʾ���׽�
 * ��ڣ�       
 *              pSrcBuf - Ҫ��ʾ�����ݣ�
 *              nSrcSz - Ҫ��ʾ���ݵĳ��ȣ�
 *              nSecond - ��ʾʱ��(1~15��)��
 * ���ڣ�       
 *              �ޣ�
 * ��������ֵ�� 
 *              -1 - ʧ�ܣ�
 *              0 - �ɹ��� 
 */
void PINPAD_ConfirmAmount(char *pSrcBuf, int nSrcSz, int nSecond);

/*
 * �������ܣ�   ͨ�����������ʾ��
 * ��ڣ�       
 *              pSrcBuf - Ҫ��ʾ�����ݣ�
 *              nSrcSz - Ҫ��ʾ���ݵĳ���;
 *              nSecond - ��ʾʱ��(1~15��)��
 * ���ڣ�       
 *              �ޣ�
 * ��������ֵ�� 
 *              -1 - ʧ�ܣ�
 *              0 - �ɹ��� 
 */
void PINPAD_DisplayBalance(char *pSrcBuf, int nSrcSz, int nSecond);

/*
 * �������ܣ�ʹ�õ�ǰ����Ĺ�����Կ���û����ݽ��м��ܣ�
 * ��ڣ�         
 *              InData - ��Ҫ���ܵ��û����ݣ� 
 *              InDataLen - �û����ݵĳ��ȣ�
 * ���ڣ�       
 *              OutData - ���ܺ�����ݣ�
 *              OutDataLen - �������ݳ��ȵĵ�ַ��
 * ��������ֵ�� 
 *              -1 - ʧ�ܣ�
 *              0  - �ɹ��� 
 */
int PINPAD_Encrypt(unsigned char *InData, int InDataLen, unsigned char *OutData, int *OutDataLen);

/*
 * �������ܣ���ȡ����汾�� 
 * ��ڣ��ޣ�
 * ���ڣ��ޣ�
 *����ֵ���ޣ�
 */
void PINPAD_GetVersion(void);

/*
 * �������ܣ���ȡ����ģʽ
 * ��ڣ��ޣ�
 * ���ڣ�cDesMode:��ǰ�ܼ��ļ���ģʽ��
 *          1 - ��DES��
 *          2 - 3DES��
 *����ֵ�� 
 *        0 - �ɹ�;
 *        -1 - ʧ�ܣ�
 */
int PINPAD_GetDesMode(char *cDesMode);
/*
 * �������ܣ�   ������Կ��������������Կ��
 * ��ڣ�       DesMode - ��/˫DESģʽ��
 *              Index - ����Կ������
 *              Mkey - ����Կ��
 *              MkeyLen - ����Կ���ȣ�
 * ���ڣ�       �ޣ�
 * ��������ֵ�� -1 - ʧ�ܣ�
 *              0  - �ɹ��� 
 */
int PINPAD_SetMasterKey(int DesMode, int Index, unsigned char *Mkey, int MkeyLen);

/*
 * �������ܣ����������С���볤��;
 * ��ڣ�Mode - ����pin��������С����ѡ�
 *           0����С���볤�ȣ�
 *           1��������볤�ȣ�
 *       Pinlen - ���볤��ֵ��
 * ���ڣ��ޣ�
 * ����ֵ��0 - �ɹ���
 *         -1 - ʧ�ܣ�
 */
int PINPAD_SetPinLen(int Mode, int PinLen);

/*
 * �������ܣ�   �����û���Կ��
 * ��ڣ�        
 *              MKIndex - ����Կ������0~9����
 *              WKIndex - �û���Կ������0~1����
 *              WKey - �û���Կ���ݣ�
 *              WKeyLen - �û���Կ���ȣ�
 * ���ڣ�       �ޣ�
 * ��������ֵ�� -1 - ʧ�ܣ�
 *              0  - �ɹ��� 
 */
int PINPAD_SetWorkKey(int MKIndex, int WKIndex, unsigned char *WKey, int WKeyLen);

/*
 * �������ܣ�   ͨ��������̼���MAC��
 * ��ڣ�        
 *              PanBuf - ���ʺ�(12λ����)��  
 * ���ڣ�       
 *              PinBlock - ���ܺ��Pin Block��
 *              PinLen - �ͻ���������볤�ȵ�ַ��
 *              lWaitTime - ��ʱʱ�� �Ժ���Ϊ��λ��
 * ��������ֵ�� 
 *              -1 - ʧ�ܣ�
 *              0  - �ɹ���  
 */
int PINPAD_CalcPinBlock(char *PanBuf, char *PinBlock,  int *PinLen, ULONG lWaitTime);

/*
 * �������ܣ�   ͨ��������̼���MAC��
 * ��ڣ�        
 *              MacMode - MAC�����㷨��
 *                      0��ANSI X9.9�㷨��
 *                      1��ECB�㷨��  
 *              InData - Ҫ�������ݣ�
 *              InDataLen - Ҫ�������ݵĳ��ȣ�
 * ���ڣ�       
 *              MacData - ���������MACֵ��
 *              MacLen - �ͻ���������볤�ȵ�ַ��
 * ��������ֵ�� 
 *              -1 - ʧ�ܣ�
 *              0  - �ɹ���  
 */
int PINPAD_CalcMAC(int MacMode, char *InData, int InDataLen, char *MacData,  int *MacLen);

/*
 * �������ܣ�   ��PINPAD��λ������״̬
 * ��ڣ�       �ޣ�
 * ���ڣ�       �ޣ�
 * ��������ֵ�� �ޣ� 
 */
void PINPAD_ResetPinpad(void);

/*
 * �������ܣ�   ���PINPAD��Ļ��ʾ
 * ��ڣ�       �ޣ�
 * ���ڣ�       �ޣ�
 * ��������ֵ�� �ޣ� 
 */
void PINPAD_ResetLCD(void);

#endif


