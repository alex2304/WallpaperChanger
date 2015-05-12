#ifndef ESWINDOW_H
#define ESWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QSettings>
#include <QDir>
#include <QString>
#include "configmanager.h"
#include "config.h"
#include "imagemanager.h"
#include <QActionGroup>

namespace Ui {
class ESWindow;
}

class ESWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ESWindow(QWidget *parent = 0);
    ~ESWindow();

private slots:
    /*void changeEvent(QEvent*); //перехват события минимизации окна
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason); //
    void trayActionExecute();*/
    void buildTrayMenu(bool menuFromFile);
    void showTrayIcon();
    void updateConfigs();
    void setPreset();
    void nextImage();
    void autoLoadChange();

private:
    Ui::ESWindow* ui;
    const QString iconPath = ":/icons/", iconFormat = ".png";
    const QString iconDeactive = "icon_deactive", iconActive = "icon_active";
    const QString autoLoadPath = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    /* сурсы */
    ConfigManager* confManager; //менеджер конфигов
    ImageManager* imgManager; //менеджер смены изображений
    /* части приложения */
    QIcon trayActiveImage, trayDeactiveImage;
    QMenu* trayIconMenu; //контекстное меню приложения
    QSystemTrayIcon* trayIcon; //иконка приложения
    QTimer* timer; //таймер для смены изображений
    /* пункты меню */
    QActionGroup* filterGroup;
    std::vector<QAction*> filterActions; //действия для пользовательских пресетов
    QAction* autoLoadAction; //действие для пункта меню "добавить в автозагрузку"
    QAction* changeAction; //действие для пункта "следующие обои"
    QAction* refreshAction; //действие для пункта "обновить"
    QAction* quitAction; //действие для пункта меню "выход"

    void buildActions(std::vector<Config*> configs);
    void bindActions();
    void clearFilterActions();
    QAction* getQActionFromConfig(Config* conf);

    bool isInAutoload();

};

#endif // ESWINDOW_H
