#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "../skin_widget/skin_widget.h"
#include "../system_tray/system_tray.h"
#include "../title_widget/title_widget.h"
#include "../content_widget/content_widget.h"

#include <QSystemTrayIcon>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void showWidget();

private slots:
    void showMax();
    void showSkinWidget();
    void showMainMenu();
    void changeSkin(QString skin_name);
    void iconIsActived(QSystemTrayIcon::ActivationReason reason);

private:
    QRect location;
    TitleWidget *title_widget; //������
    ContentWidget *content_widget; //����������
    SystemTray *system_tray; //������
    QString skin_name;//�����ڱ���ͼƬ������
    SkinWidget *skin_widget; //��ʾƤ������

};

#endif // MAINWIDGET_H
