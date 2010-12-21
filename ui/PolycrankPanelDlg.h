#ifndef _polycrankpaneldlg_h_
#define _polycrankpaneldlg_h_

#include <QDialog>
#include <QtGui>
#include <QUdpSocket>
#include <QTimer>
#include "robot.h"
#include "world.h"

class QProgressBar;
class QLabel;
class QLineEdit;
class QCheckBox;
class QSlider;

class PolycrankPanelDlg : public QDialog
{
	Q_OBJECT

public:	

    PolycrankPanelDlg (QWidget *parent, World *world);

private slots:
	void sendDatagram();
    void receiveDatagram();	
	void edpClicked();
	void saveClicked();
	void XClicked();

private:
	Robot* tableRobots[2];

	QUdpSocket udpSocket;
	int	not_synchronised_counter;
	int	failed_counter;
	
	QFile file;
	QTextStream Trajectorystream;

	QTimer timerInterval; //timer for sending & receiving

	QProgressBar *progressBar;
	QCheckBox *edpCheckBox;
	QCheckBox *saveCheckBox;
	QSpinBox *spinBox;
	QSlider *slider;

	QLabel *IPLabel;
    QLineEdit *IPLineEdit;
	QLabel *PortLabel;
    QLineEdit *PortLineEdit;
	QLabel *freqLabel;

	QLabel *syncLabel;
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
