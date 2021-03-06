#include "configmanager.h"
#include <QTextCodec>
#include <QByteArray>

QString IniMaster::MAIN_SEC = "MainSettings", IniMaster::TIMELAPSE_SEC = "Timelapse";
QString mValues[6] = {"name", "icon",
                                              "time", "folder",
                                              "subfolders", "type"},
                     tValues[3] = {"day_folder", "evening_folder", "night_folder"};

ConfigManager::ConfigManager()
{
    this->dirExists = (this->dir.cd(this->PATH) && this->dir.isReadable()); //установка пути к директории конфигов и проверка существования каталога
    this->dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks); //установка фильтров файлов
    this->dir.setNameFilters(QStringList(FILE_RESOLUTION)); //установка типов файла
    this->dir.setSorting(QDir::Size | QDir::Reversed); //установка сортировки
    codec = QTextCodec::codecForName("Windows-1251"); //установка кодека
}

ConfigManager::~ConfigManager(){
    clearConfigs();
}

void ConfigManager::clearConfigs(){
    for (int i = 0; i < configs.size(); i++){
        delete configs[i];
    }
}

std::vector<Config*> ConfigManager::getConfigs(){
    return configs;
}

std::vector<Config*> ConfigManager::getConfigsFromFiles(){
    std::vector<Config*> tmpConfigs;
    if (dirExists){ //директория имеется
        QFileInfoList list = dir.entryInfoList(); //получение списка файлов директории
        for (int i = 0; i < list.size(); i++){
            QFileInfo fileInfo = list.at(i);
            try {
                tmpConfigs.push_back(getConfigFromFile(fileInfo.fileName()));
            } catch (const IncorrectConfigException& e){
                //проблемы с конфигом
            }
        }
    } else { //проблемы с директорией

    }
    clearConfigs();
    configs = tmpConfigs;
    return configs;
}

Config* ConfigManager::getConfigFromFile(QString filename){
    QSettings confFile(this->PATH + "/" + filename, this->FILE_FORMAT); //установка файла
    confFile.setIniCodec(codec);
    if (!checkConfigFile(confFile)) throw IncorrectConfigException();
    Config* newConf = new Config();
    try {
        confFile.beginGroup(IniMaster::MAIN_SEC);
            newConf->setName(confFile.value(mValues[IniMaster::name]).toString());
            newConf->setIcon(confFile.value(mValues[IniMaster::icon], "").toString());
            newConf->setTime(confFile.value(mValues[IniMaster::time]).toInt());
            newConf->setFolder(confFile.value(mValues[IniMaster::folder]).toString());
            newConf->setSubfolders(confFile.value(mValues[IniMaster::subfolders], 0).toBool());
            newConf->setType(confFile.value(mValues[IniMaster::type]).toString());
        confFile.endGroup();
        if (newConf->getType() == Config::timelapse){
            confFile.beginGroup(IniMaster::TIMELAPSE_SEC);
            newConf->setTimelapseFolders(confFile.value(tValues[IniMaster::dayFolder]).toString(),
                                     confFile.value(tValues[IniMaster::eveningFolder]).toString(),
                                     confFile.value(tValues[IniMaster::nightFolder]).toString());
            confFile.endGroup();
        }
    } catch (const exception& e){
        delete newConf;
        throw IncorrectConfigException();
    }
    return newConf;
}

bool ConfigManager::checkConfigFile(QSettings& confFile){
    if (confFile.childGroups().contains(IniMaster::MAIN_SEC)){
        confFile.beginGroup(IniMaster::MAIN_SEC);
        bool mainOk = (confFile.contains(mValues[IniMaster::name]) && confFile.contains(mValues[IniMaster::folder]) && confFile.contains(mValues[IniMaster::type]));
        QString tmString = confFile.value(mValues[IniMaster::time], "").toString();
        int tmInt = tmString.toInt(&mainOk);
        mainOk = (tmInt > 0 && tmInt < 172800);
        confFile.endGroup();
        if (mainOk){
            if (confFile.value(IniMaster::MAIN_SEC + "/" + mValues[IniMaster::type], "").toString() == "timelapse"){
                if (confFile.childGroups().contains(IniMaster::TIMELAPSE_SEC)){
                    confFile.beginGroup(IniMaster::TIMELAPSE_SEC);
                    bool timelapseOk = (confFile.contains(tValues[IniMaster::dayFolder]) && confFile.contains(tValues[IniMaster::eveningFolder]) && confFile.contains(tValues[IniMaster::nightFolder]));
                    confFile.endGroup();
                    return timelapseOk;
                }
            } else return true;
        }
    }
    return false;
}
