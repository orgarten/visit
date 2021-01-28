# Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
# Project developers.  See the top-level LICENSE file for dates and other
# details.  No copyright assignment is required to contribute to VisIt.

#****************************************************************************
# Modifications:
#   Kathleen Bonnell, Thu Dec 10 17:53:36 MT 2009
#   Use the same find routines whether on Windows or not.
#
#   Cyrus Harrison, Fri Feb 19 15:41:04 PST 2010
#   Added install of vtk python wrappers (if they exist).
#
#   Cyrus Harrison, Tue Mar  9 07:51:00 PST 2010
#   Added install_name_tool patch of of vtk python wrappers (if they exist)
#
#   Kathleen Bonnell,  Wed Mar 17 10:03:52 MST 2010
#   Prevent '.svn' from being included when installing directories. 
#   Change how python wrappers are handled on windows, due to different
#   VTK directory structure.
#
#   Kathleen Bonnell,  Thu Dec 2 15:30:05 MST 2010
#   Add .lib files for Install on Windows.
# 
#   Tom Fogal, Fri Jan 28 13:35:29 MST 2011
#   Account for new VTK installation structure.
#
#   Kathleen Bonnell, Tue Jun  7 11:10:51 PDT 2011
#   Don't add VTK's MangledMesa directory to VTK_INCLUDE_DIRS unless VTK
#   was built with MangledMesa.
#
#   Brad Whitlock, Mon Nov 21 10:22:56 PST 2011
#   Print out some variables that were supposed to have been set by the
#   FindVTK.cmake routine so we know better what's going on. Also deal with
#   the case where VTK has been installed normally (with vtk-5.8 subdirs)
#   and change how Python filters are located on Windows.
#
#   Cyrus Harrison, Tue Sep 25 12:09:39 PDT 2012
#   Added Geoviz libs
#
#   Kathleen Biagas, Thu Dec 6 10:26:54 PST 2012 
#   Use VTK_LIBRARIES and others in determining what to install, rather than
#   listing individually, which is prone to omissions.
#
#   Kathleen Biagas, Wed Jan 30 17:54:21 MST 2013
#   Preliminary changes for VTK-6.
#
#   Kathleen Biagas, Thu Feb 21 16:04:58 MST 2013
#   Set VTK_LIBRARY_DIRS manually.
#
#   Kathleen Biagas, Thu May  2 10:11:44 PDT 2013
#   Don't attempt the python wrappers if we don't have PYTHON_VERSION.
# 
#   Kathleen Biagas, Fri May  3 17:00:03 MST 2013
#   Ensure that the vtk install has all the libraries we require.
# 
#   Alister Maguire, Thu Sep 14 14:26:07 PDT 2017
#   Added vtkRenderingVolumeOpenGL2
#
#   Kathleen Biagas, Fri Jan  17 2020
#   Install vtkTestOpenGLVersion.exe on Windows when needed.
# 
#   Kathleen Biagas, Wed Mar 18 12:36:15 PDT 2020
#   Changed module naming from vtkXXX to VTK::XXX per VTK-9 scheme.
#
#****************************************************************************/

INCLUDE(${VISIT_SOURCE_DIR}/CMake/ThirdPartyInstallLibrary.cmake)

# Use the VTK_DIR hint from the config-site .cmake file 

IF(EXISTS ${VISIT_VTK_DIR}/lib/cmake/vtk-${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}/VTKConfig.cmake)
    SET(VTK_DIR ${VISIT_VTK_DIR}/lib/cmake/vtk-${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION})
ENDIF()

MESSAGE(STATUS "Checking for VTK in ${VTK_DIR}")

# Set up our list of required and optional vtk modules
SET(REQ_VTK_MODS 
        CommonCore
        CommonDataModel
        FiltersCore
        FiltersFlowPaths
        FiltersHybrid
        FiltersModeling
        IOLegacy
        IOPLY
        IOXML
        InteractionStyle
        RenderingAnnotation
        RenderingOpenGL2
        RenderingVolumeOpenGL2
        glew)

IF(NOT VISIT_SERVER_COMPONENTS_ONLY AND NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)
    LIST(APPEND REQ_VTK_MODS GUISupportQt)
ENDIF()

# Optional
SET(OPT_VTK_MODS
       GeovisCore # Cartographic Projection Operator
       IOEnSight  # EnSight Database
       libxml2    # Xdmf Database
   )


set(Qt5_DIR ${VISIT_QT_DIR}/lib/cmake/Qt5)
find_package(VTK ${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}
    REQUIRED ${REQ_VTK_MODS}
    OPTIONAL_COMPONENTS ${OPT_VTK_MODS}
    NO_MODULE
    PATHS ${VTK_DIR})

# Ensure we have all the required modules:
FOREACH(module ${REQ_VTK_MODS})
    IF(NOT TARGET VTK::${module})
        MESSAGE(ERROR " VisIt requires VTK::${module}")
    ENDIF()
ENDFOREACH()


MESSAGE(STATUS "  VTK_FOUND=${VTK_FOUND}")
MESSAGE(STATUS "  VTK_MAJOR_VERSION=${VTK_MAJOR_VERSION}")
MESSAGE(STATUS "  VTK_MINOR_VERSION=${VTK_MINOR_VERSION}")
MESSAGE(STATUS "  VTK_BUILD_VERSION=${VTK_BUILD_VERSION}")
MESSAGE(STATUS "  VTK_PREFIX_PATH=${VTK_PREFIX_PATH}")
MESSAGE(STATUS "  VTK_PYTHON_VERSION=${VTK_PYTHON_VERSION}")
MESSAGE(STATUS "  VTK_PYTHONPATH=${VTK_PYTHONPATH}")
MESSAGE(STATUS "  VTK_LIBRARIES=${VTK_LIBRARIES}")
MESSAGE(STATUS "  VTK_AVAILABLE_COMPONENTS=${VTK_AVAILABLE_COMPONENTS}")

# Add install commands for all of the VTK libraries. Is there a better way?
IF(APPLE)
    SET(SO_EXT "dylib")
ELSE(APPLE)
    IF(WIN32)
        SET(SO_EXT "dll")
    ELSE(WIN32)
        SET(SO_EXT "so")
    ENDIF(WIN32)
ENDIF(APPLE)

IF(VISIT_VTK_SKIP_INSTALL)
    MESSAGE(STATUS "Skipping installation of VTK libraries")
ELSE(VISIT_VTK_SKIP_INSTALL)
    IF(NOT WIN32)
        SET(pathnameandprefix "${VTK_PREFIX_PATH}/lib64/lib")
    ELSE()
        SET(pathnameandprefix "${VTK_PREFIX_PATH}/bin/")
        SET(pathnameandprefixlib "${VTK_PREFIX_PATH}/lib/")
    ENDIF(NOT WIN32)
    MACRO(SETUP_INSTALL vtk_component)
        if(${vtk_component} MATCHES "vtksys")
          SET(LIBNAME   ${pathnameandprefix}${vtk_component}-${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}.${SO_EXT})
        else()
            SET(LIBNAME   ${pathnameandprefix}vtk${vtk_component}-${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}.${SO_EXT})
        endif()
        IF(EXISTS ${LIBNAME})
            THIRD_PARTY_INSTALL_LIBRARY(${LIBNAME})
        ENDIF()

        IF(WIN32)
            # install .lib versions, too
            SET(LIBNAME   ${pathnameandprefixlib}vtk${vtk_component}-${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}.lib)
            IF(EXISTS ${LIBNAME})
                THIRD_PARTY_INSTALL_LIBRARY(${LIBNAME})
            ENDIF(EXISTS ${LIBNAME})
        ENDIF(WIN32)
    ENDMACRO(SETUP_INSTALL vtk_component)

    # Base libs and their python wrappings
    FOREACH(VTKLIB ${VTK_AVAILABLE_COMPONENTS})
        SETUP_INSTALL("${VTKLIB}")
    ENDFOREACH(VTKLIB)  

    # Python
#These don't exist in this form
#    IF(PYTHON_VERSION)
#        # different naming convention.
#        # Remove '.' from python version for use in vtk python library naming. 
#        STRING(REPLACE "." "" PYVER ${PYTHON_VERSION})
#        FOREACH(VTKLIB ${VTK_LIBRARIES})
#            SETUP_INSTALL("${VTKLIB}Python${PYVER}D")
#        ENDFOREACH(VTKLIB)
#        SETUP_INSTALL(vtkWrappingPython${PYVER}Core)
#    ENDIF(PYTHON_VERSION)

    IF(VISIT_HEADERS_SKIP_INSTALL)
        MESSAGE(STATUS "Skipping vtk headers installation")
    ELSE(VISIT_HEADERS_SKIP_INSTALL)
        INSTALL(DIRECTORY ${VTK_PREFIX_PATH}/include/vtk-${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}
            DESTINATION ${VISIT_INSTALLED_VERSION_INCLUDE}/vtk
            FILE_PERMISSIONS OWNER_WRITE OWNER_READ 
                             GROUP_WRITE GROUP_READ 
                             WORLD_READ
            DIRECTORY_PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE 
                                  GROUP_WRITE GROUP_READ GROUP_EXECUTE 
                                  WORLD_READ WORLD_EXECUTE
            PATTERN ".svn" EXCLUDE
        )
    ENDIF(VISIT_HEADERS_SKIP_INSTALL)
ENDIF(VISIT_VTK_SKIP_INSTALL)

# check for python wrappers
set(VTK_PY_WRAPPERS_DIR ${VTK_PREFIX_PATH}/${VTK_PYTHONPATH})
MESSAGE(STATUS "  VTK_PY_WRAPPERS_DIR=${VTK_PY_WRAPPERS_DIR}")

IF(EXISTS ${VTK_PY_WRAPPERS_DIR}/vtkmodules)
    MESSAGE(STATUS "Found VTK Python Wrappers - ${VTK_PY_WRAPPERS_DIR}")
    # there is no egg file
    #FILE(GLOB VTK_PY_EGG ${VTK_PY_WRAPPERS_DIR}/site-packages/*.egg*)
    FILE(GLOB VTK_PY_MODULE ${VTK_PY_WRAPPERS_DIR}/vtkmodules)

    IF(VISIT_VTK_SKIP_INSTALL)
        MESSAGE(STATUS "Skipping installation of VTK Python bindings")
    ELSE(VISIT_VTK_SKIP_INSTALL)
# there is no egg file
        #INSTALL(FILES ${VTK_PY_EGG}
        #        DESTINATION ${VISIT_INSTALLED_VERSION_LIB}/site-packages/
        #        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ
        #    )
# bu there is a 'vtk.py' file
        INSTALL(FILES ${VTK_PY_WRAPPERS_DIR}/vtk.py
                DESTINATION ${VISIT_INSTALLED_VERSION_LIB}/site-packages/
                PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ
            )
        INSTALL(DIRECTORY ${VTK_PY_MODULE}
                DESTINATION ${VISIT_INSTALLED_VERSION_LIB}/site-packages/
                FILE_PERMISSIONS OWNER_WRITE OWNER_READ GROUP_WRITE GROUP_READ WORLD_READ
                DIRECTORY_PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
                PATTERN ".svn" EXCLUDE
            )
    ENDIF(VISIT_VTK_SKIP_INSTALL)

    SET(VTK_PYTHON_WRAPPERS_FOUND TRUE)
ELSE()
    SET(VTK_PYTHON_WRAPPERS_FOUND FALSE)
ENDIF()

MARK_AS_ADVANCED(VTK_PYTHON_WRAPPERS_FOUND)

# prepare for drop-in replacement of mesa with opengl, if all pieces are in place
if(WIN32 AND VISIT_MESA_REPLACE_OPENGL AND VISIT_MESAGL_DIR)
    if(EXISTS ${VISIT_VTK_DIR}/bin/vtkTestOpenGLVersion.exe)
        install(FILES ${VISIT_VTK_DIR}/bin/vtkTestOpenGLVersion.exe
                DESTINATION ${VISIT_INSTALLED_VERSION_BIN}
                PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                            WORLD_READ WORLD_EXECUTE
                CONFIGURATIONS "" None Debug Release RelWithDebInfo MinSizeRel
                )
    endif()
endif()

IF(NOT ${VTK_FOUND})
    MESSAGE(FATAL_ERROR "VTK is required to build VisIt.")
ENDIF(NOT ${VTK_FOUND})
