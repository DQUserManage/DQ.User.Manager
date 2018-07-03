#include "stdafx.h"
#include "IRow.h"
#include "ICellStyle.h"

using namespace System::Text;

void	SplitCStr(vector<CString>& vStr, CString sData, CString sSplitFlag, BOOL bSequenceAsOne)
{
	sData.Replace(L"\t", L" ");			//tab键也处理为空格
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
			if (!sTemp.IsEmpty() && sTemp != "") ////连续的分隔符视为单个处理
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

/** 创建Cell */
int		CIRow::CreateCell(int iIndex, CellDataType eType)
{
	m_IRow->CreateCell(iIndex, (CellType)eType);
	return iIndex;
}
/** 设置Cell值 */
void	CIRow::SetCellStringVal(int iIndex, CString &sVal)
{
	//if (iIndex < m_IRow->Cells->Count)
		m_IRow->GetCell(iIndex)->SetCellValue(gcnew System::String(sVal));
}
/** 设置Cell值 */
void	CIRow::SetCellfloatVal(int iIndex, double &fVal)
{
	//if (iIndex < m_IRow->Cells->Count)
		m_IRow->GetCell(iIndex)->SetCellValue(fVal);
}
/** 设置Cell值（带换行风格） */
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
/** 获取Cell值 */
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
/** 设置Cell风格 */
void	CIRow::SetCellStyle(int iIndex, CICellStyle *pStyle)
{
	//if (iIndex < m_IRow->Cells->Count)
		m_IRow->GetCell(iIndex)->CellStyle = pStyle->m_ICellStyle;
}
/** 获取总列数 */
int		CIRow::GetColCount()
{
	return m_IRow->LastCellNum;
}
/** 获取第一个Cell索引 */
int		CIRow::GetFirstIndex()
{
	return m_IRow->FirstCellNum;
}