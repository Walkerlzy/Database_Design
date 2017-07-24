// BaseArchiveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "BaseArchiveDlg.h"
//��Ӵ���       
#include "DepartmentSectionSet.h"
#include "AdministrativePostSet.h"
#include "EducationDegreeSet.h"
#include "TechnicalPostSet.h"
#include "PositionInformationSet.h"
#include "WageLevelSet.h"
#include "NationInformationSet.h"
#include "PoliticalStatusSet.h"
//��Ӵ������
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseArchiveDlg dialog


CBaseArchiveDlg::CBaseArchiveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseArchiveDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBaseArchiveDlg)
	m_strCode = _T("");
	m_strName = _T("");
	m_strSex = _T("");
	m_tmBirth = 0;
	m_strMarriage = _T("");
	m_strAge = _T("");
	m_strParty = _T("");
	m_strRace = _T("");
	m_strCID = _T("");
	m_tmWorkDate = 0;
	m_strPost = _T("");
	m_strNative = _T("");
	m_tmEntryDate = 0;
	m_strSalary = _T("");
	m_strDegree = _T("");
	m_strDept = _T("");
	m_strTechnical = _T("");
	m_strJob = _T("");
	m_strOfficePhone = _T("");
	m_strMobilePhone = _T("");
	m_strEmail = _T("");
	m_strUniversity = _T("");
	m_strSubject = _T("");
	m_tmGraduate = 0;
	m_strAddress = _T("");
	//��Ӵ���
	m_recordset = NULL;
	//��Ӵ������
	//}}AFX_DATA_INIT
}


void CBaseArchiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBaseArchiveDlg)
	DDX_Control(pDX, IDC_COMBO_JOB, m_ctrJob);
	DDX_Control(pDX, IDC_COMBO_TECHNICAL, m_ctrTechnical);
	DDX_Control(pDX, IDC_COMBO_DEPTMENT, m_ctrDept);
	DDX_Control(pDX, IDC_COMBO_DEGREE, m_ctrDegree);
	DDX_Control(pDX, IDC_COMBO_SALARY, m_ctrSalary);
	DDX_Control(pDX, IDC_COMBO_POST, m_ctrPost);
	DDX_Control(pDX, IDC_COMBO_RACE, m_ctrRace);
	DDX_Control(pDX, IDC_COMBO_PARTY, m_ctrParty);
	DDX_Control(pDX, IDC_EDIT_CODE, m_ctrCode);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strCode);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_CBString(pDX, IDC_COMBO_SEX, m_strSex);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BIRTH, m_tmBirth);
	DDX_CBString(pDX, IDC_COMBO_MARRYIAGE, m_strMarriage);
	DDX_Text(pDX, IDC_EDIT_AGE, m_strAge);
	DDX_CBString(pDX, IDC_COMBO_PARTY, m_strParty);
	DDX_CBString(pDX, IDC_COMBO_RACE, m_strRace);
	DDX_Text(pDX, IDC_EDIT_CID, m_strCID);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_WORK, m_tmWorkDate);
	DDX_CBString(pDX, IDC_COMBO_POST, m_strPost);
	DDX_Text(pDX, IDC_EDIT_NATIVE, m_strNative);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENTRY, m_tmEntryDate);
	DDX_CBString(pDX, IDC_COMBO_SALARY, m_strSalary);
	DDX_CBString(pDX, IDC_COMBO_DEGREE, m_strDegree);
	DDX_CBString(pDX, IDC_COMBO_DEPTMENT, m_strDept);
	DDX_CBString(pDX, IDC_COMBO_TECHNICAL, m_strTechnical);
	DDX_CBString(pDX, IDC_COMBO_JOB, m_strJob);
	DDX_Text(pDX, IDC_EDIT_OPHONE, m_strOfficePhone);
	DDX_Text(pDX, IDC_EDIT_MPHONE, m_strMobilePhone);
	DDX_Text(pDX, IDC_EDIT_EMAIL, m_strEmail);
	DDX_Text(pDX, IDC_EDIT_UNIVERSITY, m_strUniversity);
	DDX_Text(pDX, IDC_EDIT_SUBJECT, m_strSubject);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_GRADUAGE, m_tmGraduate);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBaseArchiveDlg, CDialog)
	//{{AFX_MSG_MAP(CBaseArchiveDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseArchiveDlg message handlers

BOOL CBaseArchiveDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//��Ӵ���
	CString strSQL;
	//Ժϵ����
	CDepartmentSectionSet DSS;
	strSQL = "select * from departmentSection";
	if(! DSS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
	    MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	} 
	while(! DSS.IsEOF())
	{
		m_ctrDept.AddString(DSS.m_division);
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
		m_ctrJob.AddString(APS.m_rank);
		APS.MoveNext();
	}
	APS.Close();
	//ְ�����
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
		m_ctrPost.AddString(PIS.m_post);
		PIS.MoveNext();
	}
	PIS.Close();
	//���ʵȼ�
	CWageLevelSet WLS;
	strSQL = "select * from wageLevel";
	if(! WLS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
	    MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	} 
	while(! WLS.IsEOF())
	{
		m_ctrSalary.AddString(WLS.m_salary);
		WLS.MoveNext();
	}
	WLS.Close();
	//������Ϣ
	CNationInformationSet NIS;
	strSQL = "select * from nationInformation";
	if(! NIS.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
	{
	    MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	} 
	while(! NIS.IsEOF())
	{
		m_ctrRace.AddString(NIS.m_folk);
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
		m_ctrParty.AddString(PSS.m_party);
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
		m_ctrDegree.AddString(EDS.m_degree);
		EDS.MoveNext();
	}
	EDS.Close();
	//��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBaseArchiveDlg::Purge()
{
	//��Ӵ���
	m_strCode = "";
	m_strName = "";
	m_strSex = "";
	m_tmBirth = 0;
	m_strMarriage = "";
	m_strAge = "";
	m_strParty = "";
	m_strRace = "";
	m_strCID = "";
	m_tmWorkDate = 0;
	m_strPost = "";
	m_strNative = "";
	m_tmEntryDate = 0;
	m_strSalary = "";
	m_strDegree = "";
	m_strDept = "";
	m_strTechnical = "";
	m_strJob = "";
	m_strOfficePhone = "";
	m_strMobilePhone = "";
	m_strEmail = "";
	m_strUniversity = "";
	m_strSubject = "";
	m_tmGraduate = 0;
	m_strAddress = "";
	UpdateData(FALSE);
	//��Ӵ������
}

BOOL CBaseArchiveDlg::Update()
{
	//��Ӵ���
	UpdateData();
    if(m_strCode == "")
	{
		MessageBox("�̹���Ų���Ϊ�գ�������̹���ţ�");
		return FALSE;
	}
	if(m_strName == "")
	{
		MessageBox("��������Ϊ�գ�������������");
		return FALSE;
	}
	CString strSQL;
    strSQL.Format("select * from staff where code ='%s'", m_strCode);
    if(!m_recordset ->Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
        MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return FALSE;
    }
	if(m_recordset ->GetRecordCount() == 0)
	{
		MessageBox("�ý̹������ڣ�");
		m_recordset ->Close();
		return FALSE;
	}
	m_recordset ->Edit();
	//�̹���Ų��䣬�����޸�
	m_recordset ->m_address        = m_strAddress;     //��ͥסַ
	m_recordset ->m_age            = atoi(m_strAge);   //����
	m_recordset ->m_identity_Card  = m_strCID;         //���֤��
	m_recordset ->m_degree         = m_strDegree;      //�Ļ��̶�
	m_recordset ->m_department     = m_strDept;        //Ժϵ����
	m_recordset ->m_email          = m_strEmail;       //��������
	m_recordset ->m_job            = m_strJob;         //ְ��
	m_recordset ->m_marriage       = m_strMarriage;    //����״��
	m_recordset ->m_mobile_Phone   = m_strMobilePhone; //�ֻ�
	m_recordset ->m_name           = m_strName;        //����
	m_recordset ->m_native         = m_strNative;      //����
	m_recordset ->m_office_Phone   = m_strOfficePhone; //�칫�绰
	m_recordset ->m_party          = m_strParty;       //������ò
	m_recordset ->m_post           = m_strPost;        //�̹���λ
	m_recordset ->m_race           = m_strRace;        //����
	m_recordset ->m_salary         = m_strSalary;      //���ʵȼ�
	m_recordset ->m_sex            = m_strSex;         //�Ա�
	m_recordset ->m_subject        = m_strSubject;     //��ѧרҵ
	m_recordset ->m_technical      = m_strTechnical;   //ְ��
	m_recordset ->m_university     = m_strUniversity;  //��ҵѧУ
	m_recordset ->m_birth          = m_tmBirth;        //����
	m_recordset ->m_word_Date      = m_tmWorkDate;     //�μӹ���ʱ��
	m_recordset ->m_enty_Date      = m_tmEntryDate;    //��ְʱ��
	m_recordset ->m_graduate_Date  = m_tmGraduate;     //��ҵʱ��
	m_recordset ->Update();
	m_recordset ->Close();
	return TRUE;
	//��Ӵ������
}

void CBaseArchiveDlg::DataUpdate()
{
    //��Ӵ���
	CString strSQL;
    strSQL.Format("select * from staff where code = '%s'",m_strCode);
    if(! m_recordset ->Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
	    MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	    return;
    }
	//����һ��20���ַ����Ļ���洢����age
char buffer[20];
    //������age������ת��Ϊ�ַ���
	_itoa(m_recordset ->m_age,buffer,10);
    m_strAge  = buffer;
	m_strAddress       = m_recordset ->m_address;           //��ͥסַ
	m_strCID           = m_recordset ->m_identity_Card  ;    //���֤��
	m_strDegree        = m_recordset ->m_degree;             //�Ļ��̶�
	m_strDept          = m_recordset ->m_department;         //Ժϵ����
	m_strEmail         = m_recordset ->m_email;              //��������
	m_strJob           = m_recordset ->m_job;                //ְ��
	m_strMarriage      = m_recordset ->m_marriage;           //����״��
	m_strMobilePhone   = m_recordset ->m_mobile_Phone;       //�ֻ�
	m_strName          = m_recordset ->m_name;               //����
	m_strNative        = m_recordset ->m_native;             //����
	m_strOfficePhone   = m_recordset ->m_office_Phone;       //�칫�绰
	m_strParty         = m_recordset ->m_party;              //������ò
	m_strPost          = m_recordset ->m_post;               //�̹���λ
	m_strRace          = m_recordset ->m_race;               //����
	m_strSalary        = m_recordset ->m_salary;             //���ʵȼ�
	m_strSex           = m_recordset ->m_sex;                //�Ա�
	m_strSubject       = m_recordset ->m_subject;            //��ѧרҵ
	m_strTechnical     = m_recordset ->m_technical;          //ְ��
	m_strUniversity    = m_recordset ->m_university;         //��ҵѧУ
	m_tmBirth          = m_recordset ->m_birth;              //����
	m_tmWorkDate       = m_recordset ->m_word_Date;          //�μӹ���ʱ��
	m_tmEntryDate      = m_recordset ->m_enty_Date;          //��ְʱ��
	m_tmGraduate       = m_recordset ->m_graduate_Date;      //��ҵʱ��
	m_recordset ->Close();
	UpdateData(FALSE); 
	//��Ӵ������
}

BOOL CBaseArchiveDlg::Save()
{
    //��Ӵ��� 
	UpdateData();
	if(m_strCode == "")
	{
		MessageBox("�̹���Ų���Ϊ�գ�������̹���ţ�");
		return FALSE; 
	}
	if(m_strName == "")
	{
		MessageBox("��������Ϊ�գ�����������!");
		return FALSE; 
	}
	CString strSQL;
    strSQL.Format("select * from staff where code = '%s'",m_strCode);
    if(! m_recordset ->Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
    {
	    MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
	    return FALSE;
    }
	if(m_recordset ->GetRecordCount() != 0)
	{
		MessageBox("�ý̹��Ѿ����ڣ�");
		m_recordset ->Close();
		return FALSE; 
	}
	m_recordset ->AddNew();
	m_recordset ->m_code           = m_strCode;        //�̹����
	m_recordset ->m_address        = m_strAddress;     //��ͥסַ
	m_recordset ->m_age            = atoi(m_strAge);   //����
	m_recordset ->m_identity_Card  = m_strCID;         //���֤��
	m_recordset ->m_degree         = m_strDegree;      //�Ļ��̶�
	m_recordset ->m_department     = m_strDept;        //Ժϵ����
	m_recordset ->m_email          = m_strEmail;       //��������
	m_recordset ->m_job            = m_strJob;         //ְ��
	m_recordset ->m_marriage       = m_strMarriage;    //����״��
	m_recordset ->m_mobile_Phone   = m_strMobilePhone; //�ֻ�
	m_recordset ->m_name           = m_strName;        //����
	m_recordset ->m_native         = m_strNative;      //����
	m_recordset ->m_office_Phone   = m_strOfficePhone; //�칫�绰
	m_recordset ->m_party          = m_strParty;       //������ò
	m_recordset ->m_post           = m_strPost;        //�̹���λ
	m_recordset ->m_race           = m_strRace;        //����
	m_recordset ->m_salary         = m_strSalary;      //���ʵȼ�
	m_recordset ->m_sex            = m_strSex;         //�Ա�
	m_recordset ->m_subject        = m_strSubject;     //��ѧרҵ
	m_recordset ->m_technical      = m_strTechnical;   //ְ��
	m_recordset ->m_university     = m_strUniversity;  //��ҵѧУ
	m_recordset ->m_birth          = m_tmBirth;        //����
	m_recordset ->m_word_Date      = m_tmWorkDate;     //�μӹ���ʱ��
	m_recordset ->m_enty_Date      = m_tmEntryDate;    //��ְʱ��
	m_recordset ->m_graduate_Date  = m_tmGraduate;     //��ҵʱ��
	m_recordset ->Update();
	m_recordset ->Close();
	return true;
	//��Ӵ������
}
