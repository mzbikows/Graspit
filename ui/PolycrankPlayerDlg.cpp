#include <QtGui>
#include "PolycrankPlayerDlg.h"
#include <iostream>

PolycrankPlayerDlg::PolycrankPlayerDlg(QWidget *parent, World *world) : QDialog(parent)
{  
    Q0Label = new QLabel(tr("Q0"));
    Q1Label = new QLabel(tr("Q1"));
    Q2Label = new QLabel(tr("Q2"));
    Q3Label = new QLabel(tr("Q3"));
    Q4Label = new QLabel(tr("Q4"));
    Q5Label = new QLabel(tr("Q5"));
    Q6Label = new QLabel(tr("Q6"));
	
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

    playerForwardTrajectoryCheckBox = new QCheckBox(tr("&Play Forward Trajectory"));
	playerForwardTrajectoryCheckBox->setEnabled(false);//hide

	chooseFileCheckBox = new QCheckBox(tr("&Open Trajectory File"));
	chooseFileCheckBox->setEnabled(true);//show

	QHBoxLayout *playerForwardTrajectoryLayout = new QHBoxLayout;
    playerForwardTrajectoryLayout->addWidget(playerForwardTrajectoryCheckBox);
	playerForwardTrajectoryLayout->addWidget(chooseFileCheckBox);
	connect(playerForwardTrajectoryCheckBox, SIGNAL(clicked()),this, SLOT(playerForwardTrajectoryClicked()));
	connect(chooseFileCheckBox, SIGNAL(clicked()),this, SLOT(chooseFileClicked()));

	playerBackwardTrajectoryCheckBox = new QCheckBox(tr("&Play Backward Trajectory"));
	playerBackwardTrajectoryCheckBox->setEnabled(false);//hide

	spinBox = new QSpinBox;
	spinBox->setRange(1, 100);
	
	spinBox->setEnabled(true);
    
	slider = new QSlider(Qt::Horizontal);
    slider->setRange(1, 100);
	slider->setEnabled(true);
	    
	freqLabel = new QLabel(tr("Frequency [Hz]"));

	QHBoxLayout *playerBackwardTrajectoryLayout = new QHBoxLayout;
    playerBackwardTrajectoryLayout->addWidget(playerBackwardTrajectoryCheckBox);
	
	playerBackwardTrajectoryLayout->addWidget(spinBox);
	playerBackwardTrajectoryLayout->addWidget(freqLabel);

	connect(playerBackwardTrajectoryCheckBox, SIGNAL(clicked()),this, SLOT(playerBackwardTrajectoryClicked()));
	QObject::connect(spinBox, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
	spinBox->setValue(50);

	QHBoxLayout *sliderLayout = new QHBoxLayout;
	sliderLayout->addWidget(slider);
	QObject::connect(slider, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
	slider->setValue(0);
	slider->setEnabled(false);

	
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
	mainLayout->addLayout(playerForwardTrajectoryLayout);
	mainLayout->addLayout(playerBackwardTrajectoryLayout);
	mainLayout->addLayout(sliderLayout);
	mainLayout->addLayout(TitleLayout);
	mainLayout->addLayout(Q0Layout);
	mainLayout->addLayout(Q1Layout);
	mainLayout->addLayout(Q2Layout);
	mainLayout->addLayout(Q3Layout);
	mainLayout->addLayout(Q4Layout);
	mainLayout->addLayout(Q5Layout);
	mainLayout->addLayout(Q6Layout);

    setLayout(mainLayout);
	setWindowTitle(tr("Play Trajectory"));

	tableRobots[0] = world->robotVec[0];//Polycrank
	//tableRobots[1] = world->robotVec[1];//Hand

	QString name = "PolycrankPlayer";
	tableRobots[0]->setName(name);
	std::cout<<"PolycrankPlayerDlg::PolycrankPlayerDlg() = "<<tableRobots[0]->getName().toStdString()<<"\n";

	QObject::connect(this, SIGNAL(rejected ()), this, SLOT(XClicked()));
}

void PolycrankPlayerDlg::XClicked()
{

	QString name = "Polycrank";
	tableRobots[0]->setName(name);
	std::cout<<"PolycrankPlayerDlg::XClicked() = "<<tableRobots[0]->getName().toStdString()<<"\n";

	timerInterval.stop();
	counter=0;
	
	//std::cout<<"Is open = "<< file.isOpen()<<"\n";
	if(file.isOpen()==1)//free if file was open
	{//it not make a sense free memory for empty tables(empty table = empty file) !!!
		//free memory before
		for (int i = 0; i < lines_counter; i++) 
		{
			free(tab[i]);
		}
		free(tab);
		tab = NULL;

		file.close();//close file with trajectory if it was opened
	}

	QMessageBox::information( this, "Window Play Trajectory was closed", "Window Play Trajectory was closed" );
}

void PolycrankPlayerDlg::playerForwardTrajectoryClicked()
{
	if (!playerForwardTrajectoryCheckBox->isChecked()) 
	{	//STOP Trajectory Movie
		
		timerInterval.stop();
		chooseFileCheckBox->setEnabled(true);
		playerBackwardTrajectoryCheckBox->setEnabled(true); 
	}
	else
	{   //PLAY Trajectory Movie

    	if(counter==lines_counter)
		{
			counter=0;
		}

		chooseFileCheckBox->setEnabled(false); // user can not load new trajectory file during playing other trajectory
		playerBackwardTrajectoryCheckBox->setEnabled(false); //user can not play forward and backward in the same time
		connect(&timerInterval, SIGNAL(timeout()), this, SLOT(renderForward()));
		//timerInterval.start(1 * 20);//set interval in (ms) between sending datagrams
		timerInterval.start(1000.0/spinBox->text().toInt());
	}
}

void PolycrankPlayerDlg::renderForward()
{
	double Qradian[7];
	double Qdegree[7];
	float percent=0;

	//std::cout<<"tempBox = "<<tempBox->text().toInt()<<"\n";
    if(playerForwardTrajectoryCheckBox->isChecked() && counter<lines_counter)
	{
		percent=(counter*100)/(lines_counter-1);
		//std::cout <<"percent = "<< percent <<"\n";
		slider->setValue(percent);
		//std::cout<<"counter = " << counter << "\n";
		for (int i = 0; i < 7; i++)
		{
			Qradian[i]=tab[counter][i];
		}

		for (int i = 0; i < 7; i++)
		{
			Qdegree[i]=(double)(180.0*Qradian[i]/3.14159265359);
		}
		
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
	
		counter++;
	}

	if (counter == lines_counter && playerForwardTrajectoryCheckBox->isChecked()) //END MOVIE
	{	//stop Timer and  reset counter
		timerInterval.stop();
		playerForwardTrajectoryCheckBox->setChecked(false);
		playerBackwardTrajectoryCheckBox->setEnabled(true);
		chooseFileCheckBox->setEnabled(true); 
	}
}

void PolycrankPlayerDlg::playerBackwardTrajectoryClicked()
{
	if (!playerBackwardTrajectoryCheckBox->isChecked()) 
	{	//STOP Trajectory Movie
		
		timerInterval.stop();
		chooseFileCheckBox->setEnabled(true);
		playerForwardTrajectoryCheckBox->setEnabled(true);
	}
	else
	{   //PLAY Trajectory Movie
		
		if(counter==0)
		{
			counter=lines_counter;
		}

		chooseFileCheckBox->setEnabled(false); // user can not load new trajectory file during playing other trajectory
		playerForwardTrajectoryCheckBox->setEnabled(false); //user can not play forward and backward in the same time
		connect(&timerInterval, SIGNAL(timeout()), this, SLOT(renderBackward()));
		//timerInterval.start(1 * 20);//set interval in (ms) between sending datagrams
		timerInterval.start(1000.0/spinBox->text().toInt());
	}
}


void PolycrankPlayerDlg::renderBackward()
{
	double Qradian[7];
	double Qdegree[7];
	float percent=0;
	
    if(playerBackwardTrajectoryCheckBox->isChecked() && counter<=lines_counter)
	{
		percent=(counter*100)/(lines_counter-1);
		//std::cout <<"percent = "<< percent <<"\n";
		slider->setValue(percent);

		counter--;

		//std::cout<<"counter = " << counter << "\n";
		for (int i = 0; i < 7; i++)
		{
			Qradian[i]=tab[counter][i];
		}

		for (int i = 0; i < 7; i++)
		{
			Qdegree[i]=(double)(180.0*Qradian[i]/3.14159265359);
		}

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

	}

	if (counter == 0 && playerBackwardTrajectoryCheckBox->isChecked()) //BEGIN OF MOVIE
	{	//stop Timer and  reset counter
		timerInterval.stop();
		playerBackwardTrajectoryCheckBox->setChecked(false);
		playerForwardTrajectoryCheckBox->setEnabled(true);
		chooseFileCheckBox->setEnabled(true); 
	}
}

void PolycrankPlayerDlg::chooseFileClicked()
{

if (!chooseFileCheckBox->isChecked())
{	//user not choses any file	

	//std::cout<<"Is open = "<< file.isOpen()<<"\n";
	if(file.isOpen()==1)//free if file was open
	{//it not make a sense free memory for empty tables(empty table = empty file) !!!
		//free memory before
		for (int i = 0; i < lines_counter; i++) 
		{
			free(tab[i]);
		}
		free(tab);
		tab = NULL;
	}
	playerForwardTrajectoryCheckBox->setEnabled(false); 
	playerBackwardTrajectoryCheckBox->setEnabled(false); 
	file.close();
}
else
{	//user load Trajectory File

	QString filename = QFileDialog::getOpenFileName( this, tr("Open Trajectory File"), QDir::currentPath(), tr("Trajectory File (*.txt)"), 0, QFileDialog::DontUseNativeDialog  );
	
	//std::cout<<"filename = " << filename.toStdString() << "\n";
	file.setFileName(filename);

	if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
	{
		QMessageBox::information( this, "Could not open the file or ANY file was not choosen", "Could not open the file or any file was not choosen" );
		chooseFileCheckBox->setChecked(false);
		return;
	}
		
	QTextStream stream( &file );
			
	lines_counter=0;

	while( !stream.atEnd() )
	{
		lines_counter++;
		stream.readLine();				
	}

	//std::cout << "lines_counter = " << lines_counter << "\n";
			
	tab = (double **)calloc(lines_counter, sizeof(*tab)); 
    
	for (int i = 0; i < lines_counter; i++) 
	{
		tab[i] = (double*) calloc(7, sizeof(double));
	}

	stream.seek( 0 ); // go to begin of Trejectory file

	for(int i=0;i<lines_counter;i++)
	{
		for(int j=0;j<7;j++) 
		{
			stream>>tab[i][j];
		}
	}
/*
	std::cout << "tab[0]= ";
	for(int j=0;j<7;j++) 
	{
		std::cout << tab[0][j] << " ";
	}
	std::cout << "\n";

	std::cout << "tab[max]= ";
	for(int j=0;j<7;j++) 
	{
		std::cout << tab[lines_counter-1][j] << " ";
	}
	std::cout << "\n";
*/
	counter=0;
	//in the beginning I can only play forward
	playerForwardTrajectoryCheckBox->setEnabled(true);
	playerBackwardTrajectoryCheckBox->setEnabled(false);
	QMessageBox::information( this, "Trajectory file was loaded", "Trajectory file was loaded" );
}

}