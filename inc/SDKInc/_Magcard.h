#ifndef __MAGCARD_H_
#define __MAGCARD_H_

#define	TRACK1_OK	0x0001
#define	TRACK2_OK	0x0002
#define	TRACK3_OK	0x0004


/*
 * function	:	�򿪶�����
 * param1	:	
 */
int MagOpen();

/*
 * function	:	�رն�����
 * param1	:	
 */
void MagClose();

/*
 * function	:	����
 * param1	:	
 */
int MagRead(int *track1_len,char *track1,int *track2_len,char *track2,int *track3_len,char *track3);


#endif
