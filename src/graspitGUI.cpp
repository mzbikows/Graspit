//######################################################################
//
// GraspIt!
// Copyright (C) 2002-2009  Columbia University in the City of New York.
// All rights reserved.
//
// GraspIt! is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// GraspIt! is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with GraspIt!.  If not, see <http://www.gnu.org/licenses/>.
//
// Author(s): Andrew T. Miller 
//
// $Id: graspitGUI.cpp,v 1.13.2.1 2009/07/23 21:18:01 cmatei Exp $
//
//######################################################################

/*! \file
  \brief Implements the graspit user interface.  Responsible for creating both MainWindow and IVmgr.
*/

#include <QString>
#include <Q3GroupBox>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <QLayout>

#ifdef Q_WS_X11
  #include <unistd.h>
#endif

#include "graspitGUI.h"
#include "mainWindow.h"
#include "ivmgr.h"
#include "world.h"
#include "mytools.h"
#include "SoComplexShape.h"
#include "SoArrow.h"
#include "SoTorquePointer.h"

bool GraspItGUI::initialized = false;
int GraspItGUI::initResult = SUCCESS;

// Used by getopt in ProcessArgs
extern int optind,optopt,opterr;
extern char *optarg;

////////////////////////// SYSTEM WIDE GLOBALS ///////////////////////////////

#ifdef GRASPITDBG
FILE *debugfile;
#endif

//! This is the system wide pointer to the graspit user interface.
GraspItGUI *graspItGUI = 0;

//////////////////////////////////////////////////////////////////////////////

/*!
  If this class hasn't been initialized in another instance, it performs
  the following operations:
  - creates a new MainWindow,
  - starts Coin by initializing SoQt,
  - initializes our Coin add on classes,
  - creates a new IVmgr,
  - sets the focus policy of the SoQt viewer so keyboard events are accepted
  - calls a method to process the command line arguments.
 */
GraspItGUI::GraspItGUI(int argc,char **argv)
{
  if (!initialized) {
	mainWindow = new MainWindow; 
    SoQt::init(mainWindow->mWindow);

    // initialize my Inventor additions
    SoComplexShape::initClass();
    SoArrow::initClass();
    SoTorquePointer::initClass();

    ivmgr = new IVmgr((QWidget *)mainWindow->mUI->viewerHolder,"myivmgr");
	
//	mainWindow->viewerHolder->setFocusProxy(ivmgr->getViewer()->getWidget());
//	mainWindow->viewerHolder->setFocusPolicy(QWidget::StrongFocus);
    
	ivmgr->getViewer()->getWidget()->setFocusPolicy(Qt::StrongFocus);

	initialized = true;
    graspItGUI = this;
    initResult = processArgs(argc,argv);
  }
}

/*!
  Deletes both the IVmgr and the MainWindow.
*/
GraspItGUI::~GraspItGUI()
{
  //originally, ivmgr is first
//	fprintf(stderr,"Delete children\n");
//  mainWindow->destroyChildren();
//  fprintf(stderr,"Delete ivmgr\n");
  delete ivmgr;
  delete mainWindow;
}

/*!
  Processes the command line arguments.  It first checks to make sure the
  GRASPIT environment variable is set, then if this is run under X11 it
  examines the command line.  The usage is the following:
\p graspit \p [-w worldname] \p [-r robotname] \p [-o objectname]
\p [-b obstaclename]
*/
int
GraspItGUI::processArgs(int argc, char** argv)
{
  QString filename;
  int errflag=0; (void*)&errflag;
  QString graspitRoot = QString(getenv("GRASPIT"));
  if (graspitRoot.isNull() ) {
    std::cerr << "Please set the GRASPIT environment variable to the root directory of graspIt." << std::endl;
    initResult = FAILURE;
    return FAILURE;
  }
 
#ifdef Q_WS_X11
  char c;
  while((c=getopt(argc, argv, "r:w:o:b:")) != EOF) {
    switch(c) {
    case 'r':
      filename = graspitRoot + QString("/models/robots/")+
	QString(optarg) + QString("/") + QString(optarg) + QString(".cfg");
      if (ivmgr->getWorld()->importRobot(filename)==NULL)
	++errflag;
      break;
    case 'w':
      filename = graspitRoot + QString("/worlds/")+ QString(optarg) +
	QString(".wld");
      if (ivmgr->getWorld()->load(filename)==FAILURE)
	++errflag;
      else
	mainWindow->mUI->worldBox->setTitle(filename);
      break;
    case 'o':
      filename = graspitRoot + QString("/models/objects/")+ QString(optarg) +
	QString(".iv");
      if (!ivmgr->getWorld()->importBody("GraspableBody",filename))
	++errflag;
      break;
    case 'b':
      filename = graspitRoot + QString("/models/obstacles/")+ QString(optarg) +
	QString(".iv");
      if (!ivmgr->getWorld()->importBody("Body",filename))
	++errflag;
      break;
    default: 
      ++errflag;
      break;
    }
  }
  if (errflag) {
    std::cerr << "Usage: graspit [-w worldname] [-r robotname] [-o objectname] [-b obstaclename]" << std::endl;
    return FAILURE;
  }
#endif
  return SUCCESS;
}

/*!
  Shows the mainWindow, sets its size, and starts the Qt event loop.
*/
void
GraspItGUI::startMainLoop()
{	
  SoQt::show(mainWindow->mWindow);
  mainWindow->setMainWorld(ivmgr->getWorld());
  mainWindow->mWindow->resize(QSize(1070,937));  
  SoQt::mainLoop();
}  

/*!
  Exits the Qt event loop.
*/
void
GraspItGUI::exitMainLoop()
{
  SoQt::exitMainLoop();
}

bool
GraspItGUI::terminalFailure() const
{
	return initResult == TERMINAL_FAILURE;
}
