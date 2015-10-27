//////////////////////////////////////////////////////////////////////////
//// CTsubasaHackDlg
// 
// 功能: 常规选项的全部功能
//
// 说明: 由于是从1.0版本升级来的，1.0版本仅有常规选项的内容，
// 1.1版本中虽然这只是三个选项卡中的一个，但仍保留CTsubasaHackDlg类名
// 由于是早期代码，风格非常烂，界面和数据没有分离，看起来可能有点累，
// 各位见谅~

// TsubasaHackDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TsubasaHack.h"
#include "TsubasaHackDlg.h"
#include <share.h>
#include <fstream>
#include <stdlib.h>
#include <locale>

#include "AboutDlg.h"
#include "TSHSheet.h"
#include "PlayerAbilityPage.h"
#include "ConfigInfo.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTsubasaHackDlg 对话框

CTsubasaHackDlg::CTsubasaHackDlg(CWnd* pParent /*=NULL*/)
: CPropertyPage(IDD_TSUBASAHACK_DIALOG)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAIN_ICON);
	m_IsIndirectSuccess = FALSE;
}

void CTsubasaHackDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILENAMEBOX, m_filenamebox);
	DDX_Control(pDX, IDC_TEAMSELECT, m_TeamSelectBox);
	DDX_Control(pDX, IDC_PLAYER1, m_PlayerSelectBox1);
	DDX_Control(pDX, IDC_PLAYER2, m_PlayerSelectBox2);
	DDX_Control(pDX, IDC_PLAYER3, m_PlayerSelectBox3);
	DDX_Control(pDX, IDC_PLAYER4, m_PlayerSelectBox4);
	DDX_Control(pDX, IDC_PLAYER5, m_PlayerSelectBox5);
	DDX_Control(pDX, IDC_PLAYER6, m_PlayerSelectBox6);
	DDX_Control(pDX, IDC_PLAYER7, m_PlayerSelectBox7);
	DDX_Control(pDX, IDC_PLAYER8, m_PlayerSelectBox8);
	DDX_Control(pDX, IDC_PLAYER9, m_PlayerSelectBox9);
	DDX_Control(pDX, IDC_PLAYER10, m_PlayerSelectBox10);
	DDX_Control(pDX, IDC_PLAYER11, m_PlayerSelectBox11);
	DDX_Control(pDX, IDC_BENCHPLAYERGK1, m_PlayerSelectBox12);
	DDX_Control(pDX, IDC_BENCHPLAYERGK2, m_PlayerSelectBox13);
	DDX_Control(pDX, IDC_BENCHPLAYER1, m_PlayerSelectBox14);
	DDX_Control(pDX, IDC_BENCHPLAYER2, m_PlayerSelectBox15);
	DDX_Control(pDX, IDC_BENCHPLAYER3, m_PlayerSelectBox16);
	DDX_Control(pDX, IDC_BENCHPLAYER4, m_PlayerSelectBox17);
	DDX_Control(pDX, IDC_BENCHPLAYER5, m_PlayerSelectBox18);
	DDX_Control(pDX, IDC_BENCHPLAYER6, m_PlayerSelectBox19);
	DDX_Control(pDX, IDC_BENCHPLAYER7, m_PlayerSelectBox20);
	DDX_Control(pDX, IDC_BENCHPLAYER8, m_PlayerSelectBox21);
	DDX_Control(pDX, IDC_CHARACTERCLR_COMBO, m_characterclr_combo);
	DDX_Control(pDX, IDC_SKINCLR_COMBO, m_skinclr_combo);
	DDX_Control(pDX, IDC_HAIRCLR_COMBO, m_hairclr_combo);
	DDX_Control(pDX, IDC_SHIRTCLR_COMBO, m_shirtclr_combo);
	DDX_Control(pDX, IDC_TROUSERSCLR_COMBO, m_trousersclr_combo);
	DDX_Control(pDX, IDC_FIGURESEL_COMBO, m_figuresel_combo);
	DDX_Control(pDX, IDC_CHARACTERFIGUER_COMBO, m_characterfiguer_combo);
	DDX_Control(pDX, IDC_GKSKL1_COMBO, m_gkskl1_combo);
	DDX_Control(pDX, IDC_GKSKL2_COMBO, m_gkskl2_combo);
	DDX_Control(pDX, IDC_GKSKL3_COMBO, m_gkskl3_combo);
	DDX_Control(pDX, IDC_GKSEL1_COMBO, m_gksel1_combo);
	DDX_Control(pDX, IDC_GKSEL2_COMBO, m_gksel2_combo);
	DDX_Control(pDX, IDC_GKSEL3_COMBO, m_gksel3_combo);
	DDX_Control(pDX, IDC_PATCH1_EDIT, m_patch1_edit);
	DDX_Control(pDX, IDC_PATCH2_EDIT, m_patch2_edit);
}

BEGIN_MESSAGE_MAP(CTsubasaHackDlg, CPropertyPage)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDFILESELECT, &CTsubasaHackDlg::OnBnClickedFileselect)
	ON_BN_CLICKED(IDONDECIDE, &CTsubasaHackDlg::OnBnClickedOndecide)
	ON_CBN_SELENDOK(IDC_TEAMSELECT, &CTsubasaHackDlg::OnCbnSelendokTeamselect)
	ON_BN_CLICKED(IDC_RESET_BUTTON, &CTsubasaHackDlg::OnBnClickedResetButton)
	
	
	
	ON_BN_CLICKED(IDC_ONDECIDEDCLR_BUTTON, &CTsubasaHackDlg::OnBnClickedOndecidedclrButton)
	ON_BN_CLICKED(IDC_ONCLEARCLRBUTTON, &CTsubasaHackDlg::OnBnClickedOnclearclrbutton)
	ON_CBN_SELENDOK(IDC_CHARACTERCLR_COMBO, &CTsubasaHackDlg::OnCbnSelendokCharacterclrCombo)
	ON_BN_CLICKED(IDC_ONDECIDEDFIGURE_BUTTON, &CTsubasaHackDlg::OnBnClickedOndecidedfigureButton)
	ON_BN_CLICKED(IDC_FIGURECLR_BUTTON, &CTsubasaHackDlg::OnBnClickedFigureclrButton)
	ON_CBN_SELENDOK(IDC_CHARACTERFIGUER_COMBO, &CTsubasaHackDlg::OnCbnSelendokCharacterfiguerCombo)
	ON_BN_CLICKED(IDC_ONDECIDEDGK1_BUTTON, &CTsubasaHackDlg::OnBnClickedOndecidedgk1Button)
	ON_BN_CLICKED(IDC_GKCLR1_BUTTON, &CTsubasaHackDlg::OnBnClickedGkclr1Button)
	ON_CBN_SELENDOK(IDC_GKSEL1_COMBO, &CTsubasaHackDlg::OnCbnSelendokGksel1Combo)
	ON_BN_CLICKED(IDC_ONDECIDEDGK2_BUTTON, &CTsubasaHackDlg::OnBnClickedOndecidedgk2Button)
	ON_BN_CLICKED(IDC_GKCLR2_BUTTON, &CTsubasaHackDlg::OnBnClickedGkclr2Button)
	ON_CBN_SELENDOK(IDC_GKSEL2_COMBO, &CTsubasaHackDlg::OnCbnSelendokGksel2Combo)
	ON_BN_CLICKED(IDC_ONDECIDEDGK3_BUTTON, &CTsubasaHackDlg::OnBnClickedOndecidedgk3Button)
	ON_BN_CLICKED(IDC_GKCLR3_BUTTON, &CTsubasaHackDlg::OnBnClickedGkclr3Button)
	ON_CBN_SELENDOK(IDC_GKSEL3_COMBO, &CTsubasaHackDlg::OnCbnSelendokGksel3Combo)
	ON_BN_CLICKED(IDC_INJECT1_BUTTON, &CTsubasaHackDlg::OnBnClickedInject1Button)
	ON_BN_CLICKED(IDC_INJECT2_BUTTON, &CTsubasaHackDlg::OnBnClickedInject2Button)
	ON_EN_CHANGE(IDC_FILENAMEBOX, &CTsubasaHackDlg::OnEnChangeFilenamebox)
END_MESSAGE_MAP()


// CTsubasaHackDlg 消息处理程序

BOOL CTsubasaHackDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	if ( !InitiateTeamInfomation() )
	{
		AfxMessageBox( _T("初始化失败") );
		exit(-1);
	}
	
	



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTsubasaHackDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CPropertyPage::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTsubasaHackDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPropertyPage::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTsubasaHackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CTsubasaHackDlg::InitiateTeamInfomation()
{
	CString TempString;
	int i;
	int j = 0;
	int k = 0;
	int Index = 0;

	//初始化球队信息结构体
	LoadTeamInfo();

	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//圣保罗球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0x4A57;
	m_teaminformation[Index].offset[1] = 0x4A58;
	m_teaminformation[Index].offset[2] = 0x4A59;
	m_teaminformation[Index].offset[3] = 0x4A5A;
	m_teaminformation[Index].offset[4] = 0x4A5B;
	m_teaminformation[Index].offset[5] = 0x4A5C;
	m_teaminformation[Index].offset[6] = 0x4A5D;
	m_teaminformation[Index].offset[7] = 0x4A5E;
	m_teaminformation[Index].offset[8] = 0x4A5F;
	m_teaminformation[Index].offset[9] = 0x4A60;
	m_teaminformation[Index].offset[10] = 0x4A61;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//科林西斯蒂安球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BB1C;
	m_teaminformation[Index].offset[9] = 0x3BB1A;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//格雷米奥球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0x3BB2A;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BB28;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//帕尔梅拉斯球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BB36;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0x3BB38;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//桑托斯球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0x3BB46;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BB44;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//弗拉门戈球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0x3BB56;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0x3BB54;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0;
	m_teaminformation[Index].offset[9] = 0x3BB52;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//南葛球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0x4A63;
	m_teaminformation[Index].offset[1] = 0x4A64;
	m_teaminformation[Index].offset[2] = 0x4A65;
	m_teaminformation[Index].offset[3] = 0x4A66;
	m_teaminformation[Index].offset[4] = 0x4A67;
	m_teaminformation[Index].offset[5] = 0x4A68;
	m_teaminformation[Index].offset[6] = 0x4A69;
	m_teaminformation[Index].offset[7] = 0x4A6A;
	m_teaminformation[Index].offset[8] = 0x4A6B;
	m_teaminformation[Index].offset[9] = 0x4A6C;
	m_teaminformation[Index].offset[10] = 0x4A6D;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//国见高中球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0x3BB62;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BB64;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//花轮高中球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BB70;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0x3BB72;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//立波高中球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0x3BB80;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0x3BB7E;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//武藏高中(下)球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0;
	m_teaminformation[Index].offset[9] = 0x3DBFF;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//富良野球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0;
	m_teaminformation[Index].offset[9] = 0x3BB96;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//东邦学园球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0x3BBA8;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0x3BBA6;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BBA2;
	m_teaminformation[Index].offset[9] = 0x3BBA4;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//罗马球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0;
	m_teaminformation[Index].offset[9] = 0x3BBB4;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//乌拉圭球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BBC2;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0x3BBC0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//汉堡球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0x3BBD4;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0x3BBD2;
	m_teaminformation[Index].offset[6] = 0x3BBCE;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0;
	m_teaminformation[Index].offset[9] = 0x3BBD0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//全日本球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0x3BBF4;
	m_teaminformation[Index].offset[1] = 0x3BBEC;
	m_teaminformation[Index].offset[2] = 0x3BBF0;
	m_teaminformation[Index].offset[3] = 0x3BBEE;
	m_teaminformation[Index].offset[4] = 0x3BBF2;
	m_teaminformation[Index].offset[5] = 0x3BBE4;
	m_teaminformation[Index].offset[6] = 0x3BBEA;
	m_teaminformation[Index].offset[7] = 0x3BBE8;
	m_teaminformation[Index].offset[8] = 0x3BBE0;
	m_teaminformation[Index].offset[9] = 0x3BBE6;
	m_teaminformation[Index].offset[10] = 0x3BBE2;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//日本青年球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0x4A6F;
	m_teaminformation[Index].offset[1] = 0x4A70;
	m_teaminformation[Index].offset[2] = 0x4A71;
	m_teaminformation[Index].offset[3] = 0x4A72;
	m_teaminformation[Index].offset[4] = 0x4A73;
	m_teaminformation[Index].offset[5] = 0x4A74;
	m_teaminformation[Index].offset[6] = 0x4A75;
	m_teaminformation[Index].offset[7] = 0x4A76;
	m_teaminformation[Index].offset[8] = 0x4A77;
	m_teaminformation[Index].offset[9] = 0x4A78;
	m_teaminformation[Index].offset[10] = 0x4A79;
	m_teaminformation[Index].offset[11] = 0x4A7A;
	m_teaminformation[Index].offset[12] = 0x4A7B;
	m_teaminformation[Index].offset[13] = 0x4A7C;
	m_teaminformation[Index].offset[14] = 0x4A7D;
	m_teaminformation[Index].offset[15] = 0x4A7E;
	m_teaminformation[Index].offset[16] = 0x4A7F;
	m_teaminformation[Index].offset[17] = 0x4A80;
	m_teaminformation[Index].offset[18] = 0x4A81;
	m_teaminformation[Index].offset[19] = 0x4A82;
	m_teaminformation[Index].offset[20] = 0x4A83;
	Index++;

	//叙利亚(无)球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//中国球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BC0C;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0x3BC0A;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//伊朗(无)球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//朝鲜(无)球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//沙特阿拉伯(无)球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//韩国球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BC36;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0x3BC38;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//瓦斯科达伽玛(无)球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//波兰球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0x3BC50;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0x3BC4E;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//英格兰球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0x3BC5E;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BC5C;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//苏联球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0x3BC6C;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BC6A;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//法国球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BC78;
	m_teaminformation[Index].offset[9] = 0x3BC7A;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//墨西哥球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0;
	m_teaminformation[Index].offset[9] = 0x3BC86;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//意大利球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0x3BC94;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BC92;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//荷兰球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0x3BCA2;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0;
	m_teaminformation[Index].offset[8] = 0x3BCA0;
	m_teaminformation[Index].offset[9] = 0;
	m_teaminformation[Index].offset[10] = 0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//阿根廷球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0x3BCB6;
	m_teaminformation[Index].offset[4] = 0;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0;
	m_teaminformation[Index].offset[7] = 0x3BCB4;
	m_teaminformation[Index].offset[8] = 0x3BCB0;
	m_teaminformation[Index].offset[9] = 0x3BCB2;
	m_teaminformation[Index].offset[10] = 0x3BCAE;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//西德球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0x3BCCE;
	m_teaminformation[Index].offset[1] = 0;
	m_teaminformation[Index].offset[2] = 0;
	m_teaminformation[Index].offset[3] = 0;
	m_teaminformation[Index].offset[4] = 0x3BCC8;
	m_teaminformation[Index].offset[5] = 0;
	m_teaminformation[Index].offset[6] = 0x3BCCC;
	m_teaminformation[Index].offset[7] = 0x3BCC6;
	m_teaminformation[Index].offset[8] = 0x3BCC4;
	m_teaminformation[Index].offset[9] = 0x3BCCA;
	m_teaminformation[Index].offset[10] = 0x3BCC2;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//巴西球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0x3BCEE;
	m_teaminformation[Index].offset[1] = 0x3BCEC;
	m_teaminformation[Index].offset[2] = 0x3BCE6;
	m_teaminformation[Index].offset[3] = 0x3BCE8;
	m_teaminformation[Index].offset[4] = 0x3BCEA;
	m_teaminformation[Index].offset[5] = 0x3BCE2;
	m_teaminformation[Index].offset[6] = 0x3BCDC;
	m_teaminformation[Index].offset[7] = 0x3BCE4;
	m_teaminformation[Index].offset[8] = 0x3BCDA;
	m_teaminformation[Index].offset[9] = 0x3BCDE;
	m_teaminformation[Index].offset[10] = 0x3BCE0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;

	//巴西(下)球员占位偏移地址
	m_teaminformation[Index].offset[0] = 0x3BCEE;
	m_teaminformation[Index].offset[1] = 0x3BCEC;
	m_teaminformation[Index].offset[2] = 0x3BCE6;
	m_teaminformation[Index].offset[3] = 0x3BCE8;
	m_teaminformation[Index].offset[4] = 0x3BCEA;
	m_teaminformation[Index].offset[5] = 0x3BCE2;
	m_teaminformation[Index].offset[6] = 0x3BCDC;
	m_teaminformation[Index].offset[7] = 0x3BCE4;
	m_teaminformation[Index].offset[8] = 0x3BCDA;
	m_teaminformation[Index].offset[9] = 0x3DBFC;
	m_teaminformation[Index].offset[10] = 0x3BCE0;
	m_teaminformation[Index].offset[11] = 0;
	m_teaminformation[Index].offset[12] = 0;
	m_teaminformation[Index].offset[13] = 0;
	m_teaminformation[Index].offset[14] = 0;
	m_teaminformation[Index].offset[15] = 0;
	m_teaminformation[Index].offset[16] = 0;
	m_teaminformation[Index].offset[17] = 0;
	m_teaminformation[Index].offset[18] = 0;
	m_teaminformation[Index].offset[19] = 0;
	m_teaminformation[Index].offset[20] = 0;
	Index++;





	//将球队名称写入TeamSelectBox
	for ( i = 0; i < TEAMNUMBER; i++ )
	{
		m_TeamSelectBox.InsertString( i, m_teaminformation[i].name );		
	}

	//初始选择"(无)"
	m_TeamSelectBox.SetCurSel( 0 );
	
	//根据球队信息使能球员下拉列表
	EnablePlayerComboBox( m_TeamSelectBox.GetCurSel() );

	j = 0;
	TempString = _T("");

	//初始化球员信息结构体
	LoadPlayerInfo();
	//球星的代码
	m_playerinformation[0].playercode = 0x01;
	m_playerinformation[1].playercode = 0x02;
	m_playerinformation[2].playercode = 0x03;
	m_playerinformation[3].playercode = 0x04;
	m_playerinformation[4].playercode = 0x05;
	m_playerinformation[5].playercode = 0x06;
	m_playerinformation[6].playercode = 0x07;
	m_playerinformation[7].playercode = 0x08;
	m_playerinformation[8].playercode = 0x09;
	m_playerinformation[9].playercode = 0x0A;
	m_playerinformation[10].playercode = 0x0B;
	m_playerinformation[11].playercode = 0x0C;
	m_playerinformation[12].playercode = 0x0D;
	m_playerinformation[13].playercode = 0x0E;
	m_playerinformation[14].playercode = 0x0F;
	m_playerinformation[15].playercode = 0x10;
	m_playerinformation[16].playercode = 0x11;
	m_playerinformation[17].playercode = 0x12;
	m_playerinformation[18].playercode = 0x13;
	m_playerinformation[19].playercode = 0x14;
	m_playerinformation[20].playercode = 0x15;
	m_playerinformation[21].playercode = 0x16;
	m_playerinformation[22].playercode = 0x17;
	m_playerinformation[23].playercode = 0x18;
	m_playerinformation[24].playercode = 0x19;
	m_playerinformation[25].playercode = 0x1A;
	m_playerinformation[26].playercode = 0x1B;
	m_playerinformation[27].playercode = 0x1C;
	m_playerinformation[28].playercode = 0x1D;
	m_playerinformation[29].playercode = 0x1E;
	m_playerinformation[30].playercode = 0x1F;
	m_playerinformation[31].playercode = 0x20;
	m_playerinformation[32].playercode = 0x21;
	m_playerinformation[33].playercode = 0x22;
	m_playerinformation[34].playercode = 0x23;
	m_playerinformation[35].playercode = 0x24;
	m_playerinformation[36].playercode = 0x25;
	m_playerinformation[37].playercode = 0x26;
	m_playerinformation[38].playercode = 0x27;
	m_playerinformation[39].playercode = 0x28;
	m_playerinformation[40].playercode = 0x29;
	m_playerinformation[41].playercode = 0x2A;
	m_playerinformation[42].playercode = 0x2B;
	m_playerinformation[43].playercode = 0x2C;
	m_playerinformation[44].playercode = 0x2D;
	m_playerinformation[45].playercode = 0x2E;
	m_playerinformation[46].playercode = 0x2F;
	m_playerinformation[47].playercode = 0x30;
	m_playerinformation[48].playercode = 0x31;
	m_playerinformation[49].playercode = 0x32;
	m_playerinformation[50].playercode = 0x33;
	m_playerinformation[51].playercode = 0x34;
	m_playerinformation[52].playercode = 0x35;
	m_playerinformation[53].playercode = 0x36;
	m_playerinformation[54].playercode = 0x37;
	m_playerinformation[55].playercode = 0x38;
	m_playerinformation[56].playercode = 0x39;
	m_playerinformation[57].playercode = 0x3A;
	m_playerinformation[58].playercode = 0x3B;
	m_playerinformation[59].playercode = 0x3C;
	m_playerinformation[60].playercode = 0x3D;
	m_playerinformation[61].playercode = 0x3E;
	m_playerinformation[62].playercode = 0x3F;
	m_playerinformation[63].playercode = 0x40;
	m_playerinformation[64].playercode = 0x41;
	m_playerinformation[65].playercode = 0x42;
	m_playerinformation[66].playercode = 0x43;
	m_playerinformation[67].playercode = 0x44;
	m_playerinformation[68].playercode = 0x45;
	m_playerinformation[69].playercode = 0x46;
	m_playerinformation[70].playercode = 0x47;
	m_playerinformation[71].playercode = 0x48;
	m_playerinformation[72].playercode = 0x49;
	m_playerinformation[73].playercode = 0x4A;
	m_playerinformation[74].playercode = 0x4B;
	m_playerinformation[75].playercode = 0x4C;
	m_playerinformation[76].playercode = 0x4D;
	m_playerinformation[77].playercode = 0x4E;
	m_playerinformation[78].playercode = 0x4F;
	m_playerinformation[79].playercode = 0x50;
	m_playerinformation[80].playercode = 0x51;
	m_playerinformation[81].playercode = 0x52;
	m_playerinformation[82].playercode = 0x53;
	m_playerinformation[83].playercode = 0x54;
	m_playerinformation[84].playercode = 0x55;
	m_playerinformation[85].playercode = 0x56;
	m_playerinformation[86].playercode = 0x57;
	m_playerinformation[87].playercode = 0x58;
	m_playerinformation[88].playercode = 0x59;
	m_playerinformation[89].playercode = 0x5A;
	m_playerinformation[90].playercode = 0x5B;
	m_playerinformation[91].playercode = 0x5C;
	m_playerinformation[92].playercode = 0x5D;
	m_playerinformation[93].playercode = 0x5E;
	m_playerinformation[94].playercode = 0x5F;
	m_playerinformation[95].playercode = 0x60;
	m_playerinformation[96].playercode = 0x61;
	m_playerinformation[97].playercode = 0x62;
	m_playerinformation[98].playercode = 0x63;
	m_playerinformation[99].playercode = 0x64;
	m_playerinformation[100].playercode = 0x65;
	m_playerinformation[101].playercode = 0x66;
	m_playerinformation[102].playercode = 0x67;
	m_playerinformation[103].playercode = 0x68;
	m_playerinformation[104].playercode = 0x69;
	m_playerinformation[105].playercode = 0x6A;
	m_playerinformation[106].playercode = 0x6B;
	m_playerinformation[107].playercode = 0x6C;
	m_playerinformation[108].playercode = 0x6D;
	m_playerinformation[109].playercode = 0x6E;
	m_playerinformation[110].playercode = 0x6F;
	m_playerinformation[111].playercode = 0x70;
	m_playerinformation[112].playercode = 0x71;
	m_playerinformation[113].playercode = 0x72;
	m_playerinformation[114].playercode = 0x73;
	m_playerinformation[115].playercode = 0x74;
	m_playerinformation[116].playercode = 0x75;

	//人物颜色地址的初始化
	Index = 0;
	int offsetAddr = 0x2B821;
	m_playerclraddr[Index].id = _T("01");
	for ( int j = 0; j < PLAYERNUMBER+9; j++ )
	{
		for ( int k = 0; k < 4; k++ )
		{
			m_playerclraddr[j].offset[k] = offsetAddr;
			offsetAddr++;
		}
		offsetAddr++;
	}

	offsetAddr = 0x2B6D7;
	for ( int j = PLAYERNUMBER+9; j < PLAYERNUMBER+41;j++)
	{
		for ( int k = 0; k < 4; k++ )
		{
			m_playerclraddr[j].offset[k] = offsetAddr;
			offsetAddr++;
		}
		offsetAddr++;
	}
	


	
	//颜色信息的初始化
	Index = 0;
	m_clrinfomation[Index].id = _T("00");
	m_clrinfomation[Index].clrcode = 0x00;
	Index++;


	m_clrinfomation[Index].id = _T("01");
	m_clrinfomation[Index].clrcode = 0x01;
	Index++;


	m_clrinfomation[Index].id = _T("02");
	m_clrinfomation[Index].clrcode = 0x02;
	Index++;

	m_clrinfomation[Index].id = _T("03");
	m_clrinfomation[Index].clrcode = 0x03;
	Index++;


	m_clrinfomation[Index].id = _T("04");
	m_clrinfomation[Index].clrcode = 0x04;
	Index++;


	m_clrinfomation[Index].id = _T("05");
	m_clrinfomation[Index].clrcode = 0x05;
	Index++;


	m_clrinfomation[Index].id = _T("06");
	m_clrinfomation[Index].clrcode = 0x06;
	Index++;


	m_clrinfomation[Index].id = _T("07");
	m_clrinfomation[Index].clrcode = 0x07;
	Index++;


	m_clrinfomation[Index].id = _T("08");
	m_clrinfomation[Index].clrcode = 0x08;
	Index++;


	m_clrinfomation[Index].id = _T("09");
	m_clrinfomation[Index].clrcode = 0x09;
	Index++;


	m_clrinfomation[Index].id = _T("0A");
	m_clrinfomation[Index].clrcode = 0x0A;
	Index++;


	m_clrinfomation[Index].id = _T("0B");
	m_clrinfomation[Index].clrcode = 0x0B;
	Index++;


	m_clrinfomation[Index].id = _T("0C");
	m_clrinfomation[Index].clrcode = 0x0C;
	Index++;


	m_clrinfomation[Index].id = _T("0D");
	m_clrinfomation[Index].clrcode = 0x0D;
	Index++;


	m_clrinfomation[Index].id = _T("0E");
	m_clrinfomation[Index].clrcode = 0x0E;
	Index++;


	m_clrinfomation[Index].id = _T("0F");
	m_clrinfomation[Index].clrcode = 0x0F;
	Index++;


	m_clrinfomation[Index].id = _T("10");
	m_clrinfomation[Index].clrcode = 0x10;
	Index++;


	m_clrinfomation[Index].id = _T("11");
	m_clrinfomation[Index].clrcode = 0x11;
	Index++;


	m_clrinfomation[Index].id = _T("12");
	m_clrinfomation[Index].clrcode = 0x12;
	Index++;

	m_clrinfomation[Index].id = _T("13");
	m_clrinfomation[Index].clrcode = 0x13;
	Index++;


	m_clrinfomation[Index].id = _T("14");
	m_clrinfomation[Index].clrcode = 0x14;
	Index++;

	m_clrinfomation[Index].id = _T("15");
	m_clrinfomation[Index].clrcode = 0x15;
	Index++;


	m_clrinfomation[Index].id = _T("16");
	m_clrinfomation[Index].clrcode = 0x16;
	Index++;

	m_clrinfomation[Index].id = _T("17");
	m_clrinfomation[Index].clrcode = 0x17;
	Index++;


	m_clrinfomation[Index].id = _T("18");
	m_clrinfomation[Index].clrcode = 0x18;
	Index++;

	m_clrinfomation[Index].id = _T("19");
	m_clrinfomation[Index].clrcode = 0x19;
	Index++;


	m_clrinfomation[Index].id = _T("1A");
	m_clrinfomation[Index].clrcode = 0x1A;
	Index++;


	m_clrinfomation[Index].id = _T("1B");
	m_clrinfomation[Index].clrcode = 0x1B;
	Index++;


	m_clrinfomation[Index].id = _T("1C");
	m_clrinfomation[Index].clrcode = 0x1C;
	Index++;


	m_clrinfomation[Index].id = _T("1D");
	m_clrinfomation[Index].clrcode = 0x1D;
	Index++;


	m_clrinfomation[Index].id = _T("1E");
	m_clrinfomation[Index].clrcode = 0x1E;
	Index++;

	m_clrinfomation[Index].id = _T("1F");
	m_clrinfomation[Index].clrcode = 0x1F;
	Index++;


	m_clrinfomation[Index].id = _T("20");
	m_clrinfomation[Index].clrcode = 0x20;
	Index++;

	m_clrinfomation[Index].id = _T("21");
	m_clrinfomation[Index].clrcode = 0x21;
	Index++;


	m_clrinfomation[Index].id = _T("22");
	m_clrinfomation[Index].clrcode = 0x22;
	Index++;

	m_clrinfomation[Index].id = _T("23");
	m_clrinfomation[Index].clrcode = 0x23;
	Index++;


	m_clrinfomation[Index].id = _T("24");
	m_clrinfomation[Index].clrcode = 0x24;
	Index++;


	m_clrinfomation[Index].id = _T("25");
	m_clrinfomation[Index].clrcode = 0x25;
	Index++;


	m_clrinfomation[Index].id = _T("26");
	m_clrinfomation[Index].clrcode = 0x26;
	Index++;


	m_clrinfomation[Index].id = _T("27");
	m_clrinfomation[Index].clrcode = 0x27;
	Index++;


	m_clrinfomation[Index].id = _T("28");
	m_clrinfomation[Index].clrcode = 0x28;
	Index++;


	m_clrinfomation[Index].id = _T("29");
	m_clrinfomation[Index].clrcode = 0x29;
	Index++;


	m_clrinfomation[Index].id = _T("2A");
	m_clrinfomation[Index].clrcode = 0x2A;
	Index++;


	m_clrinfomation[Index].id = _T("2B");
	m_clrinfomation[Index].clrcode = 0x2B;
	Index++;


	m_clrinfomation[Index].id = _T("2C");
	m_clrinfomation[Index].clrcode = 0x2C;
	Index++;


	m_clrinfomation[Index].id = _T("2D");
	m_clrinfomation[Index].clrcode = 0x2D;
	Index++;


	m_clrinfomation[Index].id = _T("2E");
	m_clrinfomation[Index].clrcode = 0x2E;
	Index++;


	m_clrinfomation[Index].id = _T("2F");
	m_clrinfomation[Index].clrcode = 0x2F;
	Index++;


	m_clrinfomation[Index].id = _T("30");
	m_clrinfomation[Index].clrcode = 0x30;
	Index++;


	m_clrinfomation[Index].id = _T("31");
	m_clrinfomation[Index].clrcode = 0x31;
	Index++;


	m_clrinfomation[Index].id = _T("32");
	m_clrinfomation[Index].clrcode = 0x32;
	Index++;


	m_clrinfomation[Index].id = _T("33");
	m_clrinfomation[Index].clrcode = 0x33;
	Index++;


	m_clrinfomation[Index].id = _T("34");
	m_clrinfomation[Index].clrcode = 0x34;
	Index++;


	m_clrinfomation[Index].id = _T("35");
	m_clrinfomation[Index].clrcode = 0x35;
	Index++;


	m_clrinfomation[Index].id = _T("36");
	m_clrinfomation[Index].clrcode = 0x36;
	Index++;


	m_clrinfomation[Index].id = _T("37");
	m_clrinfomation[Index].clrcode = 0x37;
	Index++;


	m_clrinfomation[Index].id = _T("38");
	m_clrinfomation[Index].clrcode = 0x38;
	Index++;


	m_clrinfomation[Index].id = _T("39");
	m_clrinfomation[Index].clrcode = 0x39;
	Index++;


	m_clrinfomation[Index].id = _T("3A");
	m_clrinfomation[Index].clrcode = 0x3A;
	Index++;


	m_clrinfomation[Index].id = _T("3B");
	m_clrinfomation[Index].clrcode = 0x3B;
	Index++;


	m_clrinfomation[Index].id = _T("3C");
	m_clrinfomation[Index].clrcode = 0x3C;
	Index++;

	//初始化造型偏移地址结构体
	int code = 0x28901;
	for ( int j = 0; j < PLAYERNUMBER; j++ )
	{
		m_playerfigaddr[j].offset = code;
		code++;
	}
	
	
	//初始化造型信息结构体
	Index = 0;

	m_figinfomation[Index].id = _T("00");
	m_figinfomation[Index].figcode = 0x00;
	Index++;

	m_figinfomation[Index].id = _T("01");
	m_figinfomation[Index].figcode = 0x01;
	Index++;

	m_figinfomation[Index].id = _T("02");
	m_figinfomation[Index].figcode = 0x02;
	Index++;

	m_figinfomation[Index].id = _T("03");
	m_figinfomation[Index].figcode = 0x03;
	Index++;

	m_figinfomation[Index].id = _T("04");
	m_figinfomation[Index].figcode = 0x04;
	Index++;

	m_figinfomation[Index].id = _T("05");
	m_figinfomation[Index].figcode = 0x05;
	Index++;

	m_figinfomation[Index].id = _T("06");
	m_figinfomation[Index].figcode = 0x06;
	Index++;

	m_figinfomation[Index].id = _T("07");
	m_figinfomation[Index].figcode = 0x07;
	Index++;

	m_figinfomation[Index].id = _T("08");
	m_figinfomation[Index].figcode = 0x08;
	Index++;

	m_figinfomation[Index].id = _T("09");
	m_figinfomation[Index].figcode = 0x09;
	Index++;

	m_figinfomation[Index].id = _T("0A");
	m_figinfomation[Index].figcode = 0x0A;
	Index++;

	m_figinfomation[Index].id = _T("0B");
	m_figinfomation[Index].figcode = 0x0B;
	Index++;

	m_figinfomation[Index].id = _T("0C");
	m_figinfomation[Index].figcode = 0x0C;
	Index++;

	m_figinfomation[Index].id = _T("0D");
	m_figinfomation[Index].figcode = 0x0D;
	Index++;

	m_figinfomation[Index].id = _T("0E");
	m_figinfomation[Index].figcode = 0x0E;
	Index++;

	m_figinfomation[Index].id = _T("0F");
	m_figinfomation[Index].figcode = 0x0F;
	Index++;

	//初始化GK信息结构体
	Index = 0;
	m_gkinformation[Index].id = _T("02");
	m_gkinformation[Index].gkcode = 0x02;
	Index++;

	m_gkinformation[Index].id = _T("0F");
	m_gkinformation[Index].gkcode = 0x0F;
	Index++;

	m_gkinformation[Index].id = _T("21");
	m_gkinformation[Index].gkcode = 0x21;
	Index++;

	m_gkinformation[Index].id = _T("22");
	m_gkinformation[Index].gkcode = 0x22;
	Index++;

	m_gkinformation[Index].id = _T("26");
	m_gkinformation[Index].gkcode = 0x26;
	Index++;

	m_gkinformation[Index].id = _T("33");
	m_gkinformation[Index].gkcode = 0x33;
	Index++;

	m_gkinformation[Index].id = _T("40");
	m_gkinformation[Index].gkcode = 0x40;
	Index++;

	m_gkinformation[Index].id = _T("4C");
	m_gkinformation[Index].gkcode = 0x4C;
	Index++;

	m_gkinformation[Index].id = _T("52");
	m_gkinformation[Index].gkcode = 0x52;
	Index++;

	m_gkinformation[Index].id = _T("5B");
	m_gkinformation[Index].gkcode = 0x5B;
	Index++;

	m_gkinformation[Index].id = _T("69");
	m_gkinformation[Index].gkcode = 0x69;
	Index++;

	m_gkinformation[Index].id = _T("74");
	m_gkinformation[Index].gkcode = 0x74;
	Index++;


	//初始化GK必杀技信息结构体
	Index = 0;
	m_gksklinformation[Index].id = _T("80");
	m_gksklinformation[Index].sklcode = 0x80;
	Index++;

	m_gksklinformation[Index].id = _T("81");
	m_gksklinformation[Index].sklcode = 0x81;
	Index++;

	m_gksklinformation[Index].id = _T("82");
	m_gksklinformation[Index].sklcode = 0x82;
	Index++;

	m_gksklinformation[Index].id = _T("83");
	m_gksklinformation[Index].sklcode = 0x83;
	Index++;



/*将球员名称写入PlayerSelectBox*/
	DeletePlayerName();
	AddPlayerName();

/*将球员名称写入PlayerCLRBox*/
	AddPlayerClrName();
/*将球员名称写入PlayerFIGBox*/
	AddPlayerFigName();

	m_patch1_edit.SetWindowText( _T("解决原我方球员与我方球员对抗时的死机BUG") );
	m_patch2_edit.SetWindowText( _T("敌方人物数值稳定补丁(副作用:施奈德,迪亚斯暴走和雪崩无效)") );
	
	return TRUE;
}

void CTsubasaHackDlg::EnablePlayerComboBox(int TeamID)
{
	//球员选择初始全部DISABLE
	m_PlayerSelectBox1.EnableWindow( FALSE );
	m_PlayerSelectBox2.EnableWindow( FALSE );
	m_PlayerSelectBox3.EnableWindow( FALSE );
	m_PlayerSelectBox4.EnableWindow( FALSE );
	m_PlayerSelectBox5.EnableWindow( FALSE );
	m_PlayerSelectBox6.EnableWindow( FALSE );
	m_PlayerSelectBox7.EnableWindow( FALSE );
	m_PlayerSelectBox8.EnableWindow( FALSE );
	m_PlayerSelectBox9.EnableWindow( FALSE );
	m_PlayerSelectBox10.EnableWindow( FALSE );
	m_PlayerSelectBox11.EnableWindow( FALSE );
	m_PlayerSelectBox12.EnableWindow( FALSE );
	m_PlayerSelectBox13.EnableWindow( FALSE );
	m_PlayerSelectBox14.EnableWindow( FALSE );
	m_PlayerSelectBox15.EnableWindow( FALSE );
	m_PlayerSelectBox16.EnableWindow( FALSE );
	m_PlayerSelectBox17.EnableWindow( FALSE );
	m_PlayerSelectBox18.EnableWindow( FALSE );
	m_PlayerSelectBox19.EnableWindow( FALSE );
	m_PlayerSelectBox20.EnableWindow( FALSE );
	m_PlayerSelectBox21.EnableWindow( FALSE );

	//根据球队的明星号码确定球员下拉列表使能状态
	if ( _T("0") != m_teaminformation[TeamID].playersID[0] )
	{
		m_PlayerSelectBox1.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[1] )
	{
		m_PlayerSelectBox2.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[2] )
	{
		m_PlayerSelectBox3.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[3] )
	{
		m_PlayerSelectBox4.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[4] )
	{
		m_PlayerSelectBox5.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[5] )
	{
		m_PlayerSelectBox6.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[6] )
	{
		m_PlayerSelectBox7.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[7] )
	{
		m_PlayerSelectBox8.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[8] )
	{
		m_PlayerSelectBox9.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[9] )
	{
		m_PlayerSelectBox10.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[10] )
	{
		m_PlayerSelectBox11.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[11] )
	{
		m_PlayerSelectBox12.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[12] )
	{
		m_PlayerSelectBox13.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[13] )
	{
		m_PlayerSelectBox14.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[14] )
	{
		m_PlayerSelectBox15.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[15] )
	{
		m_PlayerSelectBox16.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[16] )
	{
		m_PlayerSelectBox17.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[17] )
	{
		m_PlayerSelectBox18.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[18] )
	{
		m_PlayerSelectBox19.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[19] )
	{
		m_PlayerSelectBox20.EnableWindow( TRUE );
	}

	if ( _T("0") != m_teaminformation[TeamID].playersID[20] )
	{
		m_PlayerSelectBox21.EnableWindow( TRUE );
	}
}

// 选择文件
void CTsubasaHackDlg::OnBnClickedFileselect()
{
	
	CString TempStr;
	m_filenamebox.GetWindowText( TempStr );
	wchar_t szFilters[]=
		_T("nes Files(*.nes)|*.nes||");

	CFileDialog dlgFile( TRUE,  _T("*.nes"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST|
		OFN_PATHMUSTEXIST,szFilters );

	INT_PTR nResult = dlgFile.DoModal();

	m_FilePathName = dlgFile.GetPathName();
	m_FilePathName.Trim();

	if ( m_FilePathName != _T("") )
	{
		m_filenamebox.SetWindowText( m_FilePathName );
	}
	else
	{
		m_filenamebox.SetWindowText( TempStr );
		m_FilePathName = TempStr;
		m_FilePathName.Trim();
	}

}

void CTsubasaHackDlg::OnBnClickedOndecide(  )
{
	
	CString TempStr;
	m_IsIndirectSuccess = FALSE;

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[0] != 0 )
	{
		if ( m_PlayerSelectBox1.GetCurSel() != -1 )
		{
			m_PlayerSelectBox1.GetLBText( m_PlayerSelectBox1.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[0], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}
		
		
	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[1] != 0 )
	{
		if ( m_PlayerSelectBox2.GetCurSel() != -1 )
		{
			m_PlayerSelectBox2.GetLBText( m_PlayerSelectBox2.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[1], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[2] != 0 )
	{
		if ( m_PlayerSelectBox3.GetCurSel() != -1 )
		{
			m_PlayerSelectBox3.GetLBText( m_PlayerSelectBox3.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[2], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[3] != 0 )
	{
		if ( m_PlayerSelectBox4.GetCurSel() != -1 )
		{
			m_PlayerSelectBox4.GetLBText( m_PlayerSelectBox4.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[3], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[4] != 0 )
	{
		if ( m_PlayerSelectBox5.GetCurSel() != -1 )
		{
			m_PlayerSelectBox5.GetLBText( m_PlayerSelectBox5.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[4], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[5] != 0 )
	{
		if ( m_PlayerSelectBox6.GetCurSel() != -1 )
		{
			m_PlayerSelectBox6.GetLBText( m_PlayerSelectBox6.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[5], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[6] != 0 )
	{
		if ( m_PlayerSelectBox7.GetCurSel() != -1 )
		{
			m_PlayerSelectBox7.GetLBText( m_PlayerSelectBox7.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[6], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[7] != 0 )
	{
		if ( m_PlayerSelectBox8.GetCurSel() != -1 )
		{
			m_PlayerSelectBox8.GetLBText( m_PlayerSelectBox8.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[7], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[8] != 0 )
	{
		if ( m_PlayerSelectBox9.GetCurSel() != -1 )
		{
			m_PlayerSelectBox9.GetLBText( m_PlayerSelectBox9.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[8], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[9] != 0 )
	{
		if ( m_PlayerSelectBox10.GetCurSel() != -1 )
		{
			m_PlayerSelectBox10.GetLBText( m_PlayerSelectBox10.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[9], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[10] != 0 )
	{
		if ( m_PlayerSelectBox11.GetCurSel() != -1 )
		{
			m_PlayerSelectBox11.GetLBText( m_PlayerSelectBox11.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[10], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[11] != 0 )
	{
		if ( m_PlayerSelectBox12.GetCurSel() != -1 )
		{
			m_PlayerSelectBox12.GetLBText( m_PlayerSelectBox12.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[11], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[12] != 0 )
	{
		if ( m_PlayerSelectBox13.GetCurSel() != -1 )
		{
			m_PlayerSelectBox13.GetLBText( m_PlayerSelectBox13.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[12], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[13] != 0 )
	{
		if ( m_PlayerSelectBox14.GetCurSel() != -1 )
		{
			m_PlayerSelectBox14.GetLBText( m_PlayerSelectBox14.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[13], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[14] != 0 )
	{
		if ( m_PlayerSelectBox15.GetCurSel() != -1 )
		{
			m_PlayerSelectBox15.GetLBText( m_PlayerSelectBox15.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[14], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[15] != 0 )
	{
		if ( m_PlayerSelectBox16.GetCurSel() != -1 )
		{
			m_PlayerSelectBox16.GetLBText( m_PlayerSelectBox16.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[15], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[16] != 0 )
	{
		if ( m_PlayerSelectBox17.GetCurSel() != -1 )
		{
			m_PlayerSelectBox17.GetLBText( m_PlayerSelectBox17.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[16], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[17] != 0 )
	{
		if ( m_PlayerSelectBox18.GetCurSel() != -1 )
		{
			m_PlayerSelectBox18.GetLBText( m_PlayerSelectBox18.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[17], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[18] != 0 )
	{
		if ( m_PlayerSelectBox19.GetCurSel() != -1 )
		{
			m_PlayerSelectBox19.GetLBText( m_PlayerSelectBox19.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[18], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[19] != 0 )
	{
		if ( m_PlayerSelectBox20.GetCurSel() != -1 )
		{
			m_PlayerSelectBox20.GetLBText( m_PlayerSelectBox20.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[19], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[20] != 0 )
	{
		if ( m_PlayerSelectBox21.GetCurSel() != -1 )
		{
			m_PlayerSelectBox21.GetLBText( m_PlayerSelectBox21.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < PLAYERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_playerinformation[i].id )
					{
						IndirectCode( m_teaminformation[m_TeamSelectBox.GetCurSel()].offset[20], &(m_playerinformation[i].playercode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}


	}

	if ( m_IsIndirectSuccess )
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errSuccess ), MB_ICONINFORMATION );
	}




}



void CTsubasaHackDlg::OnCbnSelendokTeamselect()
{
	DeletePlayerName();
	//根据球队信息使能球员下拉列表
	EnablePlayerComboBox( m_TeamSelectBox.GetCurSel() );
	AddPlayerName();
}

void CTsubasaHackDlg::AddPlayerName()
{
	int i;

	//将选项填入
	for ( i = 0; i < PLAYERNUMBER; i++ )
	{
		//将守门员名称填入守门员下拉列表
		if ( ( m_playerinformation[i].id == _T("02") ) || ( m_playerinformation[i].id == _T("26") ) 
			|| ( m_playerinformation[i].id == _T("33") ) || ( m_playerinformation[i].id == _T("0F") )
			|| ( m_playerinformation[i].id == _T("21") ) || ( m_playerinformation[i].id == _T("22")	)
			|| ( m_playerinformation[i].id == _T("5B") ) || ( m_playerinformation[i].id == _T("69") )
			|| ( m_playerinformation[i].id == _T("74") ) || ( m_playerinformation[i].id == _T("52") )
			|| ( m_playerinformation[i].id == _T("40") ) || ( m_playerinformation[i].id == _T("4C") )
			|| ( m_playerinformation[i].id == _T("39") )
			)
		{
			m_PlayerSelectBox1.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );	
			m_PlayerSelectBox20.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox21.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
		}
		//将其它球员名称填入球员下拉列表
		else
		{
			m_PlayerSelectBox2.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox3.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox4.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );	
			m_PlayerSelectBox5.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox6.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );	
			m_PlayerSelectBox7.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox8.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox9.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox10.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox11.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox14.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox15.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox16.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox17.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox18.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox19.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox12.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );
			m_PlayerSelectBox13.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );

		}
	}	

}

void CTsubasaHackDlg::DeletePlayerName()
{
	m_PlayerSelectBox1.ResetContent();
	m_PlayerSelectBox2.ResetContent();
	m_PlayerSelectBox3.ResetContent();
	m_PlayerSelectBox4.ResetContent();
	m_PlayerSelectBox5.ResetContent();
	m_PlayerSelectBox6.ResetContent();
	m_PlayerSelectBox7.ResetContent();
	m_PlayerSelectBox8.ResetContent();
	m_PlayerSelectBox9.ResetContent();
	m_PlayerSelectBox10.ResetContent();
	m_PlayerSelectBox11.ResetContent();
	m_PlayerSelectBox12.ResetContent();
	m_PlayerSelectBox13.ResetContent();
	m_PlayerSelectBox14.ResetContent();
	m_PlayerSelectBox15.ResetContent();
	m_PlayerSelectBox16.ResetContent();
	m_PlayerSelectBox17.ResetContent();
	m_PlayerSelectBox18.ResetContent();
	m_PlayerSelectBox19.ResetContent();
	m_PlayerSelectBox20.ResetContent();
	m_PlayerSelectBox21.ResetContent();

}

void CTsubasaHackDlg::LoadTeamInfo()
{
	wchar_t URLTempChar[255];
	CString TeamInfo;

	std::wifstream HomePageFile( CConfigInfo::GetInstance()->GetDataFilePath() + _T("TeamInfo.dat"),  std::ios_base::in );
	if ( !HomePageFile.is_open())
	{
		AfxMessageBox( _T("球队信息数据文件打开失败！") );
	}
	else
	{
		HomePageFile.imbue(std::locale("chs"));
		//struct TEAMINFO 
		//{	
		//	CString id;				//球队id
		//	CString name;			//球队名称
		//	CString playersID[21];	//如果不是明星队员，则id为0，否则为1
		//};
		for ( int i = 0; i < TEAMNUMBER; i++ )
		{
			//读取球队id
			HomePageFile >> URLTempChar;
			TeamInfo = URLTempChar;
			m_teaminformation[i].id = TeamInfo;

			//读取球队名称
			HomePageFile >> URLTempChar;
			TeamInfo = URLTempChar;
			m_teaminformation[i].name = TeamInfo;

			//读取球队球员id
			for ( int j = 0; j < 21; j++ )
			{
				HomePageFile >> URLTempChar;
				TeamInfo = URLTempChar;
				m_teaminformation[i].playersID[j] = TeamInfo;
			}
			

		}
		
		HomePageFile.close();
	}
}

void CTsubasaHackDlg::LoadPlayerInfo()
{
	wchar_t URLTempChar[255];
	CString PlayerInfo;

	std::wifstream HomePageFile( CConfigInfo::GetInstance()->GetDataFilePath() + _T("PlayerInfo.dat"),  std::ios_base::in );
	if ( !HomePageFile.is_open())
	{
		AfxMessageBox( _T("球员信息数据文件打开失败！") );
	}
	else
	{
		HomePageFile.imbue(std::locale("chs"));
		//struct PLAYERINFO 
		//{
		//	CString id;				//球员id
		//	CString name;			//球员名称
		//};
		for ( int i = 0; i < PLAYERNUMBER; i++ )
		{
			//读取球员id
			HomePageFile >> URLTempChar;
			PlayerInfo = URLTempChar;
			m_playerinformation[i].id = PlayerInfo;

			//读取球员名称
			HomePageFile >> URLTempChar;
			PlayerInfo = URLTempChar;
			m_playerinformation[i].name = PlayerInfo;

		}

		HomePageFile.close();
	}
}

void CTsubasaHackDlg::IndirectCode( long offset, char buffer[255], size_t count )
{
	FILE *stream;
	int  result;

	m_IsIndirectSuccess = FALSE;

	stream = _wfsopen( m_FilePathName, _T("r+b"), _SH_DENYNO );

	if( stream == NULL )
	{
		m_IsIndirectSuccess = FALSE;
	}
	else
	{
		result = fseek( stream, offset, SEEK_SET);
		if( result )
		{
			m_IsIndirectSuccess = FALSE;
		}
		else
		{
			fwrite( buffer, 1, count, stream );
			m_IsIndirectSuccess = TRUE;

		}
		fclose( stream );
	}
}

CString CTsubasaHackDlg::GetIDFromPlayerCombo( CString PlayerData )
{
	int Index;
	int i;
	CString resultstr;

	Index = PlayerData.Find( _T("&"), 0 );

	for ( i=0; i<Index; i++ )
	{
		resultstr += PlayerData[i];
	}

	return resultstr;

}

CString CTsubasaHackDlg::GetFilePathName()
{
	CString ResultStr;
	m_filenamebox.GetWindowText( ResultStr );
	return ResultStr;
}

void CTsubasaHackDlg::OnBnClickedResetButton()
{

	
		m_PlayerSelectBox1.SetCurSel( -1 );
		m_PlayerSelectBox2.SetCurSel( -1 );
		m_PlayerSelectBox3.SetCurSel( -1 );
		m_PlayerSelectBox4.SetCurSel( -1 );
		m_PlayerSelectBox5.SetCurSel( -1 );
		m_PlayerSelectBox6.SetCurSel( -1 );
		m_PlayerSelectBox7.SetCurSel( -1 );
		m_PlayerSelectBox8.SetCurSel( -1 );
		m_PlayerSelectBox9.SetCurSel( -1 );
		m_PlayerSelectBox10.SetCurSel( -1 );
		m_PlayerSelectBox11.SetCurSel( -1 );
		m_PlayerSelectBox12.SetCurSel( -1 );
		m_PlayerSelectBox13.SetCurSel( -1 );
		m_PlayerSelectBox14.SetCurSel( -1 );
		m_PlayerSelectBox15.SetCurSel( -1 );
		m_PlayerSelectBox16.SetCurSel( -1 );
		m_PlayerSelectBox17.SetCurSel( -1 );
		m_PlayerSelectBox18.SetCurSel( -1 );
		m_PlayerSelectBox19.SetCurSel( -1 );
		m_PlayerSelectBox20.SetCurSel( -1 );
		m_PlayerSelectBox21.SetCurSel( -1 );
	
}

void CTsubasaHackDlg::AddPlayerClrName()
{
	int i;

	//将球员填入颜色修改球员选择框中
	for ( i = 0; i < PLAYERNUMBER; i++ )
	{
		m_characterclr_combo.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );		
	}	

	m_characterclr_combo.AddString( _T("76&") + m_playerinformation[0].name + _T("(日本)") );

	i = 14;
	m_characterclr_combo.AddString( _T("77&") + m_playerinformation[i].name + _T("(日本)") );
    i++;
    
	m_characterclr_combo.AddString( _T("78&") + m_playerinformation[i].name + _T("(日本)") );
	i++;

	m_characterclr_combo.AddString( _T("79&") + m_playerinformation[i].name + _T("(日本)") );
	i++;

	m_characterclr_combo.AddString( _T("7A&") + m_playerinformation[i].name + _T("(日本)") );
	i++;

	m_characterclr_combo.AddString( _T("7B&") + m_playerinformation[i].name + _T("(日本)") );
	i++;

	m_characterclr_combo.AddString( _T("7C&") + m_playerinformation[i].name + _T("(日本)") );
	i++;

	m_characterclr_combo.AddString( _T("7D&") + m_playerinformation[i].name + _T("(日本)") );
	i++;

	m_characterclr_combo.AddString( _T("7E&") + m_playerinformation[i].name + _T("(日本)") );
	i++;

	m_characterclr_combo.AddString( _T("7F&第1关平民") );
	m_characterclr_combo.AddString( _T("80&第2关平民") );
	m_characterclr_combo.AddString( _T("81&第3关平民") );
	m_characterclr_combo.AddString( _T("82&第4关平民") );
	m_characterclr_combo.AddString( _T("83&第5关平民") );
	m_characterclr_combo.AddString( _T("84&第6关平民") );
	m_characterclr_combo.AddString( _T("85&第7关平民") );
	m_characterclr_combo.AddString( _T("86&第8关平民") );
	m_characterclr_combo.AddString( _T("87&第9关平民") );
	m_characterclr_combo.AddString( _T("88&第10关平民") );
	m_characterclr_combo.AddString( _T("89&第11关平民") );
	m_characterclr_combo.AddString( _T("8A&第12关平民") );
	m_characterclr_combo.AddString( _T("8B&第13关平民") );
	m_characterclr_combo.AddString( _T("8C&第14关平民") );
	m_characterclr_combo.AddString( _T("8D&第15关平民") );
	m_characterclr_combo.AddString( _T("8E&(无效)第16关平民") );
	m_characterclr_combo.AddString( _T("8F&第17关平民") );
	m_characterclr_combo.AddString( _T("90&第18关平民") );
	m_characterclr_combo.AddString( _T("91&第19关平民") );
	m_characterclr_combo.AddString( _T("92&第20关平民") );
	m_characterclr_combo.AddString( _T("93&第21关平民") );
	m_characterclr_combo.AddString( _T("94&第22关平民") );
	m_characterclr_combo.AddString( _T("95&第23关平民") );
	m_characterclr_combo.AddString( _T("96&第24关平民") );
	m_characterclr_combo.AddString( _T("97&第25关平民") );
	m_characterclr_combo.AddString( _T("98&第26关平民") );
	m_characterclr_combo.AddString( _T("99&第27关平民") );
	m_characterclr_combo.AddString( _T("9A&第28关平民") );
	m_characterclr_combo.AddString( _T("9B&第29关平民") );
	m_characterclr_combo.AddString( _T("9C&第30关平民") );
	m_characterclr_combo.AddString( _T("9D&第31关平民") );
	m_characterclr_combo.AddString( _T("9E&第32关平民") );

}

void CTsubasaHackDlg::AddPlayerFigName()
{
	int i;

	//将球员填入造型修改球员选择框中
	for ( i = 0; i < PLAYERNUMBER; i++ )
	{
		m_characterfiguer_combo.AddString( m_playerinformation[i].id + _T("&") + m_playerinformation[i].name );		
	}	
}

void CTsubasaHackDlg::OnBnClickedOndecidedclrButton()
{
	CString TempStr;
	m_IsIndirectSuccess = FALSE;


	if ( m_characterclr_combo.GetCurSel() != -1 )
	{
		if ( m_skinclr_combo.GetCurSel() != -1 )
		{
			m_skinclr_combo.GetLBText( m_skinclr_combo.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < COLORNUMBER; i++ )
				{
					if ( TempStr == m_clrinfomation[i].id )
					{
						
						IndirectCode( m_playerclraddr[m_characterclr_combo.GetCurSel()].offset[0], &(m_clrinfomation[i].clrcode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}
	}
		

	if ( m_characterclr_combo.GetCurSel() != -1 )
	{
		if ( m_hairclr_combo.GetCurSel() != -1 )
		{
			m_hairclr_combo.GetLBText( m_hairclr_combo.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < COLORNUMBER; i++ )
				{
					if ( TempStr == m_clrinfomation[i].id )
					{
						IndirectCode( m_playerclraddr[m_characterclr_combo.GetCurSel()].offset[1], &(m_clrinfomation[i].clrcode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}
	}

	if ( m_characterclr_combo.GetCurSel() != -1 )
	{
		if ( m_shirtclr_combo.GetCurSel() != -1 )
		{
			m_shirtclr_combo.GetLBText( m_shirtclr_combo.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < COLORNUMBER; i++ )
				{
					if ( TempStr == m_clrinfomation[i].id )
					{
						IndirectCode( m_playerclraddr[m_characterclr_combo.GetCurSel()].offset[2], &(m_clrinfomation[i].clrcode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}
	}

	if ( m_characterclr_combo.GetCurSel() != -1 )
	{
		if ( m_trousersclr_combo.GetCurSel() != -1 )
		{
			m_trousersclr_combo.GetLBText( m_trousersclr_combo.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < COLORNUMBER; i++ )
				{
					if ( TempStr == m_clrinfomation[i].id )
					{
						IndirectCode( m_playerclraddr[m_characterclr_combo.GetCurSel()].offset[3], &(m_clrinfomation[i].clrcode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}
	}
	
	if ( m_IsIndirectSuccess )
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errSuccess ), MB_ICONINFORMATION );
	}

}

void CTsubasaHackDlg::OnBnClickedOnclearclrbutton()
{
	m_characterclr_combo.SetCurSel( -1 );
	m_skinclr_combo.SetCurSel( -1 );
	m_hairclr_combo.SetCurSel( -1 );
	m_shirtclr_combo.SetCurSel( -1 );
	m_trousersclr_combo.SetCurSel( -1 );
}

void CTsubasaHackDlg::OnCbnSelendokCharacterclrCombo()
{

	m_skinclr_combo.SetCurSel( -1 );
	m_hairclr_combo.SetCurSel( -1 );
	m_shirtclr_combo.SetCurSel( -1 );
	m_trousersclr_combo.SetCurSel( -1 );
}

void CTsubasaHackDlg::OnBnClickedOndecidedfigureButton()
{
	CString TempStr;
	m_IsIndirectSuccess = FALSE;


	if ( m_characterfiguer_combo.GetCurSel() != -1 )
	{
		if ( m_figuresel_combo.GetCurSel() != -1 )
		{
			m_figuresel_combo.GetLBText( m_figuresel_combo.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < FIGUERNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_figinfomation[i].id )
					{
						
						IndirectCode( m_playerfigaddr[m_characterfiguer_combo.GetCurSel()].offset, &(m_figinfomation[i].figcode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}
	}

	if ( m_IsIndirectSuccess )
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errSuccess ), MB_ICONINFORMATION );
	}

}

void CTsubasaHackDlg::OnBnClickedFigureclrButton()
{
	m_characterfiguer_combo.SetCurSel( -1 );
	m_figuresel_combo.SetCurSel( -1 );
}

void CTsubasaHackDlg::OnCbnSelendokCharacterfiguerCombo()
{
	m_figuresel_combo.SetCurSel( -1 );
}

void CTsubasaHackDlg::OnBnClickedOndecidedgk1Button()
{
	
	char buffer1[3] = { 0x4C, 0x10, 0xFD };
	char buffer2[20] = { 0x8D, 0x3E, 0x04,
						 0x48, 0xA9, 0x21,
						 0xCD, 0x00, 0x03,
						 0xD0, 0x15, 0xA9,
						 0x82, 0x8D, 0x3E,
						 0x04, 0x68, 0x4C,
						 0xB1, 0xD2
						};
	char buffer3[4] = { 0x68, 0x4C, 0xB1, 0xD2 };
	
	long offset1 = 0x3D2BE;
	long offset2 = 0x3FD20;
	long offset3 = 0x3FD40;

	


	CString TempStr;
	m_IsIndirectSuccess = FALSE;
	if ( m_gksel1_combo.GetCurSel() != -1 )
	{
		if ( m_gkskl1_combo.GetCurSel() != -1 )
		{
			m_gksel1_combo.GetLBText( m_gksel1_combo.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < GKNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_gkinformation[i].id )
					{
						IndirectCode( offset1, buffer1, 3 );
						IndirectCode( offset2, buffer2, 20 );
						IndirectCode( offset3, buffer3, 4 );

						IndirectCode( 0x3FD25, &(m_gkinformation[i].gkcode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}

			m_gkskl1_combo.GetLBText( m_gkskl1_combo.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < GKSKLNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_gksklinformation[i].id )
					{
						IndirectCode( 0x3FD2C, &(m_gksklinformation[i].sklcode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}
	}

	if ( m_IsIndirectSuccess )
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errSuccess ), MB_ICONINFORMATION );
	}
}

void CTsubasaHackDlg::OnBnClickedGkclr1Button()
{
	m_gksel1_combo.SetCurSel( -1 );
	m_gkskl1_combo.SetCurSel( -1 );
}

void CTsubasaHackDlg::OnCbnSelendokGksel1Combo()
{
	m_gkskl1_combo.SetCurSel( -1 );
}

void CTsubasaHackDlg::OnBnClickedOndecidedgk2Button()
{
	
	char buffer2[16] = { 0xA9, 0x74, 0xCD,
						 0x00, 0x03, 0xD0,
						 0x09, 0xA9, 0x83,
						 0x8D, 0x3E, 0x04,
						 0x68, 0x4C, 0xB1,
						 0xD2
					   };
	char buffer3[4] = { 0x68, 0x4C, 0xB1, 0xD2 };

	long offset2 = 0x3FD40;
	long offset3 = 0x3FD50;




	CString TempStr;
	m_IsIndirectSuccess = FALSE;
	if ( m_gksel2_combo.GetCurSel() != -1 )
	{
		if ( m_gkskl2_combo.GetCurSel() != -1 )
		{
			m_gksel2_combo.GetLBText( m_gksel2_combo.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < GKNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_gkinformation[i].id )
					{
						IndirectCode( offset2, buffer2, 16 );
						IndirectCode( offset3, buffer3, 4 );

						IndirectCode( 0x3FD41, &(m_gkinformation[i].gkcode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}

			m_gkskl2_combo.GetLBText( m_gkskl2_combo.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < GKSKLNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_gksklinformation[i].id )
					{
						IndirectCode( 0x3FD48, &(m_gksklinformation[i].sklcode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}
	}

	if ( m_IsIndirectSuccess )
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errSuccess ), MB_ICONINFORMATION );
	}
}

void CTsubasaHackDlg::OnBnClickedGkclr2Button()
{

	m_gksel2_combo.SetCurSel( -1 );
	m_gkskl2_combo.SetCurSel( -1 );
}

void CTsubasaHackDlg::OnCbnSelendokGksel2Combo()
{
	
	m_gkskl2_combo.SetCurSel( -1 );
}

void CTsubasaHackDlg::OnBnClickedOndecidedgk3Button()
{


	char buffer2[16] = { 0xA9, 0x33, 0xCD,
						 0x00, 0x03, 0xD0,
						 0x09, 0xA9, 0x81,
						 0x8D, 0x3E, 0x04,
						 0x68, 0x4C, 0xB1,
						 0xD2
						};
	char buffer3[4] = { 0x68, 0x4C, 0xB1, 0xD2 };

	long offset2 = 0x3FD50;
	long offset3 = 0x3FD60;




	CString TempStr;
	m_IsIndirectSuccess = FALSE;
	if ( m_gksel3_combo.GetCurSel() != -1 )
	{
		if ( m_gkskl3_combo.GetCurSel() != -1 )
		{
			m_gksel3_combo.GetLBText( m_gksel3_combo.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < GKNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_gkinformation[i].id )
					{
						IndirectCode( offset2, buffer2, 16 );
						IndirectCode( offset3, buffer3, 4 );

						IndirectCode( 0x3FD51, &(m_gkinformation[i].gkcode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}

			m_gkskl3_combo.GetLBText( m_gkskl3_combo.GetCurSel(), TempStr );
			if ( TempStr != _T("") )
			{
				for ( int i = 0; i < GKSKLNUMBER; i++ )
				{
					if ( GetIDFromPlayerCombo( TempStr ) == m_gksklinformation[i].id )
					{
						IndirectCode( 0x3FD58, &(m_gksklinformation[i].sklcode), 1);
						if ( !m_IsIndirectSuccess )
						{
							AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
							return ;
						}

					}
				}
			}
		}
	}

	if ( m_IsIndirectSuccess )
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errSuccess ), MB_ICONINFORMATION );
	}
}

void CTsubasaHackDlg::OnBnClickedGkclr3Button()
{
	
	m_gksel3_combo.SetCurSel( -1 );
	m_gkskl3_combo.SetCurSel( -1 );
}

void CTsubasaHackDlg::OnCbnSelendokGksel3Combo()
{
	m_gkskl3_combo.SetCurSel( -1 );
}

void CTsubasaHackDlg::OnBnClickedInject1Button()
{

	char buffer1[1];
	buffer1[0] = 0x40;
	m_IsIndirectSuccess = FALSE;

	IndirectCode( 0x34E09, buffer1, 1 );
	IndirectCode( 0x34E01, buffer1, 1 );
	if ( !m_IsIndirectSuccess )
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
		return ;
	}

	if ( m_IsIndirectSuccess )
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errSuccess ), MB_ICONINFORMATION );
	}
}

void CTsubasaHackDlg::OnBnClickedInject2Button()
{
	
	char buffer1[4] = { 0x4C, 0x10, 0xFE, 0xEA };
	char buffer2[12] = { 0xB1, 0x34, 0x10,
						 0x05, 0x4C, 0x61,
						 0x80, 0xEA, 0xEA,
						 0x4C, 0x61, 0x80
						};
	
	long offset1 = 0x38068;
	long offset2 = 0x3FE20;


	m_IsIndirectSuccess = FALSE;


	IndirectCode( offset1, buffer1, 4 );
	IndirectCode( offset2, buffer2, 12 );
	if ( !m_IsIndirectSuccess )
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errOpenFileFailed ) );
		return ;
	}

	if ( m_IsIndirectSuccess )
	{
		AfxMessageBox( CConfigInfo::GetInstance()->GetErrorMsg( CConfigInfo::errSuccess ), MB_ICONINFORMATION );
	}
}



void CTsubasaHackDlg::OnEnChangeFilenamebox()
{
	//更新全局文件路径
	CString strFilePath;
	m_filenamebox.GetWindowText( strFilePath );
	CConfigInfo::GetInstance()->SetObjectFilePath( strFilePath );

}
