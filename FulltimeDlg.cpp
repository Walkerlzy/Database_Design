// FulltimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "FulltimeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFulltimeDlg dialog


CFulltimeDlg::CFulltimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFulltimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFulltimeDlg)
	m_strCode = _T("");
	m_strLocation = _T("");
	m_strSetting = _T("");
	m_strFruit = _T("");
	m_strContent = _T("");
	m_strName = _T("");
	m_strLeader = _T("");
	//��Ӵ���
	m_iCondition = -1;
	//��Ӵ������
	//}}AFX_DATA_INIT
}


void CFulltimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFulltimeDlg)
	DDX_Control(pDX, IDC_LIST_FULLTIME, m_ctrFulltime);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_bntSave);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strCode);
	DDX_Text(pDX, IDC_EDIT_LOCATION, m_strLocation);
	DDX_Text(pDX, IDC_EDIT_SETTING, m_strSetting);
	DDX_Text(pDX, IDC_EDIT_FRUIT, m_strFruit);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_strContent);
	DDX_CBString(pDX, IDC_COMBO_NAME, m_strName);
	DDX_CBString(pDX, IDC_COMBO_LEADER, m_strLeader);
	//��Ӵ���
	DDX_CBIndex(pDX,IDC_COMBO_CONDITION,m_iCondition);
	//��Ӵ������
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFulltimeDlg, CDialog)
	//{{AFX_MSG_MAP(CFulltimeDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_NOTIFY(NM_CLICK, IDC_LIST_FULLTIME, OnClickListFulltime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFulltimeDlg message handlers

void CFulltimeDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	//�����򡰻�����ϸ��Ϣ���е���������
	m_strCode = "";
	m_strName = "";
	m_strLeader = "";
	m_strLocation = "";
	m_strSetting = "";
    m_strFruit = "";
	//����水ť
	m_bntSave.EnableWindow();
	UpdateData(FALSE);
	//��Ӵ������	
}

void CFulltimeDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
    //��Ӵ���
	int i = m_ctrFulltime.GetSelectionMark();
    if(i<0)
    {
        MessageBox("��ѡ��һ����¼����ɾ����");
        return;
    }
    CString strSQL;
    strSQL.Format("select * from fulltime where code ='%s'", m_ctrFulltime.GetItemText(i,0));
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
	//ɾ���õ�λ
	m_recordset.Delete();
	m_recordset.Close();
	//���µ�λ�б�
	strSQL = "select * from fulltime";
	DataUpdate(strSQL);
	m_strCode = "";
	m_strName = "";
	m_strLeader = "";
	m_strLocation = "";
	m_strSetting = "";
	m_strFruit = "";
	UpdateData(FALSE);
	//��Ӵ������	
}

void CFulltimeDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	//����fulltime����������Ϊ�յ�����
	if(m_strName == "")
	{
		MessageBox("�����뵥λ���ƣ�");
		return;
	}
	if(m_strCode == "")
	{
		MessageBox("�����뵥λ���룡");
		return;
	}
	if(m_strLeader == "")
	{
		MessageBox("�����뵥λ�쵼��");
		return;
	}
	CString tableFulltime;
	//���̨���ݱ�fulltime������ȷ�����ݱ��浽ָ������
	tableFulltime = "select * from fulltime";
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,tableFulltime))
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
	m_recordset.m_fruit        = m_strFruit;
	//���ݼ�����
	m_recordset.Update();
	m_recordset.Close();
	//��Ӵ������	
}

void CFulltimeDlg::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	CString strSQL;
	if(0 == m_iCondition)
		strSQL.Format("select * from fulltime where code = '%s'",m_strContent);
	else if(1 == m_iCondition)
		strSQL.Format("select * from fulltime where leader = '%s'",m_strContent);
	else
		strSQL.Format("select * from fulltime where name = '%s'",m_strContent);
	//��ʾȫ����Ϣ
	if(m_strContent == "")
		strSQL = "select * from fulltime";
		DataUpdate(strSQL);
	//��Ӵ������	
}

void CFulltimeDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	int i = m_ctrFulltime.GetSelectionMark();
	if(i < 0)
	{
		MessageBox("��ѡ��һ����¼�����޸ģ�");
		return;
	}
	//�ǿ�����������ݵ���ʾ
	if(m_strName == "")
	{
		MessageBox("�����뵥λ���ƣ�");
		return;
	}
	if(m_strCode == "")
	{
		MessageBox("�����뵥λ���룡");
		return;
	}
	if(m_strLeader == "")
	{
		MessageBox("�����뵥λ�쵼��");
		return;
	}
	CString strSQL;
	//��ȡҪ�޸ĵĵ�λ����
    strSQL.Format("select * from fulltime where code ='%s'", m_ctrFulltime.GetItemText(i,0));
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
	m_recordset.m_fruit        = m_strFruit;
	m_recordset.Update();
	m_recordset.Close();
	DataUpdate(strSQL);     //���û����޸�д�غ�̨���ݿ�PostDB.accdb�����ݱ�fulltime��
	//��Ӵ������	
}

void CFulltimeDlg::OnClickListFulltime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	CString strSQL;
	UpdateData(TRUE);
	int i = m_ctrFulltime.GetSelectionMark();
	m_strCode = m_ctrFulltime.GetItemText(i,0);
    strSQL.Format("select * from fulltime where code ='%s'",m_strCode);
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
	m_strFruit        = m_recordset.m_fruit;
	m_recordset.Close();
	UpdateData(FALSE);
	//��Ӵ������	
	*pResult = 0;
}

BOOL CFulltimeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// ��Ӵ���
    m_ctrFulltime.InsertColumn(0,"��������");
    m_ctrFulltime.SetColumnWidth(0,40);
    m_ctrFulltime.InsertColumn(1,"��������");
    m_ctrFulltime.SetColumnWidth(1,40);
    m_ctrFulltime.InsertColumn(2,"�����쵼");
    m_ctrFulltime.SetColumnWidth(2,40);
    m_ctrFulltime.InsertColumn(3,"�칫�ص�");
    m_ctrFulltime.SetColumnWidth(3,80);
    m_ctrFulltime.InsertColumn(4,"��������");
    m_ctrFulltime.SetColumnWidth(0,80);
    m_ctrFulltime.InsertColumn(5,"���гɹ�");
    m_ctrFulltime.SetColumnWidth(1,80);
    m_ctrFulltime.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    CString strSQL;
    strSQL="select * from fulltime";
    DataUpdate(strSQL);
    // ��Ӵ������	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFulltimeDlg::DataUpdate(CString strSQL)
{
    //��Ӵ���
	m_ctrFulltime.SetFocus();
	m_ctrFulltime.DeleteAllItems();
	m_ctrFulltime.SetRedraw(FALSE);
	UpdateData(TRUE);
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
    int i=0;
    while(!m_recordset.IsEOF())
    {
		m_ctrFulltime.InsertItem(i,m_recordset.m_code);
		m_ctrFulltime.SetItemText(i,1,m_recordset.m_name);
		m_ctrFulltime.SetItemText(i,2,m_recordset.m_leader);
		m_ctrFulltime.SetItemText(i,3,m_recordset.m_location);
		m_ctrFulltime.SetItemText(i,4,m_recordset.m_organization);
		m_ctrFulltime.SetItemText(i,5,m_recordset.m_fruit);
		i++;
		m_recordset.MoveNext();
	}
	m_recordset.Close();
	m_ctrFulltime.SetRedraw(TRUE);
	//��Ӵ������
}
