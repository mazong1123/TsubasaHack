//////////////////////////////////////////////////////////////////////////
//// CTSHSheet
// 
// ����: �����޸�ѡ�������(Container)
//
// ˵��: �����Sheet�ϳ��������޸�ѡ��(���棬�������Զ���)��ʵ���ϱ�������������
//
// ����: mazong1123

#include "StdAfx.h"
#include "TSHSheet.h"
#include "AboutDlg.h"
#include "TsubasaHackDlg.h"
#include "ConfigInfo.h"


CTSHSheet::CTSHSheet(CWnd* pParent /*=NULL*/)
: CPropertySheet(IDS_TSHPROPERTY_CAPTION, pParent )
{
	// ������������ҳ
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

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//��ȡ�˵�
	CMenu menu;
	menu.LoadMenu( IDR_MAIN_MENU );
	ASSERT( menu );
	
	SetMenu( &menu );

	//////////////////////////////////////////////////////////////////////////
	//�������ڴ�С

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
	// ��Hack�ļ�ѡ���
	( dynamic_cast<CTsubasaHackDlg*> ( GetPage( 0 )) )->OnBnClickedFileselect();
}

void CTSHSheet::OnExit()
{
	// ��ȻҪ����Ϣ����
	// ֱ�ӵ���OnClose()����
	::SendMessage( GetSafeHwnd(), WM_CLOSE, 0, 0 );
}

void CTSHSheet::OnAsmcheck()
{
	// ����6502ASMFinder
	if ( ShellExecute(NULL, _T("open"), CConfigInfo::GetInstance()->GetToolsFilePath() + _T("6502ASMFinder.exe"), NULL, CConfigInfo::GetInstance()->GetToolsFilePath() , SW_SHOWNORMAL) <= ERROR_FLAG )
	{
		AfxMessageBox( _T("δ�ҵ� 6502ASMFinder.exe ����ȷ�� 6502ASMFinder.exe �Ƿ���ڣ�") );
	}
}

void CTSHSheet::OnIndject()
{
	// ����CodeIndject
	if ( ShellExecute(NULL, _T("open"), CConfigInfo::GetInstance()->GetToolsFilePath() + _T("CodeIndject.exe"), NULL, CConfigInfo::GetInstance()->GetToolsFilePath() , SW_SHOWNORMAL) <= ERROR_FLAG )
	{
		AfxMessageBox( _T("δ�ҵ� CodeIndject.exe ����ȷ�� CodeIndject.exe �Ƿ���ڣ�") );
	}

}

void CTSHSheet::OnHelp()
{
	// ���������ļ�
	if ( ShellExecute(NULL, _T("open"), CConfigInfo::GetInstance()->GetHelpFilePath() + _T("TsubasaHackʹ��˵��.doc"), NULL, CConfigInfo::GetInstance()->GetHelpFilePath() , SW_SHOWNORMAL) <= ERROR_FLAG )
	{
		AfxMessageBox( _T("δ�ҵ� TsubasaHackʹ��˵��.doc����ȷ�� TsubasaHackʹ��˵��.doc �Ƿ���ڣ�") );
	}
}

void CTSHSheet::OnAbout()
{
	// �������ڶԻ���
	CAboutDlg dlg;
	dlg.DoModal();
}
