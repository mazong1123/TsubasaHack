//////////////////////////////////////////////////////////////////////////
//// CCustomizePage
// 
// ����: �Զ���ҳ
//
// ˵��: 1.1������ӵĹ��ܣ��û������Լ������޸��ļ�
//		 ���չ涨�ĸ�ʽ��������Hack����
//
// ����: mazong1123

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TSHFileOperator.h"

#define MAXFILENUM 500

struct DATAROWINFO 
{
	CodeInfo *codeinfo;
};


// CCustomizePage �Ի���

class CCustomizePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCustomizePage)

public:
	CCustomizePage();
	virtual ~CCustomizePage();

// �Ի�������
	enum { IDD = IDD_CUSTOMIZE_DIALOG };

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnApply();

	virtual BOOL OnInitDialog();
	void InitListCtrl();
	BOOL GetDataForListCtrlAndEdit();

	// ע�����
	BOOL IndirectCode( long offset, unsigned long *buffer, size_t count );

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedRefreshButton();
	afx_msg void OnLvnItemchangedCustomizeList(NMHDR *pNMHDR, LRESULT *pResult);

private:
	CEdit m_customize_edit;
	CListCtrl m_customize_list;

	DATAROWINFO *m_customize_code_map;	// ���ÿ�кʹ����ӳ���ϵ
	int m_offset_num[MAXFILENUM];		// ��Ÿ����ļ���ƫ�Ƶ�ַ����
	
};
