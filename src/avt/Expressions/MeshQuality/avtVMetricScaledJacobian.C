// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                              avtVMetricScaledJacobian.C                   //
// ************************************************************************* //

#include "avtVMetricScaledJacobian.h"

#include <vtkCellType.h>

#include <verdict.h>

// ****************************************************************************
//  Method: avtVMetricScaledJacobian::Metric
//
//  Purpose:
//      Inspect an element and calculate the scaled_jacobian.
//
//  Arguments:
//      coords    The set of xyz points for the cell.
//      numPoints The number of xyz points for the cell.
//      type      The vtk type of the cell.
//
//  Returns:      The scaled_jacobian of the cell, or defaultValue if not 
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
// ****************************************************************************

double avtVMetricScaledJacobian::Metric (double coords[][3], int type)
{
#ifdef HAVE_VERDICT 
    switch (type)
    {
        case VTK_HEXAHEDRON:
        case VTK_VOXEL:
            return v_hex_scaled_jacobian(8, coords);
        
        case VTK_TETRA:
            return v_tet_scaled_jacobian(4,coords);

        case VTK_QUAD:
            return v_quad_scaled_jacobian(4, coords);

        case VTK_TRIANGLE:
            return v_tri_scaled_jacobian(3, coords);
    }
#endif
    return -2;
}
