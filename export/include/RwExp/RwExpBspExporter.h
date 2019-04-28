
#ifndef RWEXPBSPEXPORTER_H
#define RWEXPBSPEXPORTER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "RwCommUserData.h"

#include "RwExp.h"
#include "RwExpExporter.h"
#include "RwExpExportOptions.h"
#include "RwExpBspGeometry.h"
#include "RwExpPolygonLimitAction.h"

struct RwCommEdge;
struct RwExpMeshInks;

struct RWEXP_API RwExpPrimEdges
{
    vector<RwCommEdge>  m_edges;
    int                 m_primIndex;
    int                 m_meshIndex;
};

// =============================================================================
// ----------------------  RwExpUserDataSectorMap CLASS  -----------------------
// =============================================================================

class RWEXP_API RwExpUserDataSectorMap
{
public:
    RwExpUserDataSectorMap();
	virtual ~RwExpUserDataSectorMap();
    
    bool operator==(const RwExpUserDataSectorMap &other) const;

    RpWorldSector   *m_sector;
    int             *m_vertexMap;
    int             *m_polygonMap;
};

typedef list<RwExpUserDataSectorMap *>              RwExpUserDataSectorMapList;
typedef list<RwExpUserDataSectorMap *>::iterator    RwExpUserDataSectorMapListIt;

// =============================================================================
// -------------------------  RwExpBspExporter CLASS  --------------------------
// =============================================================================

class RwCommAnimatable;
class RwCommTransform;

const RwCommType RwExpBspExporterType("RwExpBspExporter");


/**

   \ingroup exporters

    This is the class responsible for exporting the RpWorld structure.
    The class is derived from RwExpExporter. It is constructed with the following default exporter objects
    (RwCommExportObject), assigned to the following RwCommObjects :


<TABLE BORDER CELLSPACING=2 BORDERCOLOR="#000000" CELLPADDING=7 WIDTH=406>
<TR>
    <TD WIDTH="47%" VALIGN="MIDDLE" BGCOLOR="#ffffff">
    <B><P>RWCOMMOBJECT </B></TD>
    <TD WIDTH="53%" VALIGN="MIDDLE" BGCOLOR="#ffffff">
    <B><P>RWCOMMEXPORTOBJECT</B></TD>
</TR>
<TR>
    <TD WIDTH="47%" VALIGN="TOP" HEIGHT=11>
    <P>RwCommGeometryType</TD>
    <TD WIDTH="53%" VALIGN="TOP" HEIGHT=11>
    <P>RwExpBspGeometry</TD>
</TR>
<TR>
    <TD WIDTH="47%" VALIGN="TOP" HEIGHT=11>
    <P>RwCommShader</TD>
    <TD WIDTH="53%" VALIGN="TOP" HEIGHT=11>
    <P>RwExpRpMaterial</TD>
</TR>
<TR>
    <TD WIDTH="47%" VALIGN="TOP" HEIGHT=11>
    <P>RwCommTexture</TD>
    <TD WIDTH="53%" VALIGN="TOP" HEIGHT=11>
    <P>RwExpRwTexture</TD>
</TR>
</TABLE>
*
*
* In addition, the RwExpBspExporter is constructed with the following default traverse actions:

<TABLE BORDER CELLSPACING=2 BORDERCOLOR="#000000" CELLPADDING=7 WIDTH=548>
<TR>
    <TD WIDTH="45%" VALIGN="MIDDLE" BGCOLOR="#ffffff">
    <B><P>Traverse action</B></TD>
    <TD WIDTH="55%" VALIGN="MIDDLE" BGCOLOR="#ffffff">
    <B><P>Description</B></TD>
</TR>
<TR>
    <TD WIDTH="45%" VALIGN="TOP" HEIGHT=11>
    <P>RwExpInitAnimatables</TD>
    <TD WIDTH="55%" VALIGN="TOP" HEIGHT=11>
    <P>Goes over all animatables in the traverse list and initializes their animation frame to the user supplied frame value. </TD>
</TR>
<TR><TD WIDTH="45%" VALIGN="TOP" HEIGHT=11>
    <P>RwExpTessellateAction</TD>
    <TD WIDTH="55%" VALIGN="TOP" HEIGHT=11>
    <P>Tessellates all patches in the traverse list. </TD>
</TR>
<TR>
    <TD WIDTH="45%" VALIGN="TOP" HEIGHT=11>
    <P>RwExpOptimizeShaders</TD>
    <TD WIDTH="55%" VALIGN="TOP" HEIGHT=11>
    <P>Removes redundant shaders from the traverse list.</TD>
</TR>
<TR>
    <TD WIDTH="45%" VALIGN="TOP" HEIGHT=11>
    <P>RwExpSetPolygonLimitAction</TD>
    <TD WIDTH="55%" VALIGN="TOP" HEIGHT=11>
    <P>Counts number of primitives per geometry, for progress bar use.</TD>
</TR>
<TR>
    <TD WIDTH="45%" VALIGN="TOP" HEIGHT=11>
    <P>RwExpCalcBBoxAction</TD>
    <TD WIDTH="55%" VALIGN="TOP" HEIGHT=11>
    <P>Calculates the traverse list�s bounding box.</TD>
</TR>
<TR>
    <TD WIDTH="45%" VALIGN="TOP" HEIGHT=11>
    <P>RwExpSelectionFilter</TD>
    <TD WIDTH="55%" VALIGN="TOP" HEIGHT=11>
    <P>Removes all unselected objects from the traverse list.</TD>
</TR>
<TR>
    <TD WIDTH="45%" VALIGN="TOP" HEIGHT=11>
    <P>RwExpExportAction</TD>
    <TD WIDTH="55%" VALIGN="TOP" HEIGHT=11>
    <P>Performs the actual export action</TD>
</TR>
<TR>
    <TD WIDTH="45%" VALIGN="TOP" HEIGHT=11>
    <P>RwExpBuildWorld</TD>
    <TD WIDTH="55%" VALIGN="TOP" HEIGHT=11>
    <P>Builds the final RpWorld using the RtWorldImport toolkit.</TD>
    </TR>
    <TR><TD WIDTH="45%" VALIGN="TOP" HEIGHT=11>
    <P>RwExpCheckNodesAction</TD>
    <TD WIDTH="55%" VALIGN="TOP" HEIGHT=11>
    <P>Performs per platform object checks.</TD>
</TR>
</TABLE>
*/


class RWEXP_API RwExpBspExporter  : public RwExpExporter
{
public:
	RwExpBspExporter();
	virtual ~RwExpBspExporter();

    //RwCommObject method
    virtual RwCommType	                GetType() const                 {return RwExpBspExporterType;}
    
    static RwCommUserDataCollection     &GetWorldUserDataCollection()   {return m_worldUserDataColl;}
    static vector<RwExpMeshInks>        &GetWorldMeshInks()             {return m_vWorldMeshInks;}
    static vector<RwExpPrimEdges>       &GetRwToAppPrimEdgesMap()       {return m_rwToAppPrimEdgesMap;}
    static vector<vector<RwV3d>*>       &GetAppVertToRwVertMeshMap()    {return m_appVertToRwVertMeshMap;}

protected:
    // RwExpExporter methods.
    virtual RwCommError     PreExport(RwCommScene* pScene, const vector<RwCommTransform*>& vSelection); 
    virtual RwCommError     PostExport(RwCommScene* pScene, const vector<RwCommTransform*>& vSelection);
    virtual void            PreAction(RwExpTraverseAction* pAction);
    virtual RwCommError     BuildTraverseList(vector<RwExpTraverseObject>& vTraverseList, RwCommScene* pScene);
    virtual RwCommError     TraverseTransforms(RwCommTransform* pTransform, RwCommTransform* pParent,
                                                vector<RwExpTraverseObject>& vTraverseList);
    virtual RwCommError     TraverseShape(RwCommShape* pShape, vector<RwExpTraverseObject>  &vTraverseList);

    /** Set the tri strip method for the world's geometry. Users can override this method and assign their own
    custom tri stripping method.*/
    virtual RwCommError     SetTriStripMethod();
    
    // Callback functions.
    static RwBool           SetVertexCB(void **pUserdata, RpWorldSector *sector, RwInt32 index);
    static RwBool           SetPolygonCB(void **pUserdata, RpWorldSector *sector, RwInt32 index);
    static RwBool           InterpVertexCB(void **pUserdataDst, void **pUserdata1, void **pUserdata2, RwReal delta);
    static RpWorldSector    *WorldSectorHasMaterialFX(RpWorldSector *sector, void *pData);
    static RpMesh           *MeshCheckMaterialFX(RpMesh *mesh, RpMeshHeader *meshHeader, void *pData);
    static RpWorldSector    *WorldSectorHasNormalMap(RpWorldSector *sector, void *pData);
    static RpMesh           *MeshCheckNormalMap(RpMesh *mesh, RpMeshHeader *meshHeader, void *pData);
    static RpWorldSector    *AddUserDataToWorldSector(RpWorldSector *worldSector, void *callBackData);
    static RpWorldSector    *AddToonDataToWorldSector(RpWorldSector *worldSector, void *callBackData);
    static void             ClearStaticData();
    static RpWorldSector    *GetNumMeshIndices(RpWorldSector *sector, void *pData);

    // Override render pipelines
    virtual RwCommError     OverridePipes(RpWorld *world);

    // Stats
    void                    PrintStats(RpWorld *world);

protected:
    vector<RwCommTransform*>            m_vSelection;
    RtWorldImport                       *m_importWorld;
    
    static RwCommUserDataCollection     m_worldUserDataColl;
    static RwExpUserDataSectorMapList   m_sectorMapList;
    static vector<RwExpMeshInks>        m_vWorldMeshInks;
    static vector<RwExpPrimEdges>       m_rwToAppPrimEdgesMap;
    static vector<vector<RwV3d>*>       m_appVertToRwVertMeshMap;
};


#endif // RWEXPBSPEXPORTER_H
