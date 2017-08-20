#ifndef SIMDATATYPE_H
#define SIMDATATYPE_H

#include "ConstData.h"
#include <QVariant>

/*******************************************************************\
���Ʒ�ʽ
\*******************************************************************/
enum  ModulateMode
{
    M_Close = 0,
    M_BPSKQ = 1,
    M_BPSKI = 2,
    M_QPSK = 3,
    M_SingleCarrier = 15
};

/*******************************************************************\
�û�λ�����ݽṹ��
\*******************************************************************/
struct UserTrkData
{
	UINT64 UserID;
    UINT64 TrackBDT;//�켣ʱ�� ms
	DWORD wn;
	DWORD sow;
    double  Pos[3]; //�û�λ��
    double  Vel[3]; //�û��ٶ�
    double  Acc[3]; //�û����ٶ�
    double  Jek[3]; //�û��Ӽ��ٶ�

    double Attitude[3];	//��̬ rad
    double AngleRate[3];	//���ٶ� rad/s
};
/*******************************************************************\
����ʱ����Ϣ�ṹ��
\*******************************************************************/
typedef struct _SimTimeInfo
{
    WORD Year;
    BYTE Month;
    BYTE Day;

    BYTE Hour;
    BYTE Minute;
    BYTE Second;
    WORD Millisecond;

    DWORD BDWn;	//���ܼ���
    DWORD Sow;	//������
    DWORD BDLeapSecond;	//����

    DWORD GPSWn;	//���ܼ���
    DWORD GPSLeapSecond;	//����

    //DWORD GALWn;	//���ܼ���
    //DWORD GALLeapSecond;	//����

    DWORD GLOWn;	//���ܼ���
    DWORD GLOLeapSecond;	//����

}SimTimeInfo, *PSimTimeInfo;


/*******************************************************************\
�����ǹ۲����ݽṹ��
\*******************************************************************/
struct SatObsData
{
    BYTE Modulate;			//���Ʒ�ʽ
	int SatID;				//���Ǻ�
    double Pseudorange[4];		//α��0��1��2��3���� ��λ��s��m/s��m/s^2��m/s^3
    double Carrier;			//�ز�
    double Power;				//����dBm
    double Elevation;			//���Ǹ�����
    double Azimuth;				//���Ƿ�λ��
    double SatPos[3];
    double SatVel[3];
};
/*******************************************************************\
�۲����ݽṹ��
\*******************************************************************/
struct ObsData
{
	BYTE AntId;				//����ID 1-8
	BYTE SatCnt;			//��������
	WORD FreqID;			//Ƶ��ID
	DWORD Wn;
    DWORD Sow;				//������,ms
    SatObsData SatObs[MAX_BDS_OBS_SAT_NUM];
};

/*******************************************************************\
����ϵͳ���
\*******************************************************************/
enum eSatSystemType
{
    BD2 = 1,
    GPS = 2,
    GLO = 3,
    GAL = 4
};

/*******************************************************************\
Ӳ��Ƶ����
\*******************************************************************/
enum eFreqType
{
    BD2_B1 = 1,
    BD2_B2 = 2,
    BD2_B3 = 3,
    GPS_L1 = 4,
    GPS_L2 = 5,
    GPS_L5 = 6,
    GLO_L1 = 7,
    GLO_L2 = 8,
    BD2_B1C = 9,  //BOC(6,1)
    BD2_B1A = 10, //BOC(14,2)
    BD2_B2A = 11, //BPSK(10) - TDDM - BOC(15, 10)
    BD2_B2B = 12, //BPSK(10)-TDDM-BOC(15,10)
    BD2_B3A = 13, //QPSK(10)
    BD2_B3C = 14, //QPSK(5)
    GPS_L1C = 15,
    BD2_B3AE = 16, //B3��ǿ�ź�  QPSK(10)
    GPS_L1M = 17,

    GAL_E1BC = 20,
    GAL_E6C = 22,
    GAL_E5A = 24,
    GAL_E5B = 25,

    GLO_L3 = 26,

    BD2_B1A2 = 27, //TDDM + BOC(14,2)
    BD2_B2A2 = 28, //BPSK(10)-AltBOC(15,10)
    BD2_B2B2 = 29, //BPSK(10)-AltBOC(15,10)
    BD2_B3C2 = 30, //BOC(15,2.5)
    BD2_BS = 31,   //QPSK(8)

    BD2_B2A3 = 18,//BD2_B2A_ACE ACE-BOC(15,10)
    BD2_B2B3 = 19,//BD2_B2A_ACE ACE-BOC(15,10)
    BD2_B1C2 = 21,//BD2_B1C_QM  QMBOC
    BD2_B1A3 = 23,//BD2_B1A     BOC(14,2)

    Trans_C1 = 32, //ת��ʽC1
    Trans_C2 = 33, //ת��ʽC2
    Trans_C3 = 34, //ת��ʽC3

    GPS_SBAS = 35,  //SBAS

    BD_S = 100,

    Plans_T1S1 = 201,
    Plans_T1S2 = 202,
    Plans_T2S1 = 203,
    Plans_T2S2 = 204
};

typedef struct _InterfacePara
{
    eFreqType FreqId;
    char RemoteIP[256];
    WORD RemotePort;
    WORD LocalPort;
}InterfacePara, *PInterfacePara;

/*******************************************************************\
DDS���ݽṹ��
\*******************************************************************/
typedef struct _sDDSData
{
    DWORD	CodePhase; /*��Ƭ����:  ���8λL220ms������/��λ��
                       �θ�8λΪQ����I���ڵļ���
                       ��16λΪ��Ƭ��
                       */

    /*20120520��Ը�����ģ�����޸�*/
    DWORD	ComIG1Para;/*��16λ����λ�ü���(sec_code_addr)+��16λ��������Ƭ��(sec_code_cnt) (Ŀǰ=��������Ƭ��) */
    DWORD	ComIG2Para;/*no use*/

    UINT64	CodeK0_NCO;
    UINT64	CodeK1_NCO;
    INT64   CodeK2_NCO;
    INT64   CodeK3_NCO;

    UINT64	CarrK0_NCO;
    INT64   CarrK1_NCO;
    INT64   CarrK2_NCO;
    INT64	CarrK3_NCO;
}sDDSData;

/*******************************************************************\
RNSSƵ������DDS���ݰ��ṹ��
\*******************************************************************/
typedef struct _RNSSSatDataPakect      /*----100bytes----*/
{
    DWORD CompData1;/*  ͨ����Ч��־�����λ�����������ر�־���θ�λ�������Ǻţ��м�8λ������������(��16bits)*/
    /*
    ��������	                ��������
    0			I-Q����0:0
    1			I-Q����0:1
    2			I-Q����1:0
    3			I-Q����1:1
    15			���ز�
    */
    DWORD CompData2;/*  IQ��IPower(��16bits)��QPower(��16bits) */

    DWORD ComIG1Para;/*no use I֧·G1����ʽ(��16bits)�� I֧·G1����ʽ����(��16bits)*/
    DWORD ComIG2Para;/*no use I֧·G2����ʽ(��16bits)�� I֧·G2����ʽ����(��16bits)*/

    DWORD ChipAgPara;

    DWORD PaK0DDSLo;
    DWORD PaK0DDSHi;
    DWORD PaK1DDSLo;
    DWORD PaK1DDSHi;
    DWORD PaK2DDSLo;
    DWORD PaK2DDSHi;
    DWORD PaK3DDSLo;
    DWORD PaK3DDSHi;

    DWORD PbK0DDSLo;
    DWORD PbK0DDSHi;
    DWORD PbK1DDSLo;
    DWORD PbK1DDSHi;
    DWORD PbK2DDSLo;
    DWORD PbK2DDSHi;
    DWORD PbK3DDSLo;
    DWORD PbK3DDSHi;

    DWORD IGNPBits;
    DWORD QGNPBits;


}RNSSSatDataPakect, *PRNSSSatDataPakect;

/*******************************************************************\
���������ֽṹ��
\*******************************************************************/
typedef struct _NetCmdWord
{
    DWORD CMD;
    DWORD Length;
    DWORD TimeFlag;
    DWORD Check;
}NetCmdWord, *PNetCmdWord;


/*******************************************************************\
*BD�ⲿ�����������ݽṹ��
\*******************************************************************/
typedef struct _BDEphemerisSetPara
{
    int				toe;		//�����ο�ʱ��
    int				toc;		//�Ӳ�ο�ʱ��
    int             WN;			//���ܼ���
    double			M0;			//ƽ���ǵ�
    double			e; 			//ƫ����
    double			sqrtA;		//�����᷽��
    double			OMEGA0;		//������ྭ
    double			i0;			//������
    double			omega;		//���ص����
    double			IDOT;		//�����Ǳ仯��
    double			Crs; 		//����뾶�����ҵ��͸���������
    double			deltan;		//����ƽ���˶����������ֵ֮��
    double			OMEGADOT;	//������ྭ�仯��
    double			Crc;		//����뾶�����ҵ��͸���������
    double			Cuc;		//γ�ȷ��ǵ����ҵ��͸���������
    double			Cus;		//γ�ȷ��ǵ����ҵ��͸���������
    double			Cic;		//�����ǵ����ҵ��͸���������
    double			Cis;		//�����ǵ����ҵ��͸���������
    double         a0;			//�Ӳ� s
    double         a1;			//���� s/s
    double         a2;         //���� s/s^2
    double			TGD1;		//�����豸ʱ�Ӳ�1
    double         TGD2;		//�����豸ʱ�Ӳ�2
    double         a[4];		//��������Alpha
    double         b[4];		//��������Beta
}BDEphemerisSetPara, *PBDEphemerisSetPara;	////BD�ⲿ�����������ݽṹ��

/**************************************************************\
* BD�������ǲ���
\**************************************************************/
typedef struct NavSVPara16
{
    INT			toe;			//(��λ��Ҫת��) *2^-3
    INT			toc;			//(��λ��Ҫת��) *2^-3
    int                     weeknum;                // ��������
    double			M0;			//(��λ��Ҫת��) *2^31/3.1415926	��д������Ϣʱ��λת��Ϊ *2^23/3.1415926
    double			e; 			//��λ��Ҫת��) *2^33				��д������Ϣʱ��λת��Ϊ *2^21
    double			sqrtA;			//(��λ��Ҫת��) *2^19				��д������Ϣʱ��λת��Ϊ *2^11
    double			OMEGA0;			//(��λ��Ҫת��) *2^31/3.1415926	��д������Ϣʱ��λת��Ϊ *2^23/3.1415926
    double			i0;			//(��λ��Ҫת��) *2^31/3.1415926
    double			omega;			//(��λ��Ҫת��) *2^31/3.1415926	��д������Ϣʱ��λת��Ϊ *2^23/3.1415926
    double			IDOT;			//(��λ��Ҫת��) *2^43/3.1415926
    double			Crs; 			//(��λ��Ҫת��) *2^6
    double			deltan;			//(��λ��Ҫת��) *2^43/3.1415926
    double			OMEGADOT;		//(��λ��Ҫת��) *2^43/3.1415926	��д������Ϣʱ��λת��Ϊ *2^38/3.1415926
    double			Crc;			//(��λ��Ҫת��) *2^6
    double			Cuc;			//(��λ��Ҫת��) *2^31
    double			Cus;			//(��λ��Ҫת��) *2^31
    double			Cic;			//(��λ��Ҫת��) *2^31
    double			Cis;			//(��λ��Ҫת��) *2^31
    double                  af0;
    double                  af1;
    double                  af2;
    double			TGD1;
    double                  TGD2;
    // meo/igso ionosphere
    double                  a_g[4];
    double                  b_g[4];
    // geo ionosphere
    double			A1; 			//��������      (��λ��Ҫת��)*2^-1
    double			B; 			//��������      (��λ��Ҫת��) /7
    double			a_b[4]; 		//��������      (��λ��Ҫת��)*2^30��*2^27 ��*2^24�� *2^24
    double			b_b[4]; 		//��������      (��λ��Ҫת��)*2^-11�� *2^-14 ��*2^-16�� *2^-17
    double			c_b[4]; 		//��������      (��λ��Ҫת��)*2^-6�� *2^-11 ��*2^-14�� *2^-15
}NavSVPara16;

/**************************************************************\
* GPS�������ǲ���
\**************************************************************/
typedef struct NavSVPara  //�ⲿ�������ýṹ��
{
    BYTE			Alert;			//�̶�0
    BYTE			Anti;			//�̶�0
    unsigned short	WeekNo;
    BYTE			CodeOnL2;     	//01
    BYTE			SVAccuracy;   	//0000
    BYTE			SvHealth;		//Ĭ��ֵ000000
    unsigned short	IODC;
    BYTE			L2PDataFlag;  	//00
    double			TGD;			//
    INT				toc;			//
    double			af2;			//
    double			af1;			//
    double			af0;			//
    INT				IODE;			//
    double			Crs; 			//
    double			deltan;			//
    double			M0;				//
    double			Cuc;			//
    double			e; 				//
    double			Cus;			//
    double			sqrtA;			//
    INT				toe;			//
    BYTE			FitIntervalFlag;//0
    INT				AODO; 			//
    double			Cic;			//
    double			OMEGA0;			//
    double			Cis;			//
    double			i0;				//
    double			Crc;			//
    double			omega;			//
    double			OMEGADOT;		//
    double			IDOT;			//
    INT				toa;			//
    double			ai_alm;			//
    double			e_alm;
    double			OMEGADOT_alm;
    double			sqrtA_alm;
    double			OMEGA0_alm;
    double			omega_alm;
    double			M0_alm;
    int             health_alm;
    double			af1_alm;
    double			af0_alm;
    BYTE			WNa;
    double			a[4];
    double			b[4];
    double			A1;
    double			A0;
    INT				tot;
    BYTE			WNt;
    BYTE			deltaTLS;
    BYTE			WNLSF;
    BYTE			DN;
    BYTE			deltaTLSF;
    BYTE			SVCONFIG;
    BYTE			AvailabilityIndicator;
    BYTE			ERD; 			//100000
}NavSVPara;

typedef struct GLO_NavSVPara  //�ⲿ�������ýṹ��
{
    unsigned short	WeekNo;
    double			TGD;
	int				toc;
	double			af2;
	double			af1;
	double			af0;
    double			Crs;
    double			deltan;
    double			M0;
    double			Cuc;
    double			e;
    double			Cus;
    double			sqrtA;
    int				toe;
    double			Cic;
    double			OMEGA0;
    double			Cis;
    double			i0;
    double			Crc;
    double			omega;
    double			OMEGADOT;
    double			IDOT;
    double			a[4];
    double			b[4];
}GLO_NavSVPara;

typedef struct extGLONASS_Almanac
{
    unsigned char M;   //MnA`�����ͺ�
    unsigned char n;   //nA�����Ǻ�
    unsigned char H;   //HnA��Ƶ����
    unsigned char l;   //
    unsigned char Cn;  //������ʶ
    double tau;        //����ֵ
    double lambda;     //��nA��
    double delta_i;    //��inA��
    double epsilon;    //��nA��
    double omega;      //��nA��
    double t;          //ke����t��nA��
    double delta_T;    //��TnA
    double delta_T_dot;//��TnA��
//	char dump[3];
}extGLONASS_Almanac;

typedef struct extGLONASS_Data
{
	//========== ������ز��� =============
	int tk;           // ��0���ⲿʹ���������ʾ
	int tb;           // �����Ĳο�ʱ�䣬��һ���ڵķ��ӱ�ʾ

	double x;         // ���������ļ���д
	double x_dot;     // ���������ļ���д
	double x_dot_dot; // ���������ļ���д	
	double y;         // ���������ļ���д
	double y_dot;     // ���������ļ���д
	double y_dot_dot; // ���������ļ���д
	double z;         // ���������ļ���д
	double z_dot;     // ���������ļ���д
	double z_dot_dot; // ���������ļ���д	
	double tau;       // ��0��glonassʱ��������ʱ��֮��Ĳ�ֵ
	double gamma;     // ��0����n(tb)��
	double delta_tau; // ��0������n��

	unsigned char B;  // ��0�����ǽ���״̬��0��ʾ������4��ʾ����Bn��
	unsigned char P;  // ��0��P��
	unsigned char l;  // ��0�����Ǽ��״̬��0������1����In��
	unsigned char E;  // ��1En��
	unsigned char P1; // ��0
	unsigned char P2; // ��0
	unsigned char P3; // ��0
	unsigned char P4; // ��0��
	unsigned char FT; // ��0���û����뾫������
	unsigned char n;  // ���Ǳ��
	unsigned char M;  // ��1
	unsigned short NT;// ��0��ͨ������ʱ�����ú�������
	// ����һ�������1��1���������������󲻳�������

	//========== ������ز��� ===============
	unsigned short NA; // ��0��ͨ������ʱ�����ú�������
	// ���꿪ʼ�����ڼ���
	double tauc;       // ��0�������NAʱ�̣�GLONASSʱ��߶����UTC(SU)��ʱ�����
	double tauGPS;     // ��0��GPSʱ�����GLONASSʱ��ĸ���
	unsigned char N4;  // ��0��ͨ������ʱ�����ú�������,
	// �����1996�꿪ʼ��4��ļ��������
	extGLONASS_Almanac almanac[24];
	double B1;	   // ��0����SΪ��λ�Ĵ� �տ�ʼ��UTC��UT1֮���ƫ�����������ͨ���ⲿ�޸ģ�
	double B2;	   // ��0����SΪ��λ�Ĵ� �տ�ʼ��UTC��UT1֮���ƫ���һ�������ͨ���ⲿ�޸ģ�
	unsigned char KP;  // ��0�������ʶ��00�����룬01��һ�룬11��һ��
}extGLONASS_Data;



typedef struct _BDEphemeris
{
	double toe;			//(��λ��Ҫת��) *2^-3
	double toc;			//(��λ��Ҫת��) *2^-3
	double weeknum;                // ��������
	double M0;			//(��λ��Ҫת��) *2^31/3.1415926	��д������Ϣʱ��λת��Ϊ *2^23/3.1415926
	double e; 			//��λ��Ҫת��) *2^33				��д������Ϣʱ��λת��Ϊ *2^21
	double sqrtA;			//(��λ��Ҫת��) *2^19				��д������Ϣʱ��λת��Ϊ *2^11 
	double OMEGA0;			//(��λ��Ҫת��) *2^31/3.1415926	��д������Ϣʱ��λת��Ϊ *2^23/3.1415926
	double i0;			//(��λ��Ҫת��) *2^31/3.1415926	
	double omega;			//(��λ��Ҫת��) *2^31/3.1415926	��д������Ϣʱ��λת��Ϊ *2^23/3.1415926
	double IDOT;			//(��λ��Ҫת��) *2^43/3.1415926
	double Crs; 			//(��λ��Ҫת��) *2^6
	double deltan;			//(��λ��Ҫת��) *2^43/3.1415926
	double OMEGADOT;		//(��λ��Ҫת��) *2^43/3.1415926	��д������Ϣʱ��λת��Ϊ *2^38/3.1415926
	double Crc;			//(��λ��Ҫת��) *2^6
	double Cuc;			//(��λ��Ҫת��) *2^31
	double Cus;			//(��λ��Ҫת��) *2^31
	double Cic;			//(��λ��Ҫת��) *2^31
	double Cis;			//(��λ��Ҫת��) *2^31
	double af0;
	double af1;
	double af2;
	// meo/igso ionosphere   8 paras
	double a_g[4];
	double b_g[4];
	// geo ionosphere       14 paras
	double A1; 			//��������      (��λ��Ҫת��)*2^-1
	double B; 			//��������      (��λ��Ҫת��) /7
	double a_b[4];
	double b_b[4];
	double c_b[4];
	// =====  almanace =====================
	double sqrtA_alm;	//���ļ���ȡ
	double a0_alm;		//���ļ���ȡ
	double a1_alm;		//���ļ���ȡ
	double OMEGA0_alm;	//���ļ���ȡ
	double e_alm; 		//���ļ���ȡ
	double ceilta;		//���ļ���ȡ
	double OMEGADOT_alm;	//���ļ���ȡ
	double omega_alm;	//���ļ���ȡ
	double M0_alm;		//���ļ���ȡ  
	double Hea;		//���ļ���ȡ  
	double toa;		//���ļ���ȡ        
}BDEphemeris;

typedef struct BD_GMI_PARA  //BDϵͳGEO/MEO/IGSO����D1��Ϣ�ṹ��
{
	unsigned short  	WN;		// ͨ��BD2_SetTime�����趨
	unsigned int		SOW;		// �������
	char			URAI;		// 0
	char			SatH1;		// 0
	double			TGD1;		// 0
	double			TGD2;		// 0
	char			IODC;           // 1
	int			toc;		// ����toe
	double			a0;		// �û����и�ֵ��������ǰ�����еĲο�ֵ
	double			a1;		// �û����и�ֵ���ڸ��������������½����ֵ�� 0
	double			a2;		// �û����и�ֵ���ڸ��������������½����ֵ�� 0
	char			IODE;		// 1
	int			toe;		//���ļ���ȡ
	double			M0;		//���ļ���ȡ
	double			e; 		//���ļ���ȡ
	double			sqrtA;		//���ļ���ȡ
	double			OMEGA0;		//���ļ���ȡ
	double			i0;		//���ļ���ȡ
	double			omega;		//���ļ���ȡ
	double			IDOT;		//���ļ���ȡ
	double			Crs; 		//���ļ���ȡ
	double			deltan;		//���ļ���ȡ
	double			OMEGADOT;	//���ļ���ȡ
	double			Crc;		//���ļ���ȡ
	double			Cuc;		//���ļ���ȡ
	double			Cus;		//���ļ���ȡ
	double			Cic;		//���ļ���ȡ
	double			Cis;		//���ļ���ȡ
}BD_GMI_PARA;

typedef struct BDGEOID2Frm2_3_4  //BDϵͳGEO����D2 I֧· ��֡2 ��֡3 ��֡4 ��Ϣ�ṹ��
{
	unsigned int		SOW;
	char			EncF2;		// 1
	char			EncF3;		// 1
	char			EncF4;		// 1
	char			SatH2;		// 0
	char			BD2ID[30];	// ȫ0
	char			GPSID[30];	// ȫ0
	char			GALID[30];	// ȫ0
	char			UDREI[3][18];	// ȫ0
	char			RURAI[3][18];	// ȫ0
	unsigned short		deltat[3][18];	// ȫ0
}BDGEOID2Frm2_3_4;

typedef struct BDGEOID2Frm5  //BDϵͳGEO����D2 I֧· ��֡5 ��Ϣ�ṹ��
{

	unsigned int		SOW;			//������
	char			EncF5;			//��ʾ��֡�Ƿ����
	double			Ion[160];		// 0
	double			Iona[160];		// 0
	double			T1;                     // 0
	double			deltaX1;		// 0
	double			deltaY1;		// 0
	double			deltaZ1;		// 0
	double			A0l;			// 0
	double			A1l;			// 0
	double			deltaXDOTl;		// 0
	double			deltaYDOTl;		// 0
	double			deltaZDOTl;		// 0
	double			T2;			// 0
	double			deltaX2;		// 0
	double			deltaY2;		// 0
	double			deltaZ2;		// 0
	double			A02;			// 0
	double			A12;			// 0
	double			deltaXDOT2;		// 0
	double			deltaYDOT2;		// 0
	double			deltaZDOT2;		// 0
	double			EPIO[14];		// 3840
	// ===== iono  8 paras==================
	double			a8[4]; 			//�������� 6.519300000000e-009,1.490200000000e-008,-5.960500000000e-008,-1.192100000000e-007;
	double			b8[4]; 			//�������� 7.782400000000e+004,3.277000000000e+004,-6.554000000000e+004,-1.966100000000e+005;

	// ===== iono 14 paras==================
	double			A1; 			//�������� 0.000000000000e+000;
	double			B; 			//�������� 0.000000000000e+000;
	double			a[4]; 			//�������� 6.519300000000e-009,1.490200000000e-008,-5.960500000000e-008,-1.192100000000e-007;
	double			b[4]; 			//�������� 7.782400000000e+004,3.277000000000e+004,-6.554000000000e+004,-1.966100000000e+005;
	double			c[4]; 			//�������� 1.000000000000e-001,0.000000000000e+000,0.000000000000e+000,0.000000000000e+000
	// =====  almanace =====================  �����������̶�30,����һ�ڽ���������30�����ǵ�����  ==================
	double			sqrtA_alm[30];	        //���ļ���ȡ  //30
	double			a0_alm[30];		//���ļ���ȡ
	double			a1_alm[30];		//���ļ���ȡ
	double			OMEGA0_alm[30];	        //���ļ���ȡ
	double			e_alm[30]; 		//���ļ���ȡ
	double			ceilta[30];		//���ļ���ȡ
	double			OMEGADOT_alm[30];	//���ļ���ȡ
	double			omega_alm[30];		//���ļ���ȡ
	double			M0_alm[30];		//���ļ���ȡ
	double			Hea[30];		//���ļ���ȡ
	int			toa;			//���ļ���ȡ
	double			WNa;                    //ͨ��BD2_SetTime�����趨
	// ===== time transfer =================
	double			A0MAT;			// 0
	double			A1MAT;			// 0
	double			A0GPS;			// 0
	double			A1GPS;			// 0
	double			A0Galileo;		// 0
	double			A1Galileo;		// 0
	double			A0Glo;			// 0
	double			A1Glo;			// 0
	short			deltaTLS;		// 0
	short			deltaTLSF;		// 0
	char			WNLSF;			// 0
	double			A0UTC;			// 0
	double			A1UTC;			// 0
	char			DN;			// 0
}BDGEOID2Frm5;



Q_DECLARE_METATYPE(ObsData)
Q_DECLARE_METATYPE(UserTrkData)
Q_DECLARE_METATYPE(SatObsData)

typedef struct _NavigationBaseinformation
{
	BYTE Message[40];//������Ϣ
	WORD FreqID;//Ƶ���
	int SatID;//���Ǻ�
	DWORD Sow;//������
	DWORD Wekcount;//�ܼ���

}NavigationBaseinformation, *pNavigationBaseinformation;
typedef struct _InertialNavigation
{
	UINT64 SNOW;
	double Gyro[3];//����x y z
	double ACC[3];//���ٶȼ� x,y,z

}InertialNavigation, *PInertialNavigation;


#endif
