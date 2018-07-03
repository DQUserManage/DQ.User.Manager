#include "stdafx.h"
#include "IRow.h"
#include "ICellStyle.h"

using namespace System::Text;

void	SplitCStr(vector<CString>& vStr, CString sData, CString sSplitFlag, BOOL bSequenceAsOne)
{
	sData.Replace(L"\t", L" ");			//tab��Ҳ����Ϊ�ո�
	vStr.clear();
	if (sData.Right(1) != sSplitFlag) sData += sSplitFlag;

	CString sTemp;
	int pos = -1;
	while ((pos = sData.Find(sSplitFlag, 0)) != -1)
	{
		sTemp = sData.Left(pos);

		if (bSequenceAsOne)
		{
			vStr.push_back(sTemp);
		}
		else
		{
			if (!sTemp.IsEmpty() && sTemp != "") ////�����ķָ�����Ϊ��������
			{
				vStr.push_back(sTemp);
			}
		}
		sData = sData.Right(sData.GetLength() - pos - 1);
	}
}


CIRow::CIRow()
{
}


CIRow::~CIRow(void)
{
}

/** ����Cell */
int		CIRow::CreateCell(int iIndex, CellDataType eType)
{
	m_IRow->CreateCell(iIndex, (CellType)eType);
	return iIndex;
}
/** ����Cellֵ */
void	CIRow::SetCellStringVal(int iIndex, CString &sVal)
{
	//if (iIndex < m_IRow->Cells->Count)
		m_IRow->GetCell(iIndex)->SetCellValue(gcnew System::String(sVal));
}
/** ����Cellֵ */
void	CIRow::SetCellfloatVal(int iIndex, double &fVal)
{
	//if (iIndex < m_IRow->Cells->Count)
		m_IRow->GetCell(iIndex)->SetCellValue(fVal);
}
/** ����Cellֵ�������з�� */
void	CIRow::SetCellValByWrap(int iIndex, CString &sVal)
{
	ICell^ pCell = m_IRow->GetCell(iIndex);
	vector<CString> vRes;
	SplitCStr(vRes, sVal, L"\n", FALSE);
	if (vRes.size() <= 1)
	{
		pCell->CellStyle->WrapText = false;
		pCell->CellStyle->VerticalAlignment = VerticalAlignment::Center;
		pCell->SetCellValue(gcnew System::String(sVal));
	} 
	else
	{
		pCell->CellStyle->WrapText = true;
		pCell->CellStyle->VerticalAlignment = VerticalAlignment::Top;
		StringBuilder^ noteString = gcnew StringBuilder(gcnew System::String(vRes[0] + L"\n"));
		for (int i = 1; i < (int)vRes.size(); i++)
			noteString->Append(gcnew System::String(vRes[i] + L"\n"));
		pCell->SetCellValue(noteString->ToString());
	}
}
/** ��ȡCellֵ */
CString	CIRow::GetCellVal(int iIndex)
{
	//if (iIndex >= m_IRow->Cells->Count)
	//	return L"";
	ICell ^ cell = m_IRow->GetCell(iIndex);
	if (cell == nullptr)
		return L"";
	if (cell->CellType == NPOI::SS::UserModel::CellType::Formula)
	{
		if (cell->CachedFormulaResultType == NPOI::SS::UserModel::CellType::Numeric)
			return CString(System::Convert::ToString(cell->NumericCellValue));
		else if (cell->CachedFormulaResultType == NPOI::SS::UserModel::CellType::String)
			return CString(cell->StringCellValue->ToString());
	}
	return CString(cell->ToString());
}
/** ����Cell��� */
void	CIRow::SetCellStyle(int iIndex, CICellStyle *pStyle)
{
	//if (iIndex < m_IRow->Cells->Count)
		m_IRow->GetCell(iIndex)->CellStyle = pStyle->m_ICellStyle;
}
/** ��ȡ������ */
int		CIRow::GetColCount()
{
	return m_IRow->LastCellNum;
}
/** ��ȡ��һ��Cell���� */
int		CIRow::GetFirstIndex()
{
	return m_IRow->FirstCellNum;
}