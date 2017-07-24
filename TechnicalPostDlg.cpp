// TechnicalPostDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "TechnicalPostDlg.h"
// ��Ӵ���
#include "AddBaseInfoDlg.h"
// ��Ӵ������
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTechnicalPostDlg dialog


CTechnicalPostDlg::CTechnicalPostDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTechnicalPostDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTechnicalPostDlg)
	//}}AFX_DATA_INIT
}


void CTechnicalPostDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTechnicalPostDlg)
	DDX_Control(pDX, IDC_LIST_TECHNICALPOST, m_ctrTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTechnicalPostDlg, CDialog)
	//{{AFX_MSG_MAP(CTechnicalPostDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTechnicalPostDlg message handlers

void CTechnicalPostDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
    // ��Ӵ���
    // ���������Ϣ�Ĺ���ģ��
    CAddBaseInfoDlg abid;
    abid.m_strLabel = " ְ����� ";
    abid.m_strInformation = "ְ�ƣ�";
    if(abid.DoModal()!=IDOK)
    return;
    CString strSQL;
    strSQL.Format("select * from technicalPost where title='%s'",abid.m_strData);
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
    // �ж��û���ӵ�ְ������Ƿ��Ѿ��������ݿ���
    if(m_recordset.GetRecordCount()!=0)
    {
        m_recordset.Close();
        MessageBox("��ְ���Ѿ����ڣ�");
        return;
    }
    // ����µ�ְ�ƽ��
    m_recordset.AddNew();
    m_recordset.m_title = abid.m_strData;
    m_recordset.m_description = abid.m_strDescription;
    m_recordset.Update();
    m_recordset.Close();
    DataUpdate();
    // ��Ӵ������	
}

void CTechnicalPostDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
    // ��Ӵ���
    UpdateData(TRUE);
    int i = m_ctrTitle.GetSelectionMark();
    if(i<0)
    {
        MessageBox("��ѡ��һ���û���");
        return;
    }
    CString strSQL;
    strSQL.Format("select * from technicalPost where title='%s'",  m_ctrTitle.GetItemText(i,1));
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

BOOL CTechnicalPostDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    // ��Ӵ���
    // ��ʼ��ְ�ƽ��Ի����е��б�ؼ���ͷ
    m_ctrTitle.InsertColumn(0,"���");
    m_ctrTitle.SetColumnWidth(0,40);
    m_ctrTitle.InsertColumn(1,"ְ��");
    m_ctrTitle.SetColumnWidth(1,60);
    m_ctrTitle.InsertColumn(2,"����");
    m_ctrTitle.SetColumnWidth(2,80);
    m_ctrTitle.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    DataUpdate();
    // ��Ӵ������	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTechnicalPostDlg::DataUpdate()
{
    // ��Ӵ���
    m_ctrTitle.SetFocus();
    m_ctrTitle.DeleteAllItems();
    m_ctrTitle.SetRedraw(FALSE);
    CString strSQL;
    char  buffer[20];
    UpdateData(TRUE);
    strSQL="select * from technicalPost";
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
    return ;
    }
    int i=0;
    while(!m_recordset.IsEOF())
    {
        ltoa(m_recordset.m_ID,buffer,10);
        m_ctrTitle.InsertItem(i,buffer);
        m_ctrTitle.SetItemText(i,1,m_recordset.m_title);
        m_ctrTitle.SetItemText(i,2,m_recordset.m_description);
        i++;
        m_recordset.MoveNext();
    }
    m_recordset.Close();
    m_ctrTitle.SetRedraw(TRUE);
    // ��Ӵ������
}
