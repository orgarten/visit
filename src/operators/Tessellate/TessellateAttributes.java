// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

package llnl.visit.operators;

import llnl.visit.AttributeSubject;
import llnl.visit.CommunicationBuffer;
import llnl.visit.Plugin;

// ****************************************************************************
// Class: TessellateAttributes
//
// Purpose:
//    Attributes for the Tessellate Operator
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class TessellateAttributes extends AttributeSubject implements Plugin
{
    private static int TessellateAttributes_numAdditionalAtts = 2;

    public TessellateAttributes()
    {
        super(TessellateAttributes_numAdditionalAtts);

        chordError = 0.035;
        mergePoints = true;
    }

    public TessellateAttributes(int nMoreFields)
    {
        super(TessellateAttributes_numAdditionalAtts + nMoreFields);

        chordError = 0.035;
        mergePoints = true;
    }

    public TessellateAttributes(TessellateAttributes obj)
    {
        super(obj);

        chordError = obj.chordError;
        mergePoints = obj.mergePoints;

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return TessellateAttributes_numAdditionalAtts;
    }

    public boolean equals(TessellateAttributes obj)
    {
        // Create the return value
        return ((chordError == obj.chordError) &&
                (mergePoints == obj.mergePoints));
    }

    public String GetName() { return "Tessellate"; }
    public String GetVersion() { return "1.0"; }

    // Property setting methods
    public void SetChordError(double chordError_)
    {
        chordError = chordError_;
        Select(0);
    }

    public void SetMergePoints(boolean mergePoints_)
    {
        mergePoints = mergePoints_;
        Select(1);
    }

    // Property getting methods
    public double  GetChordError() { return chordError; }
    public boolean GetMergePoints() { return mergePoints; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteDouble(chordError);
        if(WriteSelect(1, buf))
            buf.WriteBool(mergePoints);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetChordError(buf.ReadDouble());
            break;
        case 1:
            SetMergePoints(buf.ReadBool());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + doubleToString("chordError", chordError, indent) + "\n";
        str = str + boolToString("mergePoints", mergePoints, indent) + "\n";
        return str;
    }


    // Attributes
    private double  chordError;
    private boolean mergePoints;
}

