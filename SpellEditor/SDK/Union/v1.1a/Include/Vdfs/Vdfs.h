// Supported with union (c) 2018 Union team

#ifndef __UNION_VDFS_H__
#define __UNION_VDFS_H__

namespace Vdfs32 {


#define VDF_VIRTUAL       (1)
#define VDF_PHYSICAL      (2)
#define VDF_PHYSICALFIRST (4)
#define VDF_DEFAULT VDF_VIRTUAL | VDF_PHYSICAL


  // open file and return handle
  VDFAPI long32 vdf_fopen( text fullfname, long32 flags );


  // close file
  VDFAPI long32 vdf_fclose( long32 handle );


  // read file to the buffer. return the real readed size in bytes
  VDFAPI long32 vdf_fread( long32 handle, HBuffer buffer, long32 size );


  // move the reading cursor to specified position
  VDFAPI long32 vdf_fseek( long32 handle, long32 pos );


  // get the reading cursor
  VDFAPI long32 vdf_ftell( long32 handle );


  // check the file by full name. flags - is prefer file mode - physical 
  // or virtual. if choose both, system will return the highest-priority 
  // flag of the file. or Null if file does not exists.
  VDFAPI long32 vdf_fexists( text fullfname, long32 flags );


  // finds files by relative path. second argument - the
  // found fullname if return value is not false.
  VDFAPI long32 vdf_searchfile( text filename, text fullfilename );


  // return size of file
  VDFAPI long32 vdf_ffilesize( long32 handle );


  // for union vdfs this parms unused
  VDFAPI long32 vdf_initall( long32 numdisks = None, text cdid = None, long32* cddrives = None, long32* disksfound = None );


  //
  ASTAPI long32 vdf_regvol( const char* volname );



  class zFile {
    long Handler;
    long Flow;
    string Name;

  public:
    zFile() {
      Handler = Invalid;
    }
    zFile( const string& name, const long& flow = VDF_DEFAULT, const uint& index = 0 ) {
      Handler = Invalid;
      Open( name, flow, index );
    }

    bool Open( string name, const long& flow = VDF_DEFAULT, const uint& index = 0 ) {
      if( index > 0 ) {
        char NameBuffer[1024];
        if( !vdf_searchfile( name.ToChar(), NameBuffer ) )
          return false;

        string Names = NameBuffer;
        Name = Names.GetWord( "|", index );
        if( Name.IsEmpty() )
          return false;

        Flow = vdf_fexists( Name.ToChar(), flow );
        Handler = vdf_fopen( Name.ToChar(), Flow );
      }
      else {
        Name = name;
        Flow = vdf_fexists( Name.ToChar(), flow );
        if( Flow == 0 )
          return false;
        Handler = vdf_fopen( Name.ToChar(), Flow );
      }
      return true;
    }
    
  protected:
    long Read( char*& buff, const long& length ) {
      buff = new char[length];
      return vdf_fread( Handler, buff, length );
    }

  public:
    template <class T>
    long ReadToEnd( T& buff, const long& length ) {
      return Read( (char*&)buff, length );
    }

  protected:
    long ReadToEnd( char*& buff ) {
      long tell = Tell();
      long size = Size();
      Seek( 0 );
      buff = new char[size];
      long readed = vdf_fread( Handler, buff, size );
      Seek( tell );
      return readed;
    }

  public:
    template <class T>
    long ReadToEnd( T& buff ) {
      return ReadToEnd( (char*&)buff );
    }

    long ReadString( string& str ) {
      long tell = Tell();
      long size = Size();
      Seek( 0 );
      char* buff = new char[size];
      long readed = vdf_fread( Handler, buff, size );
      str = string( buff, readed );
      delete buff;
      Seek( tell );
      return readed;
    }

    long Size() {
      return vdf_ffilesize( Handler );
    }

    long Tell() {
      return vdf_ftell( Handler );
    }

    void Seek( const long& pos ) {
      vdf_fseek( Handler, pos );
    }

    bool IsVirtual() {
      if( Flow & VDF_PHYSICALFIRST )
        return (Flow & VDF_PHYSICAL) == 0;
      return Flow & VDF_VIRTUAL;
    }

    bool IsExists() {
      return Handler != Invalid;
    }

    void Close() {
      if( Handler != Invalid ) {
        vdf_fclose( Handler );
        Handler = Invalid;
      }
    }
    operator bool() {
      return IsExists();
    }

    virtual ~zFile() {
      Close();
    }
  };
}

#endif // __UNION_VDFS_H__