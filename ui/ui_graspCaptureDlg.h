/********************************************************************************
** Form generated from reading UI file 'graspCaptureDlg.ui'
**
** Created: Sat Dec 25 12:51:09 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRASPCAPTUREDLG_H
#define UI_GRASPCAPTUREDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GraspCaptureDlgUI
{
public:
    QGroupBox *groupBox_2;
    QLabel *recordedGraspsLabel;
    QPushButton *saveToFileButton;
    QPushButton *saveToDBaseButton;
    QPushButton *clearListButton;
    QPushButton *captureButton;
    QPushButton *exitButton;

    void setupUi(QDialog *GraspCaptureDlgUI)
    {
        if (GraspCaptureDlgUI->objectName().isEmpty())
            GraspCaptureDlgUI->setObjectName(QString::fromUtf8("GraspCaptureDlgUI"));
        GraspCaptureDlgUI->resize(240, 181);
        groupBox_2 = new QGroupBox(GraspCaptureDlgUI);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 221, 131));
        recordedGraspsLabel = new QLabel(groupBox_2);
        recordedGraspsLabel->setObjectName(QString::fromUtf8("recordedGraspsLabel"));
        recordedGraspsLabel->setGeometry(QRect(10, 50, 151, 16));
        saveToFileButton = new QPushButton(groupBox_2);
        saveToFileButton->setObjectName(QString::fromUtf8("saveToFileButton"));
        saveToFileButton->setGeometry(QRect(10, 70, 91, 23));
        saveToDBaseButton = new QPushButton(groupBox_2);
        saveToDBaseButton->setObjectName(QString::fromUtf8("saveToDBaseButton"));
        saveToDBaseButton->setGeometry(QRect(120, 70, 91, 23));
        clearListButton = new QPushButton(groupBox_2);
        clearListButton->setObjectName(QString::fromUtf8("clearListButton"));
        clearListButton->setGeometry(QRect(10, 100, 201, 23));
        captureButton = new QPushButton(groupBox_2);
        captureButton->setObjectName(QString::fromUtf8("captureButton"));
        captureButton->setGeometry(QRect(10, 20, 201, 23));
        exitButton = new QPushButton(GraspCaptureDlgUI);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(160, 150, 75, 23));

        retranslateUi(GraspCaptureDlgUI);

        QMetaObject::connectSlotsByName(GraspCaptureDlgUI);
    } // setupUi

    void retranslateUi(QDialog *GraspCaptureDlgUI)
    {
        GraspCaptureDlgUI->setWindowTitle(QApplication::translate("GraspCaptureDlgUI", "Grasp capture", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("GraspCaptureDlgUI", "Recorded grasps", 0, QApplication::UnicodeUTF8));
        recordedGraspsLabel->setText(QApplication::translate("GraspCaptureDlgUI", "Recorded grasps: 0", 0, QApplication::UnicodeUTF8));
        saveToFileButton->setText(QApplication::translate("GraspCaptureDlgUI", "Save to file...", 0, QApplication::UnicodeUTF8));
        saveToDBaseButton->setText(QApplication::translate("GraspCaptureDlgUI", "Save to DBase", 0, QApplication::UnicodeUTF8));
        clearListButton->setText(QApplication::translate("GraspCaptureDlgUI", "Clear list", 0, QApplication::UnicodeUTF8));
        captureButton->setText(QApplication::translate("GraspCaptureDlgUI", "Capture", 0, QApplication::UnicodeUTF8));
        exitButton->setText(QApplication::translate("GraspCaptureDlgUI", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GraspCaptureDlgUI: public Ui_GraspCaptureDlgUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRASPCAPTUREDLG_H
