/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include <iomanip>

#include "messagesHandling.h"

#include "msrHarmonies.h"

#include "enableTracingIfDesired.h"
#ifdef TRACING_IS_ENABLED
  #include "traceOah.h"
#endif

#include "oahOah.h"
#include "generalOah.h"

#include "msrOah.h"


using namespace std;

namespace MusicXML2
{

//______________________________________________________________________________
S_msrHarmonyDegree msrHarmonyDegree::create (
  int                      inputLineNumber,
  int                      harmonyDegreeValue,
  msrAlterationKind        harmonyDegreeAlterationKind,
  msrHarmonyDegreeTypeKind harmonyDegreeTypeKind)
{
  msrHarmonyDegree* o =
    new msrHarmonyDegree (
      inputLineNumber,
      harmonyDegreeValue,
      harmonyDegreeAlterationKind,
      harmonyDegreeTypeKind);
  assert (o!=0);

  return o;
}

msrHarmonyDegree::msrHarmonyDegree (
  int                      inputLineNumber,
  int                      harmonyDegreeValue,
  msrAlterationKind        harmonyDegreeAlterationKind,
  msrHarmonyDegreeTypeKind harmonyDegreeTypeKind)
    : msrElement (inputLineNumber)
{
  fHarmonyDegreeValue          = harmonyDegreeValue;
  fHarmonyDegreeAlterationKind = harmonyDegreeAlterationKind;
  fHarmonyDegreeTypeKind       = harmonyDegreeTypeKind;

#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTraceHarmonies ()) {
    gLogStream <<
      "Creating harmony degree '" <<
      asString () <<
      "', line " << inputLineNumber <<
      endl;
  }
#endif
}

msrHarmonyDegree::~msrHarmonyDegree ()
{}

void msrHarmonyDegree::setHarmonyDegreeHarmonyUpLink (
  S_msrHarmony harmonyUpLink)
{
  // sanity check
  msgAssert(
    harmonyUpLink != nullptr,
     "harmonyUpLink is null");

  fHarmonyDegreeHarmonyUpLink =
    harmonyUpLink;
}

/* JMI ???
int msrHarmonyDegree::harmonyDegreeAsSemitones () const
{
/ *
  Kind indicates the type of chord. Degree elements
  can then add, subtract, or alter from these
  starting points.
* /

  int result = -1;

  // determine the value for an unaltered degree value
  switch (fHarmonyDegreeValue) {
    case 0:
      result = 0;
      break;
    case 1:
      result = 0;
      break;
    case 2:
      result = 0;
      break;
    case 3:
      result = 0;
      break;
    case 4:
      result = 0;
      break;
    case 5:
      result = 0;
      break;
    case 6:
      result = 0;
      break;
    case 7:
      result = 0;
      break;
    case 8:
      result = 0;
      break;
    case 9:
      result = 0;
      break;
    case 10:
      result = 0;
      break;
    case 11:
      result = 0;
      break;
    case 12:
      result = 0;
      break;
    case 13:
      result = 0;
      break;
  } // switch

  return result;
}
*/

void msrHarmonyDegree::acceptIn (basevisitor* v)
{
  if (gGlobalMsrOahGroup->getTraceMsrVisitors ()) {
    gLogStream <<
      "% ==> msrHarmonyDegree::acceptIn ()" <<
      endl;
  }

  if (visitor<S_msrHarmonyDegree>*
    p =
      dynamic_cast<visitor<S_msrHarmonyDegree>*> (v)) {
        S_msrHarmonyDegree elem = this;

        if (gGlobalMsrOahGroup->getTraceMsrVisitors ()) {
          gLogStream <<
            "% ==> Launching msrHarmonyDegree::visitStart ()" <<
            endl;
        }
        p->visitStart (elem);
  }
}

void msrHarmonyDegree::acceptOut (basevisitor* v)
{
  if (gGlobalMsrOahGroup->getTraceMsrVisitors ()) {
    gLogStream <<
      "% ==> msrHarmonyDegree::acceptOut ()" <<
      endl;
  }

  if (visitor<S_msrHarmonyDegree>*
    p =
      dynamic_cast<visitor<S_msrHarmonyDegree>*> (v)) {
        S_msrHarmonyDegree elem = this;

        if (gGlobalMsrOahGroup->getTraceMsrVisitors ()) {
          gLogStream <<
            "% ==> Launching msrHarmonyDegree::visitEnd ()" <<
            endl;
        }
        p->visitEnd (elem);
  }
}

void msrHarmonyDegree::browseData (basevisitor* v)
{}

string msrHarmonyDegree::harmonyDegreeTypeKindAsString (
  msrHarmonyDegreeTypeKind harmonyDegreeTypeKind)
{
  string result;

  switch (harmonyDegreeTypeKind) {
    case msrHarmonyDegree::kHarmonyDegreeTypeAdd:
      result = "harmonyDegreeTypeAdd";
      break;
    case msrHarmonyDegree::kHarmonyDegreeTypeAlter:
      result = "harmonyDegreeTypeAlter";
      break;
    case msrHarmonyDegree::kHarmonyDegreeTypeSubstract:
      result = "harmonyDegreeTypeSubstract";
      break;
  } // switch

  return result;
}

string msrHarmonyDegree::harmonyDegreeKindAsShortString () const
{
  string result;

  switch (fHarmonyDegreeTypeKind) {
    case msrHarmonyDegree::kHarmonyDegreeTypeAdd:
      result = "degreeAdd";
      break;
    case msrHarmonyDegree::kHarmonyDegreeTypeAlter:
      result = "degreeAlter";
      break;
    case msrHarmonyDegree::kHarmonyDegreeTypeSubstract:
      result = "degreeSubtract";
      break;
  } // switch

  return result;
}

string msrHarmonyDegree::asString () const
{
  stringstream s;

  s <<
    "HarmonyDegree" <<
    ", type: " << harmonyDegreeKindAsShortString () <<
    ", value: " << fHarmonyDegreeValue <<
    ", alteration: " <<
    msrAlterationKindAsString (
      fHarmonyDegreeAlterationKind) <<
    ", line: " << fInputLineNumber;

  return s.str ();
}

void msrHarmonyDegree::print (ostream& os) const
{
  os <<
    asString () <<
    endl;
}

ostream& operator<< (ostream& os, const S_msrHarmonyDegree& elt)
{
  elt->print (os);
  return os;
}

//______________________________________________________________________________
S_msrHarmony msrHarmony::createWithoutVoiceUplink (
  int                      inputLineNumber,
  // no harmonyVoiceUpLink yet
  msrQuarterTonesPitchKind harmonyRootQuarterTonesPitchKind,
  msrHarmonyKind           harmonyKind,
  string                   harmonyKindText,
  int                      harmonyInversion,
  msrQuarterTonesPitchKind harmonyBassQuarterTonesPitchKind,
  rational                 harmonySoundingWholeNotes,
  rational                 harmonyDisplayWholeNotes,
  int                      harmonyStaffNumber,
  msrTupletFactor          harmonyTupletFactor,
  rational                 harmonyWholeNotesOffset)
{
  msrHarmony* o =
    new msrHarmony (
      inputLineNumber,
      nullptr,
      harmonyRootQuarterTonesPitchKind,
      harmonyKind,
      harmonyKindText,
      harmonyInversion,
      harmonyBassQuarterTonesPitchKind,
      harmonySoundingWholeNotes,
      harmonyDisplayWholeNotes,
      harmonyStaffNumber,
      harmonyTupletFactor,
      harmonyWholeNotesOffset);
  assert (o!=0);

  return o;
}

S_msrHarmony msrHarmony::createWithVoiceUplink (
  int                      inputLineNumber,
  S_msrVoice               harmonyVoiceUpLink,
  msrQuarterTonesPitchKind harmonyRootQuarterTonesPitchKind,
  msrHarmonyKind           harmonyKind,
  string                   harmonyKindText,
  int                      harmonyInversion,
  msrQuarterTonesPitchKind harmonyBassQuarterTonesPitchKind,
  rational                 harmonySoundingWholeNotes,
  rational                 harmonyDisplayWholeNotes,
  int                      harmonyStaffNumber,
  msrTupletFactor          harmonyTupletFactor,
  rational                 harmonyWholeNotesOffset)
{
  msrHarmony* o =
    new msrHarmony (
      inputLineNumber,
      harmonyVoiceUpLink,
      harmonyRootQuarterTonesPitchKind,
      harmonyKind,
      harmonyKindText,
      harmonyInversion,
      harmonyBassQuarterTonesPitchKind,
      harmonySoundingWholeNotes,
      harmonyDisplayWholeNotes,
      harmonyStaffNumber,
      harmonyTupletFactor,
      harmonyWholeNotesOffset);
  assert (o!=0);

  return o;
}

msrHarmony::msrHarmony (
  int                      inputLineNumber,
  S_msrVoice               harmonyVoiceUpLink,
  msrQuarterTonesPitchKind harmonyRootQuarterTonesPitchKind,
  msrHarmonyKind           harmonyKind,
  string                   harmonyKindText,
  int                      harmonyInversion,
  msrQuarterTonesPitchKind harmonyBassQuarterTonesPitchKind,
  rational                 harmonySoundingWholeNotes,
  rational                 harmonyDisplayWholeNotes,
  int                      harmonyStaffNumber,
  msrTupletFactor          harmonyTupletFactor,
  rational                 harmonyWholeNotesOffset)
    : msrMeasureElement (
        inputLineNumber),
      fHarmonyTupletFactor (
        harmonyTupletFactor)
{
  /* JMI
  // sanity check
  msgAssert(
    harmonyVoiceUpLink != nullptr,
     "harmonyVoiceUpLink is null");
     */

  // set harmony's voice upLink
  fHarmonyVoiceUpLink =
    harmonyVoiceUpLink;

  fHarmonyRootQuarterTonesPitchKind =
    harmonyRootQuarterTonesPitchKind;

  fHarmonyKind     = harmonyKind;
  fHarmonyKindText = harmonyKindText;

  fHarmonyInversion = harmonyInversion;

  fHarmonyBassQuarterTonesPitchKind =
    harmonyBassQuarterTonesPitchKind;

// JMI  fHarmonySoundingWholeNotes =
  fMeasureElementSoundingWholeNotes =
    harmonySoundingWholeNotes;
  fHarmonyDisplayWholeNotes =
    harmonyDisplayWholeNotes;

  fHarmonyStaffNumber = harmonyStaffNumber;

  fHarmonyWholeNotesOffset = harmonyWholeNotesOffset;

  // handle harmony inversion if any
  /*
    Inversion is a number indicating which inversion is used:
    0 for root position, 1 for first inversion, etc.
  */
  if (fHarmonyInversion > 0) {
    // fetch the harmony intervals
    S_msrHarmonyStructure
      harmonyStructure =
        msrHarmonyStructure::create (
  // JMI        inputLineNumber,
          fHarmonyKind);

    // fetch the bass harmony item for the inversion
    S_msrHarmonyInterval
      bassHarmonyInterval =
        harmonyStructure->
          bassHarmonyIntervalForHarmonyInversion (
            inputLineNumber,
            fHarmonyInversion);

    // fetch the inverted harmony bass semitones pitch
    msrQuarterTonesPitchKind
      invertedHarmonyBassQuarterTonesPitchKind =
        noteAtIntervalFromQuarterTonesPitch (
          inputLineNumber,
          bassHarmonyInterval->getHarmonyIntervalIntervalKind (),
          fHarmonyRootQuarterTonesPitchKind);

    // is this compatible with bass quartertones pitch if specified?
    if (fHarmonyBassQuarterTonesPitchKind != k_NoQuarterTonesPitch_QTP) {
      if (
        invertedHarmonyBassQuarterTonesPitchKind
          !=
        fHarmonyBassQuarterTonesPitchKind
        ) {
        stringstream s;

        s <<
          "inversion '" <<
          fHarmonyInversion <<
          "' is not compatible with bass quaternotes pitch '" <<
          quarterTonesPitchKindAsStringInLanguage (
            fHarmonyBassQuarterTonesPitchKind,
            gGlobalMsrOahGroup->
              getMsrQuarterTonesPitchesLanguageKind ()) <<
          "'";

        msrMusicXMLError (
          gGlobalOahOahGroup->getInputSourceName (),
          inputLineNumber,
          __FILE__, __LINE__,
          s.str ());
      }
    }

    // set the bass quartertones pitch according to the inversion
    fHarmonyBassQuarterTonesPitchKind =
      invertedHarmonyBassQuarterTonesPitchKind;
  }

#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTraceHarmonies ()) {
    gLogStream <<
      "Creating harmony " <<
      asString () <<
      endl;
  }
#endif
}

msrHarmony::~msrHarmony ()
{}

S_msrHarmony msrHarmony::createHarmonyNewbornClone (
  S_msrVoice containingVoice)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTraceHarmonies ()) {
    gLogStream <<
      "Creating a newborn clone of harmony " <<
      asShortString () <<
      ", line " << fInputLineNumber <<
      endl;
  }
#endif

  // sanity check
  msgAssert(
    containingVoice != nullptr,
    "containingVoice is null");

  S_msrHarmony
    newbornClone =
      msrHarmony::createWithVoiceUplink (
        fInputLineNumber,
        containingVoice,
        fHarmonyRootQuarterTonesPitchKind,
        fHarmonyKind,
        fHarmonyKindText,
        fHarmonyInversion,
        fHarmonyBassQuarterTonesPitchKind,
// JMI        fHarmonySoundingWholeNotes,
        fMeasureElementSoundingWholeNotes,
        fHarmonyDisplayWholeNotes,
        fHarmonyStaffNumber,
        fHarmonyTupletFactor,
        fHarmonyWholeNotesOffset);

  // frame JMI ???
  newbornClone->fHarmonyFrame =
    fHarmonyFrame;

  return newbornClone;
}

S_msrHarmony msrHarmony::createHarmonyDeepCopy (
  S_msrVoice containingVoice)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTraceHarmonies ()) {
    gLogStream <<
      "Creating a deep copy of harmony " <<
      asShortString () <<
      ", line " << fInputLineNumber <<
      endl;
  }
#endif

  // sanity check
  msgAssert(
    containingVoice != nullptr,
    "containingVoice is null");

  S_msrHarmony
    harmonyDeepCopy =
      msrHarmony::createWithVoiceUplink (
        fInputLineNumber,
        containingVoice,
        fHarmonyRootQuarterTonesPitchKind,
        fHarmonyKind, fHarmonyKindText,
        fHarmonyInversion,
        fHarmonyBassQuarterTonesPitchKind,
// JMI        fHarmonySoundingWholeNotes,
        fMeasureElementSoundingWholeNotes,
        fHarmonyDisplayWholeNotes,
        fHarmonyStaffNumber,
        fHarmonyTupletFactor,
        fHarmonyWholeNotesOffset);

  return harmonyDeepCopy;
}

void msrHarmony::setHarmonyTupletFactor (
  msrTupletFactor tupletFactor)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTraceHarmonies ()) {
    gLogStream <<
      "Setting the tuplet factor of harmony " <<
      asShortString () <<
      " to " <<
      tupletFactor.asString () <<
      ", line " << fInputLineNumber <<
      endl;
  }
#endif

  fHarmonyTupletFactor = tupletFactor;
}

void msrHarmony::setHarmonyFrame (S_msrFrame frame)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTraceFrames ()) {
    gLogStream <<
      "Setting harmony '" << asShortString ()  << "'" <<
      " frame to '" << frame->asString () << "'" <<
      endl;
  }
#endif

  fHarmonyFrame = frame;
}

void msrHarmony::setHarmonyPositionInMeasure (
  rational positionInMeasure)
{
  // set the harmony position in measure, taking it's offset into account

  // the offset can negative, merely add it
  // this overwrites it with the same value if fHarmonyWholeNotesOffset is null
  rational
    actualPositionInMeasure =
      positionInMeasure
        +
      fHarmonyWholeNotesOffset;
  actualPositionInMeasure.rationalise ();

#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTracePositionsInMeasures ()) {
    gLogStream <<
      "Setting harmony position in measure of " << asString () <<
      " to '" <<
      positionInMeasure <<
      "', harmonyWholeNotesOffset = " <<
      fHarmonyWholeNotesOffset <<
      "', actualPositionInMeasure = " <<
      actualPositionInMeasure <<
      endl;
  }
#endif

  string context =
    "setHarmonyPositionInMeasure()";

  setMeasureElementPositionInMeasure (
    positionInMeasure,
    context);

  if (false) { // JMI
  // compute harmony's position in voice
  S_msrMeasure
    measure =
      fHarmonyNoteUpLink->
        getNoteMeasureUpLink ();

  rational
    positionInVoice =
      measure->
        getMeasurePositionInVoice ()
        +
      positionInMeasure;
  positionInVoice.rationalise ();

  // set harmony's position in voice
  setMeasureElementPositionInVoice (
    positionInVoice,
    context);

  // update current position in voice
  S_msrVoice
    voice =
      measure->
        fetchMeasureVoiceUpLink ();

  voice->
    incrementCurrentPositionInVoice (
      fHarmonyNoteUpLink->getNoteSoundingWholeNotes ());
}
}

void msrHarmony::acceptIn (basevisitor* v)
{
  if (gGlobalMsrOahGroup->getTraceMsrVisitors ()) {
    gLogStream <<
      "% ==> msrHarmony::acceptIn ()" <<
      endl;
  }

  if (visitor<S_msrHarmony>*
    p =
      dynamic_cast<visitor<S_msrHarmony>*> (v)) {
        S_msrHarmony elem = this;

        if (gGlobalMsrOahGroup->getTraceMsrVisitors ()) {
          gLogStream <<
            "% ==> Launching msrHarmony::visitStart ()" <<
            endl;
        }
        p->visitStart (elem);
  }
}

void msrHarmony::acceptOut (basevisitor* v)
{
  if (gGlobalMsrOahGroup->getTraceMsrVisitors ()) {
    gLogStream <<
      "% ==> msrHarmony::acceptOut ()" <<
      endl;
  }

  if (visitor<S_msrHarmony>*
    p =
      dynamic_cast<visitor<S_msrHarmony>*> (v)) {
        S_msrHarmony elem = this;

        if (gGlobalMsrOahGroup->getTraceMsrVisitors ()) {
          gLogStream <<
            "% ==> Launching msrHarmony::visitEnd ()" <<
            endl;
        }
        p->visitEnd (elem);
  }
}

void msrHarmony::browseData (basevisitor* v)
{
  // browse harmony degrees if any
  if (fHarmonyDegreesList.size ()) {
    for (
      list<S_msrHarmonyDegree>::const_iterator i = fHarmonyDegreesList.begin ();
      i != fHarmonyDegreesList.end ();
      ++i
    ) {
      // browse the harmony degree
      msrBrowser<msrHarmonyDegree> browser (v);
      browser.browse (*(*i));
    } // for
  }

  if (fHarmonyFrame) {
    // browse the frame
    msrBrowser<msrFrame> browser (v);
    browser.browse (*fHarmonyFrame);
  }
}

string msrHarmony::asString () const
{
  stringstream s;

  s <<
    "[Harmony" <<
    ", harmonyRootQuarterTonesPitchKind: " <<
    quarterTonesPitchKindAsStringInLanguage (
      fHarmonyRootQuarterTonesPitchKind,
      gGlobalMsrOahGroup->
        getMsrQuarterTonesPitchesLanguageKind ()) <<
    ", harmonyKind: " <<
    msrHarmonyKindAsShortString (fHarmonyKind) <<

    ", harmonySoundingWholeNotes: " <<
    fMeasureElementSoundingWholeNotes <<
    ", harmonyDisplayWholeNotes: " <<
    fHarmonyDisplayWholeNotes <<

    ", harmonyWholeNotesOffset: " <<
    fHarmonyWholeNotesOffset <<
    ", positionInMeasure: " <<
    fMeasureElementPositionInMeasure <<

    ", harmonyKindText: \"" <<
    fHarmonyKindText << "\"";

  s << ", inversion: ";
  if (fHarmonyInversion == K_HARMONY_NO_INVERSION) {
    s << "none";
  }
  else {
    s << fHarmonyInversion;
  }

  if (fHarmonyBassQuarterTonesPitchKind != k_NoQuarterTonesPitch_QTP) {
    s <<
      ", harmonyBassQuarterTonesPitchKind: " <<
    quarterTonesPitchKindAsStringInLanguage (
      fHarmonyBassQuarterTonesPitchKind,
      gGlobalMsrOahGroup->
        getMsrQuarterTonesPitchesLanguageKind ());
  }

  if (fHarmonyDegreesList.size ()) {
    s <<
      ", harmonyDegreesList: [";

    list<S_msrHarmonyDegree>::const_iterator
      iBegin = fHarmonyDegreesList.begin (),
      iEnd   = fHarmonyDegreesList.end (),
      i      = iBegin;

    for ( ; ; ) {
      s << (*i)->asString ();
      if (++i == iEnd) break;
      s << " ";
    } // for
  }

  // print the harmony staff number
  s <<
    ", harmonyStaffNumber: ";
  if (fHarmonyStaffNumber == K_NO_STAFF_NUMBER)
    s << "none";
  else
    s << fHarmonyStaffNumber;

  // print the harmony tuplet factor
  s <<
    ", harmonyTupletFactor: " <<
    fHarmonyTupletFactor.asString ();

  // print the harmony frame
  s << ", harmonyFrame: ";
  if (fHarmonyFrame) {
    s << fHarmonyFrame;
  }
  else {
    s << "none";
  }

  s <<
    ", line " << fInputLineNumber <<
    "]";

  return s.str ();
}

void msrHarmony::print (ostream& os) const
{
  os <<
    "Harmony" <<
     ", line " << fInputLineNumber <<
    endl;

  ++gIndenter;

  const unsigned int fieldWidth = 26;

  os << left <<
    setw (fieldWidth) <<
    "harmonyRoot" << " : " <<
    quarterTonesPitchKindAsStringInLanguage (
      fHarmonyRootQuarterTonesPitchKind,
      gGlobalMsrOahGroup->
        getMsrQuarterTonesPitchesLanguageKind ()) <<
    endl <<
    setw (fieldWidth) <<
    "harmonyKind" << " : " <<
    msrHarmonyKindAsString (fHarmonyKind) <<
    endl <<

    setw (fieldWidth) <<
    "harmonySoundingWholeNotes" << " : " <<
    fMeasureElementSoundingWholeNotes <<
    endl <<
    setw (fieldWidth) <<
    "harmonyDisplayWholeNotes" << " : " <<
    fHarmonyDisplayWholeNotes <<
    endl;

  // print the harmony whole notes offset
  os <<
    setw (fieldWidth) <<
    "harmonyWholeNotesOffset" << " : " << fHarmonyWholeNotesOffset <<
    endl;

  // print the harmony position in measure
  os <<
    setw (fieldWidth) <<
    "positionInMeasure" << " : " << fMeasureElementPositionInMeasure <<
    endl;

  // print the harmony bass position in voice
  os <<
    setw (fieldWidth) <<
    "positionInVoice" << " : " << fMeasureElementPositionInVoice <<
    endl;

  os <<
    setw (fieldWidth) <<
    "harmonyKindText" << " : \"" <<
    fHarmonyKindText <<
    "\"" <<
    endl <<

    setw (fieldWidth) <<
    "harmonyBass" << " : " <<
    quarterTonesPitchKindAsStringInLanguage (
      fHarmonyBassQuarterTonesPitchKind,
      gGlobalMsrOahGroup->
        getMsrQuarterTonesPitchesLanguageKind ()) <<
    endl;

  os <<
    setw (fieldWidth) <<
    "harmonyInversion" << " : ";
  if (fHarmonyInversion == K_HARMONY_NO_INVERSION) {
    os << "none";
  }
  else {
    os << fHarmonyInversion;
  }
  os << endl;

  // print harmony degrees if any
  os <<
    setw (fieldWidth) <<
    "harmonyDegrees";

  if (fHarmonyDegreesList.size ()) {
    os << endl;

    ++gIndenter;

    list<S_msrHarmonyDegree>::const_iterator
      iBegin = fHarmonyDegreesList.begin (),
      iEnd   = fHarmonyDegreesList.end (),
      i      = iBegin;

    for ( ; ; ) {
      os <<
        (*i)->asString ();
      if (++i == iEnd) break;
      os << endl;
    } // for

    os << endl;

    --gIndenter;
  }
  else {
    os <<
      " : " <<
      "none" <<
      endl;
  }

  // print the harmony staff number
  os <<
    setw (fieldWidth) <<
    "harmonyStaffNumber" << " : ";
  if (fHarmonyStaffNumber == K_NO_STAFF_NUMBER) {
    os << "none";
  }
  else {
    os << fHarmonyStaffNumber;
  }
  os << endl;

  // print the harmony tuplet factor
  os <<
    setw (fieldWidth) <<
    "harmonyTupletFactor" << " : " << fHarmonyTupletFactor.asString () <<
    endl;

  // print the harmony frame
  os <<
    setw (fieldWidth) <<
    "harmonyFrame" << " : ";
  if (fHarmonyFrame) {
    os << fHarmonyFrame;
  }
  else {
    os << "none";
  }
  os << endl;

  // print the harmony note uplink
  os <<
    setw (fieldWidth) <<
    "harmonyNoteUpLink" << " : ";
  if (fHarmonyNoteUpLink) {
    os <<
      endl <<
      gTab << fHarmonyNoteUpLink->asString ();
  }
  else {
    os << "none";
  }
  os << endl;

  --gIndenter;
}

ostream& operator<< (ostream& os, const S_msrHarmony& elt)
{
  elt->print (os);
  return os;
}


}