#include "StdAfx.h"
#include "SLangView.h"

namespace SOUI
{

	SLangView::SLangView(void)
	{
	}

	SLangView::~SLangView(void)
	{
	}

	SIZE SLangView::GetDesiredSize(int nParentWid, int nParentHei)
	{
		ILvAdapter *adapter = GetAdapter();
		IListViewItemLocator *pLocator=GetItemLocator();
		CSize szRet = __super::GetDesiredSize(nParentWid,nParentHei);
		if(!adapter || adapter->getCount()==0 || !pLocator)
		{
			szRet.cy = 30;
		}else
		{
			int nCount = adapter->getCount();
			int nItemHei = pLocator->GetItemHeight(0);
			szRet.cy = nItemHei*nCount;
			if(nParentHei<0)
				nParentHei = 900;
			szRet.cy = smin(nParentHei,szRet.cy);
			szRet.cx = 300;
		}
		return szRet;
	}

}
