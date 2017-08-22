#ifndef DATATYPE_H
#define DATATYPE_H

#include <QObject>


#define ROLE_CONTEXTMENU Qt::UserRole+1  //�Ҽ��˵�
#define ROLE_ICON  Qt::UserRole+2        //ͼ��
#define ROLE_ICONSTATE  Qt::UserRole+3    //״̬ͼ��
#define ROLE_ELEDATA  Qt::UserRole+4     //����
#define ROLE_NODENAME Qt::UserRole+5      //�ڵ�����
#define ROLE_DATFILENAME Qt::UserRole+6    //�����ļ���
#define ROLE_PARAID Qt::UserRole+7          //����ID
//#define ROLE_MotionType Qt::UserRole+8  //�����ɻ��ִ����˶����ͣ����ڵ���б���ʾ��Ӧ������

#include "ConstData.h"

enum CfgType
{
    HardwareCfg=0,
    SimCfg,
    SysCfg
};

//��������
enum VehicleType
{
    VehicleTypeUnknow = 0,
    Static = 1,//��ֹ
    Simple = 2,//���˶�
    Aircraft = 3,//�ɻ�
    Land = 4,//����
    Ship = 5,//�ִ�
    Spacecraft = 6,//̫��
    Remote = 7,//Զ��
    Special = 8,//����
    TrkFile=9, //�ⲿ�켣
	Circle=10
};
// enum SatSystemType
// {
//   BDS=0,
//   GPS=1,
//   GLONASS=2,
//   Galileo=3
// };

//�����˶�����
enum VehicleMotion
{
    VehicleMotionUnknow = 0,
    UserCircle = 1,//�û�Բ���˶�
    UserHelix = 2,//�û������˶�
    UserBigRound = 3,//�û���Բ�˶�
    UserVel = 4,//�û������˶�
    UserAcc = 5,//�û������˶�
    UserJek = 6,//�û��Ӽ����˶�
    SatPseudorangeFix = 11,//����α��̶�
    SatPseudorangeIncrease = 12,//����α�����
    SatVelFix = 13,//�����ٶȹ̶�
    SatAccFix = 14,//���Ǽ��ٶȹ̶�
    SatJekFix = 15,//���ǼӼ��ٶȹ̶�
    SatPseudorangeSin = 16//����α�����ұ仯
};

//�½������������
enum VehicleNewOperatorMotion
{
    Unknow = 0,
    Insert = 1,//����
    Replace = 2//�滻
};

/*
atmosphere_mode��16λΪ������ģ��ѡ�񣻸�16λΪ�����ģ��ѡ��

trop_mode	ģ��
0	Saastamoinen��˹��Ī��ģ��
1	�Ľ��Ļ��շƶ���ģ��
2	MOPS
3~14	Ԥ����ĿǰΪ�ر�
15	�ر�
ע��0,1��������RTK���ԣ�
td, Ps, humid�����Ϊ�¶ȣ����϶ȣ�������ѹ���������������ʪ�ȣ��ٷֱȣ�������ֵΪ20,1000,50

iono_mode	ģ��	                        ��ע
0	        ���ա�����ģ��	                ����ģ��
1	        ���ա�����ģ��	                ����ʽģ��
2	        ���ա�����ģ��	                �û��Զ���ģ��
3~7	        Ԥ����ĿǰΪ�ر�
8	        8����Klobucharģ��
9	        14����Klobucharģ��(������BD)
10			�����ģ�ͣ�GEOʹ��14����Klobucharģ��
MEOʹ��8����Klobuchar��(������BD)
9~14	        Ԥ����ĿǰΪ�ر�
15	        �ر�
ע�����ա�����ģ�͵�ʹ�òμ�iono_dll��
*/
//������ģ�ͣ�ö�٣�
enum TroposphereMode
{
	None = 15,           //�رգ���ʹ���κ�ģ��
	Saastamoinen = 0,       //��˹��Ī��
	ImproveHopfield = 1,        //�Ľ��Ļ��շƶ���
	MOPS = 2
};
//�����ģ��
enum IonosphereMode
{
	NoneMode = 15,      //�رգ���ʹ���κ�ģ��
	LandMode = 0,       //½�ص����ģ��
	SpaceMode = 1        //�ռ�����ģ��
};
//
enum SpaceIonoTECMode
{
	Constant = 0,     //����TEC����
	Multinomial = 1,     //����ʽTEC����
	UserDefined = 2     //�û��Զ������
};
enum LandIonosphereMode
{
	Para8 = 8,    //GPS,BDS
	Para14 = 9,       //BDS
	GalileoParam = 2  //Galileo
};

enum eSenceParaId
{
	SimTimePara = 1,//����ʱ��
	FileChoosePara = 2,//�ļ�ѡ��
	FileChooseEnablePara = 3,//�ļ�ѡ��ʹ��
	TrkStatic = 4,//��̬����
	TrkUserCircle = 5,//�û�Բ���˶�
	TrkUserHelix = 6,//�û������˶�
	TrkUserBigRound = 7,//�û���Բ�˶�
	TrkUserVel = 8,//�û������˶�
	TrkUserAcc = 9,//�û������˶�
	TrkUserJek = 10,//�û��Ӽ����˶�
	TrkSatPseudorangeFix = 11,//����α��̶�
	TrkSatPseudorangeIncrease = 12,//����α�����
	TrkSatVelFix = 13,//�����ٶȹ̶�
	TrkSatAccFix = 14,//���Ǽ��ٶȹ̶�
	TrkSatJekFix = 15,//���ǼӼ��ٶȹ̶�
	TrkSatPseudorangeSin = 16,//����α�����ұ仯
	TroposphereModel = 17,//���������
	BdSatHealthInfo = 18,//�������ǽ�����Ϣ
	GpsSatHealthInfo = 19,//gps���ǽ�����Ϣ
	GalSatHealthInfo = 20,//Gal���ǽ�����Ϣ
	GloSatHealthInfo=21,//glo���ǽ�����Ϣ
	BdIonoModel = 22,//bd��������
	GpsIonoModel = 23,//gps��������
	GalIonoModel = 24,//Gal��������
	GloIonoModel = 25,//GLO��������
	BdEphemeris = 26, //bd����������
	GpsEphemeris = 27,//Gps����������
	GalEphemeris = 28,//Gal����������
	GLOEphemeris = 29,//GLO����������
	Bdclockerr = 30,//bd�Ӳ�
	Gpsclockerr = 31,//gps�Ӳ�
	Galclockerr = 32,//gal�Ӳ�
	Gloclockerr = 33,//glo�Ӳ�
	BdTGD = 34,//�����豸ʱ��
	GpsTGD = 35,//Gps�豸ʱ��
	GalTGD = 36,//Gal�豸ʱ��
	Glotimesyn=37,//gloʱ��ͬ��
	Bdtimesyn = 38,//Bd�豸ʱ��ͬ��
	Gpstimesyn = 39,//Gps�豸ʱ��ͬ��
	Galtimesyn = 40,//gal�豸ʱ��ͬ��
	Interference = 41,//����
	CarOrAirDataType = 42,//�ɻ�������
	ShipDataType = 43,//�ִ�
	INSDataType = 44,//�ߵ�
	AntDataType = 45,//����
	PowSet = 46,//��������	
	EphFile=47,
	GLOAlmanac = 48//GLO�Ǽ�ʱ��Ϣ
};


class CarrierNewOperator
{
public:
    /// <summary>
    /// ��������
    /// </summary>
    VehicleType type;

    /// <summary>
    /// �����˶�����
    /// </summary>
    VehicleMotion motionType;

    /// <summary>
    /// �����������
    /// </summary>
    VehicleNewOperatorMotion operatorType;

    /// <summary>
    /// �Ƿ���������Ϣ
    /// </summary>
    bool IsKeepAntenna;
};

enum InterfereType
{
	MultiPath = 0,//��·������
	Transmit = 1,//ת��ʽ����
	UserDefine = 2 //��������

};
typedef struct MFaultParametervalue
{
  int  startime;//��ʼʱ��
  int type;//1��Ծ 2б��
  int lenth;//ʱ��
  int SatNO;//���Ǻ�
  double value;//�仯ֵ
}FaultParametervalue;

#endif // DATATYPE_H
