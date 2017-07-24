// TechnicalAccessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "TechnicalAccessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTechnicalAccessDlg dialog


CTechnicalAccessDlg::CTechnicalAccessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTechnicalAccessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTechnicalAccessDlg)
	m_tmGDate = 0;
	m_tmBDate = 0;
	m_tmEDate = 0;
	m_strMode = _T("");
	m_strTitle = _T("");
	m_strEmploy = _T("");
	m_strHire = _T("");
	m_strUnit = _T("");
	// ���Ӵ���
    m_strCode = "";
    // ���Ӵ������
	//}}AFX_DATA_INIT
}


void CTechnicalAccessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTechnicalAccessDlg)
	DDX_Control(pDX, IDC_LIST_TECHNICALACCESS, m_ctrTAccess);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_bntSave);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_bntUpdate);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_bntDelete);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_bntAdd);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_GDATE, m_tmGDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BDATE, m_tmBDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_EDATE, m_tmEDate);
	DDX_CBString(pDX, IDC_COMBO_MODE, m_strMode);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_EMPLOY, m_strEmploy);
	DDX_Text(pDX, IDC_EDIT_HIRE, m_strHire);
	DDX_Text(pDX, IDC_EDIT_UNIT, m_strUnit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTechnicalAccessDlg, CDialog)
	//{{AFX_MSG_MAP(CTechnicalAccessDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TECHNICALACCESS, OnClickListTechnicalaccess)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTechnicalAccessDlg message handlers

void CTechnicalAccessDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	// ���Ӵ���
m_strEmploy  = "";
m_strHire    = "";
m_strMode    = "";
m_strTitle   = "";
m_strUnit    = "";
m_tmBDate  = CTime::GetCurrentTime();
m_tmEDate  = CTime::GetCurrentTime();
m_tmGDate  = CTime::GetCurrentTime();
m_bntSave.EnableWindow();
m_bntAdd.EnableWindow(FALSE);
m_bntDelete.EnableWindow(FALSE);
m_bntUpdate.EnableWindow(FALSE);
UpdateData(FALSE);
// ���Ӵ������
}

void CTechnicalAccessDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	// ���Ӵ���
int i = m_ctrTAccess.GetSelectionMark();
if(i<0)
{
MessageBox("��ѡ��һ����¼����ɾ����");
return;
}
CString strSQL;
strSQL.Format("select * from technicalAssesswhere number = %s",m_ctrTAccess.GetItemText(i,0));
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
//ɾ���ü�¼
m_recordset.Delete();
m_recordset.Close();
//�����û�����
DataUpdate(m_strCode);
m_strEmploy    = "";
m_strHire       = "";
m_strMode     = "";
m_strTitle  = "";
m_strUnit       = "";
m_tmBDate  = CTime::GetCurrentTime();
m_tmEDate       = CTime::GetCurrentTime();
m_tmGDate       = CTime::GetCurrentTime();
UpdateData(FALSE);
// ���Ӵ������
}

void CTechnicalAccessDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	// ���Ӵ���
UpdateData();
int i = m_ctrTAccess.GetSelectionMark();
if(i<0)
{
MessageBox("��ѡ��һ����¼�����޸ģ�");
return;
}
CString strSQL;
strSQL.Format("select * from technicalAssess where number = %s",m_ctrTAccess.GetItemText(i,0));
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
m_recordset.Edit();
m_recordset.m_begin         = m_tmBDate;
m_recordset.m_end           = m_tmEDate;
m_recordset.m_assess_Date   = m_tmGDate;
m_recordset.m_employ        = m_strEmploy;
m_recordset.m_hire          = m_strHire;
m_recordset.m_mode          = m_strMode;
m_recordset.m_title         = m_strTitle;
m_recordset.m_unit          = m_strUnit;
m_recordset.Update();
m_recordset.Close();
DataUpdate(m_strCode);
// ���Ӵ������
}

void CTechnicalAccessDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	// ���Ӵ���
UpdateData();
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
if(m_strTitle=="")
{
MessageBox("רҵ�����ʸ����Ʋ���Ϊ�գ�������רҵ�����ʸ����ƣ�");
return;
}
m_recordset.AddNew();
m_recordset.m_employ      = m_strEmploy;
m_recordset.m_hire        = m_strHire;
m_recordset.m_begin       = m_tmBDate;
m_recordset.m_end         = m_tmEDate;
m_recordset.m_assess_Date = m_tmGDate;
m_recordset.m_mode        = m_strMode;
m_recordset.m_title       = m_strTitle;
m_recordset.m_unit        =   m_strUnit;
// �̹����codeҲҪ�������̨���ݿ�PostDB.accdb��
m_recordset.m_code  =   m_strCode  ;
m_recordset.Update();
m_recordset.Close();
DataUpdate(m_strCode);
// ���Ӵ������
}

void CTechnicalAccessDlg::OnClickListTechnicalaccess(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// ���Ӵ���
CString strSQL;
UpdateData(TRUE);
int i = m_ctrTAccess.GetSelectionMark();
strSQL.Format("select * from technicalAssess where number =%s",m_ctrTAccess.GetItemText(i,0));
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
m_strEmploy  = m_recordset.m_employ;
m_strHire    = m_recordset.m_hire;
m_tmGDate    = m_recordset.m_assess_Date;
m_tmBDate    = m_recordset.m_begin;
m_tmEDate    = m_recordset.m_end;
m_strMode    = m_recordset.m_mode;
m_strTitle   = m_recordset.m_title;
m_strUnit    = m_recordset.m_unit;
m_recordset.Close();
UpdateData(FALSE);
m_bntSave.EnableWindow(FALSE);
m_bntAdd.EnableWindow();
m_bntDelete.EnableWindow();
m_bntUpdate.EnableWindow();
// ���Ӵ������
	*pResult = 0;
}

BOOL CTechnicalAccessDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// ���Ӵ���
// ��ʼ��ְ�������Ի����е��б��ؼ���ͷ
m_ctrTAccess.InsertColumn(0,"���");
m_ctrTAccess.SetColumnWidth(0,60);
m_ctrTAccess.InsertColumn(1,"רҵ�����ʸ�����");
m_ctrTAccess.SetColumnWidth(1,80);
m_ctrTAccess.InsertColumn(2,"������ʽ");
m_ctrTAccess.SetColumnWidth(2,80);
m_ctrTAccess.InsertColumn(3,"������λ");
m_ctrTAccess.SetColumnWidth(3,80);
m_ctrTAccess.InsertColumn(4,"ȡ��ʱ��");
m_ctrTAccess.SetColumnWidth(4,80);
m_ctrTAccess.InsertColumn(5,"Ƹ��רҵ����ְ��");
m_ctrTAccess.SetColumnWidth(5,80);
m_ctrTAccess.InsertColumn(6,"Ƹ�ÿ�ʼʱ��");
m_ctrTAccess.SetColumnWidth(6,80);
m_ctrTAccess.InsertColumn(7,"Ƹ�ý���ʱ��");
m_ctrTAccess.SetColumnWidth(7,80);
m_ctrTAccess.InsertColumn(8,"Ƹ�õ�λ");
m_ctrTAccess.SetColumnWidth(8,80);
m_ctrTAccess.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
m_bntSave.EnableWindow(FALSE);
m_bntAdd.EnableWindow(FALSE);
m_bntDelete.EnableWindow(FALSE);
m_bntUpdate.EnableWindow(FALSE);
// ���Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTechnicalAccessDlg::DataUpdate(CString strCode)
{
    // ���Ӵ���
m_ctrTAccess.DeleteAllItems();
m_ctrTAccess.SetRedraw(FALSE);
UpdateData(TRUE);
CString strSQL;
m_strCode.Format("%s",strCode);
// SQL�����������ʽ�е�code�ǽ̹��Ĺ���
strSQL.Format( "select * from technicalAssess where code = '%s'",strCode);
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
int i=0;
CString strGTime; // ��Ӧȡ��ʱ��
CString strBTime; // ��ӦƸ�ÿ�ʼʱ��
CString strETime; // ��ӦƸ�ý���ʱ��
char buffer[20];
while(!m_recordset.IsEOF())
{
// ��Ӧ�б����ϵ����
_ltoa(m_recordset.m_numder,buffer,10);
m_ctrTAccess.InsertItem(i,buffer);
// ��Ӧ�б����ϵ�רҵ�����ʸ�����
m_ctrTAccess.SetItemText(i,1,m_recordset.m_title);
// ��Ӧ�б����ϵ�������ʽ
m_ctrTAccess.SetItemText(i,2,m_recordset.m_mode);
// ��Ӧ�б����ϵ�������λ
m_ctrTAccess.SetItemText(i,3,m_recordset.m_unit);
// ��Ӧ�б����ϵ�ȡ��ʱ��
strGTime.Format("%d-%d-%d",m_recordset.m_assess_Date.GetYear(),m_recordset.\
	m_assess_Date.GetMonth(),m_recordset.m_assess_Date.GetDay());
m_ctrTAccess.SetItemText(i,4,strGTime);
// ��Ӧ�б����ϵ�Ƹ��רҵ����ְ��
m_ctrTAccess.SetItemText(i,5,m_recordset.m_hire);
// ��Ӧ�б����ϵ�Ƹ�ÿ�ʼʱ��
strBTime.Format("%d-%d-%d",m_recordset.m_begin.GetYear(),m_recordset.m_begin.\
	GetMonth(),m_recordset.m_begin.GetDay());
m_ctrTAccess.SetItemText(i,6,strBTime);
// ��Ӧ�б����ϵ�Ƹ�ý���ʱ��
strETime.Format("%d-%d-%d",m_recordset.m_end.GetYear(),m_recordset.m_end.\
    GetMonth(),m_recordset.m_end.GetDay());
m_ctrTAccess.SetItemText(i,7,strETime);
// ��Ӧ�б����ϵ�Ƹ�õ�λ
m_ctrTAccess.SetItemText(i,8,m_recordset.m_employ);
i++;
m_recordset.MoveNext();
}
m_recordset.Close();
m_ctrTAccess.SetRedraw(TRUE);
// �����Ƿ������µ�ְ��������¼���������뱣��������ť��״̬
m_bntSave.EnableWindow(FALSE);
if(m_strCode=="")
m_bntAdd.EnableWindow(FALSE);
else
m_bntAdd.EnableWindow();
m_bntDelete.EnableWindow(FALSE);
m_bntUpdate.EnableWindow(FALSE);
// ���Ӵ������
}