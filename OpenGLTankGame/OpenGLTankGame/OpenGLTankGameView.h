
// OpenGLTankGameView.h : COpenGLTankGameView ��Ľӿ�
//

#pragma once
#include <gl\GLU.h>
#include <gl\GL.h>
#include <vector>
#include <gl\glut.h>
#include "Tank.h"

#define Forward -1
#define Back 1
#define Right 1
#define Left -1

#define BombFly 02

class COpenGLTankGameView : public CView
{
protected: // �������л�����
	COpenGLTankGameView();
	DECLARE_DYNCREATE(COpenGLTankGameView)

// ����
public:
	COpenGLTankGameDoc* GetDocument() const;
	HGLRC m_hRC;
	HDC m_hDC;
	Tank player;
	Bomb bomb;
	bool attacking;
// ����
public:
	void RenderScene();
	void reLook();
	void DrawPlane(double width, double length);
	void GLInit();
	void GLRelease();
	void GLResize(int cx, int cy);
	void GLSetupRC(HDC m_hDC);

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~COpenGLTankGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void judgeXMovement();
	void judgeZMovement();
	void Launch();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // OpenGLTankGameView.cpp �еĵ��԰汾
inline COpenGLTankGameDoc* COpenGLTankGameView::GetDocument() const
   { return reinterpret_cast<COpenGLTankGameDoc*>(m_pDocument); }
#endif

