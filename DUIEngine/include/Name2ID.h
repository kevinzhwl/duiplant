#pragma once
#include "DUISingleton.h"

namespace DuiEngine
{
	class DUI_EXP DuiName2ID : public Singleton<DuiName2ID>
	{
	public:
		DuiName2ID(void);
		~DuiName2ID(void);

		UINT Name2ID(LPCSTR pszName){return 0;}
		BOOL Init(pugi::xml_node xmlNode){return FALSE;}
	};
}

