#include "Main.h"
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>

#define TMP_MD5_FILE "/tmp/md5_8888.txt"
#define PKG_DEST_PATH "/usr/local/tmp.tar.gz"
#define PKG_MD5_PATH "/tmp/pkg_md5.txt"
#define DOWNLOAD_PKG_SCRIPT "/usr/local/D620D/download_update.txt"
#define DOWNLOAD_PKG_DESC "/usr/local/D620D/download_desc.txt"
#define DEL_TMP_SCRIPT "/usr/local/D620D/removeTmpFile.txt"
#define UPLOAD_LOG_SCRIPT "/usr/local/D620D/upload_log.txt"

char *local_md5=NULL;
char package_md5[33] = {0};
#define MD5_FILE_PATH "/usr/local/D620D/local_md5.txt"

/*This info is saved in the update.txt of sever*/
typedef struct update_zip_info{
	char *ver;
	char *filename;
	char *md5;
}update_zip_info_t;


#define BUF_LEN 120
char *buf=NULL;

extern char *getIMSIconfig();
extern char *get_yrjt_ver(void);

void inline safe_free_mem(void **p)
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

int update_md5_to_config(update_zip_info_t *info)
{
        FILE *fp;
        fp = fopen(PKG_MD5_PATH,"r");
        if(fp == 0){
            syslog(LOG_ERR,"open %s fail",PKG_MD5_PATH);
            return NULL;
        }
        
        while(fgets(buf,BUF_LEN, fp) != NULL){
            int i = 0;
            char *p = NULL;

            p = strstr(buf,"<m>");
            if(p){
                syslog(LOG_INFO,"find the package md5 string of %s\n",getenv("IMSI"));
                strncpy(package_md5,p+3,32);
                syslog(LOG_INFO,"The md5 string is:%s\n",package_md5);
            }

            info->md5 = package_md5;
                 
        } 
        fclose(fp);
    
        return 0;
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

int get_desc(char *buf)
{
    return 0;
}

int parse_desc(char *buf,update_zip_info_t *info)
{
    //info->md5 = "628acc3f29cc4accecbb47642418333c";
    int ret;
    syslog(LOG_INFO,"IMSI=%s",getIMSIconfig());
    setenv("IMSI",getIMSIconfig(),1);
    syslog(LOG_INFO,"echo $IMSI=%s",getenv("IMSI"));
    setenv("PKG_MD5_PATH",PKG_MD5_PATH,1); 
    syslog(LOG_INFO,"echo $PKG_MD5_PATH=%s",getenv("PKG_MD5_PATH"));
    ret = exec_cmds(DOWNLOAD_PKG_DESC);
    if(ret!= 0)
        return ret;
    ret = update_md5_to_config(info);
    info->ver = "master";
    printf("parse_desc:%s:%s\n", info->ver, info->md5);
    return ret;
}


int prepare_update_process(update_zip_info_t *info)
{
    setenv("NEW_MD5",info->md5,1);
    syslog(LOG_INFO,"echo $NEW_MD5=%s",getenv("NEW_MD5"));
    
    setenv("PKG_DEST_PATH",PKG_DEST_PATH,1); 
    syslog(LOG_INFO,"echo $PKG_DEST_PATH=%s",getenv("PKG_DEST_PATH"));

    setenv("TMP_MD5_FILE",TMP_MD5_FILE,1);
    syslog(LOG_INFO,"echo $TMP_MD5_FILE=%s",getenv("TMP_MD5_FILE"));
    return 0;
}

int download_Update_Pkg(update_zip_info_t *info)
{
    int ret = exec_cmds(DOWNLOAD_PKG_SCRIPT);
    //ret = update_md5_to_config(info);
    return ret;
}


int removeTmpFile(void)
{
    return exec_cmds(DEL_TMP_SCRIPT);
}


char *get_local_md5(void)
{
    if(local_md5 ==NULL){
        FILE *fp;
        fp = fopen(MD5_FILE_PATH,"r");
        if(fp == 0){
            syslog(LOG_ERR,"open %s fail",MD5_FILE_PATH);
            return NULL;
        }
        
        while(fgets(buf,BUF_LEN, fp) != NULL){
            int i = 0;
            char *p;
            if(buf[0] == '#')
                continue;

            if(strncmp("md5:",buf,4) == 0)
                continue;

            p = &buf[4];
            for(i=0;i<32;i++)
                {
                if(((*p)>='0' && (*p<='9')) || \
                    ((*p>='a') && (*p <= 'f')))
                    {
                    p++;
                    continue;
                    }
                else
                    break;
                }
            
            if(i == 32){
                //md5 is ok,save it and jump out the loop
                //md5 is 128bit, 32 char + 1 end
                local_md5 = malloc(33);
                memset(local_md5,0,33);
                memcpy(local_md5,&buf[4],32);
                syslog(LOG_INFO,"detect md5=%s",local_md5);
                break;
            }
            //if md5 is not right, go on to look for...        
        }
        
        fclose(fp);
    }
    
    return local_md5;
}

BOOL is_need_update(update_zip_info_t *info)
{
    if((get_local_md5()==NULL) ||(get_yrjt_ver()==NULL) \
        || info->ver ==NULL || info->md5 == NULL){
        return TRUE;
    }
    
    if((strcmp(get_yrjt_ver(),info->ver) == 0) && \
        (strcmp(get_local_md5(),info->md5) == 0))
        return FALSE;
    else
        return TRUE;
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
	info.filename = NULL;// not need
	info.md5 = NULL; 
	//download description file
	Clear();
	TextOut(0, 3, ALIGN_CENTER,"获取更新信息");
    
    ret = get_desc(buf);
    if(ret != 0){
        TextOut(0, 4, ALIGN_CENTER,"获取更新信息失败");
        TextOut(0, 5, ALIGN_CENTER,"请检查网络");
        stop_to_show_notification();
		goto out;
    }
    //parse description file
    ret = parse_desc(buf,&info);
	if(ret != 0){
        TextOut(0, 4, ALIGN_CENTER, "获取更新信息失败");
        TextOut(0, 5, ALIGN_CENTER, "请重新尝试");
        stop_to_show_notification();
		goto out;
    }


    printf("before is_need_update\n");
    //check the version
    if(FALSE == is_need_update(&info)){
		TextOut(0, 4, ALIGN_CENTER, "当前版本已是最新");	
		stop_to_show_notification();
		/*
		the current version is the newest, 
		do nothing, rm temp file and return
		*/
		goto out;
	}
    printf("after is_need_update\n");
	//prepare download update package
	TextOut(0, 4, ALIGN_CENTER, "准备更新版本");
    ret = prepare_update_process(&info);
    //download update package
    printf("after prepare_update_process\n");
	TextOut(0, 5, ALIGN_CENTER, "正在更新...");
	ret = download_Update_Pkg(&info);
    printf("after download_Update_Pkg\n");
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
    printf("error out\n");
	removeTmpFile();
    safe_free_mem((void*)&buf);
    safe_free_mem((void*)&info.ver);
    safe_free_mem((void*)&info.filename);
    safe_free_mem((void*)&info.md5);

    syslog(LOG_INFO,"exit Update_YRJT_Image");
	return;
}

//upload log function
int prepar_upload(void)
{
    //generate the tgz file name, which will be upload later.
    //tgz_filename = imsi + time.gz
#if 0
    char buf[100];
    T_DATETIME tTime;
    sprintf(buf,"%s_")
    GetDateTime(T_DATETIME * ptTime)(&tTime);
    sprintf(pos_date,"%s%s-%s-%s",tTime.century,tTime.year,tTime.month,tTime.day);
    sprintf(pos_time,"%s:%s:%s",tTime.hour,tTime.minute,tTime.second);
#endif
    char *tgz_filename=getIMSIconfig();//FIXME, add time later.
    setenv("LOG_NAME",tgz_filename,1);
    syslog(LOG_INFO,"echo $LOG_NAME=%s",getenv("LOG_NAME"));
    return 0;
}

int upload_log(void)
{
    return exec_cmds(UPLOAD_LOG_SCRIPT);
}

void upload_debug_log(void)
{
    int ret;
	TextOut(0, 3, ALIGN_CENTER, "准备上传");
    ret = prepar_upload();
    if(ret != 0){
        syslog(LOG_ERR,"prepare upload debug log fail.");
	}
    ret = upload_log();
	if(ret != 0){
		TextOut(0, 4, ALIGN_CENTER, "上传失败");
        syslog(LOG_ERR,"upload debug log fail.");
	}else{
		TextOut(0, 4, ALIGN_CENTER, "上传成功");
	}
}



