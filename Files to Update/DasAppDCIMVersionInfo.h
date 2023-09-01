/*! @file DasAppDCIMVersionInfo.h

 @brief �o�[�W�������
 
 @author  Toshiaki Ito

 @mainpage

 @version 

	DT000_100.01  2009/09/30  �ɓ����W
		�V�K�쐬�B

	DT019_201.01  2010/01/05  �ɓ����W
		Ver201�쐬�ɔ����A�o�[�W���������킹��B
	
	DT024_201.01  2010/01/05  �ɓ����W
		Starter���b�Z�[�WID�̕ύX�B(RQ_MCSW_StandbyeXDPApp �� RQ_MCSW_StandbyeXDP)

	DT039_201.01  2010/01/14  �ɓ����W
		�I�����O�֘A�G���[�R�[�h�C���B

	DT053_210.01  2010/02/15  �ɓ����W
		OsLogger�Ŗ������[�v���Ȃ��悤�ɃJ�����g�f�B���N�g����ύX�B

	DT055_210.01  2010/02/16  �ɓ����W
		�p�����[�^�l�⍇�����`�t�@�C����OSS�I�u�W�F�N�g�̃��r�W�����Ή��B

	DT049_210.01  2010/02/19  �ɓ����W
		�p�����[�^�A�N�Z�X��`�t�@�C���ɒ�`���Ȃ��ASEMI�I�u�W�F�N�g�����l�̎擾���s���̃G���[�R�[�h���C���B

	DT067_210.01  2010/03/29  �ɓ����W
		Ver210�쐬�B

	DT063_210.01  2010/03/29  �ɓ����W
		eXDP�t�H���_�\���̕ύX�ɔ����A�p�X�֘A��CmnConf�ɂ܂Ƃ߂邽�߁A�ǂݍ���Config�t�@�C���^�O��ύX�B

	DT066_210.01  2010/03/29  �ɓ����W
		ParameterTypeFileName�^�O��CimPortal�^�O����Conf�^�O�ɕύX�B

	DT081_211.01  2010/05/13  �ɓ����W
		Ver211�쐬�B

	DT087_211.01  2010/05/18  �ɓ����W
		�t�H���_�\���ύX for C++ ���ϐ��̕ύX�ɑΉ�

	DT113_212.01  2010/05/31  �ɓ����W
		Ver212�쐬�B

	DT125_212.01  2010/06/09  �ɓ����W
		DFL_ParamType.xml�t�H�[�}�b�g�ύX�Ή��B

	DT126_212.01  2010/06/09  �ɓ����W
		DFL_SEMIType.xml�̃t�H�[�}�b�g�ύX�Ή�(EventData�폜)�B

	DT119_212.01  2010/06/14  �ɓ����W
		OSS�A�N�Z�X��`�t�@�C���O�����Ή��B

	DT095_212.01  2010/06/23  �ɓ����W
		�p�����[�^�l�⍇�����`�t�@�C���̃t�H�[�}�b�g�`�F�b�N������ǉ��B

	DT097_212.01  2010/06/23  �ɓ����W
		�I�����O�A�N�Z�X��`�t�@�C���̃t�H�[�}�b�g�`�F�b�N������ǉ��B

	DT141_212.01  2010/06/24  �ɓ����W
		DasAppShutdown�̏I���҂������Ȃ��悤�ɏC���B

	DT142_212.01  2010/06/24  �ɓ����W
		DFL_EventTrigger�t�@�C���ǂݍ��ݎ��s���Ƀ��������J������悤�ɏC���B

	DT152_213.01  2010/07/05  �ɓ����W
		Ver213�쐬�B

	DT151_213.01  2010/07/14  �ɓ����W
		STA��MTA�ɕύX�B����ɔ���GlobalInterfaceTable��p�~�B

	DT140_213.01  2010/07/20  �ɓ����W
		XML�t�@�C����Validate��MSXML�ɕύX�B

	DT144_213.01  2010/07/20  �ɓ����W
		DFL_SEMIObjectAccess.xml��XSD�`�F�b�N�����ǉ��B

	DT150_213.01  2010/07/20  �ɓ����W
		DFL_ParamType.xml�ADFL_SEMIType.xml��XSD�`�F�b�N�����ǉ��B

	DT088_213.01  2010/07/26  �ɓ����W
		EqClientError�̎���(UpdateData�^�Ⴂ��Client����̒l�v����Callback)�B

	DT188_214.01  2010/09/02  �ɓ����W
		Ver214�쐬�B

	DT189_214.01  2010/09/22  �ɓ����W
		DasMask�����C�u�������B

	DT190_214.01  2010/10/18  �͕����m
		����StateMachineInstance�Ή�  DasAppDCIM

	DT204_214.01  2010/11/05  �͕����m
		 Gem_Clock -> Gem_Clock_SV�ɕύX

	DT209_215.01  2010/11/11  �ɓ����W
		Ver215�쐬�B

	DT209_215.01  2010/11/26  �͕����m
		�t�Z���֘ASV�������̑Ή�

	DT209_215.02  2010/12/07  �͕����m
		�t�Z���֘ASV�������̑Ή�

	DT209_215.02  2010/12/09  �͕����m
		Cms_CarrierContentMap�̃p�����[�^�̃Z�b�g�̃R�����g�A�E�g������

	DT055_215.03  2011/01/17  �ɓ����W
		mod_�p�����[�^�l�⍇�����`�t�@�C����OSS�I�u�W�F�N�g�̃��r�W�����Ή��B
		DFL������SEMI�I�u�W�F�N�g���}�X�N�`�F�b�N�Ń��r�W���������Ă��Ȃ������̂��C���B

	DT225_216.01  2011/01/21  �ɓ����W
		Ver216�쐬�B

	DT228_216.01  2011/02/15  �ɓ����W
		CIMPortal1.2.0Update�ɔ����\�[�X�C���BCreateValueObject���I�[�o�[���C�h�B

	DT229_216.01  2011/02/15  �ɓ����W
		�N������DFL��CLEAR���߂�InstanceParameter�̏����l�ݒ菈����ǉ��B
		CIMPortal�C���܂ł̎b��Ή��B

	DT230_216.01  2011/02/15  �ɓ����W
		SEMIObject��������InstanceParameter�̒l���X�V���Ă��Ȃ������̂��C���B

	DT231_216.01  2011/02/14  �͕����m
		�I�����O��occurs�̔���s��C���B

	DT232_216.01  2011/02/15  �ɓ����W
		ObjID_Gem_Alarm�͎g�p���Ȃ��Ȃ����̂Ŋ֘A�����̃R�����g�A�E�g�B

	DT243_217.01  2011/03/01  �ɓ����W
		Ver217�쐬�B

	DT239_217.01  2011/03/01  �ɓ����W
		�I�����O�A�N�Z�X��`�t�@�C����reqVparent�������������ꍇ�́A
		���e���쐬����悤�ɏC���B

	DT241_217.01  2011/03/01  �ɓ����W
		CarrierContentMap���ʏ����Ń^�O�擾�Ɏ��s�����ۂ�UpdateData�ŃG���[���������Ă����s����C���B

	DT240_217.01  2011/03/03  �ɓ����W
		GetE39Data��MDB�擾��ɃG���[�łȂ����UpdateData����悤�ɏC���B

	DT239_217.02  2011/03/09  �ɓ����W
		DT239mod�B
		reqVparent�w�肪���������X�g��0�łŕ񍐂��ꂽ�ꍇ�ɂ��A���e���쐬������ȍ\���ł͂Ȃ��Ȃ��Ă��������C���B

	DT251_217.04  2011/03/25  �ɓ����W
		Gem_TIMESTAMP�ɃZ�b�g���鎞�Ԃ𑗐M��������쐬�����ɕύX�B

	DT260_217.05  2011/04/13  �ɓ����W
		OBJDEL���̑����l�X�V���ANoValue����NULL�ɏC���B

	DT269_218.01  2011/05/09  �ɓ����W
		Ver218�쐬�B

	DT266_218.01  2011/05/17  �͕����m
		InstanceParameter�������Ή��ɂ����_

	DT275_520.01  2011/07/04  �ɓ����W
		Ver520�쐬�B

	DT280_520.01  2011/07/25  �ɓ����W
		�G���[����DasAppDCIM�p�G���[�C�x���g�𑗐M����悤�ɏC���B

	DT290_520.02  2011/10/28  �͕����m
		�I�����O�̉�͉��P

	DT290_520.03  2011/11/08  �͕����m
		�I�����O�̉�͉��P

	DT294_520.04  2011/11/14  �͕����m
		CIMPortal 1.2.3 SCR���� (CIMPortal1.2.3�ŏC������Ă��邩����)
		�I�����O�̉�͉��P

	DT302_520.05  2011/12/16  �ɓ����W
		CIMPortal1.2.4�Ή�

	DT320_520.06  2012/03/13  �͕����m
		�N���A�I������Sbroker�C���X�^���X�̕ی�

	DT319_520.07  2012/03/27  �͕����m
		DasAppDCIM�̃f�b�h���b�N�C��

	DT340_521.01  2012/06/06  �ɓ����W
		NSRErrorCode�������܂܂�Ă���ꍇ�̃G���[����B

	DT352_525.01  2012/09/25  �ɓ����W
		���݂��Ȃ����b�Z�[�WID�������Ă��ADAS���N���ł���悤�ɏC���B

	DT353_525.02  2012/09/25  �ɓ����W
		�I�u�W�F�N�g�폜(OBJDEL)�G���[���̃��O���x����ύX�B

	DT360_525.03  2012/10/02  �͕����m
		Share Ver309�Ή�

	DT375_531.01  2012/11/09  �ɓ����W
		GetE39DataCB�����MDB�A�N�Z�X�𐧌�ł���悤�ɏC��

	DT375_550.01  2012/11/19  �ɓ����W
		ver550�ɕύX

	DT382_550.02  2012/11/30  �͕����m
		DT382 Cimportal 1.2.9 �Ή��̂��肢

	DT382_550.03  2012/12/07  �͕����m
		DT383 DFL_EventTriggr.def-OBJDEL�ŃI�u�W�F�N�g�����݂��Ȃ��ꍇ�̏����ύX

	DT382_550.03  2012/12/07  �͕����m
		DT384 Reticle Pod�̑����l[ReticlePodLocationID]��Carrier�̑����l[LocationID]�̒l����

	DT382_550.03  2012/12/07  �͕����m
		DT385 MsgServer�ւ̖₢���킹�G���[���̃��O���x���ύX

	DT382_550.04  2012/12/26  �͕����m
		DT372 SessionFrozen����̕��A��̒ʐM���O�o��

	DT382_550.05  2012/12/26  �͕����m
		DT372-1 SessionFrozen����̕��A��̒ʐM���O�o�͕s��C��

	DT402_550.06  2013/03/06  �͕����m
		DT402 [DAS] Session���t�@�C���̃t�H���_���݃`�F�b�N�G���[

	DT405_550.07  2013/05/20  �͕����m
		DT405 [�m�F�˗�]SbMessage�T�C�Y���SK�𒴂���ƃ��b�Z�[�W���\�z�ł��Ȃ�����

	DT405_552.02  2013/05/28  �͕����m
		DT405 [�m�F�˗�]SbMessage�T�C�Y���SK�𒴂���ƃ��b�Z�[�W���\�z�ł��Ȃ�����
		       ���b�Z�[�W�̃������[�m�ۃT�C�Y��S��MESSAGE_MAXSIZE�ɕύX

	DT406_552.02  2013/05/30  �͕����m
		DT405 [�m�F�˗�]SbMessage�T�C�Y���SK�𒴂���ƃ��b�Z�[�W���\�z�ł��Ȃ�����
		MDB�̃��X�|���X���t�@�C���œn����鏈��������̂ł����A
		���̃t�@�C�����������[�ɓǂݍ��ގ��̃������[�T�C�Y���P�Q�WK�ɂ��Ă��܂���
		�ׂɃG���[���������Ă��܂����B

	DT409_553.01  2013/07/16  �͕����m
		DT409 [DAS] GetData�R�[���o�b�N��������MDB�ւ�OSS�₢�����p�~

	DT410_553.01  2013/07/16  �͕����m
		DT410 [DAS] Cimportal 1.2.12�Ή��̂��肢

	DT411_553.02  2013/07/30  �͕����m
		DT411 [DAS][Das553] �uSession���R�[���o�b�N�Ή��v�d�l�m�F�̂��肢

	DT411_553.03  2013/08/07  �͕����m
		DT420 GetData�R�[���o�b�N��������MDB�ւ�OSS�₢�����ŁAMDB�ȊO�̃p�����[�^���₢���킹���ł��Ȃ��Ȃ��Ă��܂����B

	DT426_553.04  2013/08/23  �͕����m
		DasSbMessageTagData::getDoubles�ł̃G���[�ɂ���


	DT411_554.01  2013/10/07  �͕����m
		DT411 [DAS][Das554] �uSession���R�[���o�b�N�Ή��v�d�l�m�F�̂��肢

	DT431_553.01  2014/03/19  �͕����m
		DT431 CIMPortal Ver1.2.15 �o�[�W�����A�b�v


	DT433_556.01  2014/06/04  �͕����m
		DT433 Share310B�Ή� �̂��肢

	DT434_558.01  2016/08/17  �͕����m
		DT431 CIMPortal Ver1.3.3 �o�[�W�����A�b�v

	DT434_558-P02.02  2016/09/29  �͕����m
		DT434 ver558-P02   ShutdownDCIM�R�[���o�b�N���Q�񑱂��Ĕ������錻��


	DT436_559.01 2017/01/12  �͕����m
		DT436 ver559   LotLabel�ʒm�Ή�
*/

#ifndef __DAS_APPDCIM_VERSION_INFO_H__
#define __DAS_APPDCIM_VERSION_INFO_H__

// Share�Ή�
//#include "utility/Ut_Exception.h"
//#include "memory_mgr/Mm_STL.h"
#include "Common/LangInfra/Li_Exception.h"
#include "Common/MemoryMgr/Mm_STL.h"

// �o�[�W�������̐ݒ�
#include "Utility/VersionInfo/Vi_Version.h"	// Share�Ή� #include "version_info/Vi_Version.h"

// ���C�u�����o�[�W�������
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
