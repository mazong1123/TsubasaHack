//////////////////////////////////////////////////////////////////////////
//// CPlayerAbilityPage
// 
// ����: ����ֵ�޸�ҳ
//
// ˵��: 1.1������ӵĹ��ܣ��޸���������ֵ
//
// ����: mazong1123

// PlayerAbilityPage.cpp : ʵ���ļ�
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


// CPlayerAbilityPage �Ի���

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
	//�������ڴ�С

	CRect *pRect;

	pRect = new CRect;
	GetParent()->GetWindowRect( pRect );
	m_playerability_list.SetWindowPos( NULL, 0, 0, pRect->Width()-50, pRect->Height()-180,  SWP_NOMOVE );
	delete pRect;
	pRect = NULL;

	m_refresh_button.SetWindowPos( NULL, 280, 550, 0, 0, SWP_NOSIZE );
	m_selectall_button.SetWindowPos( NULL, 390, 550, 0, 0, SWP_NOSIZE );
	
	//����ӳ���ϵ
	InitAbilityMap();

	//��ʼ���б�ؼ�
	InitListCtrl();

	//��ȡ����
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
		AfxMessageBox( _T("Player���������ļ���ʧ�ܣ�") );
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

			//���16�����ַ���
			HexStr = PlayerAbility.Left( nIndex );

			//���10�����ַ���
			DecStr = PlayerAbility.Right( PlayerAbility.GetLength() - nIndex -1 );

			//��CStringת����Int
			wchar_t *pHexCh;
			pHexCh = HexStr.GetBuffer( HexStr.GetLength() );
			HexStr.ReleaseBuffer();

			int HexInt;
			HexInt = _wtoi( pHexCh );

			//����ӳ���ϵ
			m_PlayerAbilityMap[ HexInt ] = DecStr;


		}

		PlayerAbilityFile.close();
	}

	std::wifstream GKAbilityFile( CConfigInfo::GetInstance()->GetDataFilePath() + _T("GKAbility.dat"),  std::ios_base::in );
	if ( !GKAbilityFile.is_open() )
	{
		AfxMessageBox( _T("GK���������ļ���ʧ�ܣ�") );
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

			//���16�����ַ���
			HexStr = PlayerAbility.Left( nIndex );

			//���10�����ַ���
			DecStr = PlayerAbility.Right( PlayerAbility.GetLength() - nIndex -1 );

			//��CStringת����Int
			wchar_t *pHexCh;
			pHexCh = HexStr.GetBuffer( HexStr.GetLength() );
			HexStr.ReleaseBuffer();

			int HexInt;
			HexInt = _wtoi( pHexCh );

			//����ӳ���ϵ
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
		//��ȡ��Ա����ֵ
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

					//��ȡ����ֵ
					AbilityStr = pCurVal->value;

					m_playerability_list.SetItemText( nRow, nCol, AbilityStr );
					nCol++;

				}
			}

			nCol = 2;
			nRow++;

		}
		
		//////////////////////////////////////////////////////////////////////////
		//��ȡ����Ա����ֵ
		
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

					//��ȡ����ֵ
					AbilityStr = pCurVal->value;

					m_playerability_list.SetItemText( nRow, nCol, AbilityStr );
					nCol++;

				}
			}

			for ( int j = 9; j < 24; j++ )
			{
				m_playerability_list.SetItemText( nRow, j, _T("��Ч") );
			}

			nRow++;
			nCol = 2;
		}

		//////////////////////////////////////////////////////////////////////////
		//��ȡ��Ա����

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

				//��ȡ����ֵ
				AbilityStr = pCurVal->value;
				CString TempStr;

				m_playerability_list.SetItemText( nRow, nCol, AbilityStr );
				

			}

			nRow++;

		}
		
		//////////////////////////////////////////////////////////////////////////
		//��ȡ����Ա����

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

				//��ȡ����ֵ
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

	m_playerability_list.InsertColumn( nColIndex, _T("����"), LVCFMT_LEFT, 145, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("����"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("ƽ������(GK����)"), LVCFMT_LEFT, 110, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("����(GK����)"), LVCFMT_LEFT, 90, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("����(GK����)"), LVCFMT_LEFT, 90, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("����(GK������)"), LVCFMT_LEFT, 100, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("����(GK������)"), LVCFMT_LEFT, 100, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("����(GK�Ϳճ���)"), LVCFMT_LEFT, 110, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("�Ϳ�����(GK�߿ճ���)"), LVCFMT_LEFT, 140, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("?"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("�Ϳ�ͣ��"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("�Ϳ�©��"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("?"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("�Ϳս�Χ"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("�Ϳ�����"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("?"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("�߿�����"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("?"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("�߿�ͣ��"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("�߿�©��"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("?"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("�߿ս�Χ"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("�߿�����"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	m_playerability_list.InsertColumn( nColIndex, _T("?"), LVCFMT_LEFT, 70, 0 );
	nColIndex++;

	//////////////////////////////////////////////////////////////////////////
	//��ȡ��Ա����
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
			//��ȡ��Աid
			HomePageFile >> URLTempChar;
			PlayerInfo = URLTempChar;
			PlayerName = PlayerInfo;

			//��ȡ��Ա����
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


// CPlayerAbilityPage ��Ϣ�������
void CPlayerAbilityPage::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	SetModified();

	*pResult = 0;
	
}

void CPlayerAbilityPage::OnBnClickedRefreshButton()
{	
	//��ȡ����
	GetDataForListCtrl();
}

void CPlayerAbilityPage::OnBnClickedSelectAllButton()
{
	CString TempStr;

	m_selectall_button.GetWindowText( TempStr );

	if ( TempStr == _T("ȫѡ") )
	{
		//����Item��Ϊѡ��״̬
		for ( int i = 0; i < m_playerability_list.GetItemCount(); i++ )
		{
			m_playerability_list.SetCheck( i );
		}

		m_selectall_button.SetWindowText( _T("ȫ��ȡ��") );
	}
	else
	{
		//����Item��Ϊ��ѡ��״̬
		for ( int i = 0; i < m_playerability_list.GetItemCount(); i++ )
		{
			m_playerability_list.SetCheck( i, FALSE );
		}

		m_selectall_button.SetWindowText( _T("ȫѡ") );
	}
	
}

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
	//�޸���Ա����ֵ
	for ( long i = STARTOFFSET; i <= ENDOFFSET; i += 24 )
	{
		//���ѡ�У������޸�
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

						//�ҵ���Ӧ��ӳ��
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

						//�ҵ���Ӧ��ӳ��
						if ( AbilityStr == pCurVal->value )
						{
							break;
						}
					}

					//δ�ҵ�ӳ��
					if ( i > ABILITYNUMBER )
					{
						AfxMessageBox( _T("���������ֵ��ֵ�����ڣ�������ֵ������Ϊ8������������") );
						i = 1;

						pCurVal= m_PlayerAbilityMap.PLookup( i );
						//����Ϊ8
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
	//�޸�GK����ֵ
	for ( long i = GKSTARTOFFSET; i <= GKENDOFFSET; i += 8 )
	{
		//���ѡ�У������޸�
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

						//�ҵ���Ӧ��ӳ��
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

						//�ҵ���Ӧ��ӳ��
						if ( AbilityStr == pCurVal->value )
						{
							break;
						}
					}

					//δ�ҵ�ӳ��
					if ( i > ABILITYNUMBER )
					{
						AfxMessageBox( _T("���������ֵ��ֵ�����ڣ�������ֵ������Ϊ8������������") );
						i = 1;

						pCurVal= m_PlayerAbilityMap.PLookup( i );
						//����Ϊ8
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
