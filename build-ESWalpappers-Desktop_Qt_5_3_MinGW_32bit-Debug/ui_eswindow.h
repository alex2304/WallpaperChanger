/********************************************************************************
** Form generated from reading UI file 'eswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ESWINDOW_H
#define UI_ESWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ESWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ESWindow)
    {
        if (ESWindow->objectName().isEmpty())
            ESWindow->setObjectName(QStringLiteral("ESWindow"));
        ESWindow->resize(400, 300);
        menuBar = new QMenuBar(ESWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ESWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ESWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ESWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(ESWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ESWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ESWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ESWindow->setStatusBar(statusBar);

        retranslateUi(ESWindow);

        QMetaObject::connectSlotsByName(ESWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ESWindow)
    {
        ESWindow->setWindowTitle(QApplication::translate("ESWindow", "ESWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class ESWindow: public Ui_ESWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ESWINDOW_H
