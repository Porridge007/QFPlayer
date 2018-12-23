/********************************************************************************
** Form generated from reading UI file 'QFPlay.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QFPLAY_H
#define UI_QFPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "qfslider.h"
#include "videowidget.h"

QT_BEGIN_NAMESPACE

class Ui_QFPlayClass
{
public:
    VideoWidget *openGLWidget;
    QPushButton *openButton;
    QPushButton *playButton;
    QLabel *totaltime;
    QLabel *playtime;
    QLabel *label;
    QFSlider *playslider;

    void setupUi(QWidget *QFPlayClass)
    {
        if (QFPlayClass->objectName().isEmpty())
            QFPlayClass->setObjectName(QStringLiteral("QFPlayClass"));
        QFPlayClass->resize(800, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/QFPlay/Resources/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        QFPlayClass->setWindowIcon(icon);
        openGLWidget = new VideoWidget(QFPlayClass);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 800, 600));
        openButton = new QPushButton(QFPlayClass);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(310, 500, 56, 56));
        openButton->setStyleSheet(QLatin1String("QPushButton:!hover{border-image: url(:/QFPlay/Resources/open_normal.png);}\n"
"QPushButton:hover{border-image: url(:/QFPlay/Resources/open_hot.png);}"));
        playButton = new QPushButton(QFPlayClass);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(470, 500, 56, 56));
        playButton->setStyleSheet(QLatin1String("QPushButton:!hover{border-image: url(:/QFPlay/Resources/play_normal.png);}\n"
"QPushButton:hover{border-image: url(:/QFPlay/Resources/play_hot.png);}"));
        totaltime = new QLabel(QFPlayClass);
        totaltime->setObjectName(QStringLiteral("totaltime"));
        totaltime->setGeometry(QRect(210, 530, 91, 16));
        totaltime->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255); \n"
"font:16pt \"\351\273\221\344\275\223\";"));
        playtime = new QLabel(QFPlayClass);
        playtime->setObjectName(QStringLiteral("playtime"));
        playtime->setGeometry(QRect(100, 530, 91, 16));
        playtime->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255); \n"
"font:16pt \"\351\273\221\344\275\223\";"));
        label = new QLabel(QFPlayClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(190, 530, 21, 21));
        label->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255); \n"
"font:16pt \"\351\273\221\344\275\223\";"));
        playslider = new QFSlider(QFPlayClass);
        playslider->setObjectName(QStringLiteral("playslider"));
        playslider->setGeometry(QRect(80, 470, 641, 19));
        playslider->setMaximumSize(QSize(16777215, 16777215));
        playslider->setMaximum(999);
        playslider->setOrientation(Qt::Horizontal);

        retranslateUi(QFPlayClass);
        QObject::connect(openButton, SIGNAL(clicked()), QFPlayClass, SLOT(open()));
        QObject::connect(playslider, SIGNAL(sliderPressed()), QFPlayClass, SLOT(sliderPress()));
        QObject::connect(playslider, SIGNAL(sliderReleased()), QFPlayClass, SLOT(sliderRelease()));
        QObject::connect(playButton, SIGNAL(clicked()), QFPlayClass, SLOT(play()));

        QMetaObject::connectSlotsByName(QFPlayClass);
    } // setupUi

    void retranslateUi(QWidget *QFPlayClass)
    {
        QFPlayClass->setWindowTitle(QApplication::translate("QFPlayClass", "\347\250\200\351\245\255\345\244\247\345\244\247\347\232\204\346\222\255\346\224\276\345\231\250", Q_NULLPTR));
        openButton->setText(QString());
        playButton->setText(QString());
        totaltime->setText(QApplication::translate("QFPlayClass", "00:00:00", Q_NULLPTR));
        playtime->setText(QApplication::translate("QFPlayClass", "00:00:00", Q_NULLPTR));
        label->setText(QApplication::translate("QFPlayClass", "/", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QFPlayClass: public Ui_QFPlayClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QFPLAY_H
