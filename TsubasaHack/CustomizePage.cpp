//////////////////////////////////////////////////////////////////////////
//// CCustomizePage
// 
// 功能: 自定义页
//
// 说明: 1.1版新添加的功能，用户可以自己定义修改文件
//		 按照规定的格式可以做出Hack补丁
//
// 作者: mazong1123

// CustomizePage.cpp : 实现文件
//

#include "stdafx.h"
#include "TsubasaHack.h"
#include "CustomizePage.h"

#include <share.h>
#include <fstream>
#include <stdlib.h>
#include <locale>
#include "ConfigInfo.h"


// CCustomizePage 对话框

IMPLEMENT_DYNAMIC(CCustomizePage, CPropertyPage)

CCustomizePage::CCustomizePage()
	: CPropertyPage(CCustomizePage::IDD)
{
	ZeroMemory( m_offset_num, MAXFILENUM );


	m_customize_code_map = new DATAROWINFO[MAXFILENUM];

	for ( int i = 0; i < MAXFILENUM; i++ )
	{
		m_customize_code_map[i].codeinfo = new CodeInfo[CODENUM];
	}
	
	
}

CCustomizePage::~CCustomizePage()
{
	for ( int i = 0; i < MAXFILENUM; i++ )
	{

		delete []m_customize_code_map[i].codeinfo;
		m_customize_code_map[i].codeinfo = NULL;
		
	}

	delete []m_customize_code_map;
}

void CCustomizePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOMIZE_EDIT, m_customize_edit);
	DDX_Control(pDX, IDC_CUSTOMIZE_LIST, m_customize_list);
}


BEGIN_MESSAGE_MAP(CCustomizePage, CPropertyPage)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, &CCustomizePage::OnBnClickedRefreshButton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CUSTOMIZE_LIST, &CCustomizePage::OnLvnItemchangedCustomizeList)
END_MESSAGE_MAP()


// CCustomizePage 消息处理程序

void CCustomizePage::OnBnClickedRefreshButton()
{
	ZeroMemory( m_offset_num, MAXFILENUM );
	
	//删除数据
	for ( int i = 0; i < MAXFILENUM; i++ )
	{

		delete []m_customize_code_map[i].codeinfo;
		m_customize_code_map[i].codeinfo = NULL;

	}

	delete []m_customize_code_map;

	//重新建立映射关系
	m_customize_code_map = new DATAROWINFO[MAXFILENUM];

	for ( int i = 0; i < MAXFILENUM; i++ )
	{
		m_customize_code_map[i].codeinfo = new CodeInfo[CODENUM];
	}

	m_customize_list.DeleteAllItems();

	GetDataForListCtrlAndEdit();
}

BOOL CCustomizePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	if ( CConfigInfo::GetInstance()->GetObjectFilePath().GetLength() == 0 )
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errSetCustomPageBeforeChooseFile ) );
	}

	// 初始化ListCtrl
	InitListCtrl();

	// 获取TSH文件数据
	GetDataForListCtrlAndEdit();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCustomizePage::InitListCtrl()
{
	m_customize_list.InsertColumn( 0, _T("游戏名称"), LVCFMT_LEFT, 145, 0 );
	m_customize_list.InsertColumn( 1, _T("作者"), LVCFMT_LEFT, 145, 0 );
	m_customize_list.InsertColumn( 2, _T("功能描述"), LVCFMT_LEFT, 332, 0 );

	m_customize_list.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );
}


BOOL CCustomizePage::GetDataForListCtrlAndEdit()
{
	int nItem = 0;
	int nRow = 0;

	// 查找TSH目录下的所有tsh文件
	CFileFind finder;
	BOOL bWorking = finder.FindFile( CConfigInfo::GetInstance()->GetTshFilePath() + _T("*.tsh") );

	while ( bWorking )
	{
		CTSHFileOperator tshfile;

		bWorking = finder.FindNextFile();

		if ( !tshfile.Open( finder.GetFilePath() ) )
		{
			tshfile.Close();

			return FALSE;
		}


		nItem = m_customize_list.InsertItem( nRow, tshfile.GetGameName() );
		m_customize_list.SetItemText( nItem, 1, tshfile.GetAuthorName() );
		m_customize_list.SetItemText( nItem, 2, tshfile.GetFunction() );

		//转移数据
		int offsetnum = tshfile.GetOffsetNum();

		CodeInfo *pTempCodeInfo;
		pTempCodeInfo = tshfile.GetCode();

		for ( int j = 0; j < offsetnum; j++ )
		{
			m_customize_code_map[ nRow ].codeinfo[ j ].offset  = pTempCodeInfo[j].offset;
			m_customize_code_map[ nRow ].codeinfo[ j ].count = pTempCodeInfo[j].count;
			memcpy_s( m_customize_code_map[ nRow ].codeinfo[ j ].buffer, sizeof( m_customize_code_map[ nRow ].codeinfo[ j ].buffer ), pTempCodeInfo[j].buffer, sizeof( pTempCodeInfo[j].buffer ) );
		}	

		m_offset_num[ nRow ] = tshfile.GetOffsetNum();


		tshfile.Close();

		nRow++;
		
	}
	
	return TRUE;
}

//注入代码
BOOL CCustomizePage::IndirectCode( long offset, unsigned long *buffer, size_t count )
{
	FILE *stream;
	int  result;


	stream = _wfsopen( CConfigInfo::GetInstance()->GetObjectFilePath(), _T("r+b"), _SH_DENYNO );

	if( stream == NULL )
	{
		return FALSE;
	}
	else
	{
		for ( unsigned long i = 0; i < count; i++ )
		{
			result = fseek( stream, offset + i, SEEK_SET);
			if( result )
			{
				return FALSE;
			}
			else
			{

				unsigned long Tempbuffer[255];
				Tempbuffer[0] = buffer[i];
				fwrite( Tempbuffer, 1, 1, stream );

			}
		}

		fclose( stream );
		return TRUE;
		
	}
}

void CCustomizePage::OnLvnItemchangedCustomizeList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	CString GameName;
	CString AuthorName;
	CString Function;

	int CurIndex = m_customize_list.GetNextItem( -1, LVNI_SELECTED );

	GameName = m_customize_list.GetItemText( CurIndex, 0 );
	AuthorName = m_customize_list.GetItemText( CurIndex, 1 );
	Function = m_customize_list.GetItemText( CurIndex, 2 );

	CString EditText;

	EditText = _T("游戏名称: ") + GameName + _T("\r\n作者: ") + AuthorName + _T("\r\n功能描述: ") + Function + _T("\r\n");
	m_customize_edit.SetWindowText( EditText );

	SetModified();

	*pResult = 0;
}

BOOL CCustomizePage::OnApply()
{
	if ( CConfigInfo::GetInstance()->GetObjectFilePath().GetLength() == 0 )
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errSetCustomPageBeforeChooseFile ) );
		return FALSE;
	}
	for ( int i = 0; i < m_customize_list.GetItemCount(); i++ )
	{
		if ( m_customize_list.GetCheck( i ) )
		{
			

			for ( int j = 0; j < m_offset_num[i]; j++ )
			{
				if ( !IndirectCode( m_customize_code_map[ i ].codeinfo[ j ].offset, m_customize_code_map[ i ].codeinfo[ j ].buffer, m_customize_code_map[ i ].codeinfo[ j ].count ) )
				{
					AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errInjectCodeFailed ) );
					return FALSE;
				}
			}
			
			
		}
	}
	return CPropertyPage::OnApply();
}
