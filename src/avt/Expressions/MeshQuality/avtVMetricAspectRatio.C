// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                              avtVMetricAspectRatio.C                      //
// ************************************************************************* //

#include "avtVMetricAspectRatio.h"

#include <vtkCellType.h>

#include <verdict.h>

// ****************************************************************************
//  Method: avtVMetricApsectRatio::Metric
//
//  Purpose:
//      Inspect an element and calculate the aspect ratio.
//
//  Arguments:
//      coords    The set of xyz points for the cell.
//      numPoints The number of xyz points for the cell.
//      type      The vtk type of the cell.
//
//  Returns:      The aspect ratio of the cell, or defaultValue if not 
//                supported.
//
//  Programmer:   Akira Haddox
//  Creation:     June 13, 2002
//
//  Modifications:
//
//    Hank Childs, Thu Oct 17 08:07:53 PDT 2002
//    Update for new verdict interface.
//
//    Eric Brugger, Thu Jul 31 16:11:27 PDT 2008
//    Updated for verdict version 110.
//
// ****************************************************************************

double avtVMetricAspectRatio::Metric (double coords[][3], int type)
{
#ifdef HAVE_VERDICT
    switch (type)
    {
        case VTK_HEXAHEDRON:
        case VTK_VOXEL:
            return v_hex_aspect(8, coords);
        
        case VTK_QUAD:
            return v_quad_aspect(4, coords);
    }
#endif
    return 0;
}
