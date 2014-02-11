//////////////////////////////////////////////////////////////////////////
//   File Name: duiturn3dview.h
// Description: CDuiTurn3dView
//     Creator: ZhangZhiBin QQ->276883782
//     Version: 2014.02.06 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once 

namespace DuiEngine
{
  class CDuiTurn3dView
  {
  public:
    CDuiTurn3dView();
    virtual ~CDuiTurn3dView();

    void SetFrontSide(CDuiStringA strFrontSide);
    void SetBackSide(CDuiStringA strBackSide);
    void SetCartoon(CDuiStringA strCartoon);
    void SetDuiWindow(CDuiWindow* pDuiWindow);
    void SetImage3dView(CDuiStringA str3dView);
    void SetZStep(int nZStep);
    void SetYStep(int nYStep);
    void SetIdEvent(UINT_PTR idEvent);
    void SetElapse(UINT uElapse);
    void Turn(BOOL bTurn2Front);


    void OnTimer(UINT_PTR idEvent);

    void ShowFrame();                     //显示翻转动画中的其中一帧
    BEGIN_MSG_MAP_EX(CDuiTurn3dView)
      MSG_WM_TIMER(OnTimer)
    END_MSG_MAP()
  protected:
    HBITMAP          m_hBitmapBefore;      //翻转时的正面的bitmap
    HBITMAP          m_hBitmapAfter;       //翻转时的反面的bitmap
    BOOL             m_bTurn2Front;        //是否翻转到正面
    
    int              m_nFrameIndex;        //翻转到第几帧
    LPSTR            m_lpDesk;             //指向登录界面下方的背景的指针
    BITMAPINFOHEADER m_bih;                //与窗口兼容的bitmap的图像头
    int              m_nZStep;             //z轴的每一步距离
    int              m_nYStep;             //每次动画绕Y轴旋转m_nYStep角度
    CDuiStringA      m_strFrontSide;       //正面的dlg的名称
    CDuiStringA      m_strBackSide;        //反面的dlg的名称
    CDuiStringA      m_strCartoon;         //动画的dlg的名称
    CDuiStringA      m_strImage3dView;     //image3dview用于处理动画翻转，此处定义其名称
    UINT_PTR         m_idEvent;            //开启动画的时钟的id
    UINT             m_uElapse;            //时钟的间隔
    CDuiWindow*      m_pDuiWindow;         //关联的duiwindow
  };
}