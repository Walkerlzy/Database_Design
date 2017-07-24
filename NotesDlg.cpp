// NotesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "NotesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotesDlg dialog


CNotesDlg::CNotesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNotesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNotesDlg)
	m_iCondition = -1;
	m_tmDate = 0;
	m_strType = _T("");
	m_strContent = _T("");
	m_strContext = _T("");
	m_strTitle = _T("");
	m_strUnit = _T("");
	m_strWriter = _T("");
	//}}AFX_DATA_INIT
	//��Ӵ���
	m_strNumber = "";
	//��Ӵ������
}


void CNotesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNotesDlg)
	DDX_Control(pDX, IDC_LIST_NOTES, m_ctrNotes);
	DDX_Control(pDX, IDC_COMBO_CONDITION, m_ctrCondition);
	DDX_Control(pDX, IDOK, m_bntOK);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_bntCancel);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_bntUpdate);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_bntDelete);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_bntAdd);
	DDX_CBIndex(pDX, IDC_COMBO_CONDITION, m_iCondition);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATE, m_tmDate);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_strType);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_strContent);
	DDX_Text(pDX, IDC_EDIT_CONTEXT, m_strContext);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_UNIT1, m_strUnit);
	DDX_Text(pDX, IDC_EDIT_WRITER, m_strWriter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNotesDlg, CDialog)
	//{{AFX_MSG_MAP(CNotesDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_NOTIFY(NM_CLICK, IDC_LIST_NOTES, OnClickListNotes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotesDlg message handlers

void CNotesDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	m_strType = "";
	m_strTitle = "";
	m_strContext = "";
	m_strNumber = "-1";
	m_strUnit = "";
	m_strWriter = "";
	m_tmDate = CTime::GetCurrentTime();
	m_bntOK.EnableWindow();
	m_bntCancel.EnableWindow();
	UpdateData(FALSE);
	//��Ӵ������
}

void CNotesDlg::OnButtonCancel() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	//���Ի�����ȡ���뱣��������ť����Ϊ��ɫ��disenable״̬
	m_bntOK.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	//��Ӵ������
}

void CNotesDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	int i = m_ctrNotes.GetSelectionMark();
	if(i < 0)
	{
		MessageBox("�ף���ѡ��һ������ļ�¼ɾ����");
		return;
	}
	CString strSQL;
	strSQL.Format("select * from notes where number = %s",m_ctrNotes.GetItemText(i,0));
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	//ɾ���û�ѡ��ļ�¼
	m_recordset.Delete();
	//�ر����ݼ�
	m_recordset.Close();
	//����ɾ����¼��Ի����¼���Ҫ���¼��������ؼ��ڵ�����
	strSQL = "select * from notes";
	DataUpdate(strSQL);
	m_strType = "";
	m_strTitle = "";
	m_strContext = "";
	m_strUnit = "";
	m_strWriter = "";
	m_tmDate = CTime::GetCurrentTime();
	UpdateData(FALSE);
	m_bntOK.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	//��Ӵ������
}

void CNotesDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	m_bntOK.EnableWindow();
	m_bntCancel.EnableWindow();
	//��Ӵ������
}

void CNotesDlg::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	CString strSQL;
	if(m_iCondition == 0)
		strSQL.Format("select * from notes where type = %s",m_strContent);
	else
		strSQL.Format("select * from notes where title = %s",m_strContent);
	if(m_strContent == "")
		strSQL = "select * from notes";
	DataUpdate(strSQL);
	m_bntOK.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	//��Ӵ������
}

void CNotesDlg::OnOK() 
{
	// TODO: Add extra validation here
	//��Ӵ���
	UpdateData();
	if(m_strType == "")
	{
		MessageBox("�¼����Ͳ���Ϊ�գ������룡");
		return;
	}
	CString strSQL;
	strSQL.Format("select * from notes where number = %s",m_strNumber);
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	//���½����޸������������
	if(m_recordset.GetRecordCount() == 0)
	{
		m_recordset.AddNew();   //�½�
		m_recordset.m_type = m_strType;
		m_recordset.m_title = m_strTitle;
		m_recordset.m_rDate = m_tmDate;
		m_recordset.m_content = m_strContext;
		m_recordset.m_writer = m_strWriter;
		m_recordset.m_wUnit = m_strUnit;
		m_recordset.Update();
	}
	else
	{
		m_recordset.Edit();    //�޸�
		m_recordset.m_type = m_strType;
		m_recordset.m_title = m_strTitle;
		m_recordset.m_rDate = m_tmDate;
		m_recordset.m_content = m_strContext;
		m_recordset.m_writer = m_strWriter;
		m_recordset.m_wUnit = m_strUnit;
		m_recordset.Update();
	}
    m_recordset.Close();
	strSQL = "select * from notes";
	DataUpdate(strSQL);
	m_bntOK.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	//��Ӵ������
	CDialog::OnOK();
}

void CNotesDlg::OnClickListNotes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	m_bntOK.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	CString strSQL;
	UpdateData(TRUE);
	int i = m_ctrNotes.GetSelectionMark();
	m_strNumber = m_ctrNotes.GetItemText(i,0);
    strSQL.Format("select * from notes where number = %s",m_strNumber);
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	m_strType = m_recordset.m_type;
	m_strTitle = m_recordset.m_title;
	m_tmDate = m_recordset.m_rDate;
	m_strContext = m_recordset.m_content;
	m_strUnit = m_recordset.m_wUnit;
	m_strWriter = m_recordset.m_writer;
	m_recordset.Close();
	UpdateData(FALSE);
	//��Ӵ������
	*pResult = 0;
}

BOOL CNotesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//��Ӵ���
	m_ctrNotes.InsertColumn(0,"���");
	m_ctrNotes.SetColumnWidth(0,60);
	m_ctrNotes.InsertColumn(1,"�¼�����");
	m_ctrNotes.SetColumnWidth(1,90);
	m_ctrNotes.InsertColumn(2,"��¼����");
	m_ctrNotes.SetColumnWidth(2,80);
	m_ctrNotes.InsertColumn(3,"�¼�����");
	m_ctrNotes.SetColumnWidth(3,90);
	m_ctrNotes.InsertColumn(4,"��¼��");
	m_ctrNotes.SetColumnWidth(4,80);
	m_ctrNotes.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	CString strSQL;
	strSQL = "select * from notes";
	DataUpdate(strSQL);
    m_bntOK.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	//��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNotesDlg::DataUpdate(CString strSQL)
{
    //��Ӵ���
	m_ctrNotes.SetFocus();
    m_ctrNotes.DeleteAllItems();
	m_ctrNotes.SetRedraw(FALSE);
	CString strTime;
	char buffer[20];
	UpdateData(TRUE);
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	int i = 0;
	while(!m_recordset.IsBOF())
	{
		ltoa(m_recordset.m_number,buffer,10);
        m_ctrNotes.InsertItem(i,buffer);
		m_ctrNotes.SetItemText(i,1,m_recordset.m_title);
		strTime.Format("%d - %d - %d",m_recordset.m_rDate.GetYear(),m_recordset.m_rDate.GetMonth(),m_recordset.m_rDate.GetDay());
		m_ctrNotes.SetItemText(i,2,strTime);
		m_ctrNotes.SetItemText(i,3,m_recordset.m_type);
		m_ctrNotes.SetItemText(i,4,m_recordset.m_writer);
		m_ctrNotes.SetItemText(i,5,m_recordset.m_content);
		i++;
		m_recordset.MoveNext();
	}
	m_recordset.Close();
	m_ctrNotes.SetRedraw(TRUE);
	//��Ӵ������
}
