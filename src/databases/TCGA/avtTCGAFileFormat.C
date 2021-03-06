// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                            avtTCGAFileFormat.C                           //
// ************************************************************************* //

#include <avtTCGAFileFormat.h>

#include <string>

#include <vtkFloatArray.h>
#include <vtkRectilinearGrid.h>
#include <vtkUnstructuredGrid.h>
#include <vtkImageData.h>
#include <vtkPoints.h>
#include <vtkVertex.h>

#include <avtDatabaseMetaData.h>
#include <Expression.h>

#include <InvalidVariableException.h>
#include <InvalidFilesException.h>
#include <VisItStreamUtil.h>
#include <vtkTIFFReader.h>

#include <glob.h>

using std::string;
using std::vector;

static void
extractXY(const string &str, const string &suffix, int &x, int &y);

// ****************************************************************************
//  Method: avtTCGAFileFormat constructor
//
//  Programmer: pugmire -- generated by xml2avt
//  Creation:   Mon Nov 3 15:46:13 PST 2014
//
// ****************************************************************************

avtTCGAFileFormat::avtTCGAFileFormat(const char *filename)
    : avtSTMDFileFormat(&filename, 1)
{
    initialized = false;
    imageSize[0] = 0;
    imageSize[1] = 0;
    Initialize();
}


// ****************************************************************************
//  Method: avtTCGAFileFormat::FreeUpResources
//
//  Purpose:
//      When VisIt is done focusing on a particular timestep, it asks that
//      timestep to free up any resources (memory, file descriptors) that
//      it has associated with it.  This method is the mechanism for doing
//      that.
//
//  Programmer: pugmire -- generated by xml2avt
//  Creation:   Mon Nov 3 15:46:13 PST 2014
//
// ****************************************************************************

void
avtTCGAFileFormat::FreeUpResources(void)
{
}


// ****************************************************************************
//  Method: avtTCGAFileFormat::PopulateDatabaseMetaData
//
//  Purpose:
//      This database meta-data object is like a table of contents for the
//      file.  By populating it, you are telling the rest of VisIt what
//      information it can request from you.
//
//  Programmer: pugmire -- generated by xml2avt
//  Creation:   Mon Nov 3 15:46:13 PST 2014
//
// ****************************************************************************

void
avtTCGAFileFormat::PopulateDatabaseMetaData(avtDatabaseMetaData *md)
{
    Initialize();

    avtMeshMetaData *mesh = new avtMeshMetaData;
    mesh->name = "ImageMesh";
    mesh->meshType = AVT_RECTILINEAR_MESH;
    mesh->numBlocks = imageFiles.size();
    mesh->spatialDimension = 2;
    mesh->topologicalDimension = 2;
    md->Add(mesh);

    if (!contourFiles.empty())
    {
        avtMeshMetaData *mesh = new avtMeshMetaData;
        mesh->name = "ContourMesh";
        mesh->meshType = AVT_UNSTRUCTURED_MESH;
        //mesh->meshType = AVT_POINT_MESH;
        mesh->numBlocks = imageFiles.size();
        mesh->spatialDimension = 2;
        mesh->topologicalDimension = 2;
        //mesh->topologicalDimension = 1;
        md->Add(mesh);
    }
    
    AddVectorVarToMetaData(md, "color", "ImageMesh", AVT_ZONECENT, 4);
}


//****************************************************************************
// Method:  avtTCGAFileFormat::Initialize
//
// Purpose:
//   Initialize stuff.
//
// Arguments:
//   
//
// Programmer:  Dave Pugmire
// Creation:    November  5, 2014
//
// Modifications:
//
//****************************************************************************

void
avtTCGAFileFormat::Initialize()
{
    if (initialized)
        return;

    ifstream ifile(GetFilename());
    if (ifile.fail())
        EXCEPTION1(InvalidFilesException, GetFilename());

    ifile >> imageSize[0];
    ifile >> imageSize[1];

    while (ifile.good())
    {
        string line;
        ifile >> line;
        
        //See if it's the image files.....
        if (line.find(".tif") != string::npos)
        {
            glob_t results;
            int ret = glob(line.c_str(), 0, NULL, &results);
            if (ret != 0)
                EXCEPTION1(InvalidFilesException, GetFilename());
            for (size_t i = 0; i < results.gl_pathc; i++)
                imageFiles.push_back(results.gl_pathv[i]);
            globfree(&results);
        }
        else if (line.find(".bounds.csv") != string::npos)
        {
            glob_t results;
            int ret = glob(line.c_str(), 0, NULL, &results);
            if (ret != 0)
                EXCEPTION1(InvalidFilesException, GetFilename());
            for (size_t i = 0; i < results.gl_pathc; i++)
                contourFiles.push_back(results.gl_pathv[i]);
            globfree(&results);
        }
    }

    //Must have some images.....
    if (imageFiles.size() == 0)
        EXCEPTION1(InvalidFilesException, GetFilename());
    
    initialized = true;
}


// ****************************************************************************
//  Method: avtTCGAFileFormat::GetMesh
//
//  Purpose:
//      Gets the mesh associated with this file.  The mesh is returned as a
//      derived type of vtkDataSet (ie vtkRectilinearGrid, vtkStructuredGrid,
//      vtkUnstructuredGrid, etc).
//
//  Arguments:
//      domain      The index of the domain.  If there are NDomains, this
//                  value is guaranteed to be between 0 and NDomains-1,
//                  regardless of block origin.
//      meshname    The name of the mesh of interest.  This can be ignored if
//                  there is only one mesh.
//
//  Programmer: pugmire -- generated by xml2avt
//  Creation:   Mon Nov 3 15:46:13 PST 2014
//
// ****************************************************************************

vtkDataSet *
avtTCGAFileFormat::GetMesh(int domain, const char *meshname)
{
    if (string(meshname) == "ImageMesh")
    {
        string fn = imageFiles[domain];
        int x0, y0;
        extractXY(fn, ".", x0, y0);

        vtkRectilinearGrid *rg = vtkRectilinearGrid::New();
        vtkFloatArray *x = vtkFloatArray::New();
        vtkFloatArray *y = vtkFloatArray::New();
        vtkFloatArray *z = vtkFloatArray::New();

        int sx = imageSize[0]+1;
        int sy = imageSize[1]+1;
    
        x->SetNumberOfTuples(sx);
        y->SetNumberOfTuples(sy);
        z->SetNumberOfTuples(1);

        for (int i = 0; i < sx; i++)
            x->SetTuple1(i, x0+i);
        for (int i = 0; i < sy; i++)
            y->SetTuple1(i, y0+i);
        z->SetTuple1(0,0);
        
        int dims[3] = {sx, sy, 1};
        rg->SetDimensions(dims);
        rg->SetXCoordinates(x);
        rg->SetYCoordinates(y);
        rg->SetZCoordinates(z);
    
        x->Delete();
        y->Delete();
        z->Delete();

        return rg;
    }
    else if (string(meshname) == "ContourMesh")
    {
        if (domain >= (int)contourFiles.size())
            return NULL;
        
        string fn = contourFiles[domain];
        int x0, y0;
        extractXY(fn, ".bounds.csv", x0, y0);

        vtkUnstructuredGrid *ug = vtkUnstructuredGrid::New();
        vtkPoints *pts = vtkPoints::New();
        ug->SetPoints(pts);
        pts->Delete();

        vtkIdType vertID = 0;
        string str;
        
        ifstream cFile(fn.c_str());
        while (getline(cFile, str))
        {
            if (str.empty())
                continue;

            //Parse out the x,y for each contour.
            vector<int> xy;
            size_t i0 = str.find(":"), i1 = i0;
            while ((i1 = str.find(";", i0)) != string::npos)
            {
                string xyStr = str.substr(i0+1, i1-i0);
                int x, y;
                sscanf(xyStr.c_str(), "%d,%d;", &x, &y);
                xy.push_back(x);
                xy.push_back(y);
                i0 = i1+1;
            }

            //Add the verts and lines.
            vtkIdType v0 = vertID;
            for (size_t i = 0; i < xy.size(); i+=2)
            {
                pts->InsertNextPoint(x0 + xy[i]+0.5f, y0+xy[i+1]+0.5f, 0.0f);
                if (i >= 2)
                {
                    vtkIdType v[2] = {vertID-1, vertID};
                    ug->InsertNextCell(VTK_LINE, 2, v);
                }
                vertID++;
            }
            
            //close the polyline.
            vtkIdType v[2] = {vertID-1, v0};
            ug->InsertNextCell(VTK_LINE, 2, v);
            v0 = vertID;
        }
        return ug;
    }
    return NULL;
}


// ****************************************************************************
//  Method: avtTCGAFileFormat::GetVar
//
//  Purpose:
//      Gets a scalar variable associated with this file.  Although VTK has
//      support for many different types, the best bet is vtkFloatArray, since
//      that is supported everywhere through VisIt.
//
//  Arguments:
//      domain     The index of the domain.  If there are NDomains, this
//                 value is guaranteed to be between 0 and NDomains-1,
//                 regardless of block origin.
//      varname    The name of the variable requested.
//
//  Programmer: pugmire -- generated by xml2avt
//  Creation:   Mon Nov 3 15:46:13 PST 2014
//
// ****************************************************************************

vtkDataArray *
avtTCGAFileFormat::GetVar(int domain, const char *varname)
{
    vtkTIFFReader *reader = vtkTIFFReader::New();
    reader->SetFileName(imageFiles[domain].c_str());
    reader->Update();
    vtkImageData *image = reader->GetOutput();
    
    int nChannels = image->GetNumberOfScalarComponents();

    vtkFloatArray *var = vtkFloatArray::New();
    var->SetNumberOfComponents(1);
    var->SetNumberOfTuples(imageSize[0]*imageSize[1]);
    float *ptr = (float *) var->GetVoidPointer(0);


    if (image->GetScalarType() == VTK_FLOAT)
    {
        float *data = (float *) image->GetScalarPointer();
        for (int j = 0; j < imageSize[1]; j++)
        {
            for (int i = 0; i < imageSize[0]; i++)
            {
                int index = j*imageSize[0] + i;
                float r = data[nChannels*index + 0];
                float g = data[nChannels*index + 1];
                float b = data[nChannels*index + 2];
                ptr[j*imageSize[0] + i] = (r + g + b) / 3.0f;
            }
        }
    }
    else if (image->GetScalarType() == VTK_UNSIGNED_CHAR)
    {
        unsigned char *data = (unsigned char *) image->GetScalarPointer();
        for (int j = 0; j < imageSize[1]; j++)
        {
            for (int i = 0; i < imageSize[0]; i++)
            {
                int index = j*imageSize[0] + i;
                unsigned char r = data[nChannels*index + 0];
                unsigned char g = data[nChannels*index + 1];
                unsigned char b = data[nChannels*index + 2];
                ptr[j*imageSize[0] + i] = (r + g + b) / 3.0f;
            }
        }
    }
    else
        EXCEPTION1(InvalidVariableException, varname);

    reader->Delete();
    return var;
}


// ****************************************************************************
//  Method: avtTCGAFileFormat::GetVectorVar
//
//  Purpose:
//      Gets a vector variable associated with this file.  Although VTK has
//      support for many different types, the best bet is vtkFloatArray, since
//      that is supported everywhere through VisIt.
//
//  Arguments:
//      domain     The index of the domain.  If there are NDomains, this
//                 value is guaranteed to be between 0 and NDomains-1,
//                 regardless of block origin.
//      varname    The name of the variable requested.
//
//  Programmer: pugmire -- generated by xml2avt
//  Creation:   Mon Nov 3 15:46:13 PST 2014
//
// ****************************************************************************

vtkDataArray *
avtTCGAFileFormat::GetVectorVar(int domain, const char *varname)
{
    if (string(varname) != "color")
        EXCEPTION1(InvalidVariableException, varname);

    vtkFloatArray *var = vtkFloatArray::New();
    var->SetNumberOfComponents(4);
    var->SetNumberOfTuples(imageSize[0]*imageSize[1]);
    float *ptr = (float *) var->GetVoidPointer(0);
    
    vtkTIFFReader *reader = vtkTIFFReader::New();
    reader->SetFileName(imageFiles[domain].c_str());
    reader->Update();
    vtkImageData *image = reader->GetOutput();
    int nChannels = image->GetNumberOfScalarComponents();

    if (image->GetScalarType() == VTK_FLOAT)
    {
        float *data = (float *) image->GetScalarPointer();
        int N = imageSize[0]*imageSize[1];
        for (int idx = 0; idx < N; idx++)
        {
            ptr[idx*4 + 0] = data[nChannels*idx+0];
            ptr[idx*4 + 1] = data[nChannels*idx+1];
            ptr[idx*4 + 2] = data[nChannels*idx+2];
            ptr[idx*4 + 3] = 255.0f;
        }
    }
    else if (image->GetScalarType() == VTK_UNSIGNED_CHAR)
    {
        unsigned char *data = (unsigned char *) image->GetScalarPointer();
        int N = imageSize[0]*imageSize[1];
        for (int idx = 0; idx < N; idx++)
        {
            ptr[idx*4 + 0] = data[nChannels*idx+0];
            ptr[idx*4 + 1] = data[nChannels*idx+1];
            ptr[idx*4 + 2] = data[nChannels*idx+2];
            ptr[idx*4 + 3] = 255.0f;
        }
    }
    else
        EXCEPTION1(InvalidVariableException, varname);

    reader->Delete();    
    return var;
}


//****************************************************************************
// Method:  extractXY
//
// Purpose:
//   Parse out the X,Y offsets from a filename.
//
// Programmer:  Dave Pugmire
// Creation:    November  5, 2014
//
// Modifications:
//
//****************************************************************************

static void
extractXY(const string &str, const string &suffix, int &x, int &y)
{
    size_t i0 = str.rfind(suffix);
    size_t i1 = str.rfind("-", i0-1);
    size_t i2 = str.rfind("-", i1-1);
    string yStr = str.substr(i1+1, (i0-i1-1));
    string xStr = str.substr(i2+1, (i1-i2-1));
    
    x = atoi(xStr.c_str());
    y = atoi(yStr.c_str());
}
