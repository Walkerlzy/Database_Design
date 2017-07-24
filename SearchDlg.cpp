// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "SearchDlg.h"
//��Ӵ���
#include "NationInformationSet.h"
#include "PositionInformationSet.h"
#include "EducationDegreeSet.h"
#include "PoliticalStatusSet.h"
#include "DepartmentSectionSet.h"
#include "TechnicalPostSet.h"
#include "AdministrativePostSet.h"
//��Ӵ������ 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog


CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchDlg)
	m_strEducation = _T("");
	m_strMarriage = _T("");
	m_strNation = _T("");
	m_strPolitical = _T("");
	m_strPosition = _T("");
	m_strPost = _T("");
	m_strTechnical = _T("");
	m_strUnit = _T("");
	m_strSex = _T("");
	m_iAge = 0;
	m_strName = _T("");
	m_strNative = _T("");
	//}}AFX_DATA_INIT
}


void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchDlg)
	DDX_Control(pDX, IDC_LIST_SEARCH, m_ctrSearch);
	DDX_Control(pDX, IDC_COMBO_UNIT, m_ctrUnit);
	DDX_Control(pDX, IDC_COMBO_TECHNICAL, m_ctrTechnical);
	DDX_Control(pDX, IDC_COMBO_POST, m_ctrPost);
	DDX_Control(pDX, IDC_COMBO_POSITION, m_ctrPosition);
	DDX_Control(pDX, IDC_COMBO_POLITICAL, m_ctrPolitical);
	DDX_Control(pDX, IDC_COMBO_NATION, m_ctrNation);
	DDX_Control(pDX, IDC_COMBO_MARRIAGE, m_ctrMarriage);
	DDX_Control(pDX, IDC_COMBO_EDUCATION, m_ctrEducation);
	DDX_CBString(pDX, IDC_COMBO_EDUCATION, m_strEducation);
	DDX_CBString(pDX, IDC_COMBO_MARRIAGE, m_strMarriage);
	DDX_CBString(pDX, IDC_COMBO_NATION, m_strNation);
	DDX_CBString(pDX, IDC_COMBO_POLITICAL, m_strPolitical);
	DDX_CBString(pDX, IDC_COMBO_POSITION, m_strPosition);
	DDX_CBString(pDX, IDC_COMBO_POST, m_strPost);
	DDX_CBString(pDX, IDC_COMBO_TECHNICAL, m_strTechnical);
	DDX_CBString(pDX, IDC_COMBO_UNIT, m_strUnit);
	DDX_CBString(pDX, IDC_COMBO_SEX, m_strSex);
	DDX_Text(pDX, IDC_EDIT_AGE, m_iAge);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_NATIVE, m_strNative);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchDlg)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg message handlers

void CSearchDlg::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	UpdateData();
	CString strSQL;   //���������SQL��ѯִ�����
	CString strTemp;  //���ڶ�������������ѯ����ʱSQL������
	BOOL bNoCondition = TRUE;  //���ö�������������ѯ�Ŀ��ر���
	strSQL = "select * from staff where ";  //ע��where�����пո񣬷����������
	//���̹���������ѯ
	if(m_strName != "")
	{
		strTemp.Format("name = '%s'",m_strName);
		if(!bNoCondition)
		     strSQL += "and";
		     strSQL += strTemp;
		bNoCondition = FALSE;
	}
	//���̹����Ա��ѯ
	if(m_strSex != "")
	{
		strTemp.Format("sex = '%s'",m_strSex);
		if(!bNoCondition)
		     strSQL += "and";
		     strSQL += strTemp;
		bNoCondition = FALSE;
	}
	//���̹��������ѯ
	if(m_iAge > 0)
	{
		strTemp.Format("age = '%s'",m_iAge);
		if(!bNoCondition)
		     strSQL += "and";
		     strSQL += strTemp;
		bNoCondition = FALSE;
	}
	//���̹����ڵ�Ժϵ���Ų�ѯ
	if(m_strUnit != "")
	{
		strTemp.Format("department = '%s'",m_strUnit);
		if(!bNoCondition)
		     strSQL += "and";
		     strSQL += strTemp;
		bNoCondition = FALSE;
	}
	//���̹���ְ���ѯ
	if(m_strPost != "")
	{
		strTemp.Format("job = '%s'",m_strPost);
		if(!bNoCondition)
		     strSQL += "and";
		     strSQL += strTemp;
		bNoCondition = FALSE;
	}
	//���̹����Ļ��̶Ȳ�ѯ
	if(m_strEducation != "")
	{
		strTemp.Format("degree = '%s'",m_strEducation);
		if(!bNoCondition)
		     strSQL += "and";
		     strSQL += strTemp;
		bNoCondition = FALSE;
	}
	//���̹���������Ϣ��ѯ
	if(m_strNation != "")
	{
		strTemp.Format("race = '%s'",m_strNation);
		if(!bNoCondition)
		     strSQL += "and";
		     strSQL += strTemp;
		bNoCondition = FALSE;
	}
	//���̹��ĸ�λ��ѯ
	if(m_strPosition != "")
	{
		strTemp.Format("name = '%s'",m_strPosition);
		if(!bNoCondition)
		     strSQL += "and";
		     strSQL += strTemp;
		bNoCondition = FALSE;
	}
	//���̹��Ļ���״����ѯ
	if(m_strMarriage != "")
	{
		strTemp.Format("marriage = '%s'",m_strMarriage);
		if(!bNoCondition)
		     strSQL += "and";
		     strSQL += strTemp;
		bNoCondition = FALSE;
	}
	//���̹���������ò��ѯ
	if(m_strPolitical != "")
	{
		strTemp.Format("party = '%s'",m_strPolitical);
		if(!bNoCondition)
		     strSQL += "and";
		     strSQL += strTemp;
		bNoCondition = FALSE;
	}
	//���̹���ְ�Ʋ�ѯ
	if(m_strTechnical != "")
	{
		strTemp.Format("technical = '%s'",m_strTechnical);
		if(!bNoCondition)
		     strSQL += "and";
		     strSQL += strTemp;
		bNoCondition = FALSE;
	}
	//���̹��ļ����ѯ
	if(m_strNative != "")
	{
		strTemp.Format("native = '%s'",m_strNative);
		if(!bNoCondition)
		     strSQL += "and";
		     strSQL += strTemp;
		bNoCondition = FALSE;
	}
	if(bNoCondition)
	{
		strSQL = "select * from staff";
	}
	m_ctrSearch.DeleteAllItems();
	m_ctrSearch.SetRedraw(FALSE);
	if(! m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
         MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
         return ;
    }
	char buffer[20];
	int i = 0;
	while(!m_recordset.IsEOF())
	{
		m_ctrSearch.InsertItem(i,m_recordset.m_code);
		m_ctrSearch.SetItemText(i,1,m_recordset.m_name);
		m_ctrSearch.SetItemText(i,2,m_recordset.m_sex);
		_itoa(m_recordset.m_age,buffer,10);
		m_ctrSearch.SetItemText(i,3,buffer);
		m_ctrSearch.SetItemText(i,4,m_recordset.m_marriage);
		m_ctrSearch.SetItemText(i,5,m_recordset.m_job);
		m_ctrSearch.SetItemText(i,6,m_recordset.m_technical);
		m_ctrSearch.SetItemText(i,7,m_recordset.m_post);
		m_ctrSearch.SetItemText(i,8,m_recordset.m_race);
		m_ctrSearch.SetItemText(i,9,m_recordset.m_degree);
		m_ctrSearch.SetItemText(i,10,m_recordset.m_party);
		m_ctrSearch.SetItemText(i,11,m_recordset.m_identity_Card);
		i++;
		m_recordset.MoveNext();
	}
	m_recordset.Close();
	m_ctrSearch.SetRedraw(TRUE);
	//��Ӵ������
}

BOOL CSearchDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//��Ӵ���
	m_ctrSearch.InsertColumn(0,"����");
    m_ctrSearch.SetColumnWidth(0,60);
	m_ctrSearch.InsertColumn(1,"����");
    m_ctrSearch.SetColumnWidth(1,80);
	m_ctrSearch.InsertColumn(2,"�Ա�");
    m_ctrSearch.SetColumnWidth(2,60);
	m_ctrSearch.InsertColumn(3,"����");
    m_ctrSearch.SetColumnWidth(3,60);
	m_ctrSearch.InsertColumn(4,"����״��");
    m_ctrSearch.SetColumnWidth(4,60);
	m_ctrSearch.InsertColumn(5,"ְ��");
    m_ctrSearch.SetColumnWidth(5,80);
	m_ctrSearch.InsertColumn(6,"ְ��");
    m_ctrSearch.SetColumnWidth(6,80);
	m_ctrSearch.InsertColumn(7,"�̹���λ");
    m_ctrSearch.SetColumnWidth(7,90);
	m_ctrSearch.InsertColumn(8,"����");
    m_ctrSearch.SetColumnWidth(8,80);
	m_ctrSearch.InsertColumn(9,"ѧ��");
    m_ctrSearch.SetColumnWidth(9,90);
	m_ctrSearch.InsertColumn(10,"������ò");
    m_ctrSearch.SetColumnWidth(10,100);
	m_ctrSearch.InsertColumn(11,"���֤��");
    m_ctrSearch.SetColumnWidth(11,80);
	m_ctrSearch.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    CString strSQL;
	//Ժϵ����
	CDepartmentSectionSet DSS;
	strSQL = "select * from department";
	if(! DSS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
	     MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	} 
	while(! DSS.IsEOF())
	{
		 m_ctrUnit.AddString(DSS.m_division);
		 DSS.MoveNext();
	}
	DSS.Close();
	//����ְ��
	CAdministrativePostSet APS;
	strSQL = "select * from administrativePost";
	if(! APS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
	     MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	} 
	while(! APS.IsEOF())
	{
		 m_ctrPost.AddString(APS.m_rank);
		 APS.MoveNext();
	}
	APS.Close();
	//�̹�ְ��
	CTechnicalPostSet TPS;
	strSQL = "select * from technicalPost";
	if(! TPS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
	     MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	} 
	while(! TPS.IsEOF())
	{
		 m_ctrTechnical.AddString(TPS.m_title);
		 TPS.MoveNext();
	}
	TPS.Close();
	//�̹���λ
	CPositionInformationSet PIS;
	strSQL = "select * from positionInformation";
	if(! PIS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
	     MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	} 
	while(! PIS.IsEOF())
	{
		 m_ctrPosition.AddString(PIS.m_post);
		 PIS.MoveNext();
	}
	PIS.Close();
	//������Ϣ
	CNationInformationSet NIS;
	strSQL = "select * from nationInformation";
	if(! NIS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
	     MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	} 
	while(! NIS.IsEOF())
	{
		 m_ctrNation.AddString(NIS.m_folk);
		 NIS.MoveNext();
	}
	NIS.Close();
    //������ò
	CPoliticalStatusSet PSS;
	strSQL = "select * from politicalStatus";
	if(! PSS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
	     MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	} 
	while(! PSS.IsEOF())
	{
		 m_ctrPolitical.AddString(PSS.m_party);
		 PSS.MoveNext();
	}
	PSS.Close();
    //�Ļ��̶�
	CEducationDegreeSet EDS;
	strSQL = "select * from educationDegree";
	if(! EDS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
	     MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	} 
	while(! EDS.IsEOF())
	{
		 m_ctrEducation.AddString(EDS.m_degree);
		 EDS.MoveNext();
	}
	EDS.Close();
	//��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
