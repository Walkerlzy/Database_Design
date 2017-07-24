// PaperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "PaperDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaperDlg dialog


CPaperDlg::CPaperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPaperDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPaperDlg)
	m_tmPubTime = 0;
	m_strRank = _T("");
	m_strLevel = _T("");
	m_strType = _T("");
	m_strIndex = _T("");
	m_strTitle = _T("");
	m_strPublication = _T("");
	m_strPubyear = _T("");
	m_strVolume = _T("");
	m_strIssue = _T("");
	m_strPage = _T("");
	// ��Ӵ���
    m_strCode = "";
    // ��Ӵ������
	//}}AFX_DATA_INIT
}


void CPaperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaperDlg)
	DDX_Control(pDX, IDC_LIST_PAPER, m_ctrPaper);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_bntSave);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_bntUpdate);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_bntDelete);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_bntAdd);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PUBTIME, m_tmPubTime);
	DDX_CBString(pDX, IDC_COMBO_RANK, m_strRank);
	DDX_CBString(pDX, IDC_COMBO_LEVEL, m_strLevel);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_strType);
	DDX_CBString(pDX, IDC_COMBO_INDEX, m_strIndex);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_PUBLICATION, m_strPublication);
	DDX_Text(pDX, IDC_EDIT_PUBTIME, m_strPubyear);
	DDX_Text(pDX, IDC_EDIT_VOLUME, m_strVolume);
	DDX_Text(pDX, IDC_EDIT_ISSUE, m_strIssue);
	DDX_Text(pDX, IDC_EDIT_PAGE, m_strPage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPaperDlg, CDialog)
	//{{AFX_MSG_MAP(CPaperDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PAPER, OnClickListPaper)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaperDlg message handlers

void CPaperDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
        m_strIndex       = "";
        m_strIssue       = "";
        m_strLevel       = "";
        m_strPage        = "";
        m_strPublication = "";
        m_tmPubTime  = CTime::GetCurrentTime();
        m_strPubyear     = "";
        m_strRank        = "";
        m_strTitle       = "";
        m_strType        = "";
        m_strVolume      = "";
        m_bntSave.EnableWindow();
        m_bntAdd.EnableWindow(FALSE);
        m_bntDelete.EnableWindow(FALSE);
        m_bntUpdate.EnableWindow(FALSE);
        UpdateData(FALSE);
        // ��Ӵ������
}

void CPaperDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
        int i = m_ctrPaper.GetSelectionMark();
        if(i<0)
        {
            MessageBox("��ѡ��һ����¼����ɾ����");
            return;
        }
        CString strSQL;
        strSQL.Format("select * from paper where number= %s ",m_ctrPaper.GetItemText(i,0));
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
        m_strIndex       = "";
        m_strIssue       = "";
        m_strLevel       = "";
        m_strPage        = "";
        m_strPublication = "";
        m_strPubyear     = "";
        m_strRank        = "";
        m_strTitle       = "";
        m_strType        = "";
        m_strVolume      = "";
        m_tmPubTime  = CTime::GetCurrentTime();
        UpdateData(FALSE);
        // ��Ӵ������
}

void CPaperDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
        UpdateData();
        int i = m_ctrPaper.GetSelectionMark();
        if(i<0)
        {
            MessageBox("��ѡ��һ����¼�����޸ģ�");
            return;
        }
        CString strSQL;
        strSQL.Format("select * from paper where number= %s ",m_ctrPaper.GetItemText(i,0));
        if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
        {
             MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
        return ;
        }
        m_recordset.Edit();
        m_recordset.m_pub_time    = m_tmPubTime;
        m_recordset.m_index       = m_strIndex;
        m_recordset.m_issue       = m_strIssue;
        m_recordset.m_level       = m_strLevel;
        m_recordset.m_page        = m_strPage;
        m_recordset.m_publication = m_strPublication;
        m_recordset.m_pub_year    = m_strPubyear;
        m_recordset.m_rank        = m_strRank;
        m_recordset.m_title       = m_strTitle;
        m_recordset.m_type        = m_strType;
        m_recordset.m_volume      = m_strVolume;
        m_recordset.Update();
        m_recordset.Close();
        DataUpdate(m_strCode);
        // ��Ӵ������
}

void CPaperDlg::OnButtonSave() 
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
        m_recordset.m_index       = m_strIndex;
        m_recordset.m_issue       = m_strIssue;
        m_recordset.m_pub_time    = m_tmPubTime;
        m_recordset.m_level       = m_strLevel;
        m_recordset.m_page        = m_strPage;
        m_recordset.m_publication = m_strPublication;
        m_recordset.m_pub_year    = m_strPubyear;
        m_recordset.m_rank        = m_strRank;
        m_recordset.m_title       = m_strTitle;
        m_recordset.m_type        = m_strType;
        m_recordset.m_volume      = m_strVolume;
        // �̹����codeҲҪ�������̨���ݿ�PostDB.accdb��
        m_recordset.m_code        = m_strCode;
        m_recordset.Update();
        m_recordset.Close();
        DataUpdate(m_strCode);
        // ��Ӵ������
}

void CPaperDlg::OnClickListPaper(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// ��Ӵ���
        CString strSQL;
        UpdateData(TRUE);
        int i = m_ctrPaper.GetSelectionMark();
        strSQL.Format("select * from paper where number=%s",m_ctrPaper.GetItemText(i,0));
        if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
        {
             MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
             return ;
        }
        m_strIndex       = m_recordset.m_index;
        m_strIssue       = m_recordset.m_issue;
        m_tmPubTime      = m_recordset.m_pub_time;
        m_strLevel       = m_recordset.m_level;
        m_strPage        = m_recordset.m_page;
        m_strPublication = m_recordset.m_publication;
        m_strPubyear     = m_recordset.m_pub_year;
        m_strRank        = m_recordset.m_rank;
        m_strTitle       = m_recordset.m_title;
        m_strType        = m_recordset.m_type;
        m_strVolume      = m_recordset.m_volume;
        m_recordset.Close();
        UpdateData(FALSE);
        m_bntSave.EnableWindow(FALSE);
        m_bntAdd.EnableWindow();
        m_bntDelete.EnableWindow();
        m_bntUpdate.EnableWindow();
        // ��Ӵ������
	*pResult = 0;
}

BOOL CPaperDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// ��Ӵ���
        // ��ʼ��������¼�Ի����е��б�ؼ���ͷ
        m_ctrPaper.InsertColumn(0,"���");
        m_ctrPaper.SetColumnWidth(0,60);
        m_ctrPaper.InsertColumn(1,"��Ŀ");
        m_ctrPaper.SetColumnWidth(1,80);
        m_ctrPaper.InsertColumn(2,"��������");
        m_ctrPaper.SetColumnWidth(2,80);
        m_ctrPaper.InsertColumn(3,"��������");
        m_ctrPaper.SetColumnWidth(3,80);
        m_ctrPaper.InsertColumn(4,"����ʱ��");
        m_ctrPaper.SetColumnWidth(4,80);
        m_ctrPaper.InsertColumn(5,"������");
        m_ctrPaper.SetColumnWidth(5,80);
        m_ctrPaper.InsertColumn(6,"��");
        m_ctrPaper.SetColumnWidth(6,80);
        m_ctrPaper.InsertColumn(7,"��");
        m_ctrPaper.SetColumnWidth(7,80);
        m_ctrPaper.InsertColumn(8,"ҳ��");
        m_ctrPaper.SetColumnWidth(8,80);
        m_ctrPaper.InsertColumn(9,"���Ｖ��");
        m_ctrPaper.SetColumnWidth(9,80);
        m_ctrPaper.InsertColumn(10,"��������");
        m_ctrPaper.SetColumnWidth(10,80);
        m_ctrPaper.InsertColumn(11,"��������");
        m_ctrPaper.SetColumnWidth(11,80);
        m_ctrPaper.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
        m_bntSave.EnableWindow(FALSE);
        m_bntAdd.EnableWindow(FALSE);
        m_bntDelete.EnableWindow(FALSE);
        m_bntUpdate.EnableWindow(FALSE);
        // ��Ӵ������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPaperDlg::DataUpdate(CString strCode)
{
     // ��Ӵ���
        m_ctrPaper.DeleteAllItems();
        m_ctrPaper.SetRedraw(FALSE);
        UpdateData(TRUE);
        CString strSQL;
        m_strCode.Format("%s",strCode);
        // SQL����������ʽ�е�code�ǽ̹��Ĺ���
        strSQL.Format( "select * from paper where code = '%s'",strCode);
        if(!m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL))
        {
             MessageBox("�����ݿ�ʧ��!","���ݿ����",MB_OK);
             return ;
        }
        int i=0;
        CString strTime; // ��Ӧ����ʱ��
        char buffer[20];
        while(!m_recordset.IsEOF())
        {
        // ��Ӧ�б���ϵ����
        _ltoa(m_recordset.m_number,buffer,10);
        m_ctrPaper.InsertItem(i,buffer);
        // ��Ӧ�б���ϵ���Ŀ
        m_ctrPaper.SetItemText(i,1,m_recordset.m_title);
        // ��Ӧ�б���ϵ���������
        m_ctrPaper.SetItemText(i,2,m_recordset.m_rank);
        // ��Ӧ�б���ϵĿ�������
        m_ctrPaper.SetItemText(i,3,m_recordset.m_publication);
        // ��Ӧ�б���ϵķ���ʱ��
        strTime.Format("%d-%d-%d",m_recordset.m_pub_time.GetYear(),m_recordset.m_pub_time.\
			GetMonth(),m_recordset.m_pub_time.GetDay());
        m_ctrPaper.SetItemText(i,4,strTime);
        // ��Ӧ�б���ϵĳ�����
        m_ctrPaper.SetItemText(i,5,m_recordset.m_pub_year);
        // ��Ӧ�б���ϵľ�
        m_ctrPaper.SetItemText(i,6,m_recordset.m_volume);
        // ��Ӧ�б���ϵ���
        m_ctrPaper.SetItemText(i,7,m_recordset.m_issue);
        // ��Ӧ�б���ϵ�ҳ��
        m_ctrPaper.SetItemText(i,8,m_recordset.m_page);
        // ��Ӧ�б���ϵĿ��Ｖ��
        m_ctrPaper.SetItemText(i,9,m_recordset.m_level);
        // ��Ӧ�б���ϵ���������
        m_ctrPaper.SetItemText(i,10,m_recordset.m_type);
        // ��Ӧ�б���ϵļ�������
        m_ctrPaper.SetItemText(i,11,m_recordset.m_index);
        i++;
        m_recordset.MoveNext();
        }
        m_recordset.Close();
        m_ctrPaper.SetRedraw(TRUE);
        // �����Ƿ�����µ����ĳɹ���¼��������뱣��������ť��״̬
        m_bntSave.EnableWindow(FALSE);
        if(m_strCode=="")
        m_bntAdd.EnableWindow(FALSE);
        else
           m_bntAdd.EnableWindow();
           m_bntDelete.EnableWindow(FALSE);
           m_bntUpdate.EnableWindow(FALSE);
        // ��Ӵ������
}
