// UserSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "UserSettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserSettingDlg dialog


CUserSettingDlg::CUserSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserSettingDlg)
	m_bAuthority = FALSE;
	m_strUserName = _T("");
	m_strPassword = _T("");
	m_strConfirm = _T("");
	//}}AFX_DATA_INIT
}


void CUserSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserSettingDlg)
	DDX_Control(pDX, IDC_LIST_USERLIST, m_ctrUserList);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_ctrPassword);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_ctrUserName);
	DDX_Control(pDX, IDOK, m_bntOK);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_bntAdd);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_bntDelete);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_bntCancel);
	DDX_Check(pDX, IDC_CHECK_AUTHORITY, m_bAuthority);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_CONFIRM, m_strConfirm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CUserSettingDlg)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_NOTIFY(NM_CLICK, IDC_LIST_USERLIST, OnClickListUserlist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserSettingDlg message handlers

void CUserSettingDlg::OnButtonCancel() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	m_strUserName="";
	m_strPassword="";
	m_strConfirm="";
	m_bAuthority=FALSE;
	m_ctrUserName.EnableWindow(FALSE);
	UpdateData(FALSE);
	//��Ӵ������	
}

void CUserSettingDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData(TRUE);
	//�ж�������û��Ƿ����
	if(m_strUserName=="")
	{
		MessageBox("�ף�����ѡ��һ��Ӧ�����ڵ��û���");
		return;
	}
	CString strSQL;
	strSQL.Format("select * from user where customer='%s'",m_strUserName);
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	//ɾ�����û�
	m_recordset.Delete();
	m_recordset.Close();
	//ˢ���û��б�
	DataUpdate();
	m_strUserName="";
	m_strPassword="";
	m_strConfirm="";
	m_bAuthority=FALSE;
	UpdateData(FALSE);
	//��Ӵ������	
}

void CUserSettingDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	//��յ�ǰ�û���Ϣ��ʹ������ֳ�ʼ��״̬
	m_strUserName="";
	m_strPassword="";
	m_strConfirm="";
	m_bAuthority=FALSE;
	//�û����༭��ı��ֹ״̬��������뽹�㣬��Ϊ������״̬
	m_ctrUserName.EnableWindow(TRUE);
	m_ctrUserName.SetFocus();
	UpdateData(FALSE);
	//��Ӵ������	
}

void CUserSettingDlg::OnOK() 
{
	// TODO: Add extra validation here
	//��Ӵ���
	UpdateData();
	if(m_ctrUserName.IsWindowEnabled())
	{
		//��������û����Ƿ�Ϊ��
		if(m_strUserName=="")
		{
			MessageBox("����д�û�����");
			m_ctrUserName.SetFocus();
			return;
		}
	}
	else
	{
		if(m_strUserName=="")
		{
			MessageBox("��ѡ��һ���û���");
			return;
		}
	}
	//���벻��Ϊ��
	if(m_strPassword=="")
	{
		MessageBox("���벻��Ϊ�գ����������룡");
		m_ctrPassword.SetFocus();
		return;
	}
	//�������֤
	if(m_strPassword!=m_strConfirm)
	{
		MessageBox("������������벻һ�£��������������룡");
		m_ctrPassword.SetFocus();
		m_strPassword="";
		m_strConfirm="";
		UpdateData(FALSE);
		return;
	}
	//�򿪺�̨���ݿ��user�ļ�¼��
	CString strSQL;
	strSQL.Format("select* from user where customer='%s'",m_strUserName);
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	if(m_ctrUserName.IsWindowEnabled())
	{
		//�����µ��û�
		//�ж�������û��Ƿ�Ӧ������
		if(m_recordset.GetRecordCount()!=0)
		{
			m_recordset.Close();
			MessageBox("���û��Ѿ�����!");
			return;
		}
		m_recordset.AddNew();
		m_recordset.m_customer=m_strUserName;
		m_recordset.m_password=m_strPassword;
		m_recordset.m_privilege=m_bAuthority;
		m_recordset.Update();
		MessageBox("�û���ӳɹ������ס�û��������룡");
		m_recordset.Close();
	}
	else
	{
		//�޸��û���Ϣ
		//�ж�Ҫ�޸ĵ��û��Ƿ��ں�̨���ݿ��в�����
		if(m_recordset.GetRecordCount()==0)
		{
			m_recordset.Close();
			MessageBox("���û������ڣ���������ݿ�");
			return;
		}
		m_recordset.Edit();
		m_recordset.m_customer=m_strUserName;
		m_recordset.m_password =m_strPassword;
		m_recordset.m_privilege =m_bAuthority;
		m_recordset.Update();
		MessageBox("�û��޸ĳɹ������ס�û��������룡");
		m_recordset.Close();
	}
	m_ctrUserName.EnableWindow(FALSE);
	//�������˽�к����������û��б�
	DataUpdate();
	//��Ӵ������	
	//CDialog::OnOK();
}

void CUserSettingDlg::OnClickListUserlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	CString strSQL;
	UpdateData(TRUE);
	//�����ݿ�PostDB�б�user��ȡѡ���û���������
	int i=m_ctrUserList.GetSelectionMark();
	m_strUserName=m_ctrUserList.GetItemText(i,0);
	strSQL.Format("select * from user where customer='%s'",m_strUserName);
	if(! m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	//���û��б�ؼ����б�����ʾѡȡ���û���Ϣ
	m_strPassword=m_recordset.m_password;
	m_strConfirm=m_strPassword;
	m_bAuthority=m_recordset.m_privilege;
	m_recordset.Close();
	UpdateData(FALSE);
	*pResult=0;
	//��Ӵ������	
	*pResult = 0;
}

BOOL CUserSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//��Ӵ���
	//��ʼ���б�ؼ���ֻ����һ���û�����
	m_ctrUserList.InsertColumn(0,"�û���");
	m_ctrUserList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrUserList.SetColumnWidth(0,120);
	//������û��б�������û���
	DataUpdate();
	//��Ӵ������	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserSettingDlg::DataUpdate()
{
	//��Ӵ���
	m_ctrUserList.SetFocus();
	//����û��б�
	m_ctrUserList.DeleteAllItems();
	m_ctrUserList.SetRedraw(FALSE);
	CString strSQL;
	UpdateData(TRUE);
	//�򿪺�̨���ݿ�PostDB��user�ļ�¼��
	strSQL="select * from user";
	if(! m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	//��ӱ�user���û������û��б���
	int i=0;
	while(! m_recordset.IsEOF())
	{
		m_ctrUserList.InsertItem(i++,m_recordset.m_customer);
		m_recordset.MoveNext();
	}
	m_recordset.Close();
	m_ctrUserList.SetRedraw(TRUE);
	//��Ӵ������
}
