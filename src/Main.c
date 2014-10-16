/****************************************************************************
                            D620D测试程序
****************************************************************************/
#include "Main.h"

#include <stdarg.h>

BOOL iScanHandle;
#define ALIPAY_QUERY 1
#ifdef ALIPAY_QUERY
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include "aliqr.h"
int socket_fd;
struct sockaddr_un address;
#endif


int _strcmp(char *str1,char *str2)
{
        int len1,len2;
        int len;
        int i;

        len1=strlen(str1);
        len2=strlen(str2);

        //全部切换为大写
        for(i=0;i<len1;i++)
        {
                if(str1[i]>='a'&&str1[i]<='z')
                        str1[i]-='a'-'A';
        }
        for(i=0;i<len2;i++)
        {
                if(str2[i]>='a'&&str2[i]<='z')
                        str2[i]-='a'-'A';
        }

        len=len1<len2?len1:len2;

        for(i=0;i<len;i++)
        {
                if(str1[i]==str2[i])
                        continue;
                if(str1[i]>str2[i])
                        return 1;
                if(str1[i]<str2[i])
                        return -1;
        }

        return len1-len2;
}

int main()
{
	int     i;
	int ucKey;
	//int ucKeyT;
	char sKeyName[20];
	int nRet;
	int display_y;
	char    GprsFlag;
        char    szBuff[128];
        char    szTmp[128];
        int ret;
        int mobile_flag=0;
        int j = 0;
        int nRetAttach = 0;
	//int k = 10;

	//初始化硬件
    	if(InitPOS() != OK)  
		return 0;

	DebugOut("D620D_01功能测试程序\n");

	Clear();
	//启动状态栏
	//CreateStatusBar(WHITE);
	CreateStatusBar_YRJT(WHITE);
	OpenStatusBar();

FUNC:
#ifdef ALIPAY_QUERY
    socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        printf("socket() failed\n");
        return 1;
    }

    unlink("/tmp/demo_socket");

    /* start from a clean socket structure */
    memset(&address, 0, sizeof(struct sockaddr_un));

    address.sun_family = AF_UNIX;
    snprintf(address.sun_path, 20/*UNIX_PATH_MAX*/, "/tmp/demo_socket");

    if(bind(socket_fd,
         (struct sockaddr *) &address,
         sizeof(struct sockaddr_un)) != 0)
    {
        printf("bind() failed\n");
        return 1;
    }

    if(listen(socket_fd, 5) != 0)
    {
        printf("listen() failed\n");
        return 1;
    }
#endif

	ClearKbd();
	display_y = 10;
        while(1)
        {
                printf("$$$$Main inside while loop$$$\n");
                                SetCommParam();
        }
}




