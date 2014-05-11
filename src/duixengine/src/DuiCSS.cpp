#include <dui/duistd.h>
#include <dui/DuiCSS.h>
#include <dui/DuiSystem.h>
#include <dui/mybuffer.h>

namespace DuiEngine
{

template<> DuiCSS *Singleton<DuiCSS>::ms_Singleton =0;


BOOL DuiCSS::Init(LPCTSTR pszXmlName)
{
	pugi::xml_document xmlDoc;
	if(!DuiSystem::getSingleton().LoadXmlDocment(xmlDoc,pszXmlName)) return FALSE;
	return Init(xmlDoc.child("objattr"));
}

BOOL DuiCSS::Init( pugi::xml_node xmlNode )
{
	if (strcmp(xmlNode.name(), "objattr") != 0)
	{
		DUIASSERT(FALSE);
		return FALSE;
	}

	m_xmlRoot.append_copy(xmlNode);

	pugi::xml_node xmlObjAttr=m_xmlRoot.child("objattr").first_child();
	while(xmlObjAttr)
	{
		AddKeyObject(xmlObjAttr.name(),xmlObjAttr);
		xmlObjAttr=xmlObjAttr.next_sibling();
	}

	POSITION pos=m_mapNamedObj->GetStartPosition();
	while(pos)
	{
		CDuiMap<CDuiStringA,pugi::xml_node>::CPair *p=m_mapNamedObj->GetNext(pos);
		BuildClassAttribute(p->m_value,p->m_key);
	}

	return TRUE;
}

void DuiCSS::BuildClassAttribute( pugi::xml_node & xmlNode, LPCSTR pszClassName)
{
	LPCSTR pszBaseClassName=DuiWindowFactoryManager::getSingleton().BaseClassNameFromClassName(pszClassName);
	if(!pszBaseClassName) return;

	if(HasKey(pszBaseClassName))
	{
		pugi::xml_node xmlNodeAttrs = GetKeyObject(pszBaseClassName);
		pugi::xml_attribute attr=xmlNodeAttrs.first_attribute();
		while(attr)
		{
			if(!xmlNode.attribute(attr.name()))
				xmlNode.append_attribute(attr.name()).set_value(attr.value());
			attr=attr.next_attribute();
		}
	}
	BuildClassAttribute(xmlNode,pszBaseClassName);
}

pugi::xml_node DuiCSS::GetDefAttribute(LPCSTR pszClassName )
{
	DUIASSERT(pszClassName);
	if(!DuiWindowFactoryManager::getSingletonPtr()->HasKey(pszClassName))
		return pugi::xml_node();//节点是窗口时才有默认属性
	return _GetDefAttribute(pszClassName);
}

pugi::xml_node DuiCSS::_GetDefAttribute(LPCSTR pszClassName )
{
	if(!HasKey(pszClassName))
	{
		LPCSTR pszBaseClassName=DuiWindowFactoryManager::getSingleton().BaseClassNameFromClassName(pszClassName);
		if(!pszBaseClassName) return pugi::xml_node();
		return _GetDefAttribute(pszBaseClassName);
	}else
	{
		return GetKeyObject(pszClassName);
	}
}


}//namespace DuiEngine

