#include "config.h"

int getTimesOfDay(){ //0 - утро, ...
    int hours = QTime::currentTime().hour();
    if (hours > 6 && hours < 10) return 0;
    if (hours >= 10 && hours < 17) return 1;
    if (hours >= 17 && hours < 23) return 2;
    return 3;
}

Config::Config(QString name, QString icon, int time, QString folder, bool subfolders, QString type)
{
    this->name = name;
    this->icon = icon;
    this->time = time;
    this->folder = folder;
    this->subfolders = subfolders;
    this->type = (type == "timelapse") ? timelapse: single;
}

Config::Config(){
}

void Config::setName(QString name) {
    this->name = name;
}
void Config::setIcon(QString icon) {
    this->icon = icon;
}
void Config::setTime(int time) {
    this->time = time;
}
void Config::setFolder(QString folder) {
    this->folder = folder;
}
void Config::setSubfolders(bool subfolders) {
    this->subfolders = subfolders;
}
void Config::setType(Type type) {
    this->type = type;
}

void Config::setType(QString type){
    this->type = (type == "timelapse") ? timelapse: single;
}

void Config::setTimelapseFolders(QString dayFolder, QString eveningFolder, QString nightFolder) {
    this->dayFolder = dayFolder;
    this->eveningFolder = eveningFolder;
    this->nightFolder = nightFolder;
}

QString Config::getName(){
    return name;
}

QString Config::getIcon(){
    return icon;
}

int Config::getTime(){
    return time;
}

QString Config::getFolder(){
    return folder;
}

bool Config::getSubfolders(){
    return subfolders;
}

Config::Type Config::getType(){
    return type;
}

QString Config::getDayFolder(){
    return dayFolder;
}

QString Config::getEveningFolder(){
    return eveningFolder;
}

QString Config::getNightFolder(){
    return nightFolder;
}

//возвращает список имён изображений относительно корневой папки изображений
QFileInfoList Config::getAllImages()
{
    QFileInfoList result;
    QDir dir;
    QString foldName = imgPath + "/" + folder; //имя папки с изображениями
    if (type == timelapse){
        foldName += getTimeFolder();
    }

    dir.setSorting(QDir::Size | QDir::Reversed); //установка сортировки
    getImagesRecursive(result, dir, foldName);
    return result;
}

void Config::getImagesRecursive(QFileInfoList& result, QDir& dir, QString path){
    if (!(dir.cd(path) && dir.isReadable())) return;
    dir.setFilter((QDir::Filters)imgFilter);
    QStringList filtersImg;
    filtersImg << "*.png" << "*.jpg" << "*.bmp";
    dir.setNameFilters(QStringList(filtersImg)); //установка типов файла
    result += dir.entryInfoList();

    if (subfolders){
        dir.setNameFilters(QStringList());
        dir.setFilter((QDir::Filters)folderFilter);
        QFileInfoList folders = dir.entryInfoList();
        for (int i = 0; i < folders.size(); i++){
            getImagesRecursive(result, dir, folders[i].absoluteFilePath());
        }
    }
}


QString Config::getTimeFolder()
{
    QString result;
    switch (getTimesOfDay()){
        case 0: case 2: result = "/" + eveningFolder; break;
        case 1: result = "/" + dayFolder; break;
        case 3: result = "/" + nightFolder; break;
    }
    return result;
}


