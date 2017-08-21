#include <QLabel>
#include <QEvent>
#include <QPainter>
#include <QSplitter>
#include <QHBoxLayout>
#include <QPushButton>
#include <QToolButton>

#include "content_widget.h"
#include "qteditorfactory.h"
#include "qttreepropertybrowser.h"
#include "qtbuttonpropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"
#pragma execution_character_set("utf-8")

ContentWidget::ContentWidget(QWidget *parent)
    : QWidget(parent)
{
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);

    main_splitter = new QSplitter();
    main_splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_splitter->setOrientation(Qt::Horizontal);
    main_splitter->setHandleWidth(1);
    main_splitter->setStyleSheet("QSplitter::handle{background:lightgray;}");

    this->initLeft();
    this->initRight();
    this->initRightTop();
    this->initRightCenter();
    this->initRightBottom();

    right_splitter->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    right_splitter->setOrientation(Qt::Vertical);
    right_splitter->setHandleWidth(1);
    right_splitter->setStyleSheet("QSplitter::handle{background:lightgray;}");

    right_top_widget->setFixedSize(220, 46);
    right_bottom_widget->setFixedSize(220, 46);
    right_splitter->addWidget(right_top_widget);
    right_splitter->addWidget(right_center_widget);
    right_splitter->addWidget(right_bottom_widget);
	
	main_splitter->addWidget(right_splitter);
    main_splitter->addWidget(left_widget);
    

    //��ֹ�϶�
    for(int i = 0; i<right_splitter->count();i++)
    {
        QSplitterHandle *handle = right_splitter->handle(i);
        handle->setEnabled(false);
    }

    for(int i = 0; i<main_splitter->count();i++)
    {
        QSplitterHandle *handle = main_splitter->handle(i);
        handle->setEnabled(false);
    }

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(main_splitter);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(main_layout);

    this->translateLanguage();
}

void ContentWidget::initLeft()
{
    left_widget = new QWidget();
    label = new QLabel();
    suggest_label = new QLabel();
    system_safe_label = new QLabel();
    power_button = new QPushButton();

    left_widget->resize(850, 500);

    QPixmap label_pixmap(":/contentWidget/computer");
    label->setPixmap(label_pixmap);
    label->setFixedSize(label_pixmap.size());

    QFont suggest_font = suggest_label->font();
    suggest_font.setPointSize(12);
    suggest_font.setBold(true);
    suggest_label->setFont(suggest_font);
    suggest_label->setStyleSheet("color:gray;");

    QFont system_safe_font = system_safe_label->font();
    system_safe_font.setBold(true);
    system_safe_label->setFont(system_safe_font);
    system_safe_label->setStyleSheet("color:gray;");

    QPixmap pixmap(":/contentWidget/power");
    power_button->setIcon(pixmap);
    power_button->setIconSize(pixmap.size());
    power_button->setFixedSize(180, 70);
    power_button->setStyleSheet("QPushButton{border-radius:5px; background:rgb(110, 190, 10); color:white;}"
                                "QPushButton:hover{background:rgb(140, 220, 35);}");
    QFont power_font = power_button->font();
    power_font.setPointSize(16);
    power_button->setFont(power_font);

    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->addWidget(suggest_label);
    v_layout->addWidget(system_safe_label);
    v_layout->addStretch();
    v_layout->setSpacing(15);
    v_layout->setContentsMargins(0, 20, 0, 0);

    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->addWidget(label, 0, Qt::AlignTop);
    h_layout->addLayout(v_layout);
    h_layout->addStretch();
    h_layout->setSpacing(20);
    h_layout->setContentsMargins(30, 20, 0, 0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(h_layout);
    main_layout->addWidget(power_button, 0, Qt::AlignCenter);
    main_layout->addStretch();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    left_widget->setLayout(main_layout);
}

void ContentWidget::initRight()
{
    right_splitter = new QSplitter();
    //right_splitter->resize(250, 500);
}

void ContentWidget::initRightTop()
{
    right_top_widget = new QWidget();
    open_file = new QPushButton();
	constant_file = new QPushButton();
	//----------------���ļ�------------------------
	open_file->setFixedSize(120, 40);
	open_file->setStyleSheet("QPushButton{color:green; border-image:url(:/contentWidget/login);}"
                                "QPushButton:hover{color:rgb(110, 190, 10);}");
    QFont font = open_file->font();
	font.setBold(true);
	font.setPointSize(10);
	open_file->setFont(font);
	//----------------ʵʱ����------------------------
	constant_file->setFixedSize(120, 40);
	constant_file->setStyleSheet("QPushButton{color:green; border-image:url(:/contentWidget/login);}"
		"QPushButton:hover{color:rgb(110, 190, 10);}");
	constant_file->setFont(font);

    QHBoxLayout *rightTop_layout = new QHBoxLayout();
	rightTop_layout->addWidget(open_file);
	rightTop_layout->addWidget(constant_file);
	rightTop_layout->addStretch();
	rightTop_layout->setContentsMargins(8, 0, 8, 0);

    right_top_widget->setLayout(rightTop_layout);
}

void ContentWidget::initRightCenter()
{
    right_center_widget = new QWidget();

	StarTimeManager = new QtIntPropertyManager(this);
	LengthManager = new QtIntPropertyManager(this);
	FaultTypeManager = new QtEnumPropertyManager(this);
	SatNoManager = new QtIntPropertyManager(this);
	ValueManager = new QtDoublePropertyManager(this);
	FalseAlarmRateManager = new QtDoublePropertyManager(this);
	MissedRateManager = new QtDoublePropertyManager(this);
	NoiseStandardDeviationManager = new QtDoublePropertyManager(this);
	QtGroupPropertyManager *Fault = new QtGroupPropertyManager(this);

	QtProperty *itemFault = Fault->addProperty(tr("���ϲ�������"));
	StarTime = StarTimeManager->addProperty(tr("��ʼʱ��"));
	itemFault->addSubProperty(StarTime);
	Length = LengthManager->addProperty(tr("����ʱ��"));
	itemFault->addSubProperty(Length);
	FaultType = FaultTypeManager->addProperty(tr("��������"));
	QStringList enumNames;
	enumNames << tr("��Ծ����") << tr("б�¹���");
	FaultTypeManager->setEnumNames(FaultType, enumNames);
	itemFault->addSubProperty(FaultType);
	m_Value = ValueManager->addProperty(tr("���Ϸ�ֵ"));
	itemFault->addSubProperty(m_Value);
	m_FalseAlarmRate = FalseAlarmRateManager->addProperty(tr("����"));
	FalseAlarmRateManager->setMaximum(m_FalseAlarmRate, 10);
	FalseAlarmRateManager->setMinimum(m_FalseAlarmRate, 1);
	itemFault->addSubProperty(m_FalseAlarmRate);
	m_MissedRate = MissedRateManager->addProperty(tr("©����"));
	MissedRateManager->setMinimum(m_MissedRate, 1);
	MissedRateManager->setMaximum(m_MissedRate, 10);
	itemFault->addSubProperty(m_MissedRate);
	m_NoiseStandardDeviation = NoiseStandardDeviationManager->addProperty(tr("������׼��"));
	NoiseStandardDeviationManager->setMaximum(m_NoiseStandardDeviation, 33.3);
	NoiseStandardDeviationManager->setMinimum(m_NoiseStandardDeviation, 0);
	itemFault->addSubProperty(m_NoiseStandardDeviation);
	SatNo = SatNoManager->addProperty(tr("�������Ǻ�"));
	SatNoManager->setMaximum(SatNo, 12);
	SatNoManager->setMinimum(SatNo, 1);
	itemFault->addSubProperty(SatNo);

	QtDoubleSpinBoxFactory *spinBoxFactory = new QtDoubleSpinBoxFactory(this);
	QtSpinBoxFactory *IntFactory = new QtSpinBoxFactory(this);
	QtEnumEditorFactory *comboBoxFactory = new QtEnumEditorFactory(this);
	QtAbstractPropertyBrowser *FaultBrowser = new QtGroupBoxPropertyBrowser();
	FaultBrowser->setFactoryForManager(ValueManager, spinBoxFactory);
	FaultBrowser->setFactoryForManager(FalseAlarmRateManager, spinBoxFactory);
	FaultBrowser->setFactoryForManager(MissedRateManager, spinBoxFactory);
	FaultBrowser->setFactoryForManager(NoiseStandardDeviationManager, spinBoxFactory);
	FaultBrowser->setFactoryForManager(SatNoManager, IntFactory);
	FaultBrowser->setFactoryForManager(StarTimeManager, IntFactory);
	FaultBrowser->setFactoryForManager(LengthManager, IntFactory);
	FaultBrowser->setFactoryForManager(FaultTypeManager, comboBoxFactory);
	FaultBrowser->addProperty(itemFault);

	pushbuttonClose = new QPushButton(this);
	pushbuttonClose->setText(tr("ȡ��"));
	pushbuttonOk = new QPushButton(this);
	pushbuttonOk->setText(tr("ȷ��"));
	connect(pushbuttonClose, SIGNAL(clicked()), this, SLOT(CloseSlot()));
	connect(pushbuttonOk, SIGNAL(clicked()), this, SLOT(OkSlot()));
	QHBoxLayout * bottonlayout = new QHBoxLayout;
	bottonlayout->addStretch(1);
	bottonlayout->addWidget(pushbuttonOk);
	bottonlayout->addWidget(pushbuttonClose);

	QVBoxLayout *mainlayout = new QVBoxLayout(this);
	mainlayout->setSpacing(0);
	mainlayout->setContentsMargins(0, 0, 0, 0);

	mainlayout->addWidget(FaultBrowser);
	mainlayout->addLayout(bottonlayout);

    right_center_widget->setLayout(mainlayout);
}

void ContentWidget::initRightBottom()
{
    right_bottom_widget = new QWidget();
	start_button = new QPushButton();
	pause_button = new QPushButton();

	QFont font = open_file->font();
	font.setBold(true);
	font.setPointSize(10);

	start_button->setFixedSize(120, 40);
	start_button->setStyleSheet("QPushButton{color:green; border-image:url(:/contentWidget/login);}"
		"QPushButton:hover{color:rgb(110, 190, 10);}");
	start_button->setFont(font);

	pause_button->setFixedSize(120, 40);
	pause_button->setStyleSheet("QPushButton{color:green; border-image:url(:/contentWidget/login);}"
		"QPushButton:hover{color:rgb(110, 190, 10);}");
	pause_button->setFont(font);

	QHBoxLayout *bottom_layout = new QHBoxLayout();
	bottom_layout->addWidget(start_button);
	bottom_layout->addWidget(pause_button);
	bottom_layout->addStretch();
	bottom_layout->setContentsMargins(8, 0,8, 0);

    right_bottom_widget->setLayout(bottom_layout);
}

void ContentWidget::translateLanguage()
{
    suggest_label->setText(tr("suggest"));
    system_safe_label->setText(tr("system safe"));
    power_button->setText(tr("power"));

	open_file->setText(tr("���ļ�"));
	constant_file->setText(tr("ʵʱ����"));
	
	start_button->setText(tr("��ʼ"));
	pause_button->setText(tr("��ͣ"));
}

