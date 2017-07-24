// FamilyMemberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "FamilyMemberDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFamilyMemberDlg dialog


CFamilyMemberDlg::CFamilyMemberDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFamilyMemberDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFamilyMemberDlg)
	m_tmBirth = 0;
	m_strPolitical = _T("");
	m_strCID = _T("");
	m_strName = _T("");
	m_strDuty = _T("");
	m_strEducation = _T("");
	m_strPhone = _T("");
	m_strRelation = _T("");
	m_strCompany = _T("");
	//}}AFX_DATA_INIT
	//��Ӵ���
	m_strCode = "";    //��ӦfamilyMember��Ĺ���code
	//��Ӵ������
}


void CFamilyMemberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFamilyMemberDlg)
	DDX_Control(pDX, IDC_LIST_FAMILY, m_ctrFamily);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_bntSave);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_bntUpdate);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_bntDelete);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_bntAdd);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BIRTH, m_tmBirth);
	DDX_CBString(pDX, IDC_COMBO_POLITICAL, m_strPolitical);
	DDX_Text(pDX, IDC_EDIT_CID, m_strCID);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_DUTY, m_strDuty);
	DDX_Text(pDX, IDC_EDIT_EDUCATION, m_strEducation);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
	DDX_Text(pDX, IDC_EDIT_RELATION, m_strRelation);
	DDX_Text(pDX, IDC_EDIT_COMPANY, m_strCompany);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFamilyMemberDlg, CDialog)
	//{{AFX_MSG_MAP(CFamilyMemberDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST_FAMILY, OnClickListFamily)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFamilyMemberDlg message handlers

void CFamilyMemberDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	m_strName      = "";
	m_strRelation  = "";
	m_strCompany   = ""; 
	m_strDuty      = "";
	m_strPolitical = "";
	m_strPhone     = "";
	m_tmBirth = CTime::GetCurrentTime();
	m_strEducation = ""; 
	m_strCID       = "";
	m_bntSave.EnableWindow();
	m_bntAdd.EnableWindow(FALSE);
	m_bntDelete.EnableWindow(FALSE);
	m_bntUpdate.EnableWindow(FALSE); 
	UpdateData(FALSE);
	//��Ӵ������
}

void CFamilyMemberDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
    //��Ӵ���
	int i = m_ctrFamily.GetSelectionMark();
	if(i < 0)
	{
		MessageBox("��ѡ��һ����¼����ɾ����");
		return; 
	}
	CString strSQL;
    strSQL.Format("select * from familyMember where number = %s",m_ctrFamily.GetItemText(i,0));
    if(! m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
	    MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	    return;
    }
	//ɾ���ü�¼
	m_recordset.Delete();
	m_recordset.Close();
	//�����û�����
	DataUpdate(m_strCode);
	m_strName = "";
	m_strRelation ="";
	m_strCompany = ""; 
	m_strDuty = "";
	m_strPolitical = "";
	m_strPhone = "";
	m_tmBirth = CTime::GetCurrentTime();
	m_strCID  = "";
	m_strEducation  = "";
	UpdateData(FALSE);
	//��Ӵ������	
}

void CFamilyMemberDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	int i = m_ctrFamily.GetSelectionMark();
	if(i < 0)
	{
		MessageBox("��ѡ��һ����¼�����޸ģ�");
		return; 
	}
	if(m_strName == "")
	{
		MessageBox("����������!");
		return; 
	}
	CString strSQL;
    strSQL.Format("select * from familyMember where number = %s",m_ctrFamily.GetItemText(i,0));
    if(! m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
	    MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	    return;
    }
    m_recordset.Edit(); 
	m_recordset.m_name          = m_strName;
	m_recordset.m_relation      = m_strRelation;
	m_recordset.m_birth         = m_tmBirth;
	m_recordset.m_company       = m_strCompany; 
	m_recordset.m_duty          = m_strDuty;
	m_recordset.m_political     = m_strPolitical;
	m_recordset.m_phone         = m_strPhone;
	m_recordset.m_identity_Card = m_strCID;
	m_recordset.m_education     = m_strEducation;
	m_recordset.Update();
	m_recordset.Close();
	DataUpdate(m_strCode);
	//��Ӵ������
}

void CFamilyMemberDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	if(m_strName == "")
	{
		MessageBox("����������!");
		return; 
	}
    if(! m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE))
    {
	    MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	    return;
    }
    m_recordset.AddNew(); 
	m_recordset.m_name          = m_strName;
	m_recordset.m_relation      = m_strRelation;
	m_recordset.m_birth         = m_tmBirth;
	m_recordset.m_company       = m_strCompany; 
	m_recordset.m_duty          = m_strDuty;
	m_recordset.m_political     = m_strPolitical;
	m_recordset.m_phone         = m_strPhone;
    m_recordset.m_code          = m_strCode;
	m_recordset.m_education     = m_strEducation;
	m_recordset.m_identity_Card = m_strCID;
	m_recordset.Update();
	m_recordset.Close();
	DataUpdate(m_strCode);
	//��Ӵ������
}

void CFamilyMemberDlg::OnClickListFamily(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	CString strSQL;
	UpdateData(TRUE);
	int i = m_ctrFamily.GetSelectionMark();
	//��familyMemberSet������number��Ȼ�ǳ����ͣ���where�Ӿ������ַ�������Ϊ%ld��
	//��Ȼ�������Ϳ���ƥ�䣬���޸��뱣�水ť������δѡ��ǰ��¼���쳣 
    strSQL.Format("select * from familyMember where number = %s",m_ctrFamily.GetItemText(i,0));
    if(! m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
	    MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	    return;
    } 
    m_strName      = m_recordset.m_name;
	m_strRelation  = m_recordset.m_relation;
	m_tmBirth      = m_recordset.m_birth;
	m_strCompany   = m_recordset.m_company; 
	m_strDuty      = m_recordset.m_duty;
	m_strPolitical = m_recordset.m_political;
	m_strPhone     = m_recordset.m_phone;
	m_strEducation = m_recordset.m_education;
	m_strCID       = m_recordset.m_identity_Card;
	m_recordset.Close();
	UpdateData(FALSE);
    m_bntSave.EnableWindow(FALSE);
	m_bntAdd.EnableWindow();
	m_bntDelete.EnableWindow();
	m_bntUpdate.EnableWindow();
	//��Ӵ������
	*pResult = 0;
}

BOOL CFamilyMemberDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//��Ӵ���
	//��ʼ����ͥ��Ա�Ի����е��б�ؼ���ͷ 
	m_ctrFamily.InsertColumn(0,"���");
    m_ctrFamily.SetColumnWidth(0,60);
    m_ctrFamily.InsertColumn(1,"����");
    m_ctrFamily.SetColumnWidth(1,80);
	m_ctrFamily.InsertColumn(2,"���֤��");
    m_ctrFamily.SetColumnWidth(2,80);
	m_ctrFamily.InsertColumn(3,"��̹���ϵ");
    m_ctrFamily.SetColumnWidth(3,80);
	m_ctrFamily.InsertColumn(4,"����");
    m_ctrFamily.SetColumnWidth(4,80);
	m_ctrFamily.InsertColumn(5,"������λ");
    m_ctrFamily.SetColumnWidth(5,80);
	m_ctrFamily.InsertColumn(6,"��ϵ�绰");
    m_ctrFamily.SetColumnWidth(6,80);
	m_ctrFamily.InsertColumn(7,"ְ��");
    m_ctrFamily.SetColumnWidth(7,80);
    m_ctrFamily.InsertColumn(8,"������ò");
    m_ctrFamily.SetColumnWidth(8,80);
    m_ctrFamily.InsertColumn(9,"�Ļ��̶�");
    m_ctrFamily.SetColumnWidth(9,80);
	m_ctrFamily.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 
	m_bntSave.EnableWindow(FALSE);
	m_bntAdd.EnableWindow(FALSE);
	m_bntDelete.EnableWindow(FALSE);
	m_bntUpdate.EnableWindow(FALSE);
	//��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFamilyMemberDlg::DataUpdate(CString strCode)
{
    //��Ӵ���
	m_ctrFamily.DeleteAllItems();
	m_ctrFamily.SetRedraw(FALSE);
	UpdateData(TRUE);
	CString strSQL;
	m_strCode.Format("%s",strCode);
	//SQL����������ʽ�е�code�ǽ̹��Ĺ��� 
	strSQL.Format("select * from familyMember where code = %s",strCode);
    if(! m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
	    MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	    return;
    }
	int i = 0;
	CString strTime;
	char buffer[20];
	while(! m_recordset.IsEOF())
	{
		//��Ӧ�б���ϵ����
		_ltoa(m_recordset.m_number,buffer,10);
		m_ctrFamily.InsertItem(i,buffer);
		//��Ӧ�б���ϵ�����
		m_ctrFamily.SetItemText(i,1,m_recordset.m_name);
		//��Ӧ�б���ϵ����֤�� 
		m_ctrFamily.SetItemText(i,2,m_recordset.m_identity_Card);
		//��Ӧ�б���ϵĽ̹���ϵ 
		m_ctrFamily.SetItemText(i,3,m_recordset.m_relation);
		//��Ӧ�б���ϵ�����
		strTime.Format("%d - %d - %d",m_recordset.m_birth.GetYear(),m_recordset.m_birth.GetMonth(),m_recordset.m_birth.GetDay());
		m_ctrFamily.SetItemText(i,4,strTime);   
		//��Ӧ�б���ϵĹ�����λ
		m_ctrFamily.SetItemText(i,5,m_recordset.m_company);
		//��Ӧ�б���ϵ���ϵ�绰
		m_ctrFamily.SetItemText(i,6,m_recordset.m_phone); 
		//��Ӧ�б���ϵ�ְ��
		m_ctrFamily.SetItemText(i,7,m_recordset.m_duty);
		//��Ӧ�б���ϵ�������ò
		m_ctrFamily.SetItemText(i,8,m_recordset.m_political);
		//��Ӧ�б���ϵ��Ļ��̶�
		m_ctrFamily.SetItemText(i,9,m_recordset.m_education);
		i++;
		m_recordset.MoveNext();     
	 } 
	 m_recordset.Close();
	 m_ctrFamily.SetRedraw(TRUE);
	 //�����Ƿ�����µļ�ͥ��Ա��������뱣��������ť��״̬
	 m_bntSave.EnableWindow(FALSE);
	 if(m_strCode == "")
	 m_bntAdd.EnableWindow(FALSE);
	 else
	     m_bntAdd.EnableWindow();
		 m_bntDelete.EnableWindow(FALSE);
		 m_bntUpdate.EnableWindow(FALSE);
    //��Ӵ������
}
