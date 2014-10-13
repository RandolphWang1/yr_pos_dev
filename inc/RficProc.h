/***************************************************************************
    Li,Hengbo
    2009-07-01
***************************************************************************/
#ifndef __RFIC_H_
#define __RFIC_H_


#define MODEKEYA    0
#define MODEKEYB    4 


int RficInit(int *piHandle);
void RficClose(int iHandle);
int RficDetect(int iHandle);
int RficOperate(int iHandle, int iBlock, unsigned long ulValue, int iMode);
int RficReadBlock(int iHandle, int iSector, int iBlock, char *outData);
int RficWriteBlock(int iHandle, int iSector, int iBlock, char *inData);
int SamCalcKey(int iSamInd, int iSelAB, int inLen, char *inData, int *outLen, char *outData);
int RficResetCpu(int iHandle);
int RficOperateCpu(int iHandle, APDU_SEND *ApduSend, APDU_RESP *ApduResp);


/*
 * ����������ԿA��B
 */
//��0����KeyAĬ����Կ
extern char gKeyA0[7];
//��1����KeyA��Կ
extern char gKeyA1[7];
//����Ǯ����������KeyA��KeyB��Կ
extern char gKeyA2[7], gKeyB2[7];
//���׼�¼��KeyA��KeyB��Կ
extern char gKeyA3[7], gKeyB3[7];


#endif

