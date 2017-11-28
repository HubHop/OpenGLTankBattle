
// OpenGLTankGameView.cpp : COpenGLTankGameView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OpenGLTankGame.h"
#endif

#include "OpenGLTankGameDoc.h"
#include "OpenGLTankGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLTankGameView

IMPLEMENT_DYNCREATE(COpenGLTankGameView, CView)

BEGIN_MESSAGE_MAP(COpenGLTankGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGLTankGameView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// COpenGLTankGameView 构造/析构

COpenGLTankGameView::COpenGLTankGameView()
{
	// TODO: 在此处添加构造代码

}

COpenGLTankGameView::~COpenGLTankGameView()
{
}

BOOL COpenGLTankGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COpenGLTankGameView 绘制

void COpenGLTankGameView::OnDraw(CDC* /*pDC*/)
{
	COpenGLTankGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	RenderScene();
	SwapBuffers(m_hDC);
	// TODO: 在此处为本机数据添加绘制代码
}


// COpenGLTankGameView 打印


void COpenGLTankGameView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpenGLTankGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COpenGLTankGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COpenGLTankGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void COpenGLTankGameView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COpenGLTankGameView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpenGLTankGameView 诊断

#ifdef _DEBUG
void COpenGLTankGameView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLTankGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLTankGameDoc* COpenGLTankGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLTankGameDoc)));
	return (COpenGLTankGameDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLTankGameView 消息处理程序

int COpenGLTankGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	GLInit();
	return 0;
}

void COpenGLTankGameView::GLInit()
{
	m_hDC = ::GetDC(m_hWnd);
	static PIXELFORMATDESCRIPTOR pfdWnd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW,
		PFD_SUPPORT_OPENGL,
		LPD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0,0,0,0,0,
		0,0,0,0,0,0,0,
		32,
		0,0,
		PFD_MAIN_PLANE,
		0,
		0,0
	};
	int pixelformat;
	pixelformat = ChoosePixelFormat(m_hDC, &pfdWnd);
	SetPixelFormat(m_hDC, pixelformat, &pfdWnd);

	m_hRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hRC);

	GLSetupRC(m_hDC);
}

void COpenGLTankGameView::GLSetupRC(HDC m_hDC)
{
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPos[] = { -1000.0f, 1000.0f, 1000.0f, 1.0f };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	//glMateriali(GL_FRONT, GL_SHININESS, 100);
	glEnable(GL_COLOR_MATERIAL);
	//glColor3f(0.925, 0.921, 0.930)
	glClearColor(0.925, 0.921, 0.930, 1.0f);
	glColor3f(1, 0, 0);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void COpenGLTankGameView::OnDestroy()
{
	wglMakeCurrent(NULL, NULL);
	GLRelease();
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void COpenGLTankGameView::GLRelease()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);
}


void COpenGLTankGameView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	GLResize(cx, cy);
	// TODO: 在此处添加消息处理程序代码
}

void COpenGLTankGameView::GLResize(int cx, int cy)
{
	double nRange = 3.0;
	if (cy == 0) cy = 1;
	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (double)cx / cy, 0.1, 50 * nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	double eye[3], ref[3], up_dir[3];
	eye[0] = 0; eye[1] = 30; eye[2] = 9 * nRange;
	ref[0] = 0; ref[1] = 0; ref[2] = 0;
	up_dir[0] = 0; up_dir[1] = 1; up_dir[2] = 0;
	gluLookAt(eye[0], eye[1], eye[2], ref[0], ref[1], ref[2], up_dir[0], up_dir[1], up_dir[2]);


}

BOOL COpenGLTankGameView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return true;
}

void COpenGLTankGameView::RenderScene()
{
	// clear color buffer and depth buffer 清屏
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//DrawWall();

	glLoadIdentity();
	reLook();

	DrawPlane(200, 100);
	glPushMatrix();
	player.drawSelf();
	glPopMatrix();


	if (attacking)
	{
		bomb.drawSelf();
	}

	glRotatef(30, 0, 1, 0);
	//DrawTank(-10, -10);

	glFlush();    //强制执行opengl语句
}

void COpenGLTankGameView::reLook()
{
	double nRange = 3.0;
	double eye[3], ref[3], up_dir[3];
	eye[0] = 0; eye[1] = 30; eye[2] = 9 * nRange;
	ref[0] = 0; ref[1] = 0; ref[2] = 0;
	up_dir[0] = 0; up_dir[1] = 1; up_dir[2] = 0;
	gluLookAt(eye[0], eye[1], eye[2], ref[0], ref[1], ref[2], up_dir[0], up_dir[1], up_dir[2]);
}

void COpenGLTankGameView::DrawPlane(double width, double length)
{
	//glColor3f(0.847, 0.847, 0.847);
	glPushMatrix();
	glColor3f(1, 1, 1);
	//DrawTankBody(width, 0.1, length, 0.795, 0.662, 0.661);
	/*下面开始绘制四边形*/
	glBegin(GL_QUADS);
	glVertex3f(-width / 2, 0, -length / 2); // 左上顶点
	glVertex3f(width / 2, 0, -length / 2); // 右上顶点
	glVertex3f(width / 2, 0, length / 2); // 右下顶点
	glVertex3f(-width / 2, 0, length / 2); // 左下顶点
	glEnd(); // 四边形绘制结束
	glPopMatrix();
}


void COpenGLTankGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case VK_UP:
		judgeXMovement();
		if (GetKeyState(VK_SPACE) < 0)
		{
			Launch();
		}
		this->player.moveZ(Forward);
		break;
	case VK_DOWN:
		judgeXMovement();
		if (GetKeyState(VK_SPACE) < 0)
		{
			Launch();
		}
		this->player.moveZ(Back);
		break;
	case VK_LEFT:
		judgeZMovement();
		if (GetKeyState(VK_SPACE) < 0)
		{
			Launch();
		}
		this->player.moveX(Left);
		break;
	case VK_RIGHT:
		judgeZMovement();
		if (GetKeyState(VK_SPACE) < 0)
		{
			Launch();
		}
		this->player.moveX(Right);
		break;
	case VK_SPACE:
		Launch();
		break;
	default:
		break;
	}
	RenderScene();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void COpenGLTankGameView::judgeXMovement()
{
	if (GetKeyState(VK_LEFT) < 0)
	{
		player.moveX(Left);
	}
	if (GetKeyState(VK_RIGHT) < 0)
	{
		player.moveX(Right);
	}
	if (GetKeyState(VK_SPACE) < 0)
	{
		Launch();
	}
}

void COpenGLTankGameView::judgeZMovement()
{
	if (GetKeyState(VK_UP) < 0)
	{
		player.moveZ(Forward);
	}
	if (GetKeyState(VK_DOWN) < 0)
	{
		player.moveZ(Back);
	}
}

void COpenGLTankGameView::Launch()
{
	this->bomb = Bomb();
	bomb.x = player.x;
	bomb.z = player.z;
	bomb.y = player.height;
	bomb.direction = player.angle;
	SetTimer(BombFly, 30, NULL);
	attacking = true;
}


void COpenGLTankGameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case BombFly:
		this->bomb.fly(1);
		this->attacking = true;
		RenderScene();
		break;
	}
	CView::OnTimer(nIDEvent);
}


void COpenGLTankGameView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case VK_UP:
		judgeXMovement();
		if (GetKeyState(VK_SPACE) < 0)
		{
			Launch();
		}
		break;
	case VK_DOWN:
		judgeXMovement();
		if (GetKeyState(VK_SPACE) < 0)
		{
			Launch();
		}
		break;
	case VK_LEFT:
		judgeZMovement();
		if (GetKeyState(VK_SPACE) < 0)
		{
			Launch();
		}
		break;
	case VK_RIGHT:
		judgeZMovement();
		if (GetKeyState(VK_SPACE) < 0)
		{
			Launch();
		}
		break;
	case VK_SPACE:
		judgeXMovement();
		judgeZMovement();
		break;
	default:
		break;
	}
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
