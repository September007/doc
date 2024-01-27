---
title: clang 调试初体验
categories: 
 - [ Singles]
date: 2024-01-27T21:06:42+08:00
draft: false
include_toc: true
---

`clang::ParseAST` main loop for the stmts parsing;
```cpp
    for (bool AtEOF = P.ParseFirstTopLevelDecl(ADecl, ImportState); !AtEOF;
         AtEOF = P.ParseTopLevelDecl(ADecl, ImportState)) {
      // If we got a null return and something *was* parsed, ignore it.  This
      // is due to a top-level semicolon, an action override, or a parse error
      // skipping something.
      if (ADecl && !Consumer->HandleTopLevelDecl(ADecl.get())) // CodeGen
        return;
    }
```

## Parser

```cpp
// printf(    $tok place$ "xxx")
>    clang::Parser::ParseExpressionList(llvm::SmallVectorImpl & Exprs, llvm::function_ref ExpressionStarts, bool FailImmediatelyOnInvalidExpr, bool EarlyTypoCorrection)
     clang::Parser::ParsePostfixExpressionSuffix(clang::ActionResult LHS)
     clang::Parser::ParseCastExpression(clang::Parser::CastParseKind ParseKind, bool isAddressOfOperand, bool & NotCastExpr, clang::Parser::TypeCastState isTypeCast, bool isVectorLiteral, bool * NotPrimaryExpression)
     clang::Parser::ParseCastExpression(clang::Parser::CastParseKind ParseKind, bool isAddressOfOperand, clang::Parser::TypeCastState isTypeCast, bool isVectorLiteral, bool * NotPrimaryExpression)
     clang::Parser::ParseAssignmentExpression(clang::Parser::TypeCastState isTypeCast)
     clang::Parser::ParseExpression(clang::Parser::TypeCastState isTypeCast)
     clang::Parser::ParseExprStatement(clang::Parser::ParsedStmtContext StmtCtx)
     clang::Parser::ParseStatementOrDeclarationAfterAttributes(llvm::SmallVector & Stmts, clang::Parser::ParsedStmtContext StmtCtx, clang::SourceLocation * TrailingElseLoc, clang::ParsedAttributes & CXX11Attrs, clang::ParsedAttributes & GNUAttrs)
     clang::Parser::ParseStatementOrDeclaration(llvm::SmallVector & Stmts, clang::Parser::ParsedStmtContext StmtCtx, clang::SourceLocation * TrailingElseLoc)
     clang::Parser::ParseCompoundStatementBody(bool isStmtExpr)
     clang::Parser::ParseFunctionStatementBody(clang::Decl * Decl, clang::Parser::ParseScope & BodyScope)
     clang::Parser::ParseFunctionDefinition(clang::ParsingDeclarator & D, const clang::Parser::ParsedTemplateInfo & TemplateInfo, clang::Parser::LateParsedAttrList * LateParsedAttrs)
     clang::Parser::ParseDeclGroup(clang::ParsingDeclSpec & DS, clang::DeclaratorContext Context, clang::ParsedAttributes & Attrs, clang::SourceLocation * DeclEnd, clang::Parser::ForRangeInit * FRI)
     clang::Parser::ParseDeclOrFunctionDefInternal(clang::ParsedAttributes & Attrs, clang::ParsedAttributes & DeclSpecAttrs, clang::ParsingDeclSpec & DS, clang::AccessSpecifier AS)
     clang::Parser::ParseDeclarationOrFunctionDefinition(clang::ParsedAttributes & Attrs, clang::ParsedAttributes & DeclSpecAttrs, clang::ParsingDeclSpec * DS, clang::AccessSpecifier AS)
     clang::Parser::ParseExternalDeclaration(clang::ParsedAttributes & Attrs, clang::ParsedAttributes & DeclSpecAttrs, clang::ParsingDeclSpec * DS)
     clang::Parser::ParseTopLevelDecl(clang::OpaquePtr & Result, clang::Sema::ModuleImportState & ImportState)
     clang::ParseAST(clang::Sema & S, bool PrintStats, bool SkipFunctionBodies)
     clang::ASTFrontendAction::ExecuteAction()
     clang::CodeGenAction::ExecuteAction()
     clang::FrontendAction::Execute()
     clang::CompilerInstance::ExecuteAction(clang::FrontendAction & Act)
```
### name lookup 
`OverloadCandidate`
`isBetterOverloadCandidate`
```cpp
    clang::OverloadCandidateSet::BestViableFunction(clang::Sema & S, clang::SourceLocation Loc, clang::OverloadCandidate * & Best)
     clang::Sema::BuildOverloadedCallExpr(clang::Scope * S, clang::Expr * Fn, clang::UnresolvedLookupExpr * ULE, clang::SourceLocation LParenLoc, llvm::MutableArrayRef Args, clang::SourceLocation RParenLoc, clang::Expr * ExecConfig, bool AllowTypoCorrection, bool CalleesAddressIsTaken)
     clang::Sema::BuildCallExpr(clang::Scope * Scope, clang::Expr * Fn, clang::SourceLocation LParenLoc, llvm::MutableArrayRef ArgExprs, clang::SourceLocation RParenLoc, clang::Expr * ExecConfig, bool IsExecConfig, bool AllowRecovery)
     clang::Sema::ActOnCallExpr(clang::Scope * Scope, clang::Expr * Fn, clang::SourceLocation LParenLoc, llvm::MutableArrayRef ArgExprs, clang::SourceLocation RParenLoc, clang::Expr * ExecConfig)
```

### Dialogs

```cpp
TextDiagnostic::emitDiagnosticMessage(clang::FullSourceLoc Loc, clang::PresumedLoc PLoc, clang::DiagnosticsEngine::Level Level, llvm::StringRef Message, llvm::ArrayRef<clang::CharSourceRange> Ranges, llvm::PointerUnion<clang::Diagnostic const *,clang::StoredDiagnostic const *> D)
DiagnosticRenderer::emitDiagnostic(clang::FullSourceLoc Loc, clang::DiagnosticsEngine::Level Level, llvm::StringRef Message, llvm::ArrayRef<clang::CharSourceRange> Ranges, llvm::ArrayRef<clang::FixItHint> FixItHints, llvm::PointerUnion<clang::Diagnostic const *,clang::StoredDiagnostic const *> D) 
TextDiagnosticPrinter::HandleDiagnostic(clang::DiagnosticsEngine::Level Level, const clang::Diagnostic & Info) 
DiagnosticIDs::EmitDiag(clang::DiagnosticsEngine & Diag, clang::DiagnosticIDs::Level DiagLevel) 
DiagnosticIDs::ProcessDiag(clang::DiagnosticsEngine & Diag) 
DiagnosticsEngine::ProcessDiag() 
DiagnosticsEngine::EmitCurrentDiagnostic(bool Force) 
DiagnosticBuilder::Emit() 
DiagnosticBuilder::~DiagnosticBuilder() 
Parser::ParseCastExpression(clang::Parser::CastParseKind ParseKind, bool isAddressOfOperand, clang::Parser::TypeCastState isTypeCast, bool isVectorLiteral, bool * NotPrimaryExpression) 
Parser::ParseRHSOfBinaryExpression(clang::ActionResult<clang::Expr *,1> LHS, clang::prec::Level MinPrec) 
Parser::ParseAssignmentExpression(clang::Parser::TypeCastState isTypeCast) 
Parser::ParseExpression(clang::Parser::TypeCastState isTypeCast) 
Parser::ParseExprStatement(clang::Parser::ParsedStmtContext StmtCtx) 
Parser::ParseStatementOrDeclarationAfterAttributes(llvm::SmallVector<clang::Stmt *,32> & Stmts, clang::Parser::ParsedStmtContext StmtCtx, clang::SourceLocation * TrailingElseLoc, clang::ParsedAttributes & CXX11Attrs, clang::ParsedAttributes & GNUAttrs) 
Parser::ParseStatementOrDeclaration(llvm::SmallVector<clang::Stmt *,32> & Stmts, clang::Parser::ParsedStmtContext StmtCtx, clang::SourceLocation * TrailingElseLoc) 
Parser::ParseCompoundStatementBody(bool isStmtExpr) 
Parser::ParseFunctionStatementBody(clang::Decl * Decl, clang::Parser::ParseScope & BodyScope) 
Parser::ParseFunctionDefinition(clang::ParsingDeclarator & D, const clang::Parser::ParsedTemplateInfo & TemplateInfo, clang::Parser::LateParsedAttrList * LateParsedAttrs) 
Parser::ParseDeclGroup(clang::ParsingDeclSpec & DS, clang::DeclaratorContext Context, clang::ParsedAttributes & Attrs, clang::SourceLocation * DeclEnd, clang::Parser::ForRangeInit * FRI) 
```

## codeGen

entry point

```cpp
clang::CodeGen::CodeGenFunction::GenerateCode(clang::GlobalDecl GD, llvm::Function * Fn, const clang::CodeGen::CGFunctionInfo & FnInfo)
{
    ///* int main(){    */
    CodeGenFunction::StartFunction(GD, ResTy, Fn, FnInfo, Args, Loc, BodyRange.getBegin())
    {
        CodeGenFunction::EmitFunctionProlog()
        {
            // If this- is an implicit-return-zero function, go ahead and
            // initialize the return value.  TODO: it might be nice to have
            // a more general mechanism for this that didn't require synthesized
            // return statements.
            if (const FunctionDecl *FD = dyn_cast_or_null<FunctionDecl>(CurCodeDecl)) {
                if (FD->hasImplicitReturnZero()) {
                QualType RetTy = FD->getReturnType().getUnqualifiedType();
                llvm::Type* LLVMTy = CGM.getTypes().ConvertType(RetTy);
                llvm::Constant* Zero = llvm::Constant::getNullValue(LLVMTy);
                Builder.CreateStore(Zero, ReturnValue);
                }
              }
        }
    }
    
    ///* printf("xxx"); */
    CodeGenFunction::EmitFunctionBody(const Stmt *Body)->
        CodeGenFunction::EmitCompoundStmtWithoutScop(const CompoundStmt &S,bool GetLast,AggValueSlot AggSlot)
        {
              for (auto *CurStmt : S.body())
                  EmitStmt(CurStmt);
        }
}
```

### stmt entry

```cpp
    clang::CodeGen::CodeGenFunction::EmitStmt(const clang::Stmt * S, llvm::ArrayRef<...> Attrs)
     clang::CodeGen::CodeGenFunction::EmitCompoundStmtWithoutScope(const clang::CompoundStmt & S, bool GetLast, clang::CodeGen::AggValueSlot AggSlot)
     clang::CodeGen::CodeGenFunction::EmitFunctionBody(const clang::Stmt * Body)
     clang::CodeGen::CodeGenFunction::GenerateCode(clang::GlobalDecl GD, llvm::Function * Fn, const clang::CodeGen::CGFunctionInfo & FnInfo)
     clang::CodeGen::CodeGenModule::EmitGlobalFunctionDefinition(clang::GlobalDecl GD, llvm::GlobalValue * GV)
     clang::CodeGen::CodeGenModule::EmitGlobalDefinition(clang::GlobalDecl GD, llvm::GlobalValue * GV)
     clang::CodeGen::CodeGenModule::EmitGlobal(clang::GlobalDecl GD)
     clang::CodeGen::CodeGenModule::EmitTopLevelDecl(clang::Decl * D)
```


### other

Breakpoint on `Instruction::Instruction ctor` for IR code generation
See `CodeGenFunction::EmitFunctionProlog` for *`C++ main` defaultly return 0*
