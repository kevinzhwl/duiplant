#pragma once

namespace DuiEngine
{

	struct IDuiRef
	{
		virtual int AddRef()=NULL;

		virtual int Release()=NULL;

		virtual void OnFinalRelease()=NULL;
	};

	class DUI_EXP CDuiRef : public IDuiRef
	{
	public:
		CDuiRef():m_nRef(1)
		{
		}

		~CDuiRef()
		{

		}

		int AddRef()
		{
			return ++m_nRef;
		}

		int Release()
		{
			int nRet=--m_nRef;
			if(nRet==0)
			{
				OnFinalRelease();
			}
			return nRet;
		}

	protected:
		virtual void OnFinalRelease()=NULL;

		int m_nRef;
	};

}//namespace DuiEngine