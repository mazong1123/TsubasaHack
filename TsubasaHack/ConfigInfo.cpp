//////////////////////////////////////////////////////////////////////////
//// CConfigInfo v1.0
// 
// 功能: 初始数据配置文件
//
// 说明: 这个类读取初始数据并将其保存在内存中，方便全局使用
//
// 作者: mazong1123

#include "stdafx.h"
#include "ConfigInfo.h"

// 初始化静态数据
std::auto_ptr<CConfigInfo> CConfigInfo::m_pInstancePtr;
CConfigInfo * CConfigInfo::m_pInstance = NULL;

CConfigInfo::CConfigInfo()
{
	// 将实例指针绑定到auto_ptr
	m_pInstancePtr = std::auto_ptr<CConfigInfo>( this );
}

CConfigInfo::~CConfigInfo()
{

}

//////////////////////////////////////////////////////////////////////////
//// GetInstance
// 
// 参数: void
//
// 返回值: CConfigInfo *: 配置信息类实例
//
// 功能: 获取配置信息类实例
CConfigInfo * CConfigInfo::GetInstance()
{
	if ( NULL == m_pInstance)
	{
		m_pInstance = new CConfigInfo;

		// 获取初始信息
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
// 参数: strFilePath 目标文件路径
//
// 返回值: void
//
// 功能: 设置全局目标文件路径(即要Hack的文件路径)
void CConfigInfo::SetObjectFilePath( const CString &strFilePath )
{
	m_strObjectFilePath = strFilePath;
}

//////////////////////////////////////////////////////////////////////////
//// GetObjectFilePath
// 
// 参数: void
//
// 返回值: CString 目标文件路径
//
// 功能: 获取全局目标文件路径(即要Hack的文件路径)
CString CConfigInfo::GetObjectFilePath()
{
	return m_strObjectFilePath;
}

//////////////////////////////////////////////////////////////////////////
//// GetErrorMsg
// 
// 参数: eMsgType: 错误消息类型
//
// 返回值: CString 错误消息信息
//
// 功能: 获取错误消息
CString CConfigInfo::GetErrorMsg( ErrMsg eMsgType )
{
	CString strErrorMsg;

	switch( eMsgType )
	{
	case errSuccess:
		strErrorMsg = _T("修改成功");
		break;
	case errOpenFileFailed:
		strErrorMsg = _T("无法打开文件或文件SEEK错误,请确认指定文件是否存在或已经去掉只读属性");
		break;
	case errOpenPlayerInfoFileFailed:
		strErrorMsg = _T("球员信息文件打开失败！");
		break;
	case errSetPlayerAbilityBeforeChooseFile:
		strErrorMsg = _T("尚未选择修改文件，请先在'常规'选项卡中选择文件路径，然后再点击'能力'选项卡的'刷新'按钮");
		break;
	case errSetCustomPageBeforeChooseFile:
		strErrorMsg = _T("尚未选择修改文件，请先在'常规'选项卡中选择文件路径，然后再点击'自定义'选项卡的'刷新列表'按钮");
		break;
	case errInjectCodeFailed:
		strErrorMsg = _T("注入代码出错");
		break;
	default:
	    break;
	}

	return strErrorMsg;
}

//////////////////////////////////////////////////////////////////////////
//
// 类内部函数

//////////////////////////////////////////////////////////////////////////
//// GetProgramRootPath
// 
// 参数: void
//
// 返回值: CString 当前程序所在的目录
//
// 功能: 获取当前程序所在的目录
CString   CConfigInfo::GetProgramRootPath() 
{ 
	CString   strRootPath; 

	//   取得当前程序的帮助路径 
	strRootPath   =   AfxGetApp()->m_pszHelpFilePath; 

	//   返回字符串最后一个   "\"   的索引值 
	int   index   =   strRootPath.ReverseFind('\\'); 

	//   返回索引值左边的所有字符 
	return   ( strRootPath.Left(index)   +   _T("\\") ); 
} 
