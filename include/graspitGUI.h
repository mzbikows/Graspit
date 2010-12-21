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
// Author(s):  Andrew T. Miller 
//
// $Id: graspitGUI.h,v 1.3.4.1 2009/07/23 21:17:42 cmatei Exp $
//
//######################################################################

/*! \file 
  \brief Defines a graspit user interface class that contains subpieces of the UI.
*/

#ifndef GRASPITGUI_HXX
class MainWindow;
class IVmgr;

//! This is the main user interface class that is responsible for creating and destroying the MainWindow and IVmgr.
/*!
  This class also processes command line arguments and holds pointers to both
  the MainWindow and IVmgr.  There is one global instance of this class, which
  allows access to these two main pieces of the UI.  This class also has
  methods for both the entry and exit to the interactive program loop.
*/
class GraspItGUI
{
  //! A pointer to the MainWindow.
  MainWindow *mainWindow;

  //! A pointer to the IVmgr.
  IVmgr *ivmgr;

  //! TRUE if this class has been initialized.
  static bool initialized;

  //! Holds result of UI initialization.
  static int initResult;
  
 protected:
  int processArgs(int argc, char **argv);

 public:
  GraspItGUI(int argc,char **argv);
  ~GraspItGUI();

  /*! Returns whether the UI pieces were successfully initialized. */
  bool terminalFailure() const;

  /*! Returns a pointer to the MainWindow. */
  MainWindow *getMainWindow() const {return mainWindow;}

  /*! Returns a pointer to the IVmgr. */
  IVmgr *getIVmgr() const {return ivmgr;}
  
  void startMainLoop();
  void exitMainLoop();
};

extern GraspItGUI *graspItGUI;

#define GRASPITGUI_HXX
#endif
