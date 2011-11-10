/*
	*filename:	Calculator.h
	*abstract:	declaration of class Calculator
	*version:	1.0
	*powered by twan
*/

#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <string>
#include <vector>
#include <deque>

#include "OperationFactory.h"

using std::string;
using std::vector;
using std::deque;


//�������࣬�ں�������ջ��һ�������������һ����������
class Calculator
{
protected:
	//��ż�����
	double m_dResult;
	//���������
	deque<double> m_dequeNumber;
	//��������
	deque<OperationFactory::OPERATION> m_dequeOperator;
	//����������ұߵ�һ����������m_dequeNumber�е���������Ϊ��������Ƕ�ף�����ʹ��vector
	vector< vector<int>::size_type > m_vecIndexDequeNumber;
	//����������ұߵ�һ���������m_dequeNumber�е���������Ϊ��������Ƕ�ף�����ʹ��vector
	vector< vector<int>::size_type > m_vecIndexDequeOperator;
	//��Ŵ�����Ϣ
	string m_strErrorInfo;
	//������೧
	OperationFactory m_opFac;
	//����м�ֵ
	double m_dIndirectValue;

public:
	Calculator():m_dResult(0.0), m_dIndirectValue(0.0), m_strErrorInfo("")
	{
	}
	//�������������m_dequeNumber��
	void PushNumber(double num);
	//������������m_dequeOperator��
	void PushOperator(OperationFactory::OPERATION op);

	//��ȡ������Ϣ
	string& GetErrorInfo(void);
	//�������е��������ֺ�һ��������������㣬���ؽ��
	double Calculate(double numA, double numB, OperationFactory::OPERATION op);
	//���
	void Clear(void);
	//�õ����
	double GetResult(void);
	//�õ��м�ֵ����deque��β��ֵ
	double GetIndirectValue(void);
	//�����м�ֵ
	void SetIndirectValue(void);
};

#endif
