// ClassTeachingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "ClassTeachingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClassTeachingDlg dialog


CClassTeachingDlg::CClassTeachingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClassTeachingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClassTeachingDlg)
	m_strSemester = _T("");
	m_strSort = _T("");
	m_strObject = _T("");
	m_strAnnual = _T("");
	m_strCourse = _T("");
	m_strLocation = _T("");
	m_strClass = _T("");
	m_strHour = _T("");
	m_strLevel = _T("");
	// ��Ӵ���
    m_strCode = "";
    // ��Ӵ������
	//}}AFX_DATA_INIT
}


void CClassTeachingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClassTeachingDlg)
	DDX_Control(pDX, IDC_LIST_CLASSTEACHING, m_ctrTeaching);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_bntSave);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_bntUpdate);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_bntDelete);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_bntAdd);
	DDX_CBString(pDX, IDC_COMBO_SEMESTER, m_strSemester);
	DDX_CBString(pDX, IDC_COMBO_SORT, m_strSort);
	DDX_CBString(pDX, IDC_COMBO_OBJECT, m_strObject);
	DDX_Text(pDX, IDC_EDIT_ANNUAL, m_strAnnual);
	DDX_Text(pDX, IDC_EDIT_COURSE, m_strCourse);
	DDX_Text(pDX, IDC_EDIT_LOCATION, m_strLocation);
	DDX_Text(pDX, IDC_EDIT_CLASS, m_strClass);
	DDX_Text(pDX, IDC_EDIT_HOUR, m_strHour);
	DDX_CBString(pDX, IDC_COMBO_LEVEL, m_strLevel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClassTeachingDlg, CDialog)
	//{{AFX_MSG_MAP(CClassTeachingDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CLASSTEACHING, OnClickListClassteaching)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassTeachingDlg message handlers

void CClassTeachingDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
m_strAnnual   = "";
m_strClass    = "";
m_strCourse   = "";
m_strHour     = "";
m_strLevel    = "";
m_strLocation = "";
m_strObject   = "";
m_strSemester = "";
m_strSort     = "";
m_bntSave.EnableWindow();
m_bntAdd.EnableWindow(FALSE);
m_bntDelete.EnableWindow(FALSE);
m_bntUpdate.EnableWindow(FALSE);
UpdateData(FALSE);
// ��Ӵ������
}

void CClassTeachingDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
int i = m_ctrTeaching.GetSelectionMark();
if(i<0)
{
MessageBox("��ѡ��һ����¼����ɾ����");
return;
}
CString strSQL;
strSQL.Format("select * from classTeaching where number =%s",m_ctrTeaching.GetItemText(i,0));
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
m_strAnnual     = "";
m_strClass      = "";
m_strCourse     = "";
m_strHour       = "";
m_strLevel      = "";
m_strLocation   = "";
m_strObject     = "";
m_strSemester   = "";
m_strSort       = "";
UpdateData(FALSE);
// ��Ӵ������
}

void CClassTeachingDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
UpdateData();
int i = m_ctrTeaching.GetSelectionMark();
if(i<0)
{
MessageBox("��ѡ��һ����¼�����޸ģ�");
return;
}
CString strSQL;
strSQL.Format("select * from classTeaching where number = %s",m_ctrTeaching.GetItemText(i,0));
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
m_recordset.Edit();
m_recordset.m_annual       = m_strAnnual;
m_recordset.m_class        = m_strClass;
m_recordset.m_course       = m_strCourse;
m_recordset.m_level        = m_strLevel;
m_recordset.m_object       = m_strObject;
m_recordset.m_hour         = m_strHour;
m_recordset.m_sort         = m_strSort;
m_recordset.m_location     = m_strLocation;
m_recordset.m_semester     = m_strSemester;
m_recordset.Update();
m_recordset.Close();
DataUpdate(m_strCode);
// ��Ӵ������
}

void CClassTeachingDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
UpdateData();
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
if(m_strCourse=="")
{
MessageBox("�γ�������Ϊ�գ�������γ����ƣ�");
return;
}
if(m_strClass=="")
{
MessageBox("�ڿΰ༶����Ϊ�գ��������ڿΰ༶���ƣ�");
return;
}
m_recordset.AddNew();
m_recordset.m_annual    = m_strAnnual;
m_recordset.m_class     = m_strClass;
m_recordset.m_course    = m_strCourse;
m_recordset.m_level     = m_strLevel;
m_recordset.m_object    = m_strObject;
m_recordset.m_location  = m_strLocation;
m_recordset.m_sort      = m_strSort;
m_recordset.m_semester  = m_strSemester;
m_recordset.m_hour      = m_strHour;
// �̹����codeҲҪ�������̨���ݿ�PostDB.accdb��
m_recordset.m_code      = m_strCode;
m_recordset.Update();
m_recordset.Close();
DataUpdate(m_strCode);
// ��Ӵ������
}

void CClassTeachingDlg::OnClickListClassteaching(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
CString strSQL;
UpdateData(TRUE);
int i = m_ctrTeaching.GetSelectionMark();
strSQL.Format("select * from classTeaching where number = %s",m_ctrTeaching.GetItemText(i,0));
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
m_strAnnual     = m_recordset.m_annual;
m_strClass      = m_recordset.m_class;
m_strCourse     = m_recordset.m_course;
m_strLevel      = m_recordset.m_level;
m_strObject     = m_recordset.m_object;
m_strHour       = m_recordset.m_hour;
m_strObject     = m_recordset.m_object;
m_strLocation   = m_recordset.m_location;
m_strSemester   = m_recordset.m_semester;
m_recordset.Close();
UpdateData(FALSE);
m_bntSave.EnableWindow(FALSE);
m_bntAdd.EnableWindow();
m_bntDelete.EnableWindow();
m_bntUpdate.EnableWindow();
// ��Ӵ������
	*pResult = 0;
}

BOOL CClassTeachingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// ��Ӵ���
// ��ʼ�����������Ի����е��б�ؼ���ͷ
// ��ȣ���ѧ�ڣ����γ��������γ����ʣ����γ���𣺡��ڿΰ༶�����ڿζ��󣺡�ѧʱ������ص㣺
m_ctrTeaching.InsertColumn(0,"���");
m_ctrTeaching.SetColumnWidth(0,60);
m_ctrTeaching.InsertColumn(1,"���");
m_ctrTeaching.SetColumnWidth(1,80);
m_ctrTeaching.InsertColumn(2,"ѧ��");
m_ctrTeaching.SetColumnWidth(2,80);
m_ctrTeaching.InsertColumn(3,"�γ���");
m_ctrTeaching.SetColumnWidth(3,80);
m_ctrTeaching.InsertColumn(4,"�γ�����");
m_ctrTeaching.SetColumnWidth(4,80);
m_ctrTeaching.InsertColumn(5,"�γ����");
m_ctrTeaching.SetColumnWidth(5,80);
m_ctrTeaching.InsertColumn(6,"�ڿΰ༶");
m_ctrTeaching.SetColumnWidth(6,80);
m_ctrTeaching.InsertColumn(7,"�ڿζ���");
m_ctrTeaching.SetColumnWidth(7,80);
m_ctrTeaching.InsertColumn(8,"ѧʱ");
m_ctrTeaching.SetColumnWidth(8,80);
m_ctrTeaching.InsertColumn(9,"�ص�");
m_ctrTeaching.SetColumnWidth(9,80);
m_ctrTeaching.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
m_bntSave.EnableWindow(FALSE);
m_bntAdd.EnableWindow(FALSE);
m_bntDelete.EnableWindow(FALSE);
m_bntUpdate.EnableWindow(FALSE);
// ��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CClassTeachingDlg::DataUpdate(CString strCode)
{
    // ��Ӵ���
m_ctrTeaching.DeleteAllItems();
m_ctrTeaching.SetRedraw(FALSE);
UpdateData(TRUE);
CString strSQL;
m_strCode.Format("%s",strCode);
// SQL����������ʽ�е�code�ǽ̹��Ĺ���
strSQL.Format( "select * from classTeaching where code = '%s'",strCode);
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
int i=0;
char buffer[20];
while(!m_recordset.IsEOF())
{ // ��Ӧ�б���ϵ����
_ltoa(m_recordset.m_number,buffer,10);
m_ctrTeaching.InsertItem(i,buffer);
// ��Ӧ�б���ϵ����
m_ctrTeaching.SetItemText(i,1,m_recordset.m_annual);
// ��Ӧ�б���ϵ�ѧ��
m_ctrTeaching.SetItemText(i,2,m_recordset.m_semester);
// ��Ӧ�б���ϵĿγ���
m_ctrTeaching.SetItemText(i,3,m_recordset.m_course);
// ��Ӧ�б���ϵĿγ�����
m_ctrTeaching.SetItemText(i,4,m_recordset.m_sort);
// ��Ӧ�б���ϵĿγ����
m_ctrTeaching.SetItemText(i,5,m_recordset.m_level);
// ��Ӧ�б���ϵ��ڿΰ༶
m_ctrTeaching.SetItemText(i,6,m_recordset.m_class);
// ��Ӧ�б���ϵ��ڿζ���
m_ctrTeaching.SetItemText(i,7,m_recordset.m_object);
// ��Ӧ�б���ϵ�ѧʱ
m_ctrTeaching.SetItemText(i,8,m_recordset.m_hour);
// ��Ӧ�б���ϵĵص�
m_ctrTeaching.SetItemText(i,9,m_recordset.m_location);
i++;
m_recordset.MoveNext();
}
m_recordset.Close();
m_ctrTeaching.SetRedraw(TRUE);
// �����Ƿ�����µĿ��ý�ѧ��¼��������뱣��������ť��״̬
m_bntSave.EnableWindow(FALSE);
if(m_strCode=="")
m_bntAdd.EnableWindow(FALSE);
else
m_bntAdd.EnableWindow();
m_bntDelete.EnableWindow(FALSE);
m_bntUpdate.EnableWindow(FALSE);
// ��Ӵ������
}
