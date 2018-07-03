#include "stdafx.h"
#include "ICellStyle.h"


CICellStyle::CICellStyle(void)
{
}


CICellStyle::~CICellStyle(void)
{
}

/** 水平居中：1左侧、2右侧、其他居中 */
void	CICellStyle::HorizontalStyle(int iVal)
{
	switch (iVal)
	{
	case 1:
		m_ICellStyle->Alignment = HorizontalAlignment::Left;
		break;
	case 2:
		m_ICellStyle->Alignment = HorizontalAlignment::Right;
		break;
	default:
		m_ICellStyle->Alignment = HorizontalAlignment::Center;
		break;
	}
}
/** 垂直居中：1上、2下、其他居中 */
void	CICellStyle::VerticalStyle(int iVal)
{
	switch (iVal)
	{
	case 1:
		m_ICellStyle->VerticalAlignment = VerticalAlignment::Top;
		break;
	case 2:
		m_ICellStyle->VerticalAlignment = VerticalAlignment::Bottom;
		break;
	default:
		m_ICellStyle->VerticalAlignment = VerticalAlignment::Center;
		break;
	}
}
/** 边框加粗 */
void	CICellStyle::BorderBold()
{
	m_ICellStyle->BorderTop = BorderStyle::Thin;    
	m_ICellStyle->BorderBottom = BorderStyle::Thin;  
	m_ICellStyle->BorderLeft = BorderStyle::Thin;  
	m_ICellStyle->BorderRight = BorderStyle::Thin;
}