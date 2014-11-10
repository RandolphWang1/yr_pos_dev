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

//char* subject = "Alipay";
char subject[128+1] = {0};
char* defaultsubject = "e-richpay";
int getsubject(char* name,char* buf);
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

int generator_qrcode_to_bmp(void* gout, char* price ,void* gin)
{
    char* szSourceString = NULL;
    // code from d620d start
    int ret;
    int enc_mode;
    struct qr_result* out = (struct qr_result*)gout; 
    struct payInfo* in = (struct payInfo*)gin; 
    // code from d620d end


    T_DATETIME tTime;
    char ticket_number[13] = {0};
    char client_number[21] = {0};
    char order_time[13] = {0};
    client_number[0] = '1';//to avoid 0 atoi bug
    getIMSIconfig();
    strcpy(qrpay_info.order_key,ORDERKEY);
#if 1
    /* Time for D620D Pos */
    GetDateTime(&tTime);
    //if(query_number == 0) { //if query_number != 0 then time will nto changed, bug
        sprintf(ticket_number,"%s%s%s%s%s00",tTime.year,tTime.month,tTime.day,tTime.hour,tTime.minute);
        //sprintf(ticket_number,"%s%s%s%s%s00","14","10","10","10","10");
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
    //}

    qrpay_info.order_number = query_number;
#endif
    strcpy(qrpay_info.total_fee,price);
    //strcpy(qrpay_info.total_fee,"0.01");^M
    //strcpy(qrpay_info.order_subject,"ccc");
    memset(qrpay_info.order_subject,0, sizeof(qrpay_info.order_subject));
    if(in && strlen(in->order_subject) > 0)
        strcpy(qrpay_info.order_subject,in->order_subject);
    else {
        int subjectlen = 0;
        subjectlen = getsubject("/usr/local/D620D/subject.txt",subject);
        if(subjectlen > 0 ) {
            printf("subject:%d:%s",subjectlen,subject);
            strncpy(qrpay_info.order_subject,subject,subjectlen);
        }else{
            strcpy(qrpay_info.order_subject,defaultsubject);
        }
    }
    //strcpy(qrpay_info.order_subject,"%E5%88%86%E8%B4%A6%E6%B5%8B%E8%AF%95-sky");

    sprintf(order_time, "%s%s%s%s%s%s%s", 
            tTime.century, tTime.year, tTime.month, tTime.day,
            tTime.hour, tTime.minute, tTime.second);
    strcpy(qrpay_info.order_time,order_time);

    memset(szQrcodeString, 0,sizeof(szQrcodeString)); 
    /* print the qr code from alipay */
    alipay_main(out, &qrpay_info, ALI_PREORDER);
    szSourceString = szQrcodeString;
    if(strstr(out->qrcode, "https://qr.alipay.com/")) {
        /* print QR code on D620D */
        //ret = PrintQR(10, 1, 2, szSourceString, 5, 5);
        //ret = PrintQR(6, 1, 2, szSourceString, 5, 7);
        ret = PrintQR(6, 3, 2, out->qrcode, 50, 7);
        printf("qrcode:%s\n",out->qrcode);
        if (0 > ret)
        {
            printf("the PrintQR return value is %d\n",ret);
        }
    } else {
        ret = 1;
    }
    return ret;
}

int preImsi(void* gout, int precreate_type)
{

    struct qr_result* out = (struct qr_result*)gout; 
    getIMSIconfig();
    strcpy(qrpay_info.order_key,ORDERKEY);
    alipay_main(out, &qrpay_info, precreate_type );

}
#if 1
int qTimemark(void* gout, char* time_mark)
{

    struct qr_result* out = (struct qr_result*)gout; 
    getIMSIconfig();
    strcpy(qrpay_info.time_mark, time_mark);
    memset(szQrcodeString, 0,sizeof(szQrcodeString)); 
    /* print the qr code from alipay */
    alipay_main((struct qr_result*)szQrcodeString, &qrpay_info, ALI_QUERY_TIMEMARK);

}
int qMaxtime(void* gout, int max_time)
{

    struct qr_result* out = (struct qr_result*)gout; 
    getIMSIconfig();
    qrpay_info.max_time = max_time;
    memset(szQrcodeString, 0,sizeof(szQrcodeString)); 
    /* print the qr code from alipay */
    alipay_main((struct qr_result*)szQrcodeString, &qrpay_info, ALI_QUERY_MAXTIME);

}
#endif
int createrefund(void* gout, char* serial_number, char* refund_amount )
{

    struct qr_result* out = (struct qr_result*)gout; 
    getIMSIconfig();
    strcpy(qrpay_info.order_key,ORDERKEY);
    //qrpay_info.order_number = query_number;
    qrpay_info.order_number = atoll(serial_number);
    //strcpy(qrpay_info.refund_amount, refund_amount);
    //memset(szQrcodeString, 0,sizeof(szQrcodeString)); 
    /* print the qr code from alipay */
    alipay_main(out, &qrpay_info, ALI_REFUND);

}

int viewsingle(void* gout,char* serial_number)
{
    struct qr_result* out = (struct qr_result*)gout; 
    getIMSIconfig();
    qrpay_info.order_number = atoll(serial_number);
    /* print the qr code from alipay */
    alipay_main(out, &qrpay_info, ALI_VIEW_SINGLE);
    return 1;
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

int getsubject(char* name,char* buf)
{
    FILE* fp = NULL;
    int len = 0;
    fp = fopen(name,"r");
    if(fp == NULL) {
        printf("couldn't open config.txt\n");
        return 0; 
    }
    
    fread(buf, sizeof(qrpay_info.order_subject),1,fp);
    printf("%d,%s\n",strlen(buf),buf);
    fclose(fp);
    return strlen(buf)-1;
}

void getIMSIconfig()
{
    FILE *fp;
    int i;
    char buffer[30];
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
