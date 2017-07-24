// ContactsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "ContactsDlg.h"
//��Ӵ���
#include "NewCThinDlg.h"
//��Ӵ������
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContactsDlg dialog


CContactsDlg::CContactsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CContactsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CContactsDlg)
	m_iCondition = -1;
	m_strContent = _T("");
	//}}AFX_DATA_INIT
}


void CContactsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CContactsDlg)
	DDX_Control(pDX, IDC_LIST_THIN, m_ctrThin);
	DDX_CBIndex(pDX, IDC_COMBO_CONDITION, m_iCondition);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_strContent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CContactsDlg, CDialog)
	//{{AFX_MSG_MAP(CContactsDlg)
	ON_BN_CLICKED(IDC_BUTTON_VIEW, OnButtonView)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContactsDlg message handlers

void CContactsDlg::OnButtonView() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	CString strSQL;
	strSQL = "select * from contacts";
	DataUpdate(strSQL);
	//��Ӵ������
}

void CContactsDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	//�����ͨ�Ų���Ϣ�ĶԻ���IDD_DIALOG_NEWCTHIN
	if(IDOK != m_pDlg.DoModal())
		return;
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	m_recordset.AddNew();
	m_recordset.m_name       = m_pDlg.m_strName;
	m_recordset.m_sex        = m_pDlg.m_strSex;
	m_recordset.m_fPhone     = m_pDlg.m_strFPhone;
	m_recordset.m_oPhone     = m_pDlg.m_strOPhone;
	m_recordset.m_mPhone     = m_pDlg.m_strMPhone;
	m_recordset.m_short      = m_pDlg.m_strShort;
	m_recordset.m_QQ         = m_pDlg.m_strQQ;
	m_recordset.m_weChat     = m_pDlg.m_strWeChat;
	m_recordset.m_email      = m_pDlg.m_strEmail;
	m_recordset.m_unit       = m_pDlg.m_strUnit;
	m_recordset.m_remark     = m_pDlg.m_strRemark;
	m_recordset.Update();
	m_recordset.Close();
	CString strSQL;
	strSQL = "select * from contacts ";
	DataUpdate(strSQL);
	//��Ӵ������
}

void CContactsDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	int i = m_ctrThin.GetSelectionMark();
	if(i < 0)
	{
		MessageBox("�ף�����ѡ��һ������ļ�¼ɾ����");
		return;
	}
	CString strSQL;
	strSQL.Format("select * from contacts where number = %s",m_ctrThin.GetItemText(i,0));
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	m_recordset.Delete();
	m_recordset.Close();
	strSQL = "select * from contacts";
	DataUpdate(strSQL);
	//��Ӵ������
}

void CContactsDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	int i = m_ctrThin.GetSelectionMark();
	if(i < 0)
	{
		MessageBox("�ף���ѡ��һ������ļ�¼�޸ģ�");
		return;
	}
	m_pDlg.m_strName      = m_ctrThin.GetItemText(i,1);
	m_pDlg.m_strSex       = m_ctrThin.GetItemText(i,2);
	m_pDlg.m_strFPhone    = m_ctrThin.GetItemText(i,3);
	m_pDlg.m_strOPhone    = m_ctrThin.GetItemText(i,4);
	m_pDlg.m_strMPhone    = m_ctrThin.GetItemText(i,5);
	m_pDlg.m_strShort     = m_ctrThin.GetItemText(i,6);
	m_pDlg.m_strQQ        = m_ctrThin.GetItemText(i,7);
	m_pDlg.m_strWeChat    = m_ctrThin.GetItemText(i,8);
	m_pDlg.m_strEmail     = m_ctrThin.GetItemText(i,9);
	m_pDlg.m_strUnit      = m_ctrThin.GetItemText(i,10);
	m_pDlg.m_strRemark    = m_ctrThin.GetItemText(i,11);
    if(IDOK != m_pDlg.DoModal())
		return;
	CString strSQL;
	strSQL.Format("select * from contacts where number = %s",m_ctrThin.GetItemText(i,0));
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	m_recordset.Edit();
	m_recordset.m_name       = m_pDlg.m_strName;
	m_recordset.m_sex        = m_pDlg.m_strSex;
	m_recordset.m_fPhone     = m_pDlg.m_strFPhone;
	m_recordset.m_oPhone     = m_pDlg.m_strOPhone;
	m_recordset.m_mPhone     = m_pDlg.m_strMPhone;
	m_recordset.m_short      = m_pDlg.m_strShort;
	m_recordset.m_QQ         = m_pDlg.m_strQQ;
	m_recordset.m_weChat     = m_pDlg.m_strWeChat;
	m_recordset.m_email      = m_pDlg.m_strEmail;
	m_recordset.m_unit       = m_pDlg.m_strUnit;
	m_recordset.m_remark     = m_pDlg.m_strRemark;
	m_recordset.Update();
	m_recordset.Close();
	strSQL = "select * from contacts";
	DataUpdate(strSQL);
	//��Ӵ������
}

void CContactsDlg::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	CString strSQL;
	if(m_iCondition == 0)        //���ֻ���ѯ
		strSQL.Format("select * from contacts where mphone = '%s'",m_strContent);
	if(m_iCondition == 1)        //���Ա��ѯ
		strSQL.Format("select * from contacts where sex = '%s'",m_strContent);
	else if(m_iCondition == 2)   //��������ѯ
		strSQL.Format("select * from contacts where name = '%s'",m_strContent);
	//ȫ���ѯ
	if(m_strContent == "")
		strSQL = "select * from contacts";
	DataUpdate(strSQL);
	//��Ӵ������
}

BOOL CContactsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//��Ӵ���
	m_ctrThin.InsertColumn(0,"���");
	m_ctrThin.SetColumnWidth(0,50);
	m_ctrThin.InsertColumn(1,"����");
	m_ctrThin.SetColumnWidth(1,60);
	m_ctrThin.InsertColumn(2,"�Ա�");
	m_ctrThin.SetColumnWidth(2,50);
	m_ctrThin.InsertColumn(3,"��ͥ�绰");
	m_ctrThin.SetColumnWidth(3,80);
	m_ctrThin.InsertColumn(4,"�칫�绰");
	m_ctrThin.SetColumnWidth(4,80);
	m_ctrThin.InsertColumn(5,"�ֻ�");
	m_ctrThin.SetColumnWidth(5,80);
	m_ctrThin.InsertColumn(6,"�̺�");
	m_ctrThin.SetColumnWidth(6,40);
	m_ctrThin.InsertColumn(7,"QQ");
	m_ctrThin.SetColumnWidth(7,60);
	m_ctrThin.InsertColumn(8,"΢�ź�");
	m_ctrThin.SetColumnWidth(8,80);
	m_ctrThin.InsertColumn(9,"��������");
	m_ctrThin.SetColumnWidth(9,100);
	m_ctrThin.InsertColumn(10,"��λ");
	m_ctrThin.SetColumnWidth(10,100);
	m_ctrThin.InsertColumn(11,"��ע");
	m_ctrThin.SetColumnWidth(11,200);
	m_ctrThin.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	CString strSQL;
	strSQL = "select * from contacts";
	DataUpdate(strSQL);
	//��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CContactsDlg::DataUpdate(CString strSQL)
{
	//��Ӵ���
	m_ctrThin.SetFocus();
	m_ctrThin.DeleteAllItems();
	m_ctrThin.SetRedraw(FALSE);
	UpdateData(TRUE);
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	char buffer[20];
	int i = 0;
	while(!m_recordset.IsEOF())
	{
		ltoa(m_recordset.m_number,buffer,10);
		m_ctrThin.InsertItem(i,buffer);
		m_ctrThin.SetItemText(i,1,m_recordset.m_name);
		m_ctrThin.SetItemText(i,2,m_recordset.m_sex);
		m_ctrThin.SetItemText(i,3,m_recordset.m_fPhone);
		m_ctrThin.SetItemText(i,4,m_recordset.m_oPhone);
		m_ctrThin.SetItemText(i,5,m_recordset.m_mPhone);
		m_ctrThin.SetItemText(i,6,m_recordset.m_short);
		m_ctrThin.SetItemText(i,7,m_recordset.m_QQ);
		m_ctrThin.SetItemText(i,8,m_recordset.m_weChat);
		m_ctrThin.SetItemText(i,9,m_recordset.m_email);
		m_ctrThin.SetItemText(i,10,m_recordset.m_unit);
		m_ctrThin.SetItemText(i,11,m_recordset.m_remark);
		i++;
		m_recordset.MoveNext();
	}
	m_recordset.Close();
	m_ctrThin.SetRedraw(TRUE);
	//��Ӵ������
}
