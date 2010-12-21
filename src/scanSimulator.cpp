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
// Author(s): Matei T. Ciocarlie
//
// $Id: scanSimulator.cpp,v 1.4.4.1 2009/07/23 21:18:03 cmatei Exp $
//
//######################################################################

#include <assert.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/SoPickedPoint.h>

#include "scanSimulator.h"
#include "graspitGUI.h"
#include "ivmgr.h"
#include "world.h"

ScanSimulator::ScanSimulator()
{
	mPosition = position(0,0,0);
	mDirection = vec3(1,0,0);
	mUp = vec3(0,0,1);
	mHorizDirection = vec3(0,1,0);
	mHMin = -70; mHMax = 70; mHLines = 140;
	mVMin = -30; mVMax = 30; mVLines = 60;
	mType = SCANNER_COORDINATES;
	computeTransform();
}

void ScanSimulator::computeTransform()
{
	//compute the transform so that z is "up" and x in in the scanning direction
	mTran = transf( mat3(mDirection, mHorizDirection, mUp),
			vec3(mPosition.x(), mPosition.y(), mPosition.z() ) );
	mTranInv = mTran.inverse();

}

void ScanSimulator::setPosition(position p, vec3 v, vec3 u)
{
	mPosition = p; mDirection = normalise(v); mUp = normalise(u);
	mHorizDirection = normalise(mUp * mDirection); 
	mUp = mDirection * mHorizDirection;
	//fprintf(stderr,"HORIZ: %f %f %f\n", mHorizDirection.x(), mHorizDirection.y(), mHorizDirection.z());
	//fprintf(stderr,"UP: %f %f %f\n",mUp.x(), mUp.y(), mUp.z());
	computeTransform();
}

void ScanSimulator::scan(std::vector<position> *cloud, std::vector<RawScanPoint> *rawData)
{
	float hfov = (mHMax - mHMin) * M_PI / 180.0;
	float vfov = (mVMax - mVMin) * M_PI / 180.0;

	assert(hfov>=0 && vfov>=0);
	assert( mHLines > 0 && mVLines > 0);

	float hstep = hfov / mHLines;
	float vstep = vfov / mVLines;

	fprintf(stderr,"Vfov %f and vstep %f and lines %d\n",vfov,vstep,mVLines);

	float hAngle;
	float vAngle = - vfov / 2.0;

	vec3 rayDirection;
	position rayPoint;
	RawScanPoint rawPoint;

	while( vAngle < vfov / 2.0) {
		hAngle = - hfov / 2.0;
		while (hAngle < hfov / 2.0) {
			
			computeRayDirection( hAngle, vAngle, rayDirection);
			rawPoint.hAngle = hAngle; rawPoint.vAngle = vAngle;
			rawPoint.dx = rayDirection.x();
			rawPoint.dy = rayDirection.y();
			rawPoint.dz = rayDirection.z();

			if ( shootRay( rayDirection, rayPoint ) ) {
				vec3 dist = rayPoint - mPosition;
				rawPoint.distance = dist.len();

				//we get the point in world coordinates
				if (mType == SCANNER_COORDINATES) {
					rayPoint = rayPoint * mTranInv;;
				}
				cloud->push_back(rayPoint);


			} else {
				rawPoint.distance = -1;
			}
			
			if (rawData) {
				rawData->push_back( rawPoint );
			}

			hAngle += hstep;
		}
		vAngle += vstep;
		fprintf(stderr,"Vangle: %f\n",vAngle);
	}
}

void ScanSimulator::computeRayDirection(float hAngle, float vAngle, vec3 &rayDirection)
{
	Quaternion r1(vAngle, mHorizDirection );
	Quaternion r2(hAngle, r1 * mUp);
	rayDirection = r2 * r1 * mDirection;
}

bool ScanSimulator::shootRay(const vec3 &rayDirection, position &rayPoint)
{
	SoRayPickAction action( graspItGUI->getIVmgr()->getViewer()->getViewportRegion() );

	action.setRay( mPosition.toSbVec3f(), rayDirection.toSbVec3f(), 0.0, -1.0 );
	action.setPickAll(false);

	action.apply( (SoNode*)graspItGUI->getIVmgr()->getWorld()->getIVRoot() );

	SoPickedPoint *pp = action.getPickedPoint();
	if (!pp) return false;

	rayPoint = position( pp->getPoint() );
	return true;
}

