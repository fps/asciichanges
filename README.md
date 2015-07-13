# ASCIICHANGES

A simple language describing chord progressions (changes) for tunes in ASCII text

# Examples

## Introductory Example

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
| Ebmaj7   | D7b9     | c: Gm       | (G7b9)    |

| c: Gmmaj79 |          |
</pre>

## Bars/Measures

The simplest well formed program is

<pre>| |</pre>

That is an empty bar. Whitespace is not important. This is equivalent to the previous example:

<pre>||</pre>

As is this one:

<pre>    |   |   </pre>

## Whitespace

Lines consisting of just whitespace are ignored:

<pre>    </pre>

## Comments

Comments start with a <code>#</code>, can start anywhere on a line and extend to the end of that line:

<pre># This is a comment</pre>

<pre>| Cm7 | # Vamp over this chord to get a feel for it :) </pre>


<pre>| Cm7 | F7 | Bbmaj7 |    |</pre>

# Chords

Chord symbols form an independent language themself (independent in the sense that you can use the library to parse chord symbols without having to parse a complete song).

## Examples

A C major triad:

<pre>C</pre>

A Db minor triad

<pre>Dbm</pre>

Alternative notation for minor triads:

<pre>Dbmin</pre>

Alternative roots ("slash" chords):

<pre>Cm/Bb</pre>

Suspended triads:

<pre>Csus2</pre>

<pre>Bsus4</pre>

<code>sus</code> is shorthand for <code>sus4</code>:

<pre>Gsus</pre>

Seventh chords:

<pre>Eb7</pre>
<pre>Gmaj7</pre>
<pre>Ebmajor7</pre>

Ninth chords:

<pre>E9</pre>

For sharp and flat ninth you need to disambiguify the notation. For <code>Eb9</pre> it is not clear if an <code>E</code> major triad with a <code>b9</code> extension is meant or a <code>Eb</code> with a <code>9</code> extension. You can use brackets <code>(</code><code>)</code> on either the extension or the chord symbol:

<pre>Eb(9)</pre>

or 

<pre>(Eb)9</pre>
