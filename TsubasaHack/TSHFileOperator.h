//////////////////////////////////////////////////////////////////////////
//// CTSHFileOperator v1.0
// 
// ����: TSH�ļ���д��
//
// ˵��: �������ʶ��TSH��ʽ�ļ��Ĺ��ߣ����ڶ�дTSH�ļ�������Save()��Close()
//		 ����δʵ��
//
// ����: mazong1123

#pragma once

#define MAXSIZE 1000
#define GAMESECTION 0
#define AUTHORSECTION 1
#define FUNCTIONSECTION 2
#define CODESECTION 3
#define CODENUM 255

// ������Ϣ�ṹ��
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
	//�ӿں���

	//////////////////////////////////////////////////////////////////////////
	//// Open
	//
	// ����: FilePathStr �ļ�·��
	//
	// ����ֵ: BOOL �Ƿ�ɹ�
	//
	// ����: ��TSHFile, ����ø�����������
	BOOL Open( const CString &FilePathStr );

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
	BOOL Save( const CString &FilePathStr );

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
	void Close();

	//////////////////////////////////////////////////////////////////////////
	//// GetGameName
	//
	// ����: void
	//
	// ����ֵ: CString ��Ϸ��
	//
	// ����: �����Ϸ����
	CString GetGameName();

	//////////////////////////////////////////////////////////////////////////
	//// GetAuthorName
	//
	// ����: void
	//
	// ����ֵ: CString ������
	//
	// ����: �����������
	CString GetAuthorName();


	//////////////////////////////////////////////////////////////////////////
	//// GetFunction
	//
	// ����: void
	//
	// ����ֵ: CString ��������
	//
	// ����: ��ù�������
	CString GetFunction();

	//////////////////////////////////////////////////////////////////////////
	//// GetCode
	//
	// ����: void
	//
	// ����ֵ: CodeInfo* ����
	//
	// ����: ��ô���
	CodeInfo *GetCode();

	//////////////////////////////////////////////////////////////////////////
	//// GetOffsetNum
	//
	// ����: void
	//
	// ����ֵ: int ƫ�Ƶ�ַ����
	//
	// ����: ���ƫ�Ƶ�ַ����
	int GetOffsetNum();

protected:
	//////////////////////////////////////////////////////////////////////////
	//�ڲ�����

	//��ȡָ������֮����Ӵ�
	CString GetSubString( const CString &SrcStr, int FirstIndex, int LastIndex );

	//���ָ�����ֵ�����
	CString GetSectionText( const CString &FullText, UINT uFlag );

	//��ȡ��Ϸ����
	void SetGameName( const CString &FullText );

	//��ȡ��������
	void SetAuthorName( const CString &FullText );

	//��ȡ����
	void SetFunction( const CString &FullText );

	//��ȡ����
	void SetCode( const CString &FullText );

private:
	//////////////////////////////////////////////////////////////////////////
	//���ݳ�Ա

	//TSHFileȫ������
	CString m_TSHFile_FullText;

	//��Ϸ����
	CString m_Game_Name;

	//��������
	CString m_Author_Name;

	//��������
	CString m_Game_Function;

	//������Ϣ
	CodeInfo *m_Code_Info;

	//ƫ�Ƶ�ַ����
	int m_offset_num;




};
