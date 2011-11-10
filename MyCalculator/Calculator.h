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


//计算器类，内含有两个栈，一个存放运算数，一个存放运算符
class Calculator
{
protected:
	//存放计算结果
	double m_dResult;
	//存放运算数
	deque<double> m_dequeNumber;
	//存放运算符
	deque<OperationFactory::OPERATION> m_dequeOperator;
	//存放左括号右边第一个计算数在m_dequeNumber中的索引，因为存在括号嵌套，所以使用vector
	vector< vector<int>::size_type > m_vecIndexDequeNumber;
	//存放左括号右边第一个计算符在m_dequeNumber中的索引，因为存在括号嵌套，所以使用vector
	vector< vector<int>::size_type > m_vecIndexDequeOperator;
	//存放错误信息
	string m_strErrorInfo;
	//运算符类厂
	OperationFactory m_opFac;
	//存放中间值
	double m_dIndirectValue;

public:
	Calculator():m_dResult(0.0), m_dIndirectValue(0.0), m_strErrorInfo("")
	{
	}
	//将计算数存放在m_dequeNumber中
	void PushNumber(double num);
	//将计算符存放在m_dequeOperator中
	void PushOperator(OperationFactory::OPERATION op);

	//获取错误信息
	string& GetErrorInfo(void);
	//将参数中的两个数字和一个运算符进行运算，返回结果
	double Calculate(double numA, double numB, OperationFactory::OPERATION op);
	//清空
	void Clear(void);
	//得到结果
	double GetResult(void);
	//得到中间值，即deque的尾部值
	double GetIndirectValue(void);
	//设置中间值
	void SetIndirectValue(void);
};

#endif
