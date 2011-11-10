/*
	*filename: Operation.cpp
	*abstract:	definition of class Operation, OperationAdd, OperationSub, OperationMul, OperationDiv
	*version:	1.0
	*powered by twan
*/

#include "Operation.h"
#include <assert.h>

OperationAdd::OperationAdd(double numA, double numB)
{
	m_dNumberA = numA;
	m_dNumberB = numB;
}

double OperationAdd::GetResult(void)
{
	return m_dNumberA + m_dNumberB;
}



OperationSub::OperationSub(double numA, double numB)
{
	m_dNumberA = numA;
	m_dNumberB = numB;
}

double OperationSub::GetResult(void)
{
	return m_dNumberA - m_dNumberB;
}


OperationMul::OperationMul(double numA, double numB)
{
	m_dNumberA = numA;
	m_dNumberB = numB;
}

double OperationMul::GetResult(void)
{
	return m_dNumberA * m_dNumberB;
}


OperationDiv::OperationDiv(double numA, double numB)
{
	m_dNumberA = numA;
	m_dNumberB = numB;
}

double OperationDiv::GetResult(void)
{
	//除数不能为0
	assert(m_dNumberB >= 0.000001 || m_dNumberB <= -0.000001);
	return m_dNumberA / m_dNumberB;
}