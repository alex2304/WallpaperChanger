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
    currImg = "";
    currPreset = NULL;
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
        regEdit.setValue("Wallpaper", getNextImage()->absoluteFilePath().replace("/", "\\"));
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

QFileInfo* ImageManager::getNextImage()
{
    if (images.isEmpty()) return NULL;
    if (images.size() == 1) return &images[0];

    srand(time(NULL));
    int number;
    try {
        do {
            number = rand() % images.size();
        } while (images[number].fileName() == currImg);
    } catch (const exception& e){
        return NULL;
    }
    currImg = images[number].fileName();
    return &images[number];
}
