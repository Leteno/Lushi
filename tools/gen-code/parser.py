
import sys

import astParser

def parse(content):
    tokens = tokenize(content)
    ast = astParser.buildAST(tokens)
    return ast

def tokenize(content):
    index, length = 0, len(content)
    tokens = []
    while index < length:
        # TODO Add range check inside
        ch = content[index]
        if str.isalpha(ch):
            sBegin, sEnd = index, index + 1
            while str.isalnum(content[sEnd]) or '_' == content[sEnd]:
                sEnd += 1
            index = sEnd
            tokens.append(variable(content[sBegin:sEnd]))
        elif str.isnumeric(ch):
            sBegin, sEnd = index, index + 1
            while str.isnumeric(content[sEnd]):
                sEnd += 1
            index = sEnd
            tokens.append(number(content[sBegin:sEnd]))
        elif ch in ['<', '>']:
            sBegin, sEnd = index, index + 1
            if '=' == content[sEnd]:
                sEnd += 1
            index = sEnd
            tokens.append(comp(content[sBegin:sEnd]))
        elif ch in ['+', '-', '*', '/']:
            index += 1
            tokens.append(op(ch))
        elif ch == '=':
            if content[index + 1] == '=':
                index += 2
                tokens.append(comp('=='))
            else:
                index += 1
                tokens.append(equal('='))
        elif ch == '!':
            if content[index + 1] == '=':
                index += 2
                tokens.append(comp('!='))
            else:
                index += 1
                tokens.append(_not('!'))
        elif ch == ';':
            index += 1
            tokens.append(comma(';'))
        elif ch in ['{', '}']:
            index += 1
            tokens.append(bracket(ch))
        elif ch in ['(', ')']:
            index += 1
            tokens.append(brace(ch))
        elif ch == '.':
            index += 1
            tokens.append(dot('.'))
        elif ch in [' ', '\n']:
            index += 1
        else:
            print('unrecorgnize code: index: %d, char: %s' % (index, ch))
            sys.exit(-1)
    return tokens

def variable(name):
    # TODO deal with keywords
    if name == 'for':
        return {'type': 'for', 'value': name}
    elif name == 'foreach_obj':
        return {'type': 'foreach_obj', 'value': name}
    elif name == 'if':
        return {'type': 'if', 'value': name}
    elif name == 'else':
        return {'type': 'else', 'value': name}
    else:
        return {'type': 'variable', 'value': name}

def number(n):
    return {'type': 'number', 'value': n}

def comp(s):
    return {'type': 'comp', 'value': s}

def op(s):
    return {'type': 'op', 'value': s}

def equal(s):
    return {'type': 'equal', 'value': s}

def _not(s):
    return {'type': 'not', 'value': s}

def comma(s):
    return {'type': 'comma', 'value': s}

def bracket(s):
    return {'type': 'bracket', 'value': s}

def brace(s):
    return {'type': 'brace', 'value': s}

def dot(s):
    return {'type': 'dot', 'value': s}
