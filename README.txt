                                 GraspIt!
                              Version 2.1.0 

Introduction
------------
Please see the User Manual in doc/ for an introduction to GraspIt!, a list of
features, installation instructions, getting started examples, etc.

Disclaimer
----------
This is code that has been, and is currently being used, for research. There 
are still many unfinished pieces and plenty of ways to crash the system.  It's
by no means bullet proof. Please see the Introduction in the User Manual for 
more details.

Distribution Contents
---------------------

graspit.pro
graspit-core.pro
graspit-lib-LINUX.pro
graspit-lib-WINDOWS.pro
	      -  These are the main project files for GraspIt! that you can 
		 use to create your project that you can compile. Please see
		 the User Manual for installation instructions.

doc/          -  Documentation.  Contains both the User Manual and code 
		 Reference Manual. The User Manual contains installation 
		 instructions, pointers for getting started, examples, and 
		 trouble shooting and contact information.

hardware/     -  A sub project that allows GraspIt! to work with some external
		 hardware. It is Windows-only, and very unpolished.

images/       -  A place to put images saved from GraspIt!

include/      -  Header files for the main GraspIt! source code

LICENSE.txt   -  A copy of the license you accepted when you downloaded this.

matlab/       -  MEX c-files that compile into matlab functions that can
		     communicate and interact with the GraspIt! system.

models/       -  The geometry and configuration files for all the robots and
		objects.

qhull/	  - A popular package for computing n-dimensional convex hulls.
		This is used both for the contact system and to create grasp
	      wrench spaces.

README.txt    -  This file.

src/          -  The source code for GraspIt!.

src/DBase     - source code for the interface between GraspIt and the Columbia 
		Grasp Database

tinyxml/	  - a library for processing XML documents. See the header files 
		therein for license and author information for this package.

ui/	        -  The dialog windows and interfaces for GraspIt!.

worlds/       -  A place to save GraspIt! worlds.  Also includes a few
		examples.

xmlconverter/ -  A stand-alone utility for converting old GraspIt files
		(such as .cfg and .wld) to the new XML-based format.


Troubleshooting
---------------
Please check the user manual for troubleshooting and contact information!
