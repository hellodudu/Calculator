/*
	*filename: OperationFactory.cpp
	*abstract:	definition of class OperationFactory
	*version:	1.0
	*powered by twan
*/

#include "OperationFactory.h"
#include <assert.h>

//创建运算符对象
Operation* OperationFactory::CreateOperation(OperationFactory::OPERATION op, double numA, double numB)
{
	//op为传递进来的枚举参数，用来确定生成什么运算符的对象指针
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
		//不可能进入此处
		assert(0);
	}

	return pOper;
}