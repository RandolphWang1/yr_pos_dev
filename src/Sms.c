//#include  "Sms.h"
//#include  "unicode.h"
//#include  "stdio.h"
//#include  "string.h"
//#include  "stdlib.h"
// �ɴ�ӡ�ַ���ת��Ϊ�ֽ�����
// �磺"C8329BFD0E01" --> {0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01}
// ����: pSrc - Դ�ַ���ָ��
//       nSrcLength - Դ�ַ�������
// ���: pDst - Ŀ������ָ��
// ����: Ŀ�����ݳ���
#include "Main.h"

extern int AT_GetOK();
extern int ClearGprsBuffer();

int gsmString2Bytes(const char* pSrc, unsigned char* pDst, int nSrcLength)
{
	int i;
	
	for (i = 0; i < nSrcLength; i += 2)
	{
		// �����4λ
		if ((*pSrc >= '0') && (*pSrc <= '9'))
		{
			*pDst = (*pSrc - '0') << 4;
		}
		else
		{
			*pDst = (*pSrc - 'A' + 10) << 4;
		}

		pSrc++;

		// �����4λ
		if ((*pSrc>='0') && (*pSrc<='9'))
		{
			*pDst |= *pSrc - '0';
		}
		else
		{
			*pDst |= *pSrc - 'A' + 10;
		}

		pSrc++;
		pDst++;
	}

	// ����Ŀ�����ݳ���
	return (nSrcLength / 2);
}

// �ֽ�����ת��Ϊ�ɴ�ӡ�ַ���
// �磺{0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01} --> "C8329BFD0E01" 
// ����: pSrc - Դ����ָ��
//       nSrcLength - Դ���ݳ���
// ���: pDst - Ŀ���ַ���ָ��
// ����: Ŀ���ַ�������
int gsmBytes2String(const unsigned char* pSrc, char* pDst, int nSrcLength)
{
	const char tab[]="0123456789ABCDEF";	// 0x0-0xf���ַ����ұ�
	int i;
	
	for (i =0; i < nSrcLength; i++)
	{
		*pDst++ = tab[*pSrc >> 4];		// �����4λ
		*pDst++ = tab[*pSrc & 0x0f];	// �����4λ
		pSrc++;
	}

	// ����ַ����Ӹ�������
	*pDst = '\0';

	// ����Ŀ���ַ�������
	return (nSrcLength * 2);
}

// 7bit����
// ����: pSrc - Դ�ַ���ָ��
//       nSrcLength - Դ�ַ�������
// ���: pDst - Ŀ����봮ָ��
// ����: Ŀ����봮����
int gsmEncode7bit(const char* pSrc, unsigned char* pDst, int nSrcLength)
{
	int nSrc;		// Դ�ַ����ļ���ֵ
	int nDst;		// Ŀ����봮�ļ���ֵ
	int nChar;		// ��ǰ���ڴ���������ַ��ֽڵ���ţ���Χ��0-7
	unsigned char nLeft;	// ��һ�ֽڲ��������

	// ����ֵ��ʼ��
	nSrc = 0;
	nDst = 0;

	// ��Դ��ÿ8���ֽڷ�Ϊһ�飬ѹ����7���ֽ�
	// ѭ���ô�����̣�ֱ��Դ����������
	// ������鲻��8�ֽڣ�Ҳ����ȷ����
	while (nSrc < nSrcLength)
	{
		// ȡԴ�ַ����ļ���ֵ�����3λ
		nChar = nSrc & 7;

		// ����Դ����ÿ���ֽ�
		if(nChar == 0)
		{
			// ���ڵ�һ���ֽڣ�ֻ�Ǳ�����������������һ���ֽ�ʱʹ��
			nLeft = *pSrc;
		}
		else
		{
			// ���������ֽڣ������ұ߲��������������ӣ��õ�һ��Ŀ������ֽ�
			*pDst = (*pSrc << (8-nChar)) | nLeft;

			// �����ֽ�ʣ�µ���߲��֣���Ϊ�������ݱ�������
			nLeft = *pSrc >> nChar;

			// �޸�Ŀ�괮��ָ��ͼ���ֵ
			pDst++;
			nDst++;
		}

		// �޸�Դ����ָ��ͼ���ֵ
		pSrc++;
		nSrc++;
	}

	// ����Ŀ�괮����
	return nDst;
}

// 7bit����
// ����: pSrc - Դ���봮ָ��
//       nSrcLength - Դ���봮����
// ���: pDst - Ŀ���ַ���ָ��
// ����: Ŀ���ַ�������
int gsmDecode7bit(const unsigned char* pSrc, char* pDst, int nSrcLength)
{
	int nSrc;		// Դ�ַ����ļ���ֵ
	int nDst;		// Ŀ����봮�ļ���ֵ
	int nByte;		// ��ǰ���ڴ���������ֽڵ���ţ���Χ��0-6
	unsigned char nLeft;	// ��һ�ֽڲ��������

	// ����ֵ��ʼ��
	nSrc = 0;
	nDst = 0;
	
	// �����ֽ���źͲ������ݳ�ʼ��
	nByte = 0;
	nLeft = 0;

	// ��Դ����ÿ7���ֽڷ�Ϊһ�飬��ѹ����8���ֽ�
	// ѭ���ô�����̣�ֱ��Դ���ݱ�������
	// ������鲻��7�ֽڣ�Ҳ����ȷ����
	while(nSrc<nSrcLength)
	{
		// ��Դ�ֽ��ұ߲��������������ӣ�ȥ�����λ���õ�һ��Ŀ������ֽ�
		*pDst = ((*pSrc << nByte) | nLeft) & 0x7f;

		// �����ֽ�ʣ�µ���߲��֣���Ϊ�������ݱ�������
		nLeft = *pSrc >> (7-nByte);

		// �޸�Ŀ�괮��ָ��ͼ���ֵ
		pDst++;
		nDst++;

		// �޸��ֽڼ���ֵ
		nByte++;

		// ����һ������һ���ֽ�
		if(nByte == 7)
		{
			// ����õ�һ��Ŀ������ֽ�
			*pDst = nLeft;

			// �޸�Ŀ�괮��ָ��ͼ���ֵ
			pDst++;
			nDst++;

			// �����ֽ���źͲ������ݳ�ʼ��
			nByte = 0;
			nLeft = 0;
		}

		// �޸�Դ����ָ��ͼ���ֵ
		pSrc++;
		nSrc++;
	}

	// ����ַ����Ӹ�������
	*pDst = '\0';

	// ����Ŀ�괮����
	return nDst;
}

// UCS2����
// ����: pSrc - Դ�ַ���ָ��
//       nSrcLength - Դ�ַ�������
// ���: pDst - Ŀ����봮ָ��
// ����: Ŀ����봮����
int gsmEncodeUcs2(const char* pSrc, unsigned char* pDst, int nSrcLength)
{
	int nDstLength;		// UNICODE���ַ���Ŀ
	unsigned short wchar[128];	// UNICODE��������
	int i;
	
	// �ַ���-->UNICODE��
	nDstLength = MultiByteToWideChar(pSrc, nSrcLength, wchar);
	
	// �ߵ��ֽڶԵ������
	for(i=0; i<nDstLength; i++)
	{
		*pDst++ = wchar[i] >> 8;		// �������λ�ֽ�
		*pDst++ = wchar[i] & 0xFF;		// �������λ�ֽ�
	}
	
	// ����Ŀ����봮����
	return nDstLength * 2;
}

// UCS2����
// ����: pSrc - Դ���봮ָ��
//       nSrcLength -  Դ���봮����
// ���: pDst -  Ŀ���ַ���ָ��
// ����: Ŀ���ַ�������
int gsmDecodeUcs2(unsigned char* pSrc, char* pDst, int nSrcLength)
{
	int nDstLength;		// UNICODE���ַ���Ŀ
	
	// UNICODE��-->�ַ���
	nDstLength = WideCharToMultiByte(pSrc, nSrcLength, pDst);

	// ����ַ����Ӹ�������
	pDst[nDstLength] = '\0';

	// ����Ŀ���ַ�������
	return nDstLength;
}

// ����˳����ַ���ת��Ϊ�����ߵ����ַ�����������Ϊ��������'F'�ճ�ż��
// �磺"8613851872468" --> "683158812764F8"
// ����: pSrc - Դ�ַ���ָ��
//       nSrcLength - Դ�ַ�������
// ���: pDst - Ŀ���ַ���ָ��
// ����: Ŀ���ַ�������
int gsmInvertNumbers(const char* pSrc, char* pDst, int nSrcLength)
{
	int nDstLength;		// Ŀ���ַ�������
	char ch;			// ���ڱ���һ���ַ�
	int i;
	// ���ƴ�����
	nDstLength = nSrcLength;

	// �����ߵ�
	for(i=0; i<nSrcLength;i+=2)
	{
		ch = *pSrc++;		// �����ȳ��ֵ��ַ�
		*pDst++ = *pSrc++;	// ���ƺ���ֵ��ַ�
		*pDst++ = ch;		// �����ȳ��ֵ��ַ�
	}

	// Դ��������������
	if(nSrcLength & 1)
	{
		*(pDst-2) = 'F';	// ��'F'
		nDstLength++;		// Ŀ�괮���ȼ�1
	}

	// ����ַ����Ӹ�������
	*pDst = '\0';

	// ����Ŀ���ַ�������
	return nDstLength;
}

// �����ߵ����ַ���ת��Ϊ����˳����ַ���
// �磺"683158812764F8" --> "8613851872468"
// ����: pSrc - Դ�ַ���ָ��
//       nSrcLength - Դ�ַ�������
// ���: pDst - Ŀ���ַ���ָ��
// ����: Ŀ���ַ�������
int gsmSerializeNumbers(const char* pSrc, char* pDst, int nSrcLength)
{
	int nDstLength;		// Ŀ���ַ�������
	char ch;			// ���ڱ���һ���ַ�
	int i;
	// ���ƴ�����
	nDstLength = nSrcLength;

	// �����ߵ�
	for(i=0; i<nSrcLength;i+=2)
	{
		ch = *pSrc++;		// �����ȳ��ֵ��ַ�
		*pDst++ = *pSrc++;	// ���ƺ���ֵ��ַ�
		*pDst++ = ch;		// �����ȳ��ֵ��ַ�
	}

	// �����ַ���'F'��
	if(*(pDst-1) == 'F')
	{
		pDst--;
		nDstLength--;		// Ŀ���ַ������ȼ�1
	}

	// ����ַ����Ӹ�������
	*pDst = '\0';

	// ����Ŀ���ַ�������
	return nDstLength;
}

// PDU���룬���ڱ��ơ����Ͷ���Ϣ
// ����: pSrc - ԴPDU����ָ��
// ���: pDst - Ŀ��PDU��ָ��
// ����: Ŀ��PDU������
int gsmEncodePdu(const SM_PARAM* pSrc, char* pDst)
{
	int nLength;			// �ڲ��õĴ�����
	int nDstLength;			// Ŀ��PDU������
	unsigned char buf[256];	// �ڲ��õĻ�����
	//unsigned char tmp[256]={0};	// �ڲ��õĻ�����
	//int i;

	// SMSC��ַ��Ϣ��
	nLength = strlen(pSrc->SCA);	// SMSC��ַ�ַ����ĳ���	
	buf[0] = (char)((nLength & 1) == 0 ? nLength : nLength + 1) / 2 + 1;	// SMSC��ַ��Ϣ����
	buf[1] = 0x91;		// �̶�: �ù��ʸ�ʽ����
	nDstLength = gsmBytes2String(buf, pDst, 2);		// ת��2���ֽڵ�Ŀ��PDU��
	nDstLength += gsmInvertNumbers(pSrc->SCA, &pDst[nDstLength], nLength);	// ת��SMSC���뵽Ŀ��PDU��

	// TPDU�λ���������Ŀ���ַ��
	nLength = strlen(pSrc->TPA);	// TP-DA��ַ�ַ����ĳ���
	buf[0] = 0x11;					// �Ƿ��Ͷ���(TP-MTI=01)��TP-VP����Ը�ʽ(TP-VPF=10)
	buf[1] = 0;						// TP-MR=0
	buf[2] = (char)nLength;			// Ŀ���ַ���ָ���(TP-DA��ַ�ַ�����ʵ����)
	buf[3] = 0x91;					// �̶�: �ù��ʸ�ʽ����
	nDstLength += gsmBytes2String(buf, &pDst[nDstLength], 4);		// ת��4���ֽڵ�Ŀ��PDU��
	nDstLength += gsmInvertNumbers(pSrc->TPA, &pDst[nDstLength], nLength);	// ת��TP-DA��Ŀ��PDU��

	// TPDU��Э���ʶ�����뷽ʽ���û���Ϣ��
	nLength = strlen(pSrc->TP_UD);	// �û���Ϣ�ַ����ĳ���
	buf[0] = pSrc->TP_PID;			// Э���ʶ(TP-PID)
	buf[1] = pSrc->TP_DCS;			// �û���Ϣ���뷽ʽ(TP-DCS)
	buf[2] = 0;						// ��Ч��(TP-VP)Ϊ5����
	if(pSrc->TP_DCS == GSM_7BIT)	
	{
		// 7-bit���뷽ʽ
		buf[3] = nLength;			// ����ǰ����
		nLength = gsmEncode7bit(pSrc->TP_UD, &buf[4], nLength+1) + 4;	// ת��TP-DA��Ŀ��PDU��
		nDstLength += gsmBytes2String(buf, &pDst[nDstLength], nLength);		// ת���ö����ݵ�Ŀ��PDU��
	}
	else if(pSrc->TP_DCS == GSM_UCS2)
	{
		// UCS2���뷽ʽ
		buf[3] = gsmEncodeUcs2(pSrc->TP_UD, &buf[4], nLength);	// ת��TP-DA��Ŀ��PDU��
		nLength = buf[3] + 4;		// nLength���ڸö����ݳ���
		Hex2Asc(&pDst[nDstLength],buf,nLength);
		nDstLength +=(nLength*2);
	}

	// ����Ŀ���ַ�������
	return nDstLength;
}

// PDU���룬���ڽ��ա��Ķ�����Ϣ
// ����: pSrc - ԴPDU��ָ��
// ���: pDst - Ŀ��PDU����ָ��
// ����: �û���Ϣ������
int gsmDecodePdu(const char* pSrc, SM_PARAM* pDst)
{
	int nDstLength;			// Ŀ��PDU������
	unsigned char tmp;		// �ڲ��õ���ʱ�ֽڱ���
	unsigned char buf[256];	// �ڲ��õĻ�����
	char buff[20]="";
	int i;
	
	// SMSC��ַ��Ϣ��
	gsmString2Bytes(pSrc, &tmp, 2);	// ȡ����
	tmp = (tmp - 1) * 2;	// SMSC���봮����
	pSrc += 4;			// ָ����ƣ�������SMSC��ַ��ʽ
	gsmSerializeNumbers(pSrc, pDst->SCA, tmp);	// ת��SMSC���뵽Ŀ��PDU��
	pSrc += tmp;		// ָ�����
	printf("���ĺ���:%s\n",pDst->SCA);
	// TPDU�λ�������
	gsmString2Bytes(pSrc, &tmp, 2);	// ȡ��������
	pSrc += 2;		// ָ�����

	// ȡ�ظ�����
	gsmString2Bytes(pSrc, &tmp, 2);	// ȡ����
	if(tmp & 1) tmp += 1;	// ������ż��
	pSrc += 4;			// ָ����ƣ������˻ظ���ַ(TP-RA)��ʽ
	gsmSerializeNumbers(pSrc, pDst->TPA, tmp);	// ȡTP-RA����
	pSrc += tmp;		// ָ�����
	printf("�ظ�����:%s\n",pDst->TPA);
	
	// TPDU��Э���ʶ�����뷽ʽ���û���Ϣ��
	gsmString2Bytes(pSrc, (unsigned char*)&pDst->TP_PID, 2);	// ȡЭ���ʶ(TP-PID)
	printf("Э���ʶ:%d\n",pDst->TP_PID);
	pSrc += 2;		// ָ�����
	gsmString2Bytes(pSrc, (unsigned char*)&pDst->TP_DCS, 2);	// ȡ���뷽ʽ(TP-DCS)
	printf("���뷽ʽ:%d\n",pDst->TP_DCS);

	pSrc += 2;		// ָ�����
	printf("ʣ����Ϣ:%s\n",pSrc);
	gsmSerializeNumbers(pSrc, buff, 14);		// ����ʱ����ַ���(TP_SCTS) 
	sprintf(pDst->TP_SCTS,"20");
	memcpy(pDst->TP_SCTS+2,buff,2);
	strcat(pDst->TP_SCTS+4,"-");
	memcpy(pDst->TP_SCTS+5,buff+2,2);
	strcat(pDst->TP_SCTS+7,"-");
	memcpy(pDst->TP_SCTS+8,buff+4,2);
	strcat(pDst->TP_SCTS+10," ");
	memcpy(pDst->TP_SCTS+11,buff+6,2);
	strcat(pDst->TP_SCTS+13,":");
	memcpy(pDst->TP_SCTS+14,buff+8,2);
	strcat(pDst->TP_SCTS+16,":");
	memcpy(pDst->TP_SCTS+17,buff+10,2);
	
	printf("������ʱ���:%s\n",pDst->TP_SCTS);
	
	pSrc += 14;		// ָ�����
	gsmString2Bytes(pSrc, &tmp, 2);	// �û���Ϣ����(TP-UDL)
	pSrc += 2;		// ָ�����
	if(pDst->TP_DCS == GSM_7BIT)	
	{
		// 7-bit����
		printf("GSM_7Bit����:");
		for(i=0;i<nDstLength;i++)
		{
			printf("%.2X ",buf[i]);
		}
		printf("\n");
		nDstLength = gsmString2Bytes(pSrc, buf, tmp & 7 ? (int)tmp * 7 / 4 + 2 : (int)tmp * 7 / 4);	// ��ʽת��
		gsmDecode7bit(buf, pDst->TP_UD, nDstLength);	// ת����TP-DU
		printf("7-bit����:%s\n",pDst->TP_UD);
		nDstLength = tmp;
	}
	else if(pDst->TP_DCS == GSM_UCS2)
	{
		// UCS2����
		nDstLength = gsmString2Bytes(pSrc, buf, tmp * 2);			// ��ʽת��
		printf("unicode����:");
		for(i=0;i<nDstLength;i++)
		{
			printf("%.2X ",buf[i]);
		}
		printf("\n");
		nDstLength = gsmDecodeUcs2(buf, pDst->TP_UD, nDstLength);	// ת����TP-DU
		printf("ucs2����:%s\n",pDst->TP_UD);
	}
	else
	{
		nDstLength = gsmString2Bytes(pSrc, buf, tmp * 2);
		printf("GSM_8Bit����:");
		for(i=0;i<nDstLength;i++)
		{
			printf("%.2X ",buf[i]);
		}
		printf("\n");
		gsmDecode8bit(buf, pDst->TP_UD, nDstLength);
		printf("8-bit����:%s\n",pDst->TP_UD);
	}
	// ����Ŀ���ַ�������
	return nDstLength;
}

// ���Ͷ���Ϣ���������������ȡӦ��
// ����: pSrc - ԴPDU����ָ��
int gsmSendMessage(SM_PARAM* pSrc)
{
	int nPduLength;		// PDU������
	unsigned char nSmscLength;	// SMSC������
	int nLength;		// �����յ������ݳ���
	char cmd[16];		// ���
	char pdu[512];		// PDU��
	char ans[128];		// Ӧ��
	
	nPduLength = gsmEncodePdu(pSrc, pdu);	// ����PDU����������PDU��
	strcat(pdu, "\x01a");		// ��Ctrl-Z����
	
	gsmString2Bytes(pdu, &nSmscLength, 2);	// ȡPDU���е�SMSC��Ϣ����
	nSmscLength++;		// ���ϳ����ֽڱ���
	// �����еĳ��ȣ�������SMSC��Ϣ���ȣ��������ֽڼ�
	sprintf(cmd, "AT+CMGS=%d\r", nPduLength / 2 - nSmscLength);	// ��������
	printf("cmd=%s\n",cmd);

	WriteComm(cmd, strlen(cmd),0);	// ��������

	nLength = ReadComm(ans, 128);	// ��Ӧ������

	// �����ܷ��ҵ�"\r\n> "�����ɹ����
	if(nLength == 4 && strncmp(ans, "\r\n> ", 4) == 0)
	{
		printf("%s\n",pdu);
		return WriteComm(pdu, strlen(pdu),1);		// �õ��϶��ش𣬼������PDU��
	}

	return 0;
}

// ��ȡ����Ϣ���������������ȡӦ��
// ��+CMGL����+CMGR����һ���Զ���ȫ������Ϣ
int gsmReadMessageList()
{
	return WriteComm("AT+CMGL\r", 8,0);
}

int gsmReadMessage(int index)
{
	char  cmd[12+1]="";
	int   msize;
	
	sprintf(cmd,"AT+CMGR=%d\r",index);
	msize=strlen(cmd);
	return WriteComm(cmd, msize,0);
}

// ɾ������Ϣ���������������ȡӦ��
// ����: index - ����Ϣ��ţ�1-255
int gsmDeleteMessage(int index)
{
	char cmd[16];		// ���

	sprintf(cmd, "AT+CMGD=%d\r", index);	// ��������

	// ������
	return WriteComm(cmd, strlen(cmd),0);
}

// ��ȡGSM MODEM��Ӧ�𣬿�����һ����
// ���: pBuff - ����Ӧ�𻺳���
// ����: GSM MODEM��Ӧ��״̬, GSM_WAIT/GSM_OK/GSM_ERR
// ��ע: ������Ҫ��ε��ò�����ɶ�ȡһ��Ӧ���״ε���ʱӦ��pBuff��ʼ��
int gsmGetResponse(SM_BUFF* pBuff)
{
	int nLength;		// �����յ������ݳ���
	int nState;

	// �Ӵ��ڶ����ݣ�׷�ӵ�������β��
	nLength = ReadComm(&pBuff->data[pBuff->len], 128);	
	pBuff->len += nLength;

	// ȷ��GSM MODEM��Ӧ��״̬
	nState = GSM_WAIT;
	if ((nLength > 0) && (pBuff->len >= 4))
	{
		if (strncmp(&pBuff->data[pBuff->len - 4], "OK\r\n", 4) == 0)  
			nState = GSM_OK;
		else if (strstr(pBuff->data, "+CMS ERROR") != NULL) 
			nState = GSM_ERR;
	}

	return nState;
}

// ���б��н�����ȫ������Ϣ
// ����: pBuff - ����Ϣ�б�����
// ���: pMsg - ����Ϣ������
// ����: ����Ϣ����
int gsmParseMessageList(SM_PARAM* pMsg, SM_BUFF* pBuff)
{
	int nMsg;			// ����Ϣ����ֵ
	char* ptr;			// �ڲ��õ�����ָ��

	nMsg = 0;
	ptr = pBuff->data;

	// ѭ����ȡÿһ������Ϣ, ��"+CMGL:"��ͷ
	while((ptr = strstr(ptr, "+CMGL:")) != NULL)
	{
		ptr += 6;		// ����"+CMGL:", ��λ�����
		sscanf(ptr, "%d", &pMsg->index);	// ��ȡ���

		ptr = strstr(ptr, "\r\n");	// ����һ��
		if (ptr != NULL)
		{
			ptr += 2;		// ����"\r\n", ��λ��PDU
			printf("Pdu:=[%s]\n",ptr);
			gsmDecodePdu(ptr, pMsg);	// PDU������

			pMsg++;		// ׼������һ������Ϣ
			nMsg++;		// ����Ϣ������1
		}
	}

	return nMsg;
}

//-------------------------------------------------------------------------
// ��ʼ��GPRS���Ź���             
//0:PDUģʽ
//1:textģʽ
//-------------------------------------------------------------------------

int Init_SMS(int model,char *CSCA)
{
	char cmd[18];
	int nret;
	
	memset(cmd,0x00,sizeof(cmd));
	sprintf(cmd, "AT+CMGF=%d\x0d\x0a",model);	// 
	printf("cmd=%s\n",cmd);
	WriteComm(cmd, strlen(cmd),0);
	nret=AT_GetOK(iGprsHandle,2000);
	if(nret==ERROR)
	{
		return ERROR;
	}
	memset(cmd,0x00,sizeof(cmd));
	sprintf(cmd, "AT+CSCA=\"+86%s\"\x0d\x0a",CSCA);	// 
	printf("cmd=%s\n",cmd);
	WriteComm(cmd, strlen(cmd),0);
	nret=AT_GetOK(iGprsHandle,2000);
	if(nret==ERROR)
	{
		return ERROR;
	}
	return OK;
 }

//---------------------------------------------------------------------------------
// ����GPRSģʽ����
// �ú�����GSMģʽ�¿���GPRS����ģʽ
//---------------------------------------------------------------------------------
int Open_GPGS_Mode()
{
    return(1); 
}  

//----------------------------------------------------------------------------------
//  �ر�GPRS���ܺ���
// �ĺ����ر�GPES���ܣ����ص�����ģʽ�� 
//----------------------------------------------------------------------------------
int Close_GPGS_Mode()
{
    return(1); 
} 


//---------------------------------------------------------------------------------- 
// GPRSģʽ�¶�ȡ��������
// ���޸�
//----------------------------------------------------------------------------------
int Read_GPRS_Data()
{
	return 1;
}

//-----------------------------------------------------------------------------------
//  GPRSģʽ��д��������
// д���ݵ��������� ����aΪ���ݵ�ַ��lengthΪ���ݳ��ȣ����ҳ��ȱ������2
// ������ݳ���Ϊ1��2��������Ϣ�޷�������URC���ǻظ���
//-----------------------------------------------------------------------------------
int Write_GPRS_Data(char a[],int length)
{
    return(0);    
}

//----------------------------------------------------------------------------------
// ���յ�GSM�ظ���Ϣ�����жϺ���
// �ú����д��ڽ��յ�GSM�ظ���Ϣ�����������ò�ͬ�Ĵ����ǣ��Ա��Ժ�ĳ�������
// ����ڻظ���Ϣ����������ͬ����Ϣ����ô���ǵĴ��������Ϊ���Ĵ�����
// �ú��������Ƿ���AT_Command()�����Ļظ��Ƚϲ�����
// ͬʱ��GSM_REP_Buffer�������кܿ��ܻ���URC���룬���ڱ�������ͬʱ������URC�жϣ���ֹ
// URC��Ϣ��ʧ����⵽URC��Ϣ����Ӧ��־λ��λ�������Ϣ��������0
//----------------------------------------------------------------------------------
char GSM_RecString_Comp(char ans[], int length)
{
    char code = 0;                                        // GSM�ظ���Ϣ�����Ǳ���      
    return(code);
}

//------------------------------------------------------------------------------------
// AT����ͺ���
// �ú�����GSMģ�鷢��AT������ȴ��ָ����������ָ��������ȷ���ط����������δ��󣬷��ط���ʧ��
// ��ڲ�����cmdҪ���͵�����ָ�룬str����յ��Ľ���ַ������бȽϵ��ַ�����lengthΪ�ַ����ıȽϳ���
// ���ڣ����ͳɹ�����TRUE������ʧ�ܷ���FALSE
//------------------------------------------------------------------------------------
int AT_Command(char *cmd, char length, char code, int time)
{
    return(0);
}

// д����
// ����: pData - ��д�����ݻ�����ָ��
//       nLength - ��д�����ݳ���
// ����: ʵ��д������ݳ���
int WriteComm(void* pData, int nLength,int flg)
{
	unsigned long dwNumWrite;	// ���ڷ��������ݳ���
	if(flg==0)
	{
		ClearGprsBuffer(iGprsHandle);
	}
	printf("write cmd=[%s]\n",(unsigned char *)pData);
	dwNumWrite=WriteUart(iGprsHandle, pData, (DWORD)nLength);
	return (int)dwNumWrite;
}

// ������
// ����: pData - ���������ݻ�����ָ��
//       nLength - ������������ݳ���
// ����: ʵ�ʶ��������ݳ���
int ReadComm(void* pData, int nLength)
{
	unsigned long dwNumRead;	// �����յ������ݳ���

	dwNumRead=ReadUart(iGprsHandle, pData, (DWORD)nLength,5000);
	printf("######################\n");
	printf("recv:[%s]\n",(unsigned char *)pData);
	printf("######################\n");
	return (int)dwNumRead;
}

// �ַ���-->UNICODE��
int MultiByteToWideChar(const char* lpMultiByteStr,int cchMultiByte,unsigned short * lpWideCharStr)

{
	int i,j;
	unsigned char tmp[128];
	unsigned char pdu[128];
	char  Asc='\x80';
	int  size;
	int  len;
	unsigned char unistr[2+1]="";

	memset(tmp,0x00,sizeof(tmp));
	size=0;
	len=0;
	for(i=0;i<cchMultiByte;i++)
	{
		if((lpMultiByteStr[i]&0xFF)<=Asc)
		{
			tmp[size++]='\x00'&0xFF;
			tmp[size++]=lpMultiByteStr[i]&0xFF;
			len++;
		}
		else
		{
			for(j=0;j<Unicode_Max;j++)
			{
				memset(unistr,0x00,sizeof(unistr));
				gsmString2Bytes(uni_table[j].gbk,unistr,4);
				if((lpMultiByteStr[i]&0xFF)==(unistr[0]&0xFF) &&(lpMultiByteStr[i+1]&0xFF)==(unistr[1]&0xFF))
					break;
			}
			if(j>=Unicode_Max)
			{
				tmp[size++]='\x00'&0xFF;
				tmp[size++]=lpMultiByteStr[i]&0xFF;
			}
			else
			{
				memset(unistr,0x00,sizeof(unistr));
				gsmString2Bytes(uni_table[j].unicode,unistr,4);
				tmp[size++]=unistr[0]&0xFF;
				tmp[size++]=unistr[1]&0xFF;
				i++;
			}
			len++;
		}
	}
	memset(pdu,0x00,sizeof(pdu));
	printf("=====================\n");
	for(i=0;i<size;i++)
	{
		pdu[i]=tmp[i];
		printf("%02X ",tmp[i]);
	}
	printf("\n=====================\n");
	for(i=0,j=0;i<size;i+=2,j++)
	{
		lpWideCharStr[j]=(((short)tmp[i])<<8)|((short)tmp[i+1]&0x00FF);
	}

	return (len);
}
// UNICODE��-->�ַ���
int WideCharToMultiByte(unsigned char*  lpWideCharStr,int  cchWideChar,char*  lpMultiByteStr)
{
	
	int i,j;
	char  tmp[128];
	int   size;
	int   len;
	unsigned char unistr[2+1]="";

	memset(tmp,0x00,sizeof(tmp));
	size=0;
	len=0;
	for(i=0;i<cchWideChar;i+=1)
	{
		if(lpWideCharStr[i]=='\x00')
		{
			tmp[size]=lpWideCharStr[i+1];
			size+=1;
			i++;
			len++;
		}
		else
		{
			for(j=0;j<Unicode_Max;j++)
			{
				memset(unistr,0x00,sizeof(unistr));
				gsmString2Bytes(uni_table[j].unicode,unistr,4);
				if((lpWideCharStr[i]==unistr[0]) &&(lpWideCharStr[i+1]==unistr[1]))
					break;
			}
			if(j>=Unicode_Max)
			{
				tmp[size]=lpWideCharStr[i+1];
				size+=1;
				len++;
				i++;
			}
			else
			{
				memset(unistr,0x00,sizeof(unistr));
				gsmString2Bytes(uni_table[j].gbk,unistr,4);
				memcpy(tmp+size,unistr,2);
				size+=2;
				i++;
				len+=2;
			}
		}
	}
	memcpy(lpMultiByteStr,tmp,size);
	return (len);
}

//�ߵ�ת��
void Hex2Asc(char *dest_asc, unsigned char*src_bcd, char src_len)
{
	int 	i, j;
	char 	val;
	
	for( i=0, j=0; i < src_len; i++, j++ )
	{
		val = (src_bcd[i] >> 4) & 0x0F;
		
		if( val <= 9 )	
			dest_asc[j++] = val + 0x30;
		else			
			dest_asc[j++] = val + 0x37;
		
		val = src_bcd[i] & 0x0F;
		
		if( val <= 9 )	
			dest_asc[j] = val + 0x30;
		else			
			dest_asc[j] = val + 0x37;
	}
	dest_asc[j]='\0';
}

int demo_SMS_send()
{
	SM_PARAM  info;
	char tmp[128]="";
	int ret;

	memset(&info,0x00,sizeof(SM_PARAM));
	sprintf(info.SCA,"86%s",gSMS.SCA);
	info.TP_PID = gSMS.TP_PID;
	info.TP_DCS = gSMS.TP_DCS;
	
	Clear();
	TextOut(0, 0, ALIGN_CENTER, "д����");

	ClearLine(1,9);
	ret = Input(1,1, tmp,50, IME_CHINESE, BLACK, GREEN, FALSE, FALSE, TRUE);
	if(ret==CANCEL)
		return CANCEL;
	else if(ret != OK)
	{
		FailBeep(); 
		ClearLine(1, 9);
		SetScrFont(FONT20, WHITE);
		TextOut(0, 4, ALIGN_CENTER, "ʧ��");
		WaitKey(2000);
		return ERROR;
	}
	memcpy(info.TP_UD,tmp,strlen(tmp));

	ClearLine(1,9);
	TextOut(1,1, ALIGN_LEFT, "�ռ��˺���:");
	memset(tmp,0x00,sizeof(tmp));
	ret = Input(1,3, tmp,11, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
	if(ret==CANCEL)
		return CANCEL;
	if(ret != OK)
	{
		FailBeep(); 
		ClearLine(1, 9);
		SetScrFont(FONT20, WHITE);
		TextOut(0, 4, ALIGN_CENTER, "ʧ��");
		WaitKey(2000);
		return ERROR;
	}
	sprintf(info.TPA,"86%s",tmp);
	ClearLine(1,9);
	TextOut(0,4, ALIGN_CENTER, "������...");
	while(1)
	{
		ret=gsmSendMessage(&info);
		if(ret>0)
		{
			ret=AT_GetOK(iGprsHandle,2000);
			if(ret==ERROR)
			{
				ClearLine(1,9);
				TextOut(0,3, ALIGN_CENTER, "����ʧ��!!");
				TextOut(0,4, ALIGN_CENTER, "�Ƿ��ط�?");
				if(WaitLimitKey("\x0F\x12", 2, 0) == KEY_CANCEL)
					return CANCEL;
				else
					continue;
			}
			ClearLine(1,9);
			TextOut(0,4, ALIGN_CENTER, "���ͳɹ�!!");
			WaitKey(5000);
			break;
		}
		else
		{
			ClearLine(1,9);
			TextOut(0,3, ALIGN_CENTER, "����ʧ��!!");
			TextOut(0,4, ALIGN_CENTER, "�Ƿ��ط�?");
			if(WaitLimitKey("\x0F\x12", 2, 0) == KEY_CANCEL)
				return CANCEL;
		}
	}
	
	return ret;
}
int demo_SMS_recv()
{
	int nMsg;				// �յ�����Ϣ����
	int nDelete;			// Ŀǰ����ɾ���Ķ���Ϣ���
	SM_BUFF buff;			// ���ն���Ϣ�б�Ļ�����
	SM_PARAM param[256];	//���ն���Ϣ������
	int i;

	for(i=0;i<256;i++)
	{
		memset(&param[i],0x00,sizeof(SM_PARAM));
	}
	Clear();
	TextOut(0, 0, ALIGN_CENTER, "�ռ���");
	TextOut(0, 4, ALIGN_CENTER, "���ڲ����¶���");
	TextOut(0, 5, ALIGN_CENTER, "���Ժ�...");
	memset(&buff, 0, sizeof(buff));
	while(1)
	{
		if(WaitLimitKey("\x0F\x12", 2, 1000) == KEY_CANCEL)
				return CANCEL;
		
		memset(&buff, 0, sizeof(buff));
		gsmReadMessageList();

	doing:	
		Wait(500);
		switch (gsmGetResponse(&buff))
		{
			case GSM_OK: 
				nMsg = gsmParseMessageList(param, &buff);
				if (nMsg > 0)
				{
					OkBeep();
					PutRecvMessage(param,nMsg);
					nDelete = 0;
				}
				break;
			case GSM_ERR:
				Wait(500);
				break;
			case GSM_WAIT:
				printf("recv char doing...\n");
				Wait(500);
				goto doing;
				break;
			default:
				break;
		}
	}
	
	return OK;
}

void PutRecvMessage(SM_PARAM* pparam, int nCount)
{
	int i,j;
	char tmp[128];
	char ckey;
	BOOL Flg=TRUE;
	int nret;
	
	Clear();
	for (i = 0; i < nCount && Flg; i++)
	{
		ClearLine(1,9);
		memset(tmp,0x00,sizeof(tmp));
		sprintf(tmp,"������:%s",pparam[i].TPA);
		TextOut(0, 1, ALIGN_LEFT,tmp);
		memset(tmp,0x00,sizeof(tmp));
		sprintf(tmp,"����ʱ��:%s",pparam[i].TP_SCTS);
		TextOut(0, 2, ALIGN_LEFT,tmp);
		TextOut(0, 3, ALIGN_LEFT,"--------------------------------");
		TextOut(0, 4, ALIGN_LEFT,pparam[i].TP_UD);
		for(j=0;j<strlen(pparam[i].TP_UD);j++)
		{
			printf("%.2X ",pparam[i].TP_UD[j]&0xff);
		}
		printf("\n");
		memset(tmp,0x00,sizeof(tmp));
		sprintf(tmp,"%d/%d",i+1,nCount);
		TextOut(0, 9, ALIGN_CENTER,tmp);
		ckey=WaitLimitKey("\x0F\x12\x0E", 3, 0);
		switch(ckey)
		{
			case KEY_CANCEL:
				Flg=FALSE;
				break;
			case KEY_BACKSPACE:
				ClearLine(1,9);
				TextOut(0, 3, ALIGN_CENTER,"Ҫɾ����������?");
				ckey=WaitLimitKey("\x0F\x12",2, 0);
				if(ckey==KEY_ENTER)
				{
					ClearLine(1,9);
					TextOut(0, 3, ALIGN_CENTER,"����ɾ��..");
					nret=gsmDeleteMessage(pparam[i].index);
					if(nret>0)
					{
						nret=AT_GetOK(iGprsHandle,3000);
						if(nret==ERROR)
						{
							ClearLine(1,9);
							TextOut(0, 3, ALIGN_CENTER,"ɾ��ʧ��");
						}
						else
						{
							ClearLine(1,9);
							TextOut(0, 3, ALIGN_CENTER,"ɾ���ɹ�");
							OkBeep();
						}
					}
				}
				break;
			default:
				break;
		}
		
	}

}

int SMS_Setting()
{
		int ret;
		char buff[128];
		int tempDataNum;
	
		while(1)
		{
			Clear();
			SetScrFont(FONT20, WHITE);
			TextOut(0, 0, ALIGN_CENTER, "����ģʽ");
			TextOut(2, 3, ALIGN_LEFT, "0:PDUģʽ");
			TextOut(2, 4, ALIGN_LEFT, "1:TEXTģʽ");
			TextOut(2, 5, ALIGN_LEFT, "ģʽ:");
			TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
			memset(buff, 0, sizeof(buff));
			sprintf(buff, "%d", gSMS.TP_PID);
			SetScrFont(FONT20, RED);
			ret = Input(10, 5, buff, 1, IME_NUMBER, BLACK, GREEN, FALSE, TRUE, FALSE);
			if(ret != OK)
				goto FAILED;
			tempDataNum = atoi(buff);
			if(tempDataNum <0 || tempDataNum >1)
			{
				Clear();
				SetScrFont(FONT20, WHITE);
				TextOut(0, 4, ALIGN_CENTER, "�������ݷǷ�");
				WaitKey(2000);
				continue;
			}
			gSMS.TP_PID= tempDataNum;
			DebugOut("sms module:%d\n", gSMS.TP_PID);
			break;
		}
		while(1)
		{
			Clear();
			SetScrFont(FONT20, WHITE);
			TextOut(0, 0, ALIGN_CENTER, "�������ĺ���");
			TextOut(2, 5, ALIGN_LEFT, "���ĺ���:");
			TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
			memset(buff, 0, sizeof(buff));
			SetScrFont(FONT20, RED);
			ret = Input(14, 5, gSMS.SCA, 11, IME_NUMBER, BLACK, GREEN, FALSE, TRUE, FALSE);
			if(ret != OK)
				goto FAILED;
			DebugOut("sms sca:%d\n", gSMS.SCA);
			break;
		}
		while(1)
		{
			Clear();
			SetScrFont(FONT20, WHITE);
			TextOut(0, 0, ALIGN_CENTER, "���ű��뷽ʽ");
			TextOut(2, 2, ALIGN_LEFT, "8:GSM_UCS2");
			TextOut(2, 3, ALIGN_LEFT, "4:GSM_8BIT");
			TextOut(2, 4, ALIGN_LEFT, "0:GSM_7BIT");
			
			TextOut(2, 5, ALIGN_LEFT, "����:");
			TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
			memset(buff, 0, sizeof(buff));
			sprintf(buff, "%d", gSMS.TP_DCS);
			SetScrFont(FONT20, RED);
			ret = Input(10, 5, buff, 1, IME_NUMBER, BLACK, GREEN, FALSE, TRUE, FALSE);
			if(ret != OK)
				goto FAILED;
			tempDataNum = atoi(buff);
			if(tempDataNum%4!=0)
			{
				Clear();
				SetScrFont(FONT20, WHITE);
				TextOut(0, 4, ALIGN_CENTER, "�������ݷǷ�");
				WaitKey(2000);
				continue;
			}
			gSMS.TP_DCS= tempDataNum;
			DebugOut("sms dcs:%d\n", gSMS.TP_DCS);
			break;
		}
		while(1)
		{
			Clear();
			SetScrFont(FONT20, WHITE);
			TextOut(0, 0, ALIGN_CENTER, "���Ŵ洢");
			TextOut(2, 5, ALIGN_LEFT, "��ǰ:");
			TextOut(0, 8, ALIGN_CENTER, "���ֲ����밴ȷ�ϼ�");
			memset(buff, 0, sizeof(buff));
			sprintf(buff, "%d", gSMS.uiMax);
			SetScrFont(FONT20, RED);
			ret = Input(10, 5, buff, 3, IME_NUMBER, BLACK, GREEN, FALSE, FALSE, FALSE);
			if(ret != OK)
				goto FAILED;
			tempDataNum = atoi(buff);
			if(tempDataNum <=0 || tempDataNum >250)
			{
				Clear();
				SetScrFont(FONT20, WHITE);
				TextOut(0, 4, ALIGN_CENTER, "�������ݷǷ�");
				WaitKey(2000);
				continue;
			}
			gSMS.uiMax= tempDataNum;
			DebugOut("sms module:%d\n", gSMS.uiMax);
			break;
		}
		//�����ļ�
		if(WriteData("test-sms.dat", &gSMS, sizeof(T_SMS), 0) == FALSE)
		{
			Clear();					  
			SetScrFont(FONT20, WHITE);
			TextOut(0, 3, ALIGN_CENTER, "�����ļ�����"); 
			TextOut(0, 4, ALIGN_CENTER, "���Ժ�����"); 
			FailBeep();
			WaitKey(2000);
			goto FAILED;
		}
	
		OkBeep();
		Clear();
		SetScrFont(FONT20, WHITE);
		TextOut(2, 4, ALIGN_CENTER, "���óɹ�!");
		WaitKey(2000);
		return OK;
	
	FAILED:
		memset(&gTerm, 0, sizeof(T_TERM));
		ReadData("test-sms.dat", &gSMS,sizeof(T_SMS), 0);
	
		return ERROR;
}

int gsmDecode8bit(unsigned char* pSrc, char* pDst, int nSrcLength)
{
	// �򵥸���
	memcpy(pDst, pSrc, nSrcLength);

	// ����ַ����Ӹ�������
	*pDst = '\0';

	return nSrcLength;
}

int demo_SMS_read(int index)
{
	int nMsg;				// �յ�����Ϣ����
	SM_BUFF buff;			// ���ն���Ϣ�б�Ļ�����
	SM_PARAM param[256];	//���ն���Ϣ������
	int i;
	BOOL nSend=TRUE;
	
	for(i=0;i<256;i++)
	{
		memset(&param[i],0x00,sizeof(SM_PARAM));
	}
	Clear();
	TextOut(0, 0, ALIGN_CENTER, "�ռ���");
	TextOut(0, 4, ALIGN_CENTER, "���ڲ��ն���");
	TextOut(0, 5, ALIGN_CENTER, "���Ժ�...");
	memset(&buff, 0, sizeof(buff));
	while(nSend)
	{
		if(WaitLimitKey("\x0F\x12", 2, 1000) == KEY_CANCEL)
				return CANCEL;
		
		memset(&buff, 0, sizeof(buff));
		gsmReadMessage(index);

	doing:	
		Wait(500);
		switch (gsmGetResponse(&buff))
		{
			case GSM_OK: 
				nMsg = gsmParseMessage(param, &buff);
				if (nMsg > 0)
				{
					OkBeep();
					PutRecvMessage(param,nMsg);
				}
				nSend=FALSE;
				break;
			case GSM_ERR:
				nSend=FALSE;
				break;
			case GSM_WAIT:
				printf("recv char doing...\n");
				Wait(500);
				goto doing;
				break;
			default:
				break;
		}
	}
	
	return OK;
}
int gsmParseMessage(SM_PARAM* pMsg, SM_BUFF* pBuff)
{
	int nMsg;			// ����Ϣ����ֵ
	char* ptr;			// �ڲ��õ�����ָ��

	nMsg = 0;
	ptr = pBuff->data;

	// ѭ����ȡÿһ������Ϣ, ��"+CMGL:"��ͷ
	while((ptr = strstr(ptr, "+CMGR:")) != NULL)
	{
		ptr += 6;		// ����"+CMGL:", ��λ�����
		sscanf(ptr, "%d", &pMsg->index);	// ��ȡ���

		ptr = strstr(ptr, "\r\n");	// ����һ��
		if (ptr != NULL)
		{
			ptr += 2;		// ����"\r\n", ��λ��PDU
			printf("Pdu:=[%s]\n",ptr);
			gsmDecodePdu(ptr, pMsg);	// PDU������

			pMsg++;		// ׼������һ������Ϣ
			nMsg++;		// ����Ϣ������1
		}
	}

	return nMsg;
}

