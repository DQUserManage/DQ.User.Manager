
#pragma once 

///                                                                            
///  @file     Utility.h                                                       
///  @brief    ͨ�ù��ߣ��������ļ�                                                                            
///  @author   lqt                                                                                                        
///  @version  1.0.0                                                
///  @date     2018.07.03                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////

/**
     �û�����ͨ�ú����ӿ���
*/
class CUserUtility
{
public:
	/** ����Ψһ���ظ����ִ�
	@param nLen �ִ�����
	@note  �øú���֮ǰһ��Ҫ�ȳ�ʼ�����Ӻ�����srand(GetTime(NULL))
	*/
	static CString GenerateUniqueStr(int nLen);
};