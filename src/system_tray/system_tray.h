#ifndef SYSYTEMTRAY_H
#define SYSYTEMTRAY_H

#include <QSystemTrayIcon>


class QMenu;
class QAction;

class SystemTray : public QSystemTrayIcon
{
	Q_OBJECT

public:
	explicit SystemTray(QWidget *parent = 0);
	~SystemTray();
	void translateLanguage();
	QWidget *main_weidget;
private:
	void createAction();

private:
	QMenu *tray_menu; //���̲˵�
	QAction *action_open; //�������
	QAction *action_logout; //�˳�

};

#endif //SYSYTEMTRAY_H
