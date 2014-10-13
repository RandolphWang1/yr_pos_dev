//
/**********************************************************
*函数： init_control
*说明:  
*输入：	
*返回：
*NOTE: 
***********************************************************/
int init_control(void);

//
/**********************************************************
*函数： switch_COM0
*说明:  switch COM0 between MODEM and MC55.
*输入：	
*返回： 
*NOTE:  
***********************************************************/
int switch_COM0(int channel);

//
/**********************************************************
*函数： switch_COM2
*说明:  switch COM0 between PINPAD and external mifare reader.
*输入：	
*返回： 
*NOTE:  
***********************************************************/
int switch_COM2(int channel);

//
/**********************************************************
*函数： switch_CTSRTS
*说明:  switch CTS/RTS between MODEM and MC55.
*输入：	
*返回： 
*NOTE:  
***********************************************************/
int switch_CTSRTS(int channel);

//
/**********************************************************
*函数： control_DTR
*说明:  control DTR line:0 or 1.
*输入：	
*返回： 
*NOTE:  
***********************************************************/
int control_DTR(int value);

//
/**********************************************************
*函数： modem_reset
*说明:  
*输入：	
*返回：
*NOTE: 
***********************************************************/
int modem_reset(void);

//
/**********************************************************
*函数： MC55_power_off
*说明:  
*输入：	
*返回：
*NOTE: 
***********************************************************/
int MC55_power_on(void);

//
/**********************************************************
*函数： MC55_emerg_off
*说明:  
*输入：	
*返回：
*NOTE: 
***********************************************************/
int MC55_emerg_off(void);

//
/**********************************************************
*函数： MC55_reset
*说明:  
*输入：	
*返回：
*NOTE: 
***********************************************************/
int MC55_reset(void);

//
/**********************************************************
*函数： power_5v
*说明:  
*输入：	0:off;1:on
*返回：
*NOTE: 
***********************************************************/
int power_5v(int value);

//
/**********************************************************
*函数： power_modem
*说明:  
*输入：	0:off;1:on
*返回：
*NOTE: 
***********************************************************/
int power_modem(int value);

//
/**********************************************************
*函数： get_power_mode
*说明:  
*输入：	
*返回： 
*NOTE: 
***********************************************************/
int get_power_mode(void);
//
/**********************************************************
*函数： get_power_status
*说明:  
*输入：	
*返回：
*NOTE: 
***********************************************************/
int get_power_status(void);

//
/**********************************************************
*函数： usb_slave_enable
*说明:  
*输入：	
*返回： 
*NOTE: 
***********************************************************/
int usb_slave_enable(void);

//
/**********************************************************
*函数： usb_slave_disable
*说明:  
*输入：	
*返回： 
*NOTE: 
***********************************************************/
int usb_slave_disable(void);

//
/**********************************************************
*函数： get_lan_status
*说明:  
*输入：	
*返回： -1:lan not link.0:linked.
*NOTE: 
***********************************************************/
int get_lan_status(void);

//
/**********************************************************
*函数： init_RTC
*说明:  init backup battery.
*输入：	
*NOTE:  
*返回： 
***********************************************************/
int init_RTC(void);

//
/**********************************************************
*函数： read_date
*说明:  in BCD format.
*输入：	
*NOTE:  
*返回： 
***********************************************************/
int read_date(unsigned char *century,unsigned char *year,unsigned char *month,unsigned char *day,unsigned char *week);

//
/**********************************************************
*函数： read_time
*说明:  in BCD format.
*输入：	
*NOTE:  
*返回： 
***********************************************************/
int read_time(unsigned char *hour,unsigned char *minute,unsigned char *second);

//
/**********************************************************
*函数： write_date
*说明:  in HEX format.
*输入：	
*NOTE:  
*返回： 
***********************************************************/
int write_date(unsigned int year,unsigned char month,unsigned char day);

//
/**********************************************************
*函数： write_time
*说明:  in HEX format.
*输入：	
*NOTE:  
*返回： 
***********************************************************/
int write_time(unsigned char hour,unsigned char minute,unsigned char second);

//
/**********************************************************
*函数： read_voltage
*说明： 
*调用: 
*输入：
*返回:  positive:value;
*       -1:fail
***********************************************************/
int read_voltage(void);

//
/**********************************************************
*函数： read_temp
*说明： 
*调用: 
*输入：
*返回:  positive:value;
*       -1:fail
***********************************************************/
int read_temp(void);

//
/**********************************************************
*函数： extrf_wakeup
*说明： 外置清华模块RF模块读取非接时,如果通过串口命令进入休眠,此函数可以唤醒模块
*调用: 
*输入：
*返回:  0:ok
*       -1:fail
***********************************************************/
int extrf_wakeup(void);

//
/**********************************************************
*函数： SERIAL_Open
*说明:  open serial port.
*输入：	
*NOTE:  
*返回： 
***********************************************************/
int SERIAL_Open(char *port,int speed);

//
/**********************************************************
*函数： SERIAL_Read
*说明:  
*输入：	File Handle             int iHandle
        Output Data Buffer      unsigned char *recv_data
        Output Data Buffer Len  unsigned short recv_len
*NOTE:  
*返回： 
***********************************************************/
int SERIAL_Read(int iHandle,unsigned char *recv_data,unsigned short recv_len);

//
/**********************************************************
*函数： SERIAL_Write
*说明:  
*输入：	
*NOTE:  
*返回： 
***********************************************************/
int SERIAL_Write(int iHandle,unsigned char *send_data,unsigned short send_len);

//
/******************************************************
函数：  SERIAL_Write
说明：
输入：  File Handle             int iHandle 
返回： 
dairy: 
Feb25,2011-MK modified.
*******************************************************/
int SERIAL_Close(int iHandle);

//
/**********************************************************
*函数：	se955_init
*说明：	
*输入： 
*返回： 
***********************************************************/ 
int se955_init();

//
/**********************************************************
*函数：	se955_scan
*说明：	
*输入： se955_uart_handle:uart handle.
*       timeout:扫描超时,以0.1秒为单位,最大0.1秒*200=20秒.最小超时为0.5秒.
*返回： *recv_data
*       <=0:recv fail. 
*       >0:recv byte.
***********************************************************/ 
int se955_scan(char *recv_data,int timeout);

//
/**********************************************************
*函数：	hw5180_init
*说明：	honeywell 5180 init.
*输入： 
*返回： -1:init fail. 0:ok.
***********************************************************/ 
int hw5180_init();
//
/**********************************************************
*函数：	hw5180_scan
*说明：	
*输入： scan_handle:uart handle.
*       timeout:扫描超时,以0.1秒为单位,最大0.1秒*200=20秒.最小超时为0.5秒.
*返回： *recv_data
*       <0:error.-2:timeout
*       >0:recv byte.
***********************************************************/ 
int hw5180_scan(char *recv_data,int timeout);

//
/**********************************************************
*函数： SERIAL_AutoRead
*说明:  限定条件读串口
*输入：	iHandle-串口句柄
*       read_mode-读取模式.
*           0=按指定recv_len读,若读不到指定字节数就超时,则返回-1;
*           1=按指定recv_len读,若读不到指定字节数就超时,返回实际读到的字节数目.若什么数据也没收到,则仍旧返回-1.
*       *recv_data-指向接收数据区
*       recv_len-期待接收长度
*       first_timeout:首字节接收超时,范围5-200.以0.1秒为单位,最大0.1秒*200=20秒.最小0.5秒.>200或<5视为最小超时0.5秒.
*       next_timeout:字节间超时,范围5-200.以0.1秒为单位,最大0.1秒*200=20秒.最小0.5秒.>200或<5视为最小超时0.5秒.
*NOTE:  
*返回： >0:(read_mode==1)实际收到的字节数.
*       0:(read_mode==0)接收正确.
*       -1:接收中出现错误
*       -2:接收超时.
***********************************************************/
int SERIAL_AutoRead(int iHandle,int read_mode,unsigned char *recv_data,int recv_len,int first_timeout,int next_timeout);

//
/**********************************************************
*函数： control_debug
*说明： CONTROL GPF2 PIN LOW 1us.
*调用: 
*输入：
*返回:  
***********************************************************/
void control_debug(void);

//
/**********************************************************
*函数： M35_power_on
*说明:  
*输入：	
*返回：
*NOTE: 
***********************************************************/
int M35_power_on(void);

//
/**********************************************************
*函数： send_rts
*说明： control RTS
*调用: 
*输入：
*返回:  0:process ok
*       -1:SYS ERR
***********************************************************/
int send_rts(int value);
//
/**********************************************************
*函数： recv_cts
*说明： get CTS status.
*调用: 
*输入：
*返回:  0 or 1.
*       -1:sys err.
***********************************************************/
int recv_cts(void);

//
/**********************************************************
*函数： kcli
*说明： 
*调用: 
*输入：
*返回:  
***********************************************************/
void kcli(void);
//
/**********************************************************
*函数： ksti
*说明： 
*调用: 
*输入：
*返回:  
***********************************************************/
void ksti(void);