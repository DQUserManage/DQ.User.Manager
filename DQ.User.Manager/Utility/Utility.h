
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
class CUserUtility
{
public:
	/** 生成唯一不重复的字串
	@param nLen 字串长度
	@note  用该函数之前一定要先初始化种子函数：srand(GetTime(NULL))
	*/
	static CString GenerateUniqueStr(int nLen);
};