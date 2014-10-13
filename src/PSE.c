//////////////////////////////////////////////////////////////////////////////
//20120328
//ymm
// �������_Convert.hͷ�ļ�
//////////////////////////////////////////////////////////////////////////////

#include <Main.h>

//////////////////////////////////////////////////////////////////////////////

PRECORD g_pRecord = NULL;
BOOL g_bPSE = TRUE;
int g_nAsi = 0;

//////////////////////////////////////////////////////////////////////////////
//CPU�������������ݽṹ��
//typedef struct {
//        unsigned char Command[4]; 	// ����ͷ
//        unsigned int Lc;		// Ҫ���͵����ݳ���(0��ʾ�޸��ֽ�)
//        unsigned char * DataIn;	// Ҫ���͵����ݻ�����(û�����ݸ�NULL)
//        int Le;			// Ҫ���յ����ݳ���(-1��ʾ�޸��ֽ�,
					// 0��ʾ���ݿ����͵��ֽ�)
//}APDU_SEND;
//
//typedef struct {
//        unsigned int LenOut;		// ʵ�ʽ��յ������ݳ���
//        unsigned char *DataOut;	// ���յ����ݻ�����
//        unsigned char SWA;		// ��Ӧ��SW1
//        unsigned char SWB;		// ��Ӧ��SW2
//}APDU_RESP;
//
//typedef struct{
// 	UCHAR icc_style;		// ������
//	UCHAR wk_vol;			// ������ѹ
//	UCHAR show_info;		// ��ӡ����Ϣ
//	UCHAR reserved;			// PPS��0X02=�Զ�����PPS
//	Unsigned long wait_time;	// ��ʱʱ�䡣0=Ĭ��
//}WORK_MODE;

// ��ʼ��CPU��
int OpenCpuCard(int nSlot)
{
	char szATR[ATR_TEMP_LEN] = {0};
        int nAtrLen = 0;
        int nRet = 0;
	WORK_MODE WorkMode;
	int i = 0;

	DebugOut("slot = %d.\n", nSlot);
	WorkMode.icc_style = ST_EMV;
	WorkMode.wk_vol	= VOLTAGE_5V;
	WorkMode.show_info = 1;
	WorkMode.reserved = MANUAL_RESP;
	WorkMode.wait_time = 0;

	// ���豸�ļ�
	nRet = IccOpen(nSlot);
	if (0 != nRet)
	{
		DebugOut("Open Icc ErrCode: %d\n", nRet);
		return OPEN_ERR;		
	}
	DebugOut("Open Icc ErrCode: OK \n");

	// ����Ƿ��п����� ��SAM�������
	nRet = IccDetect(nSlot);
	if (0 != nRet)
	{
		DebugOut("Detect Icc ErrCode: %d\n", nRet);
		return DETECT_ERR;		
	}
	DebugOut("Detect Icc ErrCode: OK \n");

	// ��ʼ����Ƭ 

	nRet = IccInitEx(nSlot, szATR, &nAtrLen, WorkMode);
	if (0 != nRet)
	{
		DebugOut("Init Icc Ex ErrCode: %d\n", nRet);
		return DETECT_ERR;		
	}

	for ( i = 0; i < nAtrLen; i++)
	{
		DebugOut("%02x ", szATR[i]);
		DebugOut("\n");
	}
	
	DebugOut("Init Icc Ex ErrCode: OK \n");

	return OK;	
}
// �ر�CPU��
int CloseCpuCard(int nSlot)
{
	if (0 != IccClose(nSlot))
	{
		return ERROR;
	}
	return OK;
}
// 
int GetMFData(BYTE nSlot, BYTE_PTR SWA, BYTE_PTR SWB, INT * nOutLen, BYTE_PTR data)
{
	int  nRet = 0;
	APDU_SEND ApduSend;
	APDU_RESP ApduRecv;

	if (SWA == NULL || SWB == NULL || data == NULL || nOutLen == NULL)
	{
		return ERROR;
	}

	if (ERROR == Select(&ApduSend, '\x00', '\x00', 2, "\x3F\x00"))
	{
		return ERROR;
	}
	
	if (ERROR == APDU_R_Malloc(&ApduRecv, 255))
	{
		return ERROR;
	}

	nRet = IccIsoCommand(nSlot, &ApduSend, &ApduRecv);
	if (0 != nRet)
	{
		APDU_S_Free(&ApduSend);
		APDU_R_Free(&ApduRecv);
		return nRet;
	}
        APDU_R_Length(&ApduRecv, nOutLen);
        APDU_R_SW1(&ApduRecv, SWA);
        APDU_R_SW2(&ApduRecv, SWB);
        APDU_R_Data(&ApduRecv, data);
        APDU_S_Free(&ApduSend);
        APDU_R_Free(&ApduRecv);

	return OK;	
}
// 
int GetDDFData(BYTE nSlot, BYTE_PTR SFI, BYTE_PTR SWA, BYTE_PTR SWB, INT * nOutLen, BYTE_PTR data)
{
	int  nRet = 0;
	APDU_SEND ApduSend;
	APDU_RESP ApduRecv;

	if (SWA == NULL || SWB == NULL || data == NULL || nOutLen == NULL)
	{
		return ERROR;
	}

	if (ERROR == Select(&ApduSend, '\x00', '\x00', 2, SFI))
	{
		return ERROR;
	}
	
	if (ERROR == APDU_R_Malloc(&ApduRecv, 255))
	{
		return ERROR;
	}

	nRet = IccIsoCommand(nSlot, &ApduSend, &ApduRecv);
	if (0 != nRet)
	{
		APDU_S_Free(&ApduSend);
		APDU_R_Free(&ApduRecv);
		return nRet;
	}
        APDU_R_Length(&ApduRecv, nOutLen);
        APDU_R_SW1(&ApduRecv, SWA);
        APDU_R_SW2(&ApduRecv, SWB);
        APDU_R_Data(&ApduRecv, data);
        APDU_S_Free(&ApduSend);
        APDU_R_Free(&ApduRecv);

	return OK;	
}

int GetResp(INT nSlot, BYTE_PTR SWA, BYTE_PTR SWB, INT nOutLen, BYTE_PTR data)
{
	int  nRet = 0;
	APDU_SEND ApduSend;
	APDU_RESP ApduRecv;

	if (SWB == NULL || SWB[0] == '\x00' || SWA == NULL || data == NULL)
	{
		return ERROR;
	}
	
	if (ERROR == GetResponse(&ApduSend, str_To_Dec(SWB)))
	{
		return ERROR;
	}
	
	if (ERROR == APDU_R_Malloc(&ApduRecv, 255))
	{
		return ERROR;
	}

	nRet = IccIsoCommand(nSlot, &ApduSend, &ApduRecv);
	if (0 != nRet)
	{
		APDU_S_Free(&ApduSend);
		APDU_R_Free(&ApduRecv);
		return nRet;
	}
        APDU_R_Length(&ApduRecv, &nOutLen);
        APDU_R_SW1(&ApduRecv, SWA);
        APDU_R_SW2(&ApduRecv, SWB);
        APDU_R_Data(&ApduRecv, data);
        APDU_S_Free(&ApduSend);
        APDU_R_Free(&ApduRecv);

	return OK;	
}
// �������ص�����MF
int AnalyMFData(BYTE nSlot, BYTE nOutLen, BYTE_PTR data, BYTE_PTR SFI, BYTE_PTR nRecCount, BYTE_PTR bPSE)
{
	BYTE nFCILen = 0;
	BYTE nFCIPriLen = 0;
	BYTE szFCIPri[255] = {0};
	BYTE nTmpLen = 0;
	BYTE nFCINext = 0;

	//9000
	// �������ݷ��������
	if (data == NULL || SFI == NULL)
	{
		return ERROR;
	}
	
	// ��һ���ֽ�'6F'0
	// 6F
	if ('\x6f' != data[nTmpLen])
	{
		return ERROR;
	}

	// FCIģ�峤��1
	//15
	nTmpLen += 1;
	nFCILen = data[1];

	// һ���ֽ�'6F'2
	//84
	nTmpLen += 1;
	if ('\x84' != data[nTmpLen])
	{
		return ERROR;
	}

	// DF������3
	//0E
	nTmpLen += 1;
	nFCIPriLen = data[nTmpLen];

	// DF��4
	//315041592E5359532E4444463031
	nTmpLen += 1;
	memset(szFCIPri, 0, sizeof(szFCIPri));
	memcpy(szFCIPri, data + nTmpLen, nFCIPriLen);
	if (0 == memcmp(szFCIPri, "\x31\x50\x41\x59\x2e\x53\x59\x53\x2e\x44\x44\x46\x30\x31", 14))
	{
		*bPSE = 0;
		// һ���ֽ� '\xA5'4+nFCIPriLen
		//A5
		nTmpLen += nFCIPriLen;
		if ('\xA5' != data[nTmpLen])
		{
			return ERROR;
		}

		// FCI����ר��ģ�峤��5+nFCIPriLen
		//03
		nTmpLen += 1;
		nFCINext = data[nTmpLen];

		// һ���ֽ�'\x88'6+nFCIPriLen
		//88
		nTmpLen += 1;
		if ('\x88' != data[nTmpLen])
		{
			return ERROR;
		}
	 
		// SFI���ݳ���
		//01
		nTmpLen += 1;
		*nRecCount =  *(data + nTmpLen);
		// SF1
		//01
		nTmpLen += 1;
		*SFI = *(data + nTmpLen);
	
		nTmpLen += 1;

		DebugOut("%d == %d\n", nOutLen, nTmpLen);
		if (nTmpLen != nOutLen)
		{
			return ERROR;
		}
	}
	else
	{
		*bPSE = 1;
	}

	return OK;
}
// �������ص�����DDF
int AnalyDDFData(BYTE nSlot, BYTE nOutLen, BYTE_PTR data, BYTE_PTR SFI, BYTE_PTR nRecCount)
{
	BYTE nFCILen = 0;
	BYTE nFCIPriLen = 0;
	BYTE szFCIPri[255] = {0};
	BYTE nTmpLen = 0;
	BYTE nFCINext = 0;

	//9000
	// �������ݷ��������
	if (data == NULL || SFI == NULL)
	{
		return ERROR;
	}
	
	// ��һ���ֽ�'6F'0
	// 6F
	if ('\x6f' != data[nTmpLen])
	{
		return ERROR;
	}

	// FCIģ�峤��1
	//15
	nTmpLen += 1;
	nFCILen = data[1];

	// һ���ֽ�'6F'2
	//84
	nTmpLen += 1;
	if ('\x84' != data[nTmpLen])
	{
		return ERROR;
	}

	// DF������3
	//0E
	nTmpLen += 1;
	nFCIPriLen = data[nTmpLen];

	// DF��4
	//315041592E5359532E4444463031
	nTmpLen += 1;
	memset(szFCIPri, 0, sizeof(szFCIPri));
	memcpy(szFCIPri, data + nTmpLen, nFCIPriLen);
	
	// һ���ֽ� '\xA5'4+nFCIPriLen
	//A5
	nTmpLen += nFCIPriLen;
	if ('\xA5' != data[nTmpLen])
	{
		return ERROR;
	}

	// FCI����ר��ģ�峤��5+nFCIPriLen
	//03
	nTmpLen += 1;
	nFCINext = data[nTmpLen];

	// һ���ֽ�'\x88'6+nFCIPriLen
	//88
	nTmpLen += 1;
	if ('\x88' != data[nTmpLen])
	{
		return ERROR;
	}
 
	// SFI���ݳ���
	//01
	nTmpLen += 1;
	*nRecCount =  *(data + nTmpLen);
	// SF1
	//01
	nTmpLen += 1;
	*SFI = *(data + nTmpLen);

	nTmpLen += 1;

	DebugOut("%d == %d\n", nOutLen, nTmpLen);
	if (nTmpLen != nOutLen)
	{
		return ERROR;
	}

	if (ERROR == GetSFIRecord(nSlot, *nRecCount, *SFI))
	{
		return ERROR;
	}

	return OK;
}
//============================================================================
// ��ȡSFI
int GetSFIRec(INT nSlot, INT RecNum, BYTE SFI, BYTE_PTR SWA, BYTE_PTR SWB,
	 INT *  nOutLen, BYTE_PTR data)
{
	int  nRet = 0;
	APDU_SEND ApduSend;
	APDU_RESP ApduRecv;

	DebugOut("ReadRecord %d\n", RecNum);	
	if (ERROR == ReadRecord(&ApduSend, RecNum, SFI))
	{
		return ERROR;
	}
	
	if (ERROR == APDU_R_Malloc(&ApduRecv, 255))
	{
		return ERROR;
	}

	nRet = IccIsoCommand(nSlot, &ApduSend, &ApduRecv);
	if (0 != nRet)
	{
		APDU_S_Free(&ApduSend);
		APDU_R_Free(&ApduRecv);
		return nRet;
	}
        APDU_R_Length(&ApduRecv, nOutLen);
        APDU_R_SW1(&ApduRecv, SWA);
        APDU_R_SW2(&ApduRecv, SWB);
        APDU_R_Data(&ApduRecv, data);
        APDU_S_Free(&ApduSend);
        APDU_R_Free(&ApduRecv);

	return OK;	
}
// �������ص�����SFI��DDF����ADF
int AnalyRecData(BYTE nSlot, BYTE nOutLen, BYTE_PTR data, BYTE_PTR SFI)
{
	BYTE nFCILen = 0;
	BYTE nFCIPriLen = 0;
	BYTE szFCIPri[255] = {0};
	BYTE nTmpLen = 0;
	BYTE nFCINext = 0;
	BYTE nRecCount;
	
	// �������ݷ�2�����
	if (data == NULL || SFI == NULL)
	{
		return ERROR;
	}
	
	// ��һ���ֽ�'6F'0
	// 6F
	if ('\x6f' != data[nTmpLen])
	{
		return ERROR;
	}

	// FCIģ�峤��1
	//15
	nTmpLen += 1;
	nFCILen = data[1];

	// һ���ֽ�'6F'2
	//84
	nTmpLen += 1;
	if ('\x84' != data[nTmpLen])
	{
		return ERROR;
	}

	// DF������3
	//0E
	nTmpLen += 1;
	nFCIPriLen = data[nTmpLen];

	// DF��4
	//315041592E5359532E4444463031
	nTmpLen += 1;
	memset(szFCIPri, 0, sizeof(szFCIPri));
	memcpy(szFCIPri, data + nTmpLen, nFCIPriLen);

	// һ���ֽ� '\xA5'4+nFCIPriLen
	//A5
	nTmpLen += nFCIPriLen;
	if ('\xA5' != data[nTmpLen])
	{
		return ERROR;
	}

	// FCI����ר��ģ�峤��5+nFCIPriLen
	//03
	nTmpLen += 1;
	nFCINext = data[nTmpLen];

	// һ���ֽ�'\x88'6+nFCIPriLen
	//88
	nTmpLen += 1;
	if ('\x88' == data[nTmpLen])
	{
		//DDF
		// SFI���ݳ���
		//01
		nTmpLen += 1;
		nRecCount =  *(data + nTmpLen);
		// SF1
		//01
		nTmpLen += 1;
		*SFI = *(data + nTmpLen);
		/*SFI = *(data + nTmpLen) >> 3;
		*SFI &= 0x03;*/
		
		nTmpLen += 1;
		DebugOut("%d == %d\n", nOutLen, nTmpLen);
		if (nTmpLen != nOutLen)
		{
			return ERROR;
		}

		if (ERROR == GetDDFSFI(nSlot, nRecCount, SFI))
		{
			return ERROR;
		}
	}
	if ('\x50' == data[nTmpLen])
	{
		// ADF
	}

	return OK;
}
//////////////////////////////////////////////////////////////////////////////
// ��ȡ��¼����Ϣ
int GetSFIRecord(BYTE nSlot, BYTE RecNum, BYTE SFI)
{
	BYTE	SWA[3] = {0};
	BYTE	SWB[3] = {0};
	INT 	nOutLen = 0 ;
	BYTE	data[255] = {0};
	int i = 0;

	for (i = 0; i < RecNum; i++)
	{
		// ��ȡ������¼
		if (OK != GetSFIRec(nSlot, i + 1, SFI, SWA, SWB, &nOutLen, data))
		{
			CloseCpuCard(nSlot);
			return ERROR;
		}

		if (0 != strcmp(SWA, "90") || 0 != strcmp(SWB, "00"))
		{
			if (0 == strcmp(SWA, "61"))
			{

				memset(SWA, 0, sizeof(SWA));
				memset(data, 0, sizeof(data));
				nOutLen = 0;
				if (OK == GetResp(nSlot, SWA, SWB, nOutLen, data))
				{
					if (0 == strcmp(SWA, "90") || 0 == strcmp(SWB, "00"))
					{
							goto LABLE_SFI_DATA;
					}
				}
			
			}
			else if (0 != strcmp(SWA, "6A") && 0 != strcmp(SWB, "83"))
			{
				CloseCpuCard(nSlot);
				return -2;
			}
			CloseCpuCard(nSlot);
			return ERROR;
		}
	
		LABLE_SFI_DATA:

		// ѭ����ȡ��¼������ӵ�ȫ�ֱ�����
		if (OK != AnalyRecData(nSlot, nOutLen, data, &SFI))
		{
			CloseCpuCard(nSlot);
			return ERROR;
		}
	}
	return OK;
}

int GetMFSFI(BYTE nSlot, BYTE_PTR nRecCount, BYTE_PTR SFI, BYTE_PTR bPSE)
{
	BYTE	SWA[3] = {0};
	BYTE	SWB[3] = {0};
	INT 	nOutLen = 0 ;
	BYTE	data[255] = {0};

	if (OK != GetMFData(nSlot, SWA, SWB, &nOutLen, data))
	{
		CloseCpuCard(nSlot);
		return ERROR;
	}
	DebugOut("GetMFData()\n");

	if (0 != strcmp(SWA, "90") || 0 != strcmp(SWB, "00"))
	{
		if (0 == strcmp(SWA, "61"))
		{
			memset(SWA, 0, sizeof(SWA));
			memset(data, 0, sizeof(data));
			nOutLen = 0;
			if (OK == GetResp(nSlot, SWA, SWB, nOutLen, data))
			{
				if (0 == strcmp(SWA, "90") || 0 == strcmp(SWB, "00"))
				{
					goto LABLE_SFI_DATA;
				}
			}
			
		}
		CloseCpuCard(nSlot);
		return ERROR;
	}
	
LABLE_SFI_DATA:
	// ��ȡ����
	if (OK != AnalyMFData(nSlot, nOutLen, data, SFI, nRecCount, bPSE))
	{
		CloseCpuCard(nSlot);
		return ERROR;
	}

	return OK;
}

int GetDDFSFI(BYTE nSlot, BYTE_PTR nRecCount, BYTE_PTR SFI)
{
	BYTE	SWA[3] = {0};
	BYTE	SWB[3] = {0};
	INT 	nOutLen = 0 ;
	BYTE	data[255] = {0};

	if (OK != GetDDFData(nSlot, SFI, SWA, SWB, &nOutLen, data))
	{
		CloseCpuCard(nSlot);
		return ERROR;
	}
	DebugOut("GetDDFData()\n");

	if (0 != strcmp(SWA, "90") || 0 != strcmp(SWB, "00"))
	{
		if (0 == strcmp(SWA, "61"))
		{
			memset(SWA, 0, sizeof(SWA));
			memset(data, 0, sizeof(data));
			nOutLen = 0;
			if (OK == GetResp(nSlot, SWA, SWB, nOutLen, data))
			{
				if (0 == strcmp(SWA, "90") || 0 == strcmp(SWB, "00"))
				{
				goto LABLE_SFI_DATA;
				}
			}
			
		}
	CloseCpuCard(nSlot);
	return ERROR;
	}
	
LABLE_SFI_DATA:
	// ��ȡ����
	if (OK != AnalyDDFData(nSlot, nOutLen, data, SFI, nRecCount))
	{
		CloseCpuCard(nSlot);
		return ERROR;
	}
return OK;
}

//////////////////////////////////////////////////////////////////////////////

int GetMF(int nSlot)
{
	BYTE	SFI = 0;
	BYTE	nRecCount = 0;
	BYTE	bPSE = 0;

	if (!g_bPSE)
	{
		// ����AID�б���
	}

	if ( 0 != OpenCpuCard(nSlot))
	{
		return ERROR;
	}
	DebugOut("OpenCpuCard()\n");
	if (OK != GetMFSFI(nSlot, &nRecCount, &SFI, &bPSE))
	{
		CloseCpuCard(nSlot);
		return ERROR;
	}
	DebugOut("GetMFSFI()\n");
	if (0 == bPSE)
	{
		// ����AID�б���
	}
	else if (1 == bPSE)
	{	
		SFI = 0x01;
	}
	// ��ȡSFI��¼
	if (OK != GetSFIRecord(nSlot, nRecCount, SFI))
	{
		CloseCpuCard(nSlot);
		return ERROR;
	}
	DebugOut("GetSFIRecord()\n");

	CloseCpuCard(nSlot);
	return OK;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// ͨ��AID���ӻ�ȡ����
int GetDFByName(BYTE_PTR pAid, BYTE nLen, BYTE_PTR SWA, BYTE_PTR SWB, BYTE_PTR data, BYTE_PTR nOutLen)
{
	int  nRet = 0;
	APDU_SEND ApduSend;
	APDU_RESP ApduRecv;

	if (pAid == NULL)
	{
		return ERROR;
	}

	if (SWA == NULL || SWB == NULL || data == NULL || nOutLen == NULL)
	{
		return ERROR;
	}

	if (ERROR == Select(&ApduSend, '\x04', '\x00', nLen, pAid))
	{
		return ERROR;
	}
	
	if (ERROR == APDU_R_Malloc(&ApduRecv, 255))
	{
		return ERROR;
	}

	nRet = IccIsoCommand(nSlot, &ApduSend, &ApduRecv);
	if (0 != nRet)
	{
		APDU_S_Free(&ApduSend);
		APDU_R_Free(&ApduRecv);
		return nRet;
	}
        APDU_R_Length(&ApduRecv, nOutLen);
        APDU_R_SW1(&ApduRecv, SWA);
        APDU_R_SW2(&ApduRecv, SWB);
        APDU_R_Data(&ApduRecv, data);
        APDU_S_Free(&ApduSend);
        APDU_R_Free(&ApduRecv);

	return OK;	
}
// �������ص�����AID
int AnalyAidData(BYTE nSlot, BYTE nOutLen, BYTE_PTR data, BYTE_PTR SFI)
{
	BYTE nFCILen = 0;
	BYTE nFCIPriLen = 0;
	BYTE szFCIPri[255] = {0};
	BYTE nTmpLen = 0;
	BYTE nFCINext = 0;
	BYTE nRecCount;
	
	// �������ݷ�2�����
	if (data == NULL || SFI == NULL)
	{
		return ERROR;
	}
	
	// ��һ���ֽ�'6F'0
	// 6F
	if ('\x6f' != data[nTmpLen])
	{
		return ERROR;
	}

	// FCIģ�峤��1
	//15
	nTmpLen += 1;
	nFCILen = data[1];

	// һ���ֽ�'6F'2
	//84
	nTmpLen += 1;
	if ('\x84' != data[nTmpLen])
	{
		return ERROR;
	}

	// DF������3
	//0E
	nTmpLen += 1;
	nFCIPriLen = data[nTmpLen];

	// DF��4
	//315041592E5359532E4444463031
	nTmpLen += 1;
	memset(szFCIPri, 0, sizeof(szFCIPri));
	memcpy(szFCIPri, data + nTmpLen, nFCIPriLen);

	if (/* FCI�е�DF��=AID?*/)
	{

	}
	else
	{

	}

	// һ���ֽ� '\xA5'4+nFCIPriLen
	//A5
	nTmpLen += nFCIPriLen;
	if ('\xA5' != data[nTmpLen])
	{
		return ERROR;
	}

	// FCI����ר��ģ�峤��5+nFCIPriLen
	//03
	nTmpLen += 1;
	nFCINext = data[nTmpLen];

	// һ���ֽ�'\x88'6+nFCIPriLen
	//88
	nTmpLen += 1;
	if ('\x88' == data[nTmpLen])
	{
		//DDF
		// SFI���ݳ���
		//01
		nTmpLen += 1;
		nRecCount =  *(data + nTmpLen);
		// SF1
		//01
		nTmpLen += 1;
		*SFI = *(data + nTmpLen);
		/*SFI = *(data + nTmpLen) >> 3;
		*SFI &= 0x03;*/
		
		nTmpLen += 1;
		DebugOut("%d == %d\n", nOutLen, nTmpLen);
		if (nTmpLen != nOutLen)
		{
			return ERROR;
		}

		if (ERROR == GetDDFSFI(nSlot, nRecCount, SFI))
		{
			return ERROR;
		}
	}
	if ('\x50' == data[nTmpLen])
	{
		// ADF
	}

	return OK;
}
//��ȡAID����
int GetAidData(BYTE_PTR pAid, BYTE nLen)
{
	BYTE	SWA[3] = {0};
	BYTE	SWB[3] = {0};
	INT 	nOutLen = 0 ;
	BYTE	data[255] = {0};
	
	// ��պ�ѡ�б�
	if (ERROR == GetDFByName(pAid, nLen, SWA, SWB, data, &nOutLen))
	{
		return ERROR;
	}
	DebugOut("GetDFByName()\n");

	if (0 != strcmp(SWA, "90") || 0 != strcmp(SWB, "00"))
	{
		if (0 == strcmp(SWA, "61"))
		{
			memset(SWA, 0, sizeof(SWA));
			memset(data, 0, sizeof(data));
			nOutLen = 0;
			if (OK == GetResp(nSlot, SWA, SWB, nOutLen, data))
			{
				if (0 == strcmp(SWA, "90") || 0 == strcmp(SWB, "00"))
				{
					goto LABLE_SFI_DATA;
				}
			}
			
		}
		CloseCpuCard(nSlot);
		return ERROR;
	}
	
	LABLE_SFI_DATA:

	// ѭ����ȡ��¼������ӵ�ȫ�ֱ�����
	if (OK != AnalyAidData(nSlot, nOutLen, data, &SFI))
	{
		CloseCpuCard(nSlot);
		return ERROR;
	}
	return OK;
}

int Aid()
{
	
}
