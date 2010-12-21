/********************************************************************************
** Form generated from reading ui file 'polycrank.ui'
**
** Created: Sun 2. May 00:07:52 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_POLYCRANK_H
#define UI_POLYCRANK_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PolycrankDlg
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacer5;
    QLabel *pixmapLabel1;
    QSpacerItem *spacer4;
    QLabel *versionLabel;
    QLabel *emailLabel;
    QLabel *copyrightLabel;
    QSpacerItem *spacer3;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacer2;
    QPushButton *okButton;
    QSpacerItem *spacer1;

    void setupUi(QDialog *PolycrankDlg)
    {
        if (PolycrankDlg->objectName().isEmpty())
            PolycrankDlg->setObjectName(QString::fromUtf8("PolycrankDlg"));
        PolycrankDlg->resize(375, 250);
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PolycrankDlg->sizePolicy().hasHeightForWidth());
        PolycrankDlg->setSizePolicy(sizePolicy);
        vboxLayout = new QVBoxLayout(PolycrankDlg);
        vboxLayout->setSpacing(6);
        vboxLayout->setMargin(11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacer5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacer5);

        pixmapLabel1 = new QLabel(PolycrankDlg);
        pixmapLabel1->setObjectName(QString::fromUtf8("pixmapLabel1"));
        pixmapLabel1->setPixmap(QPixmap(qPixmapFromMimeSource("polycrank.png")));
        pixmapLabel1->setScaledContents(true);
        pixmapLabel1->setWordWrap(false);

        hboxLayout->addWidget(pixmapLabel1);

        spacer4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacer4);

        vboxLayout->addLayout(hboxLayout);

        emailLabel = new QLabel(PolycrankDlg);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));
QSizePolicy sizePolicy0(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(4));
        //sizePolicy1.setHeightForWidth(emailLabel->sizePolicy().hasHeightForWidth());
        emailLabel->setSizePolicy(sizePolicy0);
        emailLabel->setAlignment(Qt::AlignCenter);
        emailLabel->setWordWrap(false);

        vboxLayout->addWidget(emailLabel);

        versionLabel = new QLabel(PolycrankDlg);
        versionLabel->setObjectName(QString::fromUtf8("versionLabel"));
        QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(4));
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(versionLabel->sizePolicy().hasHeightForWidth());
        versionLabel->setSizePolicy(sizePolicy1);
        versionLabel->setAlignment(Qt::AlignCenter);
        versionLabel->setWordWrap(false);

        vboxLayout->addWidget(versionLabel);

        copyrightLabel = new QLabel(PolycrankDlg);
        copyrightLabel->setObjectName(QString::fromUtf8("copyrightLabel"));
        sizePolicy1.setHeightForWidth(copyrightLabel->sizePolicy().hasHeightForWidth());
        copyrightLabel->setSizePolicy(sizePolicy1);
        copyrightLabel->setAlignment(Qt::AlignCenter);
        copyrightLabel->setWordWrap(false);

        vboxLayout->addWidget(copyrightLabel);

        spacer3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacer3);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacer2);

        okButton = new QPushButton(PolycrankDlg);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setDefault(true);

        hboxLayout1->addWidget(okButton);

        spacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacer1);


        vboxLayout->addLayout(hboxLayout1);


        retranslateUi(PolycrankDlg);
        QObject::connect(okButton, SIGNAL(clicked()), PolycrankDlg, SLOT(accept()));

        QMetaObject::connectSlotsByName(PolycrankDlg);
    } // setupUi

    void retranslateUi(QDialog *PolycrankDlg)
    {
        PolycrankDlg->setWindowTitle(QApplication::translate("PolycrankDlg", "Polycrank in GraspIt!", 0, QApplication::UnicodeUTF8));
        versionLabel->setText(QApplication::translate("PolycrankDlg", "Version ", 0, QApplication::UnicodeUTF8));
		emailLabel->setText(QApplication::translate("PolycrankDlg", "Version ", 0, QApplication::UnicodeUTF8));
        copyrightLabel->setText(QApplication::translate("PolycrankDlg", "Copyright (C) 2010 Warsaw University of Technology.  All rights reserved.", 0, QApplication::UnicodeUTF8));
		okButton->setText(QApplication::translate("PolycrankDlg", "OK", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(PolycrankDlg);
    } // retranslateUi
};

namespace Ui {
    class PolycrankDlg: public Ui_PolycrankDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLYCRANK_H
