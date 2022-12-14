// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"	

CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
}

CMainDlg::~CMainDlg()
{
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	return 0;
}
//TODO:消息映射
void CMainDlg::OnClose()
{
	SNativeWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}

void CMainDlg::OnBtnMenu()
{
	SWindow * btn = FindChildByID(R.id.btn_menu);
	CRect rc = btn->GetWindowRect();
	ClientToScreen2(&rc);
	SMenuEx menuTest;
	if(menuTest.LoadMenu(L"smenu:menu_test"))
	{
		int nRet = menuTest.TrackPopupMenu(TPM_RETURNCMD,rc.right,rc.top,m_hWnd);
		if(nRet == IDCANCEL)
		{
			PostQuitMessage(0);
		}
	}
}

#include <helper/SAdapterBase.h>
class SLangAdatper : public SAdapterBase
{
public:

	virtual int WINAPI getCount()
	{
		return 200;
	}

	virtual void WINAPI getView(int position, SItemPanel * pItem, SXmlNode xmlTemplate)
	{
		if(pItem->GetChildrenCount()==0)
		{
			pItem->InitFromXml(&xmlTemplate);
		}
		pItem->FindChildByName("txt_test")->SetWindowText(SStringT().Format(_T("language %d"),position+1));
	}

};

void CMainDlg::OnInitPopupMenu(SMenuEx * pMenu,int iItem)
{
	if(pMenu->GetContextHelpId()==100)
	{
		SMenuExItem *pItem = pMenu->GetMenuItem(0,FALSE);
		SLangView *pLangView = pItem->FindChildByName2<SLangView>("lv_language");
		if(pLangView)
		{
			SLangAdatper *pAdapter = new SLangAdatper;
			pLangView->SetAdapter(pAdapter);
			pAdapter->Release();
			pLangView->GetEventSet()->subscribeEvent(EventLVSelChanged::EventID,Subscriber(&CMainDlg::OnLangSelChange,this));
		}
	}
}

BOOL CMainDlg::OnLangSelChange(EventArgs*e)
{
	EventLVSelChanged *e2=sobj_cast<EventLVSelChanged>(e);
	SLOGI2("maindlg")<<"click lang:"<<e2->iNewSel;
	SMenuEx::EndMenu();
	SMessageBox(m_hWnd,SStringT().Format(_T("select language %d"),e2->iNewSel),_T("smenuex"),MB_OK);
	return true;
}

