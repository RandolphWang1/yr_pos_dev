//////////////////////////////////////////////////////////////////////////////

#ifndef __WIFI_H__
#define __WIFI_H__

//////////////////////////////////////////////////////////////////////////////
//-------------����ʹ��---------------start---------------------------------------

#define WIFIBUFLEN		1024
/////ͨѶ״̬
#define WIFI_WAIT_SYN     	0X00
#define WIFI_WAIT_CTL     	0x01
#define WIFI_LENGTH1      	0x02
#define WIFI_LENGTH2	   	0x03
#define WIFI_CHCK	   	0x04
#define WIFI_RECEDATA	   	0x05
#define WIFI_WAITPADDING  	0x06
#define WIFI_SYN          	0XAA 

//////////////Wifi Parameter/////////////////
//�����������
#define WIFI_BSSID        	0X01   	// Ap Mac Address
#define WIFI_CHANEL       	0X02   	// The Chanel of ap
#define WIFI_SSID         	0x03	// Wifi Bss network ssid
#define WIFI_ENCRYPTTYPE  	0X04	// encrypt switch 0--disbale 1--enable
#define WIFI_ENKEY        	0X05	//  WIFI Key in encrypt mode
#define WIFI_DATATYPE     	0x06	// LLC Data Format         0��RAW��1��UDP��2 �� TCP
#define WIFI_TCPPORT      	0x07	// TCP Sercer Port
#define WIFI_TCPIP        	0X08	// WIFI Module IP address
#define WIFI_TCPSERVERIP  	0x09	// Server IP address
#define WIFI_TCPSERVERMAC 	0x0a	// Server MAC Address(only in RAW mode)
#define WIFI_TCPMASET     	0X0b	// NetMask  1--255.255.255.0; 2--255.255.0.0; 3--255.0.0.0
#define WIFI_TCPGATEWAY   	0X0C	//  GateWay IP address
///ϵͳ��������
#define WIFI_BAUDBATE     	0XA2	// ������0��19200,1��38400?��57600?��115200,4-9600,5-4800,6-2400
#define WIFI_NETMODE      	0XA7	// jion Mode               0-Auto 1-manual
#define WIFI_TRANSPARENT  	0XA9	// ͸������,ģʽѡ�� 0���رգ�1��ʹ��͸�����䣨�����Զ�����ģʽ��UDP���ݸ�ʽ����Ч��
#define WIFI_TCPMONITOR   	0XAA	// TCP Server Switch       0--disbale 1--enable
#define WIFI_APBSSIDENABLE    	0XAB    // only for 1.70 firmware  0--Eable 1--disable
// ��������
#define CTL_DATA     		0X00	////Control Data	
#define NOA_DATA  		0X10	////Normal Data
#define ACK_DATA   	    	0X20	////Ack 
// ��������
#define COMAND_DATA 		0x00   //// Host to wifi
#define MESSAGE_DATA 		0X40   //// Wifi to Host
// Wifi��������
#define SCANNETWORK_DATA   	0x00  	// ��ʼɨ����������
#define LINKNETWORK_DATA   	0X01	// ��ʼ������������
#define CLOSENETWORK_DATA  	0x02	// ��ʼ�Ͽ���������
#define SETNETPARA_DATA    	0X03	// ���ò�������
#define QUERYNETPARA_DATA  	0X04	// ��ѯ��������
#define RESTWIFI_DATA      	0X05	// ��λ����
#define TCPLINK_DATA       	0x06	// TCP��������
#define TCPSENDFAILED_DATA 	0x07	// TCP����ʧ��
// ��Ϣ���ͣ�ģ�鵽���� ������Ϣ
#define SCANNET_END		0X40	// ɨ����������Ϣ
#define LINKNET_END		0X41	// ������������Ϣ 
#define CLOSENET_END		0x42	// �����ѶϿ���Ϣ
#define SETNETPARA_END     	0X43	// ���ò��������Ϣ
#define QUERYNETPARA_END   	0X44	// ��ѯ���������Ϣ
#define RESTWIFI_END       	0X45	// ��ʼ�������Ϣ
#define TCPLINK_END        	0x46	// TCP����״̬��Ϣ
////����֡λ��////////////////////////
#define SYN        		0	    //
#define CTL        		1	    //
#define LENL        		2	    //
#define LENH        		3	    //
#define CHK        		4	    //
#define CMD_DATA       		5	    //
////////�׽�������///////////////////////
#define RAW			0
#define UDP			1
#define TCP			2
//////////////////////////////////////////////////////////////////////////////
#define SERIAL_DELAY		10
//////////////////////////////////////////////////////////////////////////////
extern unsigned char __crc8_tbl[256];

typedef struct NetWorkBuffer
{
	  unsigned char gcIdx;
	  unsigned char gcChanle;
	  unsigned char gcBssId[6];
	  unsigned char gcLeg;
	  unsigned char gcSsid[20];
} NetWorkBuffer;

typedef struct NetParaBuffer
{
   unsigned char M_id;
   unsigned char cLength;
   unsigned char cInfo[64];
}NetParaBuffer;

typedef struct Buffer2
{
	unsigned char  	gcATReceData[WIFIBUFLEN];  // wifi ģ��һ�δ���1440�ֽڣ�������51оƬֻ��1280��xdata
	unsigned int 		gcATReceCount;
} Buffer2;

//-------------����ʹ��-------end-----------------------------------------------
typedef struct KEY_WEP
{
	unsigned char KeyLength;
	unsigned char KeyIndex;
	unsigned char Group[4][14];
} KEY_WEP;

typedef struct T_WIFI
{
	unsigned char nChannelNum;//�ŵ���
	unsigned char szBssid[12+1];//BSSID
	char szSsid[32+1];//SSID
	unsigned char nDatalink;//������·��
	unsigned char szEquipmentIP[15 + 1];//�豸IP
	char szServerMask[15+1];// ��
	char szServerGateway[15+1]; // ����
	char szServerIP[15+1];//��������IP ��ַ
	char szEquipmentPort[5+1];//����˿�
	unsigned char nEncrypType;//��������
	KEY_WEP key_wep;
	unsigned char bTcpMonotor;
}T_WIFI;


////////////////////////////////////////////// ��������///////////////////////
int HardWareInit(void);
int Wifi_Para_set(T_WIFI t_Wifi);
int Wifi_Para_set_Auto(T_WIFI t_Wifi);
int Wifi_Auto_Init(char * sid1,char * sid2,char * sid3,char * sid4,char * sid5,char * sid6,char * sid7,char * sid8,char * sid9);
int WIFIReset(void);
//-------------����ʹ��-------start-----------------------------------------------
int ProcessWIFIData(void);
//-------------����ʹ��-------end-----------------------------------------------
int WIFI_Connect();
int WIFI_Close();
int WIFI_Send(char *szSendData, int nSendLen);
int WIFI_Recv(char *szRecvData, int* nRecvLen);
////////////////////////////////////////////// ��������///////////////////////
#endif //__WIFI_H__


