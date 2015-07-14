# ASCIIChanges

A simple language describing chord progressions (changes) for tunes in ASCII text

# Introductory Examples

This is an introductory example showcasing some of the features:

<pre>
# Autumn Leaves

Tempo: 120
Signature: 4/4

# A:
|: Cm7     | F7       |    Bbmaj7   | Ebmaj7          |
|  Am7b5   | D7b9     | 1. Gm       | G7b9           :|
                      | 2. Gm       |                 |

# B:
| Am7b5    | D7b9     | Gm            | G7b9          |
| Cm7      | F7       | Bbmaj7        | Ebmaj7        |
| Am7b5    | D7b9     | Gm / Gm/Gb /  | Gm/F / Gm/E / |
| Ebmaj7   | D7b9     | (+) Gm        | (G7b9)        |

| (+) Gdim | Gmin(maj7,9) |
</pre>

# Scope and Motivation

Over the years the author has written several (terrible) ad-hoc parsers in different languages to parse subsets of ASCIIChanges for various experiments in algorithmic composition. He has also corresponded over EMail with other musicians discussing harmonic content of jazz standard tunes. One faithful day he realized that there is an overlap between these two areas of use.

Formalizing this language might facilitate his own and others' future experiments in algorithmic compositions. Automatic backing track generation for practice and playing is a subset of algorithmic composition. ASCIIChanges might serve as a standardized interchange format for different backing track generators.

This package aims to provide a (more or less) formal grammar of ASCIIChanges and a C++ library implemented using Boost-Spirit that creates a hopefully useful data structure representing the song from parsing valid ASCIIChanges files.

# Structure

A legal song file consists of three types of lines:

* Bars/Measures
* Whitespace lines
* Key/Value pairs

These can be freely intermixed. You're also pretty free to use whitespace to format the text nicely. Additionally comments can be started anywhere on a line with a <code>#</code>. Comments extend to the end of the line.

## Whitespace

Lines consisting of just whitespace are ignored:

<pre>    </pre>

## Comments

Comments start with a <code>#</code>, can start anywhere on a line and extend to the end of that line:

<pre># This is a comment</pre>

<pre>    # This, too</pre>

<pre>| Cm7 | # Vamp over this chord to get a feel for it :) </pre>

## Key/Value pairs

Key/Value pairs are used to describe properties of the song like the tempo, or the time signature. Their general structure is

</pre>Key: Value</pre>

The following properties can be used:

* <code>Tempo</code>: The tempo of the song in beats per minute (bpm).
* <code>Signature</code>: The time signature.
* <code>Style</code>: A style hint. This is a free form text property (example: <code>Style: "Latin"</code>

Keys are case insensitive. So an author is free to write <code>tempo</code> or <code>tEmPo</code>. 

Key/value pairs can appear on lines (even several on a single line - whitespace separated):

<pre>Tempo: 120 Signature: 4/4</pre>

## Bars/Measures

The simplest line consisting of measures/bars is

<pre>| |</pre>

That is an empty bar. Whitespace is not important. This is equivalent to the previous example:

<pre>||</pre>

As is this one:

<pre>    |   |   </pre>

A line can consist of more than one measure:

<pre>|   |   |</pre>

<pre>|   |   |   |</pre>

<pre>|   |   |   |   |</pre>

etc.

Measures can contain 

* Chord symbols
* Beat indicators
* Key/Value pairs
* Repetition markers
* Coda signs

Here are some examples for each of these:

<pre>|  Cm7  | Gm7     |</pre>

Repetition indicators:

<pre>|: Cm7  | Gm7    :|</pre>
<pre>|: Cm7  | 1. Gm7 :| 3. Ab7 G7 |</pre>

Key/Value pairs:

<pre>| Tempo: 120 Cm7  | Tempo: 130 Gm7 |</pre>

Beat indicators:

<pre>| Cm7 / / F7 | Bbmaj7  |</pre>
<pre>| Cm7 . . . . . F7 . . |</pre>

Coda signs:

<pre>
| Cm7        | (+) F7 |

# Coda:
| (+) Cmmaj7 |
</pre>

### Chords

Chord symbols form an independent language themself (independent in the sense that you can use the library to parse chord symbols without having to parse a complete song).

#### Triads

A C major triad:

<pre>C</pre>

A Db minor triad

<pre>Dbm</pre>

Alternative notation for minor triads:

<pre>Dbmin</pre>

Diminished triads:

<pre>Cdim</pre>

Augmented triads:

<pre>Daug</pre>

Alternative roots ("slash" chords):

<pre>Cm/Bb</pre>

Suspended triads:

<pre>Csus2</pre>

<pre>Bsus4</pre>

<code>sus</code> is shorthand for <code>sus4</code>:

<pre>Gsus</pre>

Praise this chord! ;)

#### Seventh Chords

Seventh chords:

<pre>Eb7</pre>
<pre>Gmaj7</pre>
<pre>Ebmajor7</pre>
<pre>Gbmmaj7</pre>
<pre>Dminmaj7</pre>
<pre>Emin7</pre>

#### Higher Extensions

Ninth chords:

<pre>E9</pre>

For <code>Eb9</pre> it is not immediately clear if an <code>E</code> major triad with a <code>b9</code> extension is meant or a <code>Eb</code> with a <code>9</code> extension. You can use brackets <code>(</code><code>)</code> on either the extension or the chord symbol:

<pre>Eb(9)</pre>

or 

<pre>(Eb)9</pre>

But the rule is that a b (#) directly following a root note letter are interpreted to lower (sharpen) the root, not modify the extension. So the above brackets are not needed. Only in the (uncommon) case of a major triad with a <code>b9</code> extension you need to use brackets:

<pre>E(b9)</pre>

Extensions can be one of the set <code>9</code>, <code>11</code>, <code>13</code>, and their sharp and flat variants (except for the <code>b11</code> and <code>#13</code>):

<pre>Eb7#11</pre>

<pre>A7b9#9</pre>

If that is too cluttered for your taste you can use commata:

<pre>D7,9,#11</pre>

Or brackets:

<pre>C7(b9#9)</pre>

Or both:

<pre>Eb7(9,#11)</pre>

Note that between extensions no extra whitespace is allowed. This is illegal:

<pre>F#maj7 9</pre>
