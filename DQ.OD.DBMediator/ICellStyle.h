#pragma once

using namespace NPOI;
using namespace NPOI::SS::UserModel;

class CICellStyle
{
public:
	CICellStyle(void);
	~CICellStyle(void);

public:
	gcroot<ICellStyle^>		m_ICellStyle;

public:
	/** 水平居中：1左侧、2右侧、其他居中 */
	void	HorizontalStyle(int iVal);
	/** 垂直居中：1上、2下、其他居中 */
	void	VerticalStyle(int iVal);
	/** 边框加粗 */
	void	BorderBold();
	/**  */
	/**  */
	/**  */
};

