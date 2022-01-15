// Supported with union (c) 2018 Union team

#ifndef __UNION_VDFS_H__
#define __UNION_VDFS_H__

namespace Vdfs32 {


#define VDF_VIRTUAL       (1)
#define VDF_PHYSICAL      (2)
#define VDF_PHYSICALFIRST (4)


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
}

#endif // __UNION_VDFS_H__