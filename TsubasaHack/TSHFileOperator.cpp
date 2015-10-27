//////////////////////////////////////////////////////////////////////////
//// CTSHFileOperator v1.0
// 
// ����: TSH�ļ���д��
//
// ˵��: �������ʶ��TSH��ʽ�ļ��Ĺ��ߣ����ڶ�дTSH�ļ�������Save()��Close()
//		 ����δʵ��
//
// ����: mazong1123

#include "StdAfx.h"
#include "TSHFileOperator.h"

#include <share.h>
#include <fstream>
#include <stdlib.h>
#include <locale>

CTSHFileOperator::CTSHFileOperator(void)
: m_TSHFile_FullText( _T("") ),
m_Game_Name( _T("") ),
m_Author_Name( _T("") ),
m_Game_Function( _T("") ),
m_Code_Info( new CodeInfo[CODENUM] ),
m_offset_num( 0 )
{

}

CTSHFileOperator::~CTSHFileOperator(void)
{

	if ( NULL != m_Code_Info )
	{
		delete []m_Code_Info;
		m_Code_Info = NULL;
	}
	
}


//////////////////////////////////////////////////////////////////////////
//�ڲ�����ʵ��

//��ȡָ������֮����Ӵ�
CString CTSHFileOperator::GetSubString( const CString &SrcStr, int FirstIndex, int LastIndex )
{
	//����������������ȷ���򷵻ؿ��ַ���
	if ( LastIndex < FirstIndex )
	{
		return _T("");
	}

	CString TempStr;
	CString SubString;

	TempStr = SrcStr.Right( SrcStr.GetLength() - FirstIndex );
	SubString = TempStr.Left( LastIndex - FirstIndex + 1 );

	return SubString;

}

//���ָ�����ֵ�����
CString CTSHFileOperator::GetSectionText( const CString &FullText, UINT uFlag )
{
	CString TitleText;

	if ( uFlag == GAMESECTION )
	{
		TitleText = _T("[Game]");
	}
	else
	{
		if ( uFlag == AUTHORSECTION )
		{
			TitleText = _T("[Author]");
		}
		else
		{
			if ( uFlag == FUNCTIONSECTION )
			{
				TitleText = _T("[Function]");
			}
			else
			{
				if ( uFlag == CODESECTION )
				{
					TitleText = _T("[Code]");
				}
			}
		}
	}

	int FirstIndex;
	int TempIndex;
	int LastIndex;

	//�ҵ�Title����
	FirstIndex = FullText.Find( TitleText, 0 );
	TempIndex = FullText.Find( _T("]"), FirstIndex );
	LastIndex = FullText.Find( _T("["), TempIndex );

	//����ò���û������
	if ( TempIndex+1 > LastIndex-1 )
	{
		return _T("");
	}

	CString ResultStr;

	//���Section����
	ResultStr = GetSubString( FullText, TempIndex+1, LastIndex-1 );
	ResultStr.Trim();

	return ResultStr; 

}

//��ȡ��Ϸ����
void CTSHFileOperator::SetGameName( const CString &FullText )
{
	CString GameSectionText;
	CString TempGameName;

	//�����Ϸ���ֵ�����
	GameSectionText = GetSectionText( FullText, GAMESECTION );

	int nIndex;
	nIndex = GameSectionText.Find( _T("="), 0 );

	//�����Ϸ���ַ���
	TempGameName = GameSectionText.Right( GameSectionText.GetLength() - nIndex -1 );
	TempGameName.Trim();

	m_Game_Name = TempGameName;

}

//��ȡ��������
void CTSHFileOperator::SetAuthorName( const CString &FullText )
{
	CString AuthorSectionText;
	CString TempAuthorName;

	//�����Ϸ���ֵ�����
	AuthorSectionText = GetSectionText( FullText, AUTHORSECTION );

	int nIndex;
	nIndex = AuthorSectionText.Find( _T("="), 0 );

	//�����Ϸ���ַ���
	TempAuthorName = AuthorSectionText.Right( AuthorSectionText.GetLength() - nIndex -1 );
	TempAuthorName.Trim();

	m_Author_Name = TempAuthorName;

}

//��ȡ����
void CTSHFileOperator::SetFunction( const CString &FullText )
{
	CString FunctionSectionText;
	CString TempFunctionName;

	//�����Ϸ���ֵ�����
	FunctionSectionText = GetSectionText( FullText, FUNCTIONSECTION );

	int nIndex;
	nIndex = FunctionSectionText.Find( _T("="), 0 );

	//�����Ϸ���ַ���
	TempFunctionName = FunctionSectionText.Right( FunctionSectionText.GetLength() - nIndex -1 );
	TempFunctionName.Trim();

	m_Game_Function = TempFunctionName;

}

//��ȡ����
void CTSHFileOperator::SetCode( const CString &FullText )
{
	CString CodeSectionText;
	CString TempOffset;
	CString TempBuffer;
	CString TempStr;

	wchar_t *TempBufferCh;
	unsigned long TempBufferHex;


	int EnterIndex = 0;

	int nCodeNum = 0;
	int nBufferNum = 0;

	//��ô��벿�ֵ�����
	CodeSectionText = GetSectionText( FullText, CODESECTION );

	int PreIndex = 0;
	int PreDotIndex = 0;
	int DotIndex = 0;
	int nIndex;
	nIndex = CodeSectionText.Find( _T("="), 0 );

	while ( nIndex != -1 )
	{
		//���ƫ�Ƶ�ַ
		TempOffset = GetSubString( CodeSectionText, PreIndex, nIndex-1 );
		TempOffset.Trim();

		wchar_t *TempOffsetCh;

		TempOffsetCh = TempOffset.GetBuffer( TempOffset.GetLength() );
		TempOffset.ReleaseBuffer();

		unsigned long TempOffsetHex;

		TempOffsetHex = wcstoul( TempOffsetCh, NULL, 16 );

		m_Code_Info[ nCodeNum ].offset = TempOffsetHex;

		//���buffer
		EnterIndex = CodeSectionText.Find( _T(";"), PreIndex );
		TempStr = GetSubString( CodeSectionText, nIndex+1, EnterIndex-1 );

		DotIndex = TempStr.Find( _T(","), PreDotIndex );
		while ( ( -1 != DotIndex ) && ( DotIndex < EnterIndex ) )
		{
			TempBuffer = GetSubString( TempStr, PreDotIndex, DotIndex-1 );
			TempBuffer.Trim();

			

			TempBufferCh = TempBuffer.GetBuffer( TempBuffer.GetLength() );
			TempBuffer.ReleaseBuffer();

			
			TempBufferHex = wcstoul( TempBufferCh, NULL, 16 );

			m_Code_Info[ nCodeNum ].buffer[ nBufferNum ] = TempBufferHex;
			m_Code_Info[ nCodeNum ].count = nBufferNum+1;

			nBufferNum++;

			PreDotIndex = DotIndex+1;
			DotIndex = TempStr.Find( _T(","), PreDotIndex );
		}

		TempBuffer = GetSubString( TempStr, PreDotIndex, TempStr.GetLength()-1 );
		TempBuffer.Trim();

		TempBufferCh = TempBuffer.GetBuffer( TempBuffer.GetLength() );
		TempBuffer.ReleaseBuffer();

		TempBufferHex = wcstoul( TempBufferCh, NULL, 16 );

		m_Code_Info[ nCodeNum ].buffer[ nBufferNum ] = TempBufferHex;
		m_Code_Info[ nCodeNum ].count = nBufferNum+1;


		nCodeNum++;
		nBufferNum = 0;
		PreDotIndex = 0;


		PreIndex = EnterIndex + 1;
		nIndex = CodeSectionText.Find( _T("="), PreIndex );

	}

	//���ƫ�Ƶ�ַ����
	m_offset_num = nCodeNum;
}


//////////////////////////////////////////////////////////////////////////
//�ӿں���ʵ��

//////////////////////////////////////////////////////////////////////////
//// Open
//
// ����: FilePathStr �ļ�·��
//
// ����ֵ: BOOL �Ƿ�ɹ�
//
// ����: ��TSHFile, ����ø�����������
BOOL CTSHFileOperator::Open( const CString &FilePathStr )
{
	CString TempStr;
	CString TempFullText = _T("");
	wchar_t TempChar[MAXSIZE];

	std::wifstream TSHFile( FilePathStr,  std::ios_base::in );
	if ( !TSHFile.is_open())
	{
		return FALSE;
	}
	else
	{
		TSHFile.imbue(std::locale("chs"));

		while ( !TSHFile.eof() )
		{
			TSHFile.getline( TempChar, MAXSIZE );

			TempStr = TempChar;
			TempFullText += TempStr;
			TempFullText += _T("\r\n");
		}

		TSHFile.close();
	}

	//���ȫ������
	m_TSHFile_FullText = TempFullText;

	//��ȡGameName
	SetGameName( m_TSHFile_FullText );

	//��ȡAuthorName
	SetAuthorName( m_TSHFile_FullText );

	//��ȡ����
	SetFunction( m_TSHFile_FullText );

	//��ȡ����
	SetCode( m_TSHFile_FullText );

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//// Save
//
// ����: FilePathStr �ļ�·��
//
// ����ֵ: BOOL �Ƿ�ɹ�
//
// ����: ������뵽TSHFile
//
// ˵��: �˺���δʵ�֣����Ժ���չ
BOOL CTSHFileOperator::Save( const CString &FilePathStr )
{
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//// Close
//
// ����: void
//
// ����ֵ: void
//
// ����: ��չ��
//
// ˵��: �˺���δʵ�֣����Ժ���չ
void CTSHFileOperator::Close()
{

}

//////////////////////////////////////////////////////////////////////////
//// GetGameName
//
// ����: void
//
// ����ֵ: CString ��Ϸ��
//
// ����: �����Ϸ����
CString CTSHFileOperator::GetGameName()
{
	return m_Game_Name;
}

//////////////////////////////////////////////////////////////////////////
//// GetAuthorName
//
// ����: void
//
// ����ֵ: CString ������
//
// ����: �����������
CString CTSHFileOperator::GetAuthorName()
{
	return m_Author_Name;
}

//////////////////////////////////////////////////////////////////////////
//// GetFunction
//
// ����: void
//
// ����ֵ: CString ��������
//
// ����: ��ù�������
CString CTSHFileOperator::GetFunction()
{
	return m_Game_Function;
}

//////////////////////////////////////////////////////////////////////////
//// GetCode
//
// ����: void
//
// ����ֵ: CodeInfo* ����
//
// ����: ��ô���
CodeInfo *CTSHFileOperator::GetCode()
{
	return m_Code_Info;
}

//////////////////////////////////////////////////////////////////////////
//// GetOffsetNum
//
// ����: void
//
// ����ֵ: int ƫ�Ƶ�ַ����
//
// ����: ���ƫ�Ƶ�ַ����
int CTSHFileOperator::GetOffsetNum()
{
	return m_offset_num;
}