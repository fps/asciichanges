const noteNames = [ 'C', 'D', 'E', 'F', 'G', 'A', 'B' ];

function parseComment(line, n)
{
  if (line.length >= 2 && line[0] == '-' && line[1] == '-')
  {
    return { parsed: true, type: "comment", value: line.substring(3, line.length) };
  }

  return { parsed: false, line: n };
}

function parseChord(line, n)
{
  if (line.length < 1)
  {
    return { parsed: false, line: n };
  }

  if (!noteNames.includes(line[0]))
  {
    return { parsed: false, line: n };
  }

  return {parsed: false, line: n };
}

function parseKeyValuePair(line, n)
{
  splitLine = line.split(":");

  if (splitLine.length != 2)
  {
    return { parsed: false, line: n };
  }

  var exp = /^[0-9a-zA-Z]+$/;

  if (!splitLine[0].match(exp))
  {
    return { parsed: false, line: n };
  }

  return { parsed: true, type: "keyValue", key: splitLine[0], value: splitLine[1].trim() };
}

function parseEmptyLine(line, n)
{
  var exp = /^ *$/;
  if (line.match(exp))
  {
    return { parsed: true, type: "whitespace" };
  }

  return { parsed: false, line: n };
}

function parseTrimmedLine(line, n)
{
  var result;

  result = parseEmptyLine(line, n)
  if (result.parsed)
  {
    return result;
  }

  result = parseKeyValuePair(line, n);
  if (result.parsed)
  {
    return result;
  }

  result = parseComment(line, n);
  if (result.parsed)
  {
    return result;
  }

  result = parseChord(line, n);
  if (result.parsed)
  {
    return result;
  }

  return { parsed: false, reason: "Expected one of: empty line, key-value pair, comment, chord, bars" };
}

function parseLine(line, n)
{
  console.log("line " + n + ": \"" + line + "\"")
  var position = 0;

  trimmedline = line.trimStart();
  position += line.length - trimmedline.length;
  trimmedLine = line.trimEnd();

  return parseTrimmedLine(trimmedLine, n);
}

function parse(text)
{
  song = []
  lines = text.split("\n");

  console.log(lines);

  lines.forEach((line, n) =>
  {
    var result = parseLine(line, n);
    if (!result.parsed)
    {
      throw new Error("Failed to parse line: " + n + ". Reason: " + result.reason);
    }
    song.push(result);
  })

  return song;
}

var fs = require('fs');
var text = fs.readFileSync(0).toString();

console.log(parse(text));
