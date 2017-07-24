// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "LoginDlg.h"
//��Ӵ���
#include <afxdb.h>      //���ODBC���ݿ���Ķ����ļ�afxdb.h
#include "User.h"
//��Ӵ������
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_strUser = _T("");
	m_strPassword = _T("");
	//}}AFX_DATA_INIT
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_ctrPassword);
	DDX_Control(pDX, IDC_COMBO_USER, m_ctrUser);
	DDX_CBString(pDX, IDC_COMBO_USER, m_strUser);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
	//��Ӵ���
	CUser recordset;
	CString strSQL;
	CDatabaseApp*ptheApp = (CDatabaseApp * ) AfxGetApp();
	UpdateData(TRUE);
	//���û���Ϊ��,��Ҫ���û������û���
	if(m_strUser.IsEmpty())
	{
		AfxMessageBox("�û�������Ϊ��,�������û���!");
		m_ctrUser.SetFocus();
		return;}
	if(m_strPassword.IsEmpty())
	{
		AfxMessageBox("���벻��Ϊ��,��������ȷ������!");
		m_ctrPassword.SetFocus();
		return;
	}
	//����û������������ȷ��
	strSQL.Format("select*from user where customer = '%s' AND \password = '%s'",m_strUser,m_strPassword);
	if(! recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
		return;
	}
	if(recordset.GetRecordCount()==0)
	{
		//����������������룻���ڼ򻯳��������޶����������ֱ���û�������ȷΪֹ
		recordset.Close();
		MessageBox("����������,����������!");
		m_strPassword = "";
		m_ctrPassword.SetFocus();
		UpdateData(FALSE);
	}
	else
	{
		//ָ���û�����Ȩ��
		ptheApp -> m_bHasSuperAuthority = recordset.m_privilege;
		recordset.Close();
		CDialog::OnOK();
	}
	//��Ӵ������
}

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//��Ӵ���
	CUser recordset;
	CString strSQL;
	UpdateData(TRUE);
	strSQL = "select*from user";
	if(! recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
		return FALSE;
	}
	while(! recordset.IsEOF())
	{
		m_ctrUser.AddString(recordset.m_customer);
		recordset.MoveNext();
	}
	recordset.Close();
	//��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
