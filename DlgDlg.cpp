// DlgDlg.cpp : implementation file
//
#include "stdafx.h"
#include "Dlg.h"
#include "DlgDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDlg dialog

CDlgDlg::CDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDlg::IDD, pParent)
{
	i=0;
	f=NULL;
	MaxI=0;
	FigType=0;
	isPressed=false;
	indexMAX=0;
	bool FigDeleted=false;
	indexMAXHistory=0;
	//orly set defulet coloer for shape, at the strat off porgram
	CMFCColorButtonPen.SetColor(RGB(0,0,0));
	CMFCColorButtonBrush.SetColor(RGB(255,255,255));
	PenColor=CMFCColorButtonPen.GetColor();
	BrushColor=CMFCColorButtonBrush.GetColor();


	//orly liner the drawing area
	PArea=new RectangleM (0,0,500,422, RGB(255,255,255),RGB(255,255,255));

	isMove=false;
	CurrentID=0;
	FileName="0";
	indexMAXHistory=0;
	//	GetDlgItem(IDC_BUTTON3)-&gt;ShowWindow(SW_HIDE);
	//{{AFX_DATA_INIT(CDlgDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDlgDlg::~CDlgDlg()
{
	for(int i=0;i<indexMAX;i++)
		delete figs[i];
	delete PArea;
}
//1 e
void CDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_MFCCOLORBUTTON1, ColorButton);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, CMFCColorButtonPen);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON3, CMFCColorButtonBrush);
	DDX_Control(pDX, IDC_BUTTON3, CButtonUndo);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, CMFCFile);
}

BEGIN_MESSAGE_MAP(CDlgDlg, CDialog)
	//{{AFX_MSG_MAP(CDlgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()

	ON_BN_CLICKED(IDC_Line, &CDlgDlg::OnBnClickedLine)
	ON_BN_CLICKED(IDC_Rectangle, &CDlgDlg::OnBnClickedRectangle)
	ON_BN_CLICKED(IDC_Ellipse, &CDlgDlg::OnBnClickedEllipse)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CDlgDlg::OnBnClickedMfccolorbutton1)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON3, &CDlgDlg::OnBnClickedMfccolorbutton3)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CDlgDlg::OnEnChangeMfceditbrowse1)
	ON_BN_CLICKED(IDR_SaveButton, &CDlgDlg::OnBnClickedSavebutton)
	ON_BN_CLICKED(IDC_LoadButton, &CDlgDlg::OnBnClickedLoadbutton)
	ON_WM_MBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTONUP, &CDlgDlg::OnBnClickedButtonup)
	ON_BN_CLICKED(IDC_BUTTONDOWN, &CDlgDlg::OnBnClickedButtondown)
	ON_BN_CLICKED(IDC_BUTTONRIGHT, &CDlgDlg::OnBnClickedButtonright)
	ON_BN_CLICKED(IDC_BUTTONLEFT, &CDlgDlg::OnBnClickedButtonleft)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDlg message handlers

BOOL CDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


void CDlgDlg::OnPaint() 
{
	CPaintDC dc (this);


	//update the MAX index ..(Used for history(redo undo))
	if (indexMAXHistory < indexMAX)
		indexMAXHistory=indexMAX;

	//Prin Paint Area
	PArea->Draw(&dc);

	//Print Figs1
	int TempPID=0;
	int i;
	if (indexMAX > 0)
		while (TempPID < MaxI)
		{
			for(i=indexMAX-1;i>=0;i--)
			{
				if ((figs[i]->pid==TempPID) && (figs[i]->action !=2))
				{
					figs[i]->Draw(&dc);
					TempPID++;
					break;
				}
				if((figs[i]->pid==TempPID) && (figs[i]->action == 2))
				{
					TempPID+=1;
					break;
				}
			}
		}


		//Print mause lines
		if(isPressed)
		{
			if(startP.x > PArea->x1 && startP.x < PArea->x2 && startP.y > PArea->y1 && startP.y < PArea->y2 )	
			{	
				if(isMove==false)
				{
					if(FigType==3)
					{
						dc.MoveTo(startP.x,startP.y);
						dc.LineTo(endP.x,endP.y);
					}
					else
					{
						dc.MoveTo(startP.x,startP.y);
						dc.LineTo(startP.x,endP.y);
						dc.LineTo(endP.x,endP.y);
						dc.LineTo(endP.x,startP.y);
						dc.LineTo(startP.x,startP.y);
					}
				}
				else
					//orly move object 
				{
					if(endP.x > PArea->x1 && endP.x < PArea->x2 && endP.y > PArea->y1 && endP.y < PArea->y2 )
					{

						DistX=endP.x - startP.x;
						DistY=endP.y - startP.y;
						TType = figs[i]->type;			

						dc.MoveTo(TstartP.x + DistX,TstartP.y + DistY);
						dc.LineTo(TstartP.x + DistX,TendP.y + DistY);
						dc.LineTo(TendP.x + DistX,TendP.y + DistY);
						dc.LineTo(TendP.x + DistX,TstartP.y + DistY);
						dc.LineTo(TstartP.x + DistX,TstartP.y + DistY);

					}
				}
			}
		}
		// orly meanu squres 
		RectangleM (0,422,603,493, RGB(220,220,220),RGB(0,0,0)).Draw(&dc);
		RectangleM (500,0,603,493, RGB(250,200,200),RGB(0,0,0)).Draw(&dc);
		RectangleM (500,422,603,493, RGB(200,200,200),RGB(0,0,0)).Draw(&dc);


		//orly Print preview
		if(FigType==1)
			RectangleM(520,430,585,485,PenColor,BrushColor).Draw(&dc);
		if(FigType==2)
			EllipseM(520,430,585,485,PenColor,BrushColor).Draw(&dc);
		if(FigType==3)
			LineM(520,430,585,485,BrushColor,PenColor).Draw(&dc);


}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDlgDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	isMove=false;
	startP=point;
	endP.x=0;
	endP.y=0;
	DistX=0;
	DistY=0;
	if(startP.x > PArea->x1 && startP.x < PArea->x2 && startP.y > PArea->y1 && startP.y < PArea->y2 )
	{

		//orly CHEAK IF CLICKED ON OBJECT
		int TempPID=MaxI;
		CurrentID=0;
		if (indexMAX > 0)
			while (TempPID >= 0)
			{

				for ( CurrentID=indexMAX-1 ; CurrentID >= 0 ; CurrentID--)
				{
					if(figs[CurrentID]->pid == TempPID)
					{
						FigDeleted = false;
						TstartP.x=figs[CurrentID]->x1;
						TstartP.y=figs[CurrentID]->y1;
						TendP.x=figs[CurrentID]->x2;
						TendP.y=figs[CurrentID]->y2;

						int temp;
						if (TstartP.x > TendP.x)
						{
							temp=TstartP.x;
							TstartP.x=TendP.x;
							TendP.x=temp;
						}
						if (TstartP.y > TendP.y)
						{
							temp=TstartP.y;
							TstartP.y=TendP.y;
							TendP.y=temp;
						}

						if(startP.x > TstartP.x && startP.x < TendP.x && startP.y > TstartP.y && startP.y < TendP.y && figs[CurrentID]->action != 2 )
						{
							for(int k=CurrentID+1 ; k < indexMAX ; k++)
							{
								if(figs[k]->pid == figs[CurrentID]->pid && figs[k]->action == 2 || figs[k]->pid == figs[CurrentID]->pid && figs[k]->action == 1)
									FigDeleted = true;
							}
							if(FigDeleted == false)
							{
								isMove=true;
								break;
							}

						}


					}

				}
				if(isMove==true)
					break;
				TempPID--;
			}

	}
	isPressed=true;
	CDialog::OnLButtonDown(nFlags, point);
}
void CDlgDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(isPressed)
	{
		endP=point;
		isPressed=false;	
		//orly Checks if muse is in the drawing area 
		if(startP.x > PArea->x1 && startP.x < PArea->x2 && startP.y > PArea->y1 && startP.y < PArea->y2 )
		{

			//orly clear history when creating new object
			if (indexMAXHistory > indexMAX)
				
			{
				for ( --indexMAXHistory  ; indexMAX <= indexMAXHistory ; indexMAXHistory--)
					delete figs[indexMAXHistory];
			}

            // orly Identifies shifted
			if(isMove==true)
			{
				TType=figs[CurrentID]->type;
				switch (TType)
				{
				case 1:
					figs[indexMAX++]=new RectangleM(figs[CurrentID]->x1+DistX,figs[CurrentID]->y1+DistY,figs[CurrentID]->x2+DistX,figs[CurrentID]->y2+DistY,figs[CurrentID]->Bcolor,figs[CurrentID]->Lcolor,1,figs[CurrentID]->pid,indexMAX);
					break;
				case 2:
					figs[indexMAX++]=new EllipseM(figs[CurrentID]->x1+DistX,figs[CurrentID]->y1+DistY,figs[CurrentID]->x2+DistX,figs[CurrentID]->y2+DistY,figs[CurrentID]->Bcolor,figs[CurrentID]->Lcolor,1,figs[CurrentID]->pid,indexMAX);
					break;
				case 3:
					figs[indexMAX++]=new LineM(figs[CurrentID]->x1+DistX,figs[CurrentID]->y1+DistY,figs[CurrentID]->x2+DistX,figs[CurrentID]->y2+DistY,figs[CurrentID]->Bcolor,figs[CurrentID]->Lcolor,1,figs[CurrentID]->pid,indexMAX);
					break;
				}


				isMove=false;
			}
			else
	//orly crate new fig
			
			{
				
				if (FigType == 1 || FigType == 2 || FigType == 3)
				{
					switch (FigType)
					{
					case 1:
						figs[indexMAX++]=new RectangleM(startP.x,startP.y,endP.x,endP.y,BrushColor,PenColor,0,MaxI,indexMAX);
						break;
					case 2:
						figs[indexMAX++]=new EllipseM(startP.x,startP.y,endP.x,endP.y,BrushColor,PenColor,0,MaxI,indexMAX);
						break;
					case 3:
						figs[indexMAX++]=new LineM(startP.x,startP.y,endP.x,endP.y,BrushColor,PenColor,0,MaxI,indexMAX);
						break;

					}
					MaxI++;
				}

			}
			Invalidate();
		}
	}

	CDialog::OnLButtonUp(nFlags, point);
}


void CDlgDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	int X1,Y1,X2,Y2,TYPE;
	bool FigDeletedTemp=false;
	COLORREF BrushC,PenC;
	startP=point;
	if(startP.x > PArea->x1 && startP.x < PArea->x2 && startP.y > PArea->y1 && startP.y < PArea->y2 )
	{
		///CHEAK IF CLICKED ON OBJECT


		int TempPID=MaxI;
		CurrentID=0;
		if (indexMAX > 0)
			while (TempPID >= 0)
			{

				//orly chacked if on object
				for ( CurrentID=indexMAX-1 ; CurrentID >= 0 ; CurrentID--)
				{
					if(figs[CurrentID]->pid == TempPID)
					{


						FigDeleted = false;
						TstartP.x=figs[CurrentID]->x1;
						TstartP.y=figs[CurrentID]->y1;
						TendP.x=figs[CurrentID]->x2;
						TendP.y=figs[CurrentID]->y2;

						int temp;
						if (TstartP.x > TendP.x)
						{
							temp=TstartP.x;
							TstartP.x=TendP.x;
							TendP.x=temp;
						}
						if (TstartP.y > TendP.y)
						{
							temp=TstartP.y;
							TstartP.y=TendP.y;
							TendP.y=temp;
						}
						// orly chacke if fig not deleted  
						if(startP.x > TstartP.x && startP.x < TendP.x && startP.y > TstartP.y && startP.y < TendP.y && figs[CurrentID]->action != 2)
						{

							for(int k=CurrentID+1 ; k < indexMAX ; k++)
							{
								if(figs[k]->pid == figs[CurrentID]->pid && figs[k]->action == 2 || figs[k]->pid == figs[CurrentID]->pid && figs[k]->action == 1)
									FigDeleted = true;
							}
							if(FigDeleted == false)
							{
								//orly ******DELETE********
								X1=figs[CurrentID]->x1;
								Y1=figs[CurrentID]->y1;
								X2=figs[CurrentID]->x2;
								Y2=figs[CurrentID]->y2;
								BrushC=figs[CurrentID]->Bcolor;
								PenC=figs[CurrentID]->Lcolor;
								TYPE=figs[CurrentID]->type;
								switch (TYPE)
								{
								case 1:
									figs[indexMAX++]=new RectangleM(X1,Y1,X2,Y2,BrushC,PenC,2,figs[CurrentID]->pid,indexMAX);
									break;
								case 2:
									figs[indexMAX++]=new EllipseM(X1,Y1,X2,Y2,BrushC,PenC,2,figs[CurrentID]->pid,indexMAX);
									break;
								case 3:
									figs[indexMAX++]=new LineM(X1,Y1,X2,Y2,BrushC,PenC,2,figs[CurrentID]->pid,indexMAX);
									break;
								}
								FigDeletedTemp=true;
								break;
							}
						}

					}

				}
				if(FigDeletedTemp==true)
					break;
				TempPID--;
			}


	}

	Invalidate();

	CDialog::OnRButtonDown(nFlags, point);
}


void CDlgDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(isPressed)
	{
		endP=point;
		Invalidate();
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CDlgDlg::OnBnClickedLine()
{
	// TODO: Add your control notification handler code here
	FigType=3;
	Invalidate();
}

void CDlgDlg::OnBnClickedRectangle()
{
	// TODO: Add your control notification handler code here
	FigType=1;
	Invalidate();
}

void CDlgDlg::OnBnClickedEllipse()
{
	// TODO: Add your control notification handler code here
	FigType=2;
	Invalidate();
}

void CDlgDlg::OnBnClickedMfccolorbutton1()
{
	//orly PEN COLOR
	// TODO: Add your control notification handler code here
	PenColor=CMFCColorButtonPen.GetColor();
	Invalidate();
}

void CDlgDlg::OnBnClickedMfccolorbutton3()
{
	//orly BRUSH COLOR 
	// TODO: Add your control notification handler code here
	BrushColor=CMFCColorButtonBrush.GetColor();
	Invalidate();

}

void CDlgDlg::OnBnClickedButton3()
{
	//orly UNDO BUTTON
	// TODO: Add your control notification handler code here
	if (indexMAX > 0)
	{
		if(figs[indexMAX-1]->action==0)
			MaxI--;
		indexMAX--;
	}
	Invalidate();
}

void CDlgDlg::OnBnClickedButton2()
{
	//REDO BUTTON
	// TODO: Add your control notification handler code here
	if (figs[indexMAX] != figs[indexMAX+1])
	{
		if(figs[indexMAX]->action==0)
			MaxI++;
		indexMAX++;
	}
	Invalidate();
}

void CDlgDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here



	CDialog::OnOK();
}

void CDlgDlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	//CMFCFile.GetCurrentMessage();
	CMFCFile.GetWindowTextA(FileName);




}

void CDlgDlg::OnBnClickedSavebutton()
{
	// TODO: Add your control notification handler code here

	if (indexMAXHistory > indexMAX)
		//ClearHistory();
	{
		for ( --indexMAXHistory  ; indexMAX <= indexMAXHistory ; indexMAXHistory--)
			delete figs[indexMAXHistory];
	}


	if (FileName=="0")
	{

		MessageBox("You did such a great job.  If you want to save your work, you must select a file.","Oh no.. Error ",0);

	}
	else{
		CFile file(_T(FileName), CFile::modeWrite | CFile::modeCreate);
		CArchive ar (&file, CArchive::store);

		ar<<MaxI;
		ar<<indexMAX;
		for(int i=0;i<indexMAX;i++)
		{
			ar<<figs[i]->x1;
			ar<<figs[i]->y1;
			ar<<figs[i]->x2;
			ar<<figs[i]->y2;
			ar<<figs[i]->type;
			ar<<figs[i]->Bcolor;
			ar<<figs[i]->Lcolor;
			ar<<figs[i]->pid;
			ar<<figs[i]->id;
			ar<<figs[i]->action;
		}

		ar.Close();
		file.Close();

	}

}

void CDlgDlg::OnBnClickedLoadbutton()
{
	// TODO: Add your control notification handler code here
	if (FileName=="0")
	{

		MessageBox("You did such a great job.  If you want to load your work, you must select a file.","Oh no.. Error ",0);

	}
	else
	{


		CFile file(_T(FileName), CFile::modeRead);
		CArchive ar (&file, CArchive::load);
		int ct;
		ar>>MaxI;
		ar>>ct;
		int X1,X2,Y1,Y2,TYPE,PID,ID,ACTION;
		COLORREF BrushC,PenC;
		for(int i=0;i<ct;i++)
		{

			ar>>X1;
			ar>>Y1;
			ar>>X2;
			ar>>Y2;
			ar>>TYPE;
			ar>>BrushC;
			ar>>PenC;
			ar>>PID;
			ar>>ID;
			ar>>ACTION;
			if(TYPE==1)
				figs[indexMAX++]=new RectangleM(X1,Y1,X2,Y2,BrushC,PenC,ACTION,PID,ID);
			if(TYPE==2)
				figs[indexMAX++]=new EllipseM(X1,Y1,X2,Y2,BrushC,PenC,ACTION,PID,ID);
			if(TYPE==3)
				figs[indexMAX++]=new LineM(X1,Y1,X2,Y2,BrushC,PenC,ACTION,PID,ID);

		}

		ar.Close();
		file.Close();
		Invalidate();
	}
}

void CDlgDlg::OnMButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnMButtonDown(nFlags, point);
}



//orly  move all objects

void CDlgDlg::OnBnClickedButtonup()
{
	// TODO: Add your control notification handler code here
	for (int i=0; i<indexMAXHistory ; i++)
	{
		figs[i]->y1 -= 100; 
		figs[i]->y2 -= 100;
	}
	Invalidate();
}


void CDlgDlg::OnBnClickedButtondown()
{
	// TODO: Add your control notification handler code here
	for (int i=0; i<indexMAXHistory ; i++)
	{
		figs[i]->y1 += 100; 
		figs[i]->y2 += 100;
	}
	Invalidate();

}


void CDlgDlg::OnBnClickedButtonright()
{
	// TODO: Add your control notification handler code here
	for (int i=0; i<indexMAXHistory ; i++)
	{
		figs[i]->x1 += 100; 
		figs[i]->x2 += 100;
	}
	Invalidate();



}


void CDlgDlg::OnBnClickedButtonleft()
{
	// TODO: Add your control notification handler code here
	for (int i=0; i<indexMAXHistory ; i++)
	{
		figs[i]->x1 -= 100; 
		figs[i]->x2 -= 100;
	}
	Invalidate();


}

