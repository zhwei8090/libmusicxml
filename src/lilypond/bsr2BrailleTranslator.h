/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifndef ___bsr2BrailleTranslator___
#define ___bsr2BrailleTranslator___

#include "bsr.h"

#include "bsrOptions.h"


namespace MusicXML2
{

//________________________________________________________________________
class bsr2BrailleTranslator :
  
  public visitor<S_bsrScore>,
  
  public visitor<S_bsrPage>,
  
  public visitor<S_bsrPageHeading>,
  
  public visitor<S_bsrNumber>,
  
  public visitor<S_bsrClef>,
  public visitor<S_bsrKey>,
  public visitor<S_bsrTime>

{
  public:
  
    bsr2BrailleTranslator (
      S_bsrOptions&    bsrOpts,
      indentedOstream& logIOstream,
      indentedOstream& brailleCodeIOstream,
      S_bsrScore       bsrScore);
        
    virtual ~bsr2BrailleTranslator ();

    void generateBrailleCodeFromBsrScore ();

  protected:
        
    virtual void visitStart (S_bsrScore& elt);
    virtual void visitEnd   (S_bsrScore& elt);

    virtual void visitStart (S_bsrPage& elt);
    virtual void visitEnd   (S_bsrPage& elt);

    virtual void visitStart (S_bsrPageHeading& elt);
    virtual void visitEnd   (S_bsrPageHeading& elt);

    virtual void visitStart (S_bsrNumber& elt);
    virtual void visitEnd   (S_bsrNumber& elt);

    virtual void visitStart (S_bsrClef& elt);
    virtual void visitEnd   (S_bsrClef& elt);

    virtual void visitStart (S_bsrKey& elt);
    virtual void visitEnd   (S_bsrKey& elt);

    virtual void visitStart (S_bsrTime& elt);
    virtual void visitEnd   (S_bsrTime& elt);

  private:

    S_bsrScore            fVisitedBsrScore;
                  
    S_bsrOptions          fBsrOptions;

    indentedOstream&      fLogOutputStream;
    indentedOstream&      fBrailleCodeIOstream;
};


}


#endif