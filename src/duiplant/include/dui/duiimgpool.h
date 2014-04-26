//////////////////////////////////////////////////////////////////////////
//  Class Name: DuiImgPool
// Description: Image Pool
//     Creator: Huang Jianxiong
//     Version: 2012.8.24 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <dui/duiimgbase.h>
#include <dui/duiresproviderbase.h>
#include <dui/DuiSingletonMap.h>

namespace DuiEngine
{

typedef CDuiImgBase * CDuiImgBasePtr;
class DUI_EXP DuiImgPool:public DuiSingletonMap<DuiImgPool,CDuiImgBasePtr,DuiResID>
{
public:
    DuiImgPool();
    virtual ~DuiImgPool();

    CDuiImgBase * GetImage(LPCTSTR pszImgName,LPCTSTR pszType=NULL);

protected:
    static void OnImageRemoved(const CDuiImgBasePtr & obj)
    {
        obj->Release();
    }
};

}//namespace DuiEngine