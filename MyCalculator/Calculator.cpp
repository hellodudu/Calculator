/*
	*filename: Calculator.cpp
	*abstract:	definition of class Calculator
	*version:	1.0
	*powered by twan
*/

#include "Calculator.h"

//��ȡ������Ϣ
string& Calculator::GetErrorInfo(void)
{
	return m_strErrorInfo;
}

//�������������m_dequeNumber��
void Calculator::PushNumber(double num)
{
	m_dequeNumber.push_back(num);
}

//������������m_dequeOperator��
void Calculator::PushOperator(OperationFactory::OPERATION op)
{

	//�жϼ�����������Ԫ���Ƿ�ֻ��һ���������ջ��û��Ԫ�أ��������ֱ�ӽ�op�������������
	if (m_dequeNumber.size() == 1 && m_dequeOperator.empty())
	{
		m_dequeOperator.push_back(op);
		//�����м�ֵ
		SetIndirectValue();
		return;
	}

	//�ж��Ƿ�Ϊ���ں�
	if (op == OperationFactory::OPER_EQUAL)
	{
		/*
			�����Ҫ���������ķ����ǵ��ںŵĻ���ô���������ѭ��������ȡ����
			������������Ԫ�غ������������һ��Ԫ�أ����������Ľ���ٴδ�
			������������ڣ�ֱ��������������Ԫ��ֻʣ��һ�������������Ľ�
			�������������������ʱ��������������Ԫ�ظ���Ϊ1�������������Ԫ��
			����Ϊ0
		*/
		while (m_dequeNumber.size() != 1 && !m_dequeOperator.empty())
		{
			double numB = m_dequeNumber.back();
			m_dequeNumber.pop_back();
			double numA = m_dequeNumber.back();
			m_dequeNumber.pop_back();

			OperationFactory::OPERATION oper = m_dequeOperator.back();
			m_dequeOperator.pop_back();
			double result = Calculate(numA, numB, oper);
			m_dequeNumber.push_back(result);
		}
		m_dResult = m_dequeNumber.back();
		//�����м�ֵ
		SetIndirectValue();
		return;
	}

	//�ж��Ƿ�Ϊ����
	if (op == OperationFactory::OPER_LBRACKET || op == OperationFactory::OPER_RBRACKET)
	{
		if (op == OperationFactory::OPER_LBRACKET)
		{
			/*
				����������ţ��������ұ���ĵ�һ���������������λ�õ�����
				��ŵ�m_itDequeNumberBracket��m_itDequeOperatorBracket����
				������ʸ��������
			*/
			m_vecIndexDequeNumber.push_back(m_dequeNumber.size()-1);
			m_vecIndexDequeOperator.push_back(m_dequeOperator.size()-1);
			//�����м�ֵ
			SetIndirectValue();
			return;
		}
		if (op == OperationFactory::OPER_RBRACKET)
		{
			/*
				����������ţ�����Ҫ���ж�ǰ���Ƿ���ֹ������ţ����û������
				�κβ�������������ȼ���������ڵ�ֵ�������������m_dequeNumber��
			*/
			if (m_vecIndexDequeNumber.empty())
			{
				//�����м�ֵ
				SetIndirectValue();
				return;
			}
			else
			{
				/*
					����������һ�������ڵ�ֵ
				*/
				vector< vector<int>::size_type >::size_type numIndex;
				vector< vector<int>::size_type >::size_type opIndex;

				/*
					ѭ�����������ڵ�ֵ��ѭ������������numIndex����ָ�����������ǰ��һ������
				*/
				while ( ( (numIndex=m_dequeNumber.size()-1) != m_vecIndexDequeNumber.back() ) && 
					( (opIndex=m_dequeOperator.size()-1) != m_vecIndexDequeOperator.back() ) )
				{
					double numB = m_dequeNumber[numIndex];
					double numA = m_dequeNumber[numIndex-1];

					OperationFactory::OPERATION oper = m_dequeOperator[opIndex];
					double result = Calculate(numA, numB, oper);
					//�Ƴ��Ѿ����������������һ������
					m_dequeNumber.pop_back();
					m_dequeNumber.pop_back();
					m_dequeOperator.pop_back();
					//������������m_dequeNumber��
					m_dequeNumber.push_back(result);
					//����index
					numIndex -= 2;
					--opIndex;
				}
				//ɾ���Ѿ����������������λ��
				m_vecIndexDequeNumber.pop_back();
				m_vecIndexDequeOperator.pop_back();
				//�����м�ֵ
				SetIndirectValue();
				return;
			}
		}
	}

	//��������������ж��Ƿ�Ϊ�˳���
	if (op == OperationFactory::OPER_MUL || op == OperationFactory::OPER_DIV)
	{
		/*	
			�����ǰҪ���������ķ����ǳ˳��ţ�������β���ķ����ǼӼ��ţ���
			��Ϊ�˳������ȼ��󽫵�ǰ������������������������У��ȴ���
			��������Ĵ�������Ž��м���
		*/
		if (m_dequeOperator.back() <= OperationFactory::OPER_SUB)
		{
			m_dequeOperator.push_back(op);
			//�����м�ֵ
			SetIndirectValue();
			return;
		}
	}

	/*
		������������ڵĵ�һ���������ֱ�Ӵ���m_dequeOperator��
		������2+���ġ�+�������ֱ�Ӵ������������
	*/
	if ( !(m_vecIndexDequeOperator.empty()) && 
		(m_vecIndexDequeOperator.back() == m_dequeOperator.size()-1) )
	{
		m_dequeOperator.push_back(op);
		//�����м�ֵ
		SetIndirectValue();
		return;
	}

	/*
		ʣ�µ���������ڽ�op���������������֮ǰ����ȡ�����������ڵ�����Ԫ��
		������������ڵ�һ��Ԫ�ؽ���������ٽ������������������ڣ����ҽ�
		��ǰ�����op����m_dequeOperator��
	*/
	if (m_dequeOperator.empty())
		return;
	double numB = m_dequeNumber.back();
	m_dequeNumber.pop_back();
	double numA = m_dequeNumber.back();
	m_dequeNumber.pop_back();

	OperationFactory::OPERATION oper = m_dequeOperator.back();
	m_dequeOperator.pop_back();
	double result = Calculate(numA, numB, oper);
	m_dequeNumber.push_back(result);
	m_dequeOperator.push_back(op);

	//�����м�ֵ
	SetIndirectValue();
}

//�������е��������ֺ�һ��������������㣬���ؽ��
double Calculator::Calculate(double numA, double numB, OperationFactory::OPERATION op)
{
	Operation* pOper = m_opFac.CreateOperation(op, numA, numB);
	//���ǳ���Ϊ0�����
	if ( (op == OperationFactory::OPER_DIV) && 
		(numB <= 0.000001 && numB >= -0.000001) )
	{
		m_strErrorInfo = "��������Ϊ0��";
		return 0.0;
	}

	double rtval = pOper->GetResult();
	delete pOper;
	pOper = NULL;
	return rtval;
}

//���
void Calculator::Clear(void)
{
	m_dResult = 0.0;
	m_dIndirectValue = 0.0;
	m_dequeNumber.clear();
	m_dequeOperator.clear();
	m_strErrorInfo.clear();
}

//�õ����
double Calculator::GetResult(void)
{
	return m_dResult;
}

//�õ��м�ֵ����deque��β��ֵ
double Calculator::GetIndirectValue(void)
{
	return m_dIndirectValue;
}

//�����м�ֵ
void Calculator::SetIndirectValue(void)
{
	//�����м�ֵ
	if (!m_dequeNumber.empty())
	{
		m_dIndirectValue = m_dequeNumber.back();
	}
}