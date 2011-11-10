/*
	*filename: Operation.h
	*abstract:	declaration of class Operation, OperationAdd, OperationSub, OperationMul, OperationDiv
	*version:	1.0
	*powered by twan
*/

#ifndef _OPERATION_H_
#define _OPERATION_H_

//运算符基类
class Operation
{
protected:
	//运算的两个操作数
	double m_dNumberA;
	double m_dNumberB;
public:
	virtual ~Operation(void) {}
	//返回运算结果
	virtual double GetResult(void) = 0;
};

//加法类
class OperationAdd : public Operation
{
public:
	OperationAdd(double numA, double numB);
	//返回运算结果
	virtual double GetResult(void);
};

//减法类
class OperationSub : public Operation
{
public:
	OperationSub(double numA, double numB);
	//返回运算结果
	virtual double GetResult(void);
};

//乘法类
class OperationMul : public Operation
{
public:
	OperationMul(double numA, double numB);
	//返回运算结果
	virtual double GetResult(void);
};

//除法类
class OperationDiv : public Operation
{
public:
	OperationDiv(double numA, double numB);
	//返回运算结果
	virtual double GetResult(void);
};

#endif