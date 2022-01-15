// Supported with union (c) 2018 Union team

#ifndef __UNION_PLUGIN_H__
#define __UNION_PLUGIN_H__

namespace UnionCore
{
  class CPlugin
  {
    Common::CString  sPluginDLL;
    HPLUGIN  hModule;

    CPlugin();
    ~CPlugin();

  public:
    ASTAPI Common::CString GetName() const;
    ASTAPI HPLUGIN GetModule() const;
           
           static void    LoadModules( Common::CString );
           static void    ExitModules();
    ASTAPI static HMODULE GetGothicModule();
    ASTAPI static HMODULE GetAgamaModule();
    ASTAPI static HMODULE FindModule( Common::CString );
           static void    ClearStorage();

    ASTAPI static const Common::CList<CPlugin>& GetPluginList();
    ASTAPI static const CPlugin*        GetCurrentPlugin();
  };

  HPLUGIN ASTAPI LoadLibraryAST( const Common::CString& name );
} // namespace UnionCore

#endif // __UNION_PLUGIN_H__