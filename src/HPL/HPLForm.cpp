#pragma execution_character_set("utf-8")
#include "HPLForm.h"
#include "ui_HPLForm.h"
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


HPLForm::HPLForm(QWidget *parent): 
	QWidget(parent),
	ui(new Ui::HPLForm)
{
	ui->setupUi(this);
	WinIni();
}

HPLForm::~HPLForm()
{
	delete ui;
}

void HPLForm::WinIni()
{
	m_HPL = new QwtPlot(this);
	m_HPL->setCanvasBackground(Qt::white);
	m_HPL->insertLegend(new QwtLegend());
	m_HPL->plotLayout()->setAlignCanvasToScales(true);//���������໥��������

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

	m_HPL->setAxisScaleDraw(QwtPlot::xBottom, scaleDraw);
	m_HPL->setAxisScaleDraw(QwtPlot::yLeft, scaleDraw2);
	m_HPL->setAxisAutoScale(QwtPlot::xBottom, true);  //����X�ᣨ�ײ����Զ�����
	m_HPL->setAxisAutoScale(QwtPlot::yLeft, true);    //����y�ᣨ��ࣩ�Զ�����
	m_HPL->setAxisScale(QwtPlot::yLeft, 0.0, 1000.0, 200);   //����y������꣬��Χ��0-1000��������200
	m_HPL->setAxisScale(QwtPlot::xBottom, 0.0, 1000.0, 200); //����x������꣬��Χ��0-1000��������200
	m_HPL->setAxisTitle(QwtPlot::yLeft, "HPLֵ");           //����x�����������
	m_HPL->setAxisTitle(QwtPlot::xBottom, tr("������"));   //����y�����������

	HPL = new QwtPlotCurve();  //�������
	HPL->setTitle("HPL");
	HPL->setStyle(QwtPlotCurve::Lines);
	HPL->setPen(Qt::red, 2);
	HPL->attach(m_HPL);


	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->attach(m_HPL);
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(m_HPL);
}