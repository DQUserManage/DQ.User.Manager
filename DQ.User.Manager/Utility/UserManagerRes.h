#pragma once

//////////////////////////////////////////////////////////////////////////////////                                                                            ///  @file     UserManagerRes.h                                                       ///  @brief    ��Դ�����ļ�                                                                             ///  @author   lqt                                                                                                        ///  @version  1.0.0                                                ///  @date     2018.06.28                                                                                ///                                                                          ///////////////////////////////////////////////////////////////////////////////

/**
	�û�������Դ��������Ӧ�ó����dll֮����Դ�л���
*/
class CUserManagerResLock
{
public:
	/** ��Դ�л�
	@param hInst ����Ϊ��ǰ��Դ����Ч���
	*/
	CUserManagerResLock(HINSTANCE hInst);

	/** �ָ�ԭ�ȵ���Դ���*/
	~CUserManagerResLock(void);
private:
	HINSTANCE m_hInst;  ///<�ɵ���Դ���
};