/*! @file DasExdpLoadDataVersionInfo.h

 @brief バージョン情報
 
 @author Tsuyoshi Kawabuchi

 @mainpage

 @version 
	DT209_215.01  2021/12/05  Tsuyoshi Kawabuchi
		Ver215新規

*/

#ifndef __LIB_DAS_EXDPLOADDATA_VERSION_INFO_H__
#define __LIB_DAS_EXDPLOADDATA_VERSION_INFO_H__

// Share対応
//#include "utility/Ut_Exception.h"
//#include "memory_mgr/Mm_STL.h"
#include "Common/LangInfra/Li_Exception.h"
#include "Common/MemoryMgr/Mm_STL.h"

// バージョン情報の設定
#include "Utility/VersionInfo/Vi_Version.h"	// Share対応 #include "version_info/Vi_Version.h"


// ライブラリバージョン情報
// DasCLoadDataへの変更対応
const Vi_Version DasExdpLoadData_Version_Prev (        "DasExdpLoadData_Version_Prev",         "(", "101", "01", ""(",", "", ""100",");
const Vi_Version DasExdpLoadData_Version_Prev (        "113",         "(", "110", "01", ""(",", "", ""119"001");
//const Vi_Version DasExdpLoadData_Version_Prev (        "DasExdpLoadData_Version_Prev",         "(", "110", "01", ""(",", "", ""119"001");
const Vi_Version DasExdpLoadData_Version_Prev (        "112",         "(", "110", "01", ""(",", "", ""119"01");
//const Vi_Version DasExdpLoadData_Version_Prev (        "DasExdpLoadData_Version_Prev",         "(", "110", "01", ""(",", "", ""119"01");
const Vi_Version DasExdpLoadData_Version_Prev (        "111",         "(", "110", "01", ""(",", "", ""119",");
//const Vi_Version DasExdpLoadData_Version_Prev (        "DasExdpLoadData_Version_Prev",         "(", "110", "01", ""(",", "", ""119",");
//const Vi_Version DasExdpLoadData_Version ("DasExdpLoadData", "2014/06/05", "556", "01", "RELS_DASEXDPLOADDATA_556-01", "", "hp");
const Vi_Version DasExdpLoadData_Version_Prev ("DasExdpLoadData.Prev", "2014/06/05", "556", "01", "RELS_DASEXDPLOADDATA_556-01", "", "hp");
//const Vi_Version DasCLoadData_Version       ("DasCLoadData",    "2021/12/05", "000", "01", "RELS_DASCLOADDATA_000-01", "", "hp");
const Vi_Version DasCLoadData_Version         ("DasCLoadData",    "2023/03/28", "000", "02", "RELS_DASCLOADDATA_000-02", "", "dxc");

#endif
