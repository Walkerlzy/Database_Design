// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Database.h"

#include "MainFrm.h"
//��Ӵ���
#include "LoginDlg.h"
#include "UserSettingDlg.h"
#include "NationInformationDlg.h"
#include "PositionInformationDlg.h"
#include "EducationDegreeDlg.h"
#include "PoliticalStatusDlg.h"  
#include "DepartmentSectionDlg.h"
#include "WageLevelDlg.h"
#include "TechnicalPostDlg.h"
#include "AdministrativePostDlg.h"
#include "DepartmentDlg.h"
#include "SectionDlg.h"
#include "AuxiliaryDlg.h"
#include "AppendantDlg.h"
#include "FulltimeDlg.h"
#include "BrowseDlg.h"
#include "SearchDlg.h"
#include "StatisticsDlg.h"
#include "NotesDlg.h"
#include "ContactsDlg.h"
#include "MeetingRecordDlg.h"
//��Ӵ������
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_COMMAND(ID_SYS_RELOAD, OnSysReload)
	ON_COMMAND(ID_SYS_USERSETTING, OnSysUsersetting)
	ON_COMMAND(ID_SYS_EXIT, OnSysExit)
	ON_UPDATE_COMMAND_UI(ID_SYS_USERSETTING, OnUpdateSysUsersetting)
	ON_COMMAND(ID_SYS_DBBACKUP, OnSysDbbackup)
	ON_UPDATE_COMMAND_UI(ID_SYS_DBBACKUP, OnUpdateSysDbbackup)
	ON_COMMAND(ID_SYS_DBRECOVER, OnSysDbrecover)
	ON_UPDATE_COMMAND_UI(ID_SYS_DBRECOVER, OnUpdateSysDbrecover)
	ON_COMMAND(ID_INF_NATION, OnInfNation)
	ON_UPDATE_COMMAND_UI(ID_INF_NATION, OnUpdateInfNation)
	ON_COMMAND(ID_INF_POSITION, OnInfPosition)
	ON_UPDATE_COMMAND_UI(ID_INF_POSITION, OnUpdateInfPosition)
	ON_COMMAND(ID_INF_EDUCATION, OnInfEducation)
	ON_UPDATE_COMMAND_UI(ID_INF_EDUCATION, OnUpdateInfEducation)
	ON_COMMAND(ID_INF_POLITICAL, OnInfPolitical)
	ON_UPDATE_COMMAND_UI(ID_INF_POLITICAL, OnUpdateInfPolitical)
	ON_COMMAND(ID_INF_DEPT, OnInfDept)
	ON_UPDATE_COMMAND_UI(ID_INF_DEPT, OnUpdateInfDept)
	ON_COMMAND(ID_INF_WAGE, OnInfWage)
	ON_UPDATE_COMMAND_UI(ID_INF_WAGE, OnUpdateInfWage)
	ON_COMMAND(ID_INF_TECHNICAL, OnInfTechnical)
	ON_UPDATE_COMMAND_UI(ID_INF_TECHNICAL, OnUpdateInfTechnical)
	ON_COMMAND(ID_INF_ADMIN, OnInfAdmin)
	ON_UPDATE_COMMAND_UI(ID_INF_ADMIN, OnUpdateInfAdmin)
	ON_COMMAND(ID_ORG_DEPT, OnOrgDept)
	ON_UPDATE_COMMAND_UI(ID_ORG_DEPT, OnUpdateOrgDept)
	ON_COMMAND(ID_ORG_SECTION, OnOrgSection)
	ON_UPDATE_COMMAND_UI(ID_ORG_SECTION, OnUpdateOrgSection)
	ON_COMMAND(ID_ORG_AUXILIARY, OnOrgAuxiliary)
	ON_UPDATE_COMMAND_UI(ID_ORG_AUXILIARY, OnUpdateOrgAuxiliary)
	ON_COMMAND(ID_ORG_APPENDANT, OnOrgAppendant)
	ON_UPDATE_COMMAND_UI(ID_ORG_APPENDANT, OnUpdateOrgAppendant)
	ON_COMMAND(ID_ORG_FULLTIME, OnOrgFulltime)
	ON_UPDATE_COMMAND_UI(ID_ORG_FULLTIME, OnUpdateOrgFulltime)
	ON_COMMAND(ID_HUMAN_BROWSE, OnHumanBrowse)
	ON_UPDATE_COMMAND_UI(ID_HUMAN_BROWSE, OnUpdateHumanBrowse)
	ON_COMMAND(ID_HUMAN_QUERY, OnHumanQuery)
	ON_UPDATE_COMMAND_UI(ID_HUMAN_QUERY, OnUpdateHumanQuery)
	ON_COMMAND(ID_HUMAN_STATISTICS, OnHumanStatistics)
	ON_COMMAND(ID_TOOL_NOTES, OnToolNotes)
	ON_COMMAND(ID_TOOL_CONTACTS, OnToolContacts)
	ON_COMMAND(ID_TOOL_MEETING, OnToolMeeting)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_COMMAND(ID_HELP_DOCUMENT, OnHelpDocument)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
//��Ӵ���
    ID_SEPARATOR,           //���ӵ���ʾ�̶��ı�����Ϣ�д���
	ID_INDICATOR_CLOCK,     //���ӵ���ʾϵͳʱ���ָʾ������
	//ɾ������3��ԭ��ָʾ������
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
//��Ӵ������
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	//��Ӵ���
	//��װ��ʱ����������ʱ������Ϊ1000����  
	SetTimer(1,1000,NULL);
	//������Ϣ�д�������
	m_wndStatusBar.SetPaneText(1,"��У������Ϣ���ݿ�Ӧ��ϵͳ",true);
	//��Ӵ������
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//��Ӵ���
	CTime time;
	time=CTime::GetCurrentTime();    //�õ���ǰʱ��
	CString s=time.Format("%H:%M:%S");     //ת��ʱ���ʽ
	//��ʾʱ��
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_CLOCK),s,true);
	//��Ӵ������
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//��Ӵ���
	KillTimer(1);     //���ٶ�ʱ��
	//��Ӵ������
	CFrameWnd::OnClose();
}

void CMainFrame::OnSysReload() 
{
	// TODO: Add your command handler code here
	//��Ӵ���
	CLoginDlg Dlg;
	int nRes=0;
	do
	{
		nRes=Dlg.DoModal();
		//�ص�������
		if(nRes==IDOK)
			return;
		//�˳�ϵͳ
		if(nRes==IDCANCEL)
		{
			if(AfxMessageBox("�ף�������ȷ�����Ҫ�˳�ϵͳ��",MB_OKCANCEL)==IDCANCEL)
			{
				return;
			}
			CFrameWnd::OnClose();
			return;
		}
	}while(1);
	//��Ӵ������
}

void CMainFrame::OnSysUsersetting() 
{
	// TODO: Add your command handler code here
	//��Ӵ���
	CUserSettingDlg UserDlg;
	UserDlg.DoModal();
	//��Ӵ������	
}

void CMainFrame::OnSysExit() 
{
	// TODO: Add your command handler code here
	//��Ӵ���
	CFrameWnd::OnClose();
	//��Ӵ������	
}

void CMainFrame::OnUpdateSysUsersetting(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//��Ӵ���
	CDatabaseApp*ptheApp=(CDatabaseApp*) AfxGetApp();
	pCmdUI -> Enable(ptheApp ->m_bHasSuperAuthority);
	//��Ӵ������
}

void CMainFrame::OnSysDbbackup() 
{
	// TODO: Add your command handler code here
	//��Ӵ���
	if(AfxMessageBox("�ף����Ƿ�Ҫ�Ա�ϵͳ�����ݿ���б��ݣ�",MB_OKCANCEL)==IDCANCEL)
	{
		return;
	}
	//������ǰ�ĺ�̨���ݿ�PostDB���ݵ���ǰ������Ŀ·�����ļ���DatabaseBackup \�е�PostDB.bak
	if(CopyFile(".\\PostDB.accdb",".\\DatabaseBackup\\PostDB.bak",FALSE))
		AfxMessageBox("���ݿⱸ�ݳɹ�!");
	else
		AfxMessageBox("���ݿⱸ��ʧ�ܣ�");
	//��Ӵ������	
}

void CMainFrame::OnUpdateSysDbbackup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//��Ӵ���
	CDatabaseApp*ptheApp=(CDatabaseApp*) AfxGetApp();
	pCmdUI -> Enable(ptheApp -> m_bHasSuperAuthority);
	//��Ӵ������	
}

void CMainFrame::OnSysDbrecover() 
{
	// TODO: Add your command handler code here
	//��Ӵ���
	//���ļ���DatabaseBackup�ڵı������ݿ�PostDB.bak���Ǻ�̨���ݿ�PostDB.accdb
	if(AfxMessageBox("ϵͳ�ĺ�̨���ݿ⽫���˸������ǣ���ȷ��Ҫ��ԭ��",MB_OKCANCEL)==IDCANCEL)
	{
		return;
	}
	if(CopyFile(".\\DatabaseBackup\\PostDB.bak",".\\PostDB.accdb",FALSE))
		AfxMessageBox("���ݿ⻹ԭ�ɹ���");
	else
		AfxMessageBox("���ݿ⻹ԭʧ�ܣ�");
	//��Ӵ������	
}

void CMainFrame::OnUpdateSysDbrecover(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//��Ӵ���
	CDatabaseApp*ptheApp = (CDatabaseApp*) AfxGetApp();
	pCmdUI->Enable(ptheApp ->m_bHasSuperAuthority);
	//��Ӵ������	
}

void CMainFrame::OnInfNation() 
{
	// TODO: Add your command handler code here
	//��Ӵ���
	CNationInformationDlg dlg;
	dlg.DoModal();
	//��Ӵ������	
}

void CMainFrame::OnUpdateInfNation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//��Ӵ���
	CDatabaseApp*ptheApp=(CDatabaseApp*) AfxGetApp();
	pCmdUI -> Enable(ptheApp -> m_bHasSuperAuthority);
	//��Ӵ������	
}

void CMainFrame::OnInfPosition() 
{
	// TODO: Add your command handler code here
	// ��Ӵ���
    CPositionInformationDlg dlg;
    dlg.DoModal();
    // ��Ӵ������
}

void CMainFrame::OnUpdateInfPosition(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	// ��Ӵ���
    CDatabaseApp*  ptheApp = (CDatabaseApp *) AfxGetApp();
    pCmdUI->Enable(ptheApp->m_bHasSuperAuthority);
    // ��Ӵ������
}

void CMainFrame::OnInfEducation() 
{
	// TODO: Add your command handler code here
	// ��Ӵ���
    CEducationDegreeDlg dlg;
    dlg.DoModal();
    // ��Ӵ������
}

void CMainFrame::OnUpdateInfEducation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	// ��Ӵ���
    CDatabaseApp*  ptheApp = (CDatabaseApp *) AfxGetApp();
    pCmdUI->Enable(ptheApp->m_bHasSuperAuthority);
    // ��Ӵ������
}

void CMainFrame::OnInfPolitical() 
{
	// TODO: Add your command handler code here
	// ��Ӵ���
    CPoliticalStatusDlg dlg;
    dlg.DoModal();
    // ��Ӵ������
}

void CMainFrame::OnUpdateInfPolitical(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    // ��Ӵ���
    CDatabaseApp*  ptheApp = (CDatabaseApp *) AfxGetApp();
    pCmdUI->Enable(ptheApp->m_bHasSuperAuthority);
    // ��Ӵ������	
}

void CMainFrame::OnInfDept() 
{
	// TODO: Add your command handler code here
    // ��Ӵ���
    CDepartmentSectionDlg dlg;
    dlg.DoModal();
    // ��Ӵ������	
}

void CMainFrame::OnUpdateInfDept(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    // ��Ӵ���
    CDatabaseApp*  ptheApp = (CDatabaseApp *) AfxGetApp();
    pCmdUI->Enable(ptheApp->m_bHasSuperAuthority);
    // ��Ӵ������	
}

void CMainFrame::OnInfWage() 
{
	// TODO: Add your command handler code here
	// ��Ӵ���
    CWageLevelDlg dlg;
    dlg.DoModal();
    // ��Ӵ������
}

void CMainFrame::OnUpdateInfWage(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	// ��Ӵ���
    CDatabaseApp*  ptheApp = (CDatabaseApp *) AfxGetApp();
    pCmdUI->Enable(ptheApp->m_bHasSuperAuthority);
    // ��Ӵ������
}

void CMainFrame::OnInfTechnical() 
{
	// TODO: Add your command handler code here
	// ��Ӵ���
    CTechnicalPostDlg dlg;
    dlg.DoModal();
    // ��Ӵ������
}

void CMainFrame::OnUpdateInfTechnical(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	// ��Ӵ���
    CDatabaseApp*  ptheApp = (CDatabaseApp *) AfxGetApp();
    pCmdUI->Enable(ptheApp->m_bHasSuperAuthority);
    // ��Ӵ������
}

void CMainFrame::OnInfAdmin() 
{
	// TODO: Add your command handler code here
	// ��Ӵ���
    CAdministrativePostDlg dlg;
    dlg.DoModal();
    // ��Ӵ������
}

void CMainFrame::OnUpdateInfAdmin(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	// ��Ӵ���
    CDatabaseApp*  ptheApp = (CDatabaseApp *) AfxGetApp();
    pCmdUI->Enable(ptheApp->m_bHasSuperAuthority);
    // ��Ӵ������
}

void CMainFrame::OnOrgDept() 
{
	// TODO: Add your command handler code here
    // ��Ӵ���
    CDepartmentDlg dlg;
    dlg.DoModal();
    // ��Ӵ������	
}

void CMainFrame::OnUpdateOrgDept(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	// ��Ӵ���
    CDatabaseApp*  ptheApp = (CDatabaseApp *) AfxGetApp();
    pCmdUI->Enable(ptheApp->m_bHasSuperAuthority);
    // ��Ӵ������
}

void CMainFrame::OnOrgSection() 
{
	// TODO: Add your command handler code here
    // ��Ӵ���
    CSectionDlg dlg;
    dlg.DoModal();
    // ��Ӵ������	
}

void CMainFrame::OnUpdateOrgSection(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    // ��Ӵ���
    CDatabaseApp*  ptheApp = (CDatabaseApp *) AfxGetApp();
    pCmdUI->Enable(ptheApp->m_bHasSuperAuthority);
    // ��Ӵ������	
}

void CMainFrame::OnOrgAuxiliary() 
{
	// TODO: Add your command handler code here
    // ��Ӵ���
    CAuxiliaryDlg dlg;
    dlg.DoModal();
    // ��Ӵ������	
}

void CMainFrame::OnUpdateOrgAuxiliary(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    // ��Ӵ���
    CDatabaseApp*  ptheApp = (CDatabaseApp *) AfxGetApp();
    pCmdUI->Enable(ptheApp->m_bHasSuperAuthority);
    // ��Ӵ������	
}

void CMainFrame::OnOrgAppendant() 
{
	// TODO: Add your command handler code here
    // ��Ӵ���
    CAppendantDlg dlg;
    dlg.DoModal();
    // ��Ӵ������		
}

void CMainFrame::OnUpdateOrgAppendant(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    // ��Ӵ���
    CDatabaseApp*  ptheApp = (CDatabaseApp *) AfxGetApp();
    pCmdUI->Enable(ptheApp->m_bHasSuperAuthority);
    // ��Ӵ������	
}

void CMainFrame::OnOrgFulltime() 
{
	// TODO: Add your command handler code here
    // ��Ӵ���
    CFulltimeDlg dlg;
    dlg.DoModal();
    // ��Ӵ������	
}

void CMainFrame::OnUpdateOrgFulltime(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    // ��Ӵ���
    CDatabaseApp*  ptheApp = (CDatabaseApp *) AfxGetApp();
    pCmdUI->Enable(ptheApp->m_bHasSuperAuthority);
    // ��Ӵ������	
}

void CMainFrame::OnHumanBrowse() 
{
	// TODO: Add your command handler code here
	// ��Ӵ���
    CBrowseDlg dlg;
    dlg.DoModal();
    // ��Ӵ������	
}

void CMainFrame::OnUpdateHumanBrowse(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	// ��Ӵ���
    CDatabaseApp*  ptheApp = (CDatabaseApp *) AfxGetApp();
    pCmdUI->Enable(ptheApp->m_bHasSuperAuthority);
    // ��Ӵ������	
}

void CMainFrame::OnHumanQuery() 
{
	// TODO: Add your command handler code here
	// ��Ӵ���
    CSearchDlg dlg;
    dlg.DoModal();
    // ��Ӵ������
}

void CMainFrame::OnUpdateHumanQuery(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	// ��Ӵ���
    CDatabaseApp*  ptheApp = (CDatabaseApp *) AfxGetApp();
    pCmdUI->Enable(ptheApp->m_bHasSuperAuthority);
    // ��Ӵ������	
}

void CMainFrame::OnHumanStatistics() 
{
	// TODO: Add your command handler code here
	// ��Ӵ���
    CStatisticsDlg dlg;
    dlg.DoModal();
    // ��Ӵ������	
}

void CMainFrame::OnToolNotes() 
{
	// TODO: Add your command handler code here
	// ��Ӵ���
    CNotesDlg dlg;
    dlg.DoModal();
    // ��Ӵ������
}

void CMainFrame::OnToolContacts() 
{
	// TODO: Add your command handler code here
	// ��Ӵ���
    CContactsDlg dlg;
    dlg.DoModal();
    // ��Ӵ������	
}

void CMainFrame::OnToolMeeting() 
{
	// TODO: Add your command handler code here
	// ��Ӵ���
    CMeetingRecordDlg dlg;
    dlg.DoModal();
    // ��Ӵ������
}

void CMainFrame::OnHelpAbout() 
{
	// TODO: Add your command handler code here
	// ��Ӵ���
    extern CDatabaseApp theApp;
	theApp.OnAppAbout();
    // ��Ӵ������
}

void CMainFrame::OnHelpDocument() 
{
	// TODO: Add your command handler code here
	//��Ӵ���
	ShellExecute(NULL,"open",".\\help.docx",NULL,NULL,SW_SHOW);
	//��Ӵ������
}
