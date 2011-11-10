/*
	*filename: Operation.h
	*abstract:	declaration of class Operation, OperationAdd, OperationSub, OperationMul, OperationDiv
	*version:	1.0
	*powered by twan
*/

#ifndef _OPERATION_H_
#define _OPERATION_H_

//���������
class Operation
{
protected:
	//���������������
	double m_dNumberA;
	double m_dNumberB;
public:
	virtual ~Operation(void) {}
	//����������
	virtual double GetResult(void) = 0;
};

//�ӷ���
class OperationAdd : public Operation
{
public:
	OperationAdd(double numA, double numB);
	//����������
	virtual double GetResult(void);
};

//������
class OperationSub : public Operation
{
public:
	OperationSub(double numA, double numB);
	//����������
	virtual double GetResult(void);
};

//�˷���
class OperationMul : public Operation
{
public:
	OperationMul(double numA, double numB);
	//����������
	virtual double GetResult(void);
};

//������
class OperationDiv : public Operation
{
public:
	OperationDiv(double numA, double numB);
	//����������
	virtual double GetResult(void);
};

#endif