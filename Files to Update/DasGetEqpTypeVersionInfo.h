/*! @file DasGetEqpTypeVersionInfo.h

 @brief バージョン情報
 
 @author t.kawabuchi
 
 @date	2021/12/05 新規作成
 
 @version

	DT000_100.01  2021/12/05  t.kawabuchi
		新規作成。
*/

#ifndef __DAS_GETEQPTYPE_VERINFO_H__
#define __DAS_GETEQPTYPE_VERINFO_H__
// バージョン情報の設定
#include <Utility/VersionInfo/Vi_Version.h>	// Share対応 #include <version_info/Vi_Version.h>

// バージョン情報
// const Vi_Version DasGetEqpType_Version_Prev ("DasGetEqpType.Prev", "2014/06/05", "556", "01", "RELS_DASGETEQPTYPE_556-01", "", "hp");
const Vi_Version DasGetEqpType_Versio_Prevn( "DasGetEqpType.Prev", "2021/12/05", "000", "01", "RELS_DASGETEQPTYPE_000-01", "", "hp");
const Vi_Version DasGetEqpType_Version( "DasGetEqpType", "2023/08/29", "345", "01", "RELS_DASGETEQPTYPE_000-01", "", "hp");

#endif
