#ifndef _polycranksaverdlg_h_
#define _polycranksaverdlg_h_

#include <QDialog>
#include <QtGui>
#include "robot.h"
#include "world.h"

class QLabel;
class QLineEdit;
class QCheckBox;

class PolycrankSaverDlg : public QDialog
{
	Q_OBJECT

public:	

    PolycrankSaverDlg (QWidget *parent, World *world);

private slots:
	void saverPositionsClicked();
	void chooseFileClicked();
	void XClicked();

private:
	Robot* tableRobots[2];

	QFile file;
	QTextStream Trajectorystream;

	QCheckBox *saverPositionsCheckBox;
	QCheckBox *chooseFileCheckBox;

	QLabel *dofLabel;
    QLabel *Q0Label;
    QLabel *Q1Label;
    QLabel *Q2Label;
    QLabel *Q3Label;
    QLabel *Q4Label;
    QLabel *Q5Label;
	QLabel *Q6Label;

	QLineEdit *DegreesLineEdit;
    QLineEdit *Q0DegreesLineEdit;
    QLineEdit *Q1DegreesLineEdit;
    QLineEdit *Q2DegreesLineEdit;
    QLineEdit *Q3DegreesLineEdit;
    QLineEdit *Q4DegreesLineEdit;
    QLineEdit *Q5DegreesLineEdit;
	QLineEdit *Q6DegreesLineEdit;

	QLineEdit *RadianLineEdit;
    QLineEdit *Q0RadianLineEdit;
    QLineEdit *Q1RadianLineEdit;
    QLineEdit *Q2RadianLineEdit;
    QLineEdit *Q3RadianLineEdit;
    QLineEdit *Q4RadianLineEdit;
    QLineEdit *Q5RadianLineEdit;
	QLineEdit *Q6RadianLineEdit;
};

#endif