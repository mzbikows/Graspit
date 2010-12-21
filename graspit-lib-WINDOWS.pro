# Windows-specific libraries for GraspIt!. Included from graspit.pro - not for standalone use.


# ---------------------- Blas and Lapack----------------------------------------

mkl {
	!exists($(MKLDIR)) {
		error("MKL not installed or MKLDIR environment variable not set")
	}
	HEADERS += include/mkl_wrappers.h
	QMAKE_LIBDIR += $(MKLDIR)/ia32/lib
      LIBS    += mkl_intel_c_dll.lib mkl_intel_thread_dll.lib mkl_core_dll.lib
	#LIBS    += libiomp5md.lib
	INCLUDEPATH += $(MKLDIR)/include
	DEFINES += MKL
} else : clapack {
	!exists($(CLAPACKDIR)) {
		error("Clapack not installed or CLAPACKDIR environment variable not set")
	}
	QMAKE_LIBDIR += $(CLAPACKDIR)/ia32/lib $(CLAPACKDIR)/LIB/Win32
	graspitdbg {
		LIBS += BLASd.lib clapackd.lib
	} else {
		LIBS += BLAS.lib clapack.lib
	}
	INCLUDEPATH += $(CLAPACKDIR)/include
	HEADERS += include/lapack_wrappers.h
	DEFINES += CLAPACK
} else {
	HEADER += include/lapack_wrappers.h
	message(Warning: no version of Blas /Lapack to link against)
}

# ---------------------- General libraries and utilities ----------------------------------

graspitdbg {
	LIBS += qhull/windows/Debug/qhull.lib $(COINDIR)/lib/Coin3d.lib $(COINDIR)/lib/SoQt1d.lib
} else {
	LIBS += qhull/windows/Release/qhull.lib $(COINDIR)/lib/Coin3.lib $(COINDIR)/lib/SoQt1.lib
}

DEFINES	+= COIN_DLL SOQT_DLL WIN32

# get rid of Windows specific warnings due to unsecure calls to fscanf, fopen etc.
# this could use a more solid, cross-platform solution
DEFINES 	+= _CRT_SECURE_NO_DEPRECATE

#------------------------------------ add-ons --------------------------------------------

mosek {
	!exists($(MOSEK5_0_INSTALLDIR)) {
		error("Mosek not installed or MOSEK5_0_INSTALLDIR environment variable not set")
	}
	INCLUDEPATH += $(MOSEK5_0_INSTALLDIR)/tools/platform/win/h
	#no separate debug or release versions of the lib
	LIBS += $(MOSEK5_0_INSTALLDIR)/tools/platform/win/dll/mosek5_0.lib
}

boost {
	!exists($(BOOST_ROOT)) {
		error("Boost not installed or BOOST_ROOT environment variable not set")
	}
	INCLUDEPATH += $(BOOST_ROOT)
	graspitdbg {
		LIBS += $(BOOST_ROOT)/lib/libboost_thread-vc71-mt-gd-1_37.lib
	} else {
		LIBS += $(BOOST_ROOT)/lib/libboost_thread-vc71-mt-1_37.lib
	}
}

hardwarelib {
	DEFINES += HARDWARE_LIB
	graspitdbg {
		LIBS += hardware/Debug/HardwareLib.lib
	} else {
		LIBS += hardware/Release/HardwareLib.lib
	}
	INCLUDEPATH += hardware

	FORMS += ui/sensorInputDlg.ui
	HEADERS += ui/sensorInputDlg.h
	SOURCES += ui/sensorInputDlg.cpp
}
