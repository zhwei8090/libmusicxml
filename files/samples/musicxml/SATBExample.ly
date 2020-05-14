\version "2.19.83"

% Generated by xml2ly 0.93 from "multistaff/SATBExample.xml"
% on Monday 2020-02-10 @ 16:58:27 CET

% The translation command line was:
%   xml2ly '-xi' '-aofn' '-dmsr' '-dpg' '--dlpsr' '-abn' '-lpcd' '-rbracks' '-mssp' '1cm' 'multistaff/SATBExample.xml'
% or, with long option names:
%  xml2ly multistaff/SATBExample.xml -xml2ly-infos -auto-output-file-name -display-msr -display-partgroups -display-lpsr -all-bar-numbers -lilypond-compile-date -repeat-brackets -markup-system-spacing.padding '1 cm'
% or, with short option names:
%   xml2ly multistaff/SATBExample.xml -xi -aofn -dmsr -dpg -dlpsr -abn -lpcd -rbracks -mssp '1 cm'

% Comment or adapt next line as needed (default is 20)
#(set-global-staff-size 20)


% Scheme function(s): "date & time"
% A set of functions to obtain a source file's modification time.

#(define comml           (object->string (command-line)))
#(define loc             (+ (string-rindex comml #\space ) 2))
#(define commllen        (- (string-length comml) 2))
#(define filen           (substring comml loc commllen))
#(define siz             (object->string (stat:size (stat filen))))
#(define ver             (object->string (lilypond-version)))
#(define dat             (strftime "%d/%m/%Y" (localtime (current-time))))
#(define tim             (strftime "%H:%M:%S" (localtime (current-time))))
#(define modTime         (stat:mtime (stat filen)))
#(define modTimeAsString (strftime "%d/%m/%Y - %H:%M:%S" (localtime modTime)))


\header {
  software           = "Frescobaldi 2.19.0"
  encodingDate       = "2016-10-04"
}

\paper {
  paper-height                   = 297\mm
  paper-width                    = 210\mm
  
  %left-margin                    = 0.0\mm
  %right-margin                   = 0.0\mm
  %top-margin                     = 0.0\mm
  %bottom-margin                  = 0.0\mm
  
  %horizontal-shift               = 0.0\mm
  %indent                         = 0.0\mm
  %short-indent                   = 0.0\mm
  
  markup-system-spacing.padding  = 1\cm
  %between-system-space           = 0.0\mm
  %page-top-space                 = 0.0\mm
  
  %page-count                     = -1
  %system-count                   = -1
  
  oddHeaderMarkup                = \markup {
    \fill-line {
      \on-the-fly \not-first-page {
        \fromproperty #'page:page-number-string
        " "
        \fromproperty #'header:title
        " "
        \fromproperty #'header:subtitle
      }
    }
  }

  evenHeaderMarkup               = \markup {
    \fill-line {
      \on-the-fly \not-first-page {
        \fromproperty #'page:page-number-string
        " "
        \fromproperty #'header:title
        " "
        \fromproperty #'header:subtitle
      }
    }
  }

  oddFooterMarkup                = \markup {
    \tiny
    \column {
      \fill-line {
        #(string-append
"Music generated from MusicXML by xml2ly 0.93 and engraved by LilyPond " (lilypond-version))
      }
      \fill-line { \italic { \modTimeAsString }}
    }
  }

  evenFooterMarkup               = ""
}

\layout {
  \context {
    \Score
    autoBeaming = ##f % to display tuplets brackets
  }
  \context {
    \Voice
  }
  \context {
    \Score
    % defaultBarType = #"!"
    startRepeatType = #"[|:"
    endRepeatType = #":|]"
    doubleRepeatType = #":|][|:"
  }
}

% Pick your choice from the next two lines as needed
myBreak = { \break }
%myBreak = { }

% Pick your choice from the next two lines as needed
myPageBreak = { \pageBreak }
%myPageBreak = { }

Part_POne_Staff_One_Voice_One = \absolute {
  \language "nederlands"
  \set Score.barNumberVisibility = #all-bar-numbers-visible
  \override Score.BarNumber.break-visibility = ##(#f #t #t)
  
  \partial 4
  \key c \major
  \time 4/4
  
  \clef "treble"
  \tempo \markup {
    \concat {
       \smaller \general-align #Y #DOWN \note #"4" #UP
      " = "
      80
    }
  }
  c''4 | % 1
  \barNumberCheck #1
  e''4. e''8 g''4 g'' | % 2
  \barNumberCheck #2
a''4 a'' g'' }

Part_POne_Staff_One_Voice_Two = \absolute {
  \language "nederlands"
  \set Score.barNumberVisibility = #all-bar-numbers-visible
  \override Score.BarNumber.break-visibility = ##(#f #t #t)
  
  \partial 4
  \key c \major
  \time 4/4
  
  \clef "treble"
  c''4 | % 1
  \barNumberCheck #1
  c''4. c''8 e''4 e'' | % 2
  \barNumberCheck #2
f''4 f'' e'' }

Part_PTwo_Staff_One_Voice_One = \absolute {
  \language "nederlands"
  \set Score.barNumberVisibility = #all-bar-numbers-visible
  \override Score.BarNumber.break-visibility = ##(#f #t #t)
  
  \partial 4
  \key c \major
  \time 4/4
  
  \clef "bass"
  e'4 | % 1
  \barNumberCheck #1
  g'4. g'8 c''4. b'8 | % 2
  \barNumberCheck #2
a'8 b' c'' d'' e''4 }

Part_PTwo_Staff_One_Voice_Two = \absolute {
  \language "nederlands"
  \set Score.barNumberVisibility = #all-bar-numbers-visible
  \override Score.BarNumber.break-visibility = ##(#f #t #t)
  
  \partial 4
  \key c \major
  \time 4/4
  
  \clef "bass"
  c'4 | % 1
  \barNumberCheck #1
  c'4. c'8 c'4 c' | % 2
  \barNumberCheck #2
f'8 g' a' b' c''4 }

\book {
  \header {
  }
  
  \score {
    <<
      
      \new StaffGroup <<
      
        \new Staff = "Part_POne_Staff_One"
        \with {
        }
        <<
          \context Voice = "Part_POne_Staff_One_Voice_One" <<
            \voiceOne % out of 2 regular voices
            \Part_POne_Staff_One_Voice_One
          >>
          \context Voice = "Part_POne_Staff_One_Voice_Two" <<
            \voiceTwo % out of 2 regular voices
            \Part_POne_Staff_One_Voice_Two
          >>
        >>
        \new Staff = "Part_PTwo_Staff_One"
        \with {
        }
        <<
          \context Voice = "Part_PTwo_Staff_One_Voice_One" <<
            \voiceOne % out of 2 regular voices
            \Part_PTwo_Staff_One_Voice_One
          >>
          \context Voice = "Part_PTwo_Staff_One_Voice_Two" <<
            \voiceTwo % out of 2 regular voices
            \Part_PTwo_Staff_One_Voice_Two
          >>
        >>
        
      >>
      
      
    >>
    
    \layout {
      \context {
        \Score
        autoBeaming = ##f % to display tuplets brackets
      }
      \context {
        \Voice
      }
      \context {
        \Score
        % defaultBarType = #"!"
        startRepeatType = #"[|:"
        endRepeatType = #":|]"
        doubleRepeatType = #":|][|:"
      }
    }
    
    \midi {
      \tempo 4 = 90
    }
  }
  
  \paper {
    paper-height                   = 297\mm
    paper-width                    = 210\mm
    
    %left-margin                    = 0.0\mm
    %right-margin                   = 0.0\mm
    %top-margin                     = 0.0\mm
    %bottom-margin                  = 0.0\mm
    
    %horizontal-shift               = 0.0\mm
    %indent                         = 0.0\mm
    %short-indent                   = 0.0\mm
    
    markup-system-spacing.padding  = 1\cm
    %between-system-space           = 0.0\mm
    %page-top-space                 = 0.0\mm
    
    %page-count                     = -1
    %system-count                   = -1
    
    oddHeaderMarkup                = \markup {
    \fill-line {
      \on-the-fly \not-first-page {
        \fromproperty #'page:page-number-string
        " "
        \fromproperty #'header:title
        " "
        \fromproperty #'header:subtitle
      }
    }
  }

    evenHeaderMarkup               = \markup {
    \fill-line {
      \on-the-fly \not-first-page {
        \fromproperty #'page:page-number-string
        " "
        \fromproperty #'header:title
        " "
        \fromproperty #'header:subtitle
      }
    }
  }

    oddFooterMarkup                = \markup {
    \tiny
    \column {
      \fill-line {
        #(string-append
"Music generated from MusicXML by xml2ly 0.93 and engraved by LilyPond " (lilypond-version))
      }
      \fill-line { \italic { \modTimeAsString }}
    }
  }

    evenFooterMarkup               = ""
  }
  
}
