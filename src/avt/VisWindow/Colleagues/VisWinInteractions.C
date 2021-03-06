// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                         VisWinInteractions.C                              //
// ************************************************************************* //

#include <VisWinInteractions.h>

#include <InteractorAttributes.h>

#include <VisWindow.h>
#include <VisWindowColleagueProxy.h>

#include <BadInteractorException.h>
#include <VisitHotPointInteractor.h>


// ****************************************************************************
//  Method: VisWinInteractions constructor
//
//  Programmer: Hank Childs
//  Creation:   May 19, 2000
//
//  Modifications:
//
//    Brad Whitlock, Mon Oct 1 10:00:41 PDT 2001
//    Modified the code so it only has a hotpoint interactor.
//
//    Hank Childs, Wed May 29 09:06:05 PDT 2002
//    Initialized spinMode.
//
//    Brad Whitlock, Wed Sep 10 15:28:12 PST 2003
//    Initialized spinModeSuspended.
//
//    Jeremy Meredith, Tue Feb  2 13:43:07 EST 2010
//    Initialize new toolUpdateMode.
//
//    Hank Childs, Sat Mar 13 18:07:25 PST 2010
//    Add "auto" setting to bounding box mode.
//
//    Eric Brugger, Thu Oct 27 13:38:58 PDT 2011
//    Added the ability to enable/disable interaction mode changes to
//    support adding a multi resolution dispaly capability for AMR data.
//
// ****************************************************************************

VisWinInteractions::VisWinInteractions(VisWindowColleagueProxy &c,
                                       VisWindowInteractorProxy &i) 
    : VisWinColleague(c)
{
    mode = NAVIGATE;
    bboxMode = InteractorAttributes::Auto;
    spinMode = false;
    spinModeSuspended = false;
    hotPointInteractor = new VisitHotPointInteractor(i);
    mediator.SetInteractor(hotPointInteractor);
    toolUpdateMode = UPDATE_ONRELEASE;
    enableInteractionModeChanges = true;
}


// ****************************************************************************
//  Method: VisWinInteractions destructor
//
//  Programmer: Hank Childs
//  Creation:   May 19, 2000
//
//  Modifications:
//    Hank Childs, Wed Aug 15 15:05:18 PDT 2001
//    Use VTK's memory management system rather than blindly deleting 
//    interactor styles.
//
//    Brad Whitlock, Mon Oct 1 09:16:19 PDT 2001
//    Changed code since there is now only one interactor style to delete.
//
// ****************************************************************************

VisWinInteractions::~VisWinInteractions()
{
    if (hotPointInteractor != NULL)
    {
        hotPointInteractor->Delete();
        hotPointInteractor = NULL;
    }
}


// ****************************************************************************
//  Method: VisWinInteractions::SetInteractionMode
//
//  Purpose:
//      Sets the interaction mode for the vis window.
//
//  Arguments:
//      m       The new interaction mode.
//
//  Programmer: Hank Childs
//  Creation:   May 30, 2000
//
//  Modifications:
//
//    Hank Childs, Tue Sep 18 10:41:30 PDT 2001
//    Added cases to switch statement to fix compiler warning.
//
//    Kathleen Bonnell, Wed May  8 14:06:50 PDT 2002  
//    Added support for curve mode. 
//
//    Jeremy Meredith, Mon Jan 28 17:59:07 EST 2008
//    Added axis array mode.
//
//    Eric Brugger, Tue Dec  9 14:22:33 PST 2008
//    Added the ParallelAxes window mode.
//
//    Eric Brugger, Mon Nov  5 15:28:10 PST 2012
//    I added the ability to display the parallel axes either horizontally
//    or vertically.
//
// ****************************************************************************

void
VisWinInteractions::SetInteractionMode(INTERACTION_MODE m)
{
    switch (mediator.GetMode())
    {
      case WINMODE_2D:
        Stop2DMode();
        break;
      case WINMODE_3D:
        Stop3DMode();
        break;
      case WINMODE_CURVE:
        StopCurveMode();
        break;
      case WINMODE_AXISARRAY:
        StopAxisArrayMode();
        break;
      case WINMODE_PARALLELAXES:
      case WINMODE_VERTPARALLELAXES:
        StopParallelAxesMode();
        break;
      case WINMODE_NONE:
      default:
        break;
    }

    mode = m;

    switch (mediator.GetMode())
    {
      case WINMODE_2D:
        Start2DMode();
        break;
      case WINMODE_3D:
        Start3DMode();
        break;
      case WINMODE_CURVE:
        StartCurveMode();
        break;
      case WINMODE_AXISARRAY:
        StartAxisArrayMode();
        break;
      case WINMODE_PARALLELAXES:
      case WINMODE_VERTPARALLELAXES:
        StartParallelAxesMode();
        break;
      case WINMODE_NONE:
      default:
        break;
    }
}


// ****************************************************************************
// Method: VisWinInteractions::GetInteractionMode
//
// Purpose: 
//   Returns the current interaction mode.
//
// Programmer: Brad Whitlock
// Creation:   Tue Nov 7 16:12:21 PST 2000
//
// Modifications:
//   
// ****************************************************************************

INTERACTION_MODE
VisWinInteractions::GetInteractionMode() const
{
    return mode;
}


// ****************************************************************************
//  Method: VisWinInteractions::Start2DMode
//
//  Purpose:
//      Sets the appropriate interactor for 2D mode.
//
//  Programmer: Hank Childs
//  Creation:   May 19, 2000
//
//  Modifications:
//    Hank Childs, Wed Aug 15 15:59:43 PDT 2001
//    Don't start up an interaction mode if there are no plots.
//
//    Brad Whitlock, Mon Oct 1 09:20:46 PDT 2001
//    I moved all of the behavior into the hot point interactor.
//
// ****************************************************************************

void
VisWinInteractions::Start2DMode(void)
{
    if(hotPointInteractor != NULL)
    {
        hotPointInteractor->Start2DMode(mode);
    }
}

// ****************************************************************************
//  Method: VisWinInteractions::Start3DMode
//
//  Purpose:
//      Sets the appropriate interactor for 3D mode.
//
//  Programmer: Hank Childs
//  Creation:   May 19, 2000
//
//  Modifications:
//    Hank Childs, Wed Aug 15 15:59:43 PDT 2001
//    Don't start up an interaction mode if there are no plots.
//
//    Brad Whitlock, Mon Oct 1 09:25:34 PDT 2001
//    I moved all of the behavior into the hot point interactor.
//
// ****************************************************************************

void
VisWinInteractions::Start3DMode(void)
{
    if(hotPointInteractor != NULL)
    {
        hotPointInteractor->Start3DMode(mode);
    }
}

// ****************************************************************************
//  Method: VisWinInteractions::StartCurveMode
//
//  Purpose:
//      Sets the appropriate interactor for Curve mode.
//
//  Programmer: Kathleen Bonnell 
//  Creation:   May 8, 2002
//
// ****************************************************************************

void
VisWinInteractions::StartCurveMode(void)
{
    if(hotPointInteractor != NULL)
    {
        hotPointInteractor->StartCurveMode(mode);
    }
}

// ****************************************************************************
//  Method: VisWinInteractions::StartAxisArrayMode
//
//  Purpose:
//      Sets the appropriate interactor for AxisArray mode.
//
//  Programmer: Jeremy Meredith
//  Creation:   January 29, 2008
//
//  Modifications:
//
// ****************************************************************************

void
VisWinInteractions::StartAxisArrayMode(void)
{
    if(hotPointInteractor != NULL)
    {
        hotPointInteractor->StartAxisArrayMode(mode);
    }
}

// ****************************************************************************
//  Method: VisWinInteractions::StartParallelAxesMode
//
//  Purpose:
//      Sets the appropriate interactor for ParallelAxes mode.
//
//  Programmer: Eric Brugger
//  Creation:   December 9, 2008
//
//  Modifications:
//
// ****************************************************************************

void
VisWinInteractions::StartParallelAxesMode(void)
{
    if(hotPointInteractor != NULL)
    {
        hotPointInteractor->StartParallelAxesMode(mode);
    }
}

// ****************************************************************************
//  Method: VisWinInteractions::Stop2DMode
//
//  Purpose:
//      Stops the 2D interactions.
//
//  Programmer: Hank Childs
//  Creation:   May 19, 2000
//
//  Modifications:
//    Brad Whitlock, Mon Oct 1 09:25:34 PDT 2001
//    I moved all of the behavior into the hot point interactor.
//
// ****************************************************************************

void
VisWinInteractions::Stop2DMode()
{
    if(hotPointInteractor != NULL)
    {
        hotPointInteractor->Stop2DMode();
    }
}


// ****************************************************************************
//  Method: VisWinInteractions::Stop3DMode
//
//  Purpose:
//      Stops the 3D interactions.
//
//  Programmer: Hank Childs
//  Creation:   May 19, 2000
//
//  Modifications:
//    Brad Whitlock, Mon Oct 1 09:25:34 PDT 2001
//    I moved all of the behavior into the hot point interactor.
//
//    Kathleen Bonnell, Thu Nov 21 09:04:22 PST 2002 
//    Fixed type ( ->Stop2DMode).
//
// ****************************************************************************

void
VisWinInteractions::Stop3DMode(void)
{
    if(hotPointInteractor != NULL)
    {
        hotPointInteractor->Stop3DMode();
    }
}


// ****************************************************************************
//  Method: VisWinInteractions::StopCurveMode
//
//  Purpose:
//      Stops the Curve interactions.
//
//  Programmer: Kathleen Bonnell 
//  Creation:   May 8, 2002
//
// ****************************************************************************

void
VisWinInteractions::StopCurveMode(void)
{
    if(hotPointInteractor != NULL)
    {
        hotPointInteractor->StopCurveMode();
    }
}


// ****************************************************************************
//  Method: VisWinInteractions::StopAxisArrayMode
//
//  Purpose:
//      Stops the AxisArray interactions.
//
//  Programmer: Jeremy Meredith
//  Creation:   January 29, 2008
//
//  Modifications:
//
// ****************************************************************************

void
VisWinInteractions::StopAxisArrayMode(void)
{
    if(hotPointInteractor != NULL)
    {
        hotPointInteractor->StopAxisArrayMode();
    }
}


// ****************************************************************************
//  Method: VisWinInteractions::StopParallelAxesMode
//
//  Purpose:
//      Stops the ParallelAxes interactions.
//
//  Programmer: Eric Brugger
//  Creation:   December 9, 2008
//
//  Modifications:
//
// ****************************************************************************

void
VisWinInteractions::StopParallelAxesMode(void)
{
    if(hotPointInteractor != NULL)
    {
        hotPointInteractor->StopParallelAxesMode();
    }
}


// ****************************************************************************
//  Method: VisWinInteractions::SetBoundingBoxMode
//
//  Purpose:
//      Sets the bounding box mode.
//
//  Returns:
//
//  Programmer: Brad Whitlock
//  Creation:   Thu Nov 9 15:52:59 PST 2000
//
//  Modifications:
//
//   Jeremy Meredith, Tue Feb  2 13:44:21 EST 2010
//   Turn off continuous tool update mode if we're turning on bbox mode.
//
//   Hank Childs, Sat Mar 13 18:07:25 PST 2010
//   Add "auto" setting to bounding box mode.
//
// ****************************************************************************

void
VisWinInteractions::SetBoundingBoxMode(int val)
{
    bboxMode = val;
    bool doingBBox = false;
    if (val == InteractorAttributes::Always)
        doingBBox = true;
    VisWindow *vw = mediator;
    bool doingSR = vw->GetScalableRendering();
    if (val == InteractorAttributes::Auto && doingSR)
        doingBBox = true;
    if (doingBBox)
    {
        // The continuous tool update mode does not
        // work when bounding box mode is on.
        if (toolUpdateMode == UPDATE_CONTINUOUS)
            toolUpdateMode = UPDATE_ONRELEASE;
    }
    else
    {
        // The continuous tool update mode does 
        // work when bounding box mode is off.
        if (toolUpdateMode == UPDATE_ONRELEASE)
            toolUpdateMode = UPDATE_CONTINUOUS;
    }
}


// ****************************************************************************
//  Method: VisWinInteractions::GetBoundingBoxMode
//
//  Purpose:
//      Determines whether the bounding box mode is enabled or disabled.
//
//  Returns:    true if bounding box mode is enabled, false otherwise.
//
//  Programmer: Hank Childs
//  Creation:   November 8, 2000
//
//  Modifications:
//
//   Hank Childs, Sat Mar 13 18:07:25 PST 2010
//   Add "auto" setting to bounding box mode.
//
// ****************************************************************************

int
VisWinInteractions::GetBoundingBoxMode() const
{
    return bboxMode;
}


// ****************************************************************************
//  Method: VisWinInteractions::SetSpinMode
//
//  Purpose:
//      Sets the spin mode.
//
//  Programmer: Hank Childs
//  Creation:   May 29, 2002
//
// ****************************************************************************

void
VisWinInteractions::SetSpinMode(bool val)
{
    spinMode = val;
}


// ****************************************************************************
//  Method: VisWinInteractions::GetSpinMode
//
//  Purpose:
//      Determines whether the spin mode is enabled or disabled.
//
//  Returns:    true if spin mode is enabled, false otherwise.
//
//  Programmer: Hank Childs
//  Creation:   May 29, 2002
//
// ****************************************************************************

bool
VisWinInteractions::GetSpinMode() const
{
    return spinMode;
}

// ****************************************************************************
//  Method: VisWinInteractions::SetSpinModeSuspended
//
//  Purpose:
//      Sets whether spin mode is temporarily suspended.
//
//  Programmer: Brad Whitlock
//  Creation:   Wed Sep 10 15:29:02 PST 2003
//
// ****************************************************************************

void
VisWinInteractions::SetSpinModeSuspended(bool val)
{
    spinModeSuspended = val;
}


// ****************************************************************************
//  Method: VisWinInteractions::GetSpinModeSuspdended
//
//  Purpose:
//      Determines whether the spin mode is suspended.
//
//  Returns:    true if spin mode is suspended, false otherwise.
//
//  Programmer: Brad Whitlock
//  Creation:   Wed Sep 10 15:59:18 PST 2003
//
// ****************************************************************************

bool
VisWinInteractions::GetSpinModeSuspended() const
{
    return spinModeSuspended;
}


// ****************************************************************************
//  Method: VisWinInteractions::NoPlots
//
//  Purpose:
//      Makes the current interactor be the NULL interactor, in response to
//      having no plots.
//
//  Programmer: Hank Childs
//  Creation:   August 15, 2001
//
//  Modifications:
//    Brad Whitlock, Mon Oct 1 09:25:34 PDT 2001
//    I moved all of the behavior into the hot point interactor.
//
//    Eric Brugger, Thu Oct 27 13:38:58 PDT 2011
//    Added the ability to enable/disable interaction mode changes to
//    support adding a multi resolution dispaly capability for AMR data.
//
// ****************************************************************************

void
VisWinInteractions::NoPlots(void)
{
    if (enableInteractionModeChanges)
    {
        if(hotPointInteractor != NULL)
        {
            hotPointInteractor->SetNullInteractor();
        }
    }
}


// ****************************************************************************
//  Method: VisWinInteractions::HasPlots
//
//  Purpose:
//      Notifies the module that we now have plots in the window.  This
//      sends the interaction mode back in, kickstarting it off with the
//      null interactor.
//
//  Programmer: Hank Childs
//  Creation:   August 15, 2001
//
//  Modifications:
//    Kathleen Bonnell, Thu May 16 08:54:34 PDT 2002  
//    Lineout not valid for 3D, so test and set mode to Navigate if necessary. 
//
//    Jeremy Meredith, Thu Jan 31 14:41:50 EST 2008
//    Added new AxisArray window mode; no lineout support for it.
//
//    Eric Brugger, Tue Dec  9 14:22:33 PST 2008
//    Added the ParallelAxes window mode.
//
//    Eric Brugger, Thu Oct 27 13:38:58 PDT 2011
//    Added the ability to enable/disable interaction mode changes to
//    support adding a multi resolution dispaly capability for AMR data.
//
//    Eric Brugger, Mon Nov  5 15:28:10 PST 2012
//    I added the ability to display the parallel axes either horizontally
//    or vertically.
//
// ****************************************************************************

void
VisWinInteractions::HasPlots(void)
{
    if (enableInteractionModeChanges)
    {
        if (!((mediator.GetMode() == WINMODE_3D
               || mediator.GetMode() == WINMODE_AXISARRAY
               || mediator.GetMode() == WINMODE_PARALLELAXES
               || mediator.GetMode() == WINMODE_VERTPARALLELAXES) &&
              mode == LINEOUT))
        {
            SetInteractionMode(mode);
        }
        else 
        {
            SetInteractionMode(NAVIGATE);
        }
    }
}


// ****************************************************************************
//  Method: VisWinInteractions::SetToolUpdateMode
//
//  Purpose:
//      Sets tool update mode.
//
//  Programmer: Jeremy Meredith
//  Creation:   February  2, 2010
//
// ****************************************************************************

void
VisWinInteractions::SetToolUpdateMode(TOOLUPDATE_MODE m)
{
    toolUpdateMode = m;
}


// ****************************************************************************
//  Method: VisWinInteractions::GetToolUpdateMode
//
//  Purpose:
//      Returns the tool update mode.
//
//  Programmer: Jeremy Meredith
//  Creation:   February  2, 2010
//
// ****************************************************************************

TOOLUPDATE_MODE
VisWinInteractions::GetToolUpdateMode() const
{
    return toolUpdateMode;
}


// ****************************************************************************
//  Method: VisWinInteractions::SetEnableInteractionModeChanges
//
//  Purpose:
//      Sets the enable interaction mode changes flag.
//
//  Programmer: Eric Brugger
//  Creation:   Thu Oct 27 13:38:58 PDT 2011
//
// ****************************************************************************

void
VisWinInteractions::SetEnableInteractionModeChanges(bool val)
{
    enableInteractionModeChanges = val;
}


// ****************************************************************************
//  Method: VisWinInteractions::GetEnableInteractionModeChanges
//
//  Purpose:
//      Gets the enable interaction mode changes flag.
//
//  Programmer: Eric Brugger
//  Creation:   Thu Oct 27 13:38:58 PDT 2011
//
// ****************************************************************************

bool
VisWinInteractions::GetEnableInteractionModeChanges() const
{
    return enableInteractionModeChanges;
}
