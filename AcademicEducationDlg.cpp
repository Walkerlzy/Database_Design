// AcademicEducationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "AcademicEducationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAcademicEducationDlg dialog


CAcademicEducationDlg::CAcademicEducationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAcademicEducationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAcademicEducationDlg)
	m_tmBDate = 0;
	m_tmEDate = 0;
	m_strDegree = _T("");
	m_strDiploma = _T("");
	m_strDepartment = _T("");
	m_strUniversity = _T("");
	m_strMajor = _T("");
	// ��Ӵ���
    m_strCode = "";
    // ��Ӵ������
	//}}AFX_DATA_INIT
}


void CAcademicEducationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAcademicEducationDlg)
	DDX_Control(pDX, IDC_LIST_ACADEMICEDUCATION, m_ctrAEducation);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_bntSave);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_bntUpdate);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_bntDelete);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_bntAdd);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BDATE, m_tmBDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_EDATE, m_tmEDate);
	DDX_CBString(pDX, IDC_COMBO_DEGREE, m_strDegree);
	DDX_CBString(pDX, IDC_COMBO_DIPLOMA, m_strDiploma);
	DDX_Text(pDX, IDC_EDIT_DEPARTMENT, m_strDepartment);
	DDX_Text(pDX, IDC_EDIT_UNIVERSITY, m_strUniversity);
	DDX_Text(pDX, IDC_EDIT_MAJOR, m_strMajor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAcademicEducationDlg, CDialog)
	//{{AFX_MSG_MAP(CAcademicEducationDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ACADEMICEDUCATION, OnClickListAcademiceducation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAcademicEducationDlg message handlers

void CAcademicEducationDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
	m_strDegree     = "";
	m_strDepartment = "";
	m_strDiploma    = "";
	m_strMajor      = "";
	m_strUniversity = "";
	m_tmBDate  = CTime::GetCurrentTime();
	m_tmEDate  = CTime::GetCurrentTime();
	m_bntSave.EnableWindow();
	m_bntAdd.EnableWindow(FALSE);
	m_bntDelete.EnableWindow(FALSE);
	m_bntUpdate.EnableWindow(FALSE);
	UpdateData(FALSE);
	// ��Ӵ������
}

void CAcademicEducationDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
int i = m_ctrAEducation.GetSelectionMark();
if(i<0)
{
MessageBox("��ѡ��һ����¼����ɾ����");
return;
}
CString strSQL;
strSQL.Format("select * from academicEducation where number = %s",m_ctrAEducation.GetItemText(i,0));
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
m_strDegree     = "";
m_strDepartment = "";
m_strDiploma    = "";
m_strMajor      = "";
m_strUniversity = "";
m_tmBDate       = CTime::GetCurrentTime();
m_tmEDate       = CTime::GetCurrentTime();
UpdateData(FALSE);
// ��Ӵ������
}

void CAcademicEducationDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
UpdateData();
int i = m_ctrAEducation.GetSelectionMark();
if(i<0)
{
MessageBox("��ѡ��һ����¼�����޸ģ�");
return;
}
CString strSQL;
strSQL.Format("select * from academicEducation where number = %s",m_ctrAEducation.GetItemText(i,0));
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
m_recordset.Edit();
m_recordset.m_begin        = m_tmBDate;
m_recordset.m_end          = m_tmEDate;
m_recordset.m_degree       = m_strDegree;
m_recordset.m_department   = m_strDepartment;
m_recordset.m_diploma      = m_strDiploma;
m_recordset.m_major        = m_strMajor;
m_recordset.m_university   = m_strUniversity;
m_recordset.Update();
m_recordset.Close();
DataUpdate(m_strCode);
// ��Ӵ������
}

void CAcademicEducationDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
UpdateData();
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
if(m_strDiploma=="")
{
MessageBox("ѧ������Ϊ�գ�������ѧ�����ƣ�");
return;
}
if(m_strDegree=="")
{
MessageBox("ѧλ����Ϊ�գ�������ѧλ���ƣ�");
return;
}
m_recordset.AddNew();
m_recordset.m_degree     = m_strDegree;
m_recordset.m_department = m_strDepartment;
m_recordset.m_begin      = m_tmBDate;
m_recordset.m_end        = m_tmEDate;
m_recordset.m_diploma    = m_strDiploma;
m_recordset.m_major      = m_strMajor;
m_recordset.m_university = m_strUniversity;
// �̹����codeҲҪ�������̨���ݿ�PostDB.accdb��
m_recordset.m_code       = m_strCode;
m_recordset.Update();
m_recordset.Close();
DataUpdate(m_strCode);
// ��Ӵ������
}

void CAcademicEducationDlg::OnClickListAcademiceducation(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
CString strSQL;
UpdateData(TRUE);
int i = m_ctrAEducation.GetSelectionMark();
strSQL.Format("select * from academicEducation where number =%s",m_ctrAEducation.GetItemText(i,0));
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
m_strDegree     = m_recordset.m_degree;
m_strDepartment = m_recordset.m_department;
m_tmBDate       = m_recordset.m_begin;
m_tmEDate       = m_recordset.m_end;
m_strDiploma    = m_recordset.m_diploma;
m_strMajor      = m_recordset.m_major;
m_strUniversity = m_recordset.m_university;
m_recordset.Close();
UpdateData(FALSE);
m_bntSave.EnableWindow(FALSE);
m_bntAdd.EnableWindow();
m_bntDelete.EnableWindow();
m_bntUpdate.EnableWindow();
// ��Ӵ������
	*pResult = 0;
}

BOOL CAcademicEducationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// ��Ӵ���
// ��ʼ��ѧ�������Ի����е��б�ؼ���ͷ
m_ctrAEducation.InsertColumn(0,"���");
m_ctrAEducation.SetColumnWidth(0,60);
m_ctrAEducation.InsertColumn(1,"��ʼʱ��");
m_ctrAEducation.SetColumnWidth(1,80);
m_ctrAEducation.InsertColumn(2,"����ʱ��");
m_ctrAEducation.SetColumnWidth(2,80);
m_ctrAEducation.InsertColumn(3,"��ҵԺУ");
m_ctrAEducation.SetColumnWidth(3,80);
m_ctrAEducation.InsertColumn(4,"����Ժϵ");
m_ctrAEducation.SetColumnWidth(4,80);
m_ctrAEducation.InsertColumn(5,"��ѧרҵ");
m_ctrAEducation.SetColumnWidth(5,80);
m_ctrAEducation.InsertColumn(6,"ѧ��");
m_ctrAEducation.SetColumnWidth(6,80);
m_ctrAEducation.InsertColumn(7,"ѧλ");
m_ctrAEducation.SetColumnWidth(7,80);
m_ctrAEducation.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
m_bntSave.EnableWindow(FALSE);
m_bntAdd.EnableWindow(FALSE);
m_bntDelete.EnableWindow(FALSE);
m_bntUpdate.EnableWindow(FALSE);
// ��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAcademicEducationDlg::DataUpdate(CString strCode)
{
    // ��Ӵ���
m_ctrAEducation.DeleteAllItems();
m_ctrAEducation.SetRedraw(FALSE);
UpdateData(TRUE);
CString strSQL;
m_strCode.Format("%s",strCode);
// SQL����������ʽ�е�code�ǽ̹��Ĺ���
strSQL.Format( "select * from academicEducation where code = '%s'",strCode);
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
int i=0;
CString strBTime; // ��Ӧ��ʼʱ��
CString strETime; // ��Ӧ����ʱ��
char buffer[20];
while(!m_recordset.IsEOF())
{
// ��Ӧ�б���ϵ����
_ltoa(m_recordset.m_number,buffer,10);
m_ctrAEducation.InsertItem(i,buffer);
// ��Ӧ�б���ϵĿ�ʼʱ��
strBTime.Format("%d-%d-%d",m_recordset.m_begin.GetYear(),m_recordset.m_begin.\
	GetMonth(),m_recordset.m_begin.GetDay());
m_ctrAEducation.SetItemText(i,1,strBTime);
// ��Ӧ�б���ϵĽ���ʱ��
strETime.Format("%d-%d-%d",m_recordset.m_end.GetYear(),m_recordset.m_end.GetMonth(),\
	m_recordset.m_end.GetDay());
m_ctrAEducation.SetItemText(i,2,strETime);
// ��Ӧ�б���ϵı�ҵԺУ
m_ctrAEducation.SetItemText(i,3,m_recordset.m_university);
// ��Ӧ�б���ϵ�����Ժϵ
m_ctrAEducation.SetItemText(i,4,m_recordset.m_department);
// ��Ӧ�б���ϵ���ѧרҵ
m_ctrAEducation.SetItemText(i,5,m_recordset.m_major);
// ��Ӧ�б���ϵ�ѧ��
m_ctrAEducation.SetItemText(i,6,m_recordset.m_diploma);
// ��Ӧ�б���ϵ�ѧλ
m_ctrAEducation.SetItemText(i,7,m_recordset.m_degree);
i++;
m_recordset.MoveNext();
}
m_recordset.Close();
m_ctrAEducation.SetRedraw(TRUE);
// �����Ƿ�����µ�ѧ��������¼��������뱣��������ť��״̬
m_bntSave.EnableWindow(FALSE);
if(m_strCode=="")
m_bntAdd.EnableWindow(FALSE);
else
m_bntAdd.EnableWindow();
m_bntDelete.EnableWindow(FALSE);
m_bntUpdate.EnableWindow(FALSE);
// ��Ӵ������
}
