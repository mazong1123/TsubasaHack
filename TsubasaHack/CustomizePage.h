//////////////////////////////////////////////////////////////////////////
//// CCustomizePage
// 
// 功能: 自定义页
//
// 说明: 1.1版新添加的功能，用户可以自己定义修改文件
//		 按照规定的格式可以做出Hack补丁
//
// 作者: mazong1123

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TSHFileOperator.h"

#define MAXFILENUM 500

struct DATAROWINFO 
{
	CodeInfo *codeinfo;
};


// CCustomizePage 对话框

class CCustomizePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCustomizePage)

public:
	CCustomizePage();
	virtual ~CCustomizePage();

// 对话框数据
	enum { IDD = IDD_CUSTOMIZE_DIALOG };

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnApply();

	virtual BOOL OnInitDialog();
	void InitListCtrl();
	BOOL GetDataForListCtrlAndEdit();

	// 注入代码
	BOOL IndirectCode( long offset, unsigned long *buffer, size_t count );

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedRefreshButton();
	afx_msg void OnLvnItemchangedCustomizeList(NMHDR *pNMHDR, LRESULT *pResult);

private:
	CEdit m_customize_edit;
	CListCtrl m_customize_list;

	DATAROWINFO *m_customize_code_map;	// 存放每行和代码的映射关系
	int m_offset_num[MAXFILENUM];		// 存放各个文件中偏移地址总数
	
};
