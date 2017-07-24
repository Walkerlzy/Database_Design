// BrowseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "BrowseDlg.h"
//��Ӵ���
//����ϵͳ��2���˵�����������Ϣ��Ӧ��8�����ݼ���
#include "NationInformationSet.h"
#include "positionInformationSet.h"
#include "educationDegreeSet.h"
#include "politicalStatusSet.h"
#include "departmentSectionSet.h"
#include "wageLevelSet.h"
#include "technicalPostSet.h"
#include "administrativePostSet.h"
//��Ӵ������
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowseDlg dialog


CBrowseDlg::CBrowseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBrowseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBrowseDlg)
	m_iCondition = -1;
	m_strContent = _T("");
	m_strCode = _T("");
	m_strName = _T("");
	//��Ӵ���
	m_bNew = FALSE;
	//��Ӵ������
	//}}AFX_DATA_INIT
}


void CBrowseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBrowseDlg)
	DDX_Control(pDX, IDC_LIST_BROWSE, m_ctrContain);
	DDX_Control(pDX, IDC_TAB_BROWSE, m_ctrContainer);
	DDX_Control(pDX, IDC_COMBO_CONTENT, m_ctrContent);
	DDX_Control(pDX, IDC_COMBO_CONDITION, m_ctrCondition);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_bntCancel);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_bntSave);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_bntUpdate);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_bntDelete);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_bntAdd);
	DDX_CBIndex(pDX, IDC_COMBO_CONDITION, m_iCondition);
	DDX_CBString(pDX, IDC_COMBO_CONTENT, m_strContent);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strCode);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBrowseDlg, CDialog)
	//{{AFX_MSG_MAP(CBrowseDlg)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_NOTIFY(NM_CLICK, IDC_LIST_BROWSE, OnClickListBrowse)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_CBN_EDITUPDATE(IDC_COMBO_CONTENT, OnEditupdateComboContent)
	ON_CBN_SELCHANGE(IDC_COMBO_CONTENT, OnSelchangeComboContent)
	ON_CBN_SELCHANGE(IDC_COMBO_CONDITION, OnSelchangeComboCondition)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_BROWSE, OnSelchangeTabBrowse)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_BROWSE, OnSelchangingTabBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowseDlg message handlers

void CBrowseDlg::OnButtonCancel() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	m_bntAdd.EnableWindow(TRUE);
	m_bntDelete.EnableWindow(TRUE);
	m_bntSave.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	m_bntUpdate.EnableWindow(TRUE);
	m_bNew = FALSE;
	//��Ӵ������
}

void CBrowseDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	int i = m_ctrContain.GetSelectionMark();
    if(i<0)
    {
        MessageBox("�ף���ѡ��һ���̹�����ɾ����");
        return;
    }
    CString strSQL;
	//�̹�����ڳ�ʼ������������Ϊ��1λ
    strSQL.Format("select * from staff where code = %s",m_ctrContain.GetItemText(i,0));
    if(! m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
         MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
         return ;
    }
	//ɾ���ý̹�
	m_recordset.Delete();
	m_recordset.Close();
	//���½̹��б�
	strSQL = "select * from staff";
	DataUpdate(strSQL);
	//��նԻ���IDD_DIALOG_BROWSE��ǰ��¼��Ϣ
	m_strCode = "";
	m_strName = "";
	UpdateData(FALSE);
	//��ս̹�������ǰ��¼��Ϣ
	m_pBaseArchiveDlg.Purge();
	//�������10����ģ�鵱ǰ��¼��Ϣ
	m_pFamilyMemberDlg.DataUpdate(m_strCode);
	m_pAcademicEducationDlg.DataUpdate(m_strCode);
	m_pClassTeachingDlg.DataUpdate(m_strCode);
	m_pContinueEducationDlg.DataUpdate(m_strCode);
	m_pDisciplinePunishDlg.DataUpdate(m_strCode);
	m_pPaperDlg.DataUpdate(m_strCode);
	m_pProjectDlg.DataUpdate(m_strCode);
	m_pRewardRecordDlg.DataUpdate(m_strCode);
	m_pTechnicalAccessDlg.DataUpdate(m_strCode);
	m_pWorkExperienceDlg.DataUpdate(m_strCode);
	//��Ӵ������
}

void CBrowseDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	if(! m_pBaseArchiveDlg.Update())
		return;
	m_pBaseArchiveDlg.DataUpdate();
	//���¶Ի���IDD_DIALOG_BROWSE��ǰ��¼��Ϣ
	m_strName = m_pBaseArchiveDlg.m_strName;
	m_strCode = m_pBaseArchiveDlg.m_strCode;
	UpdateData(FALSE);
	//���¶Ի���IDD_DIALOG_BROWSE�б��ϵ�ǰ��¼��Ϣ
	CString strSQL;
	strSQL = "select * from staff";
	DataUpdate(strSQL);
	//��������10����ģ�����Ϣ
	m_pFamilyMemberDlg.DataUpdate(m_strCode);
	m_pAcademicEducationDlg.DataUpdate(m_strCode);
	m_pClassTeachingDlg.DataUpdate(m_strCode);
	m_pContinueEducationDlg.DataUpdate(m_strCode);
	m_pDisciplinePunishDlg.DataUpdate(m_strCode);
	m_pPaperDlg.DataUpdate(m_strCode);
	m_pProjectDlg.DataUpdate(m_strCode);
	m_pRewardRecordDlg.DataUpdate(m_strCode);
	m_pTechnicalAccessDlg.DataUpdate(m_strCode);
	m_pWorkExperienceDlg.DataUpdate(m_strCode);
	//��Ӵ������
}

void CBrowseDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	//ѡ��̹�������ģ��
	m_ctrContainer.SetCurSel(0);
	//������ս̹�������ģ���е�����
	m_pBaseArchiveDlg.Purge();
	//��μ���̹�������ģ��̹���ű༭��Ŀɱ༭״̬
	m_pBaseArchiveDlg.m_ctrCode.EnableWindow();
	//�ٴ����öԻ���IDD_DIALOG_BROWSE�ĸ�����ť״̬
	m_bntAdd.EnableWindow(FALSE);
	m_bntDelete.EnableWindow(FALSE);
	m_bntSave.EnableWindow(TRUE);
	m_bntCancel.EnableWindow(TRUE);
	m_bntUpdate.EnableWindow(FALSE);
	m_bNew = TRUE;   //����½̹��Ĳ�������Ϊ��
	//��Ӵ������
}

void CBrowseDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	if(! m_pBaseArchiveDlg.Save())
		return;
	m_pBaseArchiveDlg.DataUpdate();
	m_pBaseArchiveDlg.m_ctrCode.EnableWindow(FALSE);
	//���öԻ���IDD_DIALOG_BROWSE�и�����ť��״̬
	m_bntAdd.EnableWindow(TRUE);
	m_bntDelete.EnableWindow(TRUE);
	m_bntSave.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	m_bntUpdate.EnableWindow(TRUE);
	m_bNew = FALSE;    //����½̹��Ĳ�������Ϊ��
	//���¶Ի���IDD_DIALOG_BROWSE�ϵ�ǰ��¼��Ϣ
	m_strName = m_pBaseArchiveDlg.m_strName;
	m_strCode = m_pBaseArchiveDlg.m_strCode;
	UpdateData(FALSE);
	//���¶Ի���IDD_DIALOG_BROWSE�б���Ϣ
	CString strSQL;
	strSQL = "select * from staff";
	DataUpdate(strSQL);
	//ͬʱ�����������ģ�����Ϣ
	m_pFamilyMemberDlg.DataUpdate(m_strCode);
	m_pAcademicEducationDlg.DataUpdate(m_strCode);
	m_pClassTeachingDlg.DataUpdate(m_strCode);
	m_pContinueEducationDlg.DataUpdate(m_strCode);
	m_pDisciplinePunishDlg.DataUpdate(m_strCode);
	m_pPaperDlg.DataUpdate(m_strCode);
	m_pProjectDlg.DataUpdate(m_strCode);
	m_pRewardRecordDlg.DataUpdate(m_strCode);
	m_pTechnicalAccessDlg.DataUpdate(m_strCode);
	m_pWorkExperienceDlg.DataUpdate(m_strCode);
	//��Ӵ������
}

void CBrowseDlg::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData(TRUE);
	if(m_iCondition < 0)
	{
		MessageBox("�ף�����ѡ��һ������Ĳ�ѯ������");
		m_ctrCondition.SetFocus();
		return;
	}
	if(m_strContent == "")
	{
		MessageBox("�ף������������Ĳ�ѯ���ݣ�");
		m_ctrContent.SetFocus();
		return;
	}
	CString strSQL;
	//��Ժϵ���Ų�ѯ
	if(m_iCondition == 0)
	{
		strSQL.Format("select * from staff where department = %s",m_strContent);
		DataUpdate(strSQL);
	}
	//������ְ���ѯ
	else if(m_iCondition == 1)
	{
		strSQL.Format("select * from staff where job = %s",m_strContent);
		DataUpdate(strSQL);
	}
	//��ְ������ѯ
	else if(m_iCondition == 2)
	{
		strSQL.Format("select * from staff where technical = %s",m_strContent);
		DataUpdate(strSQL);
	}
	//���̹���λ��ѯ
	else if(m_iCondition == 3)
	{
		strSQL.Format("select * from staff where post = %s",m_strContent);
		DataUpdate(strSQL);
	}
	//�����ʵȼ���ѯ
	else if(m_iCondition == 4)
	{
		strSQL.Format("select * from staff where salary = %s",m_strContent);
		DataUpdate(strSQL);
	}
	//���̹��Ա��ѯ
	else if(m_iCondition == 5)
	{
		strSQL.Format("select * from staff where sex = %s",m_strContent);
		DataUpdate(strSQL);
	}
	//������״����ѯ
	else if(m_iCondition == 6)
	{
		strSQL.Format("select * from staff where marriage = %s",m_strContent);
		DataUpdate(strSQL);
	}
	//��������Ϣ��ѯ
	else if(m_iCondition == 7)
	{
		strSQL.Format("select * from staff where race = %s",m_strContent);
		DataUpdate(strSQL);
	}
	//��������ò��ѯ
	else if(m_iCondition == 8)
	{
		strSQL.Format("select * from staff where party = %s",m_strContent);
		DataUpdate(strSQL);
	}
	//���Ļ��̶Ȳ�ѯ
	else if(m_iCondition == 9)
	{
		strSQL.Format("select * from staff where degree = %s",m_strContent);
		DataUpdate(strSQL);
	}
	//���öԻ���IDD_DIALOG_BROWSE�ϸ�����ť��״̬
	m_bntAdd.EnableWindow(TRUE);
	m_bntDelete.EnableWindow(TRUE);
	m_bntSave.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	m_bntUpdate.EnableWindow(TRUE);
	m_bNew = FALSE;   //������ֵΪ��
	//�̹�������ģ���н̹���ű༭���Ϊ���ɱ༭״̬
	m_pBaseArchiveDlg.m_ctrCode.EnableWindow(FALSE);
	//��Ӵ������
}

void CBrowseDlg::OnClickListBrowse(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	int i = m_ctrContain.GetSelectionMark();
	m_strCode = m_ctrContain.GetItemText(i,0);  //���Ϊ��1λ
	m_strName = m_ctrContain.GetItemText(i,1);  //����Ϊ��2λ
	m_pBaseArchiveDlg.m_strCode = m_strCode;
	m_pBaseArchiveDlg.DataUpdate();
	UpdateData(FALSE);
    //������ģ��Ի����и�����ť��״̬
	m_bntAdd.EnableWindow(TRUE);
	m_bntDelete.EnableWindow(TRUE);
	m_bntSave.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	m_bntUpdate.EnableWindow(TRUE);
	m_bNew = FALSE;   //�߼���ֵΪ��
	//�̹�������ģ���еĹ��ű༭״̬�ر�
    m_pBaseArchiveDlg.m_ctrCode.EnableWindow(FALSE);
	//���¸���ģ�����Ϣ
	m_pFamilyMemberDlg.DataUpdate(m_strCode);
	m_pAcademicEducationDlg.DataUpdate(m_strCode);
	m_pClassTeachingDlg.DataUpdate(m_strCode);
	m_pContinueEducationDlg.DataUpdate(m_strCode);
	m_pDisciplinePunishDlg.DataUpdate(m_strCode);
	m_pPaperDlg.DataUpdate(m_strCode);
	m_pProjectDlg.DataUpdate(m_strCode);
	m_pRewardRecordDlg.DataUpdate(m_strCode);
	m_pTechnicalAccessDlg.DataUpdate(m_strCode);
	m_pWorkExperienceDlg.DataUpdate(m_strCode);
	//��Ӵ������
	*pResult = 0;
}

void CBrowseDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CBrowseDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

BOOL CBrowseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//��Ӵ���
	m_ctrContain.InsertColumn(0,"����");
	m_ctrContain.SetColumnWidth(0,80);
	m_ctrContain.InsertColumn(1,"����");
	m_ctrContain.SetColumnWidth(1,80);
	m_ctrContain.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	CString strSQL;
	strSQL = "select * from staff";
	DataUpdate(strSQL);
	//����ģ���Tab�ؼ���ǩҳ�����11����ģ��
	m_ctrContainer.AddModel("�̹�����",&m_pBaseArchiveDlg,IDD_HUMAN_HBASEARCHIVE);
	m_ctrContainer.AddModel("��ͥ��Ա",&m_pFamilyMemberDlg,IDD_DIALOG_HFAMILYMEMBER);
	m_ctrContainer.AddModel("��������",&m_pWorkExperienceDlg,IDD_DIALOG_HWORKEXPERIENCE);
	m_ctrContainer.AddModel("������¼",&m_pRewardRecordDlg,IDD_DIALOG_HREWARDRECORD);
	m_ctrContainer.AddModel("Υ�ʹ���",&m_pDisciplinePunishDlg,IDD_DIALOG_HDISCIPLINEPUNISH);
	m_ctrContainer.AddModel("���ĳɹ�",&m_pPaperDlg,IDD_DIALOG_HPAPER);
	m_ctrContainer.AddModel("��Ŀ�ɹ�",&m_pProjectDlg,IDD_DIALOG_HPROJECT);
	m_ctrContainer.AddModel("ְ������",&m_pTechnicalAccessDlg,IDD_DIALOG_HTECHNICALACCESS);
	m_ctrContainer.AddModel("ѧ������",&m_pAcademicEducationDlg,IDD_DIALOG_HACADEMICEDUCATION);
	m_ctrContainer.AddModel("��������",&m_pContinueEducationDlg,IDD_DIALOG_HCONTINUEEDUCATION);
	m_ctrContainer.AddModel("���ý�ѧ",&m_pClassTeachingDlg,IDD_DIALOG_HCLASSTEACHING);
	m_ctrContainer.Display();
	//��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBrowseDlg::OnEditupdateComboContent() 
{
	// TODO: Add your control notification handler code here
	
}

void CBrowseDlg::OnSelchangeComboContent() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	m_bntAdd.EnableWindow(TRUE);
	m_bntDelete.EnableWindow(TRUE);
	m_bntSave.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	m_bntUpdate.EnableWindow(TRUE);
	m_bNew = FALSE;  
    m_pBaseArchiveDlg.m_ctrCode.EnableWindow(FALSE);
	//��Ӵ������
}

void CBrowseDlg::OnSelchangeComboCondition() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
    UpdateData();
	CString strSQL;
	//�����ģ���ѯ�������Ͽ�IDC_COMBO_CONTENT������
	int total = m_ctrContent.GetCount();
	for(int i = 0;i < total;i++)
	{
		m_ctrContent.DeleteString(0);
	}
	//����Ͽ�IDC_COMBO_CONDITION��Ӧ������û���ѯ
	//��Ժϵ���Ų�ѯ
	if(m_iCondition == 0)
	{
		CDepartmentSectionSet DSS;
	    strSQL = "select * from departmentSection";
	    if(! DSS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
		{
	        MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		} 
	    while(! DSS.IsEOF())
		{
		    m_ctrContent.AddString(DSS.m_division);
		    DSS.MoveNext();
		}
	    DSS.Close();
	}
	//������ְ���ѯ
	else if(m_iCondition == 1)
	{
		CAdministrativePostSet APS;
	    strSQL = "select * from administrativePost";
	    if(! APS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
		{
	        MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		} 
	    while(! APS.IsEOF())
		{
		    m_ctrContent.AddString(APS.m_rank);
		    APS.MoveNext();
		}
	    APS.Close();
	}
	//��ְ������ѯ
	else if(m_iCondition == 2)
	{
		CTechnicalPostSet TPS;
	    strSQL = "select * from technicalPost";
	    if(! TPS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
		{
	        MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		} 
	    while(! TPS.IsEOF())
		{
		    m_ctrContent.AddString(TPS.m_title);
		    TPS.MoveNext();
		}
	    TPS.Close();
	}
	//���̹���λ��ѯ
	else if(m_iCondition == 3)
	{
		CPositionInformationSet PIS;
	    strSQL = "select * from positionInformation";
	    if(! PIS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
		{
	        MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		} 
	    while(! PIS.IsEOF())
		{
		    m_ctrContent.AddString(PIS.m_post);
		    PIS.MoveNext();
		}
	    PIS.Close();
	}
	//�����ʵȼ���ѯ
	else if(m_iCondition == 4)
	{
		CWageLevelSet WLS;
	    strSQL = "select * from wageLevel";
	    if(! WLS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
		{
	        MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		} 
	    while(! WLS.IsEOF())
		{
		    m_ctrContent.AddString(WLS.m_salary);
		    WLS.MoveNext();
		}
	    WLS.Close();
	}
	//���̹��Ա��ѯ
	else if(m_iCondition == 5)
	{
		m_ctrContent.AddString("��");
		m_ctrContent.AddString("Ů");
	}
	//������״����ѯ
	else if(m_iCondition == 6)
	{
		m_ctrContent.AddString("δ��");
		m_ctrContent.AddString("�ѻ�");
	}
	//��������Ϣ��ѯ
	else if(m_iCondition == 7)
	{
		CNationInformationSet NIS;
	    strSQL = "select * from nationInformation";
	    if(! NIS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
		{
	        MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		} 
	    while(! NIS.IsEOF())
		{
		    m_ctrContent.AddString(NIS.m_folk);
		    NIS.MoveNext();
		}
	    NIS.Close();
	}
	//��������ò��ѯ
	else if(m_iCondition == 8)
	{
		CPoliticalStatusSet PSS;
	    strSQL = "select * from politicalStatus";
	    if(! PSS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
		{
	        MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		} 
	    while(! PSS.IsEOF())
		{
		    m_ctrContent.AddString(PSS.m_party);
		    PSS.MoveNext();
		}
	    PSS.Close();
	}
	//���Ļ��̶Ȳ�ѯ
	else if(m_iCondition == 9)
	{
		CEducationDegreeSet EDS;
	    strSQL = "select * from educationDegree";
	    if(! EDS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
		{
	        MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		} 
	    while(! EDS.IsEOF())
		{
		    m_ctrContent.AddString(EDS.m_degree);
		    EDS.MoveNext();
		}
	    EDS.Close();
	}
	//������ģ���и�����ť��״̬
	m_bntAdd.EnableWindow(TRUE);
	m_bntDelete.EnableWindow(TRUE);
	m_bntSave.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	m_bntUpdate.EnableWindow(TRUE);
	m_bNew = FALSE;   //�����߼���ֵΪ��
    m_pBaseArchiveDlg.m_ctrCode.EnableWindow(FALSE);
	//��Ӵ������
}

void CBrowseDlg::OnSelchangeTabBrowse(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	if(m_bNew)
	{
		m_ctrContainer.SetCurSel(1);
		m_ctrContainer.SetCurSel(0);
		m_ctrContainer.UpdateWindow();
		*pResult = 0;
		return;
	}
	//��Ӵ������
	*pResult = 0;
}

void CBrowseDlg::OnSelchangingTabBrowse(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CBrowseDlg::DataUpdate(CString strSQL)
{
    //��Ӵ���
	m_ctrContain.DeleteAllItems();
	m_ctrContain.SetRedraw(FALSE);
	UpdateData(TRUE);
	if(! m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
         MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
         return ;
    }
	int i = 0;
	while(!m_recordset.IsEOF())
	{
		m_ctrContain.InsertItem(i,m_recordset.m_code);
		m_ctrContain.SetItemText(i++,1,m_recordset.m_name);
		m_recordset.MoveNext();
	}
	m_recordset.Close();
	m_ctrContain.SetRedraw(TRUE);
	//��Ӵ������
}
