// DlgDlg.h : header file
//

#if !defined(AFX_DLGDLG_H__D02F91E6_1066_4AA4_AE0B_1D16C986AE2C__INCLUDED_)
#define AFX_DLGDLG_H__D02F91E6_1066_4AA4_AE0B_1D16C986AE2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDlgDlg dialog
// added s
#include <vector>
//1 b
#include "Figure.h"
#include "afxcolorbutton.h"
#include "afxwin.h"
#include "afxeditbrowsectrl.h"
//1 e
using namespace std;
class CDlgDlg : public CDialog
{
	//orly Variables
	Figure *f,*PArea,* figs[100];
	int DistX,DistY,DistPX,DistPY,indexMAX,i,MaxI,TType,CurrentID,indexMAXHistory;
	bool isPressed, isMove,FigDeleted;
	CString FileName;
	CPoint startP,endP, TstartP,TendP;

	
	
	// Construction
public:
	CDlgDlg(CWnd* pParent = NULL);	// standard constructor
	//1 b
	~CDlgDlg();
	//1 e
// Dialog Data
	//{{AFX_DATA(CDlgDlg)
	enum { IDD = IDD_DLG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDlg)
	int FigType;

	COLORREF PenColor,BrushColor;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedLine();
	afx_msg void OnBnClickedRectangle();
	afx_msg void OnBnClickedEllipse();
	afx_msg void OnBnClickedMfccolorbutton1();
	COLORREF ColorButton;
//	CMFCColorButton CMFColorButtonPen;
	CMFCColorButton CMFCColorButtonPen;
	CMFCColorButton CMFCColorButtonBrush;
	afx_msg void OnBnClickedMfccolorbutton3();
	CButton CButtonUndo;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	CMFCEditBrowseCtrl CMFCFile;
	afx_msg void OnEnChangeMfceditbrowse1();
	
	afx_msg void OnBnClickedSavebutton();
	afx_msg void OnBnClickedLoadbutton();
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonup();
	afx_msg void OnBnClickedButtondown();
	afx_msg void OnBnClickedButtonright();
	afx_msg void OnBnClickedButtonleft();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDLG_H__D02F91E6_1066_4AA4_AE0B_1D16C986AE2C__INCLUDED_)
