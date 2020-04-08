// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                            avtCubeFileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_Cube_FILE_FORMAT_H
#define AVT_Cube_FILE_FORMAT_H

#include <avtMTSDFileFormat.h>

#include "CubeReader.h"

#include <vector>

class DBOptionsAttributes;


// ****************************************************************************
//  Class: avtCubeFileFormat
//
//  Purpose:
//      Reads in Cube files as a plugin to VisIt.
//
//  Programmer: prabhat -- generated by xml2avt
//  Creation:   Fri Jun 12 09:11:12 PDT 2009
//
//  Programmer: oruebel -- Rename to Cube and removed Walker functionality
//  Modified:   Thu May 12 11:18 PDT 2009
//
//  Programmer: jfavre -- Added a boolean to extend the grid by one cell for CP2K users
//  Modified:   Fri Apr 26 11:12:38 CEST 2013
// ****************************************************************************

class avtCubeFileFormat : public avtMTSDFileFormat
{
  public:
                       avtCubeFileFormat(const char *, const DBOptionsAttributes *);
    virtual           ~avtCubeFileFormat() {;};

    //
    // This is used to return unconvention data -- ranging from material
    // information to information about block connectivity.
    //
    // virtual void      *GetAuxiliaryData(const char *var, int timestep, 
    //                                     const char *type, void *args, 
    //                                     DestructorFunction &);
    //

    //
    // If you know the times and cycle numbers, overload this function.
    // Otherwise, VisIt will make up some reasonable ones for you.
    //
    // virtual void        GetCycles(std::vector<int> &);
    // virtual void        GetTimes(std::vector<double> &);
    //

    virtual int            GetNTimesteps(void);

    virtual const char    *GetType(void)   { return "Cube"; };
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, const char *);
    virtual vtkDataArray  *GetVar(int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, const char *);
  protected:
    // DATA MEMBERS

    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *, int);

    CubeReader *creader;
    bool ExtendVolumeByOneCell;
};


#endif
