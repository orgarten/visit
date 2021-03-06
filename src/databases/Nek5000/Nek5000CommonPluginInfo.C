// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include <Nek5000PluginInfo.h>
#include <avtNek5000FileFormat.h>
#include <avtMTMDFileFormatInterface.h>
#include <avtGenericDatabase.h>
#include <avtNek5000Options.h>

// ****************************************************************************
//  Method:  Nek5000CommonPluginInfo::GetDatabaseType
//
//  Purpose:
//    Returns the type of a Nek5000 database.
//
//  Programmer:  generated by xml2info
//  Creation:    omitted
//
// ****************************************************************************
DatabaseType
Nek5000CommonPluginInfo::GetDatabaseType()
{
    return DB_TYPE_MTMD;
}

// ****************************************************************************
//  Method: Nek5000CommonPluginInfo::SetupDatabase
//
//  Purpose:
//      Sets up a Nek5000 database.
//
//  Arguments:
//      list    A list of file names.
//      nList   The number of timesteps in list.
//      nBlocks The number of blocks in the list.
//
//  Returns:    A Nek5000 database from list.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************
avtDatabase *
Nek5000CommonPluginInfo::SetupDatabase(const char *const *list,
                                   int nList, int nBlock)
{
    // ignore any nBlocks past 1
    int nTimestepGroups = nList / nBlock;
    avtMTMDFileFormat **ffl = new avtMTMDFileFormat*[nTimestepGroups];
    for (int i = 0; i < nTimestepGroups; i++)
    {
        ffl[i] = new avtNek5000FileFormat(list[i*nBlock], readOptions);
    }
    avtMTMDFileFormatInterface *inter
           = new avtMTMDFileFormatInterface(ffl, nTimestepGroups);
    return new avtGenericDatabase(inter);
}

// ****************************************************************************
//  Method: Nek5000CommonPluginInfo::GetReadOptions
//
//  Purpose:
//      Gets the read options.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

DBOptionsAttributes *
Nek5000CommonPluginInfo::GetReadOptions() const
{
    return GetNek5000ReadOptions();
}

// ****************************************************************************
//  Method: Nek5000CommonPluginInfo::GetWriteOptions
//
//  Purpose:
//      Gets the write options.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

DBOptionsAttributes *
Nek5000CommonPluginInfo::GetWriteOptions() const
{
    return GetNek5000WriteOptions();
}

