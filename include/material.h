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
// $Id: material.h,v 1.3.4.1 2009/07/23 21:17:45 cmatei Exp $
//
//######################################################################

#ifndef MATERIAL_HXX

enum materialT {frictionless, glass, metal, wood,plastic, rubber, stone, invalid};

#define NUM_MATERIAL 8

extern double Cof[NUM_MATERIAL][NUM_MATERIAL];
extern double KineticCof[NUM_MATERIAL][NUM_MATERIAL];
extern char *matNameList[NUM_MATERIAL];

void initCof();
materialT readMaterial(const char *matStr);
void getMaterialStr(materialT mat,char *str);
const char *getMaterialStr(materialT mat);

#define MATERIAL_HXX
#endif

