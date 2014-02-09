#pragma once

namespace DuiEngine
{
	class CImgView :
		public CDuiWindow
	{
		DUIOBJ_DECLARE_CLASS_NAME(CImgView, "imgview")
	public:
		CImgView(void);
		~CImgView(void);

		enum VIEWTYPE
		{
			VT_IMGLST,
			VT_IMGFRAME,
			VT_SCROLL,
			VT_BUTTON,
		};

		void SetViewType(VIEWTYPE vt);

		BOOL SetImageFile(LPCTSTR pszFileName);
	
		void SetStates(int nStates);

		void SetMargin(CRect rcMargin);

		void SetTile(BOOL bTile);

		void SetVertical(BOOL bVertical);
	private:
		CDuiSkinBase * GetSkin();

		void OnPaint(CDCHandle dc);

		DUIWIN_BEGIN_MSG_MAP()
			MSG_WM_PAINT(OnPaint)
		DUIWIN_END_MSG_MAP()

		DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
			DUIWIN_COLOR_ATTRIBUTE("crsep", m_crSep, TRUE)
			DUIWIN_COLOR_ATTRIBUTE("crframe", m_crFrame, TRUE)
			DUIWIN_ENUM_ATTRIBUTE("viewtype", VIEWTYPE, TRUE)
				DUIWIN_ENUM_VALUE("imglst",VT_IMGLST)
				DUIWIN_ENUM_VALUE("imgframe",VT_IMGFRAME)
				DUIWIN_ENUM_VALUE("button",VT_BUTTON)
				DUIWIN_ENUM_VALUE("scrollbar",VT_SCROLL)
			DUIWIN_ENUM_END(m_viewType)
		DUIWIN_DECLARE_ATTRIBUTES_END()

		COLORREF m_crSep;
		COLORREF m_crFrame;

		CDuiImgX	m_img;

		VIEWTYPE	m_viewType;

		CDuiSkinImgFrame m_skinImgFrame;
		CDuiSkinImgList m_skinImgList;
		CDuiSkinImgList m_skinScroll;
		CDuiSkinButton  m_skinButton;
	};

}
