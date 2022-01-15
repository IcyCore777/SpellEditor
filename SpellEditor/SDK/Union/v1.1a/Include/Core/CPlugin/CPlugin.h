// Supported with union (c) 2018 Union team

#ifndef __UNION_PLUGIN_H__
#define __UNION_PLUGIN_H__

namespace UnionCore
{
  class CPlugin
  {
    CString  sPluginDLL;
    HPLUGIN  hModule;

    CPlugin();
    ~CPlugin();

  public:
    ASTAPI CString GetName() const;
    ASTAPI HPLUGIN GetModule() const;
           
           static void    LoadModules( CString );
           static void    ExitModules();
    ASTAPI static HMODULE GetGothicModule();
    ASTAPI static HMODULE GetAgamaModule();
    ASTAPI static HMODULE FindModule( CString );
           static void    ClearStorage();

    ASTAPI static const CList<CPlugin>& GetPluginList();
    ASTAPI static const CPlugin*        GetCurrentPlugin();
  };

  HPLUGIN ASTAPI LoadLibraryAST( const CString& name );
} // namespace UnionCore

#endif // __UNION_PLUGIN_H__