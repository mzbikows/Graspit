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
// Author(s): Norases (Saint) Vesdapunt
//
// $Id: xmlconverter.h,v 1.2.2.1 2009/07/23 21:18:13 cmatei Exp $
//
//######################################################################

#include <QString>
#include <QTextStream>
#include <iostream>

#define SUCCESS 0
#define FAILURE -1
#define M_PI 3.14159265358979323846
#define DBGA(STMT) std::cerr<<STMT<<std::endl;

//! Finds the next line in a stream that is not blank or a comment
int nextValidLine(QTextStream *stream, QString *line);

//! Finds the next line that is an Inventor comment (starts with a #)
int nextCommentLine(QTextStream *stream, QString *line);

//! Finds a keyword on a line in a stream and positions the stream after it
int findString(QTextStream *stream, QString target);

int convertCfg2Xml(QString filename);
int convertWld2Xml(QString filename);
int convertObj2Xml(QString filename);

int convertTransform(QTextStream &stream,QString& xml);
