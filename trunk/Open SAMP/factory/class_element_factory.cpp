#include "../main.h"
#include "class_element_factory.h"
/*
CElement* CElementFactory::UnSerializeElement ( TiXmlElement* a_XmlElement )
{
	return NULL;
}
*/
TiXmlElement* CElementFactory::UnSerializeElementChild ( TiXmlElement* a_XmlElement, uint16_t a_uint16_ElementOwner, CElement* a_Parent )
{
	TiXmlElement* l_XmlElement = a_XmlElement->FirstChildElement();
	while ( l_XmlElement )
	{
		CElement* l_Element = NULL;
		if ( strcmp ( "sampmap", l_XmlElement->Value() ) == 0 )
		{
			logprintf ( "[Xml]-> Element: <sampmap>" );
		}
		else if ( strcmp ( XML_ELEMENT_VIRTUAL, l_XmlElement->Value() ) == 0 )
		{
			CElement* l_ElementVirtual = new CElement ( ELEMENT_TYPE_VIRTUAL );
			if ( l_ElementVirtual )
			{
				CElement* l_Parent = ( a_Parent ? a_Parent : this->m_RootElement );
				if ( l_Parent )
					l_Parent->AddChild ( l_ElementVirtual );

				l_ElementVirtual->UnSerializeAttribute ( l_XmlElement );

				this->m_VirtualElements.push_back ( l_ElementVirtual );
				this->m_Elements.push_back ( l_ElementVirtual );

				l_ElementVirtual->SetElementIndex ( this->m_Elements.size() - 1 );

				if ( a_uint16_ElementOwner == 0 )
					l_ElementVirtual->ShowForAll();
				else
					l_ElementVirtual->ShowForPlayer ( a_uint16_ElementOwner );

				l_Element = ( CElement* )l_ElementVirtual;
			}
		}
		else if ( strcmp ( XML_ELEMENT_OBJECT, l_XmlElement->Value() ) == 0 )
		{
			CObject* l_ElementObject = new CObject();
			if ( l_ElementObject )
			{
				CElement* l_Parent = ( a_Parent ? a_Parent : this->m_RootElement );
				if ( l_Parent )
					l_Parent->AddChild ( l_ElementObject );

				l_ElementObject->UnSerializeAttribute ( l_XmlElement );

				this->m_ObjectElements.push_back ( l_ElementObject );
				this->m_Elements.push_back ( l_ElementObject );

				l_ElementObject->SetElementIndex ( this->m_Elements.size() - 1 );

				if ( a_uint16_ElementOwner == 0 )
					l_ElementObject->ShowForAll();
				else
					l_ElementObject->ShowForPlayer ( a_uint16_ElementOwner );

				l_Element = ( CElement* )l_ElementObject;
			}
		}
		else if ( strcmp ( XML_ELEMENT_RADARICON, l_XmlElement->Value() ) == 0 )
		{
			CRadarIcon* l_ElementRadarIcon = new CRadarIcon();
			if ( l_ElementRadarIcon )
			{
				CElement* l_Parent = ( a_Parent ? a_Parent : this->m_RootElement );
				if ( l_Parent )
					l_Parent->AddChild ( l_ElementRadarIcon );

				l_ElementRadarIcon->UnSerializeAttribute ( l_XmlElement );

				this->m_RadarIconElements.push_back ( l_ElementRadarIcon );
				this->m_Elements.push_back ( l_ElementRadarIcon );

				l_ElementRadarIcon->SetElementIndex ( this->m_Elements.size() - 1 );

				if ( a_uint16_ElementOwner == 0 )
					l_ElementRadarIcon->ShowForAll();
				else
					l_ElementRadarIcon->ShowForPlayer ( a_uint16_ElementOwner );

				l_Element = ( CElement* )l_ElementRadarIcon;
			}
		}

		if ( l_Element )
			this->UnSerializeElementChild ( l_XmlElement, a_uint16_ElementOwner, l_Element );

		l_XmlElement = l_XmlElement->NextSiblingElement();
	}
	return NULL;
}

CElement* CElementFactory::CreateFromFile ( int8_t* a_int8_FilePath, uint16_t a_uint16_ElementOwner, tVector* a_Position, CElement* a_Parent )
{
	TiXmlDocument* l_XmlDocument = new TiXmlDocument ( a_int8_FilePath );
	if ( l_XmlDocument )
	{
		if ( !l_XmlDocument->LoadFile() )
		{
			logprintf ( "[Error] Could not Load XmlFile (%s). Error: \"%s\"", a_int8_FilePath, l_XmlDocument->ErrorDesc() );
			return NULL;
		}

		TiXmlElement* l_XmlElement = l_XmlDocument->FirstChildElement();
		while ( l_XmlElement )
		{
			this->UnSerializeElementChild ( l_XmlElement, a_uint16_ElementOwner, a_Parent );

			l_XmlElement = l_XmlElement->NextSiblingElement();
		}
	}
	return NULL;
}

CElement* CElementFactory::CreateVirtual ( uint16_t a_uint16_ElementOwner, tVector* a_Position, CElement* a_Parent )
{
	CElement* l_ElementVirtual = new CElement ( ELEMENT_TYPE_VIRTUAL );
	if ( l_ElementVirtual )
	{
		CElement* l_Parent = ( a_Parent ? a_Parent : this->m_RootElement );
		if ( l_Parent )
			l_Parent->AddChild ( l_ElementVirtual );

		l_ElementVirtual->SetPosition ( a_Position );

		this->m_VirtualElements.push_back ( l_ElementVirtual );
		this->m_Elements.push_back ( l_ElementVirtual );

		l_ElementVirtual->SetElementIndex ( this->m_Elements.size() - 1 );

		if ( a_uint16_ElementOwner == 0 )
			l_ElementVirtual->ShowForAll();
		else
			l_ElementVirtual->ShowForPlayer ( a_uint16_ElementOwner );

		return l_ElementVirtual;
	}
	return NULL;
}

CObject* CElementFactory::CreateObject ( uint16_t a_uint16_ElementOwner, uint32_t a_uint32_ModelIndex, tVector* a_Position, tVector* a_Rotation, CElement* a_Parent )
{
	CObject* l_ElementObject = new CObject ( a_uint32_ModelIndex );
	if ( l_ElementObject )
	{
		CElement* l_Parent = ( a_Parent ? a_Parent : this->m_RootElement );
		if ( l_Parent )
			l_Parent->AddChild ( l_ElementObject );

		l_ElementObject->SetPosition ( a_Position );
		l_ElementObject->SetRotation ( a_Rotation );

		this->m_ObjectElements.push_back ( l_ElementObject );
		this->m_Elements.push_back ( l_ElementObject );

		l_ElementObject->SetElementIndex ( this->m_Elements.size() - 1 );

		if ( a_uint16_ElementOwner == 0 )
			l_ElementObject->ShowForAll();
		else
			l_ElementObject->ShowForPlayer ( a_uint16_ElementOwner );

		return l_ElementObject;
	}
	return NULL;
}
	
CPickup* CElementFactory::CreatePickup ( uint16_t a_uint16_ElementOwner, uint32_t a_uint32_ModelIndex, uint32_t a_uint32_PickupType, tVector* a_Position, CElement* a_Parent )
{
	CPickup* l_Pickup = new CPickup ( a_uint32_ModelIndex, a_uint32_PickupType );
	if ( l_Pickup )
	{
		CElement* l_Parent = ( a_Parent ? a_Parent : this->m_RootElement );
		if ( l_Parent )
			l_Parent->AddChild ( l_Pickup );

		l_Pickup->SetPosition ( a_Position );

		this->m_PickupElements.push_back ( l_Pickup );
		this->m_Elements.push_back ( l_Pickup );

		l_Pickup->SetElementIndex ( this->m_Elements.size() - 1 );

		if ( a_uint16_ElementOwner == 0 )
			l_Pickup->ShowForAll();
		else
			l_Pickup->ShowForPlayer ( a_uint16_ElementOwner );

		return l_Pickup;
	}
	return NULL;
}

CRadarIcon* CElementFactory::CreateRadarIcon ( uint16_t a_uint16_ElementOwner, uint32_t a_uint32_ModelIndex, uint8_t a_uint8_RadarIconType, tVector* a_Position, uint32_t a_uint32_Color, CElement* a_Parent )
{
	CRadarIcon* l_ElementRadarIcon = new CRadarIcon ( a_uint32_ModelIndex, a_uint32_Color, a_uint8_RadarIconType );
	if ( l_ElementRadarIcon )
	{
		CElement* l_Parent = ( a_Parent ? a_Parent : this->m_RootElement );
		if ( l_Parent )
			l_Parent->AddChild ( l_ElementRadarIcon );

		l_ElementRadarIcon->SetPosition ( a_Position );

		this->m_RadarIconElements.push_back ( l_ElementRadarIcon );
		this->m_Elements.push_back ( l_ElementRadarIcon );

		l_ElementRadarIcon->SetElementIndex ( this->m_Elements.size() - 1 );
		
		if ( a_uint16_ElementOwner == 0 )
			l_ElementRadarIcon->ShowForAll();
		else
			l_ElementRadarIcon->ShowForPlayer ( a_uint16_ElementOwner );

		return l_ElementRadarIcon;
	}
	return NULL;
}

CRadarZone* CElementFactory::CreateRadarZone ( uint16_t a_uint16_ElementOwner, tVector* a_Position, tVector* a_Size, uint32_t a_uint32_Color, CElement* a_Parent )
{
	CRadarZone* l_ElementRadarZone = new CRadarZone ( a_Position, a_Size, a_uint32_Color );
	if ( l_ElementRadarZone )
	{
		CElement* l_Parent = ( a_Parent ? a_Parent : this->m_RootElement );
		if ( l_Parent )
			l_Parent->AddChild ( l_ElementRadarZone );

		this->m_RadarZoneElements.push_back ( l_ElementRadarZone );
		this->m_Elements.push_back ( l_ElementRadarZone );

		l_ElementRadarZone->SetElementIndex ( this->m_Elements.size() - 1 );

		if ( a_uint16_ElementOwner == 0 )
			l_ElementRadarZone->ShowForAll();
		else
			l_ElementRadarZone->ShowForPlayer ( a_uint16_ElementOwner );

		return l_ElementRadarZone;
	}
	return NULL;
}

CElement* CElementFactory::Clone ( CElement* a_Element, CElement* a_Parent )
{
	CElement* l_Element = NULL;

	switch ( a_Element->GetElementType() )
	{
		case ELEMENT_TYPE_VIRTUAL:
		{
			CElement* l_ElementVirtual = new CElement ( ELEMENT_TYPE_VIRTUAL );
			if ( l_ElementVirtual )
			{
				if ( a_Parent )
				{
					a_Parent->AddChild ( l_ElementVirtual );
				}
				else
				{
					a_Element->GetParent()->AddChild ( l_ElementVirtual );
				}

				l_ElementVirtual->SetPosition ( a_Element->GetPosition() );

				this->m_VirtualElements.push_back ( l_ElementVirtual );
				this->m_Elements.push_back ( l_ElementVirtual );

				l_ElementVirtual->SetElementIndex ( this->m_Elements.size() - 1 );

				if ( a_Element->GetElementOwner() == 0 )
					l_ElementVirtual->ShowForAll();
				else
					l_ElementVirtual->ShowForPlayer ( a_Element->GetElementOwner() );

				l_Element = ( CElement* )l_ElementVirtual;
			}
			break;
		}
		case ELEMENT_TYPE_OBJECT:
		{
			CObject* l_ElementObject = new CObject ( a_Element->GetElementModel() );
			if ( l_ElementObject )
			{
				if ( a_Parent )
				{
					a_Parent->AddChild ( l_ElementObject );
				}
				else
				{
					a_Element->GetParent()->AddChild ( l_ElementObject );
				}

				l_ElementObject->SetPosition ( a_Element->GetPosition() );
				l_ElementObject->SetRotation ( a_Element->GetRotation() );

				this->m_ObjectElements.push_back ( l_ElementObject );
				this->m_Elements.push_back ( l_ElementObject );

				l_ElementObject->SetElementIndex ( this->m_Elements.size() - 1 );

				if ( a_Element->GetElementOwner() == 0 )
					l_ElementObject->ShowForAll();
				else
					l_ElementObject->ShowForPlayer ( a_Element->GetElementOwner() );

				l_Element = ( CElement* )l_ElementObject;
			}
			break;
		}
		case ELEMENT_TYPE_PICKUP:
		{
			CPickup* l_Pickup = new CPickup ( a_Element->GetElementModel(), ( ( CPickup* )a_Element )->m_uint32_PickupType );
			if ( l_Pickup )
			{
				if ( a_Parent )
				{
					a_Parent->AddChild ( l_Pickup );
				}
				else
				{
					a_Element->GetParent()->AddChild ( l_Pickup );
				}

				l_Pickup->SetPosition ( a_Element->GetPosition() );

				this->m_PickupElements.push_back ( l_Pickup );
				this->m_Elements.push_back ( l_Pickup );

				l_Pickup->SetElementIndex ( this->m_Elements.size() - 1 );

				if ( a_Element->GetElementOwner() == 0 )
					l_Pickup->ShowForAll();
				else
					l_Pickup->ShowForPlayer ( a_Element->GetElementOwner() );

				l_Element = ( CElement* )l_Pickup;
			}
			break;
		}
		case ELEMENT_TYPE_RADAR_ICON:
		{	
			CRadarIcon* l_ElementRadarIcon = new CRadarIcon ( a_Element->GetElementModel(), ( ( CRadarIcon* )a_Element )->GetColor().RGBA, ( ( CRadarIcon* )a_Element )->GetRadarIconType() );
			if ( l_ElementRadarIcon )
			{
				if ( a_Parent )
				{
					a_Parent->AddChild ( l_ElementRadarIcon );
				}
				else
				{
					a_Element->GetParent()->AddChild ( l_ElementRadarIcon );
				}

				l_ElementRadarIcon->SetPosition ( a_Element->GetPosition() );

				this->m_RadarIconElements.push_back ( l_ElementRadarIcon );
				this->m_Elements.push_back ( l_ElementRadarIcon );

				l_ElementRadarIcon->SetElementIndex ( this->m_Elements.size() - 1 );
				
				if ( a_Element->GetElementOwner() == 0 )
					l_ElementRadarIcon->ShowForAll();
				else
					l_ElementRadarIcon->ShowForPlayer ( a_Element->GetElementOwner() );

				l_Element = ( CElement* )l_ElementRadarIcon;
			}
		}
		case ELEMENT_TYPE_RADAR_ZONE:
		{	
			CRadarZone* l_ElementRadarZone = new CRadarZone ( a_Element->GetPosition(), ( ( CRadarZone* )a_Element )->GetSize(), ( ( CRadarZone* )a_Element )->GetColor() );
			if ( l_ElementRadarZone )
			{
				if ( a_Parent )
				{
					a_Parent->AddChild ( l_ElementRadarZone );
				}
				else
				{
					a_Element->GetParent()->AddChild ( l_ElementRadarZone );
				}

				l_ElementRadarZone->SetFlashingColor ( ( ( CRadarZone* )a_Element )->GetFlashingColor() );
				l_ElementRadarZone->SetFlashing ( ( ( CRadarZone* )a_Element )->IsFlashing() );


				this->m_RadarZoneElements.push_back ( l_ElementRadarZone );
				this->m_Elements.push_back ( l_ElementRadarZone );

				l_ElementRadarZone->SetElementIndex ( this->m_Elements.size() - 1 );

				if ( a_Element->GetElementOwner() == 0 )
					l_ElementRadarZone->ShowForAll();
				else
					l_ElementRadarZone->ShowForPlayer ( a_Element->GetElementOwner() );

				l_Element = ( CElement* )l_ElementRadarZone;
			}
		}
		default:
		{

		}
	}

	list< CElement* > l_Children = a_Element->GetChildren();
	list< CElement* >::iterator l_IterChildren = l_Children.begin();
	for ( ; l_IterChildren != l_Children.end(); l_IterChildren++ )
	{
		this->Clone ( *l_IterChildren, l_Element );
	}
	return l_Element;
}

CElement* CElementFactory::GetElementFromIndex ( uint32_t a_uint32_ElementIndex )
{
	if ( a_uint32_ElementIndex == -1 )
		return this->m_RootElement;

	list< CElement* > ::iterator l_IterElements = this->m_Elements.begin();
	for ( ; l_IterElements != this->m_Elements.end(); l_IterElements++ )
	{
		if ( ( *l_IterElements )->GetElementIndex() == a_uint32_ElementIndex )
			return ( *l_IterElements );
	}
	return NULL;
}

void CElementFactory::InitializeForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	list< CElement* > ::iterator l_IterElements = this->m_Elements.begin();
	for ( ; l_IterElements != this->m_Elements.end(); l_IterElements++ )
	{
		( *l_IterElements )->InitializeForPlayer ( a_uint16_PlayerIndex );
	}
}

void CElementFactory::Process ( float a_float_Time )
{
	list< CElement* > ::iterator l_IterElements = this->m_Elements.begin();
	for ( ; l_IterElements != this->m_Elements.end(); l_IterElements++ )
	{
		uint8_t l_Return = ( *l_IterElements )->Process ( a_float_Time );
		if ( l_Return & 1 ) 
		{
			__NetGame->filterscriptsManager->OnObjectMoved ( ( uint16_t )( ( ( uint32_t )( *l_IterElements ) ) % 400 ) );
			if ( __NetGame->gamemodeManager ) __NetGame->gamemodeManager->OnObjectMoved ( ( uint16_t )( ( ( uint32_t )( *l_IterElements ) ) % 400 ) );
		}
	}
}