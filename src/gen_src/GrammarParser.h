
// Generated from Grammar.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  GrammarParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, TokIf = 7, 
    TokElse = 8, TokWhile = 9, TokDo = 10, LexWhitespace = 11, TokOpLogical = 12, 
    TokOpCompare = 13, TokOpAddSub = 14, TokOpMulDivMod = 15, TokOpBitwise = 16, 
    TokDecNum = 17, TokIdent = 18
  };

  enum {
    RuleProgram = 0, RuleStatements = 1, RuleListStatement = 2, RuleStatement = 3, 
    RuleAssignment = 4, RuleIfStatement = 5, RuleIfChainStatement = 6, RuleElseStatements = 7, 
    RuleWhileStatement = 8, RuleDoWhileStatement = 9, RuleExpr = 10, RuleExprLogical = 11, 
    RuleExprCompare = 12, RuleExprAddSub = 13, RuleExprMulDivModEtc = 14, 
    RuleIdentExpr = 15
  };

  GrammarParser(antlr4::TokenStream *input);
  ~GrammarParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class ProgramContext;
  class StatementsContext;
  class ListStatementContext;
  class StatementContext;
  class AssignmentContext;
  class IfStatementContext;
  class IfChainStatementContext;
  class ElseStatementsContext;
  class WhileStatementContext;
  class DoWhileStatementContext;
  class ExprContext;
  class ExprLogicalContext;
  class ExprCompareContext;
  class ExprAddSubContext;
  class ExprMulDivModEtcContext;
  class IdentExprContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementsContext *statements();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  StatementsContext : public antlr4::ParserRuleContext {
  public:
    StatementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ListStatementContext *listStatement();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementsContext* statements();

  class  ListStatementContext : public antlr4::ParserRuleContext {
  public:
    ListStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    ListStatementContext *listStatement();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ListStatementContext* listStatement();
  ListStatementContext* listStatement(int precedence);
  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementsContext *statements();
    ExprContext *expr();
    AssignmentContext *assignment();
    IfStatementContext *ifStatement();
    IfChainStatementContext *ifChainStatement();
    WhileStatementContext *whileStatement();
    DoWhileStatementContext *doWhileStatement();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  AssignmentContext : public antlr4::ParserRuleContext {
  public:
    AssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentExprContext *identExpr();
    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentContext* assignment();

  class  IfStatementContext : public antlr4::ParserRuleContext {
  public:
    IfStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokIf();
    ExprContext *expr();
    StatementsContext *statements();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfStatementContext* ifStatement();

  class  IfChainStatementContext : public antlr4::ParserRuleContext {
  public:
    IfChainStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokIf();
    ExprContext *expr();
    StatementsContext *statements();
    antlr4::tree::TerminalNode *TokElse();
    ElseStatementsContext *elseStatements();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfChainStatementContext* ifChainStatement();

  class  ElseStatementsContext : public antlr4::ParserRuleContext {
  public:
    ElseStatementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IfChainStatementContext *ifChainStatement();
    StatementsContext *statements();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElseStatementsContext* elseStatements();

  class  WhileStatementContext : public antlr4::ParserRuleContext {
  public:
    WhileStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokWhile();
    ExprContext *expr();
    StatementsContext *statements();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhileStatementContext* whileStatement();

  class  DoWhileStatementContext : public antlr4::ParserRuleContext {
  public:
    DoWhileStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokDo();
    StatementsContext *statements();
    antlr4::tree::TerminalNode *TokWhile();
    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DoWhileStatementContext* doWhileStatement();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprLogicalContext *exprLogical();
    ExprContext *expr();
    antlr4::tree::TerminalNode *TokOpLogical();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  ExprLogicalContext : public antlr4::ParserRuleContext {
  public:
    ExprLogicalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprCompareContext *exprCompare();
    ExprLogicalContext *exprLogical();
    antlr4::tree::TerminalNode *TokOpCompare();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprLogicalContext* exprLogical();
  ExprLogicalContext* exprLogical(int precedence);
  class  ExprCompareContext : public antlr4::ParserRuleContext {
  public:
    ExprCompareContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprAddSubContext *exprAddSub();
    ExprCompareContext *exprCompare();
    antlr4::tree::TerminalNode *TokOpAddSub();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprCompareContext* exprCompare();
  ExprCompareContext* exprCompare(int precedence);
  class  ExprAddSubContext : public antlr4::ParserRuleContext {
  public:
    ExprAddSubContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprMulDivModEtcContext *exprMulDivModEtc();
    ExprAddSubContext *exprAddSub();
    antlr4::tree::TerminalNode *TokOpMulDivMod();
    antlr4::tree::TerminalNode *TokOpBitwise();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprAddSubContext* exprAddSub();
  ExprAddSubContext* exprAddSub(int precedence);
  class  ExprMulDivModEtcContext : public antlr4::ParserRuleContext {
  public:
    ExprMulDivModEtcContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokDecNum();
    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprMulDivModEtcContext* exprMulDivModEtc();

  class  IdentExprContext : public antlr4::ParserRuleContext {
  public:
    IdentExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokIdent();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentExprContext* identExpr();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool listStatementSempred(ListStatementContext *_localctx, size_t predicateIndex);
  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);
  bool exprLogicalSempred(ExprLogicalContext *_localctx, size_t predicateIndex);
  bool exprCompareSempred(ExprCompareContext *_localctx, size_t predicateIndex);
  bool exprAddSubSempred(ExprAddSubContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

