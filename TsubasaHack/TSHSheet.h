//////////////////////////////////////////////////////////////////////////
//// CTSHSheet
// 
// 功能: 三个修改选项的容器(Container)
//
// 说明: 在这个Sheet上承载三个修改选项(常规，能力，自定义)，实际上本类是主界面类
//
// 作者: mazong1123

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
	// 消息映射
	afx_msg void OnOpen();			// 打开Hack文件选择框
	afx_msg void OnExit();			// 退出应用程序
	afx_msg void OnAsmcheck();		// 启动6502ASMFinder
	afx_msg void OnIndject();		// 启动CodeIndject
	afx_msg void OnHelp();			// 启动帮助文件
	afx_msg void OnAbout();			// 启动关于对话框

private:
	CTsubasaHackDlg m_GeneryPage;		// 常规页面
	CPlayerAbilityPage m_AbilityPage;	// 能力修改页面
	CCustomizePage m_CustomizePage;		// 自定义页面

	HICON m_hIcon;	// 图标

};
