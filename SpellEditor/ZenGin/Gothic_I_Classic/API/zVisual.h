// Supported with union (c) 2018 Union team

#ifndef __ZVISUAL_H__VER0__
#define __ZVISUAL_H__VER0__

namespace Gothic_I_Classic {

  enum {
    zVISUAL_CAMALIGN_NONE,
    zVISUAL_CAMALIGN_YAW,
    zVISUAL_CAMALIGN_FULL,
    zVISUAL_CAMALIGN_COUNT
  };

  struct zTRenderContext {
    int clipFlags;
    zCVob* vob;
    zCWorld* world;
    zCCamera* cam;
    float distVobToCam;
    zTVisualCamAlign visualCamAlign;
    zCOLOR hintLightingHighlightColor;
    group {
      unsigned char hintLightingFullbright : 1;
      unsigned char hintLightingSwell      : 1;
      unsigned char hintLightingHighlight  : 1;
    };

    zTRenderContext() {}
  };

  class zCVisual : public zCObject {
  public:
    zCLASS_DECLARATION( zCVisual )

    zCVisual* nextLODVisual;
    zCVisual* prevLODVisual;
    float lodFarDistance;
    float lodNearFadeOutDistance;

    void zCVisual_OnInit()                                                     zCall( 0x005D9D70 );
    zCVisual()                                                                 zInit( zCVisual_OnInit() );
    void AddNextLODVisual( zCVisual* )                                         zCall( 0x005D9F30 );
    void AddEndLODVisual( zCVisual* )                                          zCall( 0x005D9F60 );
    static void operator delete( void*, char const*, char const*, int )        zCall( 0x0046E340 );
    static void InitVisualSystem()                                             zCall( 0x005DA000 );
    static void CleanupVisualSystem()                                          zCall( 0x005DA1A0 );
    static zCVisual* LoadVisual( zSTRING const& )                              zCall( 0x005DA1F0 );
    virtual zCClassDef* _GetClassDef() const                                   zCall( 0x004C0D20 );
    virtual ~zCVisual()                                                        zCall( 0x005D9F10 );
    virtual int Render( zTRenderContext& )                                     zPureCall;
    virtual int IsBBox3DLocal()                                                zCall( 0x0054FB90 );
    virtual zTBBox3D GetBBox3D()                                               zPureCall;
    virtual zCOBBox3D* GetOBBox3D()                                            zCall( 0x004C0D30 );
    virtual zSTRING GetVisualName()                                            zPureCall;
    virtual int GetVisualDied()                                                zCall( 0x004C0D40 );
    virtual void SetVisualUsedBy( zCVob* )                                     zCall( 0x0054FBA0 );
    virtual void DynLightVisual( zCArray<zCVobLight*> const&, zMAT4* )         zCall( 0x004C0D50 );
    virtual unsigned long GetRenderSortKey() const                             zCall( 0x004C0D60 );
    virtual int CanTraceRay() const                                            zCall( 0x004C0D70 );
    virtual int TraceRay( zVEC3 const&, zVEC3 const&, int, zTTraceRayReport& ) zCall( 0x005D9FF0 );
    virtual void HostVobRemovedFromWorld( zCVob*, zCWorld* )                   zCall( 0x004C0D80 );
    virtual void HostVobAddedToWorld( zCVob*, zCWorld* )                       zCall( 0x004C0D90 );
    virtual zSTRING const* GetFileExtension( int )                             zCall( 0x004C0DA0 );
    virtual void GetLODVisualAndAlpha( float, zCVisual*&, float& )             zCall( 0x005D9F90 );
    virtual zCVisual* LoadVisualVirtual( zSTRING const& ) const                zCall( 0x004C0DB0 );

    // static properties
    static zCArray<zCVisual*>& s_visualClassList;
  };

  class zCVisualAnimate : public zCVisual {
  public:
    zCLASS_DECLARATION( zCVisualAnimate )

    zCVisualAnimate() {}
    virtual zCClassDef* _GetClassDef() const        zCall( 0x0055CDE0 );
    virtual ~zCVisualAnimate()                      zCall( 0x0055CFB0 );
    virtual int Render( zTRenderContext& )          zPureCall;
    virtual zTBBox3D GetBBox3D()                    zPureCall;
    virtual zSTRING GetVisualName()                 zPureCall;
    virtual void StartAnimation( zSTRING const& )   zPureCall;
    virtual void StopAnimation( zSTRING const& )    zPureCall;
    virtual int IsAnimationActive( zSTRING const& ) zPureCall;
    virtual zSTRING const* GetAnyAnimation()        zPureCall;
  };

  class zCDecal : public zCVisual {
  public:
    zCLASS_DECLARATION( zCDecal )

    zCMaterial* decalMaterial;
    float xdim;
    float ydim;
    float xoffset;
    float yoffset;
    int decal2Sided;

    void zCDecal_OnInit()                                               zCall( 0x00541E20 );
    zCDecal()                                                           zInit( zCDecal_OnInit() );
    void SetTexture( zSTRING& )                                         zCall( 0x00542240 );
    void SetTexture( zCTexture* )                                       zCall( 0x00542250 );
    void SetDecalDim( float, float )                                    zCall( 0x00542260 );
    static zCObject* _CreateNewInstance()                               zCall( 0x00541CD0 );
    static void operator delete( void*, char const*, char const*, int ) zCall( 0x00541DE0 );
    static void CleanupDecals()                                         zCall( 0x00541F80 );
    static void CreateDecalMeshes()                                     zCall( 0x00542000 );
    virtual zCClassDef* _GetClassDef() const                            zCall( 0x00541E00 );
    virtual void Archive( zCArchiver& )                                 zCall( 0x00542590 );
    virtual void Unarchive( zCArchiver& )                               zCall( 0x00542650 );
    virtual ~zCDecal()                                                  zCall( 0x00541F10 );
    virtual int Render( zTRenderContext& )                              zCall( 0x00542280 );
    virtual int IsBBox3DLocal()                                         zCall( 0x00541E10 );
    virtual zTBBox3D GetBBox3D()                                        zCall( 0x005423E0 );
    virtual zSTRING GetVisualName()                                     zCall( 0x00542430 );
    virtual void SetVisualUsedBy( zCVob* )                              zCall( 0x005423C0 );
    virtual void DynLightVisual( zCArray<zCVobLight*> const&, zMAT4* )  zCall( 0x00542480 );
    virtual unsigned long GetRenderSortKey() const                      zCall( 0x00542230 );
    virtual zSTRING const* GetFileExtension( int )                      zCall( 0x00542070 );
    virtual zCVisual* LoadVisualVirtual( zSTRING const& ) const         zCall( 0x005420D0 );

    // static properties
    static zCMesh*& decalMesh1Sided;
    static zCMesh*& decalMesh2Sided;
  };

  class zCMesh : public zCVisual {
  public:
    zCLASS_DECLARATION( zCMesh )

    enum zTCalcVertNormalMode {
      zMSH_VERTNORMAL_MAT,
      zMSH_VERTNORMAL_SMOOTH,
      zMSH_VERTNORMAL_FACET
    };

    int numPoly;
    int numVert;
    int numFeat;
    zCVertex** vertList;
    zCPolygon** polyList;
    zCVertFeature** featList;
    zCVertex* vertArray;
    zCPolygon* polyArray;
    zCVertFeature* featArray;
    zTBBox3D bbox3D;
    zCOBBox3D obbox3D;
    int masterFrameCtr;
    zCMesh* next;
    zCMesh* prev;
    zSTRING meshName;
    char hasLightmaps;
    int numVertAlloc;
    int numPolyAlloc;

    void zCMesh_OnInit()                                                                     zCall( 0x0054F970 );
    void LODRecalcEdge( zTLODEdge&, zCArraySort<zCPolygon*>& )                               zCall( 0x00528FC0 );
    void LODGenerate( zCArraySort<zCPolygon*>&, zCArraySort<zCPolygon*>& )                   zCall( 0x005297D0 );
    zCMesh()                                                                                 zInit( zCMesh_OnInit() );
    void DeleteAll()                                                                         zCall( 0x0054FE00 );
    zCVertex* VertexInMesh( zVEC3 const& )                                                   zCall( 0x00550C40 );
    void AllocVerts( int )                                                                   zCall( 0x00550D10 );
    void AllocPolys( int )                                                                   zCall( 0x00550E10 );
    zCVertex* AddVertex( zCVertex* )                                                         zCall( 0x00550EE0 );
    zCVertex* AddVertex( zVEC3& )                                                            zCall( 0x00551060 );
    zCVertex* AddVertexSmart( zVEC3& )                                                       zCall( 0x005511C0 );
    zCPolygon* AddPoly( zVEC3&, zVEC3&, zVEC3&, zVEC2&, zVEC2&, zVEC2& )                     zCall( 0x005512F0 );
    zCPolygon* AddPoly( zCVertex*, zCVertex*, zCVertex* )                                    zCall( 0x005515A0 );
    zCPolygon* AddPoly( zCVertex*, zCVertex*, zCVertex*, zCVertex* )                         zCall( 0x005516C0 );
    zCPolygon* AddPoly( zCPolygon* )                                                         zCall( 0x005517F0 );
    zCPolygon* AddPoly()                                                                     zCall( 0x005518A0 );
    void DeletePoly( zCPolygon* )                                                            zCall( 0x005519A0 );
    void DynLightScalePrelit( zCOLOR )                                                       zCall( 0x00551A90 );
    void PrelightMesh( zMAT4* )                                                              zCall( 0x00551AA0 );
    zCPolygon* SharePoly( int ) const                                                        zCall( 0x00551F10 );
    zCPolygon* CheckRayPolyIntersection( zVEC3 const&, zVEC3 const&, zVEC3& )                zCall( 0x00551F30 );
    zCPolygon* CheckRayPolyIntersection( zCCamera&, int, int, zVEC3& )                       zCall( 0x00551F90 );
    zCPolygon* PickPolygon( zVEC3 const&, zVEC3 const&, zVEC3& )                             zCall( 0x00552140 );
    zCPolygon* PickPolygon( zCCamera&, int, int, zVEC3& )                                    zCall( 0x00552210 );
    void CalcVertexNormals( zTCalcVertNormalMode, zCBspTree* )                               zCall( 0x00552590 );
    void UnSmoothMesh()                                                                      zCall( 0x00552C70 );
    void SetDefaultPlanarMapping( float, float )                                             zCall( 0x00552D10 );
    void CalcBBox3D( int )                                                                   zCall( 0x00552DA0 );
    void Center()                                                                            zCall( 0x00552F10 );
    void TransformAllVerts( zMAT4 const&, int )                                              zCall( 0x00553060 );
    void MergeMesh( zCMesh*, zMAT4 const& )                                                  zCall( 0x00553120 );
    void CalcNormals()                                                                       zCall( 0x005534E0 );
    void SetMaterial( zCMaterial* )                                                          zCall( 0x00553510 );
    void ScaleXZ( float, float )                                                             zCall( 0x00553570 );
    void Scale( float, float, float )                                                        zCall( 0x005535E0 );
    void CheckForMaterials() const                                                           zCall( 0x005536A0 );
    int Render_novt( zTRenderContext&, zCOLOR* )                                             zCall( 0x00553860 );
    void RenderDecal( float, float, float, int )                                             zCall( 0x00553B40 );
    void RenderDecal( zTRenderContext&, int )                                                zCall( 0x00553D00 );
    void ResetStaticLight()                                                                  zCall( 0x00553F50 );
    void SetStaticLight( zCOLOR )                                                            zCall( 0x00553F90 );
    void SetLightDyn( zCOLOR )                                                               zCall( 0x00553FD0 );
    void SetLightStatAlpha( unsigned char )                                                  zCall( 0x00554010 );
    void ResetLightDynToLightStat()                                                          zCall( 0x00554050 );
    void AddToLightDyn( zCOLOR )                                                             zCall( 0x00554090 );
    void SaveMSH( zCFileBIN& )                                                               zCall( 0x00555670 );
    void SaveMSH( zSTRING const& )                                                           zCall( 0x00555690 );
    int LoadMSH( zCFileBIN&, int )                                                           zCall( 0x00557280 );
    int LoadMSH( zSTRING const&, int )                                                       zCall( 0x00558800 );
    void CreateListsFromArrays() const                                                       zCall( 0x00558AB0 );
    void ClearLists() const                                                                  zCall( 0x00558BB0 );
    void ArraysToLists() const                                                               zCall( 0x00558C10 );
    void ShareFeatures()                                                                     zCall( 0x00558CF0 );
    void UnshareFeatures()                                                                   zCall( 0x005599D0 );
    void FlipPolys()                                                                         zCall( 0x00559AF0 );
    void SortPolysByMaterial()                                                               zCall( 0x00559B40 );
    void SortPolysByList( zCPolygon**, int )                                                 zCall( 0x00559BF0 );
    void DeletePolyAndVerts( zCPolygon* )                                                    zCall( 0x0055A440 );
    void DeletePolyAndVerts( unsigned long )                                                 zCall( 0x0055A4D0 );
    void RemoveDegeneratePolys()                                                             zCall( 0x0055A660 );
    void CombineLightmaps()                                                                  zCall( 0x0055A810 );
    void LightMesh( zCVobLight&, zMAT4&, zCWorld* )                                          zCall( 0x005FB040 );
    static void operator delete( void*, char const*, char const*, int )                      zCall( 0x00526210 );
    static zCObject* _CreateNewInstance()                                                    zCall( 0x0054F900 );
    static zCMesh* SearchName( zSTRING const& )                                              zCall( 0x00550130 );
    static zCMesh* Load( zSTRING const& )                                                    zCall( 0x005501A0 );
    static zCMesh* CreateQuadMesh( int )                                                     zCall( 0x005540D0 );
    static zCMesh* CreateTriMesh()                                                           zCall( 0x00554440 );
    static int CheckTexUVOnPlane( zCArray<zCVertex*> const&, zCArray<zCVertFeature> const& ) zCall( 0x00554640 );
    static void ConvertTrisToNPolys( zCPolygon**, int, zCMesh*, int )                        zCall( 0x00554B60 );
    static unsigned short GetFileVersion()                                                   zCall( 0x00555660 );
    static void SaveMSH( zCFileBIN&, zCPolygon**, int, zCMesh* )                             zCall( 0x005557E0 );
    virtual zCClassDef* _GetClassDef() const                                                 zCall( 0x0054FBB0 );
    virtual ~zCMesh()                                                                        zCall( 0x0054FC90 );
    virtual int Render( zTRenderContext& )                                                   zCall( 0x005537E0 );
    virtual zTBBox3D GetBBox3D()                                                             zCall( 0x0054FC10 );
    virtual zCOBBox3D* GetOBBox3D()                                                          zCall( 0x0054FC40 );
    virtual zSTRING GetVisualName()                                                          zCall( 0x0054FBC0 );
    virtual void DynLightVisual( zCArray<zCVobLight*> const&, zMAT4* )                       zCall( 0x00551A80 );
    virtual int CanTraceRay() const                                                          zCall( 0x0054FC50 );
    virtual int TraceRay( zVEC3 const&, zVEC3 const&, int, zTTraceRayReport& )               zCall( 0x00552410 );
    virtual zSTRING const* GetFileExtension( int )                                           zCall( 0x0054FDD0 );
    virtual zCVisual* LoadVisualVirtual( zSTRING const& ) const                              zCall( 0x0054FDF0 );

    // static properties
    static int& s_autoConvertMeshes;
    static int& s_numMeshes;
    static zCMesh*& s_meshRoot;
  };

} // namespace Gothic_I_Classic

#endif // __ZVISUAL_H__VER0__