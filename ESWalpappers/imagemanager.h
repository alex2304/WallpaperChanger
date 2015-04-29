#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include <vector>
#include "config.h"
#include <QString>

class ImageManager
{
public:
    ImageManager();
    void setPresets(std::vector<Config*> presets);
    bool setCurrPreset(QString name);
    void nextWallpaper();
private:
    /*константы*/
    const QString imgPath = "/img";
    /*компоненты*/
    std::vector<Config*> presets;
    Config* currPreset;
    bool res;
    void changeWallpaper();
};

#endif // IMAGEMANAGER_H
