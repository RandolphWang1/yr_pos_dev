#include"Main.h"
int ReadCardNo(int nSlot)
{
	int nRet;
        int  i = 0;
        APDU_SEND ApduSend;
        APDU_RESP ApduRecv;
        char szBuff[128] = {0};// ��ʱ�ӹ�APDU
        int  nLength = 0x00; // ��ʱ�ӹ�APDU
        //char szBuffTemp[1024] = {0}; // ���ݷ��ʹ���
        char chLength = 0x00;// APDU�ڲ�ʹ��
	//UINT uiLen = 0;
	//UINT uiLenTemp = 0;
//////////////////////////////////////////////////////////////////////////////
//�����û�������Ϣ
        printf("*******************��ȡ�û���3F00��Ϣ***********\n");
        memset(szBuff, 0, sizeof(szBuff));
        nLength = 0;
        nRet = Select(&ApduSend, 0x00, 0x00, 2, "\x3f\x00");
        if (nRet == ERROR)
        {
                APDU_S_Free(&ApduSend);
                return ERROR;
        }
        nRet = APDU_R_Malloc(&ApduRecv, 128);
	nRet = IccIsoCommand(nSlot, &ApduSend, &ApduRecv);
        APDU_S_Free(&ApduSend);
        printf("nRet=[%d]\n", nRet);
        printf("\nApduRecv.SWA=%02X\n", ApduRecv.SWA );
        printf("ApduRecv.SWB=%02X\n", ApduRecv.SWB );
        if(nRet == 0)
        {
                printf("ApduRecv.LenOut=%d\n", ApduRecv.LenOut);

                for(i=0; i<ApduRecv.LenOut; i++)
                        printf("%02X ", ApduRecv.DataOut[i] );

                if(ApduRecv.SWA != 0x90 || ApduRecv.SWB != 0x00)
                {
                        if(ApduRecv.SWA == 0x61)
                        {
                                chLength = ApduRecv.SWB;
                                APDU_R_Free(&ApduRecv);
                                nRet = GetResponse(&ApduSend, chLength);
                                if (nRet == ERROR)
                                {
                                        APDU_S_Free(&ApduSend);
                                        return ERROR;
                                }
                                nRet = APDU_R_Malloc(&ApduRecv, 128);
				nRet = IccIsoCommand(nSlot, &ApduSend, &ApduRecv);
                                APDU_S_Free(&ApduSend);
                                printf("nRet=[%d]\n", nRet);
                                printf("\nApduRecv.SWA=%02X\n", ApduRecv.SWA );
                                printf("ApduRecv.SWB=%02X\n", ApduRecv.SWB );
                                if(nRet == 0)
                                {
                                        printf("ApduRecv.LenOut=%d\n", ApduRecv.LenOut );

                                        for(i=0; i<ApduRecv.LenOut; i++)
                                                printf("%02X ", ApduRecv.DataOut[i] );
                                        if(ApduRecv.SWA != 0x90 || ApduRecv.SWB != 0x00)
                                        {
                                                goto LABLE_FAIL;
                                        }
                                        else
                                        {
                                                memcpy(szBuff, ApduRecv.DataOut, ApduRecv.LenOut);
                                                nLength = ApduRecv.LenOut;
                                                APDU_R_Free(&ApduRecv);
                                                printf("Select MF SUCCESS!\n");
                                        }

                                }
                                else
                                {
                                        goto LABLE_FAIL;
                                }
                        }
                        else
                        {
                                goto LABLE_FAIL;
                        }
                }
                else
                {
                        memcpy(szBuff, ApduRecv.DataOut, ApduRecv.LenOut);
                        nLength = ApduRecv.LenOut;
                	APDU_R_Free(&ApduRecv);
            		printf("Select MF SUCCESS!\n");
                }
        }
        else
        {
                goto LABLE_FAIL;
        }
//////////////////////////////////////////////////////////////////////////////
//�����û�������Ϣ
        printf("*******************��ȡ�û���DDF01��Ϣ***********\n");
        memset(szBuff, 0, sizeof(szBuff));
        nLength = 0;
        nRet = Select(&ApduSend, 0x04, 0x00, 14, "1PAY.SYS.DDF01");
        if (nRet == ERROR)
        {
                APDU_S_Free(&ApduSend);
                return ERROR;
        }
        nRet = APDU_R_Malloc(&ApduRecv, 128);
	nRet = IccIsoCommand(nSlot, &ApduSend, &ApduRecv);
        APDU_S_Free(&ApduSend);
        printf("nRet=[%d]\n", nRet);
        printf("\nApduRecv.SWA=%02X\n", ApduRecv.SWA );
        printf("ApduRecv.SWB=%02X\n", ApduRecv.SWB );
        if(nRet == 0)
        {
                printf("ApduRecv.LenOut=%d\n", ApduRecv.LenOut);

                for(i=0; i<ApduRecv.LenOut; i++)
                        printf("%02X ", ApduRecv.DataOut[i] );

                if(ApduRecv.SWA != 0x90 || ApduRecv.SWB != 0x00)
                {
                        if(ApduRecv.SWA == 0x61)
                        {
                                chLength = ApduRecv.SWB;
                                APDU_R_Free(&ApduRecv);
                                nRet = GetResponse(&ApduSend, chLength);
                                if (nRet == ERROR)
                                {
                                        APDU_S_Free(&ApduSend);
                                        return ERROR;
                                }
                                nRet = APDU_R_Malloc(&ApduRecv, 128);
				nRet = IccIsoCommand(nSlot, &ApduSend, &ApduRecv);
                                APDU_S_Free(&ApduSend);
                                printf("nRet=[%d]\n", nRet);
                                printf("\nApduRecv.SWA=%02X\n", ApduRecv.SWA );
                                printf("ApduRecv.SWB=%02X\n", ApduRecv.SWB );
                                if(nRet == 0)
                                {
                                        printf("ApduRecv.LenOut=%d\n", ApduRecv.LenOut );

                                        for(i=0; i<ApduRecv.LenOut; i++)
                                                printf("%02X ", ApduRecv.DataOut[i] );
                                        if(ApduRecv.SWA != 0x90 || ApduRecv.SWB != 0x00)
                                        {
                                                goto LABLE_FAIL;
                                        }
                                        else
                                        {
                                                memcpy(szBuff, ApduRecv.DataOut, ApduRecv.LenOut);
                                                nLength = ApduRecv.LenOut;
                                                APDU_R_Free(&ApduRecv);
                                                printf("Select MF SUCCESS!\n");
                                        }

                                }
                                else
                                {
                                        goto LABLE_FAIL;
                                }
                        }
                        else
                        {
                                goto LABLE_FAIL;
                        }
                }
                else
                {
                        memcpy(szBuff, ApduRecv.DataOut, ApduRecv.LenOut);
                        nLength = ApduRecv.LenOut;
                	APDU_R_Free(&ApduRecv);
            		printf("Select MF SUCCESS!\n");
                }
        }
        else
        {
                goto LABLE_FAIL;
        }

	return 0;
LABLE_FAIL:
	return ERROR;
}
