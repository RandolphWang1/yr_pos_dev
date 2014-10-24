#include "Main.h"
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>

#define TMP_DESC_PATH "/tmp/desc_8888.txt"
#define TMP_MD5_FILE "/tmp/md5_8888.txt"
#define PKG_DEST_PATH "/usr/local/tmp.tar.gz"
#define DOWNLOAD_DESC_SCRIPT "/usr/local/D620D/download_desc.txt"
#define DOWNLOAD_PKG_SCRIPT "/usr/local/D620D/download_update.txt"
#define DEL_TMP_SCRIPT "/usr/local/D620D/removeTmpFile.txt"

/*This info is saved in the update.txt of sever*/
typedef struct update_zip_info{
	char *ver;
	char *filename;
	char *md5;
}update_zip_info_t;


#define BUF_LEN 100
char *buf=NULL;


extern char *get_yrjt_ver(void);

static void inline safe_free_mem(void **p)
{
    if(*p){
        free(*p);
        *p = NULL;
    }
}
static inline void stop_to_show_notification(void)
{
    WaitLimitKey("\x12\x0F", 2, 0);
	return;
}

void showVersion(void)
{
    char *ver = get_yrjt_ver();
	Clear();
	TextOut(0, 3, ALIGN_CENTER, ver);
    stop_to_show_notification();
	return;
}

void upload_debug_log(void)
{

}
char* get_update_ver(update_zip_info_t *info)
{
	return info->ver;
}

int exec_cmds(char *path)
{
    FILE *fp;
    int line=0,ret;
    syslog(LOG_INFO,"exec_cmds file=%s",path);

    fp = fopen(path,"r");
    if(fp == 0){
        syslog(LOG_ERR,"open %s fail",path);
        return -1;
    }   

    memset(buf,0,BUF_LEN);
    while(fgets(buf,BUF_LEN, fp) != NULL){
        line ++;

        //Ignore commands
        if(buf[0] == '#')
            continue;

        //too short. not valid command line
        if(strlen(buf) < 2)
            continue;
        
        ret = system(buf);
        if(ret != 0){
            syslog(LOG_ERR,"cmd FAIL cmd=%s",buf);
            break;
        }else{
            syslog(LOG_INFO,"cmd OK cmd=%s",buf);
        }

        memset(buf,0,BUF_LEN);
    }
    fclose(fp); 
    syslog(LOG_INFO,"exec_cmds end.");

    return ret;
}


int debug_download_process(void)
{
#if 0
        syslog(LOG_INFO,info.ver);  
        syslog(LOG_INFO,info.filename);
        syslog(LOG_INFO,info.md5);
        syslog(LOG_INFO,get_yrjt_ver());
#endif
	return 0;
}

int download_desc_file(char *buf)
{
    int ret;
    ret = setenv("TMP_DESC_PATH",TMP_DESC_PATH,1);
        if(ret != 0){
           syslog(LOG_INFO,"setenv fail.err=%s",strerror(errno));
           }
    syslog(LOG_INFO,"TMP_DESC_PATH=%s",getenv("TMP_DESC_PATH"));
    ret = exec_cmds(DOWNLOAD_DESC_SCRIPT);
    return ret;
}

int parse_desc_file(char *buf,update_zip_info_t *info)
{
    FILE *fp;
    int line = 0;
    syslog(LOG_INFO,"parse file begin %s",TMP_DESC_PATH);

    fp = fopen(TMP_DESC_PATH,"r");
    if(fp == 0){
        syslog(LOG_ERR,"open %s fail",TMP_DESC_PATH);
        return -1;
    }   
    /*
    The update.txt file templete. Don't change it.

    version:master_2014-10-21_14:13
    md5sum:281cf44d85e61f592686d7ac84398961
    filename:D620D.tar.gz
    */
    
    while(fgets(buf,BUF_LEN, fp) != NULL){
        int i,line_len; 
        char *p;
        line_len=strlen(buf);
        syslog(LOG_INFO,"line=%d len=%d str=%s", line++,line_len,buf);
        for(i=0;i<line_len;i++)
            if(buf[i] == ':')break;
        buf[i] = '\0';
            
        p=&buf[i+1];
        
        if(strcmp("version",buf) == 0){
            int len = strlen(p);
            char *p_tmp=malloc(len);
            memcpy(p_tmp,p,len);
            *(p_tmp+len-1) = '\0';

            info->ver=p_tmp;        
        }


        if(strcmp("filename",buf) == 0){
            int len = strlen(p);
            char *p_tmp=malloc(len);
            memcpy(p_tmp,p,len);        
            *(p_tmp+len-1) = '\0'; 
            
            info->filename=p_tmp;
        }

        if(strcmp("md5sum",buf) == 0){
            int len = strlen(p);
            char *p_tmp = malloc(len);
            memcpy(p_tmp,p,len); 
            *(p_tmp+len-1) = '\0';      

            info->md5=p_tmp;
        }

    }
    fclose(fp); 

    syslog(LOG_INFO,"parse file end");
    return 0;
}


int prepare_update_process(update_zip_info_t *info)
{
    FILE *fp;
    setenv("SRV_PKG_NAME",info->filename,1);
    syslog(LOG_INFO,"echo $SRV_PKG_NAME=%s",getenv("SRV_PKG_NAME"));
    
    memset(buf,0,BUF_LEN);
    fp = fopen(TMP_MD5_FILE,"w");
    sprintf(buf,"%s  %s",info->md5,PKG_DEST_PATH);
    fwrite(buf,strlen(buf),1,fp);
    fclose(fp);
    
    setenv("PKG_DEST_PATH",PKG_DEST_PATH,1); 
    syslog(LOG_INFO,"echo $PKG_DEST_PATH=%s",getenv("PKG_DEST_PATH"));
	setenv("TMP_MD5_FILE",TMP_MD5_FILE,1);
    syslog(LOG_INFO,"echo $TMP_MD5_FILE=%s",getenv("TMP_MD5_FILE"));
    return 0;
}

int download_Update_Pkg(update_zip_info_t *info)
{
    return exec_cmds(DOWNLOAD_PKG_SCRIPT);
}


int removeTmpFile(void)
{
    return exec_cmds(DEL_TMP_SCRIPT);
}

void Update_YRJT_Image(void)
{
	int ret;
	struct update_zip_info info;

	syslog(LOG_INFO,"ener Update_YRJT_Image");
    
	//urgly...but no better way. initialize...	
	buf = (char*)malloc(BUF_LEN);
    memset(buf,0,BUF_LEN);
   
	info.ver = NULL;
	info.filename = NULL;
	info.md5 = NULL; 
	//download description file
	Clear();
	TextOut(0, 3, ALIGN_CENTER,"获取更新信息");
    ret = download_desc_file(buf);
    if(ret != 0){
        TextOut(0, 4, ALIGN_CENTER,"获取更新信息失败");
        TextOut(0, 5, ALIGN_CENTER,"请检查网络");
        stop_to_show_notification();
		goto out;
    }
    //parse description file
    ret = parse_desc_file(buf,&info);
	if(ret != 0){
        TextOut(0, 4, ALIGN_CENTER, "获取更新信息失败");
        TextOut(0, 5, ALIGN_CENTER, "请重新尝试");
        stop_to_show_notification();
		goto out;
    }


    //check the version
	if(strcmp(get_yrjt_ver(),get_update_ver(&info)) == 0){
		TextOut(0, 4, ALIGN_CENTER, "当前版本已是最新");	
		stop_to_show_notification();
		/*
		the current version is the newest, 
		do nothing, rm temp file and return
		*/
		goto out;
	}
	//prepare download update package
    ret = prepare_update_process(&info);
    //download update package
	TextOut(0, 4, ALIGN_CENTER, "正在更新...");
	ret = download_Update_Pkg(&info);
	if(ret != 0){
		syslog(LOG_ERR,"download file fail. ret=%d.",ret);
		goto out;
	}

	//reboot
	while(1)
	{
	Clear();
	TextOut(0, 3, ALIGN_CENTER, "升级已完成，请关机重启");
	//sleep(1);
	//stop_to_show_notification();
	}

out:
	removeTmpFile();
    safe_free_mem((void*)&buf);
    safe_free_mem((void*)&info.ver);
    safe_free_mem((void*)&info.filename);
    safe_free_mem((void*)&info.md5);

    syslog(LOG_INFO,"exit Update_YRJT_Image");
	return;
}



