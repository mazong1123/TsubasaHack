//////////////////////////////////////////////////////////////////////////
//// CPlayerAbilityPage
// 
// 功能: 能力值修改页
//
// 说明: 1.1版新添加的功能，修改人物能力值
//
// 作者: mazong1123

// PlayerAbilityPage.cpp : 实现文件
//

#include "stdafx.h"
#include "TsubasaHack.h"
#include "PlayerAbilityPage.h"
#include "TSHSheet.h"
#include "TsubasaHackDlg.h"

#include <share.h>
#include <fstream>
#include <stdlib.h>
#include <locale>
#include "ConfigInfo.h"


// CPlayerAbilityPage 对话框

IMPLEMENT_DYNAMIC(CPlayerAbilityPage, CPropertyPage)

CPlayerAbilityPage::CPlayerAbilityPage()
	: CPropertyPage(CPlayerAbilityPage::IDD)
{
	
}

CPlayerAbilityPage::~CPlayerAbilityPage()
{
}

void CPlayerAbilityPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAYERABILITY_LIST, m_playerability_list);
	DDX_Control(pDX, IDC_REFRESH_BUTTON, m_refresh_button);
	DDX_Control(pDX, IDC_SELECTALL_BUTTON, m_selectall_button);

}

BOOL CPlayerAbilityPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	if ( CConfigInfo::GetInstance()->GetObjectFilePath().GetLength() == 0 )
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errSetPlayerAbilityBeforeChooseFile ) );
	}

	//////////////////////////////////////////////////////////////////////////
	//调整窗口大小

	CRect *pRect;

	pRect = new CRect;
	GetParent()->GetWindowRect( pRect );
	m_playerability_list.SetWindowPos( NULL, 0, 0, pRect->Width()-50, pRect->Height()-180,  SWP_NOMOVE );
	delete pRect;
	pRect = NULL;

	m_refresh_button.SetWindowPos( NULL, 280, 550, 0, 0, SWP_NOSIZE );
	m_selectall_button.SetWindowPos( NULL, 390, 550, 0, 0, SWP_NOSIZE );
	
	//创建映射关系
	InitAbilityMap();

	//初始化列表控件
	InitListCtrl();

	//获取数据
	GetDataForListCtrl();

	return TRUE;
}


void CPlayerAbilityPage::InitAbilityMap()
{
	wchar_t URLTempChar[255];
	CString PlayerAbility;
	int nIndex = 0x07;

	std::wifstream PlayerAbilityFile( CConfigInfo::GetInstance()->GetDataFilePath() + _T("PlayerAbility.dat"),  std::ios_base::in );
	if ( !PlayerAbilityFile.is_open())
	{
		AfxMessageBox( _T("Player能力数据文件打开失败！") );
	}
	else
	{

		PlayerAbilityFile.imbue(std::locale("chs"));

		while ( !PlayerAbilityFile.eof() )
		{
			PlayerAbilityFile >> URLTempChar;
			PlayerAbility = URLTempChar;
			CString HexStr;
			CString DecStr;

			int nIndex;
			nIndex = PlayerAbility.Find( _T("="), 0 );

			//获得16进制字符串
			HexStr = PlayerAbility.Left( nIndex );

			//获得10进制字符串
			DecStr = PlayerAbility.Right( PlayerAbility.GetLength() - nIndex -1 );

			//把CString转换成Int
			wchar_t *pHexCh;
			pHexCh = HexStr.GetBuffer( HexStr.GetLength() );
			HexStr.ReleaseBuffer();

			int HexInt;
			HexInt = _wtoi( pHexCh );

			//创建映射关系
			m_PlayerAbilityMap[ HexInt ] = DecStr;


		}

		PlayerAbilityFile.close();
	}

	std::wifstream GKAbilityFile( CConfigInfo::GetInstance()->GetDataFilePath() + _T("GKAbility.dat"),  std::ios_base::in );
	if ( !GKAbilityFile.is_open() )
	{
		AfxMessageBox( _T("GK能力数据文件打开失败！") );
	}
	else
	{

		GKAbilityFile.imbue(std::locale("chs"));

		while ( !GKAbilityFile.eof() )
		{
			GKAbilityFile >> URLTempChar;
			PlayerAbility = URLTempChar;
			CString HexStr;
			CString DecStr;

			int nIndex;
			nIndex = PlayerAbility.Find( _T("="), 0 );

			//获得16进制字符串
			HexStr = PlayerAbility.Left( nIndex );

			//获得10进制字符串
			DecStr = PlayerAbility.Right( PlayerAbility.GetLength() - nIndex -1 );

			//把CString转换成Int
			wchar_t *pHexCh;
			pHexCh = HexStr.GetBuffer( HexStr.GetLength() );
			HexStr.ReleaseBuffer();

			int HexInt;
			HexInt = _wtoi( pHexCh );

			//创建映射关系
			m_GKAbilityMap[ HexInt ] = DecStr;


		}

		GKAbilityFile.close();

		for ( int i = 96; i < 256; i++ )
		{
			m_GKAbilityMap[ i ] = _T("976");
		}
	}
}

BOOL CPlayerAbilityPage::GetDataForListCtrl()
{
	FILE *stream;
	int  result;
	unsigned short buffer[255];
	long offset;
	int  nCol = 2;
	int	 nRow = 0;

	ZeroMemory( buffer, 255 );


	stream = _wfsopen( CConfigInfo::GetInstance()->GetObjectFilePath(), _T("r+b"), _SH_DENYNO );

	if( stream == NULL )
	{
		return FALSE;
	}
	else
	{
		//////////////////////////////////////////////////////////////////////////
		//读取球员能力值
		for ( int i = STARTOFFSET+1; i <= ENDOFFSET+1; i += 24 )
		{
			for ( offset = i; offset < i+22; offset++ )
			{
				result = fseek( stream, offset, SEEK_SET);
				if( result )
				{
		
					return FALSE;
				}
				else
				{
					fread( buffer, 1, 1, stream );

					if ( buffer[0] == NULL )
					{
						buffer[0] = 0x01;
					}

					CString AbilityStr;

					CAbilityMap::CPair *pCurVal = NULL;

					pCurVal = m_PlayerAbilityMap.PLookup( buffer[0] );

					//获取能力值
					AbilityStr = pCurVal->value;

					m_playerability_list.SetItemText( nRow, nCol, AbilityStr );
					nCol++;

				}
			}

			nCol = 2;
			nRow++;

		}
		
		//////////////////////////////////////////////////////////////////////////
		//读取守门员能力值
		
		nCol = 2;

		for ( int i = GKSTARTOFFSET+1; i <= GKENDOFFSET+1; i += 8 )
		{
			for ( offset = i; offset < i+7; offset++ )
			{
				result = fseek( stream, offset, SEEK_SET);
				if( result )
				{

					return FALSE;
				}
				else
				{
					fread( buffer, 1, 1, stream );

					if ( buffer[0] == NULL )
					{
						buffer[0] = 0x01;
					}

					CString AbilityStr;

					CAbilityMap::CPair *pCurVal = NULL;
					pCurVal = m_PlayerAbilityMap.PLookup( buffer[0] );

					//获取能力值
					AbilityStr = pCurVal->value;

					m_playerability_list.SetItemText( nRow, nCol, AbilityStr );
					nCol++;

				}
			}

			for ( int j = 9; j < 24; j++ )
			{
				m_playerability_list.SetItemText( nRow, j, _T("无效") );
			}

			nRow++;
			nCol = 2;
		}

		//////////////////////////////////////////////////////////////////////////
		//读取球员体力

		nCol = 1;
		nRow = 0;

		for ( int i = STARTOFFSET; i <= ENDOFFSET; i += 24 )
		{
			offset = i;
			result = fseek( stream, offset, SEEK_SET);
			if( result )
			{

				return FALSE;
			}
			else
			{
				fread( buffer, 1, 1, stream );

				CString AbilityStr;

				CAbilityMap::CPair *pCurVal = NULL;
				pCurVal = m_GKAbilityMap.PLookup( buffer[0] );

				//获取能力值
				AbilityStr = pCurVal->value;
				CString TempStr;

				m_playerability_list.SetItemText( nRow, nCol, AbilityStr );
				

			}

			nRow++;

		}
		
		//////////////////////////////////////////////////////////////////////////
		//读取守门员体力

		nCol = 1;

		for ( int i = GKSTARTOFFSET; i <= GKENDOFFSET; i += 8 )
		{
			offset = i;
			result = fseek( stream, offset, SEEK_SET);
			if( result )
			{

				return FALSE;
			}
			else
			{
				fread( buffer, 1, 1, stream );

				CString AbilityStr;

				CAbilityMap::CPair *pCurVal = NULL;
				pCurVal = m_GKAbilityMap.PLookup( buffer[0] );

				//获取能力值
				AbilityStr = pCurVal->value;

				m_playerability_list.SetItemText( nRow, nCol, AbilityStr );

			}			

			nRow++;

		}


		fclose( stream );
	}


	return TRUE;

}

// this function is sent to CEditList 
// there it is used to determine which type of ctrl to create 
// when cell is being edited
static int _List_Type( int col )
{
	if ( col == 0 )
	{
		return CEditList::eNoChange;
	}

	if ( col == 1 )
	{
		return CEditList::eCombo;
	}

	// else :
	return CEditList::eEdit;
}

BOOL CPlayerAbilityPage::InitListCtrl()
{
	int nColIndex = 0;

	m_playerability_list.InsertColumn( nColIndex, _T("姓名"), LVCFMT_LEFT, 145, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("体力"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("平地射门(GK传球)"), LVCFMT_LEFT, 110, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("传球(GK接球)"), LVCFMT_LEFT, 90, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("过人(GK击球)"), LVCFMT_LEFT, 90, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("挡球(GK防射门)"), LVCFMT_LEFT, 100, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("铲球(GK防过人)"), LVCFMT_LEFT, 100, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("断球(GK低空出击)"), LVCFMT_LEFT, 110, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("低空射门(GK高空出击)"), LVCFMT_LEFT, 140, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("?"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("低空停球"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("低空漏球"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("?"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("低空解围"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("低空争抢"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("?"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("高空射门"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("?"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("高空停球"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("高空漏球"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("?"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("高空解围"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("高空争抢"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("?"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	//////////////////////////////////////////////////////////////////////////
	//读取球员名称
	CString PlayerName;
	wchar_t URLTempChar[255];
	CString PlayerInfo;

	std::wifstream HomePageFile( CConfigInfo::GetInstance()->GetDataFilePath() + _T("PlayerAbilityList.dat"),  std::ios_base::in );
	if ( !HomePageFile.is_open())
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenPlayerInfoFileFailed ) );
	}
	else
	{
		HomePageFile.imbue(std::locale("chs"));

		while ( !HomePageFile.eof() )
		{
			//读取球员id
			HomePageFile >> URLTempChar;
			PlayerInfo = URLTempChar;
			PlayerName = PlayerInfo;

			//读取球员名称
			HomePageFile >> URLTempChar;
			PlayerInfo = URLTempChar;
			PlayerName += _T("&") + PlayerInfo;

			m_playerability_list.InsertItem( 0, PlayerName );
		}

		HomePageFile.close();
	}
	

	m_playerability_list.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );
	m_playerability_list.SetColumnType ( (fGetType)_List_Type );	

	CAbilityMap::CPair *pCurVal = NULL;

	for ( int j = 0; j <96; j++ )
	{
		pCurVal= m_GKAbilityMap.PLookup( j ) ;
		m_playerability_list.m_strList.AddTail( pCurVal->value );

	}

	return TRUE;
}

BEGIN_MESSAGE_MAP(CPlayerAbilityPage, CPropertyPage)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PLAYERABILITY_LIST, &CPlayerAbilityPage::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, &CPlayerAbilityPage::OnBnClickedRefreshButton)
	ON_BN_CLICKED(IDC_SELECTALL_BUTTON, &CPlayerAbilityPage::OnBnClickedSelectAllButton)
END_MESSAGE_MAP()


// CPlayerAbilityPage 消息处理程序
void CPlayerAbilityPage::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	SetModified();

	*pResult = 0;
	
}

void CPlayerAbilityPage::OnBnClickedRefreshButton()
{	
	//获取数据
	GetDataForListCtrl();
}

void CPlayerAbilityPage::OnBnClickedSelectAllButton()
{
	CString TempStr;

	m_selectall_button.GetWindowText( TempStr );

	if ( TempStr == _T("全选") )
	{
		//所有Item均为选中状态
		for ( int i = 0; i < m_playerability_list.GetItemCount(); i++ )
		{
			m_playerability_list.SetCheck( i );
		}

		m_selectall_button.SetWindowText( _T("全部取消") );
	}
	else
	{
		//所有Item均为非选中状态
		for ( int i = 0; i < m_playerability_list.GetItemCount(); i++ )
		{
			m_playerability_list.SetCheck( i, FALSE );
		}

		m_selectall_button.SetWindowText( _T("全选") );
	}
	
}

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
BOOL CPlayerAbilityPage::IndirectCode( long offset, unsigned short buffer[255], size_t count )
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
		result = fseek( stream, offset, SEEK_SET);
		if( result )
		{
			return FALSE;
		}
		else
		{
			fwrite( buffer, 1, count, stream );

		}
		fclose( stream );
		return TRUE;
	}
}

BOOL CPlayerAbilityPage::OnApply()
{
	BOOL nResult;
	CString AbilityStr;
	unsigned short buffer[255];
	int nCol = 1;
	int nRow = 0;
	long offset;

	if ( CConfigInfo::GetInstance()->GetObjectFilePath().GetLength() == 0 )
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errSetPlayerAbilityBeforeChooseFile ) );
		return FALSE;
	}

	ZeroMemory( buffer, 255 );

	//////////////////////////////////////////////////////////////////////////
	//修改球员能力值
	for ( long i = STARTOFFSET; i <= ENDOFFSET; i += 24 )
	{
		//如果选中，则作修改
		if ( m_playerability_list.GetCheck( nRow ) )
		{
			for ( offset = i; offset < i+23; offset++ )
			{
				AbilityStr = m_playerability_list.GetItemText( nRow, nCol );

				CAbilityMap::CPair *pCurVal;

				int i;

				if ( nCol == 1 )
				{
					for ( i = 0; i <= 96; i++ )
					{
						pCurVal= m_GKAbilityMap.PLookup( i );

						//找到对应的映射
						if ( AbilityStr == pCurVal->value )
						{
							break;
						}
					}


				}
				else
				{
					for ( i = 0; i <= ABILITYNUMBER; i++ )
					{
						pCurVal= m_PlayerAbilityMap.PLookup( i );

						//找到对应的映射
						if ( AbilityStr == pCurVal->value )
						{
							break;
						}
					}

					//未找到映射
					if ( i > ABILITYNUMBER )
					{
						AfxMessageBox( _T("输入的能力值数值不存在，该能力值将重置为8，请重新输入") );
						i = 1;

						pCurVal= m_PlayerAbilityMap.PLookup( i );
						//重置为8
						m_playerability_list.SetItemText( nRow, nCol, pCurVal->value );

						return FALSE;
					}
				}



				buffer[0] = i;

				nResult = IndirectCode( offset, buffer, 1 );

				if ( !nResult )
				{
					AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errInjectCodeFailed ) );
					return FALSE;
				}

				nCol++;
			}
		}

		

		nRow++;
		nCol = 1;
	}

	//////////////////////////////////////////////////////////////////////////
	//修改GK能力值
	for ( long i = GKSTARTOFFSET; i <= GKENDOFFSET; i += 8 )
	{
		//如果选中，则作修改
		if ( m_playerability_list.GetCheck( nRow ) )
		{
			for ( offset = i; offset < i+8; offset++ )
			{
				AbilityStr = m_playerability_list.GetItemText( nRow, nCol );

				CAbilityMap::CPair *pCurVal;

				int i;
				if ( nCol == 1 )
				{
					for ( i = 0; i <= 96; i++ )
					{
						pCurVal= m_GKAbilityMap.PLookup( i );

						//找到对应的映射
						if ( AbilityStr == pCurVal->value )
						{
							break;
						}
					}


				}
				else
				{
					for ( i = 0; i <= ABILITYNUMBER; i++ )
					{
						pCurVal= m_PlayerAbilityMap.PLookup( i );

						//找到对应的映射
						if ( AbilityStr == pCurVal->value )
						{
							break;
						}
					}

					//未找到映射
					if ( i > ABILITYNUMBER )
					{
						AfxMessageBox( _T("输入的能力值数值不存在，该能力值将重置为8，请重新输入") );
						i = 1;

						pCurVal= m_PlayerAbilityMap.PLookup( i );
						//重置为8
						m_playerability_list.SetItemText( nRow, nCol, pCurVal->value );

						return FALSE;
					}
				}

				buffer[0] = i;

				nResult = IndirectCode( offset, buffer, 1 );

				if ( !nResult )
				{
					AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errInjectCodeFailed ) );
					return FALSE;
				}

				nCol++;
			}
		}

		

		nRow++;
		nCol = 1;
	}
	
	if ( nResult && CPropertyPage::OnApply() )
	{
		return TRUE;
	}
	else
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errInjectCodeFailed ) );
		return FALSE;
	}
}
