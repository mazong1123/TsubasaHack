//////////////////////////////////////////////////////////////////////////
//// CTSHFileOperator v1.0
// 
// 功能: TSH文件读写器
//
// 说明: 这个类是识别TSH格式文件的工具，用于读写TSH文件，其中Save()和Close()
//		 函数未实现
//
// 作者: mazong1123

#pragma once

#define MAXSIZE 1000
#define GAMESECTION 0
#define AUTHORSECTION 1
#define FUNCTIONSECTION 2
#define CODESECTION 3
#define CODENUM 255

// 代码信息结构体
struct CodeInfo 
{
	unsigned long offset;
	unsigned long buffer[255];
	size_t count;
};


class CTSHFileOperator
{
public:
	CTSHFileOperator(void);
	~CTSHFileOperator(void);


	//////////////////////////////////////////////////////////////////////////
	//接口函数

	//////////////////////////////////////////////////////////////////////////
	//// Open
	//
	// 参数: FilePathStr 文件路径
	//
	// 返回值: BOOL 是否成功
	//
	// 功能: 打开TSHFile, 并获得各个部分内容
	BOOL Open( const CString &FilePathStr );

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
	BOOL Save( const CString &FilePathStr );

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
	void Close();

	//////////////////////////////////////////////////////////////////////////
	//// GetGameName
	//
	// 参数: void
	//
	// 返回值: CString 游戏名
	//
	// 功能: 获得游戏名称
	CString GetGameName();

	//////////////////////////////////////////////////////////////////////////
	//// GetAuthorName
	//
	// 参数: void
	//
	// 返回值: CString 作者名
	//
	// 功能: 获得作者名称
	CString GetAuthorName();


	//////////////////////////////////////////////////////////////////////////
	//// GetFunction
	//
	// 参数: void
	//
	// 返回值: CString 功能描述
	//
	// 功能: 获得功能描述
	CString GetFunction();

	//////////////////////////////////////////////////////////////////////////
	//// GetCode
	//
	// 参数: void
	//
	// 返回值: CodeInfo* 代码
	//
	// 功能: 获得代码
	CodeInfo *GetCode();

	//////////////////////////////////////////////////////////////////////////
	//// GetOffsetNum
	//
	// 参数: void
	//
	// 返回值: int 偏移地址总数
	//
	// 功能: 获得偏移地址总数
	int GetOffsetNum();

protected:
	//////////////////////////////////////////////////////////////////////////
	//内部函数

	//获取指定索引之间的子串
	CString GetSubString( const CString &SrcStr, int FirstIndex, int LastIndex );

	//获得指定部分的内容
	CString GetSectionText( const CString &FullText, UINT uFlag );

	//读取游戏名称
	void SetGameName( const CString &FullText );

	//读取作者名称
	void SetAuthorName( const CString &FullText );

	//读取功能
	void SetFunction( const CString &FullText );

	//读取代码
	void SetCode( const CString &FullText );

private:
	//////////////////////////////////////////////////////////////////////////
	//数据成员

	//TSHFile全文内容
	CString m_TSHFile_FullText;

	//游戏名称
	CString m_Game_Name;

	//作者名称
	CString m_Author_Name;

	//补丁功能
	CString m_Game_Function;

	//代码信息
	CodeInfo *m_Code_Info;

	//偏移地址总数
	int m_offset_num;




};
