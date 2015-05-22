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
    //динамически выделяемая память
    this->imgManager = new ImageManager();
    this->confManager = new ConfigManager();
    this->initiallizeDynamicComponents();

    //подготовка остальных компонентов
    this->trayActiveImage = QIcon(iconPath + iconActive + iconFormat);
    this->trayDeactiveImage = QIcon(iconPath + iconDeactive + iconFormat);
    imgManager->setPresets(confManager->getConfigsFromFiles()); //чтение и установка пользовательских пресетов
    imgManager->setTimer(timer);

    //отображение на экран
    this->buildTrayMenu(false); //создание и настройка контекстного меню
    this->showTrayIcon(); //создание иконки для трея и вывод её в трей
}

ESWindow::~ESWindow()
{
    clearFilterActions();
    delete filterGroup;
    delete confManager;
    delete imgManager;
    delete trayIconMenu;
    delete trayIcon;
    delete changeAction;
    delete autoLoadAction;
    delete refreshAction;
    delete quitAction;
    if (timer != NULL){
        if (timer->isActive()){
            timer->stop();
        }
        delete timer;
    }
    delete ui;
}

void ESWindow::initiallizeDynamicComponents(){
    //cоздание иконки
    trayIcon = new QSystemTrayIcon(this);

    //создание меню
    trayIconMenu = new QMenu(this);

    //создание группы элементов меню конфигов
    filterGroup = new QActionGroup(this);
    filterGroup->setExclusive(true);

    //создание таймера
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextImage())); //подключение обработчика к таймеру

    //создание прочих действий меню
    changeAction = new QAction("Следующее изображение", this);
    changeAction->setIcon(QIcon(iconPath + "next" + iconFormat));
    changeAction->setShortcut(QKeySequence("Ctrl+Alt+Q"));
    refreshAction = new QAction("Обновить конфигурацию", this);
    refreshAction->setIcon(QIcon(iconPath + "refresh4" + iconFormat));
    autoLoadAction = new QAction("Запускать вместе с системой", this);
    autoLoadAction->setCheckable(true);
    autoLoadAction->setChecked(isInAutoload());
    quitAction = new QAction("Выход", this);

    //задание действий на элементы управления
    connect (changeAction, SIGNAL(triggered()), this, SLOT(nextImage())); //функцию сделать
    connect (refreshAction, SIGNAL(triggered()), this, SLOT(updateConfigs()));
    connect (autoLoadAction, SIGNAL(triggered()), this, SLOT(autoLoadChange())); //функцию сделать
    connect (quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

}

void ESWindow::buildTrayMenu(bool menuFromFile)
{
    //создание пользовательских элементов менюи привязка их к событиям. построение меню.
    buildActions((menuFromFile) ? confManager->getConfigsFromFiles(): confManager->getConfigs());
    bindActions();
}

void ESWindow::buildActions(std::vector<Config*> configs){
    clearFilterActions();
    for (int i = 0; i < configs.size(); i++){
        QAction* action = getQActionFromConfig(configs[i]);
        if (action != NULL) filterActions.push_back(action);
    }
}

void ESWindow::clearFilterActions(){
    trayIconMenu->clear();
    for (std::vector<QAction*>::iterator it = filterActions.begin(); it != filterActions.end(); it++){
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
            result->setActionGroup(filterGroup);
            if ((param = conf->getIcon()) != ""){
                result->setIcon(QIcon(iconPath + param + iconFormat));
            } else {
                result->setIcon(trayActiveImage);
            }
            result->setCheckable(true);
            result->setMenuRole(QAction::TextHeuristicRole);
        } else result = NULL;
    }
    return result;
}

void ESWindow::bindActions(){
    for (std::vector<QAction*>::iterator it = filterActions.begin(); it != filterActions.end(); it++){
        //задание действий на пользовательские пресеты
        connect(*it, SIGNAL(triggered()), this, SLOT(setPreset()));
        //построение меню
        trayIconMenu->addAction(*it);
    }

    //построение меню
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(changeAction);
    trayIconMenu->addAction(refreshAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(autoLoadAction);
    trayIconMenu->addAction(quitAction);
}

void ESWindow::showTrayIcon(){
    trayIcon->setIcon(trayDeactiveImage);
    trayIcon->setContextMenu(trayIconMenu);

    //подключение обработчика клика по иконке...
    /*connect(trayIcon,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason))); */

    //вывод значка...
    trayIcon->show();
}

//----------------------------------------------------------------//

void ESWindow::updateConfigs(){
    buildTrayMenu(true);
    imgManager->setPresets(confManager->getConfigs());
    trayIcon->setIcon(trayDeactiveImage);
    trayIcon->setContextMenu(trayIconMenu);
}

void ESWindow::setPreset(){
    for (std::vector<QAction*>::iterator it = filterActions.begin(); it != filterActions.end(); it++){
        if ((*it)->isChecked()){
            QString c = (*it)->text();
            if (this->imgManager->setCurrPreset((*it)->text())) trayIcon->setIcon(trayActiveImage);
            break;
        }
    }
}

void ESWindow::nextImage()
{
    if (this->imgManager != NULL)
        this->imgManager->nextWallpaper();
}

/*void ESWindow::trayActionExecute()
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
} */

bool ESWindow::isInAutoload(){
    QSettings regEdit(autoLoadPath, QSettings::NativeFormat);
    return (regEdit.value("ESWallpaper", "").toString() != "");
}

void ESWindow::autoLoadChange(){
    QSettings regEdit(autoLoadPath, QSettings::NativeFormat);
    if (autoLoadAction->isChecked()){
        QString path = QFileInfo("ESWallpaper.exe").absoluteFilePath().replace("/", "\\");
        try {
            regEdit.setValue("ESWallpaper", path);
        } catch (const exception& e){
            qWarning("Can't write to autoload");
        }
    } else {
        regEdit.remove("ESWallpaper");
    }
}


