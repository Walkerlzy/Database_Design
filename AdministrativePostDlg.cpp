// AdministrativePostDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "AdministrativePostDlg.h"
// ��Ӵ���
#include "AddBaseInfoDlg.h"
// ��Ӵ������
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdministrativePostDlg dialog


CAdministrativePostDlg::CAdministrativePostDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdministrativePostDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdministrativePostDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAdministrativePostDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdministrativePostDlg)
	DDX_Control(pDX, IDC_LIST_ADMINISTRATIVEPOST, m_ctrRank);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdministrativePostDlg, CDialog)
	//{{AFX_MSG_MAP(CAdministrativePostDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdministrativePostDlg message handlers

void CAdministrativePostDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
    // ��Ӵ���
    // ���������Ϣ�Ĺ���ģ��
    CAddBaseInfoDlg abid;
    abid.m_strLabel = " ����ְ�� ";
    abid.m_strInformation = "ְ��";
    if(abid.DoModal()!=IDOK)
    return;
    CString strSQL;
    strSQL.Format("select * from administrativePost where rank='%s'",abid.m_strData);
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
    // �ж��û���ӵ�����ְ���Ƿ��Ѿ��������ݿ���
    if(m_recordset.GetRecordCount()!=0)
    {
        m_recordset.Close();
    MessageBox("��ְ���Ѿ����ڣ�");
    return;
    }
    // ����µ�����ְ��
    m_recordset.AddNew();
    m_recordset.m_rank = abid.m_strData;
    m_recordset.m_description = abid.m_strDescription;
    m_recordset.Update();
    m_recordset.Close();
    DataUpdate();
    // ��Ӵ������	
}

void CAdministrativePostDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
    // ��Ӵ���
    UpdateData(TRUE);
    int i = m_ctrRank.GetSelectionMark();
    if(i<0)
    {
        MessageBox("��ѡ��һ���û���");
        return;
    }
    CString strSQL;
    strSQL.Format("select * from administrativePost where rank='%s'",  m_ctrRank.GetItemText(i,1));
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

BOOL CAdministrativePostDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    // ��Ӵ���
    // ��ʼ������ְ��Ի����е��б�ؼ���ͷ
    m_ctrRank.InsertColumn(0,"���");
    m_ctrRank.SetColumnWidth(0,40);
    m_ctrRank.InsertColumn(1,"ְ��");
    m_ctrRank.SetColumnWidth(1,60);
    m_ctrRank.InsertColumn(2,"����");
    m_ctrRank.SetColumnWidth(2,80);
    m_ctrRank.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    DataUpdate();
    // ��Ӵ������	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAdministrativePostDlg::DataUpdate()
{
    // ��Ӵ���
    m_ctrRank.SetFocus();
    m_ctrRank.DeleteAllItems();
    m_ctrRank.SetRedraw(FALSE);
    CString strSQL;
    char  buffer[20];
    UpdateData(TRUE);
    strSQL="select * from administrativePost";
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
    int i=0;
    while(!m_recordset.IsEOF())
    {
    ltoa(m_recordset.m_ID,buffer,10);
    m_ctrRank.InsertItem(i,buffer);
    m_ctrRank.SetItemText(i,1,m_recordset.m_rank);
    m_ctrRank.SetItemText(i,2,m_recordset.m_description);
    i++;
    m_recordset.MoveNext();
    }
    m_recordset.Close();
    m_ctrRank.SetRedraw(TRUE);
    // ��Ӵ������
}
