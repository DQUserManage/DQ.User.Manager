#pragma once

///////////////////////////////////////////////////////////////////////////////
///                                                                            
///  @file     CustomEdit.h                                                       
///  @brief    自定义编辑框类文件                                                                             
///  @author   lqt                                                                                                        
///  @version  1.0.0                                                
///  @date     2018.07.05                                                                               
///                                                                          
///////////////////////////////////////////////////////////////////////////////

/**
      选择部门编辑控件
*/
class EXPORT_USER_MANAGER CDeptBrowserEdit : public CBCGPEdit
{
public:
	/** 弹出部门树显示窗体*/
	virtual void OnBrowse();

public:
	CString m_csDeptID;  ///<部门ID
};