
#pragma once 

///                                                                            
///  @file     Utility.h                                                       
///  @brief    通用工具（函数）文件                                                                            
///  @author   lqt                                                                                                        
///  @version  1.0.0                                                
///  @date     2018.07.03                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////

/**
     用户管理通用函数接口类
*/
class EXPORT_USER_MANAGER CUserUtility
{
public:
	/** 生成唯一不重复的字串
	@param nLen 字串长度
	@note  用该函数之前一定要先初始化种子函数：srand(time(NULL))
	*/
	static CString GenerateUniqueStr(int nLen);

	/** 显示交互信息框
	@param csMsg  提示信息
	@param nBtn   显示按钮
	@param csCaption 标题
	@param nIcon 信息图标
	*/
	static int ShowMessageBox(CString csMsg, UINT nBtn = MB_OK, CString csCaption = _T("提示"), UINT nIcon = MB_ICONINFORMATION);

	/** 文件是否存在
	@param lpszFilePath 文件全路径名
	*/
	static BOOL IsFileExist(LPCTSTR lpszFilePath);

	/**  文件内容拷贝到变体数据类型
	@param ovData 变体数据（输出）
	@param csFileName  文件全路径名
	*/
	static BOOL PutFileIntoVariant(COleVariant *ovData, const CString& csFileName);
};