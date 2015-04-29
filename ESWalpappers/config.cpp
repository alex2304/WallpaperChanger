#include "config.h"

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
