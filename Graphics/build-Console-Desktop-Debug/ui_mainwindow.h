/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *formLayoutWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *previusButton;
    QPushButton *playButton;
    QPushButton *nextButton;
    QLabel *songTitleLabel;
    QListWidget *listSong;
    QGraphicsView *waveGraphics;
    QProgressBar *songProgress;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(400, 300);
        MainWindow->setMinimumSize(QSize(400, 300));
        MainWindow->setMaximumSize(QSize(400, 300));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(9, 9, 381, 272));
        gridLayout = new QGridLayout(formLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        previusButton = new QPushButton(formLayoutWidget);
        previusButton->setObjectName(QString::fromUtf8("previusButton"));
        previusButton->setMaximumSize(QSize(96, 96));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../icons/prev.svg"), QSize(), QIcon::Normal, QIcon::Off);
        previusButton->setIcon(icon);
        previusButton->setIconSize(QSize(60, 60));

        horizontalLayout->addWidget(previusButton);

        playButton = new QPushButton(formLayoutWidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setMaximumSize(QSize(96, 96));
        playButton->setAutoFillBackground(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../icons/play.svg"), QSize(), QIcon::Normal, QIcon::Off);
        playButton->setIcon(icon1);
        playButton->setIconSize(QSize(60, 60));

        horizontalLayout->addWidget(playButton);

        nextButton = new QPushButton(formLayoutWidget);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setMaximumSize(QSize(96, 96));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../icons/next.svg"), QSize(), QIcon::Normal, QIcon::Off);
        nextButton->setIcon(icon2);
        nextButton->setIconSize(QSize(60, 60));

        horizontalLayout->addWidget(nextButton);


        verticalLayout->addLayout(horizontalLayout);

        songTitleLabel = new QLabel(formLayoutWidget);
        songTitleLabel->setObjectName(QString::fromUtf8("songTitleLabel"));
        songTitleLabel->setMaximumSize(QSize(16777215, 15));

        verticalLayout->addWidget(songTitleLabel);

        listSong = new QListWidget(formLayoutWidget);
        listSong->setObjectName(QString::fromUtf8("listSong"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listSong->sizePolicy().hasHeightForWidth());
        listSong->setSizePolicy(sizePolicy);
        listSong->setMaximumSize(QSize(16777215, 80));

        verticalLayout->addWidget(listSong);

        waveGraphics = new QGraphicsView(formLayoutWidget);
        waveGraphics->setObjectName(QString::fromUtf8("waveGraphics"));
        waveGraphics->setMaximumSize(QSize(16777215, 50));
        waveGraphics->setAutoFillBackground(true);
        waveGraphics->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 0, 0)"));
        waveGraphics->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        waveGraphics->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QBrush brush(QColor(201, 223, 50, 255));
        brush.setStyle(Qt::SolidPattern);
        waveGraphics->setBackgroundBrush(brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        waveGraphics->setForegroundBrush(brush1);
        waveGraphics->setInteractive(true);
        waveGraphics->setSceneRect(QRectF(0, 0, 0, 0));
        waveGraphics->setRenderHints(QPainter::TextAntialiasing);

        verticalLayout->addWidget(waveGraphics);

        songProgress = new QProgressBar(formLayoutWidget);
        songProgress->setObjectName(QString::fromUtf8("songProgress"));
        songProgress->setMaximum(100);
        songProgress->setValue(22);
        songProgress->setInvertedAppearance(false);

        verticalLayout->addWidget(songProgress);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Lettore/Console", 0, QApplication::UnicodeUTF8));
        previusButton->setText(QString());
        playButton->setText(QString());
        nextButton->setText(QString());
        songTitleLabel->setText(QApplication::translate("MainWindow", "Canzone Attuale:", 0, QApplication::UnicodeUTF8));
        songProgress->setFormat(QApplication::translate("MainWindow", "%p secondi di 100 trascorsi", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
