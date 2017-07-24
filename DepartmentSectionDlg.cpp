// DepartmentSectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "DepartmentSectionDlg.h"
// ��Ӵ���
#include "AddBaseInfoDlg.h"
// ��Ӵ������
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDepartmentSectionDlg dialog


CDepartmentSectionDlg::CDepartmentSectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDepartmentSectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDepartmentSectionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDepartmentSectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDepartmentSectionDlg)
	DDX_Control(pDX, IDC_LIST_DEPARTMENTSECTION, m_ctrDivision);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDepartmentSectionDlg, CDialog)
	//{{AFX_MSG_MAP(CDepartmentSectionDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDepartmentSectionDlg message handlers

void CDepartmentSectionDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
    // ��Ӵ���
    // ���������Ϣ�Ĺ���ģ��
    CAddBaseInfoDlg abid;
    abid.m_strLabel = " Ժϵ���ţ� ";
    abid.m_strInformation = "��λ��";
    if(abid.DoModal()!=IDOK)
    return;
    CString strSQL;
    strSQL.Format("select * from departmentSection where division='%s'",abid.m_strData);
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
    }
    // �ж��û���ӵ�Ժϵ�����Ƿ��Ѿ��������ݿ���
    if(m_recordset.GetRecordCount()!=0)
    {
        m_recordset.Close();
        MessageBox("�õ�λ�Ѿ����ڣ�");
        return;
    }
    // ����µ�Ժϵ����
    m_recordset.AddNew();
    m_recordset.m_division = abid.m_strData;
    m_recordset.m_description = abid.m_strDescription;
    m_recordset.Update();
    m_recordset.Close();
    DataUpdate();
    // ��Ӵ������	
}

void CDepartmentSectionDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
    // ��Ӵ���
    UpdateData(TRUE);
    int i = m_ctrDivision.GetSelectionMark();
    if(i<0)
    {
        MessageBox("��ѡ��һ���û���");
        return;
    }
    CString strSQL;
    strSQL.Format("select * from departmentSection where division='%s'",  m_ctrDivision.GetItemText(i,1));
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

BOOL CDepartmentSectionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    // ��Ӵ���
    // ��ʼ��Ժϵ���ŶԻ����е��б�ؼ���ͷ
    m_ctrDivision.InsertColumn(0,"���");
    m_ctrDivision.SetColumnWidth(0,40);
    m_ctrDivision.InsertColumn(1,"��λ");
    m_ctrDivision.SetColumnWidth(1,60);
    m_ctrDivision.InsertColumn(2,"����");
    m_ctrDivision.SetColumnWidth(2,80);
    m_ctrDivision.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    DataUpdate();
    // ��Ӵ������	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDepartmentSectionDlg::DataUpdate()
{
    // ��Ӵ���
    m_ctrDivision.SetFocus();
    m_ctrDivision.DeleteAllItems();
    m_ctrDivision.SetRedraw(FALSE);
    CString strSQL;
    char  buffer[20];
    UpdateData(TRUE);
    strSQL="select * from departmentSection";
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
         MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
         return ;
    }
    int i=0;
    while(!m_recordset.IsEOF())
   {
        ltoa(m_recordset.m_ID,buffer,10);
    m_ctrDivision.InsertItem(i,buffer);
    m_ctrDivision.SetItemText(i,1,m_recordset.m_division);
    m_ctrDivision.SetItemText(i,2,m_recordset.m_description);
    i++;
    m_recordset.MoveNext();
    }
    m_recordset.Close();
    m_ctrDivision.SetRedraw(TRUE);
    // ��Ӵ������
}
