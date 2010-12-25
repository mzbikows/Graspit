//Author  : Mariusz Żbikowski
//Project : Simulation Polycrank 
#include <QtGui>
#include "PolycrankSaverDlg.h"

PolycrankSaverDlg::PolycrankSaverDlg(QWidget *parent, World *world) : QDialog(parent)
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

    saverPositionsCheckBox = new QCheckBox(tr("&Save interpolation positions"));
	saverPositionsCheckBox->setEnabled(false);//hide
	
	chooseFileCheckBox = new QCheckBox(tr("&Choose file to save interpolation positions"));
	chooseFileCheckBox->setEnabled(true);//show

	QHBoxLayout *saverPositionsLayout = new QHBoxLayout;
    saverPositionsLayout->addWidget(saverPositionsCheckBox);
	saverPositionsLayout->addWidget(chooseFileCheckBox);
	connect(saverPositionsCheckBox, SIGNAL(clicked()),this, SLOT(saverPositionsClicked()));
	connect(chooseFileCheckBox, SIGNAL(clicked()),this, SLOT(chooseFileClicked()));

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
	mainLayout->addLayout(saverPositionsLayout);
	mainLayout->addLayout(TitleLayout);
	mainLayout->addLayout(Q0Layout);
	mainLayout->addLayout(Q1Layout);
	mainLayout->addLayout(Q2Layout);
	mainLayout->addLayout(Q3Layout);
	mainLayout->addLayout(Q4Layout);
	mainLayout->addLayout(Q5Layout);
	mainLayout->addLayout(Q6Layout);

    setLayout(mainLayout);
	setWindowTitle(tr("Save Interpolation Positions"));

	tableRobots[0] = world->robotVec[0];//Polycrank
	//tableRobots[1] = world->robotVec[1];//Hand

	QString name = "PolycrankSaver";
	tableRobots[0]->setName(name);
	std::cout<<"PolycrankSaverDlg::PolycrankSaverDlg() = "<<tableRobots[0]->getName().toStdString()<<"\n";
	
	QObject::connect(this, SIGNAL(rejected ()), this, SLOT(XClicked()));
}

void PolycrankSaverDlg::XClicked()
{
	QString name = "Polycrank";
	tableRobots[0]->setName(name);
	std::cout<<"PolycrankSaverDlg::XClicked() = "<<tableRobots[0]->getName().toStdString()<<"\n";

	file.close();//close file with trajectory if it was opened
	QMessageBox::information( this, "Window Save Interpolation Positions was closed", "Window Save Interpolation Positions was closed" );
}

void PolycrankSaverDlg::saverPositionsClicked()
{
	double Qradian[7];
	double Qdegree[7];

	if (!saverPositionsCheckBox->isChecked())
	{	//not save interpolation positions
		
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

	}
	else
	{   //show interpolation positions

		for (int i = 0; i < 7; i++)
		{
			tableRobots[0]->chainVec[0]->getJointValues(Qradian);
		}

		for (int i = 0; i < 7; i++)
		{
			Qdegree[i]=(double)(180.0*Qradian[i]/3.14159265359);
			Trajectorystream << Qradian[i] << " ";
		}
		Trajectorystream << endl;
		
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
		
		saverPositionsCheckBox->setChecked(false);
		QMessageBox::information( this, "Current interpolation positions was saved", "Current interpolation positions was saved" );
	}
}

void PolycrankSaverDlg::chooseFileClicked()
{

if (!chooseFileCheckBox->isChecked())
{	//user not choses any file	
	saverPositionsCheckBox->setEnabled(false); //user can NOT save interpolation positions, because file was not choosen	
	file.close();
}
else
{	//user saves polycrank trajectory

	QString filename = QFileDialog::getSaveFileName( this, tr("Save Interpolation Positions"), QDir::currentPath(), tr("Interpolation Positions (*.txt)"), 0, QFileDialog::DontUseNativeDialog  );
	
	filename.append(".txt"); 
	filename.replace(QRegExp(".txt.txt"), ".txt");

	if (filename ==".txt")
	{//not choose any file to save trajectory file
		
		chooseFileCheckBox->toggle();
		QMessageBox::information( this, "ANY file was choosen to save interpolation positions", "ANY file was choosen to save interpolation positions" );
	}
	else
	{
		file.setFileName(filename);
		if (file.open(QIODevice::WriteOnly|QIODevice::Text)) 
		{
			Trajectorystream.setDevice(&file);
			QMessageBox::information( this, "File to save interpolation positions was choosen", "File to save interpolation positions was choosen" );
		}
		saverPositionsCheckBox->setEnabled(true);
	}
}
}
