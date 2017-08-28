#pragma execution_character_set("utf-8")
#include "ReceiverLocationForm.h"
#include "ui_ReceiverLocationForm.h"
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

ReceiverLocationForm::ReceiverLocationForm(QWidget *parent): 
	QWidget(parent),
	ui(new Ui::ReceiverLocationForm)
{
	ui->setupUi(this);
	WinIni();
}

ReceiverLocationForm::~ReceiverLocationForm()
{
	delete ui;
}

void ReceiverLocationForm::WinIni()
{
	m_ReceiverLocationPlot = new QwtPlot(this);
	m_ReceiverLocationPlot->setTitle("�켣ͼ");
	m_ReceiverLocationPlot->setCanvasBackground(Qt::white);
	m_ReceiverLocationPlot->insertLegend(new QwtLegend());
	m_ReceiverLocationPlot->plotLayout()->setAlignCanvasToScales(true);//���������໥��������

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

	m_ReceiverLocationPlot->setAxisScaleDraw(QwtPlot::xBottom, scaleDraw);
	m_ReceiverLocationPlot->setAxisScaleDraw(QwtPlot::yLeft, scaleDraw2);
	m_ReceiverLocationPlot->setAxisAutoScale(QwtPlot::xBottom, true);  //����X�ᣨ�ײ����Զ�����
	m_ReceiverLocationPlot->setAxisAutoScale(QwtPlot::yLeft, true);    //����y�ᣨ��ࣩ�Զ�����
	m_ReceiverLocationPlot->setAxisScale(QwtPlot::yLeft, 0.0, 1000.0, 200);   //����y������꣬��Χ��0-1000��������200
	m_ReceiverLocationPlot->setAxisScale(QwtPlot::xBottom, 0.0, 1000.0, 200); //����x������꣬��Χ��0-1000��������200
	m_ReceiverLocationPlot->setAxisTitle(QwtPlot::yLeft, "��ֵ");           //����x�����������
	m_ReceiverLocationPlot->setAxisTitle(QwtPlot::xBottom, tr("������"));   //����y�����������

	m_XCurve = new QwtPlotCurve();  //X������
	m_XCurve->setTitle("X��");
	m_XCurve->setStyle(QwtPlotCurve::Lines);
	m_XCurve->setPen(Qt::blue, 2);
	m_XCurve->attach(m_ReceiverLocationPlot);
	m_YCurve = new QwtPlotCurve();  //y������
	m_YCurve->setTitle("Y��");
	m_YCurve->setStyle(QwtPlotCurve::Lines);
	m_YCurve->setPen(Qt::green,2);
	m_YCurve->attach(m_ReceiverLocationPlot);
	m_ZCurve = new QwtPlotCurve();  //z������
	m_ZCurve->setTitle("Z��");
	m_ZCurve->setStyle(QwtPlotCurve::Lines);
	m_ZCurve->setPen(Qt::red,2);
	m_ZCurve->attach(m_ReceiverLocationPlot);

	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->attach(m_ReceiverLocationPlot);
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(m_ReceiverLocationPlot);
}