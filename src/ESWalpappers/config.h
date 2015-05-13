#ifndef CONFIG_H
#define CONFIG_H
#include <QString>
#include <QTime>
#include <QDir>

using namespace std;

class Config
{
    Q_ENUMS(Type)

public:
    enum Type{
        timelapse, single
    };

private:
    const QString imgPath = "./img";
    const int folderFilter = QDir::Dirs |
                             QDir::NoSymLinks |
                             QDir::NoDot |
                             QDir::NoDotDot |
                             QDir::NoDotAndDotDot,
              imgFilter    = QDir::Files |
                             QDir::Hidden |
                             QDir::NoSymLinks;
    QString name, icon;
    int time;
    QString folder;
    bool subfolders;
    Type type;
    QString dayFolder, eveningFolder, nightFolder;
    QString getTimeFolder();
    void getImagesRecursive(QFileInfoList& result, QDir& dir, QString path);
public:
    Config(QString name, QString icon, int time, QString folder, bool subfolders, QString type);
    Config();
    void setName(QString name) ;
    void setIcon(QString icon) ;
    void setTime(int time) ;
    void setFolder(QString folder) ;
    void setSubfolders(bool subfolders) ;
    void setType(Type type);
    void setType(QString type);
    void setTimelapseFolders(QString dayFolder, QString eveningFolder, QString nightFolder) ;

    QString getName();
    QString getIcon();
    int getTime();
    QString getFolder();
    bool getSubfolders();
    Type getType();
    QString getDayFolder();
    QString getEveningFolder();
    QString getNightFolder();
    QFileInfoList getAllImages();
};

class IncorrectConfigException: public exception
{

};

#endif // CONFIG_H
