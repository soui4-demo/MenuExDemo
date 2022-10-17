#pragma once

namespace SOUI{

	class SLangView : public SListView
	{
		DEF_SOBJECT(SListView,L"langView")
	public:
		SLangView(void);
		~SLangView(void);

	protected:
		SIZE WINAPI GetDesiredSize(int nParentWid, int nParentHei) override;
	};

}
