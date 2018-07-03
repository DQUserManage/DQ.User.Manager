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

/** 水平居中：1左侧、2右侧、其他居中 */
void	CICellStyleMediator::HorizontalStyle(int iVal)
{
	m_pCellStyle->HorizontalStyle(iVal);
}
/** 垂直居中：1上、2下、其他居中 */
void	CICellStyleMediator::VerticalStyle(int iVal)
{
	m_pCellStyle->VerticalStyle(iVal);
}
/** 边框加粗 */
void	CICellStyleMediator::BorderBold()
{
	m_pCellStyle->BorderBold();
}