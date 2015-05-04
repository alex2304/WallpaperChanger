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

//возвращает список имён изображений, доступных для этого конфига
QStringList Config::getAllImages()
{
    QStringList result;
    QDir dir;
    QString foldName = imgPath + "/" + folder; //имя папки с изображениями
    if (type == timelapse){
        foldName += getTimeFolder();
    }
    if (!(dir.cd(foldName) && dir.isReadable())) return result; //установка пути к директории изображений и проверка существования каталога
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks); //установка фильтров файлов
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.bmp";
    dir.setNameFilters(QStringList(filters)); //установка типов файла
    dir.setSorting(QDir::Size | QDir::Reversed); //установка сортировки
    result = dir.entryList(); //получение инфы об изображениях
    return result;
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


