// Supported with union (c) 2018 Union team

#ifndef __SYSTEMPACK_PARSER_FILTERS_H__
#define __SYSTEMPACK_PARSER_FILTERS_H__

namespace SystemPack
{
  extern ASTAPI const Common::CString sDefaultSpace;

  extern ASTAPI const Common::CString sResource_Local;
  extern ASTAPI const Common::CString sResource_Option;
  extern ASTAPI const Common::CString sResource_Number;
  extern ASTAPI const Common::CString sResource_Operator;

  extern ASTAPI const Common::CString sNumber_Integer;
  extern ASTAPI const Common::CString sNumber_PureHex;
  extern ASTAPI const Common::CString sNumber_Float;
  extern ASTAPI const Common::CString sNumber_LineHex;

  extern ASTAPI const Common::CString sBrackets_Round   [2];
  extern ASTAPI const Common::CString sBrackets_Square  [2];
  extern ASTAPI const Common::CString sBrackets_TextLine[2];
  extern ASTAPI const Common::CString sBrackets_HexLine [2];
  extern ASTAPI const Common::CString sBrackets_Comment [2];

  extern ASTAPI const Common::CString sAssociation_Quote     [2];
  extern ASTAPI const Common::CString sAssociation_EndLine   [2];
  extern ASTAPI const Common::CString sAssociation_Tabulation[2];

  const uint32  ulResourcesNum    = 24;
  const uint32  ulNumbersNum      = 4;
  const uint32  ulBracketsNum     = 5;
  const uint32  ulAssociationsNum = 3;

  extern ASTAPI const Common::CString  arrResource   [ulResourcesNum];
  extern ASTAPI const Common::CString  arrNumber     [ulNumbersNum];
  extern ASTAPI const Common::CString* arrBrackets   [ulBracketsNum];
  extern ASTAPI const Common::CString* arrAssociation[ulAssociationsNum];

  const uint32  ulOperatorsNum = 21;

  extern ASTAPI const Common::CString sEngineBlock[2];
  extern ASTAPI const Common::CString sPatchBlock [2];
  extern ASTAPI const Common::CString sOperators  [ulOperatorsNum];
} // namespace SystemPack

#endif // __SYSTEMPACK_PARSER_FILTERS_H__