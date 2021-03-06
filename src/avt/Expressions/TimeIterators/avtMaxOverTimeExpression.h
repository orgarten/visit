// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                     avtMaxOverTimeExpression.h                            //
// ************************************************************************* //

#ifndef AVT_MAX_OVER_TIME_EXPRESSION_H
#define AVT_MAX_OVER_TIME_EXPRESSION_H

#include <avtTimeIteratorDataTreeIteratorExpression.h>


// ****************************************************************************
//  Class: avtMaxOverTimeExpression
//
//  Purpose:
//      A derived type of time iterator/data tree iterator that calculates the
//      maximum over time.
//
//  Programmer: Hank Childs
//  Creation:   February 16, 2009
//
// ****************************************************************************

class EXPRESSION_API avtMaxOverTimeExpression 
    : public avtTimeIteratorDataTreeIteratorExpression
{
  public:
                              avtMaxOverTimeExpression();
    virtual                  ~avtMaxOverTimeExpression();

    virtual const char       *GetType(void)   
                                  { return "avtMaxOverTimeExpression"; };
    virtual const char       *GetDescription(void)   
                                  { return "Calculating max over time"; };

  protected:
    virtual void              ExecuteDataset(std::vector<vtkDataArray *> &, 
                                             vtkDataArray *, int ts);
    virtual int               NumberOfVariables(void) { return 1; };
};


#endif


