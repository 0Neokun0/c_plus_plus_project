/*! @file DasExportParametersVersionInfo.h

 @brief バージョン情報
 
 @author Shinsuke Nishiyama
 
 @date	2009/06/30 新規作成
 
 @version

	DT000_100.01  2009/06/30  西山慎亮
		新規作成。

	DT019_201.01  2010/01/05  伊東利晃
		Ver201作成に伴い、バージョンを合わせる。

	DT045_201.01  2010/01/21  伊東利晃
		例外発生時のエラーコードを修正。

	DT067_210.01  2010/03/29  伊東利晃
		Ver210作成。

	DT081_211.01  2010/05/13  伊東利晃
		Ver211作成。

	DT087_211.01  2010/05/18  伊東利晃
		フォルダ構成変更 for C++ 環境変数の変更に対応

	DT113_212.01  2010/05/31  伊東利晃
		Ver212作成。

	DT125_212.01  2010/06/09  伊東利晃
		フォーマット変更対応。

	DT152_213.01  2010/07/05  伊東利晃
		Ver213作成。

	DT150_213.01  2010/07/20  伊東利晃
		DFL_ParamType.xmlのXSDチェック処理追加。

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

	DT294_520.02  2011/11/14  河淵剛士
		CIMPortal 1.2.3 SCR検証 (CIMPortal1.2.3で修正されているか検証)

	DT302_520.03  2011/12/16  河淵剛士
		CIMPortal1.2.4対応

	DT360_525.01  2012/10/02  河淵剛士
		Share Ver309対応

	DT382_550.02  2012/11/30  河淵剛士
		DT382 Cimportal 1.2.9 対応のお願い

	DT431_555.01  2014/03/19  河淵剛士
		DT431 CIMPortal Ver1.2.15 バージョンアップ


	DT433_556.01  2014/06/04  河淵剛士
		DT433 Share310B対応 のお願い

	DT434_558.01  2016/08/17  河淵剛士
		DT431 CIMPortal Ver1.3.3 バージョンアップ
*/

#ifndef __DAS_EXPORTPARAMETER_VERINFO_H__
#define __DAS_EXPORTPARAMETER_VERINFO_H__
// バージョン情報の設定
#include <Utility/VersionInfo/Vi_Version.h>	// Share対応 #include <version_info/Vi_Version.h>

// バージョン情報
//const Vi_Version DasExportParameter_Version_Prev("DasExportParameters.Prev", "2012/11/30", "550", "01", "RELS_DAS_550_01", "", "hp");
//const Vi_Version DasExpParameters_Version_Prev ( "DasExpParameters.Prev",    "2014/03/19", "555", "02", "RELS_DAS_555_02", "", "hp");
// const Vi_Version DasExpParameters_Version_Prev (   "DasExpParameters.Prev",    "2014/06/05", "556", "01", "RELS_DASEXPPARAMETERS_556-01", "", "hp");
//const Vi_Version DasExpParameters_Version (      "DasExpParameters",         "2014/06/05", "556", "01", "RELS_DASEXPPARAMETERS_556-01", "", "hp");
const Vi_Version DasExpParameters_Version (        "DasExpParameters",         "2016/08/17", "558", "01", "RELS_DASEXPPARAMETERS_558-01", "", "hp");
const Vi_Version DasExpParameters_Version (        "DasExpParameters",         "2016/08/17", "888", "01", "RELS_DASEXPPARAMETERS_558-01", "", "hp");
const Vi_Version DasExpParameters_Version (        "DasExpParameters",         "2016/08/17", "558", "01", "RELS_DASEXPPARAMETERS_558-01", "", "hp");

#endif
