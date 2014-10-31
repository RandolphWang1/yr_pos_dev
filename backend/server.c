#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include <stdlib.h>
#include <signal.h>
#include "aliqr.h"
#include <syslog.h>

#ifdef ALIPAY_FIFO
#include <fcntl.h>
#endif

struct payInfo qrpay_info;
//char qrQueryResult[1024] = {0};
char time_mark[32] = {0};
#ifdef ALIPAY_FIFO
static unsigned int query_count;
#endif

/* timer to get alipay payment response -- sample code */ 
void payment_alarm_handler(int sig) {
    //struct payInfo qrpay_info;
    struct qr_result payquery_result;
    int nbytes;
    int socket_fd;
    //strcpy(qrpay_info.imsi,"460006922139942");
    memset(payquery_result.qr_string,0,QRLEN);
    memset(payquery_result.time_mark,0,32);
#if 1
    if (time_mark[0] == '\0'){
       /* time_mark is missing, using random one to require a new one */
       //printf("query parameter: time_mark is missing!\n");
       syslog(LOG_WARNING,"query parameter: time_mark is missing!\n");
       //strcpy(qrpay_info.timemark,"1408001801550");
       //alipay_main(&payquery_result, &qrpay_info);
       alipay_main(&payquery_result, &qrpay_info, ALI_PRECREATE_QUERY);
       if(payquery_result.time_mark[0] == '\0')
           syslog(LOG_WARNING,"AT BEGINING,THE TIME_MARK is NULL!\n");
       strcpy(time_mark, payquery_result.time_mark);
       printf("query parameter: new time_mark is %s\n",time_mark);
       alarm(10);
       return;
    }
#endif
    //strcpy(qrpay_info.timemark,"123456789012345");
    //strcpy(qrpay_info.timemark,time_mark);
    printf("the query timer mark is %s\n",time_mark);
    printf("alarm!\n");
    //memset(payquery_result.qr_string,0,1024);
    //memset(payquery_result.time_mark,0,32);
    //alipay_main(&payquery_result, &qrpay_info);
    alipay_main(&payquery_result, &qrpay_info, ALI_PRECREATE_QUERY);
    if( payquery_result.time_mark[0] != '\0') 
       strcpy(time_mark, payquery_result.time_mark);
    else
       syslog(LOG_WARNING,"NO time_mark return from server!\n");
    if(payquery_result.qr_string[0]){
    struct sockaddr_un address;

    socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        printf("socket() failed\n");
        alarm(10);
        return ;
    }
    /* 从一个干净的地址结构开始 */ 
    memset(&address, 0, sizeof(struct sockaddr_un));
    address.sun_family = AF_UNIX;
    snprintf(address.sun_path, 20/*UNIX_PATH_MAX*/, "/tmp/demo_socket");

    if(connect(socket_fd, 
            (struct sockaddr *) &address, 
            sizeof(struct sockaddr_un)) != 0)
    {
        printf("connect() failed\n");
        alarm(10);
        return ;
    }
    
    nbytes = strlen(payquery_result.qr_string);
    write(socket_fd, payquery_result.qr_string, nbytes);
    close(socket_fd);
    }
    if(strlen(payquery_result.qr_string)&&strstr(payquery_result.qr_string, "TRADE_SUCCESS")){
    printf("the online qrcode payment successful\n");
    }
    else{   
    printf("the online qrcode payment failed\n");
#if 0
    int pos_fd = get_posfd();
    write(pos_fd,"\n",1);
    write(pos_fd, "TRADE_FAILURE\n",14);
    write(pos_fd,"\n",1);
    write(pos_fd,"\n",1);
    write(pos_fd,"\n",1);
#endif
    }
#ifdef ALIPAY_FIFO
    query_count--;
    if(query_count > 0)
        alarm(10);
    else {
        syslog(LOG_INFO,"The query_server alarm timer is stopped!\n");
        alarm(0);
    }
#else
   alarm(10);
#endif
   
}
 

   
int connection_handler(int connection_fd)
{
    int nbytes;
    char buffer[1024];
    //payquery_list recv_info;
    //int i;

    nbytes = read(connection_fd, buffer, 256);
    //buffer[nbytes] = 0;

    //write(connection_fd, buffer, sizeof(qrpay_info));
 
    close(connection_fd);
    return 0;
}



int main(void)
{
    FILE *fp;
    int i;
    char buffer[30] = {0};
    char pos_imsi[20] = {0};
#ifdef ALIPAY_FIFO
    int nbytes;
    const char *fifo_name = "/tmp/alipay_fifo";
    int pipe_fd = -1;
    int res = 0;
    int open_mode = O_RDONLY | O_NONBLOCK;
    query_count = 5;
#endif
    if (pos_imsi[0] == '\0'){
        /* get imsi from config.tx */
        fp = fopen("/usr/local/config.txt","r");
        if(fp == NULL)
        {
            syslog(LOG_ERR,"couldn't open config.txt\n");
            return;
        }
        if( fgets(buffer, 30, fp) == NULL )
        {
            syslog(LOG_ERR,"Error reading config\n");
            fclose(fp);
            return ;
        }
        for (i=0; i<30; i++) {
            if(buffer[i] == '\n') {
                buffer[i] = '\0';
                break;
            }
        }
        fclose(fp);
        /* copy after IMSI: */
        strcpy(pos_imsi,&buffer[5]);
        printf("the pos imsi buffer string is %s\n",pos_imsi);
    }
    strcpy(qrpay_info.imsi,pos_imsi);
    /* timer to get alipay payment response -- sample code */ 
    signal(SIGALRM, payment_alarm_handler);
    alarm(10);

#ifdef ALIPAY_FIFO
    if(access(fifo_name, F_OK) == -1)  
    {  
        //管道文件不存在  
        //创建命名管道  
        res = mkfifo(fifo_name, 0777);  
        if(res != 0)  
        {  
            syslog(LOG_ERR, "QUERY:Could not create fifo %s\n", fifo_name);  
            return 1;  
        }  
    } 
    pipe_fd = open(fifo_name, open_mode);
    if (pipe_fd == -1) {
        syslog(LOG_ERR,"Couldn't Open /tmp/ALIPAY_FIFO!\n");
        return 1;
    }
#endif
    while(1)
	{
		//sleep(10);
#ifdef ALIPAY_FIFO
                memset(buffer, 0, 30);
                nbytes = read(pipe_fd, buffer, 30);
                if(nbytes > 0 || strncmp(buffer,"START",5) == 0) {
                    syslog(LOG_INFO,"Get START Trigger From Main Server!\n"); 
                    query_count = 10;
                    alarm(10);
                }
#else 
                pause();
#endif //ALIPAY_FIFO
	}
#ifdef ALIPAY_FIFO
    close(pipe_fd);
#endif
    unlink("./demo_socket");
    return 0;
}
