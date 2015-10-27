//////////////////////////////////////////////////////////////////////////
//// CTsubasaHackDlg
// 
// 功能: 常规选项的全部功能
//
// 说明: 由于是从1.0版本升级来的，1.0版本仅有常规选项的内容，
// 1.1版本中虽然这只是三个选项卡中的一个，但仍保留CTsubasaHackDlg类名
// 由于是早期代码，风格非常烂，界面和数据没有分离，看起来可能有点累，
// 各位见谅~


// TsubasaHackDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "TTComboBox.h"

#define  TEAMNUMBER 37
#define  PLAYERNUMBER 117
#define  COLORNUMBER 61
#define  FIGUERNUMBER 16
#define  GKNUMBER 12
#define  GKSKLNUMBER 4



//球队信息的结构体
struct TEAMINFO 
{	
	CString id;				//球队id
	CString name;			//球队名称
	CString playersID[21];	//如果不是明星队员，则id为0，否则为1
	long offset[21];		//球队21个球员占位的偏移地址，如果该占位不存在，则为0
};

//球员信息的结构体
struct PLAYERINFO 
{
	CString id;				//球员id
	CString name;			//球员名称
	char playercode;		//球员的修改代码

};


//人物颜色地址的结构体
struct PLAYERCLRADDR 
{
	CString id;            //人物id
	long offset[4];        //人物肤色，发色，上衣色，短裤色的偏移地址
};

//颜色信息的结构体
struct CLRINFO 
{
	CString id;             //颜色id
	char clrcode;           //颜色代码
};

//人物造型地址的结构体
struct PLAYERFIGADDR 
{
	CString id;            //人物id
	long offset;           //人物造型的偏移地址
};


//造型信息的结构体
struct FIGINFO 
{
	CString id;            //造型id
	char figcode;          //造型代码
};

//GK人物信息结构体
struct GKINFO 
{
	CString id;
	char gkcode;
};

//GK必杀技信息结构体
struct GKSKLINFO 
{
	CString id;			//必杀技id
	char sklcode;		//必杀技代码
};


// CTsubasaHackDlg 对话框
class CTsubasaHackDlg : public CPropertyPage
{
// 构造
public:
	CTsubasaHackDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TSUBASAHACK_DIALOG };

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog();	// 初始化对话框

	//初始化球队信息
	BOOL InitiateTeamInfomation(); 
	//根据当前选择的队伍判断应该ENABLE的球员下拉列表
	void EnablePlayerComboBox(int TeamID);
	void AddPlayerName();
	void DeletePlayerName();
	void AddPlayerClrName();
	void AddPlayerFigName();

	//读取球队信息
	void LoadTeamInfo();
	//读取球员信息
	void LoadPlayerInfo();
	//注入代码
	void IndirectCode( long offset, char *buffer, size_t count );
	//从Combo中的球员数据中取出球员ID;
	CString GetIDFromPlayerCombo( CString PlayerData );
	//获得当前文件路径
	CString GetFilePathName();

	afx_msg void OnBnClickedFileselect();

	DECLARE_MESSAGE_MAP()

	// 生成的消息映射函数
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	afx_msg void OnBnClickedOndecide();
	afx_msg void OnCbnSelendokTeamselect();
	afx_msg void OnBnClickedResetButton();
	afx_msg void OnBnClickedOndecidedclrButton();
	afx_msg void OnBnClickedOnclearclrbutton();
	afx_msg void OnCbnSelendokCharacterclrCombo();
	afx_msg void OnBnClickedOndecidedfigureButton();
	afx_msg void OnBnClickedFigureclrButton();
	afx_msg void OnCbnSelendokCharacterfiguerCombo();
	afx_msg void OnBnClickedOndecidedgk1Button();
	afx_msg void OnBnClickedGkclr1Button();
	afx_msg void OnCbnSelendokGksel1Combo();
	afx_msg void OnBnClickedOndecidedgk2Button();
	afx_msg void OnBnClickedGkclr2Button();
	afx_msg void OnCbnSelendokGksel2Combo();
	afx_msg void OnBnClickedOndecidedgk3Button();
	afx_msg void OnBnClickedGkclr3Button();
	afx_msg void OnCbnSelendokGksel3Combo();
	afx_msg void OnBnClickedInject1Button();
	afx_msg void OnBnClickedInject2Button();
	afx_msg void OnEnChangeFilenamebox();

private:
	HICON m_hIcon;
	TEAMINFO m_teaminformation[TEAMNUMBER]; 
	PLAYERINFO m_playerinformation[PLAYERNUMBER];

	PLAYERCLRADDR m_playerclraddr[PLAYERNUMBER+43];
	CLRINFO m_clrinfomation[COLORNUMBER];

	PLAYERFIGADDR m_playerfigaddr[PLAYERNUMBER];
	FIGINFO m_figinfomation[FIGUERNUMBER];

	GKINFO m_gkinformation[GKNUMBER];
	GKSKLINFO m_gksklinformation[GKSKLNUMBER];

	BOOL m_IsIndirectSuccess;

	//用户指定的文件路径和文件名
	CString m_FilePathName;
	//存放文件路径的Edit
	CEdit m_filenamebox;
	//球队选择下拉列表框变量
	CTTComboBox m_TeamSelectBox;

	//球员下拉列表框变量	
	CTTComboBox m_PlayerSelectBox1;
	CTTComboBox m_PlayerSelectBox2;
	CTTComboBox m_PlayerSelectBox3;
	CTTComboBox m_PlayerSelectBox4;
	CTTComboBox m_PlayerSelectBox5;
	CTTComboBox m_PlayerSelectBox6;
	CTTComboBox m_PlayerSelectBox7;
	CTTComboBox m_PlayerSelectBox8;
	CTTComboBox m_PlayerSelectBox9;
	CTTComboBox m_PlayerSelectBox10;
	CTTComboBox m_PlayerSelectBox11;
	CTTComboBox m_PlayerSelectBox12;
	CTTComboBox m_PlayerSelectBox13;
	CTTComboBox m_PlayerSelectBox14;
	CTTComboBox m_PlayerSelectBox15;
	CTTComboBox m_PlayerSelectBox16;
	CTTComboBox m_PlayerSelectBox17;
	CTTComboBox m_PlayerSelectBox18;
	CTTComboBox m_PlayerSelectBox19;
	CTTComboBox m_PlayerSelectBox20;
	CTTComboBox m_PlayerSelectBox21;

	CEdit m_patch1_edit;
	CEdit m_patch2_edit;

	CTTComboBox m_gkskl1_combo;
	CTTComboBox m_gkskl2_combo;
	CTTComboBox m_gkskl3_combo;
	CTTComboBox m_gksel1_combo;
	CTTComboBox m_gksel2_combo;
	CTTComboBox m_gksel3_combo;
	CTTComboBox m_figuresel_combo;
	CTTComboBox m_characterfiguer_combo;
	CTTComboBox m_skinclr_combo;
	CTTComboBox m_hairclr_combo;
	CTTComboBox m_shirtclr_combo;
	CTTComboBox m_trousersclr_combo;
	CTTComboBox m_characterclr_combo;

};
