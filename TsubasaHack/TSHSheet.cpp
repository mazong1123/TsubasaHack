//////////////////////////////////////////////////////////////////////////
//// CTSHSheet
// 
// 功能: 三个修改选项的容器(Container)
//
// 说明: 在这个Sheet上承载三个修改选项(常规，能力，自定义)，实际上本类是主界面类
//
// 作者: mazong1123

#include "StdAfx.h"
#include "TSHSheet.h"
#include "AboutDlg.h"
#include "TsubasaHackDlg.h"
#include "ConfigInfo.h"


CTSHSheet::CTSHSheet(CWnd* pParent /*=NULL*/)
: CPropertySheet(IDS_TSHPROPERTY_CAPTION, pParent )
{
	// 加入三个属性页
	AddPage( &m_GeneryPage );
	AddPage( &m_AbilityPage );
	AddPage( &m_CustomizePage );

	m_hIcon = AfxGetApp()->LoadIcon( IDI_MAIN_ICON );
}

CTSHSheet::~CTSHSheet(void)
{

}



BOOL CTSHSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//读取菜单
	CMenu menu;
	menu.LoadMenu( IDR_MAIN_MENU );
	ASSERT( menu );
	
	SetMenu( &menu );

	//////////////////////////////////////////////////////////////////////////
	//调整窗口大小

	SetWindowPos( NULL, 0, 0, 770, 700,  SWP_NOMOVE );

	return bResult;
}

BEGIN_MESSAGE_MAP(CTSHSheet, CPropertySheet)
	ON_COMMAND(ID_OPEN, &CTSHSheet::OnOpen)
	ON_COMMAND(ID_EXIT, &CTSHSheet::OnExit)
	ON_COMMAND(ID_ASMCHECK, &CTSHSheet::OnAsmcheck)
	ON_COMMAND(ID_INDJECT, &CTSHSheet::OnIndject)
	ON_COMMAND(ID_HELP, &CTSHSheet::OnHelp)
	ON_COMMAND(ID_ABOUT, &CTSHSheet::OnAbout)
END_MESSAGE_MAP()

void CTSHSheet::OnOpen()
{
	// 打开Hack文件选择框
	( dynamic_cast<CTsubasaHackDlg*> ( GetPage( 0 )) )->OnBnClickedFileselect();
}

void CTSHSheet::OnExit()
{
	// 居然要发消息才行
	// 直接调用OnClose()不行
	::SendMessage( GetSafeHwnd(), WM_CLOSE, 0, 0 );
}

void CTSHSheet::OnAsmcheck()
{
	// 启动6502ASMFinder
	if ( ShellExecute(NULL, _T("open"), CConfigInfo::GetInstance()->GetToolsFilePath() + _T("6502ASMFinder.exe"), NULL, CConfigInfo::GetInstance()->GetToolsFilePath() , SW_SHOWNORMAL) <= ERROR_FLAG )
	{
		AfxMessageBox( _T("未找到 6502ASMFinder.exe ，请确认 6502ASMFinder.exe 是否存在！") );
	}
}

void CTSHSheet::OnIndject()
{
	// 启动CodeIndject
	if ( ShellExecute(NULL, _T("open"), CConfigInfo::GetInstance()->GetToolsFilePath() + _T("CodeIndject.exe"), NULL, CConfigInfo::GetInstance()->GetToolsFilePath() , SW_SHOWNORMAL) <= ERROR_FLAG )
	{
		AfxMessageBox( _T("未找到 CodeIndject.exe ，请确认 CodeIndject.exe 是否存在！") );
	}

}

void CTSHSheet::OnHelp()
{
	// 启动帮助文件
	if ( ShellExecute(NULL, _T("open"), CConfigInfo::GetInstance()->GetHelpFilePath() + _T("TsubasaHack使用说明.doc"), NULL, CConfigInfo::GetInstance()->GetHelpFilePath() , SW_SHOWNORMAL) <= ERROR_FLAG )
	{
		AfxMessageBox( _T("未找到 TsubasaHack使用说明.doc，请确认 TsubasaHack使用说明.doc 是否存在！") );
	}
}

void CTSHSheet::OnAbout()
{
	// 启动关于对话框
	CAboutDlg dlg;
	dlg.DoModal();
}
