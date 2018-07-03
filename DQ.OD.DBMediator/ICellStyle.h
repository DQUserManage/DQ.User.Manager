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
	/** ˮƽ���У�1��ࡢ2�Ҳࡢ�������� */
	void	HorizontalStyle(int iVal);
	/** ��ֱ���У�1�ϡ�2�¡��������� */
	void	VerticalStyle(int iVal);
	/** �߿�Ӵ� */
	void	BorderBold();
	/**  */
	/**  */
	/**  */
};

