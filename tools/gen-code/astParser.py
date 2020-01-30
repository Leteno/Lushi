
def buildAST(tokens):
    parser = ASTParser(tokens)
    ast = parser.buildAST()
    return ast

class ASTParser:
    def __init__(self, tokens):
        self.tokens = tokens
    def buildAST(self):
        self.index = 0
        self.tokenLen = len(self.tokens)
        ast = self.statements()
        return ast
    def statements(self):
        children = []
        stmts = {'type': 'statements', 'content': children}
        while self.index < self.tokenLen:
            stmt = self.statement()
            if stmt:
                children.append(stmt)
                continue
            b = self.block()
            if b:
                children.append(b)
                continue
            # no dealable
            return stmts

    def statement(self):
        currentType = self.currentType()
        if currentType == 'if':
            self.index += 1
            return ifClause()
        elif currentType == 'for':
            self.index += 1
            return forClause()
        elif currentType == 'foreach_obj':
            self.index += 1
            return forEachObjClause()

        # <assignment>;
        lastPosition = self.index
        assignment = self.assignment()
        if assignment and self.currentType() == 'comma':
            self.index += 1
            return {'type': 'statement', 'content': assignment}
        self.index = lastPosition
        # access-obj-content  obj.sayHello()
        return None

    def block(self):
        lastPosition = self.index
        if self.currentValue() == '{':
            self.index += 1
            stmts = self.statements()
            self._assert(self.currentValue() == '}')
            self.index += 1
            return {'type': 'block', 'content': stmts}
        else:
            return self.statement()

    def ifClause(self):
        self._assert(self.currentValue() == '(')
        self.index += 1
        compExpr = self.comp_expr()
        self._assert(compExpr)
        self._assert(self.currentValue() == ')')
        self.index += 1
        block = self.block()
        self._assert(block)
        return {'type': 'if', 'comp-expr': compExpr, 'block': block }

    def forClause(self):
        self._assert(self.currentValue() == '(')
        self.index += 1
        beginExpr = self.expr()
        self._assert(self.currentValue() == ';')
        self.index += 1
        compExpr = self.comp_expr()
        self._assert(self.currentValue() == ';')
        self.index += 1
        endExpr = self.expr()
        self._assert(self.currentValue() == ')')
        self.index += 1
        return {
            'type': 'for',
            'begin': beginExpr,
            'comp-expr': compExpr,
            'end': endExpr,
        }

    def forEachObjClause(self):
        self._assert(self.currentType() == 'variable')
        variable = self.currentToken()
        self.index += 1
        block = self.block()
        self._assert(block)
        return {
            'type': 'for-all-game-obj',
            'variable': variable,
            'block': block,
        }

    def assignment(self):
        self._assert(self.currentToken() == 'variable')
        variable = self.currentToken()
        self.index += 1
        if self.currentValue() == '.':
            self.index += 1
            return self.accessObjContent(variable)
        self._assert(self.currentValue() == '=')
        self.index += 1
        expr = self.expr()
        self._assert(expr)
        return {
            'type': 'assignment',
            'first': variable,
            'second': expr,
        }

    def expr(self):
        # TODO deal with priority of +-*/ ()
        currentType = self.currentType()
        if currentType in ['variable', 'number']:
            first = self.currentToken()
            self.index += 1
            if self.currentType() == 'op':
                op = self.currentToken()
                self.index += 1
                second = self.expr()
                self._assert(second)
                return {
                    'type': 'expr',
                    'first': first,
                    'op': op,
                    'second': second,
                }
            elif self.currentType() == 'dot':
                self.index += 1
                return self.accessObjContent(first)
            else:
                return {'type': 'expr', 'first': first}

    def comp_expr(self):
        a = self.expr()
        self._assert(a)
        self._assert(self.currentType() == 'comp')
        comp = self.currentToken()
        self.index += 1
        b = self.expr()
        self._assert(b)
        return {
            'type': 'comp-expr',
            'first': a,
            'comp': comp,
            'second': b,
        }

    def accessObjContent(self, variable):
        self._assert(self.currentType() == 'variable')
        methodName = self.currentToken()
        self.index += 1
        self._assert(self.currentValue() == '(')
        self.index += 1
        args = self.args()
        self._assert(self.currentValue() == ')')
        self.index += 1
        return {
            'type': 'access-obj-content',
            'obj': first,
            'method': methodName,
            'args': args,
        }

    def args():
        expr = self.expr()
        if self.currentValue() == ',':
            self.index += 1
            restArgs = self.args()
            self._assert(expr and restArgs)
            return {
                'type': 'args',
                'first': expr,
                'rest': restArgs
            }
        if expr:
            return {
                'type': 'args',
                'first': expr,
                'rest': None,
            }
        return None

    def currentType(self):
        return self.tokenType(self.index)
    def tokenType(self, index):
        self._assert(index < self.tokenLen)
        return self.tokens[index]['type']
    def currentValue(self):
        return self.tokenValue(self.index)
    def tokenValue(self, index):
        self._assert(index < self.tokenLen)
        return self.tokens[index]['value']
    def currentToken(self):
        return self.tokens[self.index]
    def _assert(self, exam):
        if not exam:
            print("error at: %d, current token is: %s" %
                (self.index, self.currentToken()))
            assert exam