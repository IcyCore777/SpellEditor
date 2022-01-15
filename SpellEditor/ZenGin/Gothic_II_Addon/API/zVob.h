// Supported with union (c) 2018 Union team

#ifndef __ZVOB_H__VER3__
#define __ZVOB_H__VER3__

#include "z3d.h"
#include "zBsp.h"
#include "zSound.h"
#include "zVisual.h"

namespace Gothic_II_Addon {

#define zTRACERAY_DEFAULT					0x00000000
#define zTRACERAY_VOB_CHECK_COLLDET			0x00000001
#define zTRACERAY_IGNORE_VOBS				0x00000002
#define zTRACERAY_VOB_CHECK_BBOX_ONLY		0x00000004
#define zTRACERAY_UNUSED_8					0x00000008
#define zTRACERAY_IGNORE_LEVEL				0x00000010
#define zTRACERAY_LEVEL_FIND_NEAREST_INTERS	0x00000020
#define zTRACERAY_ALLOW_PORTALS				0x00000040
#define zTRACERAY_CALC_NORMAL				0x00000080
#define zTRACERAY_IGNORE_TRANSPARENT		0x00000100
#define zTRACERAY_ALLOW_WATER				0x00000200
#define zTRACERAY_TWO_SIDED					0x00000400
#define zTRACERAY_IGNORE_CHARACTERS			0x00000800
#define zTRACERAY_VOB_FIND_ANY_INTERS		0x00001000
#define zTRACERAY_ALLOW_HELPERS				0x00002000
#define zTRACERAY_ALLOW_PROJECTILES			0x00004000	

  enum zTVobType {
    zVOB_TYPE_NORMAL,
    zVOB_TYPE_LIGHT,
    zVOB_TYPE_SOUND,
    zVOB_TYPE_LEVEL_COMPONENT,
    zVOB_TYPE_SPOT,
    zVOB_TYPE_CAMERA,
    zVOB_TYPE_STARTPOINT,
    zVOB_TYPE_WAYPOINT,
    zVOB_TYPE_MARKER,
    zVOB_TYPE_SEPARATOR = 127,
    zVOB_TYPE_MOB,
    zVOB_TYPE_ITEM,
    zVOB_TYPE_NSC
  };

  enum zTVobSleepingMode {
    zVOB_SLEEPING,
    zVOB_AWAKE,
    zVOB_AWAKE_DOAI_ONLY
  };

  enum zTAnimationMode {
    zVISUAL_ANIMODE_NONE,
    zVISUAL_ANIMODE_WIND,
    zVISUAL_ANIMODE_WIND2
  };

  enum zTVobLightType {
    zVOBLIGHT_TYPE_POINT,
    zVOBLIGHT_TYPE_SPOT,
    zVOBLIGHT_TYPE_DIR,
    zVOBLIGHT_TYPE_AMBIENT
  };

  enum zTVobLightQuality {
    zVOBLIGHT_QUAL_HI,
    zVOBLIGHT_QUAL_MID,
    zVOBLIGHT_QUAL_FASTEST
  };

  class zCEventMessage : public zCObject {
  public:
    zCLASS_DECLARATION( zCEventMessage )
	typedef zWORD			zTSubType;
    enum zTTimeBehavior {
      TBZero,
      TBFix,
      TBUnknown,
      TBAssembled
    };

    unsigned short int subType;
    int inCutscene;

    void zCEventMessage_OnInit()                                                    zCall( 0x00413B60 );
    void zCEventMessage_OnInit( unsigned short )                                    zCall( 0x00605560 );
    zCEventMessage()                                                                zInit( zCEventMessage_OnInit() );
    zCEventMessage( unsigned short a0 )                                             zInit( zCEventMessage_OnInit( a0 ));
    unsigned long GetMessageID() const                                              zCall( 0x006056D0 );
    void PackToBuffer( zCBuffer&, zCEventManager* )                                 zCall( 0x00605730 );
    unsigned short GetSubType() const                                               zCall( 0x00674290 );
    static zCObject* _CreateNewInstance()                                           zCall( 0x005FCEF0 );
    //static void operator delete( void* )                                            zCall( 0x005FD050 );
    static void AnalyzeMessageID( unsigned long, unsigned short&, unsigned short& ) zCall( 0x006056F0 );
    static zCEventMessage* CreateFromID( unsigned long )                            zCall( 0x00605710 );
    static zCEventMessage* CreateFromBuffer( zCBuffer&, zCEventManager* )           zCall( 0x00605780 );
    static void TestClassIntegrity()                                                zCall( 0x006059E0 );
    virtual zCClassDef* _GetClassDef() const                                        zCall( 0x00401F30 );
    virtual void Archive( zCArchiver& )                                             zCall( 0x006057C0 );
    virtual void Unarchive( zCArchiver& )                                           zCall( 0x006059C0 );
    virtual ~zCEventMessage()                                                       zCall( 0x004020D0 );
    virtual int IsOverlay()                                                         zCall( 0x00401F40 );
    virtual int IsNetRelevant()                                                     zCall( 0x00401F50 );
    virtual int IsHighPriority()                                                    zCall( 0x00401F60 );
    virtual int IsJob()                                                             zCall( 0x00401F70 );
    virtual int GetIgnoreCutsceneMode()                                             zCall( 0x00401F80 );
    virtual void Delete()                                                           zCall( 0x00401F90 );
    virtual int IsDeleteable()                                                      zCall( 0x00401FA0 );
    virtual int IsDeleted()                                                         zCall( 0x00401FB0 );
    virtual void SetCutsceneMode( int )                                             zCall( 0x00401FC0 );
    virtual int GetCutsceneMode()                                                   zCall( 0x00401FD0 );
    virtual int MD_GetNumOfSubTypes()                                               zCall( 0x00401FE0 );
    virtual zSTRING MD_GetSubTypeString( int )                                      zCall( 0x00401FF0 );
    virtual zSTRING MD_GetVobRefName()                                              zCall( 0x00402030 );
    virtual void MD_SetVobRefName( zSTRING const& )                                 zCall( 0x00402070 );
    virtual void MD_SetVobParam( zCVob* )                                           zCall( 0x00402080 );
    virtual zTTimeBehavior MD_GetTimeBehavior()                                     zCall( 0x00402090 );
    virtual float MD_GetMinTime()                                                   zCall( 0x004020A0 );
    virtual void Pack( zCBuffer&, zCEventManager* )                                 zCall( 0x004020B0 );
    virtual void Unpack( zCBuffer&, zCEventManager* )                               zCall( 0x004020C0 );
  };

  class zCEventCore : public zCEventMessage {
  public:
    zCLASS_DECLARATION( zCEventCore )

    enum zTEventCoreSubType {
      zEVENT_TRIGGER,
      zEVENT_UNTRIGGER,
      zEVENT_TOUCH,
      zEVENT_UNTOUCH,
      zEVENT_TOUCHLEVEL,
      zEVENT_DAMAGE,
      zEVENT_CORE_NUM_SUBTYPES
    };

    zCVob* otherVob;
    zCVob* vobInstigator;
    float damage;
    int damageType;
    zCVob* inflictorVob;
    zVEC3 hitLocation;

	zCEventCore(const zTEventCoreSubType sub) { Clear(); subType = zTSubType(sub); };
	zCEventCore(const zTEventCoreSubType sub, zCVob* inOtherVob) { Clear(); subType = zTSubType(sub); otherVob = inOtherVob; };
	zCEventCore(const zTEventCoreSubType sub, zCVob* inOtherVob, zCVob* inInstigator) { Clear(); subType = zTSubType(sub); otherVob = inOtherVob; vobInstigator = inInstigator; };
	zCEventCore(const zTEventCoreSubType sub,
		zCVob* inOtherVob, zCVob* inInflictorVob, const zREAL dam, const int damType = 0, const zVEC3& hitLoc = zVEC3(0))
	{
		
		Clear(); subType = zTSubType(sub); otherVob = inOtherVob; inflictorVob = inInflictorVob; damage = dam; damageType = damType; hitLocation = hitLoc;
	
	};

    void Clear()                                      zCall( 0x006060C0 );
    static void operator delete( void* )              zCall( 0x00402110 );
    static zCObject* _CreateNewInstance()             zCall( 0x005FD250 );
    virtual zCClassDef* _GetClassDef() const          zCall( 0x00402130 );
    virtual void Archive( zCArchiver& )               zCall( 0x006064F0 );
    virtual void Unarchive( zCArchiver& )             zCall( 0x00606560 );
    virtual ~zCEventCore()                            zCall( 0x00606100 );
    virtual int IsNetRelevant()                       zCall( 0x00402150 );
    virtual int MD_GetNumOfSubTypes()                 zCall( 0x00402140 );
    virtual zSTRING MD_GetSubTypeString( int )        zCall( 0x006062F0 );
    virtual void Pack( zCBuffer&, zCEventManager* )   zCall( 0x00606120 );
    virtual void Unpack( zCBuffer&, zCEventManager* ) zCall( 0x006061D0 );
  };

  class zCVob : public zCObject {
  public:
    zCLASS_DECLARATION( zCVob )

    zEVENT_INTERFACE


		static	zCClassDef*		GetStaticClassDef(void) { return classDef; };

    enum zTVobCharClass {
      zVOB_CHAR_CLASS_NONE,
      zVOB_CHAR_CLASS_PC,
      zVOB_CHAR_CLASS_NPC
    };

    enum zTMovementMode {
      zVOB_MOVE_MODE_NOTINBLOCK,
      zVOB_MOVE_MODE_INBLOCK,
      zVOB_MOVE_MODE_INBLOCK_NOCD
    };

    enum {
      zVOB_CDMODE_EXACT,
      zVOB_CDMODE_SPEEDBOX,
      zVOB_CDMODE_ALL
    };

    enum zTDynShadowType {
      zDYN_SHADOW_TYPE_NONE,
      zDYN_SHADOW_TYPE_BLOB,
      zDYN_SHADOW_TYPE_COUNT
    };

    struct zTCollisionContext {
      zCArray<zCCollisionObject*> otherCollObjectList;
      zCArray<zCVob*> otherCollVobList;

      zTCollisionContext() {}
      ~zTCollisionContext() zCall( 0x0061F490 );
    };

    struct zTModelLimbColl {
      zCVob* hitVob;
      zCMaterial* hitMaterial;
      zCList<zCModelNodeInst> hitModelNodeList;
      zVEC3 approxCollisionPos;

      void zTModelLimbColl_OnInit() zCall( 0x00603A20 );
      zTModelLimbColl()             zInit( zTModelLimbColl_OnInit() );
      ~zTModelLimbColl()            zCall( 0x00603A50 );
    };

    zCTree<zCVob>* globalVobTreeNode;
    int lastTimeDrawn;
    unsigned long lastTimeCollected;
    zCArray<zCBspLeaf*> vobLeafList;
    zMAT4 trafoObjToWorld;
    zTBBox3D bbox3D;
    zTBSphere3D bsphere3D;
    zCArray<zCVob*> touchVobList;
    zTVobType type;
    unsigned long groundShadowSizePacked;
    zCWorld* homeWorld;
    zCPolygon* groundPoly;
    zCAIBase* callback_ai;
    zMAT4* trafo;
    zCVisual* visual;
    float visualAlpha;
    float m_fVobFarClipZScale;
    zTAnimationMode m_AniMode;
    float m_aniModeStrength;
    int m_zBias;
    zCRigidBody* rigidBody;
    zCOLOR lightColorStat;
    zCOLOR lightColorDyn;
    zVEC3 lightDirectionStat;
    zSTRING* vobPresetName;
    zCEventManager* eventManager;
    float nextOnTimer;
	struct {
      unsigned char showVisual                : 1;
      unsigned char drawBBox3D                : 1;
      unsigned char visualAlphaEnabled        : 1;
      unsigned char physicsEnabled            : 1;
      unsigned char staticVob                 : 1;
      unsigned char ignoredByTraceRay         : 1;
      unsigned char collDetectionStatic       : 1;
      unsigned char collDetectionDynamic      : 1;
      unsigned char castDynShadow             : 2;
      unsigned char lightColorStatDirty       : 1;
      unsigned char lightColorDynDirty        : 1;
      zTMovementMode isInMovementMode         : 2;
      unsigned char sleepingMode              : 2;
      unsigned char mbHintTrafoLocalConst     : 1;
      unsigned char mbInsideEndMovementMethod : 1;
      zTVisualCamAlign visualCamAlign         : 2;
      unsigned char collButNoMove             : 4;
      unsigned char dontWriteIntoArchive      : 1;
      unsigned char bIsInWater                : 1;
      unsigned char bIsAmbientVob             : 1;
    };
    zCCollisionObjectDef* m_poCollisionObjectClass;
    zCCollisionObject* m_poCollisionObject;

    void zCVob_OnInit()                                                                                           zCall( 0x005FE1E0 );
    zVEC3 GetPositionWorld() const                                                                                zCall( 0x0052DC90 );
    zVEC3 GetAtVectorWorld() const                                                                                zCall( 0x0052DCB0 );
    zVEC3 GetUpVectorWorld() const                                                                                zCall( 0x0052DCD0 );
    zVEC3 GetRightVectorWorld() const                                                                             zCall( 0x0052DCF0 );
    zCVob()                                                                                                       zInit( zCVob_OnInit() );
    void SetVobID( unsigned long const& )                                                                         zCall( 0x005FE8E0 );
    void SetAI( zCAIBase* )                                                                                       zCall( 0x005FE8F0 );
	void SetVobPresetName(zSTRING const&);//                                                                       zCall(0x005FE940);
    zSTRING const& GetVobPresetName() const                                                                       zCall( 0x005FE950 );
    zCRigidBody* GetRigidBody()                                                                                   zCall( 0x005FE960 );
    void __fastcall ArchivePacked( zCArchiver& )                                                                  zCall( 0x005FE9D0 );
    void __fastcall ArchiveVerbose( zCArchiver& )                                                                 zCall( 0x005FEDB0 );
    void __fastcall UnarchivePacked( zCArchiver&, int )                                                           zCall( 0x005FF200 );
    void __fastcall UnarchiveVerbose( zCArchiver& )                                                               zCall( 0x005FF720 );
    void SetVobName( zSTRING const& )                                                                             zCall( 0x005FFDD0 );
    zCEventManager* __fastcall GetEM(const zBOOL dontCreateIfNotPresent = FALSE)                                                                       zCall( 0x005FFE10 );
    zCOLOR CalcLightSampleAtOrigin()                                                                              zCall( 0x00600130 );
    zCOLOR GetLightColorStat()                                                                                    zCall( 0x006001B0 );
    zCOLOR GetLightColorStatGroundPoly()                                                                          zCall( 0x00600440 );
    zCOLOR GetLightColorDyn()                                                                                     zCall( 0x00600470 );
    int __fastcall CalcStaticLight( zVEC3& ) const                                                                zCall( 0x00600650 );
    zSTRING const* GetSectorNameVobIsIn() const                                                                   zCall( 0x00600AE0 );
    void __fastcall SetGroundShadowSize( zVEC2 const& )                                                           zCall( 0x00600C30 );
    zVEC2 __fastcall GetGroundShadowSize() const                                                                  zCall( 0x00600C80 );
    void __fastcall RenderGroundShadow( zTRenderContext& )                                                        zCall( 0x00600CD0 );
    zCVisual* GetClassHelperVisual() const                                                                        zCall( 0x006011E0 );
    void CalcRenderAlpha( float, zCVisual*&, float& )                                                             zCall( 0x006013E0 );
    zCOLOR GetLightColorAtCenter() const                                                                          zCall( 0x00601AC0 );
    void RemoveVobFromWorld()                                                                                     zCall( 0x00601C40 );
    void RemoveVobSubtreeFromWorld()                                                                              zCall( 0x00601C60 );
    void AddRefVobSubtree( zCTree<zCVob>*, int )                                                                  zCall( 0x00601CC0 );
    void ReleaseVobSubtree( zCTree<zCVob>* )                                                                      zCall( 0x00601D40 );
    void RemoveWorldDependencies( int )                                                                           zCall( 0x00601DA0 );
    void RemoveVobFromGlobalVobTree()                                                                             zCall( 0x00601FF0 );
    void RemoveVobFromBspTree()                                                                                   zCall( 0x006020E0 );
    zSTRING GetVobInfo()                                                                                          zCall( 0x00602100 );
    void SetSleeping( int )                                                                                       zCall( 0x00602930 );
    void UpdateVisualDependencies(const zBOOL a_bHintTrafoChanged = TRUE)                                                                          zCall( 0x00602B20 );
    void AddVobToWorld_CorrectParentDependencies()                                                                zCall( 0x00602BB0 );
    void ResetOnTimer()                                                                                           zCall( 0x00602BD0 );
    void SetOnTimer( float )                                                                                      zCall( 0x00602BE0 );
    int IsOnTimer() const                                                                                         zCall( 0x00602C10 );
    void ProcessOnTimer()                                                                                         zCall( 0x00602C30 );
    void DoFrameActivity()                                                                                        zCall( 0x00602C60 );
    void CheckModelLimbCollision( zCModelNodeInst*, int, zCList<zTModelLimbColl>& )                               zCall( 0x00602ED0 );
    void CheckModelLimbCollisionLevel( zCModelNodeInst*, int, zCList<zTModelLimbColl>& )                          zCall( 0x00603A80 );
    void CheckModelLimbCollisionPolys( zCModelNodeInst*, int, zCPolygon**, int const&, zCList<zTModelLimbColl>& ) zCall( 0x00604710 );
    zMAT4 GetTrafoModelNodeToWorld( zSTRING const& )                                                              zCall( 0x00604960 );
    zMAT4 GetTrafoModelNodeToWorld( zCModelNodeInst* )                                                            zCall( 0x00604A50 );
    zTBBox2D GetScreenBBox2D()                                                                                    zCall( 0x00604AE0 );
    void PackStateBinary( zCBuffer& ) const                                                                       zCall( 0x00605110 );
    void UnpackStateBinary( zCBuffer& )                                                                           zCall( 0x006051C0 );
    int GetIsProjectile() const                                                                                   zCall( 0x00606C00 );
    zCVisual* GetVisual() const                                                                                   zCall( 0x00616B20 );
    void CalcGroundPoly()                                                                                         zCall( 0x0061ACD0 );
    void CalcWaterVob()                                                                                           zCall( 0x0061AE20 );
    void SetCollTypeDefaultFromVisual()                                                                           zCall( 0x0061AEF0 );
    void TouchMovement()                                                                                          zCall( 0x0061B060 );
    zMAT4 const& GetNewTrafoObjToWorld() const                                                                    zCall( 0x0061B080 );
    zMAT4& GetNewTrafoObjToWorld()                                                                                zCall( 0x0061B0A0 );
    void SetNewTrafoObjToWorld( zMAT4 const& )                                                                    zCall( 0x0061B0C0 );
    void SetBBox3DWorld( zTBBox3D const& )                                                                        zCall( 0x0061B0E0 );
    void SetBBox3DLocal( zTBBox3D const& )                                                                        zCall( 0x0061B140 );
    zTBBox3D GetBBox3DLocal() const                                                                               zCall( 0x0061B1F0 );
    void Move( float, float, float )                                                                              zCall( 0x0061B2E0 );
    void MoveWorld( float, float, float )                                                                         zCall( 0x0061B350 );
    void MoveLocal( float, float, float )                                                                         zCall( 0x0061B3C0 );
    void SetRotationWorld( zCQuat const& )                                                                        zCall( 0x0061B4C0 );
    void RotateWorld( zVEC3 const&, float )                                                                       zCall( 0x0061B520 );
    void RotateLocal( zVEC3 const&, float )                                                                       zCall( 0x0061B610 );
    void RotateLocalX( float )                                                                                    zCall( 0x0061B6B0 );
    void RotateLocalY( float )                                                                                    zCall( 0x0061B720 );
    void RotateLocalZ( float )                                                                                    zCall( 0x0061B790 );
    void RotateWorldX( float )                                                                                    zCall( 0x0061B800 );
    void RotateWorldY( float )                                                                                    zCall( 0x0061B830 );
    void RotateWorldZ( float )                                                                                    zCall( 0x0061B860 );
    void GetPositionWorld( float&, float&, float& ) const                                                         zCall( 0x0061B890 );
    void GetPositionLocal( float&, float&, float& ) const                                                         zCall( 0x0061B8C0 );
    float GetDistanceToVob( zCVob& )                                                                              zCall( 0x0061B910 );
    float GetDistanceToVobApprox( zCVob& )                                                                        zCall( 0x0061B970 );
    float GetDistanceToVob2( zCVob& )                                                                             zCall( 0x0061BA40 );
    void SetPositionLocal( zVEC3 const& )                                                                         zCall( 0x0061BAA0 );
    void SetPositionWorld( zVEC3 const& )                                                                         zCall( 0x0061BB70 );
    void SetTrafo( zMAT4 const& )                                                                                 zCall( 0x0061BBD0 );
    void SetTrafoObjToWorld( zMAT4 const& )                                                                       zCall( 0x0061BC80 );
    void ResetRotationsLocal()                                                                                    zCall( 0x0061BCF0 );
    void ResetXZRotationsLocal()                                                                                  zCall( 0x0061BE20 );
    void ResetRotationsWorld()                                                                                    zCall( 0x0061C000 );
    void ResetXZRotationsWorld()                                                                                  zCall( 0x0061C090 );
    void SetHeadingYLocal( zVEC3 const& )                                                                         zCall( 0x0061C1B0 );
    void SetHeadingYWorld( zVEC3 const& )                                                                         zCall( 0x0061C280 );
    void SetHeadingYWorld( zCVob* )                                                                               zCall( 0x0061C450 );
    void SetHeadingLocal( zVEC3 const& )                                                                          zCall( 0x0061C5E0 );
    void SetHeadingWorld( zVEC3 const& )                                                                          zCall( 0x0061C6B0 );
    void SetHeadingWorld( zCVob* )                                                                                zCall( 0x0061C780 );
    void SetHeadingAtLocal( zVEC3 const& )                                                                        zCall( 0x0061C860 );
    int HasParentVob() const                                                                                      zCall( 0x0061CBA0 );
    void SetHeadingAtWorld( zVEC3 const& )                                                                        zCall( 0x0061CBC0 );
    void __fastcall SetCollDetStat( int )                                                                         zCall( 0x0061CE50 );
    void __fastcall SetCollDetDyn( int )                                                                          zCall( 0x0061CF40 );
    void CorrectTrafo()                                                                                           zCall( 0x0061D040 );
    void DoneWithTrafoLocal()                                                                                     zCall( 0x0061D0B0 );
    void CreateTrafoLocal() const                                                                                 zCall( 0x0061D100 );
    void SetPhysicsEnabled( int )                                                                                 zCall( 0x0061D190 );
    zVEC3 GetVelocity()                                                                                           zCall( 0x0061D1C0 );
    void UpdatePhysics()                                                                                          zCall( 0x0061D2D0 );
    int DetectCollision( zMAT4 *trafoObjToWorldNew = 0)                                                                                 zCall( 0x0061D890 );
    void __fastcall SetInMovement( int )                                                                          zCall( 0x0061D9D0 );
    void __fastcall SetInMovementMode( zTMovementMode )                                                           zCall( 0x0061DA30 );
    void BeginMovement()                                                                                          zCall( 0x0061DA80 );
    void ResetToOldMovementState()                                                                                zCall( 0x0061DC00 );
    void __fastcall UpdateTouchList( zCArray<zCVob*> const& )                                                     zCall( 0x0061DC30 );
    void __fastcall CalcDestinationBBox3DWorld( zTBBox3D& )                                                       zCall( 0x0061DEE0 );
    void AdoptCollObjResults()                                                                                    zCall( 0x0061E020 );
    void SetCollisionObject( zCCollisionObject* )                                                                 zCall( 0x0061E5E0 );
    void SetCollisionClass( zCCollisionObjectDef* )                                                               zCall( 0x0061E610 );
    zCCollisionObject* GetCollisionObject() const                                                                 zCall( 0x0061E650 );
    void CreateCollisionObject()                                                                                  zCall( 0x0061E660 );
    void ResetCollisionObjectState()                                                                              zCall( 0x0061E690 );
    void __fastcall DestroyCollisionObject( int )                                                                 zCall( 0x0061E6D0 );
    void CheckEmergencyPutToSleep()                                                                               zCall( 0x0061E710 );
    void __fastcall CollectCollisionContext_Vobs( zTBBox3D const&, zTCollisionContext& )                          zCall( 0x0061E870 );
    void __fastcall CollectCollisionContext_Static( zTBBox3D const&, zCArray<zCCollisionObject*>& )               zCall( 0x0061EAD0 );
    void __fastcall CollectCollisionContext( zTCollisionContext& )                                                zCall( 0x0061EDC0 );
    void __fastcall CleanupCollisionContext( zTCollisionContext const& )                                          zCall( 0x0061EE40 );
    void __fastcall NotifyCollisionPair( zCCollisionReport*, zCArray<zCCollisionReport*> const&, int )            zCall( 0x0061EEB0 );
    void __fastcall ExecuteCollisionResponse( zCArray<zCCollisionReport*> const&, int& )                          zCall( 0x0061EF80 );
    void CheckAndResolveCollisions()                                                                              zCall( 0x0061F060 );
    int IsColliding()                                                                                             zCall( 0x0061F4F0 );
    zCWorld* GetHomeWorld() const                                                                                 zCall( 0x006742A0 );
    void SetStaticVob( int )                                                                                      zCall( 0x006CFFB0 );
    zTVobType GetVobType() const                                                                                  zCall( 0x006CFFD0 );
    void SetDrawBBox3D( int )                                                                                     zCall( 0x006CFFE0 );
    void SetCollDet( int )                                                                                        zCall( 0x006D0000 );
    //static void operator delete( void* )                                                                          zCall( 0x0043D180 );
    static zCObject* _CreateNewInstance()                                                                         zCall( 0x005FD940 );
    static void InitVobSystem()                                                                                   zCall( 0x005FE6E0 );
    static void CleanupVobSystem()                                                                                zCall( 0x005FE800 );
    static void ResetIDCtr()                                                                                      zCall( 0x005FE8C0 );
    static unsigned long GetNextFreeVobID()                                                                       zCall( 0x005FE8D0 );
    static void LoadGroundShadowMesh()                                                                            zCall( 0x00600B00 );
    static void DeleteGroundShadowMesh()                                                                          zCall( 0x00600C00 );
    static void RepairIllegalFloats( zMAT4& )                                                                     zCall( 0x00604F10 );
    static zCVob* GetAutoLinkParent( zCVob* )                                                                     zCall( 0x0061A6C0 );
    static int CanAutoLinkWith( zCVob*, zCVob* )                                                                  zCall( 0x0061A700 );
    static void CheckAutoLink( zCVob*, zCVob* )                                                                   zCall( 0x0061A840 );
    static void CheckAutoUnlink( zCVob* )                                                                         zCall( 0x0061AAC0 );
    static void SetShowHelperVisuals( int )                                                                       zCall( 0x00637110 );
    static int GetShowHelperVisuals()                                                                             zCall( 0x00637120 );
    static int GetAnimationsEnabled()                                                                             zCall( 0x00637130 );
    static void SetAnimationsEnabled( int )                                                                       zCall( 0x00637140 );
    virtual zCClassDef* _GetClassDef() const                                                                      zCall( 0x0043CCB0 );
    virtual void Archive( zCArchiver& )                                                                           zCall( 0x005FF140 );
    virtual void Unarchive( zCArchiver& )                                                                         zCall( 0x005FFC70 );
    virtual ~zCVob()                                                                                              zCall( 0x005FE470 );
    virtual void OnTrigger( zCVob*, zCVob* )                                                                      zCall( 0x005FE170 );
    virtual void OnUntrigger( zCVob*, zCVob* )                                                                    zCall( 0x005FE180 );
    virtual void OnTouch( zCVob* )                                                                                zCall( 0x005FE190 );
    virtual void OnUntouch( zCVob* )                                                                              zCall( 0x005FE1A0 );
    virtual void OnTouchLevel()                                                                                   zCall( 0x005FE1B0 );
    virtual void OnDamage( zCVob*, zCVob*, float, int, zVEC3 const& )                                             zCall( 0x005FE1C0 );
    virtual void OnMessage( zCEventMessage*, zCVob* )                                                             zCall( 0x005FE1D0 );
    virtual void OnTick()                                                                                         zCall( 0x00404270 );
    virtual void OnTimer()                                                                                        zCall( 0x0043CCC0 );
    virtual void PostLoad()                                                                                       zCall( 0x00404280 );
    virtual zTVobCharClass GetCharacterClass()                                                                    zCall( 0x00404290 );
    virtual void SetSleepingMode( zTVobSleepingMode )                                                             zCall( 0x00602960 );
    virtual void EndMovement(const zBOOL a_bHintTrafoChanged = TRUE)                                                                               zCall( 0x0061E0D0 );
    virtual int CanThisCollideWith( zCVob* )                                                                      zCall( 0x004042A0 );
    virtual int __fastcall Render( zTRenderContext& )                                                             zCall( 0x006015D0 );
    virtual void SetVisual( zCVisual* )                                                                           zCall( 0x006024F0 );
    virtual void SetVisual( zSTRING const& )                                                                      zCall( 0x00602680 );
    virtual int GetScriptInstance( zSTRING*&, int& )                                                              zCall( 0x004042B0 );
    virtual int SetByScriptInstance( zSTRING const*, int )                                                        zCall( 0x004042D0 );
    virtual int GetCSStateFlags()                                                                                 zCall( 0x004042E0 );
    virtual int TraceRay( zVEC3 const&, zVEC3 const&, int, zTTraceRayReport& )                                    zCall( 0x005FFE40 );
    virtual zSTRING const* GetTriggerTarget(int i = 0) const                                                          zCall( 0x0043CCD0 );
    virtual void ThisVobAddedToWorld( zCWorld* )                                                                  zCall( 0x00601C80 );
    virtual void ThisVobRemovedFromWorld( zCWorld* )                                                              zCall( 0x00601CA0 );

	void				SetShowVisual(zBOOL show) { showVisual = show; };
	zBOOL				GetShowVisual() const { return showVisual; };
	const zTBBox3D&		GetBBox3DWorld() const { return bbox3D; };
	zTVisualCamAlign	GetVisualCamAlign() const { return visualCamAlign; };
	void				SetVisualCamAlign(const zTVisualCamAlign a) { visualCamAlign = a; };

	void				SetVisualAlphaEnabled(const zBOOL b) { visualAlphaEnabled = b; };
	zBOOL				GetVisualAlphaEnabled() const { return visualAlphaEnabled; };
	void				SetVisualAlpha(const zREAL a) { visualAlpha = a; };
	zREAL				GetVisualAlpha() const { return visualAlpha; };
	static zBOOL		GetIgnoreVisuals() { return s_ignoreVisuals; };
	static void			SetIgnoreVisuals(zBOOL b) { s_ignoreVisuals = b; };
    // static properties
    static int& s_ignoreVisuals;
    static zCMesh*& s_shadowMesh;
    static unsigned long& s_nextFreeID;
    static int& s_vobAlreadyInMovement;
    static int& s_renderVobs;
    static int& s_showHelperVisuals;
    static int& s_enableAnimations;
    static zCCollisionDetector*& s_poCollisionDetector;

	zTVobSleepingMode	GetSleepingMode() const { return zTVobSleepingMode(sleepingMode); };
	inline zDWORD		GetVobID() const { return zDWORD(1); };
	zBOOL				GetSleeping() const { return (sleepingMode == zVOB_SLEEPING); };

	zMAT4&              GetTrafoLocal() { if (!trafo) CreateTrafoLocal(); return *trafo; }  // the vob´s transformation matrix relative to its parent vob
	const zMAT4&        GetTrafoLocal() const { if (!trafo) CreateTrafoLocal(); return *trafo; }  // the vob´s transformation matrix relative to its parent vob

	zBOOL				GetPhysicsEnabled() const { return physicsEnabled; };
	zBOOL				GetStaticVob() const { return staticVob; };
	void				SetIgnoredByTraceRay(const zBOOL i) { ignoredByTraceRay = i; };
	zBOOL				GetIgnoredByTraceRay() const { return ignoredByTraceRay; };
	const zSTRING&		GetVobName() const { return GetObjectName(); };
	zBOOL				GetCollDetStat() const { return collDetectionStatic; };
	void				GetPositionWorld(zVEC3& pos) const { trafoObjToWorld.GetTranslation(pos); };
	zBOOL				GetCollDetDyn() const { return collDetectionDynamic; };
	zCEventManager*		GetEventManager(const zBOOL dontCreateIfNotPresent = FALSE) { return GetEM(dontCreateIfNotPresent); };
	void				RotateLocal(const float x, const float y, const float z, const float angle) { RotateLocal(zVEC3(x, y, z), angle); };
	void				RotateWorld(const float x, const float y, const float z, const float angle) { RotateWorld(zVEC3(x, y, z), angle); };
	void				SetPositionLocal(const float x, const float y, const float z) { SetPositionLocal(zVEC3(x, y, z)); };
	zCPolygon*			GetGroundPoly() const { return groundPoly; };
	void				SetPositionWorld(const float x, const float y, const float z) { SetPositionWorld(zVEC3(x, y, z)); };
	zCClassDef*			GetVisualClass() const { return (visual ? visual->GetClassDef() : 0); };
	void				MoveLocal(const zVEC3& dir) { MoveLocal(dir.n[VX], dir.n[VY], dir.n[VZ]); };

	void				MoveWorld(const zVEC3& dir) { MoveWorld(dir.n[VX], dir.n[VY], dir.n[VZ]); };
	zBOOL				GetDrawBBox3D() const { return drawBBox3D; };
	int					GetZBias() const { return m_zBias; };
	void				SetZBias(const int a_iZBias) { m_zBias = a_iZBias; };

	// visual animation
	void				SetVisualAniMode(const zTAnimationMode &aniMode) { m_AniMode = aniMode; };
	zTAnimationMode		GetVisualAniMode()	const { return m_AniMode; };
	void				SetVisualAniModeStrength(zREAL aniModeStrength) { m_aniModeStrength = aniModeStrength; };
	zREAL				GetVisualAniModeStrength()  const { return m_aniModeStrength; };
	void				SetCastDynShadow(const zTDynShadowType b) { castDynShadow = b; };
	zTDynShadowType		GetCastDynShadow() const { return zTDynShadowType(castDynShadow); };
	zBOOL __fastcall spcRender(zTRenderContext &renderContext);
	void TouchMovementUnion();
	zBOOL				GetInMovement() const { return (isInMovementMode != zVOB_MOVE_MODE_NOTINBLOCK); };
  };

  class zCVobLightData {
  public:
    zCArray<float> rangeAniScaleList;
    zCArray<zCOLOR> colorAniList;
    int lensFlareFXNo;
    zCLensFlareFX* lensFlareFX;
    zCOLOR lightColor;
    float range;
    float rangeInv;
    float rangeBackup;
    float rangeAniActFrame;
    float rangeAniFPS;
    float colorAniActFrame;
    float colorAniFPS;
    float spotConeAngleDeg;
    group {
      unsigned char isStatic       : 1;
      unsigned char rangeAniSmooth : 1;
      unsigned char rangeAniLoop   : 1;
      unsigned char colorAniSmooth : 1;
      unsigned char colorAniLoop   : 1;
      unsigned char isTurnedOn     : 1;
      unsigned char lightQuality   : 4;
      unsigned char lightType      : 4;
      unsigned char m_bCanMove     : 1;
    };

    void zCVobLightData_OnInit()               zCall( 0x0060A970 );
    int SetLensFlareFXByName( zSTRING const& ) zCall( 0x00609970 );
    zSTRING const& GetLensFlareFXName() const  zCall( 0x00609A70 );
    void Archive( zCArchiver& )                zCall( 0x00609A90 );
    void Unarchive( zCArchiver& )              zCall( 0x00609FA0 );
    zCVobLightData()                           zInit( zCVobLightData_OnInit() );
    ~zCVobLightData()                          zCall( 0x0060A9F0 );
    void SetRange( float, const zBOOL doBackup = TRUE)                zCall( 0x0060AA60 );

	zTVobLightType		GetLightType()  const { return zTVobLightType(lightType); };
	void				SetLightType(const zTVobLightType ltype) { lightType = ltype; };
	zREAL				GetSpotConeAngle() const { return spotConeAngleDeg; };
	void				SetSpotConeAngle(const zREAL spotConeAngle) { this->spotConeAngleDeg = spotConeAngle; };

	zBOOL				IsRangeAnimated() const { return (rangeAniFPS != 0) && (rangeAniScaleList.GetNumInList()>0); };
	void				SetRangeAniFPS(const float fps) { rangeAniFPS = fps / 1000; rangeAniActFrame = 0; };
	zREAL				GetRangeAniFPS() const { return rangeAniFPS * 1000; };
	void				SetRangeAniSmooth(const zBOOL  b) { rangeAniSmooth = b; };
	zBOOL				GetRangeAniSmooth() const { return rangeAniSmooth; };
	void				SetRangeAniLoop(const zBOOL  b) { rangeAniLoop = b; };
	zBOOL				GetRangeAniLoop() const { return rangeAniLoop; };

	zBOOL				IsColorAnimated() const { return (colorAniFPS != 0) && (colorAniList.GetNumInList()>0); };
	void				SetColorAniFPS(const float fps) { colorAniFPS = fps / 1000; colorAniActFrame = 0; };
	zREAL				GetColorAniFPS() const { return colorAniFPS * 1000; };
	void				SetColorAniSmooth(const zBOOL  b) { colorAniSmooth = b; };
	zBOOL				GetColorAniSmooth() const { return colorAniSmooth; };
	void				SetColorAniLoop(const zBOOL  b) { colorAniLoop = b; };
	zBOOL				GetColorAniLoop() const { return colorAniLoop; };

	//
	void				SetWhiteLight(zBYTE intensity) { lightColor.SetRGB(intensity); };
	void				SetColor(zBYTE r, zBYTE g, zBYTE b) { lightColor.SetRGB(r, g, b); };
	void				SetColor(zCOLOR col) { lightColor = col; };
	zCOLOR				GetColor() const { return lightColor; };
	int					GetColorR() const { return int(lightColor.r); };
	int					GetColorG() const { return int(lightColor.g); };
	int					GetColorB() const { return int(lightColor.b); };


	float				GetRange() const { return range; };
	float				GetRangeInv() const { return rangeInv; };
	float				GetRangeFixed() const { return rangeBackup; };	// returns the fixed reference value (unaffected by rangeAnimation)
	zBOOL				GetCanMove() const { return m_bCanMove; };
	void				SetCanMove(const zBOOL a_bCanMove) { m_bCanMove = a_bCanMove; };

	void				SetIsStatic(const zBOOL b) { isStatic = b; };
	zBOOL				GetIsStatic() const { return isStatic; };

	void				SetLightQuality(const zTVobLightQuality q) { lightQuality = q; };
	zTVobLightQuality	GetLightQuality() const { return zTVobLightQuality(lightQuality); };

  };

  class zCVobLightPreset : public zCObject {
  public:
    zCLASS_DECLARATION( zCVobLightPreset )

    zCVobLightData lightData;
    zSTRING presetName;
	const zSTRING&	GetName() { return presetName; };
	void			SetName(const zSTRING& name) { presetName = name; };

    zCVobLightPreset() {}
    static zCObject* _CreateNewInstance()    zCall( 0x005FD520 );
    static void operator delete( void* )     zCall( 0x005FD670 );
    virtual zCClassDef* _GetClassDef() const zCall( 0x005FD690 );
    virtual void Archive( zCArchiver& )      zCall( 0x00609790 );
    virtual void Unarchive( zCArchiver& )    zCall( 0x006097C0 );
    virtual ~zCVobLightPreset()              zCall( 0x005FD6D0 );
  };



  class zCVobLight : public zCVob {
  public:
    zCLASS_DECLARATION( zCVobLight )
		void	ResetPresetInUse() { lightPresetInUse.Clear(); };
	const zSTRING&	GetPresetInUseName() const { return lightPresetInUse; };
    zCVobLightData lightData;
    zTRayTurboValMap<zCPolygon*, int>affectedPolyMap;
    zSTRING lightPresetInUse;
	

	void			SetShowLightSphere(const int a_bShowSphere) { collDetectionDynamic = a_bShowSphere; };
	zBOOL			GetShowLightSphere() const { return collDetectionDynamic; };
	static zCMesh*	s_pLightSphereMesh;


    void zCVobLight_OnInit()                                                              zCall( 0x00607D10 );
	zCVobLight()                                                                          zInit(zCVobLight_OnInit());
    void DoAnimation()                                                                    zCall( 0x006081C0 );
    void SetRange( float, int )                                                           zCall( 0x00608320 );
    void AddThisToPresetList( zSTRING const& ) const                                      zCall( 0x00608910 );
    int SetByPreset( zSTRING const& )                                                     zCall( 0x00608BE0 );
    int SetByPresetInUse()                                                                zCall( 0x00608E60 );
    //static void operator delete( void* )                                                  zCall( 0x0048DDA0 );
    static zCObject* _CreateNewInstance()                                                 zCall( 0x00607C60 );
    static void CleanupVobLight()                                                         zCall( 0x00607FE0 );
    static zCOLOR SumLightsAtPositionWS( zCArray<zCVobLight*> const&, zVEC3 const&, int ) zCall( 0x00608410 );
    static void LoadLightPresets()                                                        zCall( 0x00608690 );
    static void SaveLightPresets()                                                        zCall( 0x006087E0 );
    virtual zCClassDef* _GetClassDef() const                                              zCall( 0x00607E00 );
    virtual void Archive( zCArchiver& )                                                   zCall( 0x006090B0 );
    virtual void Unarchive( zCArchiver& )                                                 zCall( 0x00609100 );
    virtual ~zCVobLight()                                                                 zCall( 0x00607E40 );
    virtual void OnTrigger( zCVob*, zCVob* )                                              zCall( 0x00608050 );
    virtual void OnUntrigger( zCVob*, zCVob* )                                            zCall( 0x00608120 );
    virtual void EndMovement(const zBOOL a_bHintTrafoChanged = TRUE)                                                       zCall( 0x006092B0 );
    virtual void ThisVobAddedToWorld( zCWorld* )                                          zCall( 0x00609530 );



	zBOOL			IsRangeAnimated() const { return lightData.IsRangeAnimated(); };
	void			SetRangeAniFPS(const float fps) { lightData.SetRangeAniFPS(fps); };
	zREAL			GetRangeAniFPS() const { return lightData.GetRangeAniFPS(); };
	void			SetRangeAniSmooth(const zBOOL  b) { lightData.SetRangeAniSmooth(b); };
	zBOOL			GetRangeAniSmooth() const { return lightData.GetRangeAniSmooth(); };
	void			SetRangeAniLoop(const zBOOL  b) { lightData.SetRangeAniLoop(b); };
	zBOOL			GetRangeAniLoop() const { return lightData.GetRangeAniLoop(); };

	zBOOL			IsColorAnimated() const { return lightData.IsColorAnimated(); };
	void			SetColorAniFPS(const float fps) { lightData.SetColorAniFPS(fps); };
	zREAL			GetColorAniFPS() const { return lightData.GetColorAniFPS(); };
	void			SetColorAniSmooth(const zBOOL  b) { lightData.SetColorAniSmooth(b); };
	zBOOL			GetColorAniSmooth() const { return lightData.GetColorAniSmooth(); };
	void			SetColorAniLoop(const zBOOL  b) { lightData.SetColorAniLoop(b); };
	zBOOL			GetColorAniLoop() const { return lightData.GetColorAniLoop(); };
	zBOOL			GetIsStatic() const { return lightData.isStatic; };

	float			GetRange() const { return lightData.range; };	// returns the current range in cm (state, affected by rangeAnimation)
	float			GetRangeInv() const { return lightData.rangeInv; };
	float			GetRangeFixed() const { return lightData.rangeBackup; };	// returns the fixed reference value (unaffected by rangeAnimation)
    // static properties
    static zCArray<zCVobLightPreset*>& lightPresetList;
    static int& renderLightVisuals;
	static zBOOL	GetRenderLightVisuals() { return renderLightVisuals; };
	static void		SetRenderLightVisuals(const zBOOL b) { renderLightVisuals = b; };

  };

  class zCVobLevelCompo : public zCVob {
  public:
    zCLASS_DECLARATION( zCVobLevelCompo )

    void zCVobLevelCompo_OnInit()            zCall( 0x00605280 );
    zCVobLevelCompo()                        zInit( zCVobLevelCompo_OnInit() );
    int HasIdentityTrafo() const             zCall( 0x006052E0 );
    static zCObject* _CreateNewInstance()    zCall( 0x005FDB90 );
    //static void operator delete( void* )     zCall( 0x005FDC10 );
    virtual zCClassDef* _GetClassDef() const zCall( 0x005FDC30 );
    virtual void Archive( zCArchiver& )      zCall( 0x00605360 );
    virtual void Unarchive( zCArchiver& )    zCall( 0x00605410 );
    virtual ~zCVobLevelCompo()               zCall( 0x005FDC70 );
    virtual void SetVisual( zCVisual* )      zCall( 0x006054E0 );
    virtual void SetVisual( zSTRING const& ) zCall( 0x00605520 );

    // static properties
    static int& unarcIgnoreVisuals;
  };

} // namespace Gothic_II_Addon

#endif // __ZVOB_H__VER3__