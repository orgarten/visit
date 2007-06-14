/*****************************************************************************
*
* Copyright (c) 2000 - 2007, The Regents of the University of California
* Produced at the Lawrence Livermore National Laboratory
* All rights reserved.
*
* This file is part of VisIt. For details, see http://www.llnl.gov/visit/. The
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
*    documentation and/or materials provided with the distribution.
*  - Neither the name of the UC/LLNL nor  the names of its contributors may be
*    used to  endorse or  promote products derived from  this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED.  IN  NO  EVENT  SHALL  THE  REGENTS  OF  THE  UNIVERSITY OF
* CALIFORNIA, THE U.S.  DEPARTMENT  OF  ENERGY OR CONTRIBUTORS BE  LIABLE  FOR
* ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

#ifndef VIEWERRPC_H
#define VIEWERRPC_H
#include <viewerrpc_exports.h>
#include <string>
#include <AttributeSubject.h>

// ****************************************************************************
// Class: ViewerRPC
//
// Purpose:
//    This class contains the attributes for controlling the viewer.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue May 8 16:46:45 PST 2007
//
// Modifications:
//   
// ****************************************************************************

class VIEWER_RPC_API ViewerRPC : public AttributeSubject
{
public:
    enum ViewerRPCType
    {
        CloseRPC,
        DetachRPC,
        AddWindowRPC,
        DeleteWindowRPC,
        SetWindowLayoutRPC,
        SetActiveWindowRPC,
        ClearWindowRPC,
        ClearAllWindowsRPC,
        OpenDatabaseRPC,
        CloseDatabaseRPC,
        ActivateDatabaseRPC,
        CheckForNewStatesRPC,
        CreateDatabaseCorrelationRPC,
        AlterDatabaseCorrelationRPC,
        DeleteDatabaseCorrelationRPC,
        ReOpenDatabaseRPC,
        ReplaceDatabaseRPC,
        OverlayDatabaseRPC,
        OpenComputeEngineRPC,
        CloseComputeEngineRPC,
        AnimationSetNFramesRPC,
        AnimationPlayRPC,
        AnimationReversePlayRPC,
        AnimationStopRPC,
        TimeSliderNextStateRPC,
        TimeSliderPreviousStateRPC,
        SetTimeSliderStateRPC,
        SetActiveTimeSliderRPC,
        AddPlotRPC,
        SetPlotFrameRangeRPC,
        DeletePlotKeyframeRPC,
        MovePlotKeyframeRPC,
        DeleteActivePlotsRPC,
        HideActivePlotsRPC,
        DrawPlotsRPC,
        DisableRedrawRPC,
        RedrawRPC,
        SetActivePlotsRPC,
        ChangeActivePlotsVarRPC,
        AddOperatorRPC,
        AddInitializedOperatorRPC,
        PromoteOperatorRPC,
        DemoteOperatorRPC,
        RemoveOperatorRPC,
        RemoveLastOperatorRPC,
        RemoveAllOperatorsRPC,
        SaveWindowRPC,
        SetDefaultPlotOptionsRPC,
        SetPlotOptionsRPC,
        SetDefaultOperatorOptionsRPC,
        SetOperatorOptionsRPC,
        WriteConfigFileRPC,
        ConnectToMetaDataServerRPC,
        IconifyAllWindowsRPC,
        DeIconifyAllWindowsRPC,
        ShowAllWindowsRPC,
        HideAllWindowsRPC,
        UpdateColorTableRPC,
        SetAnnotationAttributesRPC,
        SetDefaultAnnotationAttributesRPC,
        ResetAnnotationAttributesRPC,
        SetKeyframeAttributesRPC,
        SetPlotSILRestrictionRPC,
        SetViewCurveRPC,
        SetView2DRPC,
        SetView3DRPC,
        ResetPlotOptionsRPC,
        ResetOperatorOptionsRPC,
        SetAppearanceRPC,
        ProcessExpressionsRPC,
        SetLightListRPC,
        SetDefaultLightListRPC,
        ResetLightListRPC,
        SetAnimationAttributesRPC,
        SetWindowAreaRPC,
        PrintWindowRPC,
        ResetViewRPC,
        RecenterViewRPC,
        ToggleMaintainViewModeRPC,
        ToggleMaintainDataModeRPC,
        ToggleBoundingBoxModeRPC,
        ToggleCameraViewModeRPC,
        TogglePerspectiveViewRPC,
        ToggleSpinModeRPC,
        ToggleLockTimeRPC,
        ToggleLockToolsRPC,
        ToggleLockViewModeRPC,
        ToggleFullFrameRPC,
        UndoViewRPC,
        RedoViewRPC,
        InvertBackgroundRPC,
        ClearPickPointsRPC,
        SetWindowModeRPC,
        EnableToolRPC,
        CopyViewToWindowRPC,
        CopyLightingToWindowRPC,
        CopyAnnotationsToWindowRPC,
        CopyPlotsToWindowRPC,
        ClearCacheRPC,
        ClearCacheForAllEnginesRPC,
        SetViewExtentsTypeRPC,
        ClearRefLinesRPC,
        SetRenderingAttributesRPC,
        DatabaseQueryRPC,
        PointQueryRPC,
        LineQueryRPC,
        CloneWindowRPC,
        SetMaterialAttributesRPC,
        SetDefaultMaterialAttributesRPC,
        ResetMaterialAttributesRPC,
        SetPlotDatabaseStateRPC,
        DeletePlotDatabaseKeyframeRPC,
        MovePlotDatabaseKeyframeRPC,
        ClearViewKeyframesRPC,
        DeleteViewKeyframeRPC,
        MoveViewKeyframeRPC,
        SetViewKeyframeRPC,
        OpenMDServerRPC,
        EnableToolbarRPC,
        HideToolbarsRPC,
        HideToolbarsForAllWindowsRPC,
        ShowToolbarsRPC,
        ShowToolbarsForAllWindowsRPC,
        SetToolbarIconSizeRPC,
        SaveViewRPC,
        SetGlobalLineoutAttributesRPC,
        SetPickAttributesRPC,
        ExportColorTableRPC,
        ExportEntireStateRPC,
        ImportEntireStateRPC,
        ImportEntireStateWithDifferentSourcesRPC,
        ResetPickAttributesRPC,
        AddAnnotationObjectRPC,
        HideActiveAnnotationObjectsRPC,
        DeleteActiveAnnotationObjectsRPC,
        RaiseActiveAnnotationObjectsRPC,
        LowerActiveAnnotationObjectsRPC,
        SetAnnotationObjectOptionsRPC,
        SetDefaultAnnotationObjectListRPC,
        ResetAnnotationObjectListRPC,
        ResetPickLetterRPC,
        SetDefaultPickAttributesRPC,
        ChooseCenterOfRotationRPC,
        SetCenterOfRotationRPC,
        SetQueryOverTimeAttributesRPC,
        SetDefaultQueryOverTimeAttributesRPC,
        ResetQueryOverTimeAttributesRPC,
        ResetLineoutColorRPC,
        SetInteractorAttributesRPC,
        SetDefaultInteractorAttributesRPC,
        ResetInteractorAttributesRPC,
        GetProcInfoRPC,
        SendSimulationCommandRPC,
        UpdateDBPluginInfoRPC,
        ExportDBRPC,
        SetTryHarderCyclesTimesRPC,
        OpenClientRPC,
        SuppressQueryOutputRPC,
        SetMeshManagementAttributesRPC,
        SetDefaultMeshManagementAttributesRPC,
        ResetMeshManagementAttributesRPC,
        ResizeWindowRPC,
        MoveWindowRPC,
        MoveAndResizeWindowRPC,
        SetStateLoggingRPC,
        ConstructDDFRPC,
        UpdatePlotInfoAttsRPC,
        RequestMetaDataRPC,
        SetTreatAllDBsAsTimeVaryingRPC,
        MaxRPC
    };

    ViewerRPC();
    ViewerRPC(const ViewerRPC &obj);
    virtual ~ViewerRPC();

    virtual ViewerRPC& operator = (const ViewerRPC &obj);
    virtual bool operator == (const ViewerRPC &obj) const;
    virtual bool operator != (const ViewerRPC &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectWindowArea();
    void SelectDatabase();
    void SelectProgramHost();
    void SelectProgramSim();
    void SelectProgramOptions();
    void SelectFrameRange();
    void SelectVariable();
    void SelectActivePlotIds();
    void SelectActiveOperatorIds();
    void SelectExpandedPlotIds();
    void SelectColorTableName();
    void SelectQueryName();
    void SelectQueryPoint1();
    void SelectQueryPoint2();
    void SelectQueryVariables();
    void SelectStringArg1();
    void SelectStringArg2();
    void SelectDoubleArg1();
    void SelectDoubleArg2();

    // Property setting methods
    void SetRPCType(ViewerRPCType RPCType_);
    void SetWindowLayout(int windowLayout_);
    void SetWindowId(int windowId_);
    void SetWindowMode(int windowMode_);
    void SetWindowArea(const std::string &windowArea_);
    void SetDatabase(const std::string &database_);
    void SetProgramHost(const std::string &programHost_);
    void SetProgramSim(const std::string &programSim_);
    void SetProgramOptions(const stringVector &programOptions_);
    void SetNFrames(int nFrames_);
    void SetStateNumber(int stateNumber_);
    void SetFrameRange(const int *frameRange_);
    void SetFrame(int frame_);
    void SetPlotType(int plotType_);
    void SetOperatorType(int operatorType_);
    void SetVariable(const std::string &variable_);
    void SetActivePlotIds(const intVector &activePlotIds_);
    void SetActiveOperatorIds(const intVector &activeOperatorIds_);
    void SetExpandedPlotIds(const intVector &expandedPlotIds_);
    void SetColorTableName(const std::string &colorTableName_);
    void SetQueryName(const std::string &queryName_);
    void SetQueryPoint1(const double *queryPoint1_);
    void SetQueryPoint2(const double *queryPoint2_);
    void SetQueryVariables(const stringVector &queryVariables_);
    void SetToolId(int toolId_);
    void SetBoolFlag(bool boolFlag_);
    void SetIntArg1(int intArg1_);
    void SetIntArg2(int intArg2_);
    void SetIntArg3(int intArg3_);
    void SetStringArg1(const std::string &stringArg1_);
    void SetStringArg2(const std::string &stringArg2_);
    void SetDoubleArg1(const doubleVector &doubleArg1_);
    void SetDoubleArg2(const doubleVector &doubleArg2_);

    // Property getting methods
    ViewerRPCType      GetRPCType() const;
    int                GetWindowLayout() const;
    int                GetWindowId() const;
    int                GetWindowMode() const;
    const std::string  &GetWindowArea() const;
          std::string  &GetWindowArea();
    const std::string  &GetDatabase() const;
          std::string  &GetDatabase();
    const std::string  &GetProgramHost() const;
          std::string  &GetProgramHost();
    const std::string  &GetProgramSim() const;
          std::string  &GetProgramSim();
    const stringVector &GetProgramOptions() const;
          stringVector &GetProgramOptions();
    int                GetNFrames() const;
    int                GetStateNumber() const;
    const int          *GetFrameRange() const;
          int          *GetFrameRange();
    int                GetFrame() const;
    int                GetPlotType() const;
    int                GetOperatorType() const;
    const std::string  &GetVariable() const;
          std::string  &GetVariable();
    const intVector    &GetActivePlotIds() const;
          intVector    &GetActivePlotIds();
    const intVector    &GetActiveOperatorIds() const;
          intVector    &GetActiveOperatorIds();
    const intVector    &GetExpandedPlotIds() const;
          intVector    &GetExpandedPlotIds();
    const std::string  &GetColorTableName() const;
          std::string  &GetColorTableName();
    const std::string  &GetQueryName() const;
          std::string  &GetQueryName();
    const double       *GetQueryPoint1() const;
          double       *GetQueryPoint1();
    const double       *GetQueryPoint2() const;
          double       *GetQueryPoint2();
    const stringVector &GetQueryVariables() const;
          stringVector &GetQueryVariables();
    int                GetToolId() const;
    bool               GetBoolFlag() const;
    int                GetIntArg1() const;
    int                GetIntArg2() const;
    int                GetIntArg3() const;
    const std::string  &GetStringArg1() const;
          std::string  &GetStringArg1();
    const std::string  &GetStringArg2() const;
          std::string  &GetStringArg2();
    const doubleVector &GetDoubleArg1() const;
          doubleVector &GetDoubleArg1();
    const doubleVector &GetDoubleArg2() const;
          doubleVector &GetDoubleArg2();

    // Enum conversion functions
    static std::string ViewerRPCType_ToString(ViewerRPCType);
    static bool ViewerRPCType_FromString(const std::string &, ViewerRPCType &);
protected:
    static std::string ViewerRPCType_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

    // User-defined methods
    void SetWindowArea(int x, int y, int w, int h);
private:
    int          RPCType;
    int          windowLayout;
    int          windowId;
    int          windowMode;
    std::string  windowArea;
    std::string  database;
    std::string  programHost;
    std::string  programSim;
    stringVector programOptions;
    int          nFrames;
    int          stateNumber;
    int          frameRange[2];
    int          frame;
    int          plotType;
    int          operatorType;
    std::string  variable;
    intVector    activePlotIds;
    intVector    activeOperatorIds;
    intVector    expandedPlotIds;
    std::string  colorTableName;
    std::string  queryName;
    double       queryPoint1[3];
    double       queryPoint2[3];
    stringVector queryVariables;
    int          toolId;
    bool         boolFlag;
    int          intArg1;
    int          intArg2;
    int          intArg3;
    std::string  stringArg1;
    std::string  stringArg2;
    doubleVector doubleArg1;
    doubleVector doubleArg2;

    // Static class format string for type map.
    static const char *TypeMapFormatString;
};

#endif
