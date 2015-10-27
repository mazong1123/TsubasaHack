//////////////////////////////////////////////////////////////////////////
//// CConfigInfo v1.0
// 
// ����: ��ʼ���������ļ�
//
// ˵��: ������ȡ��ʼ���ݲ����䱣�����ڴ��У�����ȫ��ʹ��
//
// ����: mazong1123

#include "stdafx.h"
#include "ConfigInfo.h"

// ��ʼ����̬����
std::auto_ptr<CConfigInfo> CConfigInfo::m_pInstancePtr;
CConfigInfo * CConfigInfo::m_pInstance = NULL;

CConfigInfo::CConfigInfo()
{
	// ��ʵ��ָ��󶨵�auto_ptr
	m_pInstancePtr = std::auto_ptr<CConfigInfo>( this );
}

CConfigInfo::~CConfigInfo()
{

}

//////////////////////////////////////////////////////////////////////////
//// GetInstance
// 
// ����: void
//
// ����ֵ: CConfigInfo *: ������Ϣ��ʵ��
//
// ����: ��ȡ������Ϣ��ʵ��
CConfigInfo * CConfigInfo::GetInstance()
{
	if ( NULL == m_pInstance)
	{
		m_pInstance = new CConfigInfo;

		// ��ȡ��ʼ��Ϣ
		m_pInstance->m_strTshFilePath = m_pInstance->GetProgramRootPath() + _T("TSHFile\\");
		m_pInstance->m_strDataFilePath = m_pInstance->GetProgramRootPath() + _T("Data\\");
		m_pInstance->m_strToolsFilePath = m_pInstance->GetProgramRootPath() + _T("Tools\\");
		m_pInstance->m_strHelpFilePath = m_pInstance->GetProgramRootPath() + _T("Help\\");
	}

	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
//// SetObjectFilePath
// 
// ����: strFilePath Ŀ���ļ�·��
//
// ����ֵ: void
//
// ����: ����ȫ��Ŀ���ļ�·��(��ҪHack���ļ�·��)
void CConfigInfo::SetObjectFilePath( const CString &strFilePath )
{
	m_strObjectFilePath = strFilePath;
}

//////////////////////////////////////////////////////////////////////////
//// GetObjectFilePath
// 
// ����: void
//
// ����ֵ: CString Ŀ���ļ�·��
//
// ����: ��ȡȫ��Ŀ���ļ�·��(��ҪHack���ļ�·��)
CString CConfigInfo::GetObjectFilePath()
{
	return m_strObjectFilePath;
}

//////////////////////////////////////////////////////////////////////////
//// GetErrorMsg
// 
// ����: eMsgType: ������Ϣ����
//
// ����ֵ: CString ������Ϣ��Ϣ
//
// ����: ��ȡ������Ϣ
CString CConfigInfo::GetErrorMsg( ErrMsg eMsgType )
{
	CString strErrorMsg;

	switch( eMsgType )
	{
	case errSuccess:
		strErrorMsg = _T("�޸ĳɹ�");
		break;
	case errOpenFileFailed:
		strErrorMsg = _T("�޷����ļ����ļ�SEEK����,��ȷ��ָ���ļ��Ƿ���ڻ��Ѿ�ȥ��ֻ������");
		break;
	case errOpenPlayerInfoFileFailed:
		strErrorMsg = _T("��Ա��Ϣ�ļ���ʧ�ܣ�");
		break;
	case errSetPlayerAbilityBeforeChooseFile:
		strErrorMsg = _T("��δѡ���޸��ļ���������'����'ѡ���ѡ���ļ�·����Ȼ���ٵ��'����'ѡ���'ˢ��'��ť");
		break;
	case errSetCustomPageBeforeChooseFile:
		strErrorMsg = _T("��δѡ���޸��ļ���������'����'ѡ���ѡ���ļ�·����Ȼ���ٵ��'�Զ���'ѡ���'ˢ���б�'��ť");
		break;
	case errInjectCodeFailed:
		strErrorMsg = _T("ע��������");
		break;
	default:
	    break;
	}

	return strErrorMsg;
}

//////////////////////////////////////////////////////////////////////////
//
// ���ڲ�����

//////////////////////////////////////////////////////////////////////////
//// GetProgramRootPath
// 
// ����: void
//
// ����ֵ: CString ��ǰ�������ڵ�Ŀ¼
//
// ����: ��ȡ��ǰ�������ڵ�Ŀ¼
CString   CConfigInfo::GetProgramRootPath() 
{ 
	CString   strRootPath; 

	//   ȡ�õ�ǰ����İ���·�� 
	strRootPath   =   AfxGetApp()->m_pszHelpFilePath; 

	//   �����ַ������һ��   "\"   ������ֵ 
	int   index   =   strRootPath.ReverseFind('\\'); 

	//   ��������ֵ��ߵ������ַ� 
	return   ( strRootPath.Left(index)   +   _T("\\") ); 
} 
