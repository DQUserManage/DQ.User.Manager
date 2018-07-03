#pragma once

class CICellStyle;

class AFX_EXT_CLASS CICellStyleMediator
{
public:
	CICellStyleMediator(void);
	~CICellStyleMediator(void);

public:
	CICellStyle *		m_pCellStyle;

public:
	/** 水平居中：1左侧、2右侧、其他居中 */
	void	HorizontalStyle(int iVal);
	/** 垂直居中：1上、2下、其他居中 */
	void	VerticalStyle(int iVal);
	/** 边框加粗 */
	void	BorderBold();
};

