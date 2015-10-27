//////////////////////////////////////////////////////////////////////////
//// CPlayerAbilityPage
// 
// 功能: 能力值修改页
//
// 说明: 1.1版新添加的功能，修改人物能力值
//
// 作者: mazong1123

#pragma once
#include "afxcmn.h"
#include "EditList.h"
#include <afxtempl.h>
#include "resource.h"

// 各种固定数据
#define ABILITYNUMBER 191 
#define STARTOFFSET 0x39FF6
#define ENDOFFSET 0x3AE7E
#define GKSTARTOFFSET 0x3AE96
#define GKENDOFFSET 0x3AFB6

typedef CMap<int, int, CString, CString> CAbilityMap;

// CPlayerAbilityPage 对话框

class CPlayerAbilityPage : public CPropertyPage
{

	DECLARE_DYNAMIC(CPlayerAbilityPage)

public:
	CPlayerAbilityPage();
	virtual ~CPlayerAbilityPage();

	//初始化列表控件
	BOOL InitListCtrl();
	virtual BOOL OnApply();

	//创建16进制能力值和10进制能力值映射关系
	void InitAbilityMap();
	//从ROM获得数据填到ListCtrl中
	BOOL GetDataForListCtrl();

	//////////////////////////////////////////////////////////////////////////
	//// IndirectCode
	//
	// 参数:	offset: 起始偏移地址
	//			buffer: 要修改的内容
	//			count:  要修改的字节数
	//
	// 返回值: BOOL 是否注入成功
	// 
	// 功能: 注入代码(字节为单位)
	BOOL IndirectCode( long offset, unsigned short *buffer, size_t count );


// 对话框数据
	enum { IDD = IDD_PLAYERABILITY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnBnClickedRefreshButton();	//刷新
	afx_msg void OnBnClickedSelectAllButton();	//全选

private:
	CEditList m_playerability_list;
	CAbilityMap m_PlayerAbilityMap;	//存放16进制能力值和10进制能力值映射关系
	CAbilityMap m_GKAbilityMap;		//GK能力值映射

	// 刷新和全选按钮
	CButton m_refresh_button;
	CButton m_selectall_button;
};
