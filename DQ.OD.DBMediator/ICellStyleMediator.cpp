#include "stdafx.h"
#include "ICellStyleMediator.h"
#include "ICellStyle.h"


CICellStyleMediator::CICellStyleMediator(void)
{
}


CICellStyleMediator::~CICellStyleMediator(void)
{
	if (m_pCellStyle)
		delete m_pCellStyle;
}

/** ˮƽ���У�1��ࡢ2�Ҳࡢ�������� */
void	CICellStyleMediator::HorizontalStyle(int iVal)
{
	m_pCellStyle->HorizontalStyle(iVal);
}
/** ��ֱ���У�1�ϡ�2�¡��������� */
void	CICellStyleMediator::VerticalStyle(int iVal)
{
	m_pCellStyle->VerticalStyle(iVal);
}
/** �߿�Ӵ� */
void	CICellStyleMediator::BorderBold()
{
	m_pCellStyle->BorderBold();
}