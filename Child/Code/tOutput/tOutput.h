/*************************************************************************\
**
**  tOutput.h: Header file for classes tOutput and tLOutput
**
**  The tOutput class handles output of triangulated mesh data to
**  files. The class handles only output of mesh data (nodes,
**  edges, and triangles); output of additional data (e.g., water or
**  sediment flow) can be handled by classes derived from tOutput.
**
**  tOutput provides functions to open and initialize output files and
**  write output at a specified time in a simulation. The class is
**  templated in order to allow for a pointer to a templated
**  tMesh object.
**
**  To handle output of application-specific data, one can create a
**  class inherited from tOutput and overload its virtual
**  WriteNodeData function to output the additional data.
**
**  Note that in the present version, the files tOutput.h/.cpp
**  contain the inherited class tLOutput which handles output for
**  the CHILD model. In the future, such inherited classes will be
**  kept in separate files to preserve the generality of tOutput.
**
**  Recent modifications:
**    - 1/00: GT added vegofs for output of vegetation cover
**    - 6/01: GT added chanwidthofs for output of channel widths
**      (only when non-regime hydraulic geometry model used)
**
**  $Id: tOutput.h,v 1.29 2002-05-01 14:48:30 arnaud Exp $
\*************************************************************************/

#ifndef TOUTPUT_H
#define TOUTPUT_H

#include <iostream.h>
#include <string.h>
#include "../tAssert.h"
#include "../errors/errors.h"
#include "../tMeshList/tMeshList.h"
#include "../MeshElements/meshElements.h"
#include "../tInputFile/tInputFile.h"
#include "../tMesh/tMesh.h"

#define kMaxNameSize 80

/**************************************************************************\
** class tOutput **********************************************************
**
** Class tOutput handles output of mesh data (nodes, edges, and
** triangles). The constructor opens and initializes the files;
** the WriteOutput function writes basic mesh data and calls the
** virtual function WriteNodeData to write any application-specific
** data.
**
** Notes:
**  - WriteNodeData and CreateAndOpenFile could be protected rather
**    than public.
**
\**************************************************************************/
template< class tSubNode >
class tOutput
{
  tOutput(const tOutput&);
  tOutput& operator=(const tOutput&);
public:
    tOutput( tMesh<tSubNode> * meshPtr, tInputFile &infile );
    virtual ~tOutput() {}
    void WriteOutput( double time );
    void WriteTSOutput( double time );
    virtual void WriteNodeData( double time );
    void CreateAndOpenFile( ofstream * theOFStream, const char * extension );

protected:
    tMesh<tSubNode> * m;          // ptr to mesh (for access to nodes, etc)
    char baseName[kMaxNameSize];  // name of output files
    ofstream nodeofs;             // output file for node data
    ofstream edgofs;              // output file for edge data
    ofstream triofs;              // output file for triangle data
    ofstream zofs;                // output file for node "z" data
    ofstream vaofs;               // output file for Voronoi areas    
    ofstream volsofs;             // catchment volume
    ofstream dvolsofs;
    ofstream tareaofs;            // total voronoi area of catchment
    double mdLastVolume;   // these 4 SHOULD BE MOVED TO ANOTHER CLASS!!

};


/**************************************************************************\
** class tLOutput *********************************************************
**
** Class tLOutput handles application-specific data for the CHILD model.
** The constructor creates additional output files, and the overloaded
** WriteNodeData function writes the data to files.
** (TODO: move to separate file)
**
** Modifications:
**  - 2/02 added output streams tauofs and qsofs for shear stress and
**    sed flux, resp. (GT)
**
\**************************************************************************/
template< class tSubNode >
class tLOutput : public tOutput<tSubNode>
{
  tLOutput(const tLOutput&);
  tLOutput& operator=(const tLOutput&);
public:
    tLOutput( tMesh<tSubNode> * meshPtr, tInputFile &infile );
    void WriteNodeData( double time );  
    void WriteTSOutput();
    int NodeCount();
    int OptTSOutput();
   

private:
    ofstream drareaofs;  // Drainage areas
    ofstream netofs;     // Downstream neighbor IDs
    ofstream slpofs;     // Slopes in the direction of flow
    ofstream qofs;       // Discharge
    ofstream layofs;     // Layer info
    ofstream texofs;     // Texture info
    ofstream vegofs;     // Vegetation cover %
    ofstream flowdepofs; // Flow depth
    ofstream vegcovofs;  // Catchment vegetation cover %
    ofstream chanwidthofs; // Channel width
    ofstream flowpathlenofs;  // Flow path length
    ofstream tauofs;     // Shear stress
    ofstream qsofs;      // Sed flux
    int optTSOutput;     // temp

   int counter;
};


/*
** The following is designed to allow for compiling under the Borland-style
** template instantiation used by the Linux/GNU and Solaris versions of GCC
*/
#ifdef __GNUC__
#include "tOutput.cpp"
#endif



#endif
