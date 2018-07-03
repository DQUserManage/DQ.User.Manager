/**
* @defgroup 
* @author   张宪顺
* @version  1.0
* @date     2017-03-15
* @{
*/


/**
* @file
* @brief
* @author   张宪顺
* @date     2017-03-15
* @version  1.0
* @note
* @{
*/
#pragma once
//#include <vcclr.h> 

class CParameterList;

/********************************************************************
* Copyright (C), 博雅仟恒软件技术（北京）有限公司
*
* 创 建 者： 张宪顺
* 创建日期： 2017-03-15
* 功能描述： 参数列表中介类
*
********************************************************************/
class AFX_EXT_CLASS CParameterListMediator
{
public:
	CParameterListMediator(void);
	CParameterListMediator(CParameterList *	pParameterList);
	~CParameterListMediator(void);

private:
	CParameterList *	m_pParameterList;	///<参数列表

public:	
	/** 获取参数列表 */
	CParameterList * GetParameterList() { return m_pParameterList; }
	/** 清空参数 */
	void		Clear();
	/** 获取参数个数 */
	int			GetCount();
	/** 添加参数 */
	void		AddParameter(CString mParameterName, COleVariant  mParameterValue);
	void		AddParameter(CString mParameterName, byte *pByte, int iByteSize);
};

/** @}*/
/** @}*/