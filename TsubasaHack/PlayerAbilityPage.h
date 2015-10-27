//////////////////////////////////////////////////////////////////////////
//// CPlayerAbilityPage
// 
// ����: ����ֵ�޸�ҳ
//
// ˵��: 1.1������ӵĹ��ܣ��޸���������ֵ
//
// ����: mazong1123

#pragma once
#include "afxcmn.h"
#include "EditList.h"
#include <afxtempl.h>
#include "resource.h"

// ���̶ֹ�����
#define ABILITYNUMBER 191 
#define STARTOFFSET 0x39FF6
#define ENDOFFSET 0x3AE7E
#define GKSTARTOFFSET 0x3AE96
#define GKENDOFFSET 0x3AFB6

typedef CMap<int, int, CString, CString> CAbilityMap;

// CPlayerAbilityPage �Ի���

class CPlayerAbilityPage : public CPropertyPage
{

	DECLARE_DYNAMIC(CPlayerAbilityPage)

public:
	CPlayerAbilityPage();
	virtual ~CPlayerAbilityPage();

	//��ʼ���б�ؼ�
	BOOL InitListCtrl();
	virtual BOOL OnApply();

	//����16��������ֵ��10��������ֵӳ���ϵ
	void InitAbilityMap();
	//��ROM��������ListCtrl��
	BOOL GetDataForListCtrl();

	//////////////////////////////////////////////////////////////////////////
	//// IndirectCode
	//
	// ����:	offset: ��ʼƫ�Ƶ�ַ
	//			buffer: Ҫ�޸ĵ�����
	//			count:  Ҫ�޸ĵ��ֽ���
	//
	// ����ֵ: BOOL �Ƿ�ע��ɹ�
	// 
	// ����: ע�����(�ֽ�Ϊ��λ)
	BOOL IndirectCode( long offset, unsigned short *buffer, size_t count );


// �Ի�������
	enum { IDD = IDD_PLAYERABILITY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnBnClickedRefreshButton();	//ˢ��
	afx_msg void OnBnClickedSelectAllButton();	//ȫѡ

private:
	CEditList m_playerability_list;
	CAbilityMap m_PlayerAbilityMap;	//���16��������ֵ��10��������ֵӳ���ϵ
	CAbilityMap m_GKAbilityMap;		//GK����ֵӳ��

	// ˢ�º�ȫѡ��ť
	CButton m_refresh_button;
	CButton m_selectall_button;
};
