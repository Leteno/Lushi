#!/usr/bin/env python3

import json
import sys

import parser

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
    content = getContent()
    pResult = parser.parse(content)
    print(json.dumps(pResult, indent=2))
    return
    gResult = codeGen.gen(pResult)

def getContent():
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

if __name__ == "__main__":
    main()