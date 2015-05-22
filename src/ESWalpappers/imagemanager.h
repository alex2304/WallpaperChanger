#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include <vector>
#include "config.h"
#include <QString>
#include <QSettings>
#include <time.h>
#include <QTimer>

class ImageManager
{
public:
    ImageManager();
    ~ImageManager();
    void setPresets(std::vector<Config*> presets);
    bool setCurrPreset(QString name);
    void nextWallpaper();
    void setTimer(QTimer* timer);
private:
    /*константы*/
    const QString regPath = "HKEY_CURRENT_USER\\Control Panel\\Desktop";
    const QString wStyle = "2", wTile = "0";
    const QString imgPath = "./img";
    /*компоненты*/
    std::vector<Config*> presets;
    Config* currPreset;
    QString currImg;
    QFileInfoList images;
    QTimer* timer;
    /*методы*/
    bool changeWallpaper();
    QFileInfo* getNextImage();
};

#endif // IMAGEMANAGER_H
