// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#ifndef QVISELEVATEWINDOW_H
#define QVISELEVATEWINDOW_H

#include <QvisOperatorWindow.h>
#include <AttributeSubject.h>

class ElevateAttributes;
class QLabel;
class QCheckBox;
class QLineEdit;
class QSpinBox;
class QButtonGroup;
class QvisVariableButton;

// ****************************************************************************
// Class: QvisElevateWindow
//
// Purpose:
//    Defines QvisElevateWindow class.
//
// Notes:      Autogenerated by xml2window.
//
// Programmer: xml2window
// Creation:   omitted
//
// Modifications:
//   Cyrus Harrison, Tue Aug 19 10:58:31 PDT 2008
//   Qt4 Port.
//
// ****************************************************************************

class QvisElevateWindow : public QvisOperatorWindow
{
    Q_OBJECT
  public:
    QvisElevateWindow(const int type,
                         ElevateAttributes *subj,
                         const QString &caption = QString(),
                         const QString &shortName = QString(),
                         QvisNotepadArea *notepad = 0);
    virtual ~QvisElevateWindow();
    virtual void CreateWindowContents();
  protected:
    void UpdateWindow(bool doAll);
    virtual void GetCurrentValues(int which_widget);
  private slots:
    void useXYLimitsChanged(int val);
    void limitsModeChanged(int val);
    void scalingChanged(int val);
    void skewFactorProcessText();
    void minFlagChanged(bool val);
    void minProcessText();
    void maxFlagChanged(bool val);
    void maxProcessText();
    void zeroFlagChanged(bool val);
    void variableChanged(const QString &varName);
  private:
    QButtonGroup *useXYLimits;
    QWidget      *useXYLimitsWidget;
    QButtonGroup *limitsMode;
    QWidget      *limitsModeWidget;
    QButtonGroup *scaling;
    QWidget      *scalingWidget;
    QLineEdit *skewFactor;
    QCheckBox *minFlag;
    QLineEdit *min;
    QCheckBox *maxFlag;
    QLineEdit *max;
    QCheckBox *zeroFlag;
    QvisVariableButton *variable;
    QLabel *useXYLimitsLabel;
    QLabel *limitsModeLabel;
    QLabel *scalingLabel;
    QLabel *skewFactorLabel;
    QLabel *minLabel;
    QLabel *maxLabel;
    QLabel *variableLabel;

    ElevateAttributes *atts;
};



#endif
