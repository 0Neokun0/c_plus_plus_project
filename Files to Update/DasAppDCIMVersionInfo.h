/*! @file DasAppDCIMVersionInfo.h

 @brief バージョン情報
 
 @author  Toshiaki Ito

 @mainpage

 @version 

	DT000_100.01  2009/09/30  伊東利晃
		新規作成。

	DT019_201.01  2010/01/05  伊東利晃
		Ver201作成に伴い、バージョンを合わせる。
	
	DT024_201.01  2010/01/05  伊東利晃
		StarterメッセージIDの変更。(RQ_MCSW_StandbyeXDPApp ⇒ RQ_MCSW_StandbyeXDP)

	DT039_201.01  2010/01/14  伊東利晃
		露光ログ関連エラーコード修正。

	DT053_210.01  2010/02/15  伊東利晃
		OsLoggerで無限ループしないようにカレントディレクトリを変更。

	DT055_210.01  2010/02/16  伊東利晃
		パラメータ値問合せ先定義ファイル内OSSオブジェクトのリビジョン対応。

	DT049_210.01  2010/02/19  伊東利晃
		パラメータアクセス定義ファイルに定義がない、SEMIオブジェクト属性値の取得失敗時のエラーコードを修正。

	DT067_210.01  2010/03/29  伊東利晃
		Ver210作成。

	DT063_210.01  2010/03/29  伊東利晃
		eXDPフォルダ構成の変更に伴い、パス関連をCmnConfにまとめるため、読み込むConfigファイルタグを変更。

	DT066_210.01  2010/03/29  伊東利晃
		ParameterTypeFileNameタグをCimPortalタグからConfタグに変更。

	DT081_211.01  2010/05/13  伊東利晃
		Ver211作成。

	DT087_211.01  2010/05/18  伊東利晃
		フォルダ構成変更 for C++ 環境変数の変更に対応

	DT113_212.01  2010/05/31  伊東利晃
		Ver212作成。

	DT125_212.01  2010/06/09  伊東利晃
		DFL_ParamType.xmlフォーマット変更対応。

	DT126_212.01  2010/06/09  伊東利晃
		DFL_SEMIType.xmlのフォーマット変更対応(EventData削除)。

	DT119_212.01  2010/06/14  伊東利晃
		OSSアクセス定義ファイル外だし対応。

	DT095_212.01  2010/06/23  伊東利晃
		パラメータ値問合せ先定義ファイルのフォーマットチェック処理を追加。

	DT097_212.01  2010/06/23  伊東利晃
		露光ログアクセス定義ファイルのフォーマットチェック処理を追加。

	DT141_212.01  2010/06/24  伊東利晃
		DasAppShutdownの終了待ちをしないように修正。

	DT142_212.01  2010/06/24  伊東利晃
		DFL_EventTriggerファイル読み込み失敗時にメモリを開放するように修正。

	DT152_213.01  2010/07/05  伊東利晃
		Ver213作成。

	DT151_213.01  2010/07/14  伊東利晃
		STA⇒MTAに変更。それに伴いGlobalInterfaceTableを廃止。

	DT140_213.01  2010/07/20  伊東利晃
		XMLファイルのValidateをMSXMLに変更。

	DT144_213.01  2010/07/20  伊東利晃
		DFL_SEMIObjectAccess.xmlのXSDチェック処理追加。

	DT150_213.01  2010/07/20  伊東利晃
		DFL_ParamType.xml、DFL_SEMIType.xmlのXSDチェック処理追加。

	DT088_213.01  2010/07/26  伊東利晃
		EqClientErrorの実装(UpdateData型違いでClientからの値要求時Callback)。

	DT188_214.01  2010/09/02  伊東利晃
		Ver214作成。

	DT189_214.01  2010/09/22  伊東利晃
		DasMaskをライブラリ化。

	DT190_214.01  2010/10/18  河淵剛士
		複数StateMachineInstance対応  DasAppDCIM

	DT204_214.01  2010/11/05  河淵剛士
		 Gem_Clock -> Gem_Clock_SVに変更

	DT209_215.01  2010/11/11  伊東利晃
		Ver215作成。

	DT209_215.01  2010/11/26  河淵剛士
		液浸水関連SV初期化の対応

	DT209_215.02  2010/12/07  河淵剛士
		液浸水関連SV初期化の対応

	DT209_215.02  2010/12/09  河淵剛士
		Cms_CarrierContentMapのパラメータのセットのコメントアウトを解除

	DT055_215.03  2011/01/17  伊東利晃
		mod_パラメータ値問合せ先定義ファイル内OSSオブジェクトのリビジョン対応。
		DFL処理のSEMIオブジェクト名マスクチェックでリビジョンを見ていなかったのを修正。

	DT225_216.01  2011/01/21  伊東利晃
		Ver216作成。

	DT228_216.01  2011/02/15  伊東利晃
		CIMPortal1.2.0Updateに伴うソース修正。CreateValueObjectをオーバーライド。

	DT229_216.01  2011/02/15  伊東利晃
		起動時とDFLのCLEAR命令にInstanceParameterの初期値設定処理を追加。
		CIMPortal修正までの暫定対応。

	DT230_216.01  2011/02/15  伊東利晃
		SEMIObject初期化でInstanceParameterの値を更新していなかったのを修正。

	DT231_216.01  2011/02/14  河淵剛士
		露光ログのoccursの判定不具合修正。

	DT232_216.01  2011/02/15  伊東利晃
		ObjID_Gem_Alarmは使用しなくなったので関連部分のコメントアウト。

	DT243_217.01  2011/03/01  伊東利晃
		Ver217作成。

	DT239_217.01  2011/03/01  伊東利晃
		露光ログアクセス定義ファイルにreqVparent属性があった場合は、
		仮親を作成するように修正。

	DT241_217.01  2011/03/01  伊東利晃
		CarrierContentMap特別処理でタグ取得に失敗した際にUpdateDataでエラーが発生していた不具合を修正。

	DT240_217.01  2011/03/03  伊東利晃
		GetE39DataのMDB取得後にエラーでなければUpdateDataするように修正。

	DT239_217.02  2011/03/09  伊東利晃
		DT239mod。
		reqVparent指定があったリストが0個でで報告された場合にも、仮親を作成し正常な構造ではなくなっていた問題を修正。

	DT251_217.04  2011/03/25  伊東利晃
		Gem_TIMESTAMPにセットする時間を送信時刻から作成時刻に変更。

	DT260_217.05  2011/04/13  伊東利晃
		OBJDEL時の属性値更新を、NoValueからNULLに修正。

	DT269_218.01  2011/05/09  伊東利晃
		Ver218作成。

	DT266_218.01  2011/05/17  河淵剛士
		InstanceParameter初期化対応による問題点

	DT275_520.01  2011/07/04  伊東利晃
		Ver520作成。

	DT280_520.01  2011/07/25  伊東利晃
		エラー時にDasAppDCIM用エラーイベントを送信するように修正。

	DT290_520.02  2011/10/28  河淵剛士
		露光ログの解析改善

	DT290_520.03  2011/11/08  河淵剛士
		露光ログの解析改善

	DT294_520.04  2011/11/14  河淵剛士
		CIMPortal 1.2.3 SCR検証 (CIMPortal1.2.3で修正されているか検証)
		露光ログの解析改善

	DT302_520.05  2011/12/16  伊東利晃
		CIMPortal1.2.4対応

	DT320_520.06  2012/03/13  河淵剛士
		起動、終了時のSbrokerインスタンスの保護

	DT319_520.07  2012/03/27  河淵剛士
		DasAppDCIMのデッドロック修正

	DT340_521.01  2012/06/06  伊東利晃
		NSRErrorCodeが多く含まれている場合のエラー回避。

	DT352_525.01  2012/09/25  伊東利晃
		存在しないメッセージIDがあっても、DASが起動できるように修正。

	DT353_525.02  2012/09/25  伊東利晃
		オブジェクト削除(OBJDEL)エラー時のログレベルを変更。

	DT360_525.03  2012/10/02  河淵剛士
		Share Ver309対応

	DT375_531.01  2012/11/09  伊東利晃
		GetE39DataCBからのMDBアクセスを制御できるように修正

	DT375_550.01  2012/11/19  伊東利晃
		ver550に変更

	DT382_550.02  2012/11/30  河淵剛士
		DT382 Cimportal 1.2.9 対応のお願い

	DT382_550.03  2012/12/07  河淵剛士
		DT383 DFL_EventTriggr.def-OBJDELでオブジェクトが存在しない場合の処理変更

	DT382_550.03  2012/12/07  河淵剛士
		DT384 Reticle Podの属性値[ReticlePodLocationID]とCarrierの属性値[LocationID]の値生成

	DT382_550.03  2012/12/07  河淵剛士
		DT385 MsgServerへの問い合わせエラー時のログレベル変更

	DT382_550.04  2012/12/26  河淵剛士
		DT372 SessionFrozenからの復帰後の通信ログ出力

	DT382_550.05  2012/12/26  河淵剛士
		DT372-1 SessionFrozenからの復帰後の通信ログ出力不具合修正

	DT402_550.06  2013/03/06  河淵剛士
		DT402 [DAS] Session情報ファイルのフォルダ存在チェックエラー

	DT405_550.07  2013/05/20  河淵剛士
		DT405 [確認依頼]SbMessageサイズが４Kを超えるとメッセージを構築できない現象

	DT405_552.02  2013/05/28  河淵剛士
		DT405 [確認依頼]SbMessageサイズが４Kを超えるとメッセージを構築できない現象
		       メッセージのメモリー確保サイズを全てMESSAGE_MAXSIZEに変更

	DT406_552.02  2013/05/30  河淵剛士
		DT405 [確認依頼]SbMessageサイズが４Kを超えるとメッセージを構築できない現象
		MDBのレスポンスがファイルで渡される処理があるのですが、
		このファイルをメモリーに読み込む時のメモリーサイズを１２８Kにしてしまった
		為にエラーが発生していました。

	DT409_553.01  2013/07/16  河淵剛士
		DT409 [DAS] GetDataコールバック発生時のMDBへのOSS問い合せ廃止

	DT410_553.01  2013/07/16  河淵剛士
		DT410 [DAS] Cimportal 1.2.12対応のお願い

	DT411_553.02  2013/07/30  河淵剛士
		DT411 [DAS][Das553] 「Session情報コールバック対応」仕様確認のお願い

	DT411_553.03  2013/08/07  河淵剛士
		DT420 GetDataコールバック発生時のMDBへのOSS問い合せで、MDB以外のパラメータも問い合わせができなくなってしまった。

	DT426_553.04  2013/08/23  河淵剛士
		DasSbMessageTagData::getDoublesでのエラーについて


	DT411_554.01  2013/10/07  河淵剛士
		DT411 [DAS][Das554] 「Session情報コールバック対応」仕様確認のお願い

	DT431_553.01  2014/03/19  河淵剛士
		DT431 CIMPortal Ver1.2.15 バージョンアップ


	DT433_556.01  2014/06/04  河淵剛士
		DT433 Share310B対応 のお願い

	DT434_558.01  2016/08/17  河淵剛士
		DT431 CIMPortal Ver1.3.3 バージョンアップ

	DT434_558-P02.02  2016/09/29  河淵剛士
		DT434 ver558-P02   ShutdownDCIMコールバックが２回続けて発生する現象


	DT436_559.01 2017/01/12  河淵剛士
		DT436 ver559   LotLabel通知対応
*/

#ifndef __DAS_APPDCIM_VERSION_INFO_H__
#define __DAS_APPDCIM_VERSION_INFO_H__

// Share対応
//#include "utility/Ut_Exception.h"
//#include "memory_mgr/Mm_STL.h"
#include "Common/LangInfra/Li_Exception.h"
#include "Common/MemoryMgr/Mm_STL.h"

// バージョン情報の設定
#include "Utility/VersionInfo/Vi_Version.h"	// Share対応 #include "version_info/Vi_Version.h"

// ライブラリバージョン情報
//const Vi_Version DasAppDCIM_Version_Prev("DasAppDCIM.Prev", "2013/08/23", "553", "04", "RELS_DAS_553_04", "", "hp");
//const Vi_Version DasAppDCIM_Version_Prev("DasAppDCIM.Prev", "2013/10/07", "554", "01", "RELS_DAS_554_01", "", "hp");
//const Vi_Version DasAppDCIM_Version_Prev("DasAppDCIM.Prev         ", "2014/03/19", "555", "02", "RELS_DAS_555_02", "", "hp");
//const Vi_Version DasAppDCIM_Version (    "DasAppDCIM              ", "2014/06/05", "556", "01", "RELS_DASAPPDCIM_556-01", "", "hp");
//const Vi_Version DasAppDCIM_Version_Prev("DasAppDCIM.Prev         ", "2014/06/05", "556", "01", "RELS_DASAPPDCIM_556-01", "", "hp");
//const Vi_Version DasAppDCIM_Version (    "DasAppDCIM              ", "2016/08/17", "558", "01", "RELS_DASAPPDCIM_558-01", "", "hp");
//const Vi_Version DasAppDCIM_Version_Prev (DasAppDCIM.Prev         ", "2016/09/29", "558", "02", "RELS_DASAPPDCIM_558-02", "P02", "hp");
//const Vi_Version DasAppDCIM_Version (    "DasAppDCIM              ", "2016/09/29", "558", "02", "RELS_DASAPPDCIM_558-02", "P02", "hp");
//const Vi_Version DasAppDCIM_Version (    "DasAppDCIM              ", "2017/01/23", "559", "01", "RELS_DASAPPDCIM_559-01", "", "hp");
//const Vi_Version DasAppDCIM_Version (    "DasAppDCIM              ", "2019/08/05", "559", "02", "RELS_DASAPPDCIM_559-02", "", "dxc");
//const Vi_Version DasAppDCIM_Version (    "DasAppDCIM              ", "2019/08/21", "559", "03", "RELS_DASAPPDCIM_559-03", "", "dxc");
//const Vi_Version DasAppDCIM_Version_Prev ( "DasAppDCIM.Prev         ", "2020/12/09", "559", "04", "RELS_DASAPPDCIM_559-04", "", "dxc");
//const Vi_Version DasAppDCIM_Version_Prev ( "DasAppDCIM.Prev", "2023/03/28", "000", "01", "RELS_DASAPPDCIM_000-01", "", "dxc");
//const Vi_Version DasAppDCIM_Version( "DasAppDCIM", "2023/03/28", "111", "01", "RELS_DASAPPDCIM_111-01", "", "dxc");
const Vi_Version DasAppDCIM_Version_Prev( "DasAppDCIM.Prev", "2023/09/01", "111", "02", "RELS_DASAPPDCIM_111-02", "", "dxc");
const Vi_Version DasAppDCIM_Version( "DasAppDCIM", "2023/09/01", "789", "02", "RELS_DASAPPDCIM_789-02", "", "dxc");

#endif
