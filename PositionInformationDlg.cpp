// PositionInformationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "PositionInformationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPositionInformationDlg dialog


CPositionInformationDlg::CPositionInformationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPositionInformationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPositionInformationDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPositionInformationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPositionInformationDlg)
	DDX_Control(pDX, IDC_LIST_POSITIONINFORMATON, m_ctrPost);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPositionInformationDlg, CDialog)
	//{{AFX_MSG_MAP(CPositionInformationDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPositionInformationDlg message handlers

void CPositionInformationDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
    // ���������Ϣ�Ĺ���ģ��
    CAddBaseInfoDlg abid;
    abid.m_strLabel = " �̹���λ�� ";
    abid.m_strInformation = "��λ��";
    if(abid.DoModal()!=IDOK)
    return;
    CString strSQL;
    strSQL.Format("select * from positionInformation where post='%s'",abid.m_strData);
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
         MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
         return ;
	}
    // �ж��û���ӵĽ̹���λ�Ƿ��Ѿ��������ݿ���
    if(m_recordset.GetRecordCount()!=0)
	{
        m_recordset.Close();
        MessageBox("�ø�λ�Ѿ����ڣ�");
        return;
	}
    // ����µĽ̹���λ
    m_recordset.AddNew();
    m_recordset.m_post = abid.m_strData;
    m_recordset.m_description = abid.m_strDescription;
    m_recordset.Update();
    m_recordset.Close();
    DataUpdate();
    // ��Ӵ������
}

void CPositionInformationDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
    UpdateData(TRUE);
    int i = m_ctrPost.GetSelectionMark();
    if(i<0)
	{
         MessageBox("��ѡ��һ���û���");
         return;
	}
    CString strSQL;
    strSQL.Format("select * from positionInformation where post='%s'",\
		m_ctrPost.GetItemText(i,1));
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

BOOL CPositionInformationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// ��Ӵ���
    // ��ʼ���̹�����Ի����е��б�ؼ���ͷ
    m_ctrPost.InsertColumn(0,"���");
    m_ctrPost.SetColumnWidth(0,40);
    m_ctrPost.InsertColumn(1,"��λ");
    m_ctrPost.SetColumnWidth(1,60);
    m_ctrPost.InsertColumn(2,"����");
    m_ctrPost.SetColumnWidth(2,80);
    m_ctrPost.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    DataUpdate();
    // ��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPositionInformationDlg::DataUpdate()
{
    // ��Ӵ���
    m_ctrPost.SetFocus();
    m_ctrPost.DeleteAllItems();
    m_ctrPost.SetRedraw(FALSE);
    CString strSQL;
    char  buffer[20];
    UpdateData(TRUE);
    strSQL="select * from positionInformation";
    if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
         MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
         return ;
	}
    int i=0;
    while(!m_recordset.IsEOF())
	{
        ltoa(m_recordset.m_ID,buffer,10);
        m_ctrPost.InsertItem(i,buffer);
        m_ctrPost.SetItemText(i,1,m_recordset.m_post);
        m_ctrPost.SetItemText(i,2,m_recordset.m_description);
        i++;
        m_recordset.MoveNext();
	}
    m_recordset.Close();
    m_ctrPost.SetRedraw(TRUE);
    // ��Ӵ������
}
