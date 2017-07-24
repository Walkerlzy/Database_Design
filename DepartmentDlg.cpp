// DepartmentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "DepartmentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDepartmentDlg dialog


CDepartmentDlg::CDepartmentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDepartmentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDepartmentDlg)
	m_strCode = _T("");
	m_strLocation = _T("");
	m_strSetting = _T("");
	m_strTeaching = _T("");
	m_strResearching = _T("");
	m_strStudent = _T("");
	m_strContent = _T("");
	m_strName = _T("");
	m_strLeader = _T("");
	//��Ӵ���
	m_iCondition = -1;
	//��Ӵ������
	//}}AFX_DATA_INIT
}


void CDepartmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDepartmentDlg)
	DDX_Control(pDX, IDC_LIST_DEPARTMENT, m_ctrDepartment);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_bntSave);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strCode);
	DDX_Text(pDX, IDC_EDIT_LOCATION, m_strLocation);
	DDX_Text(pDX, IDC_EDIT_SETTING, m_strSetting);
	DDX_Text(pDX, IDC_EDIT_TEACHING, m_strTeaching);
	DDX_Text(pDX, IDC_EDIT_RESEARCHING, m_strResearching);
	DDX_Text(pDX, IDC_EDIT_STUDENT, m_strStudent);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_strContent);
	DDX_CBString(pDX, IDC_COMBO_NAME, m_strName);
	DDX_CBString(pDX, IDC_COMBO_LEADER, m_strLeader);
	//��Ӵ���
	DDX_CBIndex(pDX,IDC_COMBO_CONDITION,m_iCondition);
	//��Ӵ������
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDepartmentDlg, CDialog)
	//{{AFX_MSG_MAP(CDepartmentDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DEPARTMENT, OnClickListDepartment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDepartmentDlg message handlers

void CDepartmentDlg::DataUpdate(CString strSQL)
{
    //��Ӵ���
	m_ctrDepartment.SetFocus();
	m_ctrDepartment.DeleteAllItems();
	m_ctrDepartment.SetRedraw(FALSE);
	UpdateData(TRUE);
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
    int i=0;
    while(!m_recordset.IsEOF())
    {
		m_ctrDepartment.InsertItem(i,m_recordset.m_code);
		m_ctrDepartment.SetItemText(i,1,m_recordset.m_name);
		m_ctrDepartment.SetItemText(i,2,m_recordset.m_leader);
		m_ctrDepartment.SetItemText(i,3,m_recordset.m_location);
		m_ctrDepartment.SetItemText(i,4,m_recordset.m_organization);
		m_ctrDepartment.SetItemText(i,5,m_recordset.m_teach);
		m_ctrDepartment.SetItemText(i,6,m_recordset.m_research);
		m_ctrDepartment.SetItemText(i,7,m_recordset.m_student);
		i++;
		m_recordset.MoveNext();
	}
	m_recordset.Close();
	m_ctrDepartment.SetRedraw(TRUE);
	//��Ӵ������
}

void CDepartmentDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	//������Ժϵ��ϸ��Ϣ���е���������
	m_strCode = "";
	m_strName = "";
	m_strLeader = "";
	m_strLocation = "";
	m_strSetting = "";
	m_strTeaching = "";
	m_strResearching = "";
	m_strStudent = "";
	//����水ť
	m_bntSave.EnableWindow();
	UpdateData(FALSE);
	//��Ӵ������	
}

void CDepartmentDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
    //��Ӵ���
	int i = m_ctrDepartment.GetSelectionMark();
    if(i<0)
    {
        MessageBox("��ѡ��һ����¼����ɾ����");
        return;
    }
    CString strSQL;
    strSQL.Format("select * from department where code ='%s'", m_ctrDepartment.GetItemText(i,0));
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
	//ɾ����Ժϵ
	m_recordset.Delete();
	m_recordset.Close();
	//����Ժϵ�б�
	strSQL = "select * from department";
	DataUpdate(strSQL);
	m_strCode = "";
	m_strName = "";
	m_strLeader = "";
	m_strLocation = "";
	m_strSetting = "";
	m_strTeaching = "";
	m_strResearching = "";
	m_strStudent = "";
	UpdateData(FALSE);
	//��Ӵ������
}

void CDepartmentDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	//����department����������Ϊ�յ�����
	if(m_strName == "")
	{
		MessageBox("������Ժϵ���ƣ�");
		return;
	}
	if(m_strCode == "")
	{
		MessageBox("������Ժϵ���룡");
		return;
	}
	if(m_strLeader == "")
	{
		MessageBox("������Ժϵ�쵼��");
		return;
	}
	CString tableDepartment;
	//���̨���ݱ�department������ȷ�����ݱ��浽ָ������
	tableDepartment = "select * from department";
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,tableDepartment))
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
	m_recordset.m_teach        = m_strTeaching;
	m_recordset.m_research     = m_strResearching;
	m_recordset.m_student      = m_strStudent;
	//���ݼ�����
	m_recordset.Update();
	m_recordset.Close();
	//��Ӵ������
}

void CDepartmentDlg::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	CString strSQL;
	if(0 == m_iCondition)
		strSQL.Format("select * from department where code = '%s'",m_strContent);
	else if(1 == m_iCondition)
		strSQL.Format("select * from department where leader = '%s'",m_strContent);
	else
		strSQL.Format("select * from department where name = '%s'",m_strContent);
	//��ʾȫ����Ϣ
	if(m_strContent == "")
		strSQL = "select * from department";
		DataUpdate(strSQL);
	//��Ӵ������
}

void CDepartmentDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	int i = m_ctrDepartment.GetSelectionMark();
	if(i < 0)
	{
		MessageBox("��ѡ��һ����¼�����޸ģ�");
		return;
	}
	//�ǿ�����������ݵ���ʾ
	if(m_strName == "")
	{
		MessageBox("������Ժϵ���ƣ�");
		return;
	}
	if(m_strCode == "")
	{
		MessageBox("������Ժϵ���룡");
		return;
	}
	if(m_strLeader == "")
	{
		MessageBox("������Ժϵ�쵼��");
		return;
	}
	CString strSQL;
	//��ȡҪ�޸ĵ�Ժϵ����
    strSQL.Format("select * from department where code ='%s'", m_ctrDepartment.GetItemText(i,0));
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
	m_recordset.m_teach        = m_strTeaching;
	m_recordset.m_research     = m_strResearching;
	m_recordset.m_student      = m_strStudent;
	m_recordset.Update();
	m_recordset.Close();
	DataUpdate(strSQL);     //���û����޸�д�غ�̨���ݿ�PostDB.accdb�����ݱ�department��
	//��Ӵ������
}

void CDepartmentDlg::OnClickListDepartment(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	CString strSQL;
	UpdateData(TRUE);
	int i = m_ctrDepartment.GetSelectionMark();
	m_strCode = m_ctrDepartment.GetItemText(i,0);
    strSQL.Format("select * from department where code ='%s'",m_strCode);
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
	m_strTeaching     = m_recordset.m_teach;
	m_strResearching  = m_recordset.m_research;
	m_strStudent      = m_recordset.m_student;
	m_recordset.Close();
	UpdateData(FALSE);
	//��Ӵ������
	*pResult = 0;
}

BOOL CDepartmentDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//��Ӵ���
	m_ctrDepartment.InsertColumn(0,"Ժϵ����");
    m_ctrDepartment.SetColumnWidth(0,40);
    m_ctrDepartment.InsertColumn(1,"Ժϵ����");
    m_ctrDepartment.SetColumnWidth(1,40);
	m_ctrDepartment.InsertColumn(2,"Ժϵ�쵼");
    m_ctrDepartment.SetColumnWidth(2,40);
	m_ctrDepartment.InsertColumn(3,"�칫�ص�");
    m_ctrDepartment.SetColumnWidth(3,80);
	m_ctrDepartment.InsertColumn(4,"��֯����");
    m_ctrDepartment.SetColumnWidth(0,80);
	m_ctrDepartment.InsertColumn(5,"��ѧ����");
    m_ctrDepartment.SetColumnWidth(1,80);
	m_ctrDepartment.InsertColumn(6,"���й���");
    m_ctrDepartment.SetColumnWidth(2,80);
	m_ctrDepartment.InsertColumn(7,"ѧ������");
    m_ctrDepartment.SetColumnWidth(3,80);
	m_ctrDepartment.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	CString strSQL;
	strSQL = "select * from department";
	DataUpdate(strSQL);
	//��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
