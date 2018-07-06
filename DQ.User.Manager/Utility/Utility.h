
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
class EXPORT_USER_MANAGER CUserUtility
{
public:
	/** ����Ψһ���ظ����ִ�
	@param nLen �ִ�����
	@note  �øú���֮ǰһ��Ҫ�ȳ�ʼ�����Ӻ�����srand(time(NULL))
	*/
	static CString GenerateUniqueStr(int nLen);

	/** ��ʾ������Ϣ��
	@param csMsg  ��ʾ��Ϣ
	@param nBtn   ��ʾ��ť
	@param csCaption ����
	@param nIcon ��Ϣͼ��
	*/
	static int ShowMessageBox(CString csMsg, UINT nBtn = MB_OK, CString csCaption = _T("��ʾ"), UINT nIcon = MB_ICONINFORMATION);

	/** �ļ��Ƿ����
	@param lpszFilePath �ļ�ȫ·����
	*/
	static BOOL IsFileExist(LPCTSTR lpszFilePath);

	/**  �ļ����ݿ�����������������
	@param ovData �������ݣ������
	@param csFileName  �ļ�ȫ·����
	*/
	static BOOL PutFileIntoVariant(COleVariant *ovData, const CString& csFileName);
};