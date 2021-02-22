/*

  Copyright (C) 2003-2008  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the MusicXML Library use.
  It shows how to build a memory representation of a score from scratch.

*/

#include <signal.h>

#ifdef WIN32
#include <windows.h>
#endif

#include <fstream>

#include "version.h"

#include "libmusicxml.h" // for xmlErr

#include "enableTracingIfDesired.h"
#ifdef TRACING_IS_ENABLED
  #include "traceOah.h"
#endif

#include "oahOah.h"
#include "generalOah.h"

#include "msdl2msdrOah.h"

#include "msdl2msdrInsiderHandler.h"
#include "msdl2msdrRegularHandler.h"

#include "msdl2guido.h"
#include "msdl2lilypond.h"
#include "msdl2braille.h"
#include "msdl2musicxml.h"


using namespace MusicXML2;

//_______________________________________________________________________________
#ifndef WIN32
static void _sigaction (int signal, siginfo_t *si, void *arg)
{
  cerr << "Signal #" << signal << " catched!" << endl;
  exit (-2);
}

static void catchSignals ()
{
	struct sigaction sa;

  memset (&sa, 0, sizeof(struct sigaction));

  sigemptyset (&sa.sa_mask);

  sa.sa_sigaction = _sigaction;
  sa.sa_flags     = SA_SIGINFO;

  sigaction (SIGSEGV, &sa, NULL);
  sigaction (SIGILL,  &sa, NULL);
  sigaction (SIGFPE,  &sa, NULL);
}
#else
static void catchSignals () {}
#endif

//_______________________________________________________________________________
static void argvElements2stringsVector (
  int argc, char *argv[],
  vector<string>& stringsVector)
{
	for (int i=1; i<argc; ++i) {
		stringsVector.push_back (argv [i]);
	} // for
}

//_______________________________________________________________________________
static bool arguments2optionsVector (
  int argc, char *argv[], optionsVector& theOptionsVector)
{
  // create a strings vector from the elements in argv
	vector<string> stringsVector;

	argvElements2stringsVector (argc, argv, stringsVector);

#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    cerr << "arguments2optionsVector: stringsVector size: " << stringsVector.size() << endl;
    cerr << "==> stringsVector:" << endl;
    for (auto str: stringsVector) {
      cerr << "   " << str << endl;
    } // for
    cerr << endl;
  }
#endif

  // populate the optionsVector
  // ------------------------------------------------------

	string curOption;

	for (unsigned int i = 0; i < stringsVector.size (); ++i) {
	  string str = stringsVector [i];

#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
	  cerr << "--> curOption: \"" << curOption << "\"" << endl;
	  cerr << "--> str      : \"" << str << "\"" << endl;
  }
#endif

		if (curOption.empty ()) {	// wait for option
			if (str [0] == '-') {
			  curOption = str;
      }
			else {
#ifdef TRACING_IS_ENABLED
        if (getTraceOah ()) {
          cerr << "--> str contains an argument: " << str << endl;
        }
#endif
      }

	// JMI ???		  return false;
    }

		else {
			if (str [0] == '-') {
				// option without value
				theOptionsVector.push_back (make_pair (curOption, ""));
				curOption = str;
			}
			else {
			  // option with value
				theOptionsVector.push_back (make_pair(curOption, str));
				curOption = "";
			}
		}
	} // for

	if (curOption.size())
		theOptionsVector.push_back (make_pair (curOption, ""));

	return true;
}

//------------------------------------------------------------------------
void enforceSomeOptions (
  generatorOutputKind theGeneratorOutputKind)
//------------------------------------------------------------------------
{
  /*
    This is a way to enforce options 'permanently'
    independently of the options chosen by the user
  */

  // trace
  // ------------------------------------------------------

/*
  gGlobalTraceOahGroup->setTraceScores ();
  gGlobalTraceOahGroup->setTracePartGroups ();
  gGlobalTraceOahGroup->setTraceParts ();
  gGlobalTraceOahGroup->setTraceStaves ();
  gGlobalTraceOahGroup->setTraceVoices ();
  gGlobalTraceOahGroup->setTraceSegments ();
  gGlobalTraceOahGroup->setTraceMeasures ();
  gGlobalTraceOahGroup->setTraceNotes ();
*/

  // MSR
  // ------------------------------------------------------

/*
  gGlobalMsrOahGroup->setTraceMsr ();
  gGlobalMsrOahGroup->setTraceMsrVisitors ();
  gGlobalMsrOahGroup->setDisplayMsr ();

  gGlobalMsrOahGroup->setTraceMsrDurations ();
*/

  // generate code dependant specific options
  // ------------------------------------------------------

  switch (theGeneratorOutputKind) {
    case k_NoOutput:
      // should not occur
      break;

    case kGuidoOutput:
/*
     gGlobalMusicxmlOahGroup->setTraceDivisions ();
*/
     break;

    case kLilyPondOutput:
      // LPSR
      // ------------------------------------------------------

/*
      gGlobalLpsrOahGroup->setTraceLpsr ();
      gGlobalLpsrOahGroup->setTraceLpsrVisitors ();
      gGlobalLpsrOahGroup->setDisplayLpsr ();
*/

      // lpsr2lilypond
      // ------------------------------------------------------

/*
      gGlobalLpsr2lilypondOahGroup->setLilypondCompileDate (); // JMI NOT OK
      gGlobalLpsr2lilypondOahGroup->setInputLineNumbers ();
*/
      break;

    case kBrailleOutput:
      // BSR
      // ------------------------------------------------------

/*
      gGlobalBsrOahGroup->setTraceBsr ();
      //  gGlobalBsrOahGroup->setTraceBsrVisitors ();
*/

      // bsr2braille
      // ------------------------------------------------------

/*
      gGlobalBsr2brailleOahGroup->
        setBrailleOutputKind (kBrailleOutputUTF8Debug);
*/
      break;

    case kMusicXMLOutput:
      // MusicXML
      // ------------------------------------------------------

/*
      gGlobalMusicxmlOahGroup->setTraceDivisions ();

      gGlobalMxmlTreeOahGroup->setTraceMusicXMLTreeVisitors ();
*/
      break;

    case kMidiOutput:
/*
*/
      break;
  } // switch
}

xmlErr generateCodeFromStandardInput (
  S_oahHandler        handler,
  generatorOutputKind theGeneratorOutputKind)
{
  xmlErr result = kNoErr;

  switch (theGeneratorOutputKind) {
    case k_NoOutput:
      // should not occur, unless the run is a pure help one
      break;

    case kGuidoOutput:
      result =
        msdlStream2guidoWithHandler (
          cin,
          /*
          "Pass 2",
          "Convert the MSR score into a second MSR",
          "Pass 3",
          "Convert the second MSR into an mxmlTree",
          "Pass 4",
          "Convert the mxmlTree into Guido text",
*/
          handler,
          cout,
          cerr);
      break;

    case kLilyPondOutput:
      result =
        msdlStream2lilypondWithHandler (
          cin,
          /*
          "Pass 2",
          "Convert the MSR into an LPSR",
          "Pass 3",
          "Convert the LPSR into LilyPond code",
*/
          handler,
          cout,
          cerr);
      break;

    case kBrailleOutput:
      result =
        msdlStream2brailleWithHandler (
          cin,
          /*
          "Pass 2a",
          "Create the first BSR from the MSR",
          "Pass 2b",
          "Create the finalized BSR from the first BSR",
          "Pass 3",
          "Convert the BSR into Braille music text",
*/
          handler,
          cout,
          cerr);
      break;

    case kMusicXMLOutput:
      result =
        msdlStream2musicxmlWithHandler (
          cin,
          /*
          "Pass 2",
          "Convert the MSR score into a second MSR",
          "Pass 3",
          "Convert the second MSR into an mxmlTree",
          "Pass 4",
          "Convert the mxmlTree into MusicXML text",
*/
          handler,
          cout,
          cerr);
      break;

    case kMidiOutput:
      break;
  } // switch

  return result;
}

xmlErr generateCodeFromAFile (
  string              inputFileName,
  S_oahHandler        handler,
  generatorOutputKind theGeneratorOutputKind)
{
  xmlErr result = kNoErr;

  switch (theGeneratorOutputKind) {
    case k_NoOutput:
      // should not occur, unless the run is a pure help one
      break;

    case kGuidoOutput:
      result =
        msdlFile2guidoWithHandler (
          inputFileName,
          /*
          "Pass 2",
          "Convert the MSR score into a second MSR",
          "Pass 3",
          "Convert the second MSR into an mxmlTree",
          "Pass 4",
          "Convert the mxmlTree into Guido text",
*/
          handler,
          cout,
          cerr);
      break;

    case kLilyPondOutput:
      result =
        msdlFile2lilypondWithHandler (
          inputFileName,
          /*
          "Pass 2",
          "Convert the MSR into an LPSR",
          "Pass 3",
          "Convert the LPSR into LilyPond code",
*/
          handler,
          cout,
          cerr);
      break;

    case kBrailleOutput:
      result =
        msdlFile2brailleWithHandler (
          inputFileName,
          /*
          "Pass 2a",
          "Create the first BSR from the MSR",
          "Pass 2b",
          "Create the finalized BSR from the first BSR",
          "Pass 3",
          "Convert the BSR into Braille music text",
*/
          handler,
          cout,
          cerr);
      break;

    case kMusicXMLOutput:
      result =
        msdlFile2musicxmlWithHandler (
          inputFileName,
          /*
          "Pass 2",
          "Convert the MSR score into a second MSR",
          "Pass 3",
          "Convert the second MSR into an mxmlTree",
          "Pass 4",
          "Convert the mxmlTree into MusicXML text",
*/
          handler,
          cout,
          cerr);
      break;

    case kMidiOutput:
      break;
  } // switch

  return result;
}

//------------------------------------------------------------------------
int main (int argc, char * argv[])
//------------------------------------------------------------------------
{
  // setup signals catching
  // ------------------------------------------------------

// JMI	catchSignals ();

//  setTraceOah (); // JMI TEMP

  // the executable name
  // ------------------------------------------------------

  string executableName = argv [0];

  // are there insider/regular or trace OAH options present?
  // ------------------------------------------------------

  bool insiderOptions = false;
  bool regularOptions = false;

	for (int i = 1; i < argc; ++i) {
	  string argumentAsString = string (argv [i]);

    string argumentWithoutDash = argumentAsString.substr (1);

#ifdef TRACING_IS_ENABLED
    if (
      argumentWithoutDash == K_TRACE_OAH_SHORT_OPTION_NAME
        ||
      argumentWithoutDash == K_TRACE_OAH_LONG_OPTION_NAME
    ) {
      setTraceOah ();
    }
#endif

		if (argumentWithoutDash == K_INSIDER_OPTION_NAME) {
		  insiderOptions = true;
		}
		if (argumentWithoutDash == K_REGULAR_OPTION_NAME) {
		  regularOptions = true;
		}
	} // for

#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    cerr <<
      executableName << " main()" <<
      ", insiderOptions: " << booleanAsString (insiderOptions) <<
      ", regularOptions: " << booleanAsString (regularOptions) <<
      endl;
  }
#endif

  if (insiderOptions && regularOptions) {
    stringstream s;

    s <<
      "options '-insider' and '-regular' cannot be used together";

    oahError (s.str ());
  }

  // here, at most one of insiderOptions and regularOptions is true

  // create the global output and log indented streams
  // ------------------------------------------------------

  createTheGlobalIndentedOstreams (cout, cerr);

  // fetch the theOptionsVector from argc/argv
  // ------------------------------------------------------

	optionsVector theOptionsVector;

	if (! arguments2optionsVector (argc, argv, theOptionsVector)) {
	  // arguments2optionsVector() returned false
    cerr <<
      executableName <<
      " has at least an argument" <<
      endl;

// JMI ???    return 1;
	}

#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    displayOptionsVector (theOptionsVector, cerr);
  }
#endif

  // fetch the generated output kind from theOptionsVector,
  // since the OAH handler should only use the OAH groups needed for it
  // ------------------------------------------------------

  generatorOutputKind
    theGeneratorOutputKind = k_NoOutput;

  for (unsigned int i = 0; i < theOptionsVector.size (); ++i) {
    string optionName  = theOptionsVector [i].first;
    string optionValue = theOptionsVector [i].second;

    string optionNameWithoutDash = optionName.substr (1);

    if (
      optionNameWithoutDash == K_GENERATED_OUTPUT_KIND_SHORT_NAME
        ||
      optionNameWithoutDash == K_GENERATED_OUTPUT_KIND_LONG_NAME
    ) {
      theGeneratorOutputKind =
        generatorOutputKindFromString (optionValue);
    }
    else if (optionNameWithoutDash == K_GENERATED_OUTPUT_KIND_GUIDO_NAME) {
      theGeneratorOutputKind = kGuidoOutput;
    }
    else if (optionNameWithoutDash == K_GENERATED_OUTPUT_KIND_LIlYPOND_NAME) {
      theGeneratorOutputKind = kLilyPondOutput;
    }
    else if (optionNameWithoutDash == K_GENERATED_OUTPUT_KIND_BRAILLE_NAME) {
      theGeneratorOutputKind = kBrailleOutput;
    }
    else if (optionNameWithoutDash == K_GENERATED_OUTPUT_KIND_MUSICXML_NAME) {
      theGeneratorOutputKind = kMusicXMLOutput;
    }
    else if (optionNameWithoutDash == K_GENERATED_OUTPUT_KIND_MIDI_NAME) {
      theGeneratorOutputKind = kMidiOutput;
    }
  } //for


#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    cerr <<
      "==> generatorOutputKind: " <<
      generatorOutputKindAsString (theGeneratorOutputKind) <<
      endl;
  }
#endif

  switch (theGeneratorOutputKind) {
    case k_NoOutput:
      // wait until after help options have been handled
      // before issuing an error message
      break;

    case kGuidoOutput:
    case kLilyPondOutput:
    case kBrailleOutput:
    case kMusicXMLOutput:
      break;

    case kMidiOutput:
      gLogStream <<
        "MIDI output is not implemented yet, sorry" <<
        endl;

      return 0;
      break;
  } // switch

  // the oahHandler, set below
  // ------------------------------------------------------

  S_oahHandler handler;

  try {
    // create an msdl2msdr insider OAH handler
    // ------------------------------------------------------

    S_msdl2msdrInsiderHandler
      insiderOahHandler =
        msdl2msdrInsiderHandler::create (
          executableName,
          executableName + " insider OAH handler with argc/argv",
          theGeneratorOutputKind);

    // the OAH handler to be used, a regular handler is the default
    // ------------------------------------------------------

    if (insiderOptions) {
      // use the insider msdl2msdr OAH handler
      handler = insiderOahHandler;
    }
    else {
      // create a regular msdl2msdr OAH handler
      handler =
        msdl2msdrRegularHandler::create (
          executableName,
          executableName + " regular OAH handler with argc/argv",
          insiderOahHandler,
          theGeneratorOutputKind);
    }

    // handle the command line options and arguments
    // ------------------------------------------------------

    // handle the options and arguments from argc/argv
    oahElementHelpOnlyKind
      helpOnlyKind =
        handler->
          handleOptionsAndArgumentsFromArgcAndArgv (
            argc, argv);

    // have help options been used?
    switch (helpOnlyKind) {
      case kElementHelpOnlyYes:
        return 0; // quit now
        break;
      case kElementHelpOnlyNo:
        // go ahead
        break;
    } // switch
  }
  catch (msgOahException& e) {
    displayException (e, gOutputStream);
    return kInvalidOption;
  }
  catch (exception& e) {
    displayException (e, gOutputStream);
    return kInvalidFile;
  }

  // has the output kind been chosen?
  // ------------------------------------------------------

  switch (theGeneratorOutputKind) {
    case k_NoOutput:
      {
        stringstream s;

        s <<
          executableName <<
          " requires the output kind to be suplied thru one of the options " <<
          "'-" << K_GENERATED_OUTPUT_KIND_SHORT_NAME << "'" <<
          ", -'" << K_GENERATED_OUTPUT_KIND_LONG_NAME << "'" <<
          ", -'" << K_GENERATED_OUTPUT_KIND_GUIDO_NAME << "'" <<
          ", -'" << K_GENERATED_OUTPUT_KIND_LIlYPOND_NAME << "'" <<
          ", -'" << K_GENERATED_OUTPUT_KIND_BRAILLE_NAME << "'" <<
          ", -'" << K_GENERATED_OUTPUT_KIND_MUSICXML_NAME << "'" <<
          " or '" << K_GENERATED_OUTPUT_KIND_MIDI_NAME << "'" <<
          ", unless the run is a pure help one";

        oahError (s.str ());
      }
      break;

    default:
      ;
  } // switch

  // check indentation
  // ------------------------------------------------------

  if (gIndenter != 0) {
    gLogStream <<
      "### " <<
      executableName <<
      " gIndenter value after options ands arguments checking: " <<
      gIndenter.getIndent () <<
      " ###" <<
      endl;

    gIndenter.resetToZero ();
  }

  // display the OAH handler if needed
  // ------------------------------------------------------

  if (gGlobalOahOahGroup->getDisplayOahHandler ()) {
    gLogStream <<
      "The OAH handler contains:" <<
      endl;

    ++gIndenter;
    handler->print (gLogStream);
    --gIndenter;
  }

  if (gGlobalOahOahGroup->getDisplayOahHandlerSummary ()) {
    gLogStream <<
      "The summary of the OAH handler contains:" <<
      endl;

    ++gIndenter;
    handler->printSummary (gLogStream);
    --gIndenter;
  }

  if (gGlobalOahOahGroup->getDisplayOahHandlerEssentials ()) {
    gLogStream <<
      "The essentials of the OAH handler contains:" <<
      endl;

    ++gIndenter;
    handler->printHandlerEssentials (
      gLogStream,
      30); // fieldWidth
    --gIndenter;
  }

  // let's go ahead
  // ------------------------------------------------------

  string
    inputSourceName =
      gGlobalOahOahGroup->getInputSourceName ();

  string
    outputFileName =
      handler->
        fetchOutputFileNameFromTheOptions ();

#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    string separator =
      "%--------------------------------------------------------------";

    gLogStream <<
      executableName << ": " <<
      "inputSourceName = \"" << inputSourceName << "\"" <<
      ", outputFileName = \"" << outputFileName << "\"" <<
      endl <<
      separator <<
      endl;
  }
#endif

/* JMI
  // what if no input source name has been supplied?
  if (! inputSourceName.size ()) {
    if (handler->getOahHandlerFoundAHelpOption ()) {
      return 0; // pure help run
    }
    else {
      stringstream s;

      s <<
        "this is not a pure help run, \"" <<
        executableName <<
        " needs an input file name: " <<
        handler->getHandlerUsage ();

      oahError (s.str ());
    }
  }
*/

  // set the desired options
  // ------------------------------------------------------

  enforceSomeOptions (theGeneratorOutputKind);

  // should we generate Guido, LilyPond, braille music or MusicXML?
  // ------------------------------------------------------


  // has quiet mode been requested?
  // ------------------------------------------------------

  if (gGlobalGeneralOahGroup->getQuiet ()) {
    // disable all trace and display options
    handler->
      enforceHandlerQuietness ();
  }

  // welcome message
  // ------------------------------------------------------

#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTracePasses ()) {
    int
      outputFileNameSize =
        outputFileName.size ();

    gLogStream <<
      "This is \"" << executableName << "\" " << currentVersionNumber () <<
      " from libmusicxml2 v" << musicxmllibVersionStr () <<
      endl;

    gLogStream <<
      "Launching the conversion of ";

    if (inputSourceName == MSDR_STANDARD_INPUT_NAME) {
      gLogStream <<
        "standard input";
    }
    else {
      gLogStream <<
        "\"" << inputSourceName << "\"";
    }

    gLogStream <<
      " to LilyPond" <<
      endl;

    gLogStream <<
      "Time is " <<
      gGlobalGeneralOahGroup->getTranslationDateFull () <<
      endl;

    gLogStream <<
      "LilyPond code will be written to ";
    if (outputFileNameSize) {
      gLogStream <<
        outputFileName;
    }
    else {
      gLogStream <<
        "standard output";
    }
    gLogStream << endl;

    gLogStream <<
      "The command line is:" <<
      endl;

    ++gIndenter;
    gLogStream <<
      handler->
        commandLineWithShortNamesAsString () <<
      endl;
    --gIndenter;

    gLogStream <<
      "or:" <<
      endl;

    ++gIndenter;
    gLogStream <<
      handler->
        commandLineWithLongNamesAsString () <<
      endl;
    --gIndenter;
  }
#endif

  // acknoledge end of command line analysis
  // ------------------------------------------------------

#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTracePasses ()) {
    gLogStream <<
      "The command line options and arguments have been analyzed" <<
      endl;
  }
#endif

  // do the translation
  // ------------------------------------------------------

/*
  // start the clock
  clock_t startClock = clock ();
*/

#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTracePasses ()) {
    string separator =
      "%--------------------------------------------------------------";
    cerr <<
      endl <<
      separator <<
      endl <<
      gTab <<
      "Pass 1: Creating the MSDR score" <<
      endl <<
      separator <<
      endl;
  }
#endif

/*
  // create the MSDR score
  // ------------------------------------------------------

  // the msdl2msdrGenerator
  S_msdl2msdrGenerator
    generator =
      msdl2msdrGenerator::create ();

  // register time spent
  clock_t endClock = clock ();

  timing::gGlobalTiming.appendTimingItem (
    "Pass 1",
    "Create the MSR score",
    timingItem::kMandatory,
    startClock,
    endClock);
*/

  xmlErr err = kNoErr;

  try {
    if (inputSourceName == MSDR_STANDARD_INPUT_NAME) {
      // MSDL data comes from standard input
#ifdef TRACING_IS_ENABLED
      if (getTraceOah ()) {
      cerr << "Reading standard input" << endl;
      }
#endif

      err =
        generateCodeFromStandardInput (
          handler,
          theGeneratorOutputKind);
    }

    else {
      // MSDL data comes from a file
#ifdef TRACING_IS_ENABLED
      if (getTraceOah ()) {
        cerr << "Reading file \"" << inputSourceName << "\"" << endl;
      }
#endif

    err =
      generateCodeFromAFile (
        inputSourceName,
        handler,
        theGeneratorOutputKind);
    }

#ifdef TRACING_IS_ENABLED
    if (getTraceOah ()) {
      if (err != 0) {
        cerr <<
          executableName << ", " <<
          generatorOutputKindAsString (theGeneratorOutputKind) <<
          ", err = " <<
          err <<
          endl;
      }
    }
#endif
  }
  catch (msgException& e) {
    displayException (e, gOutputStream);
    return kInvalidFile;
  }
  catch (std::exception& e) {
    displayException (e, gOutputStream);
    return kInvalidFile;
  }

  // display the input line numbers for which messages have been issued
  // ------------------------------------------------------

  displayWarningsAndErrorsInputLineNumbers ();

  // print timing information
  // ------------------------------------------------------

  if (gGlobalGeneralOahGroup->getDisplayCPUusage ())
    timing::gGlobalTiming.print (gLogStream);

  // check indentation
  // ------------------------------------------------------

  if (gIndenter != 0) {
    gLogStream <<
      "### " << executableName << " gIndenter final value: " <<
      gIndenter.getIndent () <<
      " ###" <<
      endl;

    gIndenter.resetToZero ();
  }

  // over!
  // ------------------------------------------------------

  if (err != kNoErr) {
    gLogStream <<
      "### The generation of " <<
      generatorOutputKindAsString (theGeneratorOutputKind) <<
      " output failed ###" <<
      endl;
  }

  switch (err) {
    case kNoErr:
      return 0;
      break;
    case kInvalidFile:
      return 1;
      break;
    case kInvalidOption:
      return 2;
      break;
    case kUnsupported:
      return 3;
      break;
  } // switch
}

/*
    static unsigned int k_note_counter = 0;

    ++k_note_counter;

    if (k_note_counter > 1) {
      abort ();
    }

*/