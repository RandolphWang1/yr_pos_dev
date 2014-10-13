//////////////////////////////////////////////////////////////////////////////
//20120413
//ymm
//////////////////////////////////////////////////////////////////////////////

#include <Main.h>

//////////////////////////////////////////////////////////////////////////////
int Support();
int SupportSelectApp();
int SelectApp(BYTE_PTR pNum);
int SupportAckApp();
int AckApp();
int Enable();
int TopApp(BYTE_PTR pNum);
int SendSelect(BYTE nNum);
int DeleteApp(BYTE nNum);
//============================================================================
// Ӧ��ѡ��
int AppSelect()
{
	INT nNum = 0 ;

	while(1)
	{
		// �Ƿ�˫����֧�ֵ�Ӧ��
		if (ERROR == Support())
		{
			// ��ֹ����
			return ERROR;
		}
		// �ն��Ƿ�֧�ֳֿ���ѡ��Ӧ��
		if (ERROR != SupportSelectApp())
		{
			// ��ʾӦ��
			// ѡ��Ӧ��
			if (ERROR == SelectApp(&nNum))
			{
				// ��ֹ����
				return ERROR;
			}
			// ����SELECT����
			goto LABLE_SELECT;
		}
		
		// �ն��Ƿ�֧�ֳֿ���ȷ��Ӧ��
		if (ERROR != SupportAckApp())
		{
			// ��ʾ��߼���Ӧ��
			// ȷ��Ӧ��
			if (ERROR == AckApp())
			{
				// �Ƴ�Ӧ��
				DeleteApp(nNum);
				continue;
			}	
			// ����SELECT����
			goto LABLE_SELECT;
		}

		// Ӧ��û��ȷ��,�Ƿ�����ѡ��
		if (ERROR == Enable())
		{
			// ��ֹ����
			return ERROR;
		}
		// ��ʾ��߼���Ӧ��
		// ��߼����Ӧ������ȷ��Ӧ��
		TopApp(&nNum);

	LBALE_SELECT:
		// SendSelect
		if (ERROR == SendSelect(nNum))
		{
			// �Ƴ�Ӧ��
			DeleteApp(nNum);
			continue;
		}
		
		break;
	}

	return OK;
}

//////////////////////////////////////////////////////////////////////////////

int GetProOpt();
int AnalyGPOData();
//============================================================================
int AppInit()
{
	// �����Ƿ�����
	if (ERROR == GetProOpt())
	{
		DeleteApp(nNum);
		// ����Ӧ���б�	
		return ERROR;
	}
	
	if (ERROR == AnalyGPOData())
	{
		return ERROR;
	}
	return OK;
}

//////////////////////////////////////////////////////////////////////////////

//============================================================================
int ReadAppData()
{
	// �ն˴�AFL��ѡ���һ���ļ����
	if (ERROR == OptFile())
	{
		return ERROR;
	}
	
	LABLE_MID:
	if (ERROR == ReadFileRecord())
	{
		return ERROR
	}

	if (ERROR != SDA())
	{
		InputSDAData();
	}

	if (ERROR == TellEndItem())
	{
		goto LABLE_MID;
	}

	if (ERROR != OtherEnter())
	{
		OptEnterNext();
		goto LABLE_MID;
	}

	return OK;
}

//////////////////////////////////////////////////////////////////////////////

//============================================================================
int DA(BYTE_PTR tvr)
{
	// ͨ��ʹ��RID��PKI
	if (ERROR == GetPKByCA())
	{
		goto LABLE_DA;
	}
	
	// ʹ��PK��SAD��ȡ����
	if (ERROR == GetHashBySAD())
	{
		goto LABLE_DA;
	}
	// Compare hash
	if (ERROR == ComHashValue())
	{
		goto LABLE_DA;
	}

	return OK;
	
	LABLE_DA:
		*tvr == 1;
		return ERROR;
}
//////////////////////////////////////////////////////////////////////////////

//============================================================================
int ProLimit(BYTE_PTR tvr)
{
	if (ERROR == AppVerNum())
	{
		goto LABLE_NEXT;
	}

	if (ERROR == CompVerNum())
	{
		*tvr = 1;
	}
	
LABLE_NEXT:
	if (ERROR != AppCode())
	{
		if (ERROR == Limit())
		{
			*tvr = 1;
		}
	}

	if (ERROR == ableDate())
	{
			*tvr = 1;
	}

	if (ERROR == EnableDate())
	{
			*tvr = 1;
	}
	
	return OK;			
}

//////////////////////////////////////////////////////////////////////////////

//============================================================================
int Cardholder()
{
	if (ERROR == CardSupport())
	{
		
	}
	
}

