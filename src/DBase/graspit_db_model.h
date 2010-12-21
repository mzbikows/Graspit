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
// Author(s):  Hao Dang and Matei T. Ciocarlie
//
// $Id: graspit_db_model.h,v 1.7.2.1 2009/07/23 21:18:05 cmatei Exp $
//
//######################################################################

/*! \file 
  \brief Defines the special %GraspitDBModel class
 */

#ifndef _GRASPIT_DB_MODEL_ENTRY_H_
#define _GRASPIT_DB_MODEL_ENTRY_H_

#include <QString>

#include "DBPlanner/model.h"

class World;
class GraspableBody;

/*! This is the class to define the data entry of model in CGDB
*/
class GraspitDBModel : public db_planner::Model{
private:
	//! Tells us if the scene graph geometry of this object has been loaded
	bool mGeometryLoaded;
	//! This is the body representation in GraspIt
	GraspableBody* mGraspableBody;
public:
	GraspitDBModel() : mGraspableBody(NULL), mGeometryLoaded(false){}
	~GraspitDBModel();
	//! Calls the super and also sets the mGeometryLoaded flag
	int load(World* w);
	//! Returns the flag that tells us if geometry has been loaded
	bool geometryLoaded() const {return mGeometryLoaded;}
	//! Returns the Graspable body
	GraspableBody* getGraspableBody() const { return mGraspableBody; }
};

//! An implementation of ModelAllocator that returns new GraspitDBModel objects.
class GraspitDBModelAllocator : public db_planner::ModelAllocator
{
public:
	GraspitDBModelAllocator(){}
	db_planner::Model* Get() const {
		return new GraspitDBModel();
	}
};

#endif