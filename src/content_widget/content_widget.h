 #ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "datatype.h"
#include "qtpropertybrowser.h"
#include "qtpropertymanager.h"
#include "./DeviationInformation/DeviationInformation.h"
#include "./DOP/DopFrom.h"
#include "./sky/skyplot.h"
#include "./ReceiverLocationForm/ReceiverLocationForm.h"
#include "./FaultDetectionForm/FaultDetectionForm.h"
#include "./FaultDetectionResult/DetectionResultForm.h"
#include "./HPL/HPLForm.h"

class QLabel;
class QSplitter;
class QPushButton;
class QToolButton;
class QProgressBar;

struct TCMDParaHdrRec
{
	unsigned int CMDID;
	unsigned int MsgLEN;
	unsigned int MsgNo;
	unsigned int CMDPara;
};
//�û��켣����
struct TUserTrackRec
{
	long long iTrackBDT;//�켣ʱ�� ms

	unsigned int iTrackID;   //�켣�������
	float    fbeSimTime; //Ԥ��ʱ��ms

	double   dUserPosX; //�û�λ��X
	double   dUserPosY; //�û�λ��Y
	double   dUserPosZ; //�û�λ��Z

	double   dUserVelX; //�û��ٶ�X
	double   dUserVelY; //�û��ٶ�Y
	double   dUserVelZ; //�û��ٶ�Z

	double   dUserAccX; //�û����ٶ�X
	double   dUserAccY; //�û����ٶ�Y
	double   dUserAccZ; //�û����ٶ�Z

	double   dUserJekX; //�û��Ӽ��ٶ�X
	double   dUserJekY; //�û��Ӽ��ٶ�Y
	double   dUserJekZ; //�û��Ӽ��ٶ�Z
};
//�û��켣��������--����������0x0A5A5A05
struct TUserTrkTransRec
{
	struct TCMDParaHdrRec  sCmdHdr;
	struct TUserTrackRec   sUserTrk;
};
struct TUDPTrackTransRec
{
	double   dCMDID;
	double   dMsgLEN;
	double   dMsgNo;
	double   dCMDPara;

	double   dTrackBDT;//�켣ʱ�� ms

	double   dTrackID;   //�켣�������
	double   dbeSimTime; //Ԥ��ʱ��ms

	double   dUserPosX; //�û�λ��X
	double   dUserPosY; //�û�λ��Y
	double   dUserPosZ; //�û�λ��Z

	double   dUserVelX; //�û��ٶ�X
	double   dUserVelY; //�û��ٶ�Y
	double   dUserVelZ; //�û��ٶ�Z

	double   dUserAccX; //�û����ٶ�X
	double   dUserAccY; //�û����ٶ�Y
	double   dUserAccZ; //�û����ٶ�Z

	double   dUserJekX; //�û��Ӽ��ٶ�X
	double   dUserJekY; //�û��Ӽ��ٶ�Y
	double   dUserJekZ; //�û��Ӽ��ٶ�Z

};


class ContentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContentWidget(QWidget *parent = 0);
    void translateLanguage();
	ContentWidget(FaultParametervalue &Value, QWidget *parent = 0);

/**
*˽�к���
*/
private:
    void initLeft();
    void initRightTop();
    void initRightCenter();
    void initRightBottom();
    void initRight();
	void DrawSkyForm();   //�����ǿ�ͼ

/**
*˽�вۺ���
*/
private slots:
	void OkSlot();
	void CloseSlot();
	void startPause();  //��ʼ-��ͣ�ۺ���
	void stop();        //������ť
	void openFile();
	void constantFile();

private:
    QSplitter *main_splitter;

    QWidget *left_widget;
	DeviationInformation *m_deviation;
	DopFrom *m_dopfrom;
	Skyplot *m_skyplot;
	ReceiverLocationForm *m_receiverLocation;
	FaultDetectionForm *m_faultDetectionForm;
	DetectionResultForm *m_detetionResultForm;
	HPLForm *m_HPLForm;


    QSplitter *right_splitter;
    QWidget *right_widget;
    QWidget *right_top_widget;
    QLabel *name_label;
    QToolButton *menu_button;
    QProgressBar *progress_bar;
    QToolButton *grade_button;

    QPushButton *open_file; //��ȡ�����ļ�
	QPushButton *constant_file; //ʵʱ�ļ�

    QWidget *right_center_widget;

    QWidget *right_bottom_widget;
	QToolButton *start_pause_btn;  //����+��ͣ
	QToolButton *stop_btn;         //����

	QtProperty *StarTime;
	QtProperty *Length;
	QtProperty *FaultType;
	QtProperty *SatNo;
	QtProperty *m_Value;
	QtProperty *m_FalseAlarmRate;
	QtProperty *m_MissedRate;
	QtProperty *m_NoiseStandardDeviation;

	QtIntPropertyManager *StarTimeManager;
	QtIntPropertyManager *LengthManager;
	QtEnumPropertyManager *FaultTypeManager;
	QtIntPropertyManager *SatNoManager;
	QtDoublePropertyManager *ValueManager;
	QtDoublePropertyManager *FalseAlarmRateManager;
	QtDoublePropertyManager *MissedRateManager;
	QtDoublePropertyManager *NoiseStandardDeviationManager;
	QPushButton *pushbuttonClose;
	QPushButton *pushbuttonOk;
	FaultParametervalue *m_data;

	int glTrkDataID, glSndTimerLen, glOneTimeCnt, glDataIncCnt;
	struct TUDPTrackTransRec lTrkTransAry[5000];//100msһ����
	QDateTime  glCurrDTime;
	int glSimStepCnt;
	FILE  *fpTrkLog;
	char glTcpDatBuf[32768];
	QString glsLogDatPathDir;
	//TFileStream  *pFileTrjWrPtr[RNSSMDLCNT];
	int  fGnssNewLogSimData(char * pData); //����<0��ʾ�洢ʧ��,=0��ʾ����ת��,=1��ʾת��
	void fGnssNewLogDatOver();//�������ݴ洢
	bool glbIfRuning;
};


#endif // CONTENTWIDGET_H
