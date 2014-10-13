
#include "Main.h"



#define IDENTIFY_TIME_OUT				500
#define IDENTIFY_TIME_OUT2				500


#define MINZU_COUNT			58
char *minzu_code[]={
"01,����",
"02,�ɹ���",
"03,����",
"04,����",
"05,ά�����",
"06,����",
"07,����",
"08,׳��",
"09,������",
"10,������",
"11,����",
"12,����",
"13,����",
"14,����",
"15,������",
"16,������",
"17,��������",
"18,����",
"19,����",
"20,������",
"21,����",
"22,���",
"23,��ɽ��",
"24,������",
"25,ˮ��",
"26,������",
"27,������",
"28,������",
"29,�¶�������",
"30,����",
"31,���Ӷ���",
"32,������",
"33,Ǽ��",
"34,������",
"35,������",
"36,ë����",
"37,������",
"38,������",
"39,������",
"40,������",
"41,��������",
"42,ŭ��",
"43,���α����",
"44,����˹��",
"45,���¿���",
"46,������",
"47,������",
"48,ԣ����",
"49,����",
"50,��������",
"51,������",
"52,���״���",
"53,������",
"54,�Ű���",
"55,�����",
"56,��ŵ��",
"97,����",
"98,���Ѫͳ",
};

/*
void read_line(char *buff, unsigned long line_num)
{
	char ch;
	int row = 0;
	char read_data[1024+100];
	int read_len = 0;
	int have_read = 0;
	int file_size = 0;
	int hFile;
	int read_max = 1024;
	int i;
	int flag = 0;
	int j = 0;

	hFile = open("unicode.dat", O_RDONLY);
	if(hFile < 0)
		return;

	file_size = lseek(hFile, 0, SEEK_END);
	lseek(hFile, 0, SEEK_SET);

	while(1)
	{
		//����Ҫ���ĳ���
		if(file_size-have_read > read_max)
			read_len = read_max;
		else
			read_len = file_size-have_read;
		memset(read_data, 0, sizeof(read_data));
		if(read(hFile, read_data, read_len) != read_len)
			goto END;
		//������һλ��0x0D�����Ŷ�1λ
		ch = read_data[read_len-1];
		while(ch == 0x0D && have_read+read_len < file_size)
		{
			if(read(hFile, &ch, 1) != 1)
				goto END;
			read_data[read_len] = ch;
			read_len ++;
		}

		for(i = 0; i < read_len-1; i ++)
		{
			//�ҵ�һ�����з�
			if(read_data[i] == 0x0D && read_data[i+1] == 0x0A)
			{
				row ++;
				//n-1�����з�
				//�ҵ���ʼλ��
				if(row == line_num-1)
				{
					i ++;
					flag = 1;
				}
				//n�����з�
				else if(row == line_num)
					goto END;
			}
			else if(flag == 1)
				buff[j++] = read_data[i];
		}

		have_read += read_len;
	}

END:
	close(hFile);
}
*/

void read_line(char *buff, int line_num)
{
	char ch;
	char temp[2] = "";
	int row;
	int hFile;

	hFile = open("unicode.dat", O_RDONLY);
	if(hFile < 0)
		return;

	temp[0] = 0x0D;
	row = 0;
	while(1)
	{
		if(read(hFile, &ch, 1) != 1)
			break;
		if(ch == 0x0D)
		{
			if(read(hFile, &ch, 1) != 1)
				break;
			if(ch == 0x0A)
			{
				if(row == line_num-1)
					break;
				else
				{
					strcpy(buff, "");
					row ++;
					continue;
				}
			}
			else
			{
				strcat(buff, temp);
				lseek(hFile, -1, SEEK_CUR);
				continue;
			}
		}
		else
		{
			temp[0] = ch;
			strcat(buff, temp);
			continue;
		}
	}

}

void Unicode2Asc(char *unicode, char *asc)
{
	unsigned long line_num;
	char ch;
	char buff[200];
	int pos;

	line_num = 0;
	ch = unicode[0];
	if(ch >= '0' && ch <= '9')
		line_num += 256*(ch-0x30);
	else if(ch >= 'A' && ch <= 'F')
		line_num += 256*(ch-55);
	else if(ch >= 'a' && ch <= 'f')
		line_num += 256*(ch-87);

	ch = unicode[1];
	if(ch >= '0' && ch <= '9')
		line_num += 16*(ch-0x30);
	else if(ch >= 'A' && ch <= 'F')
		line_num += 16*(ch-55);
	else if(ch >= 'a' && ch <= 'f')
		line_num += 16*(ch-87);

	ch = unicode[2];
	if(ch >= '0' && ch <= '9')
		line_num += ch-0x30+1;
	else if(ch >= 'A' && ch <= 'F')
		line_num += ch-55+1;
	else if(ch >= 'a' && ch <= 'f')
		line_num += ch-87+1;

	ch = unicode[3];
	if(ch >= '0' && ch <= '9')
		pos = 5+3*(ch-0x30);
	else if(ch >= 'A' && ch <= 'F')
		pos = 5+3*(ch-55);
	else if(ch >= 'a' && ch <= 'f')
		pos = 5+3*(ch-87);

	memset(buff, 0, sizeof(buff));
	read_line(buff, line_num);
	if(strlen(buff) >= pos+2)
		memcpy(asc, buff+pos, 2);
}

void ProcData(char *buff, int in_len, char *data, int *out_len)
{
	char temp[200];
	char temp2[200];
	char ch;
	int i;
	int k;

	k = 0;
	for(i = 0; i < in_len; i += 2)
	{
		if(buff[i] == 0x20 && buff[i+1] == 0x00)
			break;
		if(buff[i+1] == 0x00)
			data[k++] = buff[i];
		else
		{
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buff+i, 2);
			//��ż����
			ch = temp[0];
			temp[0] = temp[1];
			temp[1] = ch;

			memset(temp2, 0, sizeof(temp2));
			BcdToAsc(temp2, temp, 4, 0);

			//unicode to ASC
			memset(temp, 0, sizeof(temp));
			Unicode2Asc(temp2, temp);
			memcpy(data+k, temp, 2);
			k += 2;
		}
	}
}


int ReadSerialData(int handle, char *data, int len, LONG time_out)
{
	int temp_len;
	int read_len;
	char buff[1024];
	clock_t start, end;
	long interval;
	long lWaitTime;

    lWaitTime = time_out*10;
	start = clock();
	temp_len = 0;
	while(1)
	{
		end = clock();
		interval = (end-start)/CLK_TCK;
		if(interval >= lWaitTime)
			return temp_len;

		memset(buff, 0, sizeof(buff));
		read_len = SERIAL_Read(handle, buff, len - temp_len);
		if(read_len > 0)
		{
			memcpy(data+temp_len, buff, read_len);
			temp_len += read_len;
			if(temp_len > len)
				return temp_len;
			else if(temp_len == len)
				break;
		}
	}
	return temp_len;
}

void ClearSerial(int handle)
{
	char buff[1024];

	SERIAL_Read(handle, buff, 1000);
	Wait(200);
	SERIAL_Read(handle, buff, 1000);
}

int ReadCmd(int handle, char cmd, int need_len, char *data, LONG time_out)
{
	int temp_len;
	int read_len;
	UINT data_len;
	char buff[READ_MAX_LENGTH];
	clock_t start, end;
	long interval;
	long lWaitTime;
	int status;
	char *p;

	if(need_len <= 0)
		return -1;

    lWaitTime = time_out*10;
	start = clock();
	status = 0;
	temp_len = 0;
	ClearKbd();   
	while(1)
	{
		end = clock();
		interval = (end-start)/CLK_TCK;
		if(interval >= lWaitTime)
		{
			printf("time out...\n");
			return temp_len;
		}

		if(WaitKey(50) == KEY_CANCEL)
			return -1;

		//��ͷ
		if(status == 0)
		{
			memset(buff, 0, sizeof(buff));
			read_len = SERIAL_Read(handle, buff, 1);
			if(read_len == 1 && buff[0] == 0x86)
			{
				memcpy(data+temp_len, buff, read_len);
				temp_len += read_len;
				status = 1;
			}
		}
		//������
		else if(status == 1)
		{
			memset(buff, 0, sizeof(buff));
			read_len = ReadSerialData(handle, buff, 2, lWaitTime-interval);
			if(read_len <= 0)
				continue;
			else if(read_len == 2)
			{
				p = (char *)&data_len;
				p[0] = buff[1];
				p[1] = buff[0];
				//���Ȳ���
				if(need_len != data_len)
				{
					status = 0;
					memset(data, 0, temp_len);
					temp_len = 0;
					continue;
				}
				memcpy(data+temp_len, buff, read_len);
				temp_len += read_len;
				status = 2;
				if(data_len <= 0 || data_len > READ_MAX_LENGTH)
				{
					printf("data length error...\n");
					return -2;
				}
			}
			else
			{
				printf("read data error 1...\n");
				return -1;
			}
		}
		//��ʣ������
		else if(status == 2)
		{
			memset(buff, 0, sizeof(buff));
			read_len = ReadSerialData(handle, buff, data_len, lWaitTime-interval);
			if(read_len <= 0)
				continue;
			else if(read_len == data_len)
			{
				if(buff[0] != cmd)
				{
					status = 0;
					memset(data, 0, temp_len);
					temp_len = 0;
					continue;
				}
				memcpy(data+temp_len, buff, read_len);
				temp_len += read_len;
				status = 3;
				return temp_len;
			}
			else
			{
				printf("read data error 2...\n");
				return -1;
			}
		}
	}

	printf("other error...\n");
}

int read_name(int handle, char *name, int *out_len)
{
	int ret;
	int i;
	char cmd[200];
	int len;
	char buff[100];
	char temp[100];

	while(1)
	{
		len = 6;
		memset(cmd, 0, sizeof(cmd));
		memcpy(cmd, "\x86\x00\x03\x21\x24\x16", 6);
		printf("========================================\n");
		printf("send data:%d\n", len);
		for(i = 0; i < len; i ++)
			printf("%02x ", cmd[i]);
		printf("\n\n");
		SERIAL_Write(handle, cmd, len);

		Wait(200);

		memset(buff, 0, sizeof(buff));
		ret = ReadCmd(handle, '\x91', 33, buff, IDENTIFY_TIME_OUT);
		if(ret > 0)
		{
			printf("recv data:%d\n", ret);
			for(i = 0; i < ret; i ++)
				printf("%02x ", buff[i]);
			printf("\n\n");
		}
		else
			return -1;

		//�������
		memset(temp, 0, sizeof(temp));
		memcpy(temp, buff+4, 30);

		memset(buff, 0, sizeof(buff));
        ProcData(temp, 30, buff, &len);

		return 0;
	}

	return -1;
}

int read_sex(int handle, char *sex)
{
	int ret;
	int i;
	char cmd[200];
	int len;
	char buff[100];

	//ClearSerial(handle);

	while(1)
	{
		len = 6;
		memset(cmd, 0, sizeof(cmd));
		memcpy(cmd, "\x86\x00\x03\x22\x25\x16", 6);
		printf("========================================\n");
		printf("send data:%d\n", len);
		for(i = 0; i < len; i ++)
			printf("%02x ", cmd[i]);
		printf("\n\n");
		SERIAL_Write(handle, cmd, len);

		Wait(200);

		memset(buff, 0, sizeof(buff));
		ret = ReadCmd(handle, '\x92', 5, buff, IDENTIFY_TIME_OUT);
		if(ret > 0)
		{
			printf("recv data:%d\n", ret);
			for(i = 0; i < ret; i ++)
				printf("%02x ", buff[i]);
			printf("\n\n");
		}
		else
			return -1;

		//����Ա�
		memset(sex, 0, sizeof(sex));
		memcpy(sex, buff+4, 2);

		return 0;
	}

	return -1;
}

int read_birthday(int handle, char *date)
{
	int ret;
	int i;
	char cmd[200];
	int len;
	char buff[100];

	while(1)
	{
		len = 6;
		memset(cmd, 0, sizeof(cmd));
		memcpy(cmd, "\x86\x00\x03\x24\x27\x16", 6);
		printf("========================================\n");
		printf("send data:%d\n", len);
		for(i = 0; i < len; i ++)
			printf("%02x ", cmd[i]);
		printf("\n\n");
		SERIAL_Write(handle, cmd, len);

		Wait(200);

		memset(buff, 0, sizeof(buff));
		ret = ReadCmd(handle, '\x94', 19, buff, IDENTIFY_TIME_OUT);
		if(ret > 0)
		{
			printf("recv data:%d\n", ret);
			for(i = 0; i < ret; i ++)
				printf("%02x ", buff[i]);
			printf("\n\n");
		}
		else
			return -1;

		//����Ա�
		memset(date, 0, sizeof(date));
		memcpy(date, buff+4, 16);

		return 0;
	}

	return -1;
}

int read_ID(int handle, char *id)
{
	int ret;
	int i;
	char cmd[200];
	int len;
	char buff[100];

	while(1)
	{
		len = 6;
		memset(cmd, 0, sizeof(cmd));
		memcpy(cmd, "\x86\x00\x03\x26\x29\x16", 6);
		printf("========================================\n");
		printf("send data:%d\n", len);
		for(i = 0; i < len; i ++)
			printf("%02x ", cmd[i]);
		printf("\n\n");
		SERIAL_Write(handle, cmd, len);

		Wait(200);

		memset(buff, 0, sizeof(buff));
		ret = ReadCmd(handle, '\x96', 39, buff, IDENTIFY_TIME_OUT);
		if(ret > 0)
		{
			printf("recv data:%d\n", ret);
			for(i = 0; i < ret; i ++)
				printf("%02x ", buff[i]);
			printf("\n\n");
		}
		else
			return -1;

		//����Ա�
		memset(id, 0, sizeof(id));
		memcpy(id, buff+4, 36);

		return 0;
	}

	return -1;
}

int read_all(int handle, char *all_data, int *out_len)
{
	int ret;
	int i;
	char cmd[200];
	int len;
	char buff[1024];

	while(1)
	{
		len = 6;
		memset(cmd, 0, sizeof(cmd));
		memcpy(cmd, "\x86\x00\x03\x20\x23\x16", 6);
		//printf("========================================\n");
		//printf("send data:%d\n", len);
		//for(i = 0; i < len; i ++)
		//	printf("%02x ", cmd[i]);
		//printf("\n\n");
		SERIAL_Write(handle, cmd, len);

		memset(buff, 0, sizeof(buff));
		ret = ReadCmd(handle, '\x90', 259, buff, IDENTIFY_TIME_OUT);
		if(ret == 262)
		{
			printf("recv data:%d\n", ret);
			for(i = 0; i < ret; i ++)
				printf("%02x ", buff[i]);
			printf("\n\n");
			//�����������
			memset(all_data, 0, sizeof(all_data));
			memcpy(all_data, buff+4, 256);
			*out_len = ret;
			return 0;
		}
		else if(ret < 0)
			return ret;
	}

	return -1;
}

int read_photo(int handle, char *photo_data, int *out_len)
{
	int ret;
	int i;
	char cmd[200];
	int len;
	char buff[READ_MAX_LENGTH];

	while(1)
	{
		//�崮��
		//ClearSerial(handle);
		len = 6;
		memset(cmd, 0, sizeof(cmd));
		memcpy(cmd, "\x86\x00\x03\x30\x33\x16", 6);
		//printf("========================================\n");
		//printf("send data:%d\n", len);
		//for(i = 0; i < len; i ++)
		//	printf("%02x ", cmd[i]);
		//printf("\n\n");
		SERIAL_Write(handle, cmd, len);

		memset(buff, 0, sizeof(buff));
		ret = ReadCmd(handle, '\xA0', 1027, buff, IDENTIFY_TIME_OUT);
		if(ret == 1030)
		{
			printf("recv data:%d\n", ret);
			for(i = 0; i < ret; i ++)
				printf("%02x ", buff[i]);
			printf("\n\n");
			//���ͼ������
			memset(photo_data, 0, sizeof(photo_data));
			memcpy(photo_data, buff+4, 1024);
			*out_len = ret;
			return 0;
		}
	}

	return -1;
}

void clear_all(int handle)
{
	ClearSerial(handle);
	SERIAL_Write(handle, "\x86\x00\x03\x12\x15\x16", 6);
	Wait(200);
	ClearSerial(handle);
}

int init(int handle)
{
	int ret;
	int i;
	char cmd[200];
	int len;
	char buff[100];

	while(1)
	{
		len = 6;
		memset(cmd, 0, sizeof(cmd));
		memcpy(cmd, "\x86\x00\x03\x10\x13\x16", 6);
		printf("========================================\n");
		printf("send data:%d\n", len);
		for(i = 0; i < len; i ++)
			printf("%02x ", cmd[i]);
		printf("\n\n");
		SERIAL_Write(handle, cmd, len);

		Wait(200);

		memset(buff, 0, sizeof(buff));
		ret = ReadCmd(handle, '\x80', 19, buff, IDENTIFY_TIME_OUT2);
		if(ret > 0)
		{
			printf("recv data:%d\n", ret);
			for(i = 0; i < ret; i ++)
				printf("%02x ", buff[i]);
			printf("\n\n");
		}
		else
			return -1;

		return 0;
	}

	return -1;
}

int ReadIdentify(T_IDENTIFY_INFO *pInfo)
{
	char buff[READ_MAX_LENGTH];
	int photo_len;
	int handle;
	int len;
	char temp[200];
	char temp2[200];
	int i;
	int success;

	SwitchCom0_Pinpad();
	if((handle = SERIAL_Open("/dev/ttyS2", 115200)) < 0 )  
	{
		FailBeep();
		Clear();
		TextOut(0, 3, ALIGN_CENTER, "    �򿪴���ʧ��");
		WaitKey(2000);
		return -1;
	}

	init(handle);
	clear_all(handle);

	while(1)
	{
		Clear();
		TextOut(0, 0, ALIGN_CENTER, "  ���֤�Ķ�������  ");

		TextOut(0, 2, ALIGN_CENTER, "   ��ˢ���֤...");

		success = 0;

		memset(buff, 0, sizeof(buff));
		if(read_all(handle, buff, &len) == 0)
		{
			memset(pInfo, 0, sizeof(T_IDENTIFY_INFO));
		
			success = 1;
			Clear();
			TextOut(0, 3, ALIGN_CENTER, "    ���Ժ�...");
			TextOut(0, 4, ALIGN_CENTER, "    ���ڽ���...");

			//��������
			//����
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buff, 30);
			ProcData(temp, 30, pInfo->name, &len);

			//�Ա�
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buff+30, 1);
			if(temp[0] == '1')
				strcpy(pInfo->sex, "��");
			else
				strcpy(pInfo->sex, "Ů");

			//����
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buff+30+2, 4);
			memset(temp2, 0, sizeof(temp2));
			ProcData(temp, 4, temp2, &len);
			for(i = 0; i < MINZU_COUNT; i ++)
			{
				if(!memcmp(temp2, minzu_code[i], 2))
					memcpy(pInfo->minzu, minzu_code[i]+3, strlen(minzu_code[i])-3);
			}

			//��������
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buff+30+2+4, 16);
			memset(temp2, 0, sizeof(temp2));
			ProcData(temp, 16, temp2, &len);
			memcpy(pInfo->birthday, temp2, 4);
			memcpy(pInfo->birthday+4, "��", 2);
			memcpy(pInfo->birthday+6, temp2+4, 2);
			memcpy(pInfo->birthday+8, "��", 2);
			memcpy(pInfo->birthday+10, temp2+6, 2);
			memcpy(pInfo->birthday+12, "��", 2);

			//����
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buff+30+2+4+16, 70);
			ProcData(temp, 70, pInfo->address, &len);

			//���֤��
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buff+30+2+4+16+70, 36);
			ProcData(temp, 36, pInfo->id, &len);

			//ǩ������
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buff+30+2+4+16+70+36, 30);
			ProcData(temp, 30, pInfo->department, &len);


			//��Ч��������-��
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buff+30+2+4+16+70+36+30, 16);
			memset(temp2, 0, sizeof(temp2));
			ProcData(temp, 16, temp2, &len);
			memcpy(pInfo->date_start, temp2, 4);
			memcpy(pInfo->date_start+4, "��", 2);
			memcpy(pInfo->date_start+6, temp2+4, 2);
			memcpy(pInfo->date_start+8, "��", 2);
			memcpy(pInfo->date_start+10, temp2+6, 2);
			memcpy(pInfo->date_start+12, "��", 2);

			//��Ч��������-ֹ
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buff+30+2+4+16+70+36+30+16, 16);
			memset(temp2, 0, sizeof(temp2));
			ProcData(temp, 16, temp2, &len);
			memcpy(pInfo->date_end, temp2, 4);
			memcpy(pInfo->date_end+4, "��", 2);
			memcpy(pInfo->date_end+6, temp2+4, 2);
			memcpy(pInfo->date_end+8, "��", 2);
			memcpy(pInfo->date_end+10, temp2+6, 2);
			memcpy(pInfo->date_end+12, "��", 2);
		}
		else
			return -1;

		if(success == 1)
		{
			//��ͼ��
			if(read_photo(handle, pInfo->photo_data, &photo_len) == 0)
			{
				success = 2;

				memset(buff, 0, sizeof(buff));
				memcpy(buff, pInfo->photo_data, 80);
				memset(pInfo->photo_data, 0, sizeof(pInfo->photo_data));
				BcdToAsc(pInfo->photo_data, buff, 160, 0);
			}
		}
		
		Clear();

		if(success == 1 || success == 2)
		{
			Clear();
			memset(buff, 0, sizeof(buff));
			sprintf(buff, "����:%s", pInfo->name);
			TextOut(0, 0, ALIGN_LEFT, buff);

			sprintf(buff, "�Ա�: %s", pInfo->sex);
			TextOut(0, 1, ALIGN_LEFT, buff);

			memset(buff, 0, sizeof(buff));
			sprintf(buff, "����: %s", pInfo->minzu);
			TextOut(0, 2, ALIGN_LEFT, buff);

			TextOut(0, 3, ALIGN_LEFT, "��������:");
			TextOut(0, 4, ALIGN_LEFT, pInfo->birthday);

			TextOut(0, 5, ALIGN_LEFT, "����:");
			TextOut(0, 6, ALIGN_LEFT, pInfo->address);

			TextOut(0, 8, ALIGN_LEFT, "���֤��:");
			TextOut(0, 9, ALIGN_LEFT, pInfo->id);

			WaitKey(0);

			Clear();
			TextOut(0, 1, ALIGN_LEFT, "ǩ������:");
			TextOut(0, 2, ALIGN_LEFT, pInfo->department);

			TextOut(0, 4, ALIGN_LEFT, "��Ч��ʼ����:");
			TextOut(0, 5, ALIGN_LEFT, pInfo->date_start);

			TextOut(0, 6, ALIGN_LEFT, "��Ч��ֹ����:");
			TextOut(0, 7, ALIGN_LEFT, pInfo->date_end);

			WaitKey(0);
		}
		if(success == 2)
		{
			Clear();
			memset(buff, 0, sizeof(buff));
			sprintf(buff, "ͼ������ ��%d�ֽ�", photo_len-6);
			TextOut(0, 0, ALIGN_LEFT, buff);
			TextOut(0, 1, ALIGN_CENTER, "����ʾǰ80�ֽ�");
			for(i = 0; i < 5; i ++)
			{
				memset(buff, 0, sizeof(buff));
				memcpy(buff, pInfo->photo_data+32*i, 32);
				TextOut(0, 2+i, ALIGN_LEFT, buff);
			}

			WaitKey(0);
		}

		clear_all(handle);
	}

	return 0;
}



