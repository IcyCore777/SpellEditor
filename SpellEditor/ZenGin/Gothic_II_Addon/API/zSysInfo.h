// Supported with union (c) 2018 Union team

#ifndef __ZSYS_INFO_H__VER3__
#define __ZSYS_INFO_H__VER3__

namespace Gothic_II_Addon {

  class zCSystemInfo {
  public:
    enum zTOperatingSystem {
      OS_UNKNOWN,
      OS_WINDOWS_3_1,
      OS_WINDOWS_95,
      OS_WINDOWS_98,
      OS_WINDOWS_98ME,
      OS_WINDOWS_NT,
      OS_WINDOWS_2000,
      OS_OTHER
    };

    enum zTCpuType {
      CPU_UNKNOWN,
      CPU_INTEL_PENTIUM_I,
      CPU_INTEL_PENTIUM_II,
      CPU_INTEL_PENTIUM_III,
      CPU_INTEL_PENTIUM_IV,
      CPU_AMD_K6,
      CPU_AMD_ATHLON,
      CPU_OTHER
    };

    zSTRING osName;
    zSTRING osServicePack;
    zSTRING cpuID;
    unsigned long cpuSpeed;
    unsigned long memSize;
    unsigned long memAvailable;
    zSTRING graName;
    unsigned long graMemSize;

    void zCSystemInfo_OnInit() zCall( 0x0046D1B0 );
    zCSystemInfo()             zInit( zCSystemInfo_OnInit() );
    void AnalyseMemory()       zCall( 0x0046D450 );
    void AnalyseCpu()          zCall( 0x0046D480 );
    void AnalyseOs()           zCall( 0x0046D650 );
    void AnalyseGcard()        zCall( 0x0046DA80 );
    zSTRING GetOsName()        zCall( 0x0046E400 );
    virtual ~zCSystemInfo()    zCall( 0x0046D370 );
    virtual void AnalyseNow()  zCall( 0x0046DAA0 );
  };

} // namespace Gothic_II_Addon

#endif // __ZSYS_INFO_H__VER3__