//////////////////////////////////////////////////////////////////////////
//// CTsubasaHackDlg
// 
// ����: ����ѡ���ȫ������
//
// ˵��: �����Ǵ�1.0�汾�������ģ�1.0�汾���г���ѡ������ݣ�
// 1.1�汾����Ȼ��ֻ������ѡ��е�һ�������Ա���CTsubasaHackDlg����
// ���������ڴ��룬���ǳ��ã����������û�з��룬�����������е��ۣ�
// ��λ����~


// TsubasaHackDlg.h : ͷ�ļ�
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



//�����Ϣ�Ľṹ��
struct TEAMINFO 
{	
	CString id;				//���id
	CString name;			//�������
	CString playersID[21];	//����������Ƕ�Ա����idΪ0������Ϊ1
	long offset[21];		//���21����Առλ��ƫ�Ƶ�ַ�������ռλ�����ڣ���Ϊ0
};

//��Ա��Ϣ�Ľṹ��
struct PLAYERINFO 
{
	CString id;				//��Աid
	CString name;			//��Ա����
	char playercode;		//��Ա���޸Ĵ���

};


//������ɫ��ַ�Ľṹ��
struct PLAYERCLRADDR 
{
	CString id;            //����id
	long offset[4];        //�����ɫ����ɫ������ɫ���̿�ɫ��ƫ�Ƶ�ַ
};

//��ɫ��Ϣ�Ľṹ��
struct CLRINFO 
{
	CString id;             //��ɫid
	char clrcode;           //��ɫ����
};

//�������͵�ַ�Ľṹ��
struct PLAYERFIGADDR 
{
	CString id;            //����id
	long offset;           //�������͵�ƫ�Ƶ�ַ
};


//������Ϣ�Ľṹ��
struct FIGINFO 
{
	CString id;            //����id
	char figcode;          //���ʹ���
};

//GK������Ϣ�ṹ��
struct GKINFO 
{
	CString id;
	char gkcode;
};

//GK��ɱ����Ϣ�ṹ��
struct GKSKLINFO 
{
	CString id;			//��ɱ��id
	char sklcode;		//��ɱ������
};


// CTsubasaHackDlg �Ի���
class CTsubasaHackDlg : public CPropertyPage
{
// ����
public:
	CTsubasaHackDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TSUBASAHACK_DIALOG };

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual BOOL OnInitDialog();	// ��ʼ���Ի���

	//��ʼ�������Ϣ
	BOOL InitiateTeamInfomation(); 
	//���ݵ�ǰѡ��Ķ����ж�Ӧ��ENABLE����Ա�����б�
	void EnablePlayerComboBox(int TeamID);
	void AddPlayerName();
	void DeletePlayerName();
	void AddPlayerClrName();
	void AddPlayerFigName();

	//��ȡ�����Ϣ
	void LoadTeamInfo();
	//��ȡ��Ա��Ϣ
	void LoadPlayerInfo();
	//ע�����
	void IndirectCode( long offset, char *buffer, size_t count );
	//��Combo�е���Ա������ȡ����ԱID;
	CString GetIDFromPlayerCombo( CString PlayerData );
	//��õ�ǰ�ļ�·��
	CString GetFilePathName();

	afx_msg void OnBnClickedFileselect();

	DECLARE_MESSAGE_MAP()

	// ���ɵ���Ϣӳ�亯��
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

	//�û�ָ�����ļ�·�����ļ���
	CString m_FilePathName;
	//����ļ�·����Edit
	CEdit m_filenamebox;
	//���ѡ�������б�����
	CTTComboBox m_TeamSelectBox;

	//��Ա�����б�����	
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
