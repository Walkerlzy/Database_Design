// ContinueEducationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "ContinueEducationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContinueEducationDlg dialog


CContinueEducationDlg::CContinueEducationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CContinueEducationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CContinueEducationDlg)
	m_tmBDate = 0;
	m_tmEDate = 0;
	m_strMode = _T("");
	m_strEffect = _T("");
	m_strContent = _T("");
	m_strUnit = _T("");
	m_strLocation = _T("");
	m_strCost = _T("");
	m_strHour = _T("");
	// ��Ӵ���
    m_strCode = "";
    // ��Ӵ������
	//}}AFX_DATA_INIT
}


void CContinueEducationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CContinueEducationDlg)
	DDX_Control(pDX, IDC_LIST_CONTINUEEDUCATION, m_ctrCEducation);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_bntSave);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_bntUpdate);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_bntDelete);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_bntAdd);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BDATE, m_tmBDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_EDATE, m_tmEDate);
	DDX_CBString(pDX, IDC_COMBO_MODE, m_strMode);
	DDX_CBString(pDX, IDC_COMBO_EFFECT, m_strEffect);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_strContent);
	DDX_Text(pDX, IDC_EDIT_UNIT, m_strUnit);
	DDX_Text(pDX, IDC_EDIT_LOCATION, m_strLocation);
	DDX_Text(pDX, IDC_EDIT_COST, m_strCost);
	DDX_Text(pDX, IDC_EDIT_HOUR, m_strHour);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CContinueEducationDlg, CDialog)
	//{{AFX_MSG_MAP(CContinueEducationDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CONTINUEEDUCATION, OnClickListContinueeducation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContinueEducationDlg message handlers

void CContinueEducationDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
m_strContent   = "";
m_strCost      = "";
m_strEffect    = "";
m_strHour      = "";
m_strUnit      = "";
m_strLocation  = "";
m_strMode      = "";
m_tmBDate  = CTime::GetCurrentTime();
m_tmEDate  = CTime::GetCurrentTime();
m_bntSave.EnableWindow();
m_bntAdd.EnableWindow(FALSE);
m_bntDelete.EnableWindow(FALSE);
m_bntUpdate.EnableWindow(FALSE);
UpdateData(FALSE);
// ��Ӵ������
}

void CContinueEducationDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
int i = m_ctrCEducation.GetSelectionMark();
if(i<0)
{
MessageBox("��ѡ��һ����¼����ɾ����");
return;
}
CString strSQL;
strSQL.Format("select * from continueEducation where number = %s",m_ctrCEducation.GetItemText(i,0));
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
m_strContent    = "";
m_strCost       = "";
m_strEffect     = "";
m_strHour       = "";
m_strUnit       = "";
m_strLocation   = "";
m_strMode       = "";
m_tmBDate  = CTime::GetCurrentTime();
m_tmEDate       = CTime::GetCurrentTime();
UpdateData(FALSE);
// ��Ӵ������
}

void CContinueEducationDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
UpdateData();
int i = m_ctrCEducation.GetSelectionMark();
if(i<0)
{
MessageBox("��ѡ��һ����¼�����޸ģ�");
return;
}
CString strSQL;
strSQL.Format("select * from continueEducation where number = %s",m_ctrCEducation.GetItemText(i,0));
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
m_recordset.Edit();
m_recordset.m_begin        = m_tmBDate;
m_recordset.m_end          = m_tmEDate;
m_recordset.m_content      = m_strContent;
m_recordset.m_cost         = m_strCost;
m_recordset.m_effect       = m_strEffect;
m_recordset.m_hour         = m_strHour;
m_recordset.m_unit         = m_strUnit;
m_recordset.m_location     = m_strLocation;
m_recordset.m_mode         = m_strMode;
m_recordset.Update();
m_recordset.Close();
DataUpdate(m_strCode);
// ��Ӵ������
}

void CContinueEducationDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
UpdateData();
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
if(m_strContent=="")
{
MessageBox("���ݲ���Ϊ�գ�����������������ƣ�");
return;
}
if(m_strEffect=="")
{
MessageBox("����Ч������Ϊ�գ����������Ч�����ƣ�");
return;
}
m_recordset.AddNew();
m_recordset.m_content   = m_strContent;
m_recordset.m_cost      = m_strCost;
m_recordset.m_begin     = m_tmBDate;
m_recordset.m_end       = m_tmEDate;
m_recordset.m_effect    = m_strEffect;
m_recordset.m_location  = m_strLocation;
m_recordset.m_unit      = m_strUnit;
m_recordset.m_mode      = m_strMode;
m_recordset.m_hour      = m_strHour;
// �̹����codeҲҪ�������̨���ݿ�PostDB.accdb��
m_recordset.m_code      = m_strCode;
m_recordset.Update();
m_recordset.Close();
DataUpdate(m_strCode);
// ��Ӵ������
}

void CContinueEducationDlg::OnClickListContinueeducation(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
CString strSQL;
UpdateData(TRUE);
int i = m_ctrCEducation.GetSelectionMark();
strSQL.Format("select * from continueEducation where \
	number =%s",m_ctrCEducation.GetItemText(i,0));
if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
{
MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
return ;
}
m_strContent    = m_recordset.m_content;
m_strCost       = m_recordset.m_cost;
m_tmBDate       = m_recordset.m_begin;
m_tmEDate       = m_recordset.m_end;
m_strEffect     = m_recordset.m_effect;
m_strHour       = m_recordset.m_hour;
m_strUnit       = m_recordset.m_unit;
m_strLocation   = m_recordset.m_location;
m_strMode       = m_recordset.m_mode;
m_recordset.Close();
UpdateData(FALSE);
m_bntSave.EnableWindow(FALSE);
m_bntAdd.EnableWindow();
m_bntDelete.EnableWindow();
m_bntUpdate.EnableWindow();
// ��Ӵ������
	*pResult = 0;
}

BOOL CContinueEducationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// ��Ӵ���
// ��ʼ�����������Ի����е��б�ؼ���ͷ
m_ctrCEducation.InsertColumn(0,"���");
m_ctrCEducation.SetColumnWidth(0,60);
m_ctrCEducation.InsertColumn(1,"������ʽ");
m_ctrCEducation.SetColumnWidth(1,80);
m_ctrCEducation.InsertColumn(2,"��ʼʱ��");
m_ctrCEducation.SetColumnWidth(2,80);
m_ctrCEducation.InsertColumn(3,"����ʱ��");
m_ctrCEducation.SetColumnWidth(3,80);
m_ctrCEducation.InsertColumn(4,"����Ч��");
m_ctrCEducation.SetColumnWidth(4,80);
m_ctrCEducation.InsertColumn(5,"��������");
m_ctrCEducation.SetColumnWidth(5,80);
m_ctrCEducation.InsertColumn(6,"��ѵ��λ");
m_ctrCEducation.SetColumnWidth(6,80);
m_ctrCEducation.InsertColumn(7,"��ѵ�ص�");
m_ctrCEducation.SetColumnWidth(7,80);
m_ctrCEducation.InsertColumn(8,"��ѵ����");
m_ctrCEducation.SetColumnWidth(8,80);
m_ctrCEducation.InsertColumn(9,"��ѵѧʱ");
m_ctrCEducation.SetColumnWidth(9,80);
m_ctrCEducation.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
m_bntSave.EnableWindow(FALSE);
m_bntAdd.EnableWindow(FALSE);
m_bntDelete.EnableWindow(FALSE);
m_bntUpdate.EnableWindow(FALSE);
// ��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CContinueEducationDlg::DataUpdate(CString strCode)
{
    // ��Ӵ���
m_ctrCEducation.DeleteAllItems();
m_ctrCEducation.SetRedraw(FALSE);
UpdateData(TRUE);
CString strSQL;
m_strCode.Format("%s",strCode);
// SQL����������ʽ�е�code�ǽ̹��Ĺ���
strSQL.Format( "select * from continueEducation where code = '%s'",strCode);
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
m_ctrCEducation.InsertItem(i,buffer);
// ��Ӧ�б���ϵĽ�����ʽ
m_ctrCEducation.SetItemText(i,1,m_recordset.m_mode);
// ��Ӧ�б���ϵĿ�ʼʱ��
strBTime.Format("%d-%d-%d",m_recordset.m_begin.GetYear(),m_recordset.m_begin.\
	GetMonth(),m_recordset.m_begin.GetDay());
m_ctrCEducation.SetItemText(i,2,strBTime);
// ��Ӧ�б���ϵĽ���ʱ��
strETime.Format("%d-%d-%d",m_recordset.m_end.GetYear(),m_recordset.m_end.\
	GetMonth(),m_recordset.m_end.GetDay());
m_ctrCEducation.SetItemText(i,3,strETime);
// ��Ӧ�б���ϵĽ���Ч��
m_ctrCEducation.SetItemText(i,4,m_recordset.m_effect);
// ��Ӧ�б���ϵĽ�������
m_ctrCEducation.SetItemText(i,5,m_recordset.m_content);
// ��Ӧ�б���ϵ���ѵ��λ
m_ctrCEducation.SetItemText(i,6,m_recordset.m_unit);
// ��Ӧ�б���ϵ���ѵ�ص�
m_ctrCEducation.SetItemText(i,7,m_recordset.m_location);
// ��Ӧ�б���ϵ���ѵ����
m_ctrCEducation.SetItemText(i,8,m_recordset.m_cost);
// ��Ӧ�б���ϵ���ѵѧʱ
m_ctrCEducation.SetItemText(i,9,m_recordset.m_hour);
i++;
m_recordset.MoveNext();
}
m_recordset.Close();
m_ctrCEducation.SetRedraw(TRUE);
// �����Ƿ�����µļ���������¼��������뱣��������ť��״̬
m_bntSave.EnableWindow(FALSE);
if(m_strCode=="")
m_bntAdd.EnableWindow(FALSE);
else
m_bntAdd.EnableWindow();
m_bntDelete.EnableWindow(FALSE);
m_bntUpdate.EnableWindow(FALSE);
// ��Ӵ������
}
