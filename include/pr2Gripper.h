//######################################################################
//
// GraspIt!
// Copyright (C) 2002-2008  Columbia University in the City of New York.
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
// Author(s):  Matei Ciocarlie (cmatei@cs.columbia.edu)
//
// $Id: 
//
//######################################################################

/*! \file 
  \brief Defines the special %Pr2Gripper class
 */

#ifndef PR2GRIPPER_H

#include "robot.h"

//! A special hand because collisions must be turned off between the first links of the two chains
/*! A special hand because collisions must be turned off between the
    first links of the two chains.  This is done by overriding the
    load method.
 */
class Pr2Gripper : public Hand {
	Q_OBJECT

 public:

  /*! Empty constructor (placeholder) */
  Pr2Gripper(World *w,const char *name) : Hand(w,name) {}
  
   /*! Performs the normal robot load routine from xml then turns off collisions 
       between the first links of the two chains
 */
  virtual int loadFromXml(const TiXmlElement* root,QString rootPath);

 /*! Performs the normal robot clone routine then turns off collisions between
     the first links of the two chains
 */
  virtual void cloneFrom(Hand *original);

};

#define PR2GRIPPER_H
#endif
