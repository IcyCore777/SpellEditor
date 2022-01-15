// Supported with union (c) 2018 Union team

#ifndef __ZMATERIAL_H__VER3__
#define __ZMATERIAL_H__VER3__

#include "zRenderer.h"
#include "zTexture.h"
#include "zFft.h"

namespace Gothic_II_Addon {

  enum zTMat_Group {
    zMAT_GROUP_UNDEF,
    zMAT_GROUP_METAL,
    zMAT_GROUP_STONE,
    zMAT_GROUP_WOOD,
    zMAT_GROUP_EARTH,
    zMAT_GROUP_WATER,
    zMAT_GROUP_SNOW,
    zMAT_NUM_MAT_GROUP
  };

  enum zTWaveAniMode {
    zWAVEANI_NONE,
    zWAVEANI_GROUND_AMBIENT,
    zWAVEANI_GROUND,
    zWAVEANI_WALL_AMBIENT,
    zWAVEANI_WALL,
    zWAVEANI_ENV,
    zWAVEANI_WIND_AMBIENT,
    zWAVEANI_WIND
  };

  class zCTexAniCtrl {
  public:
    int aniChannel;
    float actFrame;
    float aniFPS;
    unsigned long frameCtr;
    int bOneShotAni;

    void zCTexAniCtrl_OnInit()    zCall( 0x00565D30 );
    zCTexAniCtrl()                zInit( zCTexAniCtrl_OnInit() );
    void AdvanceAni( zCTexture* ) zCall( 0x00565D50 );
	void		SetAniFPS(const zREAL fps) { aniFPS = fps / 1000.0F; };
	zREAL		GetAniFPS() const { return aniFPS * 1000.0F; };
	zREAL		GetActFrame() const { return actFrame; };
	void		SetActFrame(const zREAL f) { actFrame = f; };
	void		SetAniChannel(const int c) { aniChannel = c; };
	int			GetAniChannel() const { return aniChannel; };
	void		SetOneShotAni(const zBOOL b) { bOneShotAni = b; };
	zBOOL		GetOneShotAni() const { return bOneShotAni; };

	static void IncMasterFrameCtr() { masterFrameCtr++; };
    // static properties
    static unsigned long& masterFrameCtr;
  };

  class zCMaterial : public zCObject {
  public:
    zCLASS_DECLARATION( zCMaterial )

    enum {
      zMAT_USAGE_LEVEL,
      zMAT_USAGE_OTHER
    };

    zCArray<zCPolygon*> polyList;
    unsigned long polyListTimeStamp;
    zCTexture* texture;
    zCOLOR color;
    float smoothAngle;
    zTMat_Group matGroup;
    zCBspSector* bspSectorFront;
    zCBspSector* bspSectorBack;
    zCTexAniCtrl texAniCtrl;
    zSTRING* detailObjectVisualName;
    float kambient;
    float kdiffuse;
    float m_bEnvironmentalMappingStrength;
    group {
      unsigned char smooth                   : 1;
      unsigned char dontUseLightmaps         : 1;
      unsigned char texAniMap                : 1;
      unsigned char lodDontCollapse          : 1;
      unsigned char noCollDet                : 1;
      unsigned char forceOccluder            : 1;
      unsigned char m_bEnvironmentalMapping  : 1;
      unsigned char polyListNeedsSort        : 1;
      unsigned char matUsage                 : 8;
      unsigned char libFlag                  : 8;
      zTRnd_AlphaBlendFunc rndAlphaBlendFunc : 8;
      unsigned char m_bIgnoreSun             : 1;
    };
    zTWaveAniMode m_enuWaveMode;
    zTFFT m_enuWaveSpeed;
    float m_fWaveMaxAmplitude;
    float m_fWaveGridSize;
    zCTexture* detailTexture;
    float detailTextureScale;
    zVEC2 texAniMapDelta;
    zVEC2 default_mapping;
    zVEC2 texScale;

    void zCMaterial_OnInit()                               zCall( 0x00563E00 );
    void zCMaterial_OnInit( zSTRING const& )               zCall( 0x00563EE0 );
    void zCMaterial_OnInit( zCMaterial const& )            zCall( 0x00563FA0 );
    zSTRING const& GetName() const                         zCall( 0x0055FF10 );
    zCMaterial()                                           zInit( zCMaterial_OnInit() );
    zCMaterial( zSTRING const& a0 )                        zInit( zCMaterial_OnInit( a0 ));
    zCMaterial( zCMaterial const& a0 )                     zInit( zCMaterial_OnInit( a0 ));
    zCMaterial& operator =( zCMaterial const& )            zCall( 0x00564050 );
    void InitThisByMaterial( zCMaterial const& )           zCall( 0x00564130 );
    void InitValues()                                      zCall( 0x00564260 );
    void SetDetailObjectVisual( zSTRING const& )           zCall( 0x00564370 );
    zSTRING const& GetDetailObjectVisual() const           zCall( 0x005644F0 );
    void ApplyTexAniMapping( zCPolygon* )                  zCall( 0x00564500 );
    zVEC3 GetTexAniVector( zCPolygon* )                    zCall( 0x00564590 );
    int IsPortalMaterial() const                           zCall( 0x005648D0 );
    void SetTexAniMappingDir( zVEC2 const& )               zCall( 0x005649C0 );
    void SetTexture( zSTRING& )                            zCall( 0x005649E0 );
    void SetTexture( zCTexture* )                          zCall( 0x00564B20 );
    void SetDetailTexture( zSTRING& )                      zCall( 0x00564CD0 );
    void SetDetailTexture( zCTexture* )                    zCall( 0x00564DD0 );
    void AutoAssignDetailTexture()                         zCall( 0x00564E20 );
    zVEC2 GetTexScale()                                    zCall( 0x00564FC0 );
    void SetTexScale( zVEC2 )                              zCall( 0x00565020 );
    void RemoveTexture()                                   zCall( 0x00565040 );
    zSTRING const& GetMatGroupString() const               zCall( 0x00565170 );
    void SetMatGroupByString( zSTRING const& )             zCall( 0x005651D0 );
    void RefreshAvgColorFromTexture()                      zCall( 0x005653D0 );
    zCTexture* GetAniTexture()                             zCall( 0x0064BA20 );
    //static void operator delete( void* )                   zCall( 0x00474C50 );
    static zCObject* _CreateNewInstance()                  zCall( 0x00563D20 );
    static zSTRING const& GetMatGroupString( zTMat_Group ) zCall( 0x00565110 );
    static zCMaterial* SearchName( zSTRING& )              zCall( 0x00565E30 );
    virtual zCClassDef* _GetClassDef() const               zCall( 0x00563DF0 );
    virtual void Archive( zCArchiver& )                    zCall( 0x00565420 );
    virtual void Unarchive( zCArchiver& )                  zCall( 0x00565780 );
    virtual ~zCMaterial()                                  zCall( 0x00564070 );
	void					SetAlphaBlendFunc(const zTRnd_AlphaBlendFunc	a) { rndAlphaBlendFunc = a; };
	zTRnd_AlphaBlendFunc	GetAlphaBlendFunc() const { return rndAlphaBlendFunc; };
	void					SetLibFlag(const zBYTE flag) { libFlag = flag; };
	zBYTE					GetLibFlag() const { return libFlag; };
	void					SetUsage(const zBYTE usage) { matUsage = usage; };
	void					SetUsageFromDefault() { matUsage = s_matUsageDefault; };
	zBYTE					GetUsage() const { return matUsage; };
	static void				SetUsageDefault(const zBYTE usage) { s_matUsageDefault = usage; };
	zTMat_Group				GetMatGroup() const { return matGroup; };
	zBOOL					SetName(const zSTRING& name) { return SetObjectName(name); };
	void					SetColor(zBYTE r, zBYTE g, zBYTE b) { color.r = r; color.g = g; color.b = b; };
	void					SetColor(zCOLOR col) { color = col; };
	zCOLOR					GetColor() const { return color; };
	zBYTE					GetColorR() const { return color.r; };
	zBYTE					GetColorG() const { return color.g; };
	zBYTE					GetColorB() const { return color.b; };
	void					SetAlpha(const zBYTE a) { color.alpha = a; };
	zCTexture*				GetDetailTexture() const { return detailTexture; }
	zREAL					GetDetailTextureScale() const { return detailTextureScale; }

	zBYTE					GetAlpha() const { return color.alpha; };
	void					SetTexAniMapping(zBOOL b) { texAniMap = b; };
	zBOOL					GetTexAniMapping() const { return texAniMap; };
	zCTexture*				GetTexture() const { return texture; };
	zVEC2					GetTexAniMappingDir() const { return texAniMapDelta; };
	void					SetDefaultMapping(const zVEC2& defMap) { default_mapping = defMap; };
	zVEC2					GetDefaultMapping() const { return default_mapping; };
	void					SetEnvMapStrength(const zREAL a_bEnvMapStr) { m_bEnvironmentalMappingStrength = a_bEnvMapStr; };
	zREAL					GetEnvMapStrength()	const { return m_bEnvironmentalMappingStrength; };
	zBOOL					GetEnvMapEnabled() const { return m_bEnvironmentalMapping; };
	void					SetEnvMapEnabled(const zBOOL a_bEnEnvMap) { m_bEnvironmentalMapping = a_bEnEnvMap; };
    // static properties
	zBOOL IsSectorMaterial()const
	{
		zSTRING name = GetName();
		if (name.Length() >= 2)
			if (name[0] == 'S')
				if (name[1] == ':') return TRUE;
		return FALSE;
	}
    static unsigned char& s_matUsageDefault;
  };

} // namespace Gothic_II_Addon

#endif // __ZMATERIAL_H__VER3__