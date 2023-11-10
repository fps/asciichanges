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

function parseTrimmedLine(line, n)
{
  var result;

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

  return { parsed: false };
}

function parseLine(line, n)
{
  console.log("line " + n + ": \"" + line + "\"")
  var position = 0;

  trimmedline = line.trimStart();
  position += line.length - trimmedline.length;
  trimmedLine = line.trimEnd();
  console.log("position: " + position);

  return parseTrimmedLine(trimmedLine, n);
}

function parse(text)
{
  song = []
  lines = text.split("\n");

  lines.forEach((line, n) =>
  {
    var result = parseLine(line, n);
    if (!result.parsed)
    {
      console.log("Failed to parse line: " + n);
    }
    song.push(parseLine(line, n));
  })

  return song;
}

var fs = require('fs');
var text = fs.readFileSync(0).toString();

console.log(parse(text));
