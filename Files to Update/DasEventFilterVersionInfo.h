/*! @file DasEventFilterVersionInfo.h

 @brief バージョン情報
 
 @author  Toshiaki Ito

 @mainpage

 @version 

	DT000_100.01  2009/11/30  伊東利晃
		新規作成。

	DT019_201.01  2010/01/05  伊東利晃
		Ver201作成に伴い、バージョンを合わせる。
	
	DT024_201.01  2010/01/05  伊東利晃
		StarterメッセージIDの変更。(RQ_MCSW_StandbyDasApp ⇒ RQ_MCSW_StandbyDas)

	DT067_210.01  2010/03/29  伊東利晃
		Ver210作成。

	DT081_211.01  2010/05/13  伊東利晃
		Ver211作成。

	DT087_211.01  2010/05/18  伊東利晃
		フォルダ構成変更 for C++ 環境変数の変更に対応

	DT113_212.01  2010/05/31  伊東利晃
		Ver212作成。

	DT152_213.01  2010/07/05  伊東利晃
		Ver213作成。

	DT188_214.01  2010/09/02  伊東利晃
		Ver214作成。

	DT209_215.01  2010/11/11  伊東利晃
		Ver215作成。

	DT225_216.01  2011/01/21  伊東利晃
		Ver216作成。

	DT243_217.01  2011/03/01  伊東利晃
		Ver217作成。

	DT269_218.01  2011/05/09  伊東利晃
		Ver218作成。

	DT275_520.01  2011/07/04  伊東利晃
		Ver520作成。

	DT360_525.01  2012/10/02  河淵剛士
		Share Ver309対応

	DT405_552.02  2013/05/28  河淵剛士
		DT405 [確認依頼]SbMessageサイズが４Kを超えるとメッセージを構築できない現象
		       メッセージのメモリー確保サイズを全てMESSAGE_MAXSIZEに変更


	DT433_556.01  2014/06/04  河淵剛士
		DT433 Share310B対応 のお願い

*/

#ifndef __DAS_EVENTFILTER_VERSION_INFO_H__
#define __DAS_EVENTFILTER_VERSION_INFO_H__

#include "Common/LangInfra/Li_Exception.h"
#include "Common/MemoryMgr/Mm_STL.h"


// バージョン情報の設定
#include "Utility/VersionInfo/Vi_Version.h"

// ライブラリバージョン情報
// const Vi_Version DasEventFilter_Version_Prev ("DasEventFilter.Prev", "2013/05/28", "552", "02", "RELS_DAS_552_02", "", "hp");
// const Vi_Version DasEventFilter_Version_Prev ("DasEventFilter.Prev", "2014/06/05", "556", "01", "RELS_DASEVENTFILTER_556-01", "", "hp");
// const Vi_Version DasEventFilter_Version_Prev ("DasEventFilter.Prev", "2023/08/30", "001", "01", "RELS_DASEVENTFILTER_001-01", "", "hp");
// const Vi_Version DasEventFilter_Version_Prev ("DasEventFilter.Prev", "2023/08/30", "002", "01", "RELS_DASEVENTFILTER_002-01", "", "hp");
// const Vi_Version DasEventFilter_Version_Prev ("DasEventFilter.Prev", "2023/08/30", "003", "01", "RELS_DASEVENTFILTER_003-01", "", "hp");
// const Vi_Version DasEventFilter_Version_Prev ("DasEventFilter.Prev", "2023/08/30", "004", "01", "RELS_DASEVENTFILTER_004-01", "", "hp");
//const Vi_Version DasEventFilter_Version ("DasEventFilter", "2023/08/30", "005", "01", "RELS_DASEVENTFILTER_005-01", "", "hp");
//const Vi_Version DasEventFilter_Version ("DasEventFilter", "2023/08/30", "005", "02", "RELS_DASEVENTFILTER_005-02", "", "hp");
//const Vi_Version DasEventFilter_Version ("DasEventFilter", "2023/08/30", "005", "03", "RELS_DASEVENTFILTER_005-03", "", "hp");
//const Vi_Version DasEventFilter_Version ("DasEventFilter", "2023/08/30", "005", "04", "RELS_DASEVENTFILTER_005-04", "", "hp");
//const Vi_Version DasEventFilter_Version ("DasEventFilter", "2023/08/30", "005", "05", "RELS_DASEVENTFILTER_005-05", "", "hp");
//const Vi_Version DasEventFilter_Version ("DasEventFilter", "2023/08/30", "005", "06", "RELS_DASEVENTFILTER_005-06", "", "hp");
// const Vi_Version DasEventFilter_Version_Prev ("DasEventFilter.Prev", "2023/08/30", "005", "07", "RELS_DASEVENTFILTER_005-07", "", "hp");
//const Vi_Version DasEventFilter_Version ("DasEventFilter", "2023/08/30", "006", "01", "RELS_DASEVENTFILTER_006-001", "", "hp");
//const Vi_Version DasEventFilter_Version ("DasEventFilter", "2023/08/30", "006", "02", "RELS_DASEVENTFILTER_006-02", "", "hp");
// const Vi_Version DasEventFilter_Version_Prev ("DasEventFilter.Prev", "2023/08/30", "006", "03", "RELS_DASEVENTFILTER_006-03", "", "hp");
// const Vi_Version DasEventFilter_Version_Prev ("DasEventFilter.Prev", "2023/08/30", "007", "01", "RELS_DASEVENTFILTER_007-001", "", "hp");
//const Vi_Version DasEventFilter_Version ("DasEventFilter", "2023/08/30", "008", "01", "RELS_DASEVENTFILTER_008-001", "", "hp");
//const Vi_Version DasEventFilter_Version ("DasEventFilter", "2023/08/30", "008", "02", "RELS_DASEVENTFILTER_008-02", "", "hp");
//const Vi_Version DasEventFilter_Version_Prev ("DasEventFilter.Prev", "2023/08/30", "008", "03", "RELS_DASEVENTFILTER_008-03", "", "hp");
const Vi_Version DasEventFilter_Version_Prev ("DasEventFilter.Prev", "2023/08/30", "009", "01", "RELS_DASEVENTFILTER_009-001", "", "hp");
const Vi_Version DasEventFilter_Version ("DasEventFilter", "2023/08/30", "123", "01", "RELS_DASEVENTFILTER_123-001", "", "hp");
#endif
