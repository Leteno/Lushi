
def gen(AST):
    generator = CodeGenerator(AST)
    return generator.parse()

class CodeGenerator:
    def __init__(self, AST):
        self.AST = AST
        self.variables = {}

    def parse(self):
        return self.parseInternal(self.AST)

    def parseInternal(self, obj):
        assert obj, "None obj, lastObj is: %s" % self.lastObj
        self.lastObj = obj
        objType = obj['type']
        if objType == 'statements':
            return self.statements(obj)
        elif objType == 'statement':
            return self.statement(obj)
        elif objType == 'block':
            return self.block(obj)
        elif objType == 'if':
            return self.ifClause(obj)
        elif objType == 'for':
            return self.forClause(obj)
        elif objType == 'for-all-game-obj':
            return self.forEachObjClause(obj)
        elif objType == 'assignment':
            return self.assignment(obj)
        elif objType == 'expr':
            return self.expr(obj)
        elif objType == 'comp-expr':
            return self.comp_expr(obj)
        elif objType == 'access-obj-content':
            return self.accessObjContent(obj)
        elif objType == 'args':
            return self.args(obj)
        assert False, 'unknown objType: %s' % objType

    def statements(self, obj):
        codes = []
        for stmt in obj['content']:
            codes += self.parseInternal(stmt)
        return codes

    def statement(self, obj):
        return self.parseInternal(obj['content'])

    def block(self, obj):
        return self.parseInternal(obj['content'])

    def ifClause(self, obj):
        codes = []
        codes += self.comp_expr(obj['comp-expr'])
        pos = self.emit("JMP_IF_FALSE", codes)
        codes += self.block(obj['block'])
        if 'else' in obj and obj['else']:
            self.backPatch(pos, codes)
            codes += self.parseInternal(obj['else'])
        else:
            self.backPatch(pos, codes)
        return codes

    def forClause(self, obj):
        codes = []
        codes += self.parseInternal(obj['begin'])

        # loop validation
        codes += self.comp_expr(obj['comp-expr'])
        loopBegin = self.emit("JMP_IF_FALSE", codes)

        # loop content
        codes += self.parseInternal(obj['block'])
        codes += self.parseInternal(obj['end'])

        # back to loop begin
        jumpBack = self.emit("JMP" , codes)
        self.backPatchInternal(jumpBack, loopBegin, codes)

        # loop end
        self.backPatch(loopBegin, codes)
        return codes

    def forEachObjClause(self, obj):
        codes = []
        self.emit("RESET_OBJ", codes)

        loopBegin = self.emit("MEET_END_OBJ", codes)
        pos = self.emit("JMP_IF_FALSE", codes)
        jumpEnd = self.emit("JMP", codes)
        self.backPatch(pos, codes)

        self.emit("LOAD_OBJ", codes)
        codes += self.block(obj['block'])

        jumpBack = self.emit("JMP", codes)
        self.backPatchInternal(jumpBack, loopBegin, codes)

        self.backPatch(jumpEnd, codes)
        return codes

    def assignment(self, obj):
        name = obj['first']['value']
        # for the instruction like: LOAD <index>,  STORE <index>
        if name not in self.variables:
            index = len(self.variables)
            self.variables[name] = index
        else:
            index = self.variables[name]

        codes = []
        codes += self.parseInternal(obj['second'])
        self.emit("STORE %d" % index, codes)
        self.emit("POP", codes)
        return codes

    def expr(self, obj):
        codes = []
        fType, fValue = obj['first']['type'], obj['first']['value']
        if fType == 'number':
            self.emit("PUSH %s" % fValue, codes)
        elif fType == 'variable':
            assert fValue in self.variables, "Use variable before declare: %s" % fValue
            index = self.variables[fValue]
            self.emit("LOAD %s" % index, codes)
        else:
            assert False, "Unknown expr: %s" % obj

        if 'op' in obj:
            assert 'second' in obj
            codes += self.parseInternal(obj['second'])
            op = obj['op']['value']
            if op == '+':
                self.emit("ADD", codes)
            elif op == '-':
                self.emit("MINUS", codes)
            elif op == '*':
                self.emit("MUL", codes)
            elif op == '/':
                self.emit("DIV", codes)
            else:
                assert False, "Unknown op: %s in %s" % (op, obj)

        return codes

    def comp_expr(self, obj):
        codes = []
        codes += self.parseInternal(obj['first'])
        codes += self.parseInternal(obj['second'])
        comp = obj['comp']['value']
        if comp == '>':
            self.emit("GT", codes)
        elif comp == '>=':
            self.emit("GTE", codes)
        elif comp == '<':
            self.emit("LT", codes)    
        elif comp == '<=':
            self.emit("LTE", codes)
        else:
            assert False, "Unknown comp_expr: %s in obj: %s" % (comp, obj)
        return codes

    def accessObjContent(self, obj):
        # TODO deal with variable name obj['obj']

        codes = []

        codes += self.parseInternal(obj['args'])

        method = obj['method']['value']
        if method == 'getHealth':
            self.emit("GET_HEALTH", codes)
        elif method == 'setHealth':
            self.emit("SET_HEALTH", codes)
        else:
            assert False, "Unsupported method %s in %s" % (method, obj)

        return codes

    def args(self, obj):
        codes = []
        p = obj
        while p:
            firstExpr = p['first']
            codes += self.parseInternal(firstExpr)
            p = p['rest']
        return codes

    def emit(self, code, codes):
        codes.append(code)
        pos = len(codes) - 1
        return pos

    def backPatch(self, patchPos, codes):
        targetPos = len(codes) - 1
        return self.backPatchInternal(patchPos, targetPos, codes)
    
    def backPatchInternal(self, patchPos, targetPos, codes):
        offset = targetPos - patchPos
        codes[patchPos] += " %d" % offset
