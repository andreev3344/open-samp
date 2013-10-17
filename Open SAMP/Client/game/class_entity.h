

#ifndef __CLASS_ENTITY_H__
#define __CLASS_ENTITY_H__

class CEntitySA : public CPlaceableSA
{
#pragma pack( 1 )
public:
	// TODO Toufik : Faire des getter / setter
		
	void*		renderWare_Object;	// + 0x0018


	// FROM MTA SAN ANDREAS PROJECT !
	// http://code.google.com/p/mtasa-blue/
    /********** BEGIN CFLAGS **************/
    uint32_t bUsesCollision : 1;			// does entity use collision
    uint32_t bCollisionProcessed : 1;		// has object been processed by a ProcessEntityCollision function
    uint32_t bIsStatic : 1;					// is entity static
    uint32_t bHasContacted : 1;				// has entity processed some contact forces
    uint32_t bIsStuck : 1;					// is entity stuck
    uint32_t bIsInSafePosition : 1;			// is entity in a collision free safe position
    uint32_t bWasPostponed : 1;				// was entity control processing postponed
    uint32_t bIsVisible : 1;				//is the entity visible
    
    uint32_t bIsBIGBuilding : 1;			// Set if this entity is a big building
    uint32_t bRenderDamaged : 1;			// use damaged LOD models for objects with applicable damage
    uint32_t bStreamingDontDelete : 1;		// Dont let the streaming remove this 
    uint32_t bRemoveFromWorld : 1;			// remove this entity next time it should be processed
    uint32_t bHasHitWall : 1;				// has collided with a building (changes subsequent collisions)
    uint32_t bImBeingRendered : 1;			// don't delete me because I'm being rendered
    uint32_t bDrawLast :1;					// draw object last
    uint32_t bDistanceFade :1;				// Fade entity because it is far away
    
    uint32_t bDontCastShadowsOn : 1;		// Dont cast shadows on this object
    uint32_t bOffscreen : 1;				// offscreen flag. This can only be trusted when it is set to true
    uint32_t bIsStaticWaitingForCollision : 1; // this is used by script created entities - they are static until the collision is loaded below them
    uint32_t bDontStream : 1;				// tell the streaming not to stream me
    uint32_t bUnderwater : 1;				// this object is underwater change drawing order
    uint32_t bHasPreRenderEffects : 1;		// Object has a prerender effects attached to it
    uint32_t bIsTempBuilding : 1;			// whether or not the building is temporary (i.e. can be created and deleted more than once)
    uint32_t bDontUpdateHierarchy : 1;		// Don't update the aniamtion hierarchy this frame
    
    uint32_t bHasRoadsignText : 1;			// entity is roadsign and has some 2deffect text stuff to be rendered
    uint32_t bDisplayedSuperLowLOD : 1;
    uint32_t bIsProcObject : 1;				// set object has been generate by procedural object generator
    uint32_t bBackfaceCulled : 1;			// has backface culling on
    uint32_t bLightObject : 1;				// light object with directional lights
    uint32_t bUnimportantStream : 1;		// set that this object is unimportant, if streaming is having problems
    uint32_t bTunnel : 1;					// Is this model part of a tunnel
    uint32_t bTunnelTransition : 1;			// This model should be rendered from within and outside of the tunnel
    /********** END CFLAGS **************/

	uint16_t	unknown0020;			// + 0x0020
	uint16_t	modelIndex;				// + 0x0022

	void*		reference;				// + 0x0024

	uint8_t		unknown[ 0x1C ];		// + 0x0028

private:

};

#endif