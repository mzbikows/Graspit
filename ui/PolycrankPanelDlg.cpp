#include <QUdpSocket>
#include <QtGui>
#include <QtNetwork>
#include "PolycrankPanelDlg.h"

PolycrankPanelDlg::PolycrankPanelDlg(QWidget *parent, World *world) : QDialog(parent)
{  
	syncLabel = new QLabel(tr("Status   MRROC++   Connection"));
    Q0Label = new QLabel(tr("Q1"));
    Q1Label = new QLabel(tr("Q2"));
    Q2Label = new QLabel(tr("Q3"));
    Q3Label = new QLabel(tr("Q4"));
    Q4Label = new QLabel(tr("Q5"));
    Q5Label = new QLabel(tr("Q6"));
    Q6Label = new QLabel(tr("Q7"));
	
	dofLabel = new QLabel(tr("Q  "));

	DegreesLineEdit = new QLineEdit;
	DegreesLineEdit->setText("DEGREES");
	DegreesLineEdit->setEnabled(false);

    Q0DegreesLineEdit = new QLineEdit;
    Q1DegreesLineEdit = new QLineEdit;
    Q2DegreesLineEdit = new QLineEdit;
    Q3DegreesLineEdit = new QLineEdit;
    Q4DegreesLineEdit = new QLineEdit;
    Q5DegreesLineEdit = new QLineEdit;
    Q6DegreesLineEdit = new QLineEdit;

	RadianLineEdit = new QLineEdit;
	RadianLineEdit->setText("RADIAN");
	RadianLineEdit->setEnabled(false);

    Q0RadianLineEdit = new QLineEdit;
    Q1RadianLineEdit = new QLineEdit;
    Q2RadianLineEdit = new QLineEdit;
    Q3RadianLineEdit = new QLineEdit;
    Q4RadianLineEdit = new QLineEdit;
    Q5RadianLineEdit = new QLineEdit;
    Q6RadianLineEdit = new QLineEdit;

    Q0DegreesLineEdit->setReadOnly(true);
    Q1DegreesLineEdit->setReadOnly(true);
    Q2DegreesLineEdit->setReadOnly(true);
    Q3DegreesLineEdit->setReadOnly(true);
    Q4DegreesLineEdit->setReadOnly(true);
    Q5DegreesLineEdit->setReadOnly(true);
	Q6DegreesLineEdit->setReadOnly(true);

    Q0RadianLineEdit->setReadOnly(true);
    Q1RadianLineEdit->setReadOnly(true);
    Q2RadianLineEdit->setReadOnly(true);
    Q3RadianLineEdit->setReadOnly(true);
    Q4RadianLineEdit->setReadOnly(true);
    Q5RadianLineEdit->setReadOnly(true);
	Q6RadianLineEdit->setReadOnly(true);

	progressBar = new QProgressBar();
	progressBar->setTextVisible( false );
	progressBar->setRange( 0, 1 );

	IPLabel = new QLabel(tr("&IP   "));
    IPLineEdit = new QLineEdit;
    IPLabel->setBuddy(IPLineEdit);
	IPLineEdit->setText("192.168.15.129");
	QRegExpValidator *reVal = new QRegExpValidator( QRegExp("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}"), this );
    IPLineEdit->setValidator( reVal );

	PortLabel = new QLabel(tr("&Port"));
    PortLineEdit = new QLineEdit;
    PortLabel->setBuddy(PortLineEdit);
	PortLineEdit->setText("50020");
	QIntValidator *intVal = new QIntValidator( 0, 100000, this );//range of port 0-100.000
	PortLineEdit->setValidator(intVal);

	spinBox = new QSpinBox;
	spinBox->setRange(1, 100);
	
	spinBox->setEnabled(true);
    
	slider = new QSlider(Qt::Horizontal);
    slider->setRange(1, 100);
	slider->setEnabled(true);
	
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
	spinBox->setValue(50);
    
	freqLabel = new QLabel(tr("Frequency [Hz]"));
    QHBoxLayout *freqLayout = new QHBoxLayout;
	freqLayout->addWidget(freqLabel);
	freqLayout->addWidget(slider);
    freqLayout->addWidget(spinBox);

    edpCheckBox = new QCheckBox(tr("&Connect with EDP Polycrank"));
	edpCheckBox->setEnabled(true);//show
	
	saveCheckBox = new QCheckBox(tr("&Save Polycrank Trajectory"));
	saveCheckBox->setEnabled(false);//hide

	QHBoxLayout *edpLayout = new QHBoxLayout;
    edpLayout->addWidget(edpCheckBox);
	edpLayout->addWidget(saveCheckBox);
	connect(edpCheckBox, SIGNAL(clicked()),this, SLOT(edpClicked()));
	connect(saveCheckBox, SIGNAL(clicked()),this, SLOT(saveClicked()));
	
    QHBoxLayout *ipLayout = new QHBoxLayout;
    ipLayout->addWidget(IPLabel);
    ipLayout->addWidget(IPLineEdit);

    QHBoxLayout *portLayout = new QHBoxLayout;
    portLayout->addWidget(PortLabel);
    portLayout->addWidget(PortLineEdit);

	QHBoxLayout *syncLayout = new QHBoxLayout;
	syncLayout->addWidget(syncLabel);
	syncLayout->addWidget(progressBar);

	QHBoxLayout *TitleLayout = new QHBoxLayout;
    TitleLayout->addWidget(dofLabel);
    TitleLayout->addWidget(DegreesLineEdit);
	TitleLayout->addWidget(RadianLineEdit);

	QHBoxLayout *Q0Layout = new QHBoxLayout;
    Q0Layout->addWidget(Q0Label);
    Q0Layout->addWidget(Q0DegreesLineEdit);
	Q0Layout->addWidget(Q0RadianLineEdit);

	QHBoxLayout *Q1Layout = new QHBoxLayout;
	Q1Layout->addWidget(Q1Label);
    Q1Layout->addWidget(Q1DegreesLineEdit);
	Q1Layout->addWidget(Q1RadianLineEdit);

	QHBoxLayout *Q2Layout = new QHBoxLayout;
    Q2Layout->addWidget(Q2Label);
    Q2Layout->addWidget(Q2DegreesLineEdit);
	Q2Layout->addWidget(Q2RadianLineEdit);

	QHBoxLayout *Q3Layout = new QHBoxLayout;
	Q3Layout->addWidget(Q3Label);
    Q3Layout->addWidget(Q3DegreesLineEdit);
	Q3Layout->addWidget(Q3RadianLineEdit);

	QHBoxLayout *Q4Layout = new QHBoxLayout;
    Q4Layout->addWidget(Q4Label);
    Q4Layout->addWidget(Q4DegreesLineEdit);
	Q4Layout->addWidget(Q4RadianLineEdit);

	QHBoxLayout *Q5Layout = new QHBoxLayout;
	Q5Layout->addWidget(Q5Label);
    Q5Layout->addWidget(Q5DegreesLineEdit);
	Q5Layout->addWidget(Q5RadianLineEdit);

	QHBoxLayout *Q6Layout = new QHBoxLayout;
	Q6Layout->addWidget(Q6Label);
    Q6Layout->addWidget(Q6DegreesLineEdit);
	Q6Layout->addWidget(Q6RadianLineEdit);
	
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(ipLayout);
	mainLayout->addLayout(portLayout);
	mainLayout->addLayout(freqLayout);
	mainLayout->addLayout(edpLayout);
	mainLayout->addLayout(syncLayout);
	mainLayout->addLayout(TitleLayout);
	mainLayout->addLayout(Q0Layout);
	mainLayout->addLayout(Q1Layout);
	mainLayout->addLayout(Q2Layout);
	mainLayout->addLayout(Q3Layout);
	mainLayout->addLayout(Q4Layout);
	mainLayout->addLayout(Q5Layout);
	mainLayout->addLayout(Q6Layout);

    setLayout(mainLayout);
	setWindowTitle(tr("Connect with MRROC++"));

	tableRobots[0] = world->robotVec[0];//Polycrank
	//tableRobots[1] = world->robotVec[1];//Hand
	
	QString name = "PolycrankPanel";
	tableRobots[0]->setName(name);
	std::cout<<"PolycrankPanelDlg::PolycrankPanelDlg() = "<<tableRobots[0]->getName().toStdString()<<"\n";

	QObject::connect(this, SIGNAL(rejected ()), this, SLOT(XClicked()));
}

void PolycrankPanelDlg::XClicked()
{
	QString name = "Polycrank";
	tableRobots[0]->setName(name);
	std::cout<<"PolycrankPanelDlg::XClicked() = "<<tableRobots[0]->getName().toStdString()<<"\n";

	//Reset Timers for send & receive
	timerInterval.stop();
	edpCheckBox->setChecked(false);//disconnect with MRROC++ when user suddelny closes the window
	udpSocket.close();//close socket if it was opened

	file.close();//close file with trajectory if it was opened
	QMessageBox::information( this, "Window Connect with MRROC++ was closed", "Window Connect with MRROC++ was closed" );
}

void PolycrankPanelDlg::edpClicked()
{
	if (!edpCheckBox->isChecked())
	{	//edpCheckBox is NOT active (Graspit is NOT connecting with MRROC++)

		IPLineEdit->setEnabled(true);
		PortLineEdit->setEnabled(true);

		slider->setEnabled(true);//user can change frequency
		spinBox->setEnabled(true);//user can change frequency

		//Reset Timer for send & receive
		timerInterval.stop();

		saveCheckBox->setChecked(false); //set button in state :: off

		//saveCheckBox->setChecked(true); //set button in state :: on
		saveCheckBox->setEnabled(false); //user can NOT save trajectory, because connection failed

		udpSocket.close();

		Q0DegreesLineEdit->clear();
		Q1DegreesLineEdit->clear();
		Q2DegreesLineEdit->clear();
		Q3DegreesLineEdit->clear();
		Q4DegreesLineEdit->clear();
		Q5DegreesLineEdit->clear();
		Q6DegreesLineEdit->clear();

		Q0RadianLineEdit->clear();
		Q1RadianLineEdit->clear();
		Q2RadianLineEdit->clear();
		Q3RadianLineEdit->clear();
		Q4RadianLineEdit->clear();
		Q5RadianLineEdit->clear();
		Q6RadianLineEdit->clear();

		progressBar->setRange( 0, 1 );

	
		file.close();//very important, when user suddenly cancel EDP Polycrank
					 //in first step app should close socket
					 //in second step app should close file (descriptor)
					 //when user want to save trajectory again trajectory will be saved in new file
					 //NOT the same file 
	}
	else
	{   //edpCheckBox is active (Graspit is connecting with MRROC++)
/*
		Q0DegreesLineEdit->clear();
		Q1DegreesLineEdit->clear();
		Q2DegreesLineEdit->clear();
		Q3DegreesLineEdit->clear();
		Q4DegreesLineEdit->clear();
		Q5DegreesLineEdit->clear();
		Q6DegreesLineEdit->clear();

		Q0RadianLineEdit->clear();
		Q1RadianLineEdit->clear();
		Q2RadianLineEdit->clear();
		Q3RadianLineEdit->clear();
		Q4RadianLineEdit->clear();
		Q5RadianLineEdit->clear();
		Q6RadianLineEdit->clear();
*/
		Q0DegreesLineEdit->setText("PLEASE WAIT");
		Q1DegreesLineEdit->setText("PLEASE WAIT");
		Q2DegreesLineEdit->setText("PLEASE WAIT");
		Q3DegreesLineEdit->setText("PLEASE WAIT");
		Q4DegreesLineEdit->setText("PLEASE WAIT");
		Q5DegreesLineEdit->setText("PLEASE WAIT");
		Q6DegreesLineEdit->setText("PLEASE WAIT");
	
		Q0RadianLineEdit->setText("PLEASE WAIT");
		Q1RadianLineEdit->setText("PLEASE WAIT");
		Q2RadianLineEdit->setText("PLEASE WAIT");
		Q3RadianLineEdit->setText("PLEASE WAIT");
		Q4RadianLineEdit->setText("PLEASE WAIT");
		Q5RadianLineEdit->setText("PLEASE WAIT");
		Q6RadianLineEdit->setText("PLEASE WAIT");

		progressBar->setRange( 0, 1 );

		not_synchronised_counter=0;
		failed_counter=0;

		IPLineEdit->setEnabled(false);
		PortLineEdit->setEnabled(false);

		slider->setEnabled(false);//user can NOT change frequency during the connection
		spinBox->setEnabled(false);//user can NOT change frequency during the connection
		
		saveCheckBox->setEnabled(true);//user can save trajectory

		//udpSocket.bind(5000);
		udpSocket.bind(PortLineEdit->text().toLong());
		
		connect(&timerInterval, SIGNAL(timeout()), this, SLOT(sendDatagram()));
		//set interval in (ms) between sending datagrams
		timerInterval.start(1000.0/ spinBox->text().toInt());

		connect(&timerInterval, SIGNAL(timeout()), this, SLOT(receiveDatagram()));
		//set interval in (ms) between receiving datagrams
		timerInterval.start(1000.0/ spinBox->text().toInt());
	}
}

void PolycrankPanelDlg::saveClicked()
{
if (!saveCheckBox->isChecked())
{	//user not choses any file	
		QMessageBox::information( this, "Trajectory IS NOT saving NOW", "Trajectory IS NOT saving NOW" );
		file.close();
}
else
{	//user saves polycrank trajectory

	QString filename = QFileDialog::getSaveFileName( this, tr("Save Polycrank Trajectory"), QDir::currentPath(), tr("Trajectory (*.txt)"), 0, QFileDialog::DontUseNativeDialog  );
	
	filename.append(".txt"); 
	filename.replace(QRegExp(".txt.txt"), ".txt");
	
	if (filename ==".txt")
	{//not choose any file to save trajectory file
		
		saveCheckBox->toggle();
		QMessageBox::information( this, "ANY file was choosen to save trajectory", "ANY file was choosen to save trajectory" );
	}
	else
	{
		file.setFileName(filename);
		if (file.open(QIODevice::WriteOnly|QIODevice::Text)) 
		{
			Trajectorystream.setDevice(&file);
			QMessageBox::information( this, "Trajectory IS saving NOW", "Trajectory IS saving NOW" );
		}
	}
}
}

void PolycrankPanelDlg::sendDatagram()
{
	std::cout<<"send datagram"<<std::endl;
	if (edpCheckBox->isChecked())
	{   //edpCheckBox is active (Graspit is connecting with MRROC++)

		//QString ip_polycrank = "127.0.0.1";
		QString ip_polycrank = IPLineEdit->text();
		//QString ip_polycrank = "10.4.33.4";
		//long port = 5000;
		long port = PortLineEdit->text().toLong();
		int sync=1;

		QByteArray datagram;
		QDataStream out(&datagram, QIODevice::WriteOnly);
		out << sync;
		udpSocket.writeDatagram(datagram, QHostAddress(ip_polycrank), port);
	}
}

void PolycrankPanelDlg::receiveDatagram()
{
    QByteArray datagram;
	char bufor[4];
	float current=0.0;
	double Qradian[7];
	double Qdegree[7];

	std::cout<<"receive datagram"<< std::endl;
if (edpCheckBox->isChecked())
{	//edpCheckBox is active (Graspit is connecting with MRROC++)
	
	for (int i=0; i<7; i++)
		Qradian[i]=0.0;

	for (int i=0; i<7; i++)
		Qdegree[i]=0.0;

    do 
	{
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
    } while (udpSocket.hasPendingDatagrams());

	std::cout <<  "COUT   datagram.size() = " << datagram.size() << std::endl;

	if (datagram.size() > 4)
	{

		//Precision, 6 digits after dot
		Trajectorystream.setRealNumberNotation(QTextStream::FixedNotation); 
	
		for (int shiftBuffer=1; shiftBuffer<8; shiftBuffer+=1)
		{
			for(int i=0; i<4; i++)
			{
				bufor[i]=datagram[(shiftBuffer*4)+i];
			}
			memcpy(&current,bufor,4);

			if (current>0.0000000)
			{
				current+=(float)0.0004;
			}
			else
			;
			Qdegree[shiftBuffer-1 ]=(double)(180.0*current/3.14159265359);
			Qradian[shiftBuffer-1 ]=(double)(current);

			if (current>0.0000000)
			{
				Trajectorystream << "+" << current << " ";
			}
			else
			{
				Trajectorystream << current << " ";
			}
		}

		Trajectorystream << endl;

		//UPDATE POLYCRANK JOINTS AND DOF'S
		tableRobots[0]->chainVec[0]->setJointValues(Qradian);
		tableRobots[0]->chainVec[0]->updateLinkPoses();
		tableRobots[0]->updateDOFFromJoints(Qradian);
		
		Q0DegreesLineEdit->setText(tr("%1").arg(Qdegree[0]));
		Q1DegreesLineEdit->setText(tr("%1").arg(Qdegree[1]));
		Q2DegreesLineEdit->setText(tr("%1").arg(Qdegree[2]));
		Q3DegreesLineEdit->setText(tr("%1").arg(Qdegree[3]));
		Q4DegreesLineEdit->setText(tr("%1").arg(Qdegree[4]));
		Q5DegreesLineEdit->setText(tr("%1").arg(Qdegree[5]));
		Q6DegreesLineEdit->setText(tr("%1").arg(Qdegree[6]));

		Q0RadianLineEdit->setText(tr("%1").arg(Qradian[0]));
		Q1RadianLineEdit->setText(tr("%1").arg(Qradian[1]));
		Q2RadianLineEdit->setText(tr("%1").arg(Qradian[2]));
		Q3RadianLineEdit->setText(tr("%1").arg(Qradian[3]));
		Q4RadianLineEdit->setText(tr("%1").arg(Qradian[4]));
		Q5RadianLineEdit->setText(tr("%1").arg(Qradian[5]));
		Q6RadianLineEdit->setText(tr("%1").arg(Qradian[6]));

		progressBar->setRange( 0, 0 );
		
		not_synchronised_counter=0;
		failed_counter=0;
	}
	else if (datagram.size()==4)
	{
		//edpCheckBox is active (Graspit is connecting with MRROC++)
		//size of datagram=4 (one integer) so synchronization=0
		//IS NOT SYNCHRONISED
		not_synchronised_counter++;
		failed_counter=0;
		
		if(not_synchronised_counter>100)
		{
			Q0DegreesLineEdit->setText("IS NOT SYNCHRONISED");
			Q1DegreesLineEdit->setText("IS NOT SYNCHRONISED");
			Q2DegreesLineEdit->setText("IS NOT SYNCHRONISED");
			Q3DegreesLineEdit->setText("IS NOT SYNCHRONISED");
			Q4DegreesLineEdit->setText("IS NOT SYNCHRONISED");
			Q5DegreesLineEdit->setText("IS NOT SYNCHRONISED");
			Q6DegreesLineEdit->setText("IS NOT SYNCHRONISED");
	
			Q0RadianLineEdit->setText("IS NOT SYNCHRONISED");
			Q1RadianLineEdit->setText("IS NOT SYNCHRONISED");
			Q2RadianLineEdit->setText("IS NOT SYNCHRONISED");
			Q3RadianLineEdit->setText("IS NOT SYNCHRONISED");
			Q4RadianLineEdit->setText("IS NOT SYNCHRONISED");
			Q5RadianLineEdit->setText("IS NOT SYNCHRONISED");
			Q6RadianLineEdit->setText("IS NOT SYNCHRONISED");
			progressBar->setRange( 0, 1 );

			edpCheckBox->setChecked(false);//disconnect with MRROC++ when user suddelny closes the window
			IPLineEdit->setEnabled(true);
			PortLineEdit->setEnabled(true);

			slider->setEnabled(true);//user can change frequency
			spinBox->setEnabled(true);//user can change frequency

			//Reset Timer for send & receive
			timerInterval.stop();

			saveCheckBox->setChecked(false); //set button in state :: off

			//saveCheckBox->setChecked(true); //set button in state :: on
			saveCheckBox->setEnabled(false); //user can NOT save trajectory, because connection failed
		}
	}
	else
	{   
		//edpCheckBox is active (Graspit is connecting with MRROC++)
		//size od datagram = 0 (empty datagram)
		failed_counter++;
		not_synchronised_counter=0;
		
		if(failed_counter>100)
		{
			Q0DegreesLineEdit->setText("Polycrank EDP failed");
			Q1DegreesLineEdit->setText("Polycrank EDP failed");
			Q2DegreesLineEdit->setText("Polycrank EDP failed");
			Q3DegreesLineEdit->setText("Polycrank EDP failed");
			Q4DegreesLineEdit->setText("Polycrank EDP failed");
			Q5DegreesLineEdit->setText("Polycrank EDP failed");
			Q6DegreesLineEdit->setText("Polycrank EDP failed");
	
			Q0RadianLineEdit->setText("Polycrank EDP failed");
			Q1RadianLineEdit->setText("Polycrank EDP failed");
			Q2RadianLineEdit->setText("Polycrank EDP failed");
			Q3RadianLineEdit->setText("Polycrank EDP failed");
			Q4RadianLineEdit->setText("Polycrank EDP failed");
			Q5RadianLineEdit->setText("Polycrank EDP failed");
			Q6RadianLineEdit->setText("Polycrank EDP failed");
			progressBar->setRange( 0, 1 );

			edpCheckBox->setChecked(false);//disconnect with MRROC++ when user suddelny closes the window
			IPLineEdit->setEnabled(true);
			PortLineEdit->setEnabled(true);

			slider->setEnabled(true);//user can change frequency
			spinBox->setEnabled(true);//user can change frequency

			//Reset Timers for send & receive
			timerInterval.stop();

			saveCheckBox->setChecked(false); //set button in state :: off

			//saveCheckBox->setChecked(true); //set button in state :: on
			saveCheckBox->setEnabled(false); //user can NOT save trajectory, because connection failed
		}	
	}
}

}
