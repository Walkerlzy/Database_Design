// PoliticalStatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "PoliticalStatusDlg.h"
// ��Ӵ���
#include "AddBaseInfoDlg.h"
// ��Ӵ������
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPoliticalStatusDlg dialog


CPoliticalStatusDlg::CPoliticalStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPoliticalStatusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPoliticalStatusDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPoliticalStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPoliticalStatusDlg)
	DDX_Control(pDX, IDC_LIST_POLITICALSTATUS, m_ctrParty);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPoliticalStatusDlg, CDialog)
	//{{AFX_MSG_MAP(CPoliticalStatusDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPoliticalStatusDlg message handlers

void CPoliticalStatusDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
    // ��Ӵ���
    // ���������Ϣ�Ĺ���ģ��
    CAddBaseInfoDlg abid;
    abid.m_strLabel = " ������ò�� ";
    abid.m_strInformation = "���ɣ�";
    if(abid.DoModal()!=IDOK)
    return;
    CString strSQL;
    strSQL.Format("select * from politicalStatus where party='%s'",abid.m_strData);
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
         MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
         return ;
    }
    // �ж��û���ӵ�������ò�Ƿ��Ѿ��������ݿ���
    if(m_recordset.GetRecordCount()!=0)
    {
         m_recordset.Close();
         MessageBox("�õ����Ѿ����ڣ�");
         return;
    }
    // ����µ�������ò
    m_recordset.AddNew();
    m_recordset.m_party = abid.m_strData;
    m_recordset.m_description = abid.m_strDescription;
    m_recordset.Update();
    m_recordset.Close();
    DataUpdate();
    // ��Ӵ������	
}

void CPoliticalStatusDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
    // ��Ӵ���
    UpdateData(TRUE);
    int i = m_ctrParty.GetSelectionMark();
    if(i<0)
    {
        MessageBox("��ѡ��һ���û���");
        return;
    }
    CString strSQL;
    strSQL.Format("select * from politicalStatus where party='%s'",  m_ctrParty.GetItemText(i,1));
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
         MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
         return ;
    }
    // ɾ�����û�
    m_recordset.Delete();
    m_recordset.Close();
    DataUpdate();
    // ��Ӵ������	
}

BOOL CPoliticalStatusDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    // ��Ӵ���
    // ��ʼ��������ò�Ի����е��б�ؼ���ͷ
    m_ctrParty.InsertColumn(0,"���");
    m_ctrParty.SetColumnWidth(0,40);
    m_ctrParty.InsertColumn(1,"����");
    m_ctrParty.SetColumnWidth(1,60);    
    m_ctrParty.InsertColumn(2,"����");
    m_ctrParty.SetColumnWidth(2,80);
    m_ctrParty.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    DataUpdate();
    // ��Ӵ������	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPoliticalStatusDlg::DataUpdate()
{
    // ��Ӵ���
    m_ctrParty.SetFocus();
    m_ctrParty.DeleteAllItems();
    m_ctrParty.SetRedraw(FALSE);
    CString strSQL;
    char  buffer[20];
    UpdateData(TRUE);
    strSQL="select * from politicalStatus";
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
         MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
         return ;
    }
    int i=0;
    while(!m_recordset.IsEOF())
    {
         ltoa(m_recordset.m_ID,buffer,10);
         m_ctrParty.InsertItem(i,buffer);
         m_ctrParty.SetItemText(i,1,m_recordset.m_party);
         m_ctrParty.SetItemText(i,2,m_recordset.m_description);
         i++;
         m_recordset.MoveNext();
    }
    m_recordset.Close();
    m_ctrParty.SetRedraw(TRUE);
    // ��Ӵ������
}
