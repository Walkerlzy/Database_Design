// DisciplinePunishDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "DisciplinePunishDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisciplinePunishDlg dialog


CDisciplinePunishDlg::CDisciplinePunishDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDisciplinePunishDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDisciplinePunishDlg)
	m_tmPDate = 0;
	m_tmDDate = 0;
	m_strPeriod = _T("");
	m_strSort = _T("");
	m_strPReason = _T("");
	m_strDReason = _T("");
	m_strUnit = _T("");
	// ��Ӵ���
    m_strCode = "";
    // ��Ӵ������
	//}}AFX_DATA_INIT
}


void CDisciplinePunishDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisciplinePunishDlg)
	DDX_Control(pDX, IDC_LIST_DISCIPLINEPUNISH, m_ctrDisPunish);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_bntSave);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_bntUpdate);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_bntDelete);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_bntAdd);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PDATE, m_tmPDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DDATE, m_tmDDate);
	DDX_CBString(pDX, IDC_COMBO_PERIOD, m_strPeriod);
	DDX_CBString(pDX, IDC_COMBO_SORT, m_strSort);
	DDX_Text(pDX, IDC_EDIT_PREASON, m_strPReason);
	DDX_Text(pDX, IDC_EDIT_DREASON, m_strDReason);
	DDX_Text(pDX, IDC_EDIT_UNIT1, m_strUnit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDisciplinePunishDlg, CDialog)
	//{{AFX_MSG_MAP(CDisciplinePunishDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DISCIPLINEPUNISH, OnClickListDisciplinepunish)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisciplinePunishDlg message handlers

void CDisciplinePunishDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
        m_strDReason = "";
        m_strPeriod  = "";
        m_strSort    = "";
        m_strPReason = "";
        m_strUnit    = "";
        m_tmDDate  = CTime::GetCurrentTime();
        m_tmPDate  = CTime::GetCurrentTime();
        m_bntSave.EnableWindow();
        m_bntAdd.EnableWindow(FALSE);
        m_bntDelete.EnableWindow(FALSE);
        m_bntUpdate.EnableWindow(FALSE);
        UpdateData(FALSE);
        // ��Ӵ������
}

void CDisciplinePunishDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
        int i = m_ctrDisPunish.GetSelectionMark();
        if(i<0)
        {
            MessageBox("��ѡ��һ����¼����ɾ����");
            return;
        }
        CString strSQL;
        strSQL.Format("select * from disciplinePunish where number = %s",m_ctrDisPunish.GetItemText(i,0));
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
        m_strDReason = "";
        m_strPReason = "";
        m_strSort    = "";
        m_strPeriod  = "";
        m_strUnit    = "";
        m_tmDDate  = CTime::GetCurrentTime();
        m_tmPDate  = CTime::GetCurrentTime();
        UpdateData(FALSE);
        // ��Ӵ������
}

void CDisciplinePunishDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
        UpdateData();
        int i = m_ctrDisPunish.GetSelectionMark();
        if(i<0)
        {
            MessageBox("��ѡ��һ����¼�����޸ģ�");
            return;
        }
        CString strSQL;
        strSQL.Format("select * from disciplinePunish where number = %s",m_ctrDisPunish.GetItemText(i,0));
        if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
        {
             MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
             return ;
        }
        m_recordset.Edit();
        m_recordset.m_ddate   = m_tmDDate;
        m_recordset.m_pdate   = m_tmPDate;
        m_recordset.m_dreason = m_strDReason;
        m_recordset.m_sort    = m_strSort;
        m_recordset.m_period  = m_strPeriod;
        m_recordset.m_unit    = m_strUnit;
        m_recordset.m_preason = m_strPReason;
        m_recordset.Update();
        m_recordset.Close();
        DataUpdate(m_strCode);
        // ��Ӵ������
}

void CDisciplinePunishDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
        UpdateData();
        if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE))
        {
             MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
             return ;
        }
        m_recordset.AddNew();
        m_recordset.m_dreason = m_strDReason;
        m_recordset.m_period  = m_strPeriod;
        m_recordset.m_ddate   = m_tmDDate;
        m_recordset.m_pdate   = m_tmPDate;
        m_recordset.m_sort    = m_strSort;
        m_recordset.m_preason = m_strPReason;
        m_recordset.m_unit    = m_strUnit;
        // �̹����codeҲҪ�������̨���ݿ�PostDB.accdb��
        m_recordset.m_code    = m_strCode;
        m_recordset.Update();
        m_recordset.Close();
        DataUpdate(m_strCode);
        // ��Ӵ������
}

void CDisciplinePunishDlg::OnClickListDisciplinepunish(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
        CString strSQL;
        UpdateData(TRUE);
        int i = m_ctrDisPunish.GetSelectionMark();
        strSQL.Format("select * from disciplinePunish where number=%s",m_ctrDisPunish.GetItemText(i,0));
        if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
        {
             MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
             return ;
        }
        m_strDReason = m_recordset.m_dreason;
        m_strPeriod   = m_recordset.m_period;
        m_tmDDate  = m_recordset.m_ddate;
        m_tmPDate  = m_recordset.m_pdate;
        m_strSort    = m_recordset.m_sort;
        m_strPReason = m_recordset.m_preason;
        m_strUnit    = m_recordset.m_unit;
        m_recordset.Close();
        UpdateData(FALSE);
        m_bntSave.EnableWindow(FALSE);
        m_bntAdd.EnableWindow();
        m_bntDelete.EnableWindow();
        m_bntUpdate.EnableWindow();
        // ��Ӵ������
	*pResult = 0;
}

BOOL CDisciplinePunishDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// ��Ӵ���
        // ��ʼ��������¼�Ի����е��б�ؼ���ͷ
        m_ctrDisPunish.InsertColumn(0,"���");
        m_ctrDisPunish.SetColumnWidth(0,60);
        m_ctrDisPunish.InsertColumn(1,"Υ������");
        m_ctrDisPunish.SetColumnWidth(1,80);
        m_ctrDisPunish.InsertColumn(2,"������");
        m_ctrDisPunish.SetColumnWidth(2,80);
        m_ctrDisPunish.InsertColumn(3,"Υ��ԭ��");
        m_ctrDisPunish.SetColumnWidth(3,80);
        m_ctrDisPunish.InsertColumn(4,"����ʱ��");
        m_ctrDisPunish.SetColumnWidth(4,80);
        m_ctrDisPunish.InsertColumn(5,"���ʱ��");
        m_ctrDisPunish.SetColumnWidth(5,80);
        m_ctrDisPunish.InsertColumn(6,"���ԭ��");
        m_ctrDisPunish.SetColumnWidth(6,80);
        m_ctrDisPunish.InsertColumn(7,"������׼��λ");
        m_ctrDisPunish.SetColumnWidth(7,80);
        m_ctrDisPunish.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
        m_bntSave.EnableWindow(FALSE);
        m_bntAdd.EnableWindow(FALSE);
        m_bntDelete.EnableWindow(FALSE);
        m_bntUpdate.EnableWindow(FALSE);
        // ��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDisciplinePunishDlg::DataUpdate(CString strCode)
{
       // ��Ӵ���
        m_ctrDisPunish.DeleteAllItems();
        m_ctrDisPunish.SetRedraw(FALSE);
        UpdateData(TRUE);
        CString strSQL;
        m_strCode.Format("%s",strCode);
        // SQL����������ʽ�е�code�ǽ̹��Ĺ���
        strSQL.Format( "select * from disciplinePunish where code = '%s'",strCode);
        if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
        {
             MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
             return ;
        }
        int i=0;
        CString strPTime; // ��Ӧ����ʱ��
        CString strDTime; // ��Ӧ���ʱ��
        char buffer[20];
        while(!m_recordset.IsEOF())
        {
        // ��Ӧ�б���ϵ����
        _ltoa(m_recordset.m_number,buffer,10);
        m_ctrDisPunish.InsertItem(i,buffer);
        // ��Ӧ�б���ϵ�Υ������
        m_ctrDisPunish.SetItemText(i,1,m_recordset.m_sort);
        // ��Ӧ�б���ϵĴ�����
        m_ctrDisPunish.SetItemText(i,2,m_recordset.m_period);
        // ��Ӧ�б���ϵ�Υ��ԭ��
        m_ctrDisPunish.SetItemText(i,3,m_recordset.m_preason);
        // ��Ӧ�б���ϵĴ���ʱ��
        strPTime.Format("%d-%d-%d",m_recordset.m_pdate.GetYear(),m_recordset.m_pdate.\
			GetMonth(),m_recordset.m_pdate.GetDay());
        m_ctrDisPunish.SetItemText(i,4,strPTime);
        // ��Ӧ�б���ϵĽ��ʱ��
        strDTime.Format("%d-%d-%d",m_recordset.m_ddate.GetYear(),m_recordset.m_ddate.\
			GetMonth(),m_recordset.m_ddate.GetDay());
        m_ctrDisPunish.SetItemText(i,5,strDTime);
        // ��Ӧ�б���ϵĽ��ԭ��
        m_ctrDisPunish.SetItemText(i,6,m_recordset.m_dreason);
        // ��Ӧ�б���ϵĴ�����׼��λ
        m_ctrDisPunish.SetItemText(i,7,m_recordset.m_unit);
        i++;
        m_recordset.MoveNext();
        }
        m_recordset.Close();
        m_ctrDisPunish.SetRedraw(TRUE);
        // �����Ƿ�����µ�Υ�ʹ�����¼��������뱣��������ť��״̬
        m_bntSave.EnableWindow(FALSE);
        if(m_strCode=="")
        m_bntAdd.EnableWindow(FALSE);
        else
            m_bntAdd.EnableWindow();
            m_bntDelete.EnableWindow(FALSE);
            m_bntUpdate.EnableWindow(FALSE);
        // ��Ӵ������
}
