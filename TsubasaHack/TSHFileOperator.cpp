//////////////////////////////////////////////////////////////////////////
//// CTSHFileOperator v1.0
// 
// 功能: TSH文件读写器
//
// 说明: 这个类是识别TSH格式文件的工具，用于读写TSH文件，其中Save()和Close()
//		 函数未实现
//
// 作者: mazong1123

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
//内部函数实现

//获取指定索引之间的子串
CString CTSHFileOperator::GetSubString( const CString &SrcStr, int FirstIndex, int LastIndex )
{
	//如果输入的索引不正确，则返回空字符串
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

//获得指定部分的内容
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

	//找到Title部分
	FirstIndex = FullText.Find( TitleText, 0 );
	TempIndex = FullText.Find( _T("]"), FirstIndex );
	LastIndex = FullText.Find( _T("["), TempIndex );

	//如果该部分没有内容
	if ( TempIndex+1 > LastIndex-1 )
	{
		return _T("");
	}

	CString ResultStr;

	//获得Section内容
	ResultStr = GetSubString( FullText, TempIndex+1, LastIndex-1 );
	ResultStr.Trim();

	return ResultStr; 

}

//读取游戏名称
void CTSHFileOperator::SetGameName( const CString &FullText )
{
	CString GameSectionText;
	CString TempGameName;

	//获得游戏部分的内容
	GameSectionText = GetSectionText( FullText, GAMESECTION );

	int nIndex;
	nIndex = GameSectionText.Find( _T("="), 0 );

	//获得游戏名字符串
	TempGameName = GameSectionText.Right( GameSectionText.GetLength() - nIndex -1 );
	TempGameName.Trim();

	m_Game_Name = TempGameName;

}

//读取作者名称
void CTSHFileOperator::SetAuthorName( const CString &FullText )
{
	CString AuthorSectionText;
	CString TempAuthorName;

	//获得游戏部分的内容
	AuthorSectionText = GetSectionText( FullText, AUTHORSECTION );

	int nIndex;
	nIndex = AuthorSectionText.Find( _T("="), 0 );

	//获得游戏名字符串
	TempAuthorName = AuthorSectionText.Right( AuthorSectionText.GetLength() - nIndex -1 );
	TempAuthorName.Trim();

	m_Author_Name = TempAuthorName;

}

//读取功能
void CTSHFileOperator::SetFunction( const CString &FullText )
{
	CString FunctionSectionText;
	CString TempFunctionName;

	//获得游戏部分的内容
	FunctionSectionText = GetSectionText( FullText, FUNCTIONSECTION );

	int nIndex;
	nIndex = FunctionSectionText.Find( _T("="), 0 );

	//获得游戏名字符串
	TempFunctionName = FunctionSectionText.Right( FunctionSectionText.GetLength() - nIndex -1 );
	TempFunctionName.Trim();

	m_Game_Function = TempFunctionName;

}

//读取代码
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

	//获得代码部分的内容
	CodeSectionText = GetSectionText( FullText, CODESECTION );

	int PreIndex = 0;
	int PreDotIndex = 0;
	int DotIndex = 0;
	int nIndex;
	nIndex = CodeSectionText.Find( _T("="), 0 );

	while ( nIndex != -1 )
	{
		//获得偏移地址
		TempOffset = GetSubString( CodeSectionText, PreIndex, nIndex-1 );
		TempOffset.Trim();

		wchar_t *TempOffsetCh;

		TempOffsetCh = TempOffset.GetBuffer( TempOffset.GetLength() );
		TempOffset.ReleaseBuffer();

		unsigned long TempOffsetHex;

		TempOffsetHex = wcstoul( TempOffsetCh, NULL, 16 );

		m_Code_Info[ nCodeNum ].offset = TempOffsetHex;

		//获得buffer
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

	//获得偏移地址总数
	m_offset_num = nCodeNum;
}


//////////////////////////////////////////////////////////////////////////
//接口函数实现

//////////////////////////////////////////////////////////////////////////
//// Open
//
// 参数: FilePathStr 文件路径
//
// 返回值: BOOL 是否成功
//
// 功能: 打开TSHFile, 并获得各个部分内容
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

	//获得全文内容
	m_TSHFile_FullText = TempFullText;

	//读取GameName
	SetGameName( m_TSHFile_FullText );

	//读取AuthorName
	SetAuthorName( m_TSHFile_FullText );

	//读取功能
	SetFunction( m_TSHFile_FullText );

	//读取代码
	SetCode( m_TSHFile_FullText );

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//// Save
//
// 参数: FilePathStr 文件路径
//
// 返回值: BOOL 是否成功
//
// 功能: 保存代码到TSHFile
//
// 说明: 此函数未实现，待以后扩展
BOOL CTSHFileOperator::Save( const CString &FilePathStr )
{
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//// Close
//
// 参数: void
//
// 返回值: void
//
// 功能: 扩展用
//
// 说明: 此函数未实现，待以后扩展
void CTSHFileOperator::Close()
{

}

//////////////////////////////////////////////////////////////////////////
//// GetGameName
//
// 参数: void
//
// 返回值: CString 游戏名
//
// 功能: 获得游戏名称
CString CTSHFileOperator::GetGameName()
{
	return m_Game_Name;
}

//////////////////////////////////////////////////////////////////////////
//// GetAuthorName
//
// 参数: void
//
// 返回值: CString 作者名
//
// 功能: 获得作者名称
CString CTSHFileOperator::GetAuthorName()
{
	return m_Author_Name;
}

//////////////////////////////////////////////////////////////////////////
//// GetFunction
//
// 参数: void
//
// 返回值: CString 功能描述
//
// 功能: 获得功能描述
CString CTSHFileOperator::GetFunction()
{
	return m_Game_Function;
}

//////////////////////////////////////////////////////////////////////////
//// GetCode
//
// 参数: void
//
// 返回值: CodeInfo* 代码
//
// 功能: 获得代码
CodeInfo *CTSHFileOperator::GetCode()
{
	return m_Code_Info;
}

//////////////////////////////////////////////////////////////////////////
//// GetOffsetNum
//
// 参数: void
//
// 返回值: int 偏移地址总数
//
// 功能: 获得偏移地址总数
int CTSHFileOperator::GetOffsetNum()
{
	return m_offset_num;
}