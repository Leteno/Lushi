#!/usr/bin/env python3

import re
import sys

def main():
    lineCount = 0
    for line in sys.stdin:
        code, value = parseLine(line)
        if code:
            lineCount += 1
            print(formatCode(code, value))
    print("print line: %s" % lineCount)

def parseLine(line):
    m = re.search("\d*\)\s*([A-Z_]+)\s*([0-9-]*)", line)
    if m:
        return m.group(1), m.group(2)
    return None, None

def formatCode(code, value):
    if value:
        return "iList.push_back(buildInstruction(Sequence::Code::%s, Sequence::Value::INT, %s));" % (code, value)
    else:
        return "iList.push_back(buildInstruction(Sequence::Code::%s, Sequence::Value::NONE, -1));" % code

if __name__ == "__main__":
    main()