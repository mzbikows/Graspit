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
// Author(s):  Corey Goldfeder
//
// $Id: sql_database_manager.h,v 1.12.2.1 2009/07/23 21:18:06 cmatei Exp $
//
//######################################################################

/*! \file 
    \brief Defines %SqlDatabaseManager class.
 */

#ifndef DB_PLANNER_SQL_DATABASE_MANAGER_H
#define DB_PLANNER_SQL_DATABASE_MANAGER_H

#include <cstdlib>
#include <string>
#include <vector>
#include "database.h"
#include "db_manager.h"
using std::string;
using std::vector;

namespace db_planner {

//! SqlDatabaseManager implements DatabaseManager for using the Postgresql version of the CGDB.
class SqlDatabaseManager : public DatabaseManager {
 private:
  //! The connection to the SQL database
  mutable DatabaseConnection database_;
  //! An object to allocate new Model's/
  /*! These will be derived Model types, but we will only know them as Model*'s.*/
  ModelAllocator *model_allocator_;
  //! An object to allocate new Grasp's/
  /*! These will be derived Grasp types, but we will only know them as Grasp*'s.*/
  GraspAllocator *grasp_allocator_;
  //! Absolute path to the root directory where geometry and thumbnails are stored.
  string model_root_;
 public:
  SqlDatabaseManager(const string& host_name,                     
                     const int port,
                     const string& user_name,
                     const string& password,
                     const string& database_name, 
                     ModelAllocator *model_allocator,
                     GraspAllocator *grasp_allocator,
                     const string& connection_type = "QPSQL") 
                        : database_(host_name, 
                                    port, 
                                    user_name, 
                                    password, 
                                    database_name, 
                                    connection_type),
                          model_allocator_(model_allocator),
                          grasp_allocator_(grasp_allocator),
                          model_root_(getenv("CGDB_MODEL_ROOT")) {}
  ~SqlDatabaseManager(){delete model_allocator_; delete grasp_allocator_;}
  //! Returns true if the manager has successfully connected to the database
  virtual bool isConnected() const {return database_.isConnected();}
  //! Get the 4x4 alignment for 2 Models that are both in the database.
  /*! Returns false if either Model isn't in the database or if no alignment is found.
      Transforms are left-multiply and column major. */
  virtual bool GetAlignment(const Model& source,
                            const Model& dest, 
                            const string& alignment_method_name, 
                            float alignment[16]) const;
  //! Save a 4x4 alignment into the database.
  /*! Transforms are left-multiply and column major. */
  virtual bool SaveAlignment(const Model& source,
                             const Model& dest, 
                             const string& alignment_method_name, 
                             const float alignment[16]) const;
  //! Get the neighbors for a model from the database. Returns false if no neighbors are found.
  /*! Note that num_neighbors is misleading; this will return up to 2 x num_neighbors models,
      since whenever possible it returns a model at the scale above and below the query model. */
  virtual bool GetNeighbors(const Model& model, 
                            const string& distance_function_name, 
                            const int num_neighbors,
                            vector<pair<Model*, double> >* neighbors) const;
  //! Save the neighbors for a model into the database.
  virtual bool SaveNeighbors(const Model& model, 
                             const string& distance_function_name, 
                             const vector<pair<Model*, double> >& neighbors) const;
  //! Get a list of the Grasps for a Model.
  virtual bool GetGrasps(const Model& model, 
                         const string& hand_name, 
                         vector<Grasp*>* grasp_list) const;
  //! Save a Model's Grasps into the database.
  virtual bool SaveGrasps(const vector<Grasp*>) const;
  //! Returns a vector with pointers to every Model in the database, possibly filtered.
  virtual bool ModelList(vector<Model*>* model_list, 
						             FilterList::FilterType filter = FilterList::NONE) const;
  //! Returns a vector of strings representing the available grasp sources.
  virtual bool GraspTypeList(vector<string>* type_list) const;
  //! Returns a vector of strings representing the available neighbor distance functions.
  virtual bool DistanceFunctionList(
      vector<string>* distance_function_list) const;
  //! Returns a vector of strings representing the available precomputed alignment methods.
  virtual bool AlignmentMethodList(
      vector<string>* alignment_method_list) const;
};

}  // end namespace db_planne

#endif  // DB_PLANNER_SQL_DATABASE_MANAGER
