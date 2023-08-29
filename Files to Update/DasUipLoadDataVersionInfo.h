/*! @file DasUipLoadDataVersionInfo.h

 @brief �o�[�W�������
 
 @author Tsuyoshi Kawabuchi

 @mainpage

 @version 

	DT000_100.01  2021/12/05  �͕����m
		�V�K�쐬�B
*/

#ifndef __LIB_DAS_UIPLOADDATA_VERSION_INFO_H__
#define __LIB_DAS_UIPLOADDATA_VERSION_INFO_H__

// Share�Ή�
//#include "utility/Ut_Exception.h"
//#include "memory_mgr/Mm_STL.h"
#include "Common/LangInfra/Li_Exception.h"
#include "Common/MemoryMgr/Mm_STL.h"

// �o�[�W�������̐ݒ�
#include "Utility/VersionInfo/Vi_Version.h"	// Share�Ή� #include "version_info/Vi_Version.h"

// ���C�u�����o�[�W�������
// DasMLoadData�ւ̕ύX�Ή�
const Vi_Version DasUipLoadData_Version_Prev ("DasUipLoadData", "2014/06/05", "556", "01", "RELS_DASUIPLOADDATA_556-01", "", "hp");
const Vi_Version DasMLoadData_Version        ("DasMLoadData",   "2021/12/05", "000", "01", "RELS_DASMLOADDATA_000-01", "", "hp");

#endif
