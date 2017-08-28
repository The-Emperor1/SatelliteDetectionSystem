#pragma execution_character_set("utf-8")
#include "DetectionResultForm.h"
#include "ui_DetectionResultForm.h"
#include <qlayout.h>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_canvas.h>
#include <qwt_scale_draw.h>
#include <qwt_legend.h>
#include <qwt_point_data.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_layout.h>
#include <qwt_text.h>
#include <qwt_symbol.h>
#include <qwt_math.h>
#include <math.h>

DetectionResultForm::DetectionResultForm(QWidget *parent): 
	QWidget(parent),
	ui(new Ui::DetectionResultForm)
{
	ui->setupUi(this);
	WinIni();
}

DetectionResultForm::~DetectionResultForm()
{
	delete ui;
}
void DetectionResultForm::WinIni()
{
	m_DetectionResult = new QwtPlot(this);
	m_DetectionResult->setCanvasBackground(Qt::white);
	m_DetectionResult->insertLegend(new QwtLegend());
	m_DetectionResult->plotLayout()->setAlignCanvasToScales(true);//���������໥��������

	QwtScaleDraw *scaleDraw = new QwtScaleDraw();//������Ļ滭
	scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, true);//�̶�����
	scaleDraw->setTickLength(QwtScaleDiv::MinorTick, 0);//�̶���
	scaleDraw->setTickLength(QwtScaleDiv::MediumTick, 0);
	scaleDraw->setTickLength(QwtScaleDiv::MajorTick, 0);
	scaleDraw->setPenWidth(1);
	QwtScaleDraw *scaleDraw2 = new QwtScaleDraw();
	scaleDraw2->enableComponent(QwtAbstractScaleDraw::Backbone, true);//�̶�����
	scaleDraw2->setTickLength(QwtScaleDiv::MinorTick, 0);//�̶���s
	scaleDraw2->setTickLength(QwtScaleDiv::MediumTick, 0);
	scaleDraw2->setTickLength(QwtScaleDiv::MajorTick, 0);
	scaleDraw2->setPenWidth(1);

	m_DetectionResult->setAxisScaleDraw(QwtPlot::xBottom, scaleDraw);
	m_DetectionResult->setAxisScaleDraw(QwtPlot::yLeft, scaleDraw2);
	m_DetectionResult->setAxisAutoScale(QwtPlot::xBottom, true);  //����X�ᣨ�ײ����Զ�����
	m_DetectionResult->setAxisAutoScale(QwtPlot::yLeft, true);    //����y�ᣨ��ࣩ�Զ�����
	m_DetectionResult->setAxisScale(QwtPlot::yLeft, 0.0, 1000.0, 200);   //����y������꣬��Χ��0-1000��������200
	m_DetectionResult->setAxisScale(QwtPlot::xBottom, 0.0, 1000.0, 200); //����x������꣬��Χ��0-1000��������200
	m_DetectionResult->setAxisTitle(QwtPlot::yLeft, "���Ǻ�");           //����x�����������
	m_DetectionResult->setAxisTitle(QwtPlot::xBottom, tr("������"));   //����y�����������

	detectionValue = new QwtPlotCurve();  //�������
	detectionValue->setTitle("������");
	detectionValue->setStyle(QwtPlotCurve::Lines);
	detectionValue->setPen(Qt::red, 2);
	detectionValue->attach(m_DetectionResult);
	faultSatellite = new QwtPlotCurve();  //ͳ�Ƽ����
	faultSatellite->setTitle("���ֵ");
	faultSatellite->setStyle(QwtPlotCurve::Lines);
	faultSatellite->setPen(Qt::blue, 2);
	faultSatellite->attach(m_DetectionResult);
	

	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->attach(m_DetectionResult);
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(m_DetectionResult);
}