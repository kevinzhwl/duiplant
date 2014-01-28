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

		BOOL SetImageFile(LPCTSTR pszFileName);
	
		void SetStates(int nStates){m_nStates=nStates;}

		void SetMargin(CRect rcMargin){m_rcMargin=rcMargin;}

		void SetTile(BOOL bTile){m_bTile=bTile;}

		void SetVertical(BOOL bVertical){m_bVertical=bVertical;}
	private:
		void OnPaint(CDCHandle dc);

		DUIWIN_BEGIN_MSG_MAP()
			MSG_WM_PAINT(OnPaint)
		DUIWIN_END_MSG_MAP()

		CDuiStringT m_strFileName;
		CDuiImgX	m_img;
		int			m_nStates;
		CRect		m_rcMargin;
		BOOL		m_bTile;
		BOOL		m_bVertical;
	};

}
