# ASCIICHANGES

A simple language describing chord progressions (changes) for tunes in ASCII text

# Examples

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
| Am7b5    | D7b9     | Gm          | (G7b9)    |
</pre>



The simplest well formed program is

<pre>| |</pre>

That is an empty bar. Whitespace is not important. This is equivalent to the previous example:

<pre>||</pre>

As is this one:

<pre>    |   |   </pre>

Lines consisting of just whitespace are ignored:

<pre>    </pre>

Comments start with a <code>#</code>, can start anywhere on a line and extend to the end of that line:

<pre># This is a comment</pre>

<pre>| Cm7 | F7 | Bbmaj7 |    |</pre>
