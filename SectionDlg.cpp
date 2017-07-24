// SectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "SectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSectionDlg dialog


CSectionDlg::CSectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSectionDlg)
	m_strCode = _T("");
	m_strLocation = _T("");
	m_strSetting = _T("");
	m_strRule = _T("");
	m_strContent = _T("");
	m_strLeader = _T("");
	m_strName = _T("");
	//��Ӵ���
	m_iCondition = -1;
	//��Ӵ������
	//}}AFX_DATA_INIT
}


void CSectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSectionDlg)
	DDX_Control(pDX, IDC_LIST_SECTION, m_ctrSection);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_bntSave);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strCode);
	DDX_Text(pDX, IDC_EDIT_LOCATION, m_strLocation);
	DDX_Text(pDX, IDC_EDIT_SETTING, m_strSetting);
	DDX_Text(pDX, IDC_EDIT_RULE, m_strRule);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_strContent);
	DDX_CBString(pDX, IDC_COMBO_LEADER, m_strLeader);
	DDX_CBString(pDX, IDC_COMBO_NAME, m_strName);
	//��Ӵ���
	DDX_CBIndex(pDX,IDC_COMBO_CONDITION,m_iCondition);
	//��Ӵ������
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSectionDlg, CDialog)
	//{{AFX_MSG_MAP(CSectionDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SECTION, OnClickListSection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSectionDlg message handlers

void CSectionDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	//�����򡰲�����ϸ��Ϣ���е���������
	m_strCode = "";
	m_strName = "";
	m_strLeader = "";
	m_strLocation = "";
	m_strSetting = "";
    m_strRule = "";
	//����水ť
	m_bntSave.EnableWindow();
	UpdateData(FALSE);
	//��Ӵ������	
}

void CSectionDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
    //��Ӵ���
	int i = m_ctrSection.GetSelectionMark();
    if(i<0)
    {
        MessageBox("��ѡ��һ����¼����ɾ����");
        return;
    }
    CString strSQL;
    strSQL.Format("select * from section where code ='%s'", m_ctrSection.GetItemText(i,0));
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
	//ɾ���ò���
	m_recordset.Delete();
	m_recordset.Close();
	//���²����б�
	strSQL = "select * from section";
	DataUpdate(strSQL);
	m_strCode = "";
	m_strName = "";
	m_strLeader = "";
	m_strLocation = "";
	m_strSetting = "";
	m_strRule = "";
	UpdateData(FALSE);
	//��Ӵ������	
}

void CSectionDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	//����section����������Ϊ�յ�����
	if(m_strName == "")
	{
		MessageBox("�����벿�����ƣ�");
		return;
	}
	if(m_strCode == "")
	{
		MessageBox("�����벿�ű��룡");
		return;
	}
	if(m_strLeader == "")
	{
		MessageBox("�����벿���쵼��");
		return;
	}
	CString tableSection;
	//���̨���ݱ�section������ȷ�����ݱ��浽ָ������
	tableSection = "select * from section";
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,tableSection))
	{
		MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
		return;
	}
	//������ݼ��е�����
	m_recordset.AddNew();
	m_recordset.m_code         = m_strCode;
	m_recordset.m_name         = m_strName;
	m_recordset.m_leader       = m_strLeader;
	m_recordset.m_location     = m_strLocation;
	m_recordset.m_organization = m_strSetting;
	m_recordset.m_rule         = m_strRule;
	//���ݼ�����
	m_recordset.Update();
	m_recordset.Close();
	//��Ӵ������	
}

void CSectionDlg::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	CString strSQL;
	if(0 == m_iCondition)
		strSQL.Format("select * from section where code = '%s'",m_strContent);
	else if(1 == m_iCondition)
		strSQL.Format("select * from section where leader = '%s'",m_strContent);
	else
		strSQL.Format("select * from section where name = '%s'",m_strContent);
	//��ʾȫ����Ϣ
	if(m_strContent == "")
		strSQL = "select * from section";
		DataUpdate(strSQL);
	//��Ӵ������	
}

void CSectionDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	int i = m_ctrSection.GetSelectionMark();
	if(i < 0)
	{
		MessageBox("��ѡ��һ����¼�����޸ģ�");
		return;
	}
	//�ǿ�����������ݵ���ʾ
	if(m_strName == "")
	{
		MessageBox("�����벿�����ƣ�");
		return;
	}
	if(m_strCode == "")
	{
		MessageBox("�����벿�ű��룡");
		return;
	}
	if(m_strLeader == "")
	{
		MessageBox("�����벿���쵼��");
		return;
	}
	CString strSQL;
	//��ȡҪ�޸ĵĲ��ű���
    strSQL.Format("select * from section where code ='%s'", m_ctrSection.GetItemText(i,0));
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
	m_recordset.Edit();
	m_recordset.m_code         = m_strCode;
	m_recordset.m_name         = m_strName;
	m_recordset.m_leader       = m_strLeader;
	m_recordset.m_location     = m_strLocation;
	m_recordset.m_organization = m_strSetting;
	m_recordset.m_rule         = m_strRule;
	m_recordset.Update();
	m_recordset.Close();
	DataUpdate(strSQL);     //���û����޸�д�غ�̨���ݿ�PostDB.accdb�����ݱ�section��
	//��Ӵ������	
}

void CSectionDlg::OnClickListSection(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	CString strSQL;
	UpdateData(TRUE);
	int i = m_ctrSection.GetSelectionMark();
	m_strCode = m_ctrSection.GetItemText(i,0);
    strSQL.Format("select * from section where code ='%s'",m_strCode);
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
	m_strCode         = m_recordset.m_code;
	m_strName         = m_recordset.m_name;
	m_strLeader       = m_recordset.m_leader;
	m_strLocation     = m_recordset.m_location;
	m_strSetting      = m_recordset.m_organization;
	m_strRule         = m_recordset.m_rule;
	m_recordset.Close();
	UpdateData(FALSE);
	//��Ӵ������	
	*pResult = 0;
}

BOOL CSectionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// ��Ӵ���
    m_ctrSection.InsertColumn(0,"���ű���");
    m_ctrSection.SetColumnWidth(0,40);
    m_ctrSection.InsertColumn(1,"��������");
    m_ctrSection.SetColumnWidth(1,40);
    m_ctrSection.InsertColumn(2,"�����쵼");
    m_ctrSection.SetColumnWidth(2,40);
    m_ctrSection.InsertColumn(3,"�칫�ص�");
    m_ctrSection.SetColumnWidth(3,80);
    m_ctrSection.InsertColumn(4,"��֯����");
    m_ctrSection.SetColumnWidth(0,80);
    m_ctrSection.InsertColumn(5,"�����ƶ�");
    m_ctrSection.SetColumnWidth(1,80);
    m_ctrSection.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    CString strSQL;
    strSQL="select * from section";
    DataUpdate(strSQL);
    // ��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSectionDlg::DataUpdate(CString strSQL)
{
    //��Ӵ���
	m_ctrSection.SetFocus();
	m_ctrSection.DeleteAllItems();
	m_ctrSection.SetRedraw(FALSE);
	UpdateData(TRUE);
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
    int i=0;
    while(!m_recordset.IsEOF())
    {
		m_ctrSection.InsertItem(i,m_recordset.m_code);
		m_ctrSection.SetItemText(i,1,m_recordset.m_name);
		m_ctrSection.SetItemText(i,2,m_recordset.m_leader);
		m_ctrSection.SetItemText(i,3,m_recordset.m_location);
		m_ctrSection.SetItemText(i,4,m_recordset.m_organization);
		m_ctrSection.SetItemText(i,5,m_recordset.m_rule);
		i++;
		m_recordset.MoveNext();
	}
	m_recordset.Close();
	m_ctrSection.SetRedraw(TRUE);
	//��Ӵ������
}
