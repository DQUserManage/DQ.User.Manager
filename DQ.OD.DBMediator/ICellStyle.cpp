#include "stdafx.h"
#include "ICellStyle.h"


CICellStyle::CICellStyle(void)
{
}


CICellStyle::~CICellStyle(void)
{
}

/** ˮƽ���У�1��ࡢ2�Ҳࡢ�������� */
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
/** ��ֱ���У�1�ϡ�2�¡��������� */
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
/** �߿�Ӵ� */
void	CICellStyle::BorderBold()
{
	m_ICellStyle->BorderTop = BorderStyle::Thin;    
	m_ICellStyle->BorderBottom = BorderStyle::Thin;  
	m_ICellStyle->BorderLeft = BorderStyle::Thin;  
	m_ICellStyle->BorderRight = BorderStyle::Thin;
}