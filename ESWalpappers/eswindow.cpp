#include "eswindow.h"
#include "ui_eswindow.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
#include <QSettings>
#include <QVariant>

ESWindow::ESWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ESWindow)
{
    ui->setupUi(this);
    this->imgManager = new ImageManager();
    this->confManager = new ConfigManager();
    imgManager->setPresets(confManager->getConfigsFromFiles()); //чтение и установка пользовательских пресетов
    this->buildTrayMenu(false); //создание и настройка контекстного меню
    this->showTrayIcon(); //создание иконки для трея и вывод её в трей
}

ESWindow::~ESWindow()
{
    delete ui;
    clearFilterActions();
    delete confManager;
    delete imgManager;
    delete trayIconMenu;
    delete trayIcon;
    delete changeAction;
    delete autoLoadAction;
    delete refreshAction;
    delete quitAction;
}

void ESWindow::clearFilterActions(){
    for (std::vector<QAction*>::iterator it = filterActions.begin(); it != filterActions.end(); it++){
        trayIconMenu->removeAction(*it);
        delete *it;
    }
    filterActions.clear();
}

QAction* ESWindow::getQActionFromConfig(Config* conf){
    QAction* result;
    if (conf != NULL){
        QString param = conf->getName();
        if (param != NULL){
            result = new QAction(param, this);
            if ((param = conf->getIcon()) != ""){
                result->setIcon(QIcon(iconPath + param + iconFormat));
            } else {
                result->setIcon(QIcon(iconPath + "icon1" + iconFormat));
            }
            result->setCheckable(true);
            result->setMenuRole(QAction::TextHeuristicRole);
        } else result = NULL;
    }
    return result;
}

void ESWindow::buildActions(std::vector<Config*> configs){
    clearFilterActions();
    for (int i = 0; i < configs.size(); i++){
        QAction* action = getQActionFromConfig(configs[i]);
        if (action != NULL) filterActions.push_back(action);
    }
    //создание элементов меню управления
    changeAction = new QAction("Следующее изображение", this);
    changeAction->setIcon(QIcon(iconPath + "next" + iconFormat));
    refreshAction = new QAction("Обновить конфигурацию", this);
    refreshAction->setIcon(QIcon(iconPath + "refresh4" + iconFormat));
    autoLoadAction = new QAction("Запускать вместе с системой", this);
    quitAction = new QAction("Выход", this);
}

void ESWindow::bindActions(){
    for (std::vector<QAction*>::iterator it = filterActions.begin(); it != filterActions.end(); it++){
        //задание действий на пользовательские пресеты
        connect(*it, SIGNAL(triggered()), this, SLOT(setPreset()));
        //построение меню
        trayIconMenu->addAction(*it);
    }
    //задание действий на элементы управления
    //connect (changeAction, SIGNAL(triggered()), this, SLOT(nextImage())); //функцию сделать
    connect (refreshAction, SIGNAL(triggered()), this, SLOT(updateConfigs()));
    //connect (autoLoadAction, SIGNAL(triggered()), this, SLOT(autoLoad())); //функцию сделать
    connect (quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    //построение меню
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(changeAction);
    trayIconMenu->addAction(refreshAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(autoLoadAction);
    trayIconMenu->addAction(quitAction);
}

void ESWindow::updateConfigs(){
    buildTrayMenu(true);
    trayIcon->setContextMenu(trayIconMenu);
}

void ESWindow::setPreset(){
    for (std::vector<QAction*>::iterator it = filterActions.begin(); it != filterActions.end(); it++){
        if ((*it)->isChecked()){
            QString c = (*it)->text();
            this->imgManager->setCurrPreset((*it)->text());
            break;
        }
    }
}

void ESWindow::buildTrayMenu(bool menuFromFile)
{
    //создание меню
    trayIconMenu = new QMenu(this);
    //создание пользовательских элементов менюи привязка их к событиям. построение меню.
    buildActions((menuFromFile) ? confManager->getConfigsFromFiles(): confManager->getConfigs());
    bindActions();
}

void ESWindow::showTrayIcon(){
    //cоздание экземпляра класса и задание его свойств...
    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(iconPath + "icon1.png");
    trayIcon->setIcon(trayImage);
    trayIcon->setContextMenu(trayIconMenu);

    //подключение обработчика клика по иконке...
    connect(trayIcon,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    //вывод значка...
    trayIcon->show();
}

void ESWindow::trayActionExecute()
{
    QMessageBox::information(this, "TrayIcon", "Тестовое сообщение. Замените вызов этого сообщения своим кодом.");
}

void ESWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            this->trayActionExecute();
            break;
        default:
            break;
    }
}

void ESWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    if (event->type() == QEvent::WindowStateChange)
    {
        if (isMinimized())
        {
            this->hide();
        }
    }
}


