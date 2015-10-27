//////////////////////////////////////////////////////////////////////////
//// CConfigInfo v1.0
// 
// ����: ��ʼ���������ļ�
//
// ˵��: ������ȡ��ʼ���ݲ����䱣�����ڴ��У�����ȫ��ʹ��
//
// ����: mazong1123

#ifndef CONFIGINFO_H
#define CONFIGINFO_H

#include <memory>

// ����ShellExecute�ķ���ֵ�Ĵ����жϱ�־,�������ֵ
// ���ڵ������ֵ��ɹ�, ����ʧ��
#define ERROR_FLAG ((HINSTANCE)DWORD(0x20))

// ������Ϣ��
class CConfigInfo
{
public:

	// ������Ϣ����
	typedef enum
	{
		errSuccess,
		errOpenFileFailed,
		errOpenPlayerInfoFileFailed,
		errSetPlayerAbilityBeforeChooseFile,
		errSetCustomPageBeforeChooseFile,
		errInjectCodeFailed
	} ErrMsg;

	//////////////////////////////////////////////////////////////////////////
	//// GetInstance
	// 
	// ����: void
	//
	// ����ֵ: CConfigInfo *: ������Ϣ��ʵ��
	//
	// ����: ��ȡ������Ϣ��ʵ��
	static CConfigInfo * GetInstance();

	//////////////////////////////////////////////////////////////////////////
	//// SetObjectFilePath
	// 
	// ����: strFilePath Ŀ���ļ�·��
	//
	// ����ֵ: void
	//
	// ����: ����ȫ��Ŀ���ļ�·��(��ҪHack���ļ�·��)
	void SetObjectFilePath( const CString &strFilePath );	

	//////////////////////////////////////////////////////////////////////////
	//// GetObjectFilePath
	// 
	// ����: void
	//
	// ����ֵ: CString Ŀ���ļ�·��
	//
	// ����: ��ȡȫ��Ŀ���ļ�·��(��ҪHack���ļ�·��)
	CString GetObjectFilePath();

	//////////////////////////////////////////////////////////////////////////
	//// GetErrorMsg
	// 
	// ����: eMsgType: ������Ϣ����
	//
	// ����ֵ: CString ������Ϣ��Ϣ
	//
	// ����: ��ȡ������Ϣ
	CString GetErrorMsg( ErrMsg eMsgType );

	inline CString GetTshFilePath(){ return m_strTshFilePath; }		// ��ȡTSH�ļ����·��
	inline CString GetDataFilePath(){ return m_strDataFilePath; }	// ��ȡData�ļ����·��
	inline CString GetToolsFilePath(){ return m_strToolsFilePath; } // ��ȡTools�ļ����·��
	inline CString GetHelpFilePath(){ return m_strHelpFilePath; }	// ��ȡHelp�ļ����·��

protected:
	CConfigInfo();
	virtual ~CConfigInfo();

	//////////////////////////////////////////////////////////////////////////
	//// GetProgramRootPath
	// 
	// ����: void
	//
	// ����ֵ: CString ��ǰ�������ڵ�Ŀ¼
	//
	// ����: ��ȡ��ǰ�������ڵ�Ŀ¼
	CString GetProgramRootPath();

private:
	friend std::auto_ptr<CConfigInfo>;
	static CConfigInfo * m_pInstance;					// CConfigInfo���Ψһʵ��
	static std::auto_ptr<CConfigInfo> m_pInstancePtr;	// ����Ψһʵ�����Զ�ָ�룬�����ٺ��Զ��ͷ�ʵ��ָ��

	//////////////////////////////////////////////////////////////////////////
	// ������Ϣ

	CString m_strObjectFilePath;	// Ŀ���ļ�·��(��ҪHack���ļ�·��)
	CString m_strTshFilePath;		// TSH�ļ����·��
	CString m_strDataFilePath;		// Data�ļ����·��
	CString m_strToolsFilePath;     // Tools�ļ����·��
	CString m_strHelpFilePath;		// Help�ļ����·��
};

#endif 