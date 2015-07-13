# ASCIICHANGES

A simple language describing chord progressions (changes) for tunes in ASCII text

# Examples

## Introductory Example and General Structure

This is an introductory example showcasing some of the features:

<pre>
# Autumn Leaves

Tempo: 120bpm
Signature: 4/4

# A:
|: Cm7     | F7       |    Bbmaj7   | Ebmaj7    |
|  Am7b5   | D7b9     | 1. Gm       | G7b9     :|
                      | 2. Gm       |           |

# B:
| Am7b5    | D7b9     | Gm          | G7b9      |
| Cm7      | F7       | Bbmaj7      | Ebmaj7    |
| Am7b5    | D7b9     | Gm  Gm/Gb   | Gm/F Gm/E |
| Ebmaj7   | D7b9     | (+) Gm      | (G7b9)    |

| (+) Gdim | Gmin(maj7,9) |          |
</pre>

## General Structure

A legal song file consists of three types of lines:

* Bars/Measures
* Whitespace lines
* Key/Value pairs

These can be freely intermixed. You're also pretty free to use whitespace to format the text nicely.

## Whitespace

Lines consisting of just whitespace are ignored:

<pre>    </pre>

## Comments

Comments start with a <code>#</code>, can start anywhere on a line and extend to the end of that line:

<pre># This is a comment</pre>

<pre>    # This, too</pre>

<pre>| Cm7 | # Vamp over this chord to get a feel for it :) </pre>

## Key/Value pairs

## Bars/Measures

The simplest well formed program is

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

# Chords

Chord symbols form an independent language themself (independent in the sense that you can use the library to parse chord symbols without having to parse a complete song).

## Examples

### Triads

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

### Seventh Chords

Seventh chords:

<pre>Eb7</pre>
<pre>Gmaj7</pre>
<pre>Ebmajor7</pre>

### Higher Extensions

Ninth chords:

<pre>E9</pre>

For sharp and flat ninth you need to disambiguify the notation. For <code>Eb9</pre> it is not clear if an <code>E</code> major triad with a <code>b9</code> extension is meant or a <code>Eb</code> with a <code>9</code> extension. You can use brackets <code>(</code><code>)</code> on either the extension or the chord symbol:

<pre>Eb(9)</pre>

or 

<pre>(Eb)9</pre>

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
