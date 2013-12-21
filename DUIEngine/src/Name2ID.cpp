#include "duistd.h"
#include "Name2ID.h"

namespace DuiEngine
{

	template<> DuiName2ID * Singleton<DuiName2ID>::ms_Singleton=0;

DuiName2ID::DuiName2ID(void)
{
}

DuiName2ID::~DuiName2ID(void)
{
}

}