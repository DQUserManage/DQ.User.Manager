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
	/** ˮƽ���У�1��ࡢ2�Ҳࡢ�������� */
	void	HorizontalStyle(int iVal);
	/** ��ֱ���У�1�ϡ�2�¡��������� */
	void	VerticalStyle(int iVal);
	/** �߿�Ӵ� */
	void	BorderBold();
};

