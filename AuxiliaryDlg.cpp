// AuxiliaryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "AuxiliaryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAuxiliaryDlg dialog


CAuxiliaryDlg::CAuxiliaryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAuxiliaryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAuxiliaryDlg)
	m_strCode = _T("");
	m_strLocation = _T("");
	m_strSetting = _T("");
	m_strDuty = _T("");
	m_strContent = _T("");
	m_strName = _T("");
	m_strLeader = _T("");
	//��Ӵ���
	m_iCondition = -1;
	//��Ӵ������
	//}}AFX_DATA_INIT
}


void CAuxiliaryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAuxiliaryDlg)
	DDX_Control(pDX, IDC_LIST_AUXILIARY, m_ctrAuxiliary);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_bntSave);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strCode);
	DDX_Text(pDX, IDC_EDIT_LOCATION, m_strLocation);
	DDX_Text(pDX, IDC_EDIT_SETTING, m_strSetting);
	DDX_Text(pDX, IDC_EDIT_DUTY, m_strDuty);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_strContent);
	DDX_CBString(pDX, IDC_COMBO_NAME, m_strName);
	DDX_CBString(pDX, IDC_COMBO_LEADER, m_strLeader);
	//��Ӵ���
	DDX_CBIndex(pDX,IDC_COMBO_CONDITION,m_iCondition);
	//��Ӵ������
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAuxiliaryDlg, CDialog)
	//{{AFX_MSG_MAP(CAuxiliaryDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_NOTIFY(NM_CLICK, IDC_LIST_AUXILIARY, OnClickListAuxiliary)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAuxiliaryDlg message handlers

void CAuxiliaryDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	//�����򡰲�����ϸ��Ϣ���е���������
	m_strCode = "";
	m_strName = "";
	m_strLeader = "";
	m_strLocation = "";
	m_strSetting = "";
	m_strDuty = "";
	//����水ť
	m_bntSave.EnableWindow();
	UpdateData(FALSE);
	//��Ӵ������	
}

void CAuxiliaryDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
    //��Ӵ���
	int i = m_ctrAuxiliary.GetSelectionMark();
    if(i<0)
    {
        MessageBox("��ѡ��һ����¼����ɾ����");
        return;
    }
    CString strSQL;
    strSQL.Format("select * from auxiliary where code ='%s'", m_ctrAuxiliary.GetItemText(i,0));
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
	//ɾ���ò���
	m_recordset.Delete();
	m_recordset.Close();
	//���²����б�
	strSQL = "select * from auxiliary";
	DataUpdate(strSQL);
	m_strCode = "";
	m_strName = "";
	m_strLeader = "";
	m_strLocation = "";
	m_strSetting = "";
	m_strDuty = "";
	UpdateData(FALSE);
	//��Ӵ������	
}

void CAuxiliaryDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	//����auxiliary����������Ϊ�յ�����
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
	CString tableAuxiliary;
	//���̨���ݱ�auxiliary������ȷ�����ݱ��浽ָ������
	tableAuxiliary = "select * from auxiliary";
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,tableAuxiliary))
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
	m_recordset.m_duty         = m_strDuty;
	//���ݼ�����
	m_recordset.Update();
	m_recordset.Close();
	//��Ӵ������	
}

void CAuxiliaryDlg::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	CString strSQL;
	if(0 == m_iCondition)
		strSQL.Format("select * from auxiliary where code = '%s'",m_strContent);
	else if(1 == m_iCondition)
		strSQL.Format("select * from auxiliary where leader = '%s'",m_strContent);
	else
		strSQL.Format("select * from auxiliary where name = '%s'",m_strContent);
	//��ʾȫ����Ϣ
	if(m_strContent == "")
		strSQL = "select * from auxiliary";
		DataUpdate(strSQL);
	//��Ӵ������	
}

void CAuxiliaryDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	int i = m_ctrAuxiliary.GetSelectionMark();
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
    strSQL.Format("select * from auxiliary where code ='%s'", m_ctrAuxiliary.GetItemText(i,0));
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
	m_recordset.m_duty         = m_strDuty;
	m_recordset.Update();
	m_recordset.Close();
	DataUpdate(strSQL);     //���û����޸�д�غ�̨���ݿ�PostDB.accdb�����ݱ�auxiliary��
	//��Ӵ������	
}

void CAuxiliaryDlg::OnClickListAuxiliary(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	CString strSQL;
	UpdateData(TRUE);
	int i = m_ctrAuxiliary.GetSelectionMark();
	m_strCode = m_ctrAuxiliary.GetItemText(i,0);
    strSQL.Format("select * from auxiliary where code ='%s'",m_strCode);
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
	m_strDuty         = m_recordset.m_duty;
	m_recordset.Close();
	UpdateData(FALSE);
	//��Ӵ������	
	*pResult = 0;
}

BOOL CAuxiliaryDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// ��Ӵ���
    m_ctrAuxiliary.InsertColumn(0,"���ű���");
    m_ctrAuxiliary.SetColumnWidth(0,40);
    m_ctrAuxiliary.InsertColumn(1,"��������");
    m_ctrAuxiliary.SetColumnWidth(1,40);
    m_ctrAuxiliary.InsertColumn(2,"�����쵼");
    m_ctrAuxiliary.SetColumnWidth(2,40);
    m_ctrAuxiliary.InsertColumn(3,"�칫�ص�");
    m_ctrAuxiliary.SetColumnWidth(3,80);
    m_ctrAuxiliary.InsertColumn(4,"��֯����");
    m_ctrAuxiliary.SetColumnWidth(0,80);
    m_ctrAuxiliary.InsertColumn(5,"��λְ��");
    m_ctrAuxiliary.SetColumnWidth(1,80);
    m_ctrAuxiliary.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    CString strSQL;
    strSQL="select * from auxiliary";
    DataUpdate(strSQL);
    // ��Ӵ������	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAuxiliaryDlg::DataUpdate(CString strSQL)
{
    //��Ӵ���
	m_ctrAuxiliary.SetFocus();
	m_ctrAuxiliary.DeleteAllItems();
	m_ctrAuxiliary.SetRedraw(FALSE);
	UpdateData(TRUE);
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
    int i=0;
    while(!m_recordset.IsEOF())
    {
		m_ctrAuxiliary.InsertItem(i,m_recordset.m_code);
		m_ctrAuxiliary.SetItemText(i,1,m_recordset.m_name);
		m_ctrAuxiliary.SetItemText(i,2,m_recordset.m_leader);
		m_ctrAuxiliary.SetItemText(i,3,m_recordset.m_location);
		m_ctrAuxiliary.SetItemText(i,4,m_recordset.m_organization);
		m_ctrAuxiliary.SetItemText(i,5,m_recordset.m_duty);
		i++;
		m_recordset.MoveNext();
	}
	m_recordset.Close();
	m_ctrAuxiliary.SetRedraw(TRUE);
	//��Ӵ������
}
