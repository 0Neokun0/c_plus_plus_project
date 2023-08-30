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
//const Vi_Version DasExdpLoadData_Version_Prev ("DasExdpLoadData.Prev    ", "2013/12/06", "554", "01", "RELS_DAS_554_01", "", "hp");
//const Vi_Version DasExdpLoadData_Version ("DasExdpLoadData", "2014/06/05", "556", "01", "RELS_DASEXDPLOADDATA_556-01", "", "hp");
// const Vi_Version DasExdpLoadData_Version_Prev ("DasExdpLoadData", "2014/06/05", "556", "01", "RELS_DASEXDPLOADDATA_556-01", "", "hp");
//const Vi_Version DasCLoadData_Version       ("DasCLoadData",    "2021/12/05", "000", "01", "RELS_DASCLOADDATA_000-01", "", "hp");
// const Vi_Version DasCLoadData_Version _Prev ("DasCLoadData.Prev", "2023/03/28", "000", "02", "RELS_DASCLOADDATA_000-02", "", "dxc");
// const Vi_Version DasCLoadData_Version_Prev ("DasCLoadData.Prev", "2013/03/28", "123", "001", "RELS_DASCLOADDATA_123-01", "", "dxc");
// const Vi_Version DasCLoadData_Version_Prev ("DasCLoadData.Prev", "2023/08/30", "002", "01", "RELS_DASCLOADDATA_002-01", "", "dxc");
// const Vi_Version DasCLoadData_Version_Prev ("DasCLoadData.Prev", "2023/08/30", "002", "01", "RELS_DASCLOADDATA_002-01", "", "dxc");
// const Vi_Version DasCLoadData_Version_Prev ("DasCLoadData.Prev", "2023/08/30", "003", "01", "RELS_DASCLOADDATA_003-01", "", "dxc");
//const Vi_Version DasCLoadData_Version ("DasCLoadData", "2023/08/30", "004", "01", "RELS_DASCLOADDATA_004-01", "", "dxc");
//const Vi_Version DasCLoadData_Version ("DasCLoadData", "2023/08/30", "004", "02", "RELS_DASCLOADDATA_004-02", "", "dxc");
//const Vi_Version DasCLoadData_Version ("DasCLoadData", "2023/08/30", "004", "03", "RELS_DASCLOADDATA_004-03", "", "dxc");
//const Vi_Version DasCLoadData_Version ("DasCLoadData", "2023/08/30", "004", "04", "RELS_DASCLOADDATA_004-04", "", "dxc");
//const Vi_Version DasCLoadData_Version ("DasCLoadData", "2023/08/30", "004", "05", "RELS_DASCLOADDATA_004-05", "", "dxc");
//const Vi_Version DasCLoadData_Version ("DasCLoadData", "2023/08/30", "004", "06", "RELS_DASCLOADDATA_004-06", "", "dxc");
//const Vi_Version DasCLoadData_Version ("DasCLoadData", "2023/08/30", "004", "07", "RELS_DASCLOADDATA_004-07", "", "dxc");
//const Vi_Version DasCLoadData_Version ("DasCLoadData", "2023/08/30", "004", "08", "RELS_DASCLOADDATA_004-07", "", "dxc");
//const Vi_Version DasCLoadData_Version ("DasCLoadData", "2023/08/30", "004", "08", "RELS_DASCLOADDATA_004-09", "", "dxc");
// const Vi_Version DasCLoadData_Version_Prev ("DasCLoadData.Prev", "2023/08/30", "004", "09", "RELS_DASCLOADDATA_004-09", "", "dxc");
//const Vi_Version DasCLoadData_Version ("DasCLoadData", "2023/08/30", "005", "01", "RELS_DASCLOADDATA_005-001", "", "dxc");
// const Vi_Version DasCLoadData_Version_Prev ("DasCLoadData.Prev", "2023/08/30", "005", "02", "RELS_DASCLOADDATA_005-02", "", "dxc");
//const Vi_Version DasCLoadData_Version ("DasCLoadData", "2013/08/30", "006", "001", "RELS_DASCLOADDATA_006-01", "", "dxc");
//const Vi_Version DasCLoadData_Version ("DasCLoadData", "2023/08/30", "006", "02", "RELS_DASCLOADDATA_006-02", "", "dxc");
//const Vi_Version DasCLoadData_Version ("DasCLoadData", "2023/08/30", "006", "03", "RELS_DASCLOADDATA_006-03", "", "dxc");
//const Vi_Version DasCLoadData_Version ("DasCLoadData", "2023/08/30", "006", "04", "RELS_DASCLOADDATA_006-04", "", "dxc");
// const Vi_Version DasCLoadData_Version_Prev ("DasCLoadData.Prev", "2023/08/30", "006", "05", "RELS_DASCLOADDATA_006-05", "", "dxc");
// const Vi_Version DasCLoadData_Version_Prev ("DasCLoadData.Prev", "2023/08/30", "007", "01", "RELS_DASCLOADDATA_007-001", "", "dxc");
const Vi_Version DasCLoadData_Version_Prev ("DasCLoadData.Prev", "2023/08/30", "008", "01", "RELS_DASCLOADDATA_008-001", "", "dxc");
const Vi_Version DasCLoadData_Version ("DasCLoadData", "2023/08/30", "009", "01", "RELS_DASCLOADDATA_009-001", "", "dxc");

#endif
