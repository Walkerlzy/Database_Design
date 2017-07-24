// StatisticsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "StatisticsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatisticsDlg dialog


CStatisticsDlg::CStatisticsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatisticsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatisticsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStatisticsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatisticsDlg)
	DDX_Control(pDX, IDC_RESULT, m_ctrResult);
	DDX_Control(pDX, IDC_SELECTION, m_ctrSelection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatisticsDlg, CDialog)
	//{{AFX_MSG_MAP(CStatisticsDlg)
	ON_NOTIFY(NM_CLICK, IDC_SELECTION, OnClickSelection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatisticsDlg message handlers

void CStatisticsDlg::OnClickSelection(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//��Ӵ���
	CString strSQL;               //����SQL���
	CString strAttribute = "0";   //�洢����ֵ
	CDatabase db;
	db.Open(_T("PostDB"));
	CRecordset m_recordset(&db);
	UpdateData(TRUE);
	int iSort = m_ctrSelection.GetSelectionMark();
	int i = 0;
	switch(iSort)
	{
	//���Ա�ͳ��
	case 0:
		m_ctrResult.DeleteAllItems();
		m_ctrResult.DeleteColumn(1);
		m_ctrResult.DeleteColumn(0);
		m_ctrResult.InsertColumn(0,"�Ա�");
		m_ctrResult.InsertColumn(1,"����");
		m_ctrResult.SetColumnWidth(0,80);
		m_ctrResult.SetColumnWidth(1,100);
		strSQL = "select count(code) as amount ,sex from staff group by sex";
		if(!m_recordset.Open(CRecordset::forwardOnly,strSQL))
		{
			MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		}
		while(!m_recordset.IsEOF())
		{
			m_recordset.GetFieldValue("sex",strAttribute);
			m_ctrResult.InsertItem(i,strAttribute);
			m_recordset.GetFieldValue("amount",strAttribute);
			m_ctrResult.SetItemText(i,1,strAttribute);
			i++;
			m_recordset.MoveNext();
		}
		m_recordset.Close();
		break;
	//������ͳ��
	case 1:
		m_ctrResult.DeleteAllItems();
		m_ctrResult.DeleteColumn(1);
		m_ctrResult.DeleteColumn(0);
		m_ctrResult.InsertColumn(0,"����");
		m_ctrResult.InsertColumn(1,"����");
		m_ctrResult.SetColumnWidth(0,80);
		m_ctrResult.SetColumnWidth(1,100);
		strSQL = "select count(code) as amount ,age from staff group by age";
		if(!m_recordset.Open(CRecordset::forwardOnly,strSQL))
		{
			MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		}
		while(!m_recordset.IsEOF())
		{
			m_recordset.GetFieldValue("age",strAttribute);
			m_ctrResult.InsertItem(i,strAttribute);
			m_recordset.GetFieldValue("amount",strAttribute);
			m_ctrResult.SetItemText(i,1,strAttribute);
			i++;
			m_recordset.MoveNext();
		}
		m_recordset.Close();
		break;
	//������ͳ��
	case 2:
		m_ctrResult.DeleteAllItems();
		m_ctrResult.DeleteColumn(1);
		m_ctrResult.DeleteColumn(0);
		m_ctrResult.InsertColumn(0,"����");
		m_ctrResult.InsertColumn(1,"����");
		m_ctrResult.SetColumnWidth(0,80);
		m_ctrResult.SetColumnWidth(1,100);
		strSQL = "select count(code) as amount ,race from staff group by race";
		if(!m_recordset.Open(CRecordset::forwardOnly,strSQL))
		{
			MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		}
		while(!m_recordset.IsEOF())
		{
			m_recordset.GetFieldValue("race",strAttribute);
			m_ctrResult.InsertItem(i,strAttribute);
			m_recordset.GetFieldValue("amount",strAttribute);
			m_ctrResult.SetItemText(i,1,strAttribute);
			i++;
			m_recordset.MoveNext();
		}
		m_recordset.Close();
		break;
	//������ͳ��
	case 3:
		m_ctrResult.DeleteAllItems();
		m_ctrResult.DeleteColumn(1);
		m_ctrResult.DeleteColumn(0);
		m_ctrResult.InsertColumn(0,"����");
		m_ctrResult.InsertColumn(1,"����");
		m_ctrResult.SetColumnWidth(0,80);
		m_ctrResult.SetColumnWidth(1,100);
		strSQL = "select count(code) as amount ,native from staff group by native";
		if(!m_recordset.Open(CRecordset::forwardOnly,strSQL))
		{
			MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		}
		while(!m_recordset.IsEOF())
		{
			m_recordset.GetFieldValue("native",strAttribute);
			m_ctrResult.InsertItem(i,strAttribute);
			m_recordset.GetFieldValue("amount",strAttribute);
			m_ctrResult.SetItemText(i,1,strAttribute);
			i++;
			m_recordset.MoveNext();
		}
		m_recordset.Close();
		break;
	//��ְ�����ͳ��
	case 4:
		m_ctrResult.DeleteAllItems();
		m_ctrResult.DeleteColumn(1);
		m_ctrResult.DeleteColumn(0);
		m_ctrResult.InsertColumn(0,"ְ��");
		m_ctrResult.InsertColumn(1,"����");
		m_ctrResult.SetColumnWidth(0,80);
		m_ctrResult.SetColumnWidth(1,100);
		strSQL = "select count(code) as amount ,job from staff group by job";
		if(!m_recordset.Open(CRecordset::forwardOnly,strSQL))
		{
			MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		}
		while(!m_recordset.IsEOF())
		{
			m_recordset.GetFieldValue("job",strAttribute);
			m_ctrResult.InsertItem(i,strAttribute);
			m_recordset.GetFieldValue("amount",strAttribute);
			m_ctrResult.SetItemText(i,1,strAttribute);
			i++;
			m_recordset.MoveNext();
		}
		m_recordset.Close();
		break;
	//��ְ�����ͳ��
	case 5:
		m_ctrResult.DeleteAllItems();
		m_ctrResult.DeleteColumn(1);
		m_ctrResult.DeleteColumn(0);
		m_ctrResult.InsertColumn(0,"ְ��");
		m_ctrResult.InsertColumn(1,"����");
		m_ctrResult.SetColumnWidth(0,80);
		m_ctrResult.SetColumnWidth(1,100);
		strSQL = "select count(code) as amount ,technical from staff group by technical";
		if(!m_recordset.Open(CRecordset::forwardOnly,strSQL))
		{
			MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		}
		while(!m_recordset.IsEOF())
		{
			m_recordset.GetFieldValue("technical",strAttribute);
			m_ctrResult.InsertItem(i,strAttribute);
			m_recordset.GetFieldValue("amount",strAttribute);
			m_ctrResult.SetItemText(i,1,strAttribute);
			i++;
			m_recordset.MoveNext();
		}
		m_recordset.Close();
		break;
	//��ѧ��ͳ��
	case 6:
		m_ctrResult.DeleteAllItems();
		m_ctrResult.DeleteColumn(1);
		m_ctrResult.DeleteColumn(0);
		m_ctrResult.InsertColumn(0,"ѧ��");
		m_ctrResult.InsertColumn(1,"����");
		m_ctrResult.SetColumnWidth(0,80);
		m_ctrResult.SetColumnWidth(1,100);
		strSQL = "select count(code) as amount ,degree from staff group by degree";
		if(!m_recordset.Open(CRecordset::forwardOnly,strSQL))
		{
			MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		}
		while(!m_recordset.IsEOF())
		{
			m_recordset.GetFieldValue("degree",strAttribute);
			m_ctrResult.InsertItem(i,strAttribute);
			m_recordset.GetFieldValue("amount",strAttribute);
			m_ctrResult.SetItemText(i,1,strAttribute);
			i++;
			m_recordset.MoveNext();
		}
		m_recordset.Close();
		break;
	//��������òͳ��
	case 7:
		m_ctrResult.DeleteAllItems();
		m_ctrResult.DeleteColumn(1);
		m_ctrResult.DeleteColumn(0);
		m_ctrResult.InsertColumn(0,"������ò");
		m_ctrResult.InsertColumn(1,"����");
		m_ctrResult.SetColumnWidth(0,80);
		m_ctrResult.SetColumnWidth(1,100);
		strSQL = "select count(code) as amount ,party from staff group by party";
		if(!m_recordset.Open(CRecordset::forwardOnly,strSQL))
		{
			MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		}
		while(!m_recordset.IsEOF())
		{
			m_recordset.GetFieldValue("party",strAttribute);
			m_ctrResult.InsertItem(i,strAttribute);
			m_recordset.GetFieldValue("amount",strAttribute);
			m_ctrResult.SetItemText(i,1,strAttribute);
			i++;
			m_recordset.MoveNext();
		}
		m_recordset.Close();
		break;
	//��Ժϵ����ͳ��
	case 8:
		m_ctrResult.DeleteAllItems();
		m_ctrResult.DeleteColumn(1);
		m_ctrResult.DeleteColumn(0);
		m_ctrResult.InsertColumn(0,"Ժϵ����");
		m_ctrResult.InsertColumn(1,"����");
		m_ctrResult.SetColumnWidth(0,80);
		m_ctrResult.SetColumnWidth(1,100);
		strSQL = "select count(code) as amount ,department from staff group by department";
		if(!m_recordset.Open(CRecordset::forwardOnly,strSQL))
		{
			MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		}
		while(!m_recordset.IsEOF())
		{
			m_recordset.GetFieldValue("department",strAttribute);
			m_ctrResult.InsertItem(i,strAttribute);
			m_recordset.GetFieldValue("amount",strAttribute);
			m_ctrResult.SetItemText(i,1,strAttribute);
			i++;
			m_recordset.MoveNext();
		}
		m_recordset.Close();
		break;
	//���̹���λͳ��
	case 9:
		m_ctrResult.DeleteAllItems();
		m_ctrResult.DeleteColumn(1);
		m_ctrResult.DeleteColumn(0);
		m_ctrResult.InsertColumn(0,"�̹���λ");
		m_ctrResult.InsertColumn(1,"����");
		m_ctrResult.SetColumnWidth(0,80);
		m_ctrResult.SetColumnWidth(1,100);
		strSQL = "select count(code) as amount ,post from staff group by post";
		if(!m_recordset.Open(CRecordset::forwardOnly,strSQL))
		{
			MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		}
		while(!m_recordset.IsEOF())
		{
			m_recordset.GetFieldValue("post",strAttribute);
			m_ctrResult.InsertItem(i,strAttribute);
			m_recordset.GetFieldValue("amount",strAttribute);
			m_ctrResult.SetItemText(i,1,strAttribute);
			i++;
			m_recordset.MoveNext();
		}
		m_recordset.Close();
		break;
	//�����ʵȼ�ͳ��
	case 10:
		m_ctrResult.DeleteAllItems();
		m_ctrResult.DeleteColumn(1);
		m_ctrResult.DeleteColumn(0);
		m_ctrResult.InsertColumn(0,"���ʵȼ�");
		m_ctrResult.InsertColumn(1,"����");
		m_ctrResult.SetColumnWidth(0,80);
		m_ctrResult.SetColumnWidth(1,100);
		strSQL = "select count(code) as amount ,salary from staff group by salary";
		if(!m_recordset.Open(CRecordset::forwardOnly,strSQL))
		{
			MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		}
		while(!m_recordset.IsEOF())
		{
			m_recordset.GetFieldValue("salary",strAttribute);
			m_ctrResult.InsertItem(i,strAttribute);
			m_recordset.GetFieldValue("amount",strAttribute);
			m_ctrResult.SetItemText(i,1,strAttribute);
			i++;
			m_recordset.MoveNext();
		}
		m_recordset.Close();
		break;
	//������״��ͳ��
	case 11:
		m_ctrResult.DeleteAllItems();
		m_ctrResult.DeleteColumn(1);
		m_ctrResult.DeleteColumn(0);
		m_ctrResult.InsertColumn(0,"����״��");
		m_ctrResult.InsertColumn(1,"����");
		m_ctrResult.SetColumnWidth(0,80);
		m_ctrResult.SetColumnWidth(1,100);
		strSQL = "select count(code) as amount ,marriage from staff group by marriage";
		if(!m_recordset.Open(CRecordset::forwardOnly,strSQL))
		{
			MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		}
		while(!m_recordset.IsEOF())
		{
			m_recordset.GetFieldValue("marriage",strAttribute);
			m_ctrResult.InsertItem(i,strAttribute);
			m_recordset.GetFieldValue("amount",strAttribute);
			m_ctrResult.SetItemText(i,1,strAttribute);
			i++;
			m_recordset.MoveNext();
		}
		m_recordset.Close();
		break;
	//����ҵԺУͳ��
	case 12:
		m_ctrResult.DeleteAllItems();
		m_ctrResult.DeleteColumn(1);
		m_ctrResult.DeleteColumn(0);
		m_ctrResult.InsertColumn(0,"��ҵԺУ");
		m_ctrResult.InsertColumn(1,"����");
		m_ctrResult.SetColumnWidth(0,80);
		m_ctrResult.SetColumnWidth(1,100);
		strSQL = "select count(code) as amount ,university from staff group by university";
		if(!m_recordset.Open(CRecordset::forwardOnly,strSQL))
		{
			MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		}
		while(!m_recordset.IsEOF())
		{
			m_recordset.GetFieldValue("university",strAttribute);
			m_ctrResult.InsertItem(i,strAttribute);
			m_recordset.GetFieldValue("amount",strAttribute);
			m_ctrResult.SetItemText(i,1,strAttribute);
			i++;
			m_recordset.MoveNext();
		}
		m_recordset.Close();
		break;
	//����ѧרҵͳ��
	case 13:
		m_ctrResult.DeleteAllItems();
		m_ctrResult.DeleteColumn(1);
		m_ctrResult.DeleteColumn(0);
		m_ctrResult.InsertColumn(0,"��ѧרҵ");
		m_ctrResult.InsertColumn(1,"����");
		m_ctrResult.SetColumnWidth(0,80);
		m_ctrResult.SetColumnWidth(1,100);
		strSQL = "select count(code) as amount ,subject from staff group by subject";
		if(!m_recordset.Open(CRecordset::forwardOnly,strSQL))
		{
			MessageBox("�����ݿ�ʧ�ܣ�","���ݿ����",MB_OK);
			return;
		}
		while(!m_recordset.IsEOF())
		{
			m_recordset.GetFieldValue("subject",strAttribute);
			m_ctrResult.InsertItem(i,strAttribute);
			m_recordset.GetFieldValue("amount",strAttribute);
			m_ctrResult.SetItemText(i,1,strAttribute);
			i++;
			m_recordset.MoveNext();
		}
		m_recordset.Close();
		break;
	default:
		return;
	}
	UpdateData(FALSE);
	//��Ӵ������
	*pResult = 0;
}

BOOL CStatisticsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//��Ӵ���
	m_ctrSelection.InsertColumn(0,"ͳ�����");
    m_ctrSelection.SetColumnWidth(0,120);
	m_ctrSelection.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_ctrSelection.InsertItem(0,"���Ա�ͳ��");
	m_ctrSelection.InsertItem(1,"������ͳ��");
	m_ctrSelection.InsertItem(2,"������ͳ��");
	m_ctrSelection.InsertItem(3,"������ͳ��");
	m_ctrSelection.InsertItem(4,"��ְ��ͳ��");
	m_ctrSelection.InsertItem(5,"��ְ��ͳ��");
	m_ctrSelection.InsertItem(6,"��ѧ��ͳ��");
	m_ctrSelection.InsertItem(7,"��������òͳ��");
	m_ctrSelection.InsertItem(8,"��Ժϵ����ͳ��");
	m_ctrSelection.InsertItem(9,"���̹���λͳ��");
	m_ctrSelection.InsertItem(10,"�����ʵȼ�ͳ��");
	m_ctrSelection.InsertItem(11,"������״��ͳ��");
	m_ctrSelection.InsertItem(12,"����ҵԺУͳ��");
	m_ctrSelection.InsertItem(13,"����ѧרҵͳ��");
	m_ctrResult.InsertColumn(0,"");
	m_ctrResult.SetColumnWidth(0,80);
	m_ctrResult.InsertColumn(1,"");
	m_ctrResult.SetColumnWidth(1,100);
	m_ctrResult.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	//��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
