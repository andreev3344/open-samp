#ifndef __CLASS_ELEMENT_FACTORY_H_
#define __CLASS_ELEMENT_FACTORY_H_

#include <list>

using namespace std;	

#define XML_ELEMENT_VIRTUAL			"virtual"
#define XML_ELEMENT_OBJECT			"object"
#define XML_ELEMENT_RADARICON		"radaricon"

class CElementFactory
{
private:

	CElement* m_RootElement;
	
	list< CElement* > m_Elements;

	list< CElement* > m_VirtualElements;

	list< CObject* > m_ObjectElements;
	list< CPickup* > m_PickupElements;

	list< CRadarIcon* > m_RadarIconElements;
	list< CRadarZone* > m_RadarZoneElements;

public:

	CElementFactory()
	{
		this->m_RootElement = new CElement ( ELEMENT_TYPE_ROOT );
	};

	~CElementFactory()
	{
		if ( this->m_RootElement )
			this->m_RootElement->Drop();
	};
	
	//CElement* UnSerializeElement ( TiXmlElement* a_XmlElement );

	TiXmlElement* UnSerializeElementChild ( TiXmlElement* a_XmlElement, uint16_t a_uint16_ElementOwner, CElement* a_Parent );
	CElement* CreateFromFile ( int8_t* a_int8_FilePath, uint16_t a_uint16_ElementOwner, tVector* a_Position, CElement* a_Parent = NULL );
	

	CElement* CreateVirtual ( uint16_t a_uint16_ElementOwner, tVector* a_Position, CElement* a_Parent = NULL );
	
	CObject* CreateObject ( uint16_t a_uint16_ElementOwner, uint32_t a_uint32_ModelIndex, tVector* a_Position, tVector* a_Rotation, CElement* a_Parent = NULL );
	CPickup* CreatePickup ( uint16_t a_uint16_ElementOwner, uint32_t a_uint32_ModelIndex, uint32_t a_uint32_PickupType, tVector* a_Position, CElement* a_Parent = NULL );
	CRadarIcon* CreateRadarIcon ( uint16_t a_uint16_ElementOwner, uint32_t a_uint32_ModelIndex, uint8_t a_uint8_RadarIconType, tVector* a_Position, uint32_t a_uint32_Color, CElement* a_Parent = NULL );
	CRadarZone* CreateRadarZone ( uint16_t a_uint16_ElementOwner, tVector* a_Position, tVector* a_Size, uint32_t a_uint32_Color, CElement* a_Parent = NULL );

	CElement* Clone ( CElement* a_Element, CElement* a_Parent = NULL );
	CElement* GetElementFromIndex ( uint32_t a_uint32_ElementIndex );

	void InitializeForPlayer ( uint16_t a_uint16_PlayerIndex );

	void Process ( float a_float_Time );
};

// __CLASS_ELEMENT_FACTORY_H_
#endif