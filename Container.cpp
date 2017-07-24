// Container.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "Container.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContainer

CContainer::CContainer()
{
	//��Ӵ���
	//��ģ�����뵱ǰģ��ĳ�ʼ��
	m_iTotalModels = 0;
	m_iCurrentModel = 0;
	//��Ӵ������
}

CContainer::~CContainer()
{
}


BEGIN_MESSAGE_MAP(CContainer, CTabCtrl)
	//{{AFX_MSG_MAP(CContainer)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContainer message handlers

BOOL CContainer::AddModel(LPCTSTR title, CDialog *pDialog, UINT ID)
{
    //��Ӵ���
    if(MAXMODEL == m_iTotalModels)
	    return FALSE;
    m_iTotalModels++;
    //�βθ�ֵ
    m_pMODELS[m_iTotalModels - 1] = pDialog;
    m_MID[m_iTotalModels - 1] = ID;
	m_strTitle[m_iTotalModels - 1] = title;
	return TRUE;
	//��Ӵ������
}

int CContainer::GetCurSel()
{
	//��Ӵ���
	return CTabCtrl::GetCurSel();
	//��Ӵ������
}

int CContainer::SetCurSel(int iOption)
{
    //��Ӵ���
	//��ǰѡ���쳣�Ĵ���
	if(iOption < 0 || iOption >= m_iTotalModels)
		return -1;
	int ret = m_iCurrentModel;
	//���û���ǰ����ȷѡ��ģ��������ʾ����
	if(m_iCurrentModel != iOption)
	{
		m_pMODELS[m_iCurrentModel] ->ShowWindow(SW_HIDE);
		m_iCurrentModel = iOption;
		m_pMODELS[m_iCurrentModel] ->ShowWindow(SW_SHOW);
		CTabCtrl::SetCurSel(iOption);
	}
	return ret;
	//��Ӵ������
}

void CContainer::SetRect()
{
    //��Ӵ���
	//�����������������
	CRect tabCtrlRect,optionRect;
	//����4�����ͱ������������������εı߽�
	int Xt,Yt,Xd,Yd;
	GetClientRect(&tabCtrlRect);
	GetItemRect(0,&optionRect);
	Xt = optionRect.left;
	Yt = optionRect.bottom + 1;
	Xd = tabCtrlRect.right - optionRect.left - 2;
	Yd = tabCtrlRect.bottom - Yt -2;
	m_pMODELS[0] ->SetWindowPos(&wndTop,Xt,Yt,Xd,Yd,SWP_SHOWWINDOW);
	for(int i = 1;i < m_iTotalModels;i++)
	m_pMODELS[i] ->SetWindowPos(&wndTop,Xt,Yt,Xd,Yd,SWP_HIDEWINDOW);
	//��Ӵ������
}

void CContainer::Display()
{
    //��Ӵ���
	for(int i = 0;i < m_iTotalModels;i++)
	{
		m_pMODELS[i] ->Create(m_MID[i],this);
		InsertItem(i,m_strTitle[i]);
	}
	m_pMODELS[0] ->ShowWindow(SW_SHOW);
	for(i = 1;i < m_iTotalModels;i++)
		m_pMODELS[i] ->ShowWindow(SW_HIDE);
	SetRect();
	//��Ӵ������
}

void CContainer::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CTabCtrl::OnLButtonDown(nFlags, point);
	//��Ӵ���
	//ģ����������ҳ��֮����л�
	if(m_iCurrentModel != GetCurFocus())
	{
		m_pMODELS[m_iCurrentModel] ->ShowWindow(SW_HIDE);
		m_iCurrentModel = GetCurFocus();
		m_pMODELS[m_iCurrentModel] ->ShowWindow(SW_SHOW);
	}
	//��Ӵ������
}
