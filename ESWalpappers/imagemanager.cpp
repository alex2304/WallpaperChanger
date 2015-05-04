#include "imagemanager.h"
#include <windows.h>
#include <iostream>
#include <QSettings>
ImageManager::ImageManager()
{
    this->currPreset = NULL;
    this->timer = NULL;
    QSettings regEdit(regPath, QSettings::NativeFormat);
    regEdit.setValue("WallpaperStyle", "2");
    regEdit.setValue("TileWallpaper", "0");
}

ImageManager::~ImageManager()
{

}

void ImageManager::setPresets(std::vector<Config*> presets){
    this->presets = presets;
    if (timer != NULL)
        if (timer->isActive())
            timer->stop();
}

bool ImageManager::setCurrPreset(QString name){
    bool exists = false;
    for (std::vector<Config*>::iterator it = presets.begin(); it != presets.end(); it++){
        if (name == (*it)->getName()){
            currPreset = (*it);
            changeWallpaper();
            exists = true;
            break;
        }
    }
    return exists;
}

void ImageManager::nextWallpaper()
{
    changeWallpaper();
}

void ImageManager::setTimer(QTimer *timer)
{
    this->timer = timer;
}

bool ImageManager::changeWallpaper(){

    if (currPreset == NULL) return false;

    QSettings regEdit(regPath, QSettings::NativeFormat);
    images = currPreset->getAllImages();
    if (!images.isEmpty()){
        QString img = getNextImage();
        if (currPreset->getType() == Config::timelapse)
            img = currPreset->getTimeFolder() + "\\" + img;
        regEdit.setValue("Wallpaper", QFileInfo(imgPath + "\\" + currPreset->getFolder() + "\\" + img ).absoluteFilePath().replace("/", "\\"));
        if (!timer->isActive()){
            timer->start(currPreset->getTime()*1000);
        } else {
            timer->setInterval(currPreset->getTime()*1000);
        }
        return !SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, NULL, SPIF_SENDWININICHANGE);
    } else {
        return false;
    }
}

QString ImageManager::getNextImage()
{
    if (images.isEmpty()) return "";
    srand(time(NULL));
    int number = rand() % images.size();
    return images[number];
}
