/*! @file DasMaskApplyVersionInfo.h

 @brief バージョン情報
 
 @author Haruka Shibasaki

 @mainpage

 @version 

	DT000_200.01  2009/11/30  芝崎陽香
		新規作成。

	DT001_200.01  2009/12/16  芝崎陽香
		・DasMaskApplyConf.xml内のタグを下記のように変更し、フルパスで定義するように変更
			<InputDir>→<BasePartsFolder>
			<ParametersFileName>→ <BaseParametersFileName>
			<EventsFileName>→<BaseEventsFileName>
			<ExceptionsFileName>→<BaseExceptionsFileName>
		・上記に伴うアプリの修正
		・上記に伴うシステム設計書の修正

	DT019_201.01  2010/01/05  伊東利晃
		Ver201作成に伴い、バージョンを合わせる。
	
	DT016_201.01  2010/01/05  芝崎陽香
		部品xmlファイルのMask処理で出力先フォルダにファイルが存在する場合、フォルダ内のファイルを削除する処理を追加

	DT045_201.01  2010/01/21  伊東利晃
		例外発生時のエラーコードを修正。

	DT048_210.01  2010/02/12  芝崎陽香
		バージョンの異なるモデルインスタンスをマスクするように修正

	DT052_210.01  2010/02/15  芝崎陽香
		Exception部品定義ファイルに対応するマスク処理の追加

	DT054_210.01  2010/02/15  芝崎陽香
		パーツファイル検索、正規表現ミス

	DT067_210.01  2010/03/29  伊東利晃
		Ver210作成。

	DT063_210.01  2010/03/29  伊東利晃
		eXDPフォルダ構成の変更に伴い、パス関連をCmnConfにまとめるため、読み込むConfigファイルタグを変更。

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

	DT189_214.01  2010/09/22  伊東利晃
		複数StateMachineInstance対応(LocationIdValueを指定可能に)。DasMaskをライブラリ化。

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


	DT433_556.01  2014/06/04  河淵剛士
		DT433 Share310B対応 のお願い

*/

#ifndef __DAS_MASKAPPLY_VERINFO_H__
#define __DAS_MASKAPPLY_VERINFO_H__
// バージョン情報の設定
#include <Utility/VersionInfo/Vi_Version.h>	// Share対応 #include <version_info/Vi_Version.h>

// バージョン情報
// const Vi_Version DasMaskApply_Version_Prev ("DasMaskApply.Prev", "2012/10/02", "525", "01", "RELS_DAS_525_01", "", "hp");
// const Vi_Version DasMaskApply_Version_Prev ("DasMaskApply.Prev", "2014/06/05", "556", "01", "RELS_DASMASKAPPLY_556-01", "", "hp");
//const Vi_Version DasMaskApply_Version ("DasMaskApply", "2023/08/30", "001", "01", "RELS_DASMASKAPPLY_001-01", "", "hp");
//const Vi_Version DasMaskApply_Version ("DasMaskApply", "2023/08/30", "001", "02", "RELS_DASMASKAPPLY_001-02", "", "hp");
//const Vi_Version DasMaskApply_Version ("DasMaskApply", "2023/08/30", "001", "03", "RELS_DASMASKAPPLY_001-03", "", "hp");
//const Vi_Version DasMaskApply_Version ("DasMaskApply", "2023/08/30", "001", "04", "RELS_DASMASKAPPLY_001-04", "", "hp");
//const Vi_Version DasMaskApply_Version ("DasMaskApply", "2023/08/30", "001", "05", "RELS_DASMASKAPPLY_001-05", "", "hp");
//const Vi_Version DasMaskApply_Version ("DasMaskApply", "2023/08/30", "001", "06", "RELS_DASMASKAPPLY_001-06", "", "hp");
const Vi_Version DasMaskApply_Version_Prev ("DasMaskApply.Prev", "2023/08/30", "001", "07", "RELS_DASMASKAPPLY_001-07", "", "hp");
//const Vi_Version DasMaskApply_Version ("DasMaskApply", "2023/08/30", "002", "01", "RELS_DASMASKAPPLY_002-001", "", "hp");
const Vi_Version DasMaskApply_Version ("DasMaskApply", "2023/08/30", "002", "02", "RELS_DASMASKAPPLY_002-02", "", "hp");

#endif
