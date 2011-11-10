/*
	*filename: OperationFactory.cpp
	*abstract:	definition of class OperationFactory
	*version:	1.0
	*powered by twan
*/

#include "OperationFactory.h"
#include <assert.h>

//�������������
Operation* OperationFactory::CreateOperation(OperationFactory::OPERATION op, double numA, double numB)
{
	//opΪ���ݽ�����ö�ٲ���������ȷ������ʲô������Ķ���ָ��
	Operation* pOper = NULL;

	switch(op)
	{
	case OPER_ADD:
		pOper = new OperationAdd(numA, numB);
		break;
	case OPER_SUB:
		pOper = new OperationSub(numA, numB);
		break;
	case OPER_MUL:
		pOper = new OperationMul(numA, numB);
		break;
	case OPER_DIV:
		pOper = new OperationDiv(numA, numB);
		break;
	default:
		//�����ܽ���˴�
		assert(0);
	}

	return pOper;
}