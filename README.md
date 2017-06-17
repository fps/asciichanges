# ASCIIChanges

A simple language describing chord progressions (changes) for tunes in ASCII text

# Introductory Examples

This is an introductory example showcasing some of the features:

<pre>
-- Autumn Leaves

Tempo: 120
Time: 4/4

-- A:
|: Cm7     | F7       |   Bbmaj7     | Ebmaj7        |
|  Am7b5   | D7b9     |1. Gm         | G7b9         :|
                      |2. Gm         |               |

-- B:
| Am7b5    | D7b9     | Gm           | G7b9          |
| Cm7      | F7       | Bbmaj7       | Ebmaj7        |
| Am7b5    | D7b9     | Gm / Gm/Gb / | Gm/F / Gm/E / |
| Ebmaj7   | D7b9     | (+) Gm       | (G7b9)  D.C.  |

| (+) Gdim | Gminmaj79 |
</pre>

And here is the super minimal example (which is just the C major triad):

<pre>
| C |
</pre>

# Scope and Motivation

Over the years the author has written several (terrible) ad-hoc parsers in different languages to parse subsets of ASCIIChanges for various experiments in algorithmic composition. He has also corresponded over EMail with other musicians discussing harmonic content of jazz standard tunes. One faithful day he realized that there is an overlap between these two areas of use.

Formalizing this language might facilitate his own and others' future experiments in algorithmic compositions. Automatic backing track generation for practice and playing is a subset of algorithmic composition. ASCIIChanges might serve as a standardized interchange format for different backing track generators.

This package aims to provide a (more or less) formal grammar of ASCIIChanges and a C++ library implemented using [pegjs](https://pegjs.org/) that creates a hopefully useful data structure representing the song from parsing valid ASCIIChanges files.

# Structure

A legal song file consists of these types of lines:

* Chord symbols
* Bars/Measures
* Whitespace lines
* Key/Value pairs
* Comments

These can be freely intermixed. You're also pretty free to use whitespace to format the text nicely. 

## Whitespace

Lines consisting of just whitespace are ignored:

<pre>    </pre>

## Comments

Comments start with a <code>--</code>. They have to start at the beginning of a line and extend to the end of that line.

<pre>-- This is a comment</pre>

<pre>    -- This is not a comment</pre>

## Key/Value pairs

Key/Value pairs are used to describe properties of the song like the tempo, or the time signature. Their general structure is

</pre>Key: Value</pre>

What key/value pairs mean is implementation dependent.

Key/value pairs can appear on individual lines:

<pre>
Tempo: 120 
Time: 4/4
</pre>

## Bars/Measures

The simplest line consisting of measures/bars is

<pre>| |</pre>

That is an empty bar.

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

### A Word about Multiple Chords per Measure/Bar

For simple cases it is possible to use multiple chords per measure/bar without resorting to using beat indicators (see below.) 

### Repetition Indicators

To indicate repetitions we us

Repeat once:

<pre>|: Cm7  | Gm7    :|</pre>

Repeat once, but use an alternative ending on the second time around:

<pre>|: Cm7  | 1. Gm7 :| 2. Ab7 G7 |</pre>

If you want, you can have as many alternative endings as you want:

<pre>|: Cm7  | 1. Gm7 :| 2. Ab7 G7 :| 3. Db7 :| 4. Ebm Dbm |</pre>


### Beat Indicators

You can use <code>/</code> to indicate quarter beats:

<pre>| Cm7 / / F7 | Bbmaj7  |</pre>

### Coda Signs

<pre>
| Cm7        | (+) F7 |

-- Coda:
| (+) Cmmaj7 |
</pre>

### Chords

#### Triads

A C major triad:

<pre>C</pre>

A Db minor triad

<pre>Dbm</pre>

Alternative notation for minor triads:

<pre>
Dbmin
Dbminor
</pre>

Diminished triads:

<pre>Cdim</pre>

Augmented triads:

<pre>Daug</pre>

Alternative roots ("slash" chords):

<pre>Cm/Bb</pre>

Suspended triads:

<pre>
Csus2
Bsus4
</pre>

<code>sus</code> is shorthand for <code>sus4</code>:

<pre>Gsus</pre>

Praise this chord! ;)

#### Seventh Chords

Seventh chords:

<pre>
Eb7
Gmaj7
Ebmajor7
Gbmmaj7
Dminmaj7
Emin7
</pre>

#### Higher Extensions

Ninth chords:

<pre>E9</pre>

For <code>Eb9</code> it is not immediately clear if an <code>E</code> major triad with a <code>b9</code> extension is meant or a <code>Eb</code> with a <code>9</code> extension. You can use brackets <code>(</code><code>)</code> on either the extension or the chord symbol:

<pre>Eb(9)</pre>

or 

<pre>(Eb)9</pre>

But the rule is that a b (#) directly following a root note letter are interpreted to lower (sharpen) the root, not modify the extension. So the above brackets are not needed. Only in the (uncommon) case of a major triad with a <code>b9</code> extension you need to use brackets:

<pre>E(b9)</pre>

Extensions can be one of the set <code>9</code>, <code>11</code>, <code>13</code>, and their sharp and flat variants (except for the <code>b11</code> and <code>#13</code>):

<pre>
Eb7#11
A7b9#9
</pre>


Note that between extensions no extra whitespace is allowed. This is illegal:

<pre>F#maj7 9</pre>
