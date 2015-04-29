#include "imagemanager.h"
#include <windows.h>
#include <iostream>
ImageManager::ImageManager()
{
}

void ImageManager::setPresets(std::vector<Config*> presets){
    this->presets = presets;
    changeWallpaper();
}

bool ImageManager::setCurrPreset(QString name){
    bool exists = false;
    for (std::vector<Config*>::iterator it = presets.begin(); it != presets.end(); it++){
        if (name == (*it)->getName()){
            currPreset = (*it);
            exists = true;
        }
    }
    return exists;
}

void ImageManager::changeWallpaper(){

    /*if (bmp){
        RegWriteString(HKEY_CURRENT_USER, "Control Panel\\Desktop", "WallpaperStyle", "2");
        RegWriteString(HKEY_CURRENT_USER, "Control Panel\\Desktop", "TileWallpaper", "0");
    } else {
    }*/
    res = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)"E:\ext_beach_day.bmp", SPIF_SENDCHANGE);
}
