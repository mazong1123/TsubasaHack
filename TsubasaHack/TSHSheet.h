//////////////////////////////////////////////////////////////////////////
//// CTSHSheet
// 
// ����: �����޸�ѡ�������(Container)
//
// ˵��: �����Sheet�ϳ��������޸�ѡ��(���棬�������Զ���)��ʵ���ϱ�������������
//
// ����: mazong1123

#pragma once
#include <afxdlgs.h>
#include "resource.h"
#include "TsubasaHackDlg.h"
#include "PlayerAbilityPage.h"
#include "CustomizePage.h"

class CTSHSheet: public CPropertySheet 
{

public:
	CTSHSheet(CWnd* pParent = NULL);
	~CTSHSheet(void);
public:
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP();

	//////////////////////////////////////////////////////////////////////////
	//
	// ��Ϣӳ��
	afx_msg void OnOpen();			// ��Hack�ļ�ѡ���
	afx_msg void OnExit();			// �˳�Ӧ�ó���
	afx_msg void OnAsmcheck();		// ����6502ASMFinder
	afx_msg void OnIndject();		// ����CodeIndject
	afx_msg void OnHelp();			// ���������ļ�
	afx_msg void OnAbout();			// �������ڶԻ���

private:
	CTsubasaHackDlg m_GeneryPage;		// ����ҳ��
	CPlayerAbilityPage m_AbilityPage;	// �����޸�ҳ��
	CCustomizePage m_CustomizePage;		// �Զ���ҳ��

	HICON m_hIcon;	// ͼ��

};
