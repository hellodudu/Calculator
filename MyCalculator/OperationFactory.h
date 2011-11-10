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

//运算符类厂
class OperationFactory
{
public:
	//OPERATION 为传递给CreateOperation函数的参数，用来确定生成什么运算符的指针
	enum OPERATION {OPER_ADD, OPER_SUB, OPER_MUL, OPER_DIV, OPER_LBRACKET, OPER_RBRACKET, OPER_EQUAL};
	Operation* CreateOperation(OPERATION op, double numA, double numB);
};

#endif