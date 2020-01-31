#!/usr/bin/env python3

import json
import sys

import parser
import codeGen

def usage():
    print("""

python3 buildInstructionCode.py < test

<variable> => [a-zA-Z][a-zA-Z0-9_]
<number> => [0-9]
<op> => +-*/
<expr> => <variable> <op> <expr> | <number> <op> <expr> | <variable> | <number> | <access-obj-content>
<comp> => < <= > >= == !=
<comp-expr> => <expr> <comp> <expr>
<assignment> => <variable> = <expr>
<block> => <statement> | { <statements> }
<if> => if (<comp-expr>) <block>
<for-loop> => for (<assignment> ; <comp-expr>; <assignment>) <block>
<statement> => <assignment>; | <if> | <for-loop> | <for-all-game-obj> | <access-obj-content>
<statements> => <statement> | <block> | <statement> <statements>

game-object related
<for-all-game-obj> => foreach_obj obj <block>  // you can access GameObject like obj.getHealth()
<access-obj-content> => obj.<method-name>(<args>) | obj.<method-name>()    // like obj.getHealth()
<args> => <expr> | <expr>, <args>

For example:

// Card Natrue Balance

sum = 0;
count = 0;
foreach_obj obj {
    sum = sum + obj.getHealth();
    count = count + 1;
}

average = sum / count;

foreach_obj obj {
    k = obj.getHealth();
    if (k < average) {
        obj.setHealth(k + 10);
    }
    else if (k > average){
        obj.setHealth(k - 10);
    }
}

""")
    sys.exit(-1)

def main():
    test()

def test():
    content = getTestContent()
    pResult = parser.parse(content)
    gResult = codeGen.gen(pResult)
    compare(gResult, expectTestResult())
    print("pass!")

def compare(codes, expectCodes):
    lCodes, lExpect = len(codes), len(expectCodes)
    detectSize = min(lCodes, lExpect)
    for i in range(detectSize):
        a, b = codes[i], expectCodes[i]
        assert a == b, "code dismatch in %d, %s vs %s" % (i, a, b)
    assert lCodes == lExpect, "code len dismatch: %d %d" % (lCodes, lExpect)

def printCodes(codes):
    for code in codes:
        print(code)

def getTestContent():
    return """
sum = 0;
count = 0;
foreach_obj obj {
    sum = sum + obj.getHealth();
    count = count + 1;
}

average = sum / count;

foreach_obj obj {
    k = obj.getHealth();
    if (k < average) {
        obj.setHealth(k + 10);
    }
    else if (k > average){
        obj.setHealth(k - 10);
    }
}
"""

def expectTestResult():
    return ['PUSH 0', 'PUSH 0', 'PUSH 0', 'PUSH 0', 'PUSH 0', 'STORE 0', 'POP', 'PUSH 0', 'STORE 1', 'POP', 'RESET_OBJ', 'MEET_END_OBJ', 'JMP_IF_FALSE 2', 'JMP 14', 'LOAD_OBJ', 'LOAD 0', 'GET_HEALTH', 'ADD', 'STORE 0', 'POP', 'LOAD 1', 'PUSH 1', 'ADD', 'STORE 1', 'POP', 'MOVE_ON_OBJ', 'JMP -15', 'LOAD 0', 'LOAD 1', 'DIV', 'STORE 2', 'POP', 'RESET_OBJ', 'MEET_END_OBJ', 'JMP_IF_FALSE 2', 'JMP 23', 'LOAD_OBJ', 'GET_HEALTH', 'STORE 3', 'POP', 'LOAD 3', 'LOAD 2', 'LT', 'JMP_IF_FALSE 5', 'LOAD 3', 'PUSH 10', 'ADD', 'SET_HEALTH', 'LOAD 3', 'LOAD 2', 'GT', 'JMP_IF_FALSE 5', 'LOAD 3', 'PUSH 10', 'MINUS', 'SET_HEALTH', 'MOVE_ON_OBJ', 'JMP -24']

if __name__ == "__main__":
    main()