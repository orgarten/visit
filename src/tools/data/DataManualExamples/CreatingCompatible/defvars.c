// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include <silo.h>
#include <stdio.h>
#include <stdlib.h>

void
write_curv3d(DBfile *dbfile)
{
    /* Write a curvilinear mesh. */
    float x[2][3][4] = {
       {{0.,1.,2.,3.},{0.,1.,2.,3.}, {0.,1.,2.,3.}},
       {{0.,1.,2.,3.},{0.,1.,2.,3.}, {0.,1.,2.,3.}}
    };
    float y[2][3][4] = {
       {{0.5,0.,0.,0.5},{1.,1.,1.,1.}, {1.5,2.,2.,1.5}},
       {{0.5,0.,0.,0.5},{1.,1.,1.,1.}, {1.5,2.,2.,1.5}}
    };
    float z[2][3][4] = {
       {{0.,0.,0.,0.},{0.,0.,0.,0.},{0.,0.,0.,0.}},
       {{1.,1.,1.,1.},{1.,1.,1.,1.},{1.,1.,1.,1.}}
    };
    int dims[] = {4, 3, 2};
    int ndims = 3;
    float *coords[3];
    coords[0] = (float*)x;
    coords[1] = (float*)x;
    coords[2] = (float*)x;
    DBPutQuadmesh(dbfile, "quadmesh", NULL, coords, dims, ndims,
                  DB_FLOAT, DB_NONCOLLINEAR, NULL);

    /* Write coordinates also as nodal vars. */
    DBPutQuadvar1(dbfile, "xc", "quadmesh", (float *)x, dims,
                  ndims, NULL, 0, DB_FLOAT, DB_NODECENT, NULL);
    DBPutQuadvar1(dbfile, "yc", "quadmesh", (float *)y, dims,
                  ndims, NULL, 0, DB_FLOAT, DB_NODECENT, NULL);
    DBPutQuadvar1(dbfile, "zc", "quadmesh", (float *)z, dims,
                  ndims, NULL, 0, DB_FLOAT, DB_NODECENT, NULL);
}

#define NX 4
#define NY 3
#define NZ 2

void
write_zonecent_quadvar(DBfile *dbfile)
{
    int i, dims[3], ndims = 3;
    int ncells = (NX-1)*(NY-1)*(NZ-1);
    float *data = (float *)malloc(sizeof(float)*ncells);
    for(i = 0; i < ncells; ++i)
        data[i] = (float)i;
    dims[0] = NX-1; dims[1] = NY-1; dims[2] = NZ-1;
    DBPutQuadvar1(dbfile, "zonal", "quadmesh", data, dims,
                  ndims, NULL, 0, DB_FLOAT, DB_ZONECENT, NULL);
    free(data);
}

void
write_nodecent_quadvar(DBfile *dbfile)
{
    int i, dims[3], ndims = 3;
    int nnodes = NX*NY*NZ;
    float *data = (float *)malloc(sizeof(float)*nnodes);
    for(i = 0; i < nnodes; ++i)
        data[i] = (float)i;
    dims[0] = NX; dims[1] = NY; dims[2] = NZ;
    DBPutQuadvar1(dbfile, "nodal", "quadmesh", data, dims,
                  ndims, NULL, 0, DB_FLOAT, DB_NODECENT, NULL);
    free(data);
}

void
write_defvars(DBfile *dbfile)
{
    const char *names[] = {"velocity", "speed"};
    const char *defs[] = {"{xc,yc,zc}", "magnitude(velocity)"};
    int types[] = {DB_VARTYPE_VECTOR, DB_VARTYPE_SCALAR};
    DBPutDefvars(dbfile, "defvars", 2, (DBCAS_t)names, types, (DBCAS_t)defs, NULL);
}

int
main(int argc, char *argv[])
{
    DBfile *dbfile = NULL;
    /* Open the Silo file */
    dbfile = DBCreate("defvars.silo", DB_CLOBBER, DB_LOCAL,
        "This file has defvars", DB_HDF5);
    if(dbfile == NULL)
    {
        fprintf(stderr, "Could not create Silo file!\n");
        return -1;
    }

    /* Add other Silo calls here. */
    write_curv3d(dbfile);
    write_zonecent_quadvar(dbfile);
    write_nodecent_quadvar(dbfile);
    write_defvars(dbfile);

    /* Close the Silo file. */
    DBClose(dbfile);
    return 0;
}
