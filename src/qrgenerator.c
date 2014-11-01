#include "aliqr.h"
#include "qrgenerator.h"
#include <stdio.h>
#include <string.h>
#include "Main.h"

char qrQueryResult[16] = {0};
struct payInfo qrpay_info;
unsigned long long query_number = 0;
unsigned long long query_number_idx = 1;
unsigned long long old_query_number = 1;
char pos_imsi[20];

void getIMSIconfig();
char szQrcodeString[QRRESULT] = {0};

int viewsingle(int temp);
int createrefund(char* serial_number, char* refund_amount );

int generator_qrcode_to_bmp(int out, char* price);

int preImsi(int precreate_type);
int qTimemark(char* time_mark);
int qMaxtime(int max_time);
char* subject = "Alipay";
#if 0
int main(int argc, char** argv)
{
    int precreate_type = 1;//ALI_EXCHANGE  
    if(argc >=2)
        precreate_type = atoi(argv[1]);
    
    strcpy(qrpay_info.order_key,"11");
    switch (precreate_type)
    {
        case ALI_PREORDER:
            if(argc == 4) {
                query_number = atoll(argv[2]);
                generator_qrcode_to_bmp(-1, argv[3]);
            }
            break;
        case ALI_EXCHANGE:
        case ALI_EXCHANGEORDER:
        case ALI_TEMPLATEMD5:
        case ALI_TEMPLATE:
        case ALI_LASTESTMD5:
        case ALI_LASTEST:
        case ALI_QUERY_24H: /* query the recent 24h */
            preImsi(precreate_type);
            break;
        case ALI_QUERY_TIMEMARK: /* query the payment status of order with timemask */
            //*len = sprintf(common,PREQUERYTIMEMASK);
            if(argc == 3) {
                qTimemark(argv[2]);
            }
            break;
        case ALI_QUERY_MAXTIME: /* query the payment status of order with timemask */
            if(argc == 3) {
                qMaxtime(atoi(argv[2]));
            }
            break;
        case ALI_VIEW_SINGLE: /* query the with serial no */
            if(argc == 3) {
                query_number = atoll(argv[2]);
                viewsingle(0);
            }
            break;
        case ALI_REFUND:
            if(argc == 4) {
                query_number = atoll(argv[2]);
                createrefund(argv[2], argv[3] );
            }
            break;
        default:
        //    *len = sprintf(common,PREIMSI);
            break;
    }

    return 0;
    
}
#endif

int generator_qrcode_to_bmp(int out, char* price)
{
    char* szSourceString = NULL;
    // code from d620d start
    int ret;
    int enc_mode;

    // code from d620d end


    T_DATETIME tTime;
    char ticket_number[13]={0};
    char client_number[21]={0};

    client_number[0] = '1';//to avoid 0 atoi bug
    getIMSIconfig();
    strcpy(qrpay_info.order_key,"11");
#if 1
    /* Time for D620D Pos */
    GetDateTime(&tTime);
    if(query_number == 0) { //if query_number != 0 then time will nto changed, bug
        sprintf(ticket_number,"%s%s%s%s%s00",tTime.year,tTime.month,tTime.day,tTime.hour,tTime.minute);
        sprintf(ticket_number,"%s%s%s%s%s00","14","10","10","10","10");
        /* use last 4-bit of IMSI */
        strncpy(client_number+1, &(qrpay_info.imsi[11]), 5);
        strcat(client_number, ticket_number);
        query_number = (unsigned long long)atoll(client_number);
        if(old_query_number == query_number/100 ) {
            query_number = query_number + query_number_idx;
            query_number_idx++;
        } else {
            query_number_idx = 1;
            old_query_number = query_number/100; 
        }
    }

#else
    qrpay_info.order_number = query_number;
#endif
    strcpy(qrpay_info.total_fee,price);
    //strcpy(qrpay_info.total_fee,"0.01");^M
    //strcpy(qrpay_info.order_subject,"ccc");
    memset(qrpay_info.order_subject,0, sizeof(qrpay_info.order_subject));
    strcpy(qrpay_info.order_subject,subject);
    //strcpy(qrpay_info.order_subject,"%E5%88%86%E8%B4%A6%E6%B5%8B%E8%AF%95-sky");
    strcpy(qrpay_info.order_time,"2014-08-0514:15:30");
    memset(szQrcodeString, 0,sizeof(szQrcodeString)); 
    /* print the qr code from alipay */
    alipay_main((struct qr_result*)szQrcodeString, &qrpay_info, ALI_PREORDER);
    szSourceString = szQrcodeString;
    if(szQrcodeString[0] != '\0') {
        /* print QR code on D620D */
        //ret = PrintQR(10, 1, 2, szSourceString, 5, 5);
        //ret = PrintQR(6, 1, 2, szSourceString, 5, 7);
        //  ret = PrintQR(6, 3, 2, szSourceString, 50, 7);
        printf("qrcode%s\n",szSourceString);
        if (0 > ret)
        {
            printf("the PrintQR return value is %d\n",ret);
        }
    } else {
        ret = 1;
    }
    return ret;
}

int preImsi(int precreate_type)
{

    getIMSIconfig();
    memset(szQrcodeString, 0,sizeof(szQrcodeString)); 
    /* print the qr code from alipay */
    alipay_main((struct qr_result*)szQrcodeString, &qrpay_info, precreate_type );

}
#if 1
int qTimemark(char* time_mark)
{

    getIMSIconfig();
    strcpy(qrpay_info.time_mark, time_mark);
    memset(szQrcodeString, 0,sizeof(szQrcodeString)); 
    /* print the qr code from alipay */
    alipay_main((struct qr_result*)szQrcodeString, &qrpay_info, ALI_QUERY_TIMEMARK);

}
int qMaxtime(int max_time)
{

    getIMSIconfig();
    qrpay_info.max_time = max_time;
    memset(szQrcodeString, 0,sizeof(szQrcodeString)); 
    /* print the qr code from alipay */
    alipay_main((struct qr_result*)szQrcodeString, &qrpay_info, ALI_QUERY_MAXTIME);

}
#endif
int createrefund(char* serial_number, char* refund_amount )
{

    getIMSIconfig();
    //qrpay_info.order_number = query_number;
    qrpay_info.order_number = atoll(serial_number);
    strcpy(qrpay_info.refund_amount, refund_amount);
    memset(szQrcodeString, 0,sizeof(szQrcodeString)); 
    /* print the qr code from alipay */
    alipay_main((struct qr_result*)szQrcodeString, &qrpay_info, ALI_REFUND);

}

int viewsingle(int temp)
{
    getIMSIconfig();
    qrpay_info.order_number = query_number;
    memset(szQrcodeString, 0,sizeof(szQrcodeString)); 
    /* print the qr code from alipay */
    alipay_main((struct qr_result*)szQrcodeString, &qrpay_info, ALI_VIEW_SINGLE);

}

#if 1
//user don't need to input imsi and year month date, but hour,minutes,and serial no is needed,
void getSNoPre(char* prefix_str)
{
    T_DATETIME tTime;
    char ticket_number[13]={0};
    char client_number[21]={0};
    getIMSIconfig();
    GetDateTime(&tTime);
    memset(ticket_number, 0, 13);
    memset(client_number, 0, 21);
    client_number[0] = '1'; //to avoid atoi bug
    sprintf(ticket_number,"%s%s%s\0",
            tTime.year, tTime.month, tTime.day);
    /* use last 4-bit of IMSI */
    strncpy(client_number+1, &(qrpay_info.imsi[11]), 5);
    strcat(client_number, ticket_number);
    memcpy(prefix_str, client_number,strlen(client_number));
    printf("ticket_number:%s, client_number:%s, prefix:%s\n",
            ticket_number, client_number, prefix_str);
}
#endif
void getIMSIconfig()
{
    FILE *fp;
    int i;
    char buffer[30];
#if 1
    strcpy(qrpay_info.imsi,"123456789012345");
    //strcpy(qrpay_info.imsi,"460024104033474");
#else
    if (pos_imsi[0] == '\0'){
        /* get imsi from config.tx */
        fp = fopen("/usr/local/config.txt","r");
        if(fp == NULL)
        {
            printf("couldn't open config.txt\n");
            return;
        }
        if( fgets(buffer, 30, fp) == NULL )
        {
            printf("Error reading config\n");
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
#endif
}
#if 0

int alipay_query_single(unsigned long long queryNo)
{
    int ret = 0;
    getIMSIconfig();
    strcpy(qrpay_info.order_key,"11");
    qrpay_info.order_number = queryNo;
    memset(szQrcodeString, 0,sizeof(szQrcodeString)); 
    alipay_main((struct qr_result*)szQrcodeString, &qrpay_info, ALI_PRECREATE_QUERY_SINGLE);
    if(strcmp("TRADE_SUCCESS", szQrcodeString) == 0)
        ret = 1;
    else
        ret = 0;
    return ret;
}

int alipay_query_24h(char* query_24h)
{
    int ret = 0;
    getIMSIconfig();
    strcpy(qrpay_info.order_key,"11");
    alipay_main((struct qr_result*)query_24h, &qrpay_info, ALI_PRECREATE_QUERY_24H);
    return ret;
}
#endif
