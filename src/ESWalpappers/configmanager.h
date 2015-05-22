#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
#include <QDir>
#include <QSettings>
#include <QSTring>
#include "config.h"
#include <QFileInfoList>
#include <QFileInfo>

class ConfigManager;

class IniMaster {

    Q_ENUMS(MainSec)
    Q_ENUMS(TimelapseSec)

    friend class ConfigManager;
    static QString MAIN_SEC, TIMELAPSE_SEC;
    enum MainSec {
        name = 0, icon = 1,
        time = 2, folder = 3,
        subfolders = 4, type = 5
    };
    enum TimelapseSec {
        dayFolder = 0, eveningFolder = 1, nightFolder = 2
    };
};



//загружает из файлов, проверяет на корректность и хранит список настроек
class ConfigManager
{
private:
    const QString PATH = "./conf"; //путь к папке конфигурации
    const QSettings::Format FILE_FORMAT = QSettings::IniFormat; //формат файлов конфигурации
    const QString FILE_RESOLUTION = "*.ini"; //формат файла
    bool dirExists;
    /* работа с файлами конфигурации */
    QDir dir; //папка с файлами конфигурации
    std::vector<Config*> configs; //список конфигураций
    QTextCodec* codec; //кодек для кодирования файлов конфигураций

    Config* getConfigFromFile(QString filename);
    bool checkConfigFile(QSettings& confFile);
    void clearConfigs();
public:
    std::vector<Config*> getConfigsFromFiles();
    std::vector<Config*> getConfigs();
    ConfigManager();
    ~ConfigManager();
};



#endif // CONFIGMANAGER_H
