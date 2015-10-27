//////////////////////////////////////////////////////////////////////////
//// CConfigInfo v1.0
// 
// 功能: 初始数据配置文件
//
// 说明: 这个类读取初始数据并将其保存在内存中，方便全局使用
//
// 作者: mazong1123

#ifndef CONFIGINFO_H
#define CONFIGINFO_H

#include <memory>

// 定义ShellExecute的返回值的错误判断标志,如果返回值
// 大于等于这个值则成功, 否则失败
#define ERROR_FLAG ((HINSTANCE)DWORD(0x20))

// 配置信息类
class CConfigInfo
{
public:

	// 错误消息类型
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
	// 参数: void
	//
	// 返回值: CConfigInfo *: 配置信息类实例
	//
	// 功能: 获取配置信息类实例
	static CConfigInfo * GetInstance();

	//////////////////////////////////////////////////////////////////////////
	//// SetObjectFilePath
	// 
	// 参数: strFilePath 目标文件路径
	//
	// 返回值: void
	//
	// 功能: 设置全局目标文件路径(即要Hack的文件路径)
	void SetObjectFilePath( const CString &strFilePath );	

	//////////////////////////////////////////////////////////////////////////
	//// GetObjectFilePath
	// 
	// 参数: void
	//
	// 返回值: CString 目标文件路径
	//
	// 功能: 获取全局目标文件路径(即要Hack的文件路径)
	CString GetObjectFilePath();

	//////////////////////////////////////////////////////////////////////////
	//// GetErrorMsg
	// 
	// 参数: eMsgType: 错误消息类型
	//
	// 返回值: CString 错误消息信息
	//
	// 功能: 获取错误消息
	CString GetErrorMsg( ErrMsg eMsgType );

	inline CString GetTshFilePath(){ return m_strTshFilePath; }		// 获取TSH文件存放路径
	inline CString GetDataFilePath(){ return m_strDataFilePath; }	// 获取Data文件存放路径
	inline CString GetToolsFilePath(){ return m_strToolsFilePath; } // 获取Tools文件存放路径
	inline CString GetHelpFilePath(){ return m_strHelpFilePath; }	// 获取Help文件存放路径

protected:
	CConfigInfo();
	virtual ~CConfigInfo();

	//////////////////////////////////////////////////////////////////////////
	//// GetProgramRootPath
	// 
	// 参数: void
	//
	// 返回值: CString 当前程序所在的目录
	//
	// 功能: 获取当前程序所在的目录
	CString GetProgramRootPath();

private:
	friend std::auto_ptr<CConfigInfo>;
	static CConfigInfo * m_pInstance;					// CConfigInfo类的唯一实例
	static std::auto_ptr<CConfigInfo> m_pInstancePtr;	// 保存唯一实例的自动指针，类销毁后自动释放实例指针

	//////////////////////////////////////////////////////////////////////////
	// 配置信息

	CString m_strObjectFilePath;	// 目标文件路径(即要Hack的文件路径)
	CString m_strTshFilePath;		// TSH文件存放路径
	CString m_strDataFilePath;		// Data文件存放路径
	CString m_strToolsFilePath;     // Tools文件存放路径
	CString m_strHelpFilePath;		// Help文件存放路径
};

#endif 