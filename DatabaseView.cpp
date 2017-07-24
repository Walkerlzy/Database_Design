// DatabaseView.cpp : implementation of the CDatabaseView class
//

#include "stdafx.h"
#include "Database.h"

#include "DatabaseDoc.h"
#include "DatabaseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView

IMPLEMENT_DYNCREATE(CDatabaseView, CView)

BEGIN_MESSAGE_MAP(CDatabaseView, CView)
	//{{AFX_MSG_MAP(CDatabaseView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView construction/destruction

CDatabaseView::CDatabaseView()
{
	// TODO: add construction code here

}

CDatabaseView::~CDatabaseView()
{
}

BOOL CDatabaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView drawing

void CDatabaseView::OnDraw(CDC* pDC)
{
	CDatabaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView printing

BOOL CDatabaseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDatabaseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDatabaseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView diagnostics

#ifdef _DEBUG
void CDatabaseView::AssertValid() const
{
	CView::AssertValid();
}

void CDatabaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDatabaseDoc* CDatabaseView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDatabaseDoc)));
	return (CDatabaseDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView message handlers

void CDatabaseView::OnPaint() 
{
	//CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//��Ӵ���
	CPaintDC*pDC = new CPaintDC(this);//device context for painting
	//�ֲ���������
	CBitmap bmp;
	RECT Rect;
	RECT RectView;
	POINT ptSize;
	CDC dcmem;
	BITMAP bm;
	int b = bmp.LoadBitmap(IDB_BITMAP_BG);    //װ�ر���λͼ��Դ
	dcmem.CreateCompatibleDC(pDC);
	dcmem.SelectObject(&bmp);
	dcmem.SetMapMode(pDC->GetMapMode());      //����λͼӳ��ģʽ
        GetObject(bmp.m_hObject,sizeof(BITMAP),(LPSTR)&bm);
	GetClientRect(&Rect);
	ptSize.x=bm.bmWidth;
	ptSize.y=bm.bmHeight;
	pDC->DPtoLP((LPPOINT)&ptSize,1);    //�豸��λת��Ϊ�߼���Ԫ
	GetClientRect(&RectView);
	CRect RectBmp = RectView;
	//���Ʊ���λͼ��Ŀ����Σ���Ҫʱ��Ŀ���豸���õ�ģʽ��ͼƬ
	//���������ѹ��
	pDC->StretchBlt(RectBmp.left,RectBmp.top,RectBmp.right,\
		RectBmp.bottom,&dcmem,0,0,bm.bmWidth,bm.bmHeight,\
		SRCCOPY);
	dcmem.DeleteDC();
	//��Ӵ������
	// Do not call CView::OnPaint() for painting messages
}
