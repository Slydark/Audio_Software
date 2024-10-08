/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *sampleRateLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *labelTitleWav;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *openButton;
    QPushButton *FFTButton;
    QPushButton *inverseFFTButton;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_2;
    QComboBox *comboBoxOrdreFiltre;
    QPushButton *FiltreButton;
    QLineEdit *lineEditFrequenceCoupure;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSlider *positionSlider;
    QLabel *labelDuration;
    QCustomPlot *waveSignalPlot;
    QCustomPlot *customPlot;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(673, 704);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 651, 641));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        sampleRateLabel = new QLabel(verticalLayoutWidget);
        sampleRateLabel->setObjectName("sampleRateLabel");

        horizontalLayout->addWidget(sampleRateLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        labelTitleWav = new QLabel(verticalLayoutWidget);
        labelTitleWav->setObjectName("labelTitleWav");

        horizontalLayout->addWidget(labelTitleWav);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        openButton = new QPushButton(verticalLayoutWidget);
        openButton->setObjectName("openButton");

        horizontalLayout->addWidget(openButton);

        FFTButton = new QPushButton(verticalLayoutWidget);
        FFTButton->setObjectName("FFTButton");

        horizontalLayout->addWidget(FFTButton);

        inverseFFTButton = new QPushButton(verticalLayoutWidget);
        inverseFFTButton->setObjectName("inverseFFTButton");

        horizontalLayout->addWidget(inverseFFTButton);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        comboBoxOrdreFiltre = new QComboBox(verticalLayoutWidget);
        comboBoxOrdreFiltre->addItem(QString());
        comboBoxOrdreFiltre->addItem(QString());
        comboBoxOrdreFiltre->addItem(QString());
        comboBoxOrdreFiltre->setObjectName("comboBoxOrdreFiltre");

        gridLayout->addWidget(comboBoxOrdreFiltre, 0, 1, 1, 1);

        FiltreButton = new QPushButton(verticalLayoutWidget);
        FiltreButton->setObjectName("FiltreButton");

        gridLayout->addWidget(FiltreButton, 2, 1, 1, 1);

        lineEditFrequenceCoupure = new QLineEdit(verticalLayoutWidget);
        lineEditFrequenceCoupure->setObjectName("lineEditFrequenceCoupure");

        gridLayout->addWidget(lineEditFrequenceCoupure, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        playButton = new QPushButton(verticalLayoutWidget);
        playButton->setObjectName("playButton");

        horizontalLayout_2->addWidget(playButton);

        pauseButton = new QPushButton(verticalLayoutWidget);
        pauseButton->setObjectName("pauseButton");

        horizontalLayout_2->addWidget(pauseButton);

        stopButton = new QPushButton(verticalLayoutWidget);
        stopButton->setObjectName("stopButton");

        horizontalLayout_2->addWidget(stopButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        positionSlider = new QSlider(verticalLayoutWidget);
        positionSlider->setObjectName("positionSlider");
        positionSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_3->addWidget(positionSlider);

        labelDuration = new QLabel(verticalLayoutWidget);
        labelDuration->setObjectName("labelDuration");

        horizontalLayout_3->addWidget(labelDuration);


        verticalLayout_3->addLayout(horizontalLayout_3);

        waveSignalPlot = new QCustomPlot(verticalLayoutWidget);
        waveSignalPlot->setObjectName("waveSignalPlot");

        verticalLayout_3->addWidget(waveSignalPlot);


        verticalLayout_2->addLayout(verticalLayout_3);


        verticalLayout->addLayout(verticalLayout_2);

        customPlot = new QCustomPlot(verticalLayoutWidget);
        customPlot->setObjectName("customPlot");
        customPlot->setEnabled(true);

        verticalLayout->addWidget(customPlot);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 673, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Sample Rate : ", nullptr));
        sampleRateLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        labelTitleWav->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        openButton->setText(QCoreApplication::translate("MainWindow", "Ouvrir", nullptr));
        FFTButton->setText(QCoreApplication::translate("MainWindow", "FFT", nullptr));
        inverseFFTButton->setText(QCoreApplication::translate("MainWindow", "FFT Inverse", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Fr\303\251quance de coupure :", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Ordre du filtre :", nullptr));
        comboBoxOrdreFiltre->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        comboBoxOrdreFiltre->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        comboBoxOrdreFiltre->setItemText(2, QCoreApplication::translate("MainWindow", "3", nullptr));

        FiltreButton->setText(QCoreApplication::translate("MainWindow", "Filtrer", nullptr));
        playButton->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        labelDuration->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
