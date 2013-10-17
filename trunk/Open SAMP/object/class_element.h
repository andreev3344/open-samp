#ifndef __CLASS_ELEMENT_H_
#define __CLASS_ELEMENT_H_

#define ELEMENT_TYPE_NULL			0
#define ELEMENT_TYPE_ROOT			1
#define ELEMENT_TYPE_OBJECT			2
#define ELEMENT_TYPE_RADAR_ICON		3
#define ELEMENT_TYPE_RADAR_ZONE		4
#define ELEMENT_TYPE_PICKUP			5
#define ELEMENT_TYPE_VIRTUAL		6

class CElement : public CReferenceCounter
{
protected:

	uint16_t m_uint16_ElementOwner; // will became an element when player will be done.

	uint32_t m_uint32_ElementIndex;
	uint8_t m_uint8_ElementType;

	uint32_t m_uint32_ModelIndex;

	CElement* m_Parent;
	list< CElement* > m_Children;

	tVector m_Position;
	tVector m_RelativePosition;

	tVector m_Rotation;

	float m_float_Health;

	uint32_t m_uint32_VirtualWorld;

public:

	CElement ( uint8_t a_uint8_ElementType = ELEMENT_TYPE_NULL )
	{
		this->m_uint16_ElementOwner = 0;

		this->m_uint32_ElementIndex = -1;
		this->m_uint8_ElementType = ELEMENT_TYPE_NULL;

		this->m_uint32_ModelIndex = -1;

		this->m_Parent = NULL;
		
		this->m_Position.X = 0.0f;
		this->m_Position.Y = 0.0f;
		this->m_Position.Z = 0.0f;

		this->m_RelativePosition.X = 0.0f;
		this->m_RelativePosition.Y = 0.0f;
		this->m_RelativePosition.Z = 0.0f;

		this->m_Rotation.X = 0.0f;
		this->m_Rotation.Y = 0.0f;
		this->m_Rotation.Z = 0.0f;
	};

	virtual ~CElement();

	void SetElementIndex ( uint32_t a_uint32_ElementIndex );
	uint32_t GetElementIndex ( void );

	void SetElementType ( uint8_t a_uint8_ElementType );
	uint8_t GetElementType ( void );

	virtual void SetElementOwner ( uint16_t a_uint16_ElementOwner );
	virtual uint16_t GetElementOwner ( void );

	virtual bool SetElementModel ( uint32_t a_uint32_ModelIndex );
	virtual uint32_t GetElementModel ( void );

	void SetParent ( CElement* a_Element );
	CElement* GetParent ( void );

	void AddChild ( CElement* a_Element );

	list< CElement* > GetChildren ( void ) { return this->m_Children; };

	void Remove ( void );
	void RemoveChildren ( void );
	void RemoveChild ( CElement* a_Element );

	virtual TiXmlElement* SerializeAttribute ( void );
	virtual void UnSerializeAttribute ( TiXmlElement* a_XmlElement );

	virtual void SetRotation ( tVector* a_Rotation );
	virtual tVector* GetRotation ( void );
	
	virtual void SetPosition ( tVector* a_Position );
	virtual tVector* GetPosition ( void );
	virtual void SetAbsolutePosition ( tVector* a_AbsolutePosition );
	virtual tVector* GetAbsolutePosition ( void );

	virtual void SetHealth ( float a_float_Health );
	virtual float GetHealth ( void );

	virtual void SetVirtualWorld ( uint32_t a_uint32_VirtualWorld );
	virtual uint32_t GetVirtualWorld ( void );

	float GetDistanceFrom ( tVector* a_Position );
	float GetDistanceFrom ( CElement* a_Element );

	virtual void InitializeForPlayer ( uint16_t a_uint16_PlayerIndex ) { };
	virtual void InitializeForAll ( void ) { };

	virtual void ShowForPlayer ( uint16_t a_uint16_PlayerIndex );
	virtual void ShowForAll ( void );

	virtual void HideForPlayer ( uint16_t a_uint16_PlayerIndex ) { };
	virtual void HideForAll ( void ) { };

	virtual uint8_t Process ( float a_float_Time ) { return -1; };

	virtual void UpdatePosition ( void );

};

// __CLASS_ELEMENT_H_
#endif