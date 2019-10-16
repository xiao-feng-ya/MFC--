
// codeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "code.h"
#include "codeDlg.h"
#include "afxdialogex.h"
#include "HalconCpp.h"
using namespace Halcon;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//相机的参数
 Hobject  Image1,Image2,Image3;
 HTuple  AcqHandle1,AcqHandle2,AcqHandle3;
 HTuple  hv_WindowHandle1,hv_WindowHandle2,hv_WindowHandle3;
 //相机视频流是否打开与关闭的辅助判断
 bool camera1ontime=FALSE,camera2ontime=FALSE,camera3ontime=FALSE;
 //halcon窗口打开和关闭的 标识
 bool HalconW1=FALSE,HalconW2=FALSE,HalconW3=FALSE;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CcodeDlg 对话框




CcodeDlg::CcodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcodeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Control(pDX, IDC_CHECK2, m_check2);
	DDX_Control(pDX, IDC_CHECK3, m_check3);
}

BEGIN_MESSAGE_MAP(CcodeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CcodeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CcodeDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CcodeDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CcodeDlg::OnBnClickedButton4)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON5, &CcodeDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CcodeDlg 消息处理程序

BOOL CcodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CcodeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CcodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//相机的初始化
void CcodeDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
    //第一个相机是否选中
	if (1==m_check1.GetCheck())
    {
		Icamera1();

    } 
    else
    {
		MessageBox("1号没选中");
    }
	//第2个相机是否选中
	if (1==m_check2.GetCheck())
	{
		Icamera2();
	} 
	else
	{
		MessageBox("2号没选中");
	}
	//第3 个相机是否选中
	if (1==m_check3.GetCheck())
	{
		Icamera3();
	} 
	else
	{
		MessageBox("3号没选中");
	}

}

//视频流的初始化
void CcodeDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//第一个相机是否选中
	if (1==m_check1.GetCheck())
	{		
		//开始视频流
		camera1ontime=TRUE;//辅助标记视频流打开
		SetTimer(1,50,NULL);
	} 
	else
	{
		
	}

	//第2个相机是否选中
	if (1==m_check2.GetCheck())
	{
		//开始视频流
		camera2ontime=TRUE;//辅助标记视频流打开
		SetTimer(2,50,NULL);
	} 
	else
	{
		
	}
	//第3 个相机是否选中
	if (1==m_check3.GetCheck())
	{
		camera3ontime=TRUE;
		SetTimer(3,50,NULL);
	} 
	else
	{
		
	}
}
//初始化相机1号，放置图片控件和HALCON窗口与相机的放置
void CcodeDlg::Icamera1()
{
	CRect m_rect1;                              //创建矩阵
	GetDlgItem(IDC_STATIC_1)->GetWindowRect(&m_rect1);  //讲图片空间的大小保存，把第1个图片控件的ID放入
	HWND hwnd1= GetDlgItem(IDC_STATIC_1)->m_hWnd;   //把第一个图框（IDC_IMAGE_STATIC）的句柄格式转换
	//打开相机，使控件和相机的采集大小匹配

	//更换相机用haclon的助手调用
	open_framegrabber("GigEVision", 0, 0, 0, 0, 0, 0, "progressive", -1, "default", 
		-1, "false", "default", "0021490171f7_DahengImaging_MER50014GC", 0, -1, &AcqHandle1);
	//

	grab_image_start(AcqHandle1, -1);
    grab_image_async(&Image1, AcqHandle1, -1);	
	//放置窗口
	HalconW1=TRUE;//标识打开窗口1
	open_window(0,0,m_rect1.Width(),m_rect1.Height(),(long)hwnd1,"visible","",&hv_WindowHandle1);//第5个位置，输入转换格式(long)hwnd1
	HDevWindowStack::Push(hv_WindowHandle1);	
	if (HDevWindowStack::IsOpen())
		disp_obj(Image1, hv_WindowHandle1);//显示图片
	    set_draw(hv_WindowHandle1,"margin");
	    set_color(hv_WindowHandle1,"red");

	
}
//初始化相机2号，放置图片控件和HALCON窗口与相机的放置
//跟换相机只要更改open_framegrabber,相机的参数更改用HALCON里的助手直接得到
void CcodeDlg::Icamera2()
{
	CRect m_rect2;                              //创建矩阵
	GetDlgItem(IDC_STATIC_2)->GetWindowRect(&m_rect2);  //讲图片空间的大小保存，把第1个图片控件的ID放入
	HWND hwnd2= GetDlgItem(IDC_STATIC_2)->m_hWnd;   //把第一个图框（IDC_IMAGE_STATIC）的句柄格式转换
	//打开相机，使控件和相机的采集大小匹配

	//open_framegrabber用HALCON获取带入
	//
	open_framegrabber("GigEVision", 0, 0, 0, 0, 0, 0, "progressive", -1, "default", 
		-1, "false", "default", "0021490171f7_DahengImaging_MER50014GC", 0, -1, &AcqHandle2);
	//
	grab_image_start(AcqHandle2, -1);
	grab_image_async(&Image2, AcqHandle2, -1);	
	//放置窗口
	HalconW2=TRUE;//标识打开窗口2
	open_window(0,0,m_rect2.Width(),m_rect2.Height(),(long)hwnd2,"visible","",&hv_WindowHandle2);//第5个位置，输入转换格式(long)hwnd1
	HDevWindowStack::Push(hv_WindowHandle2);	
	if (HDevWindowStack::IsOpen())
		disp_obj(Image2, hv_WindowHandle2);//显示图片
	set_draw(hv_WindowHandle2,"margin");
	set_color(hv_WindowHandle2,"red");
}//初始化相机3号，放置图片控件和HALCON窗口与相机的放置
void CcodeDlg::Icamera3()
{
	CRect m_rect3;                              //创建矩阵
	GetDlgItem(IDC_STATIC_3)->GetWindowRect(&m_rect3);  //讲图片空间的大小保存，把第1个图片控件的ID放入
	HWND hwnd3= GetDlgItem(IDC_STATIC_3)->m_hWnd;   //把第一个图框（IDC_IMAGE_STATIC）的句柄格式转换
	//打开相机，使控件和相机的采集大小匹配
	open_framegrabber("GigEVision", 0, 0, 0, 0, 0, 0, "progressive", -1, "default", 
		-1, "false", "default", "0021490171f7_DahengImaging_MER50014GC", 0, -1, &AcqHandle3);
	//
	grab_image_start(AcqHandle3, -1);
	grab_image_async(&Image3, AcqHandle3, -1);	
	//放置窗口
	HalconW3=TRUE;//标识打开窗口3
	open_window(0,0,m_rect3.Width(),m_rect3.Height(),(long)hwnd3,"visible","",&hv_WindowHandle3);//第5个位置，输入转换格式(long)hwnd1
	HDevWindowStack::Push(hv_WindowHandle3);	
	if (HDevWindowStack::IsOpen())
		disp_obj(Image3, hv_WindowHandle3);//显示图片
	set_draw(hv_WindowHandle3,"margin");
	set_color(hv_WindowHandle3,"red");
}

//关闭全部相机
void CcodeDlg::OnBnClickedButton3()
{
	// 1号相机
	if (camera1ontime==TRUE)
	{
		KillTimer(1);
		camera1ontime=FALSE;
	}
	if (HalconW1==TRUE)
	{
		if (HDevWindowStack::IsOpen())
		clear_window(hv_WindowHandle1);
	    close_window(hv_WindowHandle1);
		HalconW1=FALSE;
	}
	
	//2号相机
	if (camera2ontime==TRUE)
	{
		KillTimer(2);
		camera2ontime=FALSE;
	}
	if(HalconW2==TRUE)
	{
		if (HDevWindowStack::IsOpen())
			clear_window(hv_WindowHandle2);
			close_window(hv_WindowHandle2);
		HalconW2=FALSE;
	}
	
	//3号相机
	if (camera3ontime==TRUE)
	{
		KillTimer(3);
		camera3ontime=FALSE;
	}
	if(HalconW3==TRUE)
	{
		if (HDevWindowStack::IsOpen())
			clear_window(hv_WindowHandle3);
			close_window(hv_WindowHandle3);
		HalconW3=FALSE;
	}

    close_all_framegrabbers();//关闭全部相机


}
//

void CcodeDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	


}

//1,2,3用于视频流的使用
void CcodeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)      
	{      
	case 1: 
		// 一号相机视频流的采集，可加预处理     
		grab_image_async(&Image1,AcqHandle1,-1);
		clear_window(hv_WindowHandle1);
		disp_obj(Image1,hv_WindowHandle1);
		break;      
	case 2:      
		// 如果收到ID为2的定时器的消息则调用函数      
		grab_image_async(&Image2,AcqHandle2,-1);
		clear_window(hv_WindowHandle2);
		disp_obj(Image2,hv_WindowHandle2);   
		break;     
	case 3:
		grab_image_async(&Image3,AcqHandle3,-1);
		clear_window(hv_WindowHandle3);
		disp_obj(Image3,hv_WindowHandle3);  
		break;
	default:      
		break;      
	}      
	CDialogEx::OnTimer(nIDEvent);
}

//触发相机拍照，可放在处理函数
void CcodeDlg::OnBnClickedButton5()
{
	// 1号相机
	if (1==m_check1.GetCheck())
	{
	    if (camera1ontime==TRUE)
	  {
		KillTimer(1);
		camera1ontime=FALSE;
	  }
	  grab_image(&Image1,AcqHandle1);
	  scale_image(Image1,&Image1,-1,255);
	  clear_window(hv_WindowHandle1);
	  disp_obj(Image1,hv_WindowHandle1);
	}
	//2号相机
	if (1==m_check2.GetCheck())
	{
		if (camera2ontime==TRUE)
		{
			KillTimer(2);
			camera2ontime=FALSE;
		}
		grab_image(&Image2,AcqHandle2);
		scale_image(Image2,&Image2,-1,255);
		clear_window(hv_WindowHandle2);
		disp_obj(Image2,hv_WindowHandle2);
	}
	//3号相机
	if (1==m_check3.GetCheck())
	{
		if (camera3ontime==TRUE)
		{
			KillTimer(3);
			camera3ontime=FALSE;
		}
		grab_image(&Image3,AcqHandle3);
		scale_image(Image3,&Image3,-1,255);
		clear_window(hv_WindowHandle3);
		disp_obj(Image3,hv_WindowHandle3);
	}
}
