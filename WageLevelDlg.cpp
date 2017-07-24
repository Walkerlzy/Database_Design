// WageLevelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "WageLevelDlg.h"
// ��Ӵ���
#include "AddBaseInfoDlg.h"
// ��Ӵ������
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWageLevelDlg dialog


CWageLevelDlg::CWageLevelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWageLevelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWageLevelDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWageLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWageLevelDlg)
	DDX_Control(pDX, IDC_LIST_WAGELEVEL, m_ctrSalary);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWageLevelDlg, CDialog)
	//{{AFX_MSG_MAP(CWageLevelDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWageLevelDlg message handlers

void CWageLevelDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
    // ��Ӵ���
    // ���������Ϣ�Ĺ���ģ��
    CAddBaseInfoDlg abid;
    abid.m_strLabel = " ���ʵȼ��� ";
    abid.m_strInformation = "�ȼ���";
    if(abid.DoModal()!=IDOK)
    return;
    CString strSQL;
    strSQL.Format("select * from wageLevel where salary='%s'",abid.m_strData);
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
    // �ж��û���ӵĹ��ʵȼ��Ƿ��Ѿ��������ݿ���
    if(m_recordset.GetRecordCount()!=0)
    {
        m_recordset.Close();
        MessageBox("�õȼ��Ѿ����ڣ�");
        return;
    }
    // ����µĹ��ʵȼ�
    m_recordset.AddNew();
    m_recordset.m_salary = abid.m_strData;
    m_recordset.m_description = abid.m_strDescription;
    m_recordset.Update();
    m_recordset.Close();
    DataUpdate();
    // ��Ӵ������	
}

void CWageLevelDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
    // ��Ӵ���
    UpdateData(TRUE);
    int i = m_ctrSalary.GetSelectionMark();
    if(i<0)
    {
        MessageBox("��ѡ��һ���û���");
        return;
    }
    CString strSQL;
    strSQL.Format("select * from wageLevel where salary='%s'",  m_ctrSalary.GetItemText(i,1));
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

BOOL CWageLevelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    // ��Ӵ���
    // ��ʼ�����ʵȼ��Ի����е��б�ؼ���ͷ
    m_ctrSalary.InsertColumn(0,"���");
    m_ctrSalary.SetColumnWidth(0,40);
    m_ctrSalary.InsertColumn(1,"�ȼ�");
    m_ctrSalary.SetColumnWidth(1,60);
    m_ctrSalary.InsertColumn(2,"����");
    m_ctrSalary.SetColumnWidth(2,80);
    m_ctrSalary.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    DataUpdate();
    // ��Ӵ������	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWageLevelDlg::DataUpdate()
{
    // ��Ӵ���
    m_ctrSalary.SetFocus();
    m_ctrSalary.DeleteAllItems();
    m_ctrSalary.SetRedraw(FALSE);
    CString strSQL;
    char  buffer[20];
    UpdateData(TRUE);
    strSQL="select * from wageLevel";
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return; 
    }
    int i=0;
    while(!m_recordset.IsEOF())
    {
        ltoa(m_recordset.m_ID,buffer,10);
        m_ctrSalary.InsertItem(i,buffer);
        m_ctrSalary.SetItemText(i,1,m_recordset.m_salary);
        m_ctrSalary.SetItemText(i,2,m_recordset.m_description);
        i++;
        m_recordset.MoveNext();
    }
    m_recordset.Close();
    m_ctrSalary.SetRedraw(TRUE);
    // ��Ӵ������
}
