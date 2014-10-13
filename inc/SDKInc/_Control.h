#ifndef __CONTROL_H_
#define __CONTROL_H_




/*
 * function	:	��ʼ����������
 * param1	:	
 * return	:	0	-	ִ������
 				-1	-	�����򿪴���
 				-2	-	Ŧ�۵���쳣����ʾ�û��������
 				-3	-	��������
 */
int InitControl();

#define POWER_MODE_DC			0	//��ʹ����ӵ�Դ��
#define POWER_MODE_BAT			1	//��ʹ�õ�ء�
#define POWER_MODE_CHARGE		2	//��ӵ�Դ�͵��ͬʱʹ�ã������
#define POWER_MODE_COMPLETE		3	//��ӵ�Դ�͵��ͬʱʹ�ã�������
/*
 * function	:	��ȡ����ģʽ
 * param1	:	
 * return	:	0	-	��ʹ����ӵ�Դ��
 				1	-	��ʹ�õ�ء�
 				2	-	��ӵ�Դ�͵��ͬʱʹ�ã������
 				3	-	��ӵ�Դ�͵��ͬʱʹ�ã�������
 				����-	ִ�д���
 */
int GetPowerMode();

#define POWER_STATUS_RELEASE_0		0	//�ŵ�״̬��0������������״̬�������������ݣ�������ʾ��ǿ�ƹػ���
#define POWER_STATUS_RELEASE_1		1	//�ŵ�״̬��1�����������ʣ�಻��20%��������Ҫ�����硣
#define POWER_STATUS_RELEASE_2		2	//�ŵ�״̬��2������
#define POWER_STATUS_RELEASE_3		3	//�ŵ�״̬��3������
#define POWER_STATUS_RELEASE_4		4	//�ŵ�״̬��4������
#define POWER_STATUS_RELEASE_5		5	//�ŵ�״̬��5�����������ʣ�����>80%

#define POWER_STATUS_CHARGE_1		6	//���״̬���������С��20%
#define POWER_STATUS_CHARGE_2		7	//���״̬���������20%~40%
#define POWER_STATUS_CHARGE_3		8	//���״̬���������40%~60%
#define POWER_STATUS_CHARGE_4		9	//���״̬���������60%~80%
#define POWER_STATUS_CHARGE_5		10	//�����90%����

#define POWER_STATUS_DC				11	//����������������
/*
 * function	:	��ȡ���״̬
 * param1	:	
 * return	:	0	-	�ŵ�״̬��0������������״̬�������������ݣ�������ʾ��ǿ�ƹػ���
 				1	-	�ŵ�״̬��1�����������ʣ�಻��20%��������Ҫ�����硣
 				2	-	�ŵ�״̬��2������
 				3	-	�ŵ�״̬��3������
 				4	-	�ŵ�״̬��4������
 				5	-	�ŵ�״̬��5�����������ʣ�����>80%
 				6	-	���״̬���������С��20%
 				7	-	���״̬���������20%~40%
 				8	-	���״̬���������40%~60%
 				9	-	���״̬���������60%~80%
 				10	-	�����90%����
 				11	-	����������������
 				����-	ִ�д���
 * info:		1. �������ʱ������ÿ2������ʱ����һ�Ρ�
				2. ��ز�ͬ�����£���ѹ�᲻ͬ������ĳЩ������ֵ�����ʾ���䣬����������

 */
int GetPowerStatus();

/*
 * function	:	����modem��Դ����
 * param1	:	ִ�б�־λ 0-�ر� 1-����
 * return	:	0	-	��ȷִ��
 				����-	ִ�д���
 */
int PowerModem(int value);

/*
 * function	:	�л�����ͨ��
 * param1	:	�л�����2������modemͨ��
 * return	:	0	-	��ȷִ��
 				����-	ִ�д���
 */
int SwitchCom2_Modem();

/*
 * function	:	�л�����ͨ��
 * param1	:	�л�����0������modemͨ��
 * return	:	0	-	��ȷִ��
 				����-	ִ�д���
 */
// �����ʹ��
int SwitchCom0_Modem();

/*
 * function	:	�л�����ͨ��
 * param1	:	�л�����0��MC323ͨ��
 * return	:	0	-	��ȷִ��
 				����-	ִ�д���
 */
int SwitchCom0_MC323();

/*
 * function	:	�л�����ͨ��
 * param1	:	�л�����0��MC55ͨ��
 * return	:	0	-	��ȷִ��
 				����-	ִ�д���
 */
int SwitchCom0_MC55();

/*
 * function	:	�л�����ͨ��
 * param1	:	�л�����0��Pinpadͨ��
 * return	:	0	-	��ȷִ��
 				����-	ִ�д���
 */
int SwitchCom2_Pinpad();// ����ʹ��
int SwitchCom0_Pinpad();

/*
 * function	:	�л�����ͨ��
 * param1	:	�л�����2��scanͨ��
 * return	:	0	-	��ȷִ��
 				����-	ִ�д���
 */
int SwitchCom2_Scan();

/*
 * function	:	�л�����ͨ��
 * param1	:	�л�����2���ǽ�ͨ��
 * return	:	0	-	��ȷִ��
 				����-	ִ�д���
 */
int SwitchCom2_Rf(int port);

/*
 * function	:	�л�����ͨ��
 * param1	:	�л�����2���¿��ǽ�ͨ��
 * return	:	0	-	��ȷִ��
 				����-	ִ�д���
 */
int SwitchCom2_DC();

/*
 * function	:	�л�����ͨ��
 * param1	:	�л�����2������ǽ�ͨ��
 * return	:	0	-	��ȷִ��
 				����-	ִ�д���
 */
int SwitchCom2_HH();

/*
 * function	:	��MC55��Դ
 * return	:	0	-	��ȷִ��
 				����-	ִ�д���
 */
int PowerOnMC55();

/*
 * function	:	�ر�MC55��Դ
 * return	:	0	-	��ȷִ��
 				����-	ִ�д���
 */
int PowerOffMC55();

/*
 * function	:	����MODEM
 * return	:	0	-	��ȷִ��
 				����-	ִ�д���
 */
int ModemReset();

/*
 * function	:	����MC55
 * return	:	0	-	��ȷִ��
 				����-	ִ�д���
 */
int MC55Reset();

//
/**********************************************************
*������	se955_init
*˵����	
*���룺 
*���أ� 
***********************************************************/ 
int se955_init();
int InitScan();// ����ʹ��

//
/**********************************************************
*������	se955_scan
*˵����	
*���룺 se955_uart_handle:uart handle.
*       timeout:ɨ�賬ʱ,��0.1��Ϊ��λ,���0.1��*200=20��.��С��ʱΪ0.5��.
*���أ� *recv_data
*       <=0:recv fail. 
*       >0:recv byte.
***********************************************************/ 
int se955_scan(char *recv_data,int timeout);
int StartScan(char *pszRecvData, int nTimeOut);//����ʹ��

//
/**********************************************************
*������ SERIAL_Open
*˵��:  open serial port.
*���룺	
*NOTE:  
*���أ� 
***********************************************************/
int SERIAL_Open(char *port,int speed);

//
/**********************************************************
*������ SERIAL_Read
*˵��:  
*���룺	File Handle             int iHandle
        Output Data Buffer      unsigned char *recv_data
        Output Data Buffer Len  unsigned short recv_len
*NOTE:  
*���أ� 
***********************************************************/
int SERIAL_Read(int iHandle,unsigned char *recv_data,unsigned short recv_len);

//
/**********************************************************
*������ SERIAL_Write
*˵��:  
*���룺	
*NOTE:  
*���أ� 
***********************************************************/
int SERIAL_Write(int iHandle,unsigned char *send_data,unsigned short send_len);

//
/******************************************************
������  SERIAL_Write
˵����
���룺  File Handle             int iHandle 
���أ� 
dairy: 
Feb25,2011-MK modified.
*******************************************************/
int SERIAL_Close(int iHandle);
int M35_power_on();

#endif
