// MeetingRecordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "MeetingRecordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeetingRecordDlg dialog


CMeetingRecordDlg::CMeetingRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMeetingRecordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMeetingRecordDlg)
	m_iCondition = -1;
	m_tmDate = 0;
	m_strSort = _T("");
	m_strContent = _T("");
	m_strLocation = _T("");
	m_strSubject = _T("");
	m_strHostUnit = _T("");
	m_strWriter = _T("");
	m_strPartiUnit = _T("");
	m_strHost = _T("");
	m_strRemark = _T("");
	m_strDetails = _T("");
	//}}AFX_DATA_INIT
	//��Ӵ���
	m_strNumber = "";
	//��Ӵ������
}


void CMeetingRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMeetingRecordDlg)
	DDX_Control(pDX, IDC_LIST_MEETING, m_ctrMeeting);
	DDX_Control(pDX, IDC_COMBO_CONDITION, m_ctrCondition);
	DDX_Control(pDX, IDOK, m_bntOK);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_bntCancel);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_bntUpdate);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_bntDelete);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_bntAdd);
	DDX_CBIndex(pDX, IDC_COMBO_CONDITION, m_iCondition);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATE, m_tmDate);
	DDX_CBString(pDX, IDC_COMBO_SORT, m_strSort);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_strContent);
	DDX_Text(pDX, IDC_EDIT_LOCATION, m_strLocation);
	DDX_Text(pDX, IDC_EDIT_SUBJECT, m_strSubject);
	DDX_Text(pDX, IDC_EDIT_HOSTUNIT, m_strHostUnit);
	DDX_Text(pDX, IDC_EDIT_WRITER1, m_strWriter);
	DDX_Text(pDX, IDC_EDIT_PARTICIPATEUNIT, m_strPartiUnit);
	DDX_Text(pDX, IDC_EDIT_HOST, m_strHost);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_strRemark);
	DDX_Text(pDX, IDC_EDIT_DETAILS, m_strDetails);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMeetingRecordDlg, CDialog)
	//{{AFX_MSG_MAP(CMeetingRecordDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MEETING, OnClickListMeeting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeetingRecordDlg message handlers

void CMeetingRecordDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	m_strContent = "";
	m_strHost = "";
	m_strLocation = "";
	m_strHostUnit = "";
	m_strWriter = "";
	m_strPartiUnit = "";
	m_strSort = "";
	m_strRemark = "";
	m_strSubject = "";
	m_tmDate = CTime::GetCurrentTime();
	m_strNumber = "-1";
	m_bntOK.EnableWindow();
	m_bntCancel.EnableWindow();
	UpdateData(FALSE);
	//��Ӵ������
}

void CMeetingRecordDlg::OnButtonCancel() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	//���Ի�����ȡ���뱣��������ť����Ϊ��ɫ��disenable״̬
	m_bntOK.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	//��Ӵ������
}

void CMeetingRecordDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	int i = m_ctrMeeting.GetSelectionMark();
	if(i < 0)
	{
		MessageBox("�ף�����ѡ��һ������ļ�¼ɾ����");
		return;
	}
	CString strSQL;
	strSQL.Format("select * from meetingRecord where number = %s",m_ctrMeeting.GetItemText(i,0));
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	//ɾ���û�ѡ��ļ�¼
	m_recordset.Delete();
	//�ر����ݼ�
	m_recordset.Close();
	//����ɾ����¼��Ի�������ؼ�������
	strSQL = "select * from meetingRecord";
	DataUpdate(strSQL);
	m_strContent = "";
	m_strHost = "";
	m_strLocation = "";
	m_strHostUnit = "";
	m_strWriter = "";
	m_strPartiUnit = "";
	m_strSort = "";
	m_strRemark = "";
	m_strSubject = "";
	m_tmDate = CTime::GetCurrentTime();
	UpdateData(FALSE);
	m_bntOK.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	//��Ӵ������
}

void CMeetingRecordDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	m_bntOK.EnableWindow();
	m_bntCancel.EnableWindow();
	//��Ӵ������
}

void CMeetingRecordDlg::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	CString strSQL;
	if(m_iCondition == 0)        //������ص��ѯ
		strSQL.Format("select * from meetingRecord where location = '%s'",m_strDetails);
	if(m_iCondition == 1)        //����������ѯ
		strSQL.Format("select * from meetingRecord where sort = '%s'",m_strDetails);
	if(m_iCondition == 2)        //�����������ѯ
		strSQL.Format("select * from meetingRecord where subject = '%s'",m_strDetails);
    if(m_iCondition == 3)        //���ٰ쵥λ��ѯ
		strSQL.Format("select * from meetingRecord where hostUnit = '%s'",m_strDetails);
	else if(m_iCondition == 4)   //�������˲�ѯ
		strSQL.Format("select * from meetingRecord where host = '%s'",m_strDetails);
	//����ѯ����Ϊ�գ���ȫ���ѯ
	if(m_strDetails == "")
		strSQL = "select * from meetingRecord";
	DataUpdate(strSQL);
	m_bntOK.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	//��Ӵ������
}

void CMeetingRecordDlg::OnOK() 
{
	// TODO: Add extra validation here
	//��Ӵ���
	UpdateData();
	if(m_strSubject == "")
	{
		MessageBox("�������ⲻ��Ϊ�գ������룡");
		return;
	}
	CString strSQL;
	strSQL.Format("select * from meetingRecord where number = %s",m_strNumber);
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	//���½����޸������������
	if(m_recordset.GetRecordCount() == 0)
	{
		m_recordset.AddNew();    //�½�
		m_recordset.m_sort             = m_strSort;
	    m_recordset.m_content          = m_strContent;
     	m_recordset.m_mDate            = m_tmDate;
	    m_recordset.m_host             = m_strHost;
	    m_recordset.m_writer           = m_strWriter;
	    m_recordset.m_host_Unit        = m_strHostUnit;
 	    m_recordset.m_location         = m_strLocation;
	    m_recordset.m_participate_Unit = m_strPartiUnit;
	    m_recordset.m_remark           = m_strRemark;
	    m_recordset.m_subject          = m_strSubject;
	    m_recordset.Update();
	}
	else
	{
		m_recordset.Edit();    //�޸�
		m_recordset.m_sort             = m_strSort;
	    m_recordset.m_content          = m_strContent;
     	m_recordset.m_mDate            = m_tmDate;
	    m_recordset.m_host             = m_strHost;
	    m_recordset.m_writer           = m_strWriter;
	    m_recordset.m_host_Unit        = m_strHostUnit;
 	    m_recordset.m_location         = m_strLocation;
	    m_recordset.m_participate_Unit = m_strPartiUnit;
	    m_recordset.m_remark           = m_strRemark;
	    m_recordset.m_subject          = m_strSubject;
	    m_recordset.Update();
	}
	m_recordset.Close();
	strSQL = "select * from meetingRecord";
	DataUpdate(strSQL);
	m_bntOK.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	//��Ӵ������
	CDialog::OnOK();
}

void CMeetingRecordDlg::OnClickListMeeting(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	m_bntOK.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	CString strSQL;
	UpdateData(TRUE);
	int i = m_ctrMeeting.GetSelectionMark();
	m_strNumber = m_ctrMeeting.GetItemText(i,0);
	strSQL.Format("select * from meetingRecord where number = %s",m_strNumber);
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	m_strSort = m_recordset.m_sort;
	m_strContent = m_recordset.m_content;
	m_tmDate = m_recordset.m_mDate;
	m_strHost = m_recordset.m_host;
	m_strHostUnit = m_recordset.m_host_Unit;
	m_strWriter = m_recordset.m_writer;
	m_strLocation = m_recordset.m_location;
	m_strPartiUnit = m_recordset.m_participate_Unit;
	m_strRemark = m_recordset.m_remark;
	m_strSubject = m_recordset.m_subject;
	m_recordset.Close();
	UpdateData(FALSE);
	//��Ӵ������
	*pResult = 0;
}

BOOL CMeetingRecordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//��Ӵ���
	m_ctrMeeting.InsertColumn(0,"���");
	m_ctrMeeting.SetColumnWidth(0,60);
	m_ctrMeeting.InsertColumn(1,"����ʱ��");
	m_ctrMeeting.SetColumnWidth(1,90);
	m_ctrMeeting.InsertColumn(2,"����ص�");
	m_ctrMeeting.SetColumnWidth(2,80);
	m_ctrMeeting.InsertColumn(3,"�������");
	m_ctrMeeting.SetColumnWidth(3,90);
	m_ctrMeeting.InsertColumn(4,"��������");
	m_ctrMeeting.SetColumnWidth(4,80);
	m_ctrMeeting.InsertColumn(5,"�ٰ쵥λ");
	m_ctrMeeting.SetColumnWidth(5,60);
	m_ctrMeeting.InsertColumn(6,"���뵥λ");
	m_ctrMeeting.SetColumnWidth(6,90);
	m_ctrMeeting.InsertColumn(7,"������");
	m_ctrMeeting.SetColumnWidth(7,80);
	m_ctrMeeting.InsertColumn(8,"��¼��");
	m_ctrMeeting.SetColumnWidth(8,90);
	m_ctrMeeting.InsertColumn(9,"��������");
	m_ctrMeeting.SetColumnWidth(9,180);
	m_ctrMeeting.InsertColumn(10,"��ע");
	m_ctrMeeting.SetColumnWidth(10,80);
	m_ctrMeeting.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	CString strSQL;
	strSQL = "select * from meetingRecord";
	DataUpdate(strSQL);
	m_bntOK.EnableWindow(FALSE);
	m_bntCancel.EnableWindow(FALSE);
	//��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMeetingRecordDlg::DataUpdate(CString strSQL)
{
	//��Ӵ���
	m_ctrMeeting.SetFocus();
	m_ctrMeeting.DeleteAllItems();
	m_ctrMeeting.SetRedraw(FALSE);
	CString strTime;
	char buffer[20];
	UpdateData(TRUE);
	if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
		MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
		return;
	}
	int i = 0;
	while(!m_recordset.IsEOF())
	{
		ltoa(m_recordset.m_number,buffer,10);
		m_ctrMeeting.InsertItem(i,buffer);
		strTime.Format("%d - %d - %d",m_recordset.m_mDate.GetYear(),m_recordset.m_mDate.GetMonth(),m_recordset.m_mDate.GetDay());
		m_ctrMeeting.SetItemText(i,1,strTime);
		m_ctrMeeting.SetItemText(i,2,m_recordset.m_location);
		m_ctrMeeting.SetItemText(i,3,m_recordset.m_sort);
		m_ctrMeeting.SetItemText(i,4,m_recordset.m_subject);
		m_ctrMeeting.SetItemText(i,5,m_recordset.m_host_Unit);
		m_ctrMeeting.SetItemText(i,6,m_recordset.m_participate_Unit);
		m_ctrMeeting.SetItemText(i,7,m_recordset.m_host);
		m_ctrMeeting.SetItemText(i,8,m_recordset.m_writer);
		m_ctrMeeting.SetItemText(i,9,m_recordset.m_content);
		m_ctrMeeting.SetItemText(i,10,m_recordset.m_remark);
		i++;
		m_recordset.MoveNext();
	}
	m_recordset.Close();
	m_ctrMeeting.SetRedraw(TRUE);
	//��Ӵ������
}
