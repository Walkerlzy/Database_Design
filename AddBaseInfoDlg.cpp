// AddBaseInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "AddBaseInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddBaseInfoDlg dialog


CAddBaseInfoDlg::CAddBaseInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddBaseInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddBaseInfoDlg)
	m_strData = _T("");
	//��Ӵ���
	m_strLabel=_T("");
	m_strInformation=_T("");
	//��Ӵ������
	m_strDescription = _T("");
	//}}AFX_DATA_INIT
}


void CAddBaseInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddBaseInfoDlg)
	DDX_Control(pDX, IDC_EDIT_DESCRIPTION, m_ctrDescription);
	DDX_Control(pDX, IDC_EDIT_DATA, m_ctrData);
	DDX_Text(pDX, IDC_EDIT_DATA, m_strData);
	//��Ӵ���
	DDX_Text(pDX,IDC_STATIC_ADD,m_strLabel);
	DDX_Text(pDX,IDC_STATIC_INFORMATION,m_strInformation);
	//��Ӵ������
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_strDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddBaseInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CAddBaseInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddBaseInfoDlg message handlers

void CAddBaseInfoDlg::OnOK() 
{
	// TODO: Add extra validation here
	//��Ӵ���
	UpdateData();
	if(m_strData=="")
	{
		MessageBox("���������������Ϣ��");
		m_ctrData.SetFocus();
		return;
	}
	//��Ӵ������	
	CDialog::OnOK();
}
