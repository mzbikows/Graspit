# list of core source files for GraspIt!
# included in both graspit-WINDOWS.pro and graspit-LINUX.pro 
# not for stand-alone use. 

#----------------------general settings--------------------

QT +=  qt3support 

CONFIG += qt warn_on exceptions assistant

INCLUDEPATH += $(QTDIR)/include $(COINDIR)/include qhull

DESTDIR = bin

UI_DIR = ui

# ---------------------- Graspit source code ----------------------------------------------

INCLUDEPATH += src src/Collision include include/math include/Planner include/EGPlanner ui ui/Planner ui/EGPlanner

DEPENDPATH += src src/Collision include include/math include/Planner include/EGPlanner ui ui/Planner ui/EGPlanner

HEADERS	+= include/barrett.h \
	include/body.h \
	include/bbox.h \
	include/bbox_inl.h \
	include/contact.h \
	include/contactSetting.h \
	include/debug.h \
	include/dof.h \
	include/dynamics.h \
	include/eigenGrasp.h \
	include/gloveInterface.h \
	include/grasp.h \
	include/graspRecord.h \
	include/gws.h \
	include/gwsprojection.h \
	include/ivmgr.h \
	include/jacobian.h \
	include/joint.h \
	include/kinematicChain.h \
	include/lmiOptimizer.h \
	include/material.h \
	include/matvec3D.h \
	include/matvecIO.h \
	include/maxdet.h \
	include/mcGrip.h \
	include/mytools.h \
	include/profiling.h \
	include/puma560.h \
	include/qhull_mutex.h \
	include/quality.h \
	include/pr2Gripper.h \
	include/m7.h \
	include/m7tool.h \
	include/robonaut.h \
	include/robot.h \
	include/humanHand.h \
	include/SoArrow.h \
	include/SoComplexShape.h \
	include/SoTorquePointer.h \
	include/scanSimulator.h \
	include/triangle_inl.h \
	include/triangle.h \
	include/worldElement.h \
	include/world.h \
	include/graspitGUI.h \
	include/graspitServer.h \
	include/graspitApp.h \
	include/dynJoint.h \
	include/arch.h \
	include/math/matrix.h \
	src/Collision\collisionInterface.h \
	src/Collision\collisionStructures.h \
	include/Planner/grasp_visualization.h \
	include/Planner/grasp_tester.h \
	include/Planner/grasp_preshape.h \
	include/Planner/grasp_presenter.h \
	include/Planner/grasp_planner.h \
	include/Planner/grasp_manager.h \
	include/Planner/grasp_grasps.h \
	include/Planner/grasp_directions.h \
	include/Planner/grasp_coordinates.h \
	include/EGPlanner/search.h \
	include/EGPlanner/simAnn.h \
	include/EGPlanner/searchState.h \
	include/EGPlanner/searchStateImpl.h \
	include/EGPlanner/searchEnergy.h \
	include/EGPlanner/onLinePlanner.h \
	include/EGPlanner/egPlanner.h \
	include/EGPlanner/simAnnPlanner.h \
	include/EGPlanner/guidedPlanner.h \
	include/EGPlanner/loopPlanner.h \
	include/EGPlanner/timeTest.h \
	include/EGPlanner/graspTesterThread.h \
	include/EGPlanner/onLineGraspInterface.h \
	include/EGPlanner/listPlanner.h \
	include/FitParabola.h \
	include/shadow.h

SOURCES	+= src/arch.cpp \
	src/barrett.cpp \
	src/bbox.cpp \
	src/body.cpp \
	src/contact.cpp \
	src/contactSetting.cpp \
	src/dof.cpp \
	src/dynamics.cpp \
	src/dynJoint.cpp \
	src/eigenGrasp.cpp \
	src/gloveInterface.cpp \
	src/grasp.cpp \
	src/graspitGUI.cpp \
	src/graspitServer.cpp \
	src/graspitApp.cpp \
	src/graspRecord.cpp \
	src/gws.cpp \
	src/gwsprojection.cpp \
	src/humanHand.cpp \
	src/ivmgr.cpp \
	src/jacobian.cpp \
	src/joint.cpp \
	src/kinematicChain.cpp \
	src/lmiOptimizer.cpp \
	src/main.cpp \
	src/material.cpp \
	src/matvec.cpp \
	src/matvecIO.cpp \
	src/maxdet_src.cpp \
	src/mcGrip.cpp \
	src/mytools.cpp \
	src/profiling.cpp \
	src/pr2Gripper.cpp \
	src/m7.cpp \
	src/m7tool.cpp \
	src/puma560.cpp \
	src/quality.cpp \
	src/robonaut.cpp \
	src/robot.cpp \
	src/scanSimulator.cpp \
	src/shadow.cpp \
	src/SoArrow.cpp \
	src/SoComplexShape.cpp \
	src/SoTorquePointer.cpp \	
	src/triangle.cpp \
	src/world.cpp \
	src/worldElement.cpp \
	src/math/matrix.cpp \
	src/Collision/collisionInterface.cpp \
	src/Planner/grasp_visualization.cpp \
	src/Planner/grasp_tester.cpp \
	src/Planner/grasp_preshape.cpp \
	src/Planner/grasp_presenter.cpp \
	src/Planner/grasp_planner.cpp \
	src/Planner/grasp_manager.cpp \
	src/Planner/grasp_grasps.cpp \
	src/Planner/grasp_directions.cpp \
	src/Planner/grasp_coordinates.cpp \
	src/EGPlanner/simAnn.cpp \
	src/EGPlanner/searchState.cpp \
	src/EGPlanner/searchStateImpl.cpp \
	src/EGPlanner/searchEnergy.cpp \
	src/EGPlanner/onLinePlanner.cpp \
	src/EGPlanner/egPlanner.cpp \
	src/EGPlanner/simAnnPlanner.cpp \
	src/EGPlanner/guidedPlanner.cpp \
	src/EGPlanner/loopPlanner.cpp \
	src/EGPlanner/timeTest.cpp \
	src/EGPlanner/graspTesterThread.cpp \
	src/EGPlanner/onLineGraspInterface.cpp \\
	src/EGPlanner/listPlanner.cpp\

#--------------------------------------- Implementations of the collision interface ---------------------------------

graspit_collision {
	DEFINES += GRASPIT_COLLISION
	INCLUDEPATH += src/Collision/Graspit
	DEPENDPATH += src/Collision/Graspit
	HEADERS	+= src/Collision/Graspit/collisionModel.h \
			   src/Collision/Graspit/collisionAlgorithms.h \
			   src/Collision/Graspit/collisionAlgorithms_inl.h \
			   src/Collision/Graspit/graspitCollision.h 		
	SOURCES	+= src/Collision/Graspit/collisionModel.cpp \
			   src/Collision/Graspit/collisionAlgorithms.cpp \
			   src/Collision/Graspit/graspitCollision.cpp
} else {
	error("Collision detection method not specified")
}

#--------------------------------------- User interface: main window and dialogs ---------------------------------

INCLUDEPATH	+= ui ui/Planner ui/EGPlanner
DEPENDPATH += ui ui/Planner ui/EGPlanner

FORMS += ui/mainWindow.ui \
	ui/about.ui \
	ui/archBuilderDlg.ui \
	ui/barrettHandDlg.ui \
	ui/bodyPropDlg.ui \
	ui/contactExaminerDlg.ui \
	ui/eigenGraspDlg.ui \
	ui/gfoDlg.ui \
	ui/gloveCalibrationDlg.ui \
	ui/graspCaptureDlg.ui \
	ui/gwsProjDlgBase.ui \
	ui/qmDlg.ui \
	ui/qualityIndicator.ui \
	ui/settingsDlg.ui \
	ui/Planner/plannerdlg.ui \
	ui/EGPlanner/egPlannerDlg.ui \
	ui/EGPlanner/compliantPlannerDlg.ui

HEADERS += ui/mainWindow.h \
	ui/archBuilderDlg.h \
	ui/PolycrankPanelDlg.h \
	ui/PolycrankSaverDlg.h \
	ui/PolycrankPlayerDlg.h \
	ui/barrettHandDlg.h \
	ui/bodyPropDlg.h \
	ui/contactExaminerDlg.h \
	ui/eigenGraspDlg.h \
	ui/gfoDlg.h \
	ui/gloveCalibrationDlg.h \
	ui/graspCaptureDlg.h \
	ui/gwsProjDlg.h \
	ui/settingsDlg.h \
	ui/qmDlg.h \
	ui/Planner/plannerdlg.h \
	ui/EGPlanner/egPlannerDlg.h \
	ui/EGPlanner/compliantPlannerDlg.h


SOURCES += ui/mainWindow.cpp \
	ui/archBuilderDlg.cpp \
	ui/PolycrankPanelDlg.cpp \
	ui/PolycrankSaverDlg.cpp \
	ui/PolycrankPlayerDlg.cpp \
	ui/barrettHandDlg.cpp \
	ui/bodyPropDlg.cpp \
	ui/contactExaminerDlg.cpp \
	ui/eigenGraspDlg.cpp \
	ui/gfoDlg.cpp \
	ui/gloveCalibrationDlg.cpp \
	ui/graspCaptureDlg.cpp \
	ui/gwsProjDlg.cpp \
	ui/qmDlg.cpp \
	ui/settingsDlg.cpp \
	ui/Planner/plannerdlg.cpp \
	ui/EGPlanner/egPlannerDlg.cpp \
	ui/EGPlanner/compliantPlannerDlg.cpp

#-------------------------------------- images and resources -------------------------------------------------------

IMAGES	= src/images/play.xpm \
	src/images/pause.xpm \
	src/images/splash.jpg \
	src/images/logo.png \
	src/images/polycrank.png \
	src/images/nocollide.xpm \
	src/images/collide.xpm \
	src/images/translateTool.xpm \
	src/images/selectTool.xpm \
	src/images/rotateTool.xpm \
	src/images/mark.xpm \
	src/images/prevMark.xpm \
	src/images/filenew.xpm \
	src/images/fileopen.xpm \
	src/images/filesave.xpm \
	src/images/filenew \
	src/images/fileopen \
	src/images/filesave \
	src/images/print \
	src/images/undo \
	src/images/redo \
	src/images/editcut \
	src/images/editcopy \
	src/images/editpaste \
	src/images/searchfind

#-------------------------------------- The TinyXML XML parser ---------------------------------------------------

SOURCES += tinyxml/tinyxmlparser.cpp

HEADERS += tinyxml/tinyxml.h \
	     tinyxml/tinystr.h

INCLUDEPATH += tinyxml

#-------------------------------------- The Columbia Grasp Database ---------------------------------------------------

cgdb{
	#library linking for cgdb is in platform specific files

	!exists(src/DBase) {
		error("CGDB interface code not found")
	}
	!exists(src/DBase/DBPlanner) {
		error("DBPlanner code not found")
	}
	!exists($(CGDB_MODEL_ROOT)) {
		error("CGDB_MODEL_ROOT not set, or directory not found")
	}

	QT += sql

	INCLUDEPATH += src/DBase src/DBase/DBPlanner
	DEPENDPATH += src/DBase src/DBase/DBPlanner

	SOURCES += src/DBase/dbaseDlg.cpp \
		     src/DBase/dbasePlannerDlg.cpp \
 		     src/DBase/dbase_grasp.cpp \
		     src/DBase/graspit_db_model.cpp \
		     src/DBase/graspit_db_grasp.cpp \
		     src/DBase/DBPlanner/database.cpp \
		     src/DBase/DBPlanner/sql_database_manager.cpp \
		     src/DBase/graspit_db_planner.cpp

	HEADERS += src/DBase/dbaseDlg.h \
		     src/DBase/dbasePlannerDlg.h \
		     src/DBase/dbase_grasp.h \
		     src/DBase/graspit_db_model.h \
		     src/DBase/graspit_db_grasp.h \
		     src/DBase/DBPlanner/grasp.h \
		     src/DBase/DBPlanner/model.h \
		     src/DBase/DBPlanner/db_manager.h \
		     src/DBase/DBPlanner/database.h \
		     src/DBase/DBPlanner/sql_database_manager.h \
		     src/DBase/graspit_db_planner.h

	FORMS += src/DBase/dbaseDlg.ui \
		   src/DBase/dbasePlannerDlg.ui

	#you can also define BATCH_PROCESSING in order to supress error output which requires user attention
	DEFINES += CGDB_ENABLED BATCH_PROCESSING
}


#-------------------------------------- Interfaces to QP solvers ------------------------------------------------------

mosek {
	DEFINES += MOSEK_QP
	SOURCES += src/math/mosek_qp.cpp
	HEADERS += src/math/mosek_qp.h
}
