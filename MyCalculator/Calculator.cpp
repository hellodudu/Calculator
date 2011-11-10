/*
	*filename: Calculator.cpp
	*abstract:	definition of class Calculator
	*version:	1.0
	*powered by twan
*/

#include "Calculator.h"

//获取错误信息
string& Calculator::GetErrorInfo(void)
{
	return m_strErrorInfo;
}

//将计算数存放在m_dequeNumber中
void Calculator::PushNumber(double num)
{
	m_dequeNumber.push_back(num);
}

//将计算符存放在m_dequeOperator中
void Calculator::PushOperator(OperationFactory::OPERATION op)
{

	//判断计算数容器内元素是否只有一个且运算符栈内没有元素，如果是则直接将op存入运算符容器
	if (m_dequeNumber.size() == 1 && m_dequeOperator.empty())
	{
		m_dequeOperator.push_back(op);
		//设置中间值
		SetIndirectValue();
		return;
	}

	//判断是否为等于号
	if (op == OperationFactory::OPER_EQUAL)
	{
		/*
			如果将要存入容器的符号是等于号的话那么输入结束，循环操作“取计算
			数容器内两个元素和运算符容器内一个元素，并将计算后的结果再次存
			入计算数容器内，直到计算数容器内元素只剩下一个”。计算最后的结
			果存入计算数容器，此时计算数中容器内元素个数为1，运算符容器内元素
			个数为0
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
		//设置中间值
		SetIndirectValue();
		return;
	}

	//判断是否为括号
	if (op == OperationFactory::OPER_LBRACKET || op == OperationFactory::OPER_RBRACKET)
	{
		if (op == OperationFactory::OPER_LBRACKET)
		{
			/*
				如果是左括号，则将括号右边起的第一个运算数和运算符位置迭代器
				存放到m_itDequeNumberBracket和m_itDequeOperatorBracket两个
				迭代器矢量容器中
			*/
			m_vecIndexDequeNumber.push_back(m_dequeNumber.size()-1);
			m_vecIndexDequeOperator.push_back(m_dequeOperator.size()-1);
			//设置中间值
			SetIndirectValue();
			return;
		}
		if (op == OperationFactory::OPER_RBRACKET)
		{
			/*
				如果是右括号，则需要先判断前面是否出现过左括号，如果没有则不做
				任何操作，如果有则先计算出括号内的值，并将结果放入m_dequeNumber中
			*/
			if (m_vecIndexDequeNumber.empty())
			{
				//设置中间值
				SetIndirectValue();
				return;
			}
			else
			{
				/*
					计算最后面的一对括号内的值
				*/
				vector< vector<int>::size_type >::size_type numIndex;
				vector< vector<int>::size_type >::size_type opIndex;

				/*
					循环计算括号内的值，循环结束条件是numIndex索引指向的是左括号前的一个数字
				*/
				while ( ( (numIndex=m_dequeNumber.size()-1) != m_vecIndexDequeNumber.back() ) && 
					( (opIndex=m_dequeOperator.size()-1) != m_vecIndexDequeOperator.back() ) )
				{
					double numB = m_dequeNumber[numIndex];
					double numA = m_dequeNumber[numIndex-1];

					OperationFactory::OPERATION oper = m_dequeOperator[opIndex];
					double result = Calculate(numA, numB, oper);
					//移除已经计算过的两个数和一个符号
					m_dequeNumber.pop_back();
					m_dequeNumber.pop_back();
					m_dequeOperator.pop_back();
					//将计算结果放入m_dequeNumber中
					m_dequeNumber.push_back(result);
					//调整index
					numIndex -= 2;
					--opIndex;
				}
				//删除已经计算完的括号索引位置
				m_vecIndexDequeNumber.pop_back();
				m_vecIndexDequeOperator.pop_back();
				//设置中间值
				SetIndirectValue();
				return;
			}
		}
	}

	//如果不是括号则判断是否为乘除号
	if (op == OperationFactory::OPER_MUL || op == OperationFactory::OPER_DIV)
	{
		/*	
			如果当前要存入容器的符号是乘除号，而容器尾部的符号是加减号，则
			因为乘除号优先级大将当前计算数和运算符都存入容器中，等待下
			次运算符的存入操作才进行计算
		*/
		if (m_dequeOperator.back() <= OperationFactory::OPER_SUB)
		{
			m_dequeOperator.push_back(op);
			//设置中间值
			SetIndirectValue();
			return;
		}
	}

	/*
		如果是在括号内的第一个运算符就直接存入m_dequeOperator，
		即“（2+”的“+”运算符直接存入运算符容器
	*/
	if ( !(m_vecIndexDequeOperator.empty()) && 
		(m_vecIndexDequeOperator.back() == m_dequeOperator.size()-1) )
	{
		m_dequeOperator.push_back(op);
		//设置中间值
		SetIndirectValue();
		return;
	}

	/*
		剩下的情况都是在将op存入运算符容器内之前先提取计算数容器内的两个元素
		和运算符容器内的一个元素进行运算后，再将结果存入计算数容器内，并且将
		当前运算符op存入m_dequeOperator中
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

	//设置中间值
	SetIndirectValue();
}

//将参数中的两个数字和一个运算符进行运算，返回结果
double Calculator::Calculate(double numA, double numB, OperationFactory::OPERATION op)
{
	Operation* pOper = m_opFac.CreateOperation(op, numA, numB);
	//考虑除数为0的情况
	if ( (op == OperationFactory::OPER_DIV) && 
		(numB <= 0.000001 && numB >= -0.000001) )
	{
		m_strErrorInfo = "除数不能为0！";
		return 0.0;
	}

	double rtval = pOper->GetResult();
	delete pOper;
	pOper = NULL;
	return rtval;
}

//清空
void Calculator::Clear(void)
{
	m_dResult = 0.0;
	m_dIndirectValue = 0.0;
	m_dequeNumber.clear();
	m_dequeOperator.clear();
	m_strErrorInfo.clear();
}

//得到结果
double Calculator::GetResult(void)
{
	return m_dResult;
}

//得到中间值，即deque的尾部值
double Calculator::GetIndirectValue(void)
{
	return m_dIndirectValue;
}

//设置中间值
void Calculator::SetIndirectValue(void)
{
	//设置中间值
	if (!m_dequeNumber.empty())
	{
		m_dIndirectValue = m_dequeNumber.back();
	}
}