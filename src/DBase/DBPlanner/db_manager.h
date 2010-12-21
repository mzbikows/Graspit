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
// $Id: db_manager.h,v 1.12.2.1 2009/07/23 21:18:06 cmatei Exp $
//
//######################################################################

/*! \file 
  \brief Defines the %DatabaseManager and %FilterType classes.
*/

#ifndef DB_PLANNER_DB_MANAGER_H
#define DB_PLANNER_DB_MANAGER_H

#include <string>
#include <vector>
#include <utility>
#include "model.h"
#include "grasp.h"
using std::pair;
using std::string;
using std::vector;

namespace db_planner {

//! FilterList maps an enum of named filters for filtering a list of Models
//! to a SQL "WHERE" clause that can be tacked onto a query.
class FilterList{
public:
  //! The list of available filters.
	enum FilterType{NONE, HAS_HUMAN_GRASPS, HAS_HUMAN_REFINED_GRASPS};
  //! Maps a FilterType enum to a SQL "WHERE" clause.
	static string GetWhereClause(FilterType filter) {
		if (filter == HAS_HUMAN_GRASPS) {
			return "WHERE model_name IN (SELECT DISTINCT scaled_model_name "
				   "FROM grasp JOIN scaled_model USING(scaled_model_id) "
				   "WHERE grasp_source_id = 2)";
		} else if (filter == HAS_HUMAN_REFINED_GRASPS) {
			return "WHERE model_name IN (SELECT DISTINCT scaled_model_name "
				   "FROM grasp JOIN scaled_model USING(scaled_model_id) "
				   "WHERE grasp_source_id = 3)";
		} else {
			return "";
		}
	}
};


//! Pure virtual base class for interfacing GraspIt with an unspecified Grasp Database.
class DatabaseManager {
 public:
  //! Returns true if the manager has successfully connected to the database
  virtual bool isConnected() const = 0;
  //! Get the 4x4 alignment for 2 Models that are both in the database.
  /*! Returns false if either Model isn't in the database or if no alignment is found.
      Transforms are left-multiply and column major. */
  virtual bool GetAlignment(const Model& source,
                            const Model& dest, 
                            const string& alignment_method_name, 
                            float alignment[16]) const = 0;
  //! Save a 4x4 alignment into the database.
  /*! Transforms are left-multiply and column major. */
  virtual bool SaveAlignment(const Model& source,
                             const Model& dest, 
                             const string& alignment_method_name, 
                             const float alignment[16]) const = 0;
  //! Get the neighbors for a model from the database. Returns false if no neighbors are found.
  /*! Note that num_neighbors is misleading; this will return up to 2 x num_neighbors models,
      since whenever possible it returns a model at the scale above and below the query model. */
  virtual bool GetNeighbors(const Model& model, 
                            const string& distance_function_name, 
                            const int num_neighbors,
                            vector<pair<Model*, double> >* neighbors) 
                            const = 0;
  //! Save the neighbors for a model into the database.
  virtual bool SaveNeighbors(const Model& model, 
                             const string& distance_function_name, 
                             const vector<pair<Model*, double> >& neighbors) 
                             const = 0;
  //! Get a list of the Grasps for a Model.
  virtual bool GetGrasps(const Model& model, 
                         const string& hand_name, 
					             	 vector<Grasp*>* grasp_list) const = 0;
  //! Save a Model's Grasps into the database.
  virtual bool SaveGrasps(const vector<Grasp*>) const = 0;
  //! Returns a vector with pointers to every Model in the database, possibly filtered.
  virtual bool ModelList(vector<Model*>* model_list, 
						             FilterList::FilterType filter = FilterList::NONE) const = 0;
  //! Returns a vector of strings representing the available grasp sources.
  virtual bool GraspTypeList(vector<string>* type_list) const = 0;
  //! Returns a vector of strings representing the available neighbor distance functions.
  virtual bool DistanceFunctionList(
      vector<string>* distance_function_list) const = 0;
  //! Returns a vector of strings representing the available precomputed alignment methods.
  virtual bool AlignmentMethodList(
      vector<string>* alignment_method_list) const = 0;
};

}
#endif  // DB_PLANNER_DB_MANAGER
