#*****************************************************************************
#
# Copyright (c) 2000 - 2019, Lawrence Livermore National Security, LLC
# Produced at the Lawrence Livermore National Laboratory
# LLNL-CODE-442911
# All rights reserved.
#
# This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
# full copyright notice is contained in the file COPYRIGHT located at the root
# of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
#
# Redistribution  and  use  in  source  and  binary  forms,  with  or  without
# modification, are permitted provided that the following conditions are met:
#
#  - Redistributions of  source code must  retain the above  copyright notice,
#    this list of conditions and the disclaimer below.
#  - Redistributions in binary form must reproduce the above copyright notice,
#    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
#    documentation and/or other materials provided with the distribution.
#  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
#    be used to endorse or promote products derived from this software without
#    specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
# ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
# LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
# DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
# SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
# CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
# LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
# OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
# DAMAGE.
#
# Modifications:
#
#****************************************************************************/

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${VISIT_COMMON_INCLUDES}
${VISIT_SOURCE_DIR}/avt/DBAtts/MetaData
${VISIT_SOURCE_DIR}/avt/DBAtts/SIL
${VISIT_SOURCE_DIR}/avt/DataBinning
${VISIT_SOURCE_DIR}/avt/Database/Database
${VISIT_SOURCE_DIR}/avt/Database/Ghost
${VISIT_SOURCE_DIR}/avt/Expressions/Abstract
${VISIT_SOURCE_DIR}/avt/Expressions/CMFE
${VISIT_SOURCE_DIR}/avt/Expressions/Conditional
${VISIT_SOURCE_DIR}/avt/Expressions/Derivations
${VISIT_SOURCE_DIR}/avt/Expressions/General
${VISIT_SOURCE_DIR}/avt/Expressions/ImageProcessing
${VISIT_SOURCE_DIR}/avt/Expressions/Management
${VISIT_SOURCE_DIR}/avt/Expressions/Math
${VISIT_SOURCE_DIR}/avt/Expressions/MeshQuality
${VISIT_SOURCE_DIR}/avt/FileWriter
${VISIT_SOURCE_DIR}/avt/Filters
${VISIT_SOURCE_DIR}/avt/Math
${VISIT_SOURCE_DIR}/avt/VisWindow/VisWindow
${VISIT_SOURCE_DIR}/avt/Pipeline/AbstractFilters
${VISIT_SOURCE_DIR}/avt/Pipeline/Data
${VISIT_SOURCE_DIR}/avt/Pipeline/Pipeline
${VISIT_SOURCE_DIR}/avt/Pipeline/Sinks
${VISIT_SOURCE_DIR}/avt/Pipeline/Sources
${VISIT_SOURCE_DIR}/avt/Plotter
${VISIT_SOURCE_DIR}/avt/Queries/Abstract
${VISIT_SOURCE_DIR}/avt/Queries/Misc
${VISIT_SOURCE_DIR}/avt/Queries/Pick
${VISIT_SOURCE_DIR}/avt/Queries/Queries
${VISIT_SOURCE_DIR}/avt/View
${VISIT_SOURCE_DIR}/avt/VisWindow/Colleagues
${VISIT_SOURCE_DIR}/avt/VisWindow/Proxies
${VISIT_SOURCE_DIR}/avt/VisWindow/Tools
${VISIT_SOURCE_DIR}/avt/VisWindow/VisWindow
${VISIT_SOURCE_DIR}/engine/main
${VTK_INCLUDE_DIRS}
)

LINK_DIRECTORIES(${LIBRARY_OUTPUT_DIRECTORY}
${ALL_THIRDPARTY_IO_LIBRARY_DIR}
${ICET_LIBRARY_DIR}
)

ADD_EXECUTABLE(avtFilterExample avtFilterExample.C)
VISIT_INSTALL_TARGETS(avtFilterExample)
VISIT_EXAMPLES_ADD_FOLDER(avtexamples avtFilterExample)

TARGET_LINK_LIBRARIES(avtFilterExample
${engine_ser_exe_IDatabase}
${engine_ser_exe_EDatabase_ser}
avtdatabase_ser
avtdbatts
avtfilters_ser
avtpipeline_ser
lightweight_visit_vtk 
visitcommon
visit_vtk
${ALL_THIRDPARTY_IO_LIB} 
${VTK_EXTRA_LIBS}
${OPENGL_LIBRARIES}
${CMAKE_THREAD_LIBS} 
${ZLIB_LIB}
)

if(HAVE_OSMESA)
    target_link_libraries(avtFilterExample ${OSMESA_LIBRARIES})
elseif(HAVE_EGL)
    target_link_libraries(avtFilterExample ${EGL_LIBRARIES})
endif()

ADD_EXECUTABLE(avtRenderExample avtRenderExample.C)
VISIT_INSTALL_TARGETS(avtRenderExample)
VISIT_EXAMPLES_ADD_FOLDER(avtexamples avtRenderExample)

TARGET_LINK_LIBRARIES(avtRenderExample
${engine_ser_exe_IDatabase}
${engine_ser_exe_EDatabase_ser}
avtdatabase_ser
avtdbatts
avtfilters_ser
avtpipeline_ser
avtplotter_ser
avtview
avtviswindow_ser
avtwriter_ser
lightweight_visit_vtk 
visitcommon
visit_vtk
${ALL_THIRDPARTY_IO_LIB} 
${VTK_EXTRA_LIBS}
${OPENGL_LIBRARIES}
${CMAKE_THREAD_LIBS} 
${ZLIB_LIB}
)

if(HAVE_OSMESA)
    target_link_libraries(avtRenderExample ${OSMESA_LIBRARIES})
elseif(HAVE_EGL)
    target_link_libraries(avtRenderExample ${EGL_LIBRARIES})
endif()


ADD_EXECUTABLE(avtPluginExample avtPluginExample.C)
VISIT_INSTALL_TARGETS(avtPluginExample)
VISIT_EXAMPLES_ADD_FOLDER(avtexamples avtPluginExample)

TARGET_LINK_LIBRARIES(avtPluginExample
${engine_ser_exe_IDatabase}
${engine_ser_exe_EDatabase_ser}
avtdatabase_ser
avtdbatts
avtfilters_ser
avtpipeline_ser
lightweight_visit_vtk 
visitcommon
visit_vtk
${ALL_THIRDPARTY_IO_LIB} 
${VTK_EXTRA_LIBS}
${OPENGL_LIBRARIES}
${CMAKE_THREAD_LIBS} 
${ZLIB_LIB}
)

if(HAVE_OSMESA)
    target_link_libraries(avtPluginExample ${OSMESA_LIBRARIES})
elseif(HAVE_EGL)
    target_link_libraries(avtPluginExample ${EGL_LIBRARIES})
endif()

ADD_EXECUTABLE(avtPlotPluginExample avtPlotPluginExample.C)
VISIT_INSTALL_TARGETS(avtPlotPluginExample)
VISIT_EXAMPLES_ADD_FOLDER(avtexamples avtPlotPluginExample)

TARGET_LINK_LIBRARIES(avtPlotPluginExample
${engine_ser_exe_IDatabase}
${engine_ser_exe_EDatabase_ser}
avtdatabase_ser
avtdbatts
avtfilters_ser
avtpipeline_ser
avtplotter_ser
avtview
avtviswindow_ser
avtwriter_ser
lightweight_visit_vtk 
visitcommon
visit_vtk
${ALL_THIRDPARTY_IO_LIB} 
${VTK_EXTRA_LIBS}
${OPENGL_LIBRARIES}
${CMAKE_THREAD_LIBS} 
${ZLIB_LIB}
)

if(HAVE_OSMESA)
    target_link_libraries(avtPlotPluginExample ${OSMESA_LIBRARIES})
elseif(HAVE_EGL)
    target_link_libraries(avtPlotPluginExample ${EGL_LIBRARIES})
endif()

ADD_EXECUTABLE(networkManagerExample networkManagerExample.C)
VISIT_INSTALL_TARGETS(networkManagerExample)
VISIT_EXAMPLES_ADD_FOLDER(avtexamples networkManagerExample)

TARGET_LINK_LIBRARIES(networkManagerExample
${engine_ser_exe_IDatabase}
${engine_ser_exe_EDatabase_ser}
avtdatabase_ser
avtdbatts
avtfilters_ser
avtpipeline_ser
avtplotter_ser
avtview
avtviswindow_ser
avtwriter_ser
engine_ser
lightweight_visit_vtk 
visitcommon
visit_vtk
${ALL_THIRDPARTY_IO_LIB} 
${VTK_EXTRA_LIBS}
${OPENGL_LIBRARIES}
${CMAKE_THREAD_LIBS} 
${ZLIB_LIB}
)