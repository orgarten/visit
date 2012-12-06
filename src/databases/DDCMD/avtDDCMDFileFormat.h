/*****************************************************************************
*
* Copyright (c) 2000 - 2012, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//                            avtDDCMDFileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_DDCMD_FILE_FORMAT_H
#define AVT_DDCMD_FILE_FORMAT_H

#include <avtSTMDFileFormat.h>

#include <vectortypes.h>
#include <visitstream.h>

class vtkPoints;

// ****************************************************************************
//  Class: avtDDCMDFileFormat
//
//  Purpose:
//      Reads in DDCMD files as a plugin to VisIt.
//
//  Programmer: brugger -- generated by xml2avt
//  Creation:   Fri Aug 31 15:27:59 PST 2007
//
//  Modifications:
//    Eric Brugger, Thu Jan  3 11:07:49 PST 2008
//    I changed the destructor so that it is defined in the ".C" file.
//
//    Eric Brugger, Tue Jul 15 15:19:36 PDT 2008
//    I added support for the 'b' field type. This involved adding the method
//    bFieldConvert and the variables labelSize, iSpeciesSize, labelUnsigned
//    and iSpeciesUnsigned.
//
//    Eric Brugger, Thu Nov 20 10:44:45 PST 2008
//    I added the ability to read atom files, which required being able to
//    read multiple files to get all the data.
//
//    Eric Brugger, Fri Dec  5 16:37:44 PST 2008
//    I enhanced the reader to read ascii atom files.
//
//    Brad Whitlock, Mon Oct  8 15:29:33 PDT 2012
//    Use stringVector and std::string in some places.
//
//    Brad Whitlock, Thu Dec  6 10:48:33 PST 2012
//    I changed several members to unsigned long to allow for larger files.
//
// ****************************************************************************

class DDCMDHeader
{
  public:
                           DDCMDHeader(const std::string &fname,
                                       const std::string &subname);
    virtual               ~DDCMDHeader();
    bool                   IsLegacy() const;
    void                   Print(ostream &os) const;
    bool                   GetCGridFile() const;

    inline unsigned int        GetHeaderLength() const { return headerLength; }
    inline const std::string  &GetDataType() const     { return dataType; }
    inline unsigned int        GetLRec() const         { return lRec; }
    inline unsigned long       GetNRecord() const      { return nRecord; }
    inline unsigned int        GetNFiles() const       { return nFiles; }
    inline unsigned int        GetNFields() const      { return nFields; }
    inline unsigned int        GetSwap() const         { return swap; }
    inline const double       *GetHMatrix() const      { return hMatrix; }
    inline int                 GetLoop() const         { return loop; }
    inline double              GetTime() const         { return time; }
    inline const stringVector &GetFieldNames() const   { return fieldNames; }
    inline const stringVector &GetFieldTypes() const   { return fieldTypes; }
    inline const stringVector &GetFieldUnits() const   { return fieldUnits; }
    inline unsigned int       *GetFieldSizes() const   { return fieldSizes; }
    inline unsigned int        GetNXFile() const       { return nXFile; }
    inline unsigned int        GetNYFile() const       { return nYFile; }
    inline unsigned int        GetNZFile() const       { return nZFile; }
    inline unsigned int        GetNSpecies() const     { return (unsigned int)speciesNames.size(); }
    inline const stringVector &GetSpeciesNames() const { return speciesNames; }
    inline unsigned int        GetNGroups() const      { return (unsigned int)groupNames.size(); }
    inline const stringVector &GetGroupNames() const   { return groupNames; }
    inline unsigned int        GetNTypes() const       { return (unsigned int)typeNames.size(); }
    inline const stringVector &GetTypeNames() const    { return typeNames; }
    inline const std::string  &GetExeVersion() const   { return exeVersion; }

  private:
    int  Read(const std::string &filename, int maxlen, char *header);
    void ParseHeader(char *header);

    unsigned int           headerLength;
    std::string            dataType;
    unsigned int           lRec, nFiles, nFields, swap;
    unsigned long          nRecord;
    double                 hMatrix[9];
    int                    loop;
    double                 time;
    stringVector           fieldNames, fieldTypes, fieldUnits;
    unsigned int          *fieldSizes;
    unsigned int           nXFile, nYFile, nZFile;
    stringVector           speciesNames;
    stringVector           groupNames;
    stringVector           typeNames;
    std::string            exeVersion;
};
    
class avtDDCMDFileFormat : public avtSTMDFileFormat
{
  public:
                       avtDDCMDFileFormat(const char *);
    virtual           ~avtDDCMDFileFormat();

    //
    // This is used to return unconvention data -- ranging from material
    // information to information about block connectivity.
    //
    // virtual void      *GetAuxiliaryData(const char *var, int domain,
    //                                     const char *type, void *args, 
    //                                     DestructorFunction &);
    //

    virtual bool           ReturnsValidCycle() const { return true; };
    virtual int            GetCycle(void);
    virtual bool           ReturnsValidTime() const { return true; };
    virtual double         GetTime(void);

    void                   ActivateTimestep(void);

    virtual const char    *GetType(void)   { return "DDCMD"; };
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, const char *);
    virtual vtkDataArray  *GetVar(int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, const char *);

  protected:
    std::string            fname;
    stringVector           subnames;
    int                    nXFileBlocks, nYFileBlocks, nZFileBlocks, nBlocks;

    // Global header information
    bool                   cgridFile, isLegacy;
    int                    loop;
    double                 time;
    unsigned int           nXFile, nYFile, nZFile;
    unsigned int           nSpecies;
    stringVector           speciesNames;
    unsigned int           nGroups;
    stringVector           groupNames;
    unsigned int           nTypes;
    stringVector           typeNames;

    // Mesh information
    std::string            coordsUnit;
    unsigned int           nDims;
    unsigned int           nXMesh, nYMesh, nZMesh;
    unsigned int           nXMeshBlocks, nYMeshBlocks, nZMeshBlocks;
    float                  xMin, yMin, zMin;
    float                  dX, dY, dZ;
    float                  coordsScale;
    unsigned long          nPoints;

    // Block information
    unsigned int           nXBlock, nYBlock, nZBlock;
    unsigned long          nZonesBlock;
    unsigned int           nVarsBlock;
    stringVector           varNamesBlock, varUnitsBlock;
    float                **varsBlock;
    vtkPoints             *coordsBlock;
    unsigned int          *pinfoBlock;

    // Variable information
    int                    labelOffset, iSpeciesOffset;
    int                    labelSize, iSpeciesSize;
    bool                   labelUnsigned, iSpeciesUnsigned;
    int                    groupOffset, speciesOffset, typeOffset;
    int                    pinfoOffset, xOffset, yOffset, zOffset;
    int                    pinfoSize, xSize, ySize, zSize;
    char                   pinfoType, xType, yType, zType;
    int                    nVars;
    stringVector           varNames, varUnits;
    float                **varValues;
    int                   *varOffsets;
    int                   *varSizes;
    char                  *varTypes;

    // File information
    bool                   dataRead;
    unsigned long         *nRecordsList;
    unsigned int          *fileNumberList;
    unsigned long         *fileOffsetList;

    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *);

    struct DataRecords
    {
        unsigned long  nRecords;
        char          *data;
    };

    void                   Convert(void *, int);
    long long              bFieldConvert(const unsigned char *, int);
    void                   DetermineBlockDecomposition();
    DataRecords            ExchangeProcessorData(const DDCMDHeader *, DataRecords &input);
    void                   CopyExchangeDataToBlocks(const DDCMDHeader *, DataRecords &input);

    void                   CopyAsciiDataToBlocks(const DDCMDHeader *, DataRecords &input);
    void                   CopyBinaryDataToBlocks(const DDCMDHeader *, DataRecords &input);
    void                   CopyDataToBlocks(const DDCMDHeader *, DataRecords &input);

    DataRecords            ReadProcessorChunk(const DDCMDHeader *,
                                              const std::string &subname);

    void                   DetermineProcessorReadOffset(const DDCMDHeader *,
                                                        const std::string &);
    std::vector<DDCMDHeader*>   ReadHeader();
    void                   ParseCGridHeader(const DDCMDHeader *);
    void                   ParseAtomHeader(const DDCMDHeader *);
    void                   ReadCGridData(const DDCMDHeader *, const std::string &);
    void                   ReadAtomData(const DDCMDHeader *, const std::string &);
    void                   ReadData(std::vector<DDCMDHeader*> &);
    vtkDataSet            *GetPointMesh();
    vtkDataSet            *GetRectilinearMesh();
    vtkDataArray          *GetPointVar(const char *);
    vtkDataArray          *GetRectilinearVar(const char *);
};


#endif
