/*
	*filename: OperationFactory.h
	*abstract:	declaration of class OperationFactory
	*version:	1.0
	*powered by twan
*/

#ifndef _OPERATION_FACTORY_H_
#define _OPERATION_FACTORY_H_

#include "Operation.h"
#include <string>

using std::string;

//������೧
class OperationFactory
{
public:
	//OPERATION Ϊ���ݸ�CreateOperation�����Ĳ���������ȷ������ʲô�������ָ��
	enum OPERATION {OPER_ADD, OPER_SUB, OPER_MUL, OPER_DIV, OPER_LBRACKET, OPER_RBRACKET, OPER_EQUAL};
	Operation* CreateOperation(OPERATION op, double numA, double numB);
};

#endif