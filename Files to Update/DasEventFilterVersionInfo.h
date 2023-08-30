/*! @file DasEventFilterVersionInfo.h

 @brief �o�[�W�������
 
 @author  Toshiaki Ito

 @mainpage

 @version 

	DT000_100.01  2009/11/30  �ɓ����W
		�V�K�쐬�B

	DT019_201.01  2010/01/05  �ɓ����W
		Ver201�쐬�ɔ����A�o�[�W���������킹��B
	
	DT024_201.01  2010/01/05  �ɓ����W
		Starter���b�Z�[�WID�̕ύX�B(RQ_MCSW_StandbyDasApp �� RQ_MCSW_StandbyDas)

	DT067_210.01  2010/03/29  �ɓ����W
		Ver210�쐬�B

	DT081_211.01  2010/05/13  �ɓ����W
		Ver211�쐬�B

	DT087_211.01  2010/05/18  �ɓ����W
		�t�H���_�\���ύX for C++ ���ϐ��̕ύX�ɑΉ�

	DT113_212.01  2010/05/31  �ɓ����W
		Ver212�쐬�B

	DT152_213.01  2010/07/05  �ɓ����W
		Ver213�쐬�B

	DT188_214.01  2010/09/02  �ɓ����W
		Ver214�쐬�B

	DT209_215.01  2010/11/11  �ɓ����W
		Ver215�쐬�B

	DT225_216.01  2011/01/21  �ɓ����W
		Ver216�쐬�B

	DT243_217.01  2011/03/01  �ɓ����W
		Ver217�쐬�B

	DT269_218.01  2011/05/09  �ɓ����W
		Ver218�쐬�B

	DT275_520.01  2011/07/04  �ɓ����W
		Ver520�쐬�B

	DT360_525.01  2012/10/02  �͕����m
		Share Ver309�Ή�

	DT405_552.02  2013/05/28  �͕����m
		DT405 [�m�F�˗�]SbMessage�T�C�Y���SK�𒴂���ƃ��b�Z�[�W���\�z�ł��Ȃ�����
		       ���b�Z�[�W�̃������[�m�ۃT�C�Y��S��MESSAGE_MAXSIZE�ɕύX


	DT433_556.01  2014/06/04  �͕����m
		DT433 Share310B�Ή� �̂��肢

*/

#ifndef __DAS_EVENTFILTER_VERSION_INFO_H__
#define __DAS_EVENTFILTER_VERSION_INFO_H__

#include "Common/LangInfra/Li_Exception.h"
#include "Common/MemoryMgr/Mm_STL.h"


// �o�[�W�������̐ݒ�
#include "Utility/VersionInfo/Vi_Version.h"

// ���C�u�����o�[�W�������
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
