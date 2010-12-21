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
// $Id: graspit_db_model.cpp,v 1.11.2.2 2009/07/29 13:14:43 cmatei Exp $
//
//######################################################################

/*! \file 
  \brief Defines the special %GraspitDBModel class
 */

#include "graspit_db_model.h"

#include <Inventor/nodes/SoScale.h>

#include <string>

#include "mytools.h"
#include "body.h"
#include "world.h"
//#define GRASPITDBG
#include "debug.h"

GraspitDBModel::~GraspitDBModel()
{
	if(mGraspableBody) delete mGraspableBody;
}

int GraspitDBModel::load(World* w)
{
	// delete the previously loaded graspabody
	if(mGraspableBody) delete mGraspableBody;
	// load the body
	mGraspableBody = new GraspableBody(w, ModelName().c_str());
	mGraspableBody->setDBModel(this);
	//material is default
	mGraspableBody->setMaterial(w->getMaterialIdx("wood"));

	//PSB objects have a scale of their own. To get to "graspable size"
	//we manually set a scaling factor for each of them, which is in the
	//database as well. We need to scale the geometry appropriately
	SoScale* scale = new SoScale();
	scale->scaleFactor.setValue(RescaleFactor(), RescaleFactor(), RescaleFactor());
	mGraspableBody->getIVGeomRoot()->addChild(scale);

	//load the geometry itself directly from the PSB file
	int result = mGraspableBody->loadGeometryOFF(QString(GeometryPath().c_str()));
	if (result != SUCCESS) {
		mGeometryLoaded = false;
		DBGA("Failed to load CGDB model from file " << GeometryPath());
		return result;
	}
	mGeometryLoaded = true;
	mGraspableBody->addIVMat();

	//set the dynamic properties. This needs a better solution...
	mGraspableBody->setDefaultDynamicParameters();
	mGraspableBody->setMaxRadius(mGraspableBody->computeDefaultMaxRadius());

	return result;
}
