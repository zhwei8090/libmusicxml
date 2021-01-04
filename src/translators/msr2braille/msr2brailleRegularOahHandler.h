/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifndef ___msr2brailleRegularOahHandler___
#define ___msr2brailleRegularOahHandler___

#include "msr2brailleInsiderOahHandler.h"

#include "msr2brailleInsiderOahHandler.h"


namespace MusicXML2
{
//_______________________________________________________________________________
class EXP msr2brailleRegularOahHandler : public oahRegularOahHandler
/*
  An msr2braille regular OAH handler can rely on the existence of an insider handler,
  whose creation initialized gGlobalXml2brailleInsiderOahGroup.
  The latter contains all the options values gathered from the user.
*/
{
  public:

    // creation
    // ------------------------------------------------------

    static SMARTP<msr2brailleRegularOahHandler> create (
      string      executableName,
      string      executableAboutInformation,
      string      handlerHeader,
      S_msr2brailleInsiderOahHandler
                  insiderOahHandler);

  protected:

    // constructors/destructor
    // ------------------------------------------------------

    msr2brailleRegularOahHandler (
      string      executableName,
      string      executableAboutInformation,
      string      handlerHeader,
      S_msr2brailleInsiderOahHandler
                  insiderOahHandler);

    virtual ~msr2brailleRegularOahHandler ();

  public:

    // public services
    // ------------------------------------------------------

    void                  checkOptionsAndArgumentsFromArgcAndArgv () const override;

    string                fetchOutputFileNameFromTheOptions () const override
                              {
                                return
                                  fInsiderOahHandler->
                                    fetchOutputFileNameFromTheOptions ();
                              }

    // quiet mode
    void                  enforceHandlerQuietness () override
                              {
                                fInsiderOahHandler->
                                  checkHandlerOptionsConsistency ();
                              }

    // consistency check
    void                  checkHandlerOptionsConsistency () override
                              {
                                fInsiderOahHandler->
                                  checkHandlerOptionsConsistency ();
                              }

  public:

    // visitors
    // ------------------------------------------------------

  public:

    // print
    // ------------------------------------------------------

    void                  print (ostream& os) const;

  private:

    // private services
    // ------------------------------------------------------

    // regular handler groups creation

    void                  createRegularHandlerGroups () override;

    // the groups themselves

    void                  createInformationsRegularGroup ();

    void                  createFilesRegularGroup ();

    void                  createOahRegularGroup ();

    void                  createWarningAndErrorsRegularGroup ();

    void                  createInputRegularGroup ();

    void                  createPresentationRegularGroup ();

    void                  createPartsRegularGroup ();
    void                  createStavesRegularGroup ();
    void                  createVoicesRegularGroup ();

    void                  createTranspositionsRegularGroup ();

    void                  createClefsRegularGroup ();
    void                  createKeysRegularGroup ();
    void                  createTimesRegularGroup ();

    void                  createRestsRegularGroup ();
    void                  createNotesRegularGroup ();

    void                  creatBeamsRegularGroup ();

    void                  createArticulationsRegularGroup ();

    void                  createOrnamentsRegularGroup ();

    void                  createGraceNotesRegularGroup ();

    void                  createChordsRegularGroup ();

    void                  createTiesRegularGroup ();
    void                  createSlursRegularGroup ();
    void                  createLigaturesRegularGroup ();

    void                  createDynamicsRegularGroup ();

    void                  createWedgesRegularGroup ();
    void                  createStringsRegularGroup ();

    void                  createTupletsRegularGroup ();

    void                  createLyricsRegularGroup ();

    void                  createTablaturesRegularGroup ();

    void                  createHarmoniesRegularGroup ();
    void                  createFiguredBassesRegularGroup ();

    void                  createOutputRegularGroup ();

  private:

    // private fields
    // ------------------------------------------------------
};
typedef SMARTP<msr2brailleRegularOahHandler> S_msr2brailleRegularOahHandler;
EXP ostream& operator<< (ostream& os, const S_msr2brailleRegularOahHandler& elt);


}


#endif