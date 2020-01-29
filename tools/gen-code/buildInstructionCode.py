#!/usr/bin/env python3

import sys

import parser

def usage():
    print("""

python3 buildInstructionCode.py < test

<variable> => [a-zA-Z][a-zA-Z0-9_]
<number> => [0-9]
<op> => +-*/
<expr> => <variable> <op> <expr> | <number> <op> <expr> | <variable> | <number>
<assignment> => <variable> = <expr>
<comp> => < <= > >= == !=
<comp-expr> => <expr> <comp> <expr>
<statement> => <expr>;
<statements> => <statement> | <statement> <statements>
<block> => <expr>; | { <statements> }
<if> => if (<comp-expr>) <block>
<for-loop> => for (<expr> ; <compr-expr>; <expr>) <block>

game-object related
<for-all-game-obj> => foreach_obj obj <block>  // you can access GameObject like obj.getHealth()
<access-obj-content> => obj.<method-name>()    // like obj.getHealth()

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
    print(pResult)
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