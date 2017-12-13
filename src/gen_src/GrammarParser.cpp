
// Generated from Grammar.g4 by ANTLR 4.7.1


#include "GrammarVisitor.h"

#include "GrammarParser.h"


using namespace antlrcpp;
using namespace antlr4;

GrammarParser::GrammarParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

GrammarParser::~GrammarParser() {
  delete _interpreter;
}

std::string GrammarParser::getGrammarFileName() const {
  return "Grammar.g4";
}

const std::vector<std::string>& GrammarParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& GrammarParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

GrammarParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::StatementsContext* GrammarParser::ProgramContext::statements() {
  return getRuleContext<GrammarParser::StatementsContext>(0);
}


size_t GrammarParser::ProgramContext::getRuleIndex() const {
  return GrammarParser::RuleProgram;
}

antlrcpp::Any GrammarParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::ProgramContext* GrammarParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, GrammarParser::RuleProgram);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(32);
    statements();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementsContext ------------------------------------------------------------------

GrammarParser::StatementsContext::StatementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::ListStatementContext* GrammarParser::StatementsContext::listStatement() {
  return getRuleContext<GrammarParser::ListStatementContext>(0);
}


size_t GrammarParser::StatementsContext::getRuleIndex() const {
  return GrammarParser::RuleStatements;
}

antlrcpp::Any GrammarParser::StatementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitStatements(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::StatementsContext* GrammarParser::statements() {
  StatementsContext *_localctx = _tracker.createInstance<StatementsContext>(_ctx, getState());
  enterRule(_localctx, 2, GrammarParser::RuleStatements);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(34);
    match(GrammarParser::T__0);
    setState(35);
    listStatement(0);
    setState(36);
    match(GrammarParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ListStatementContext ------------------------------------------------------------------

GrammarParser::ListStatementContext::ListStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::StatementContext* GrammarParser::ListStatementContext::statement() {
  return getRuleContext<GrammarParser::StatementContext>(0);
}

GrammarParser::ListStatementContext* GrammarParser::ListStatementContext::listStatement() {
  return getRuleContext<GrammarParser::ListStatementContext>(0);
}


size_t GrammarParser::ListStatementContext::getRuleIndex() const {
  return GrammarParser::RuleListStatement;
}

antlrcpp::Any GrammarParser::ListStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitListStatement(this);
  else
    return visitor->visitChildren(this);
}


GrammarParser::ListStatementContext* GrammarParser::listStatement() {
   return listStatement(0);
}

GrammarParser::ListStatementContext* GrammarParser::listStatement(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  GrammarParser::ListStatementContext *_localctx = _tracker.createInstance<ListStatementContext>(_ctx, parentState);
  GrammarParser::ListStatementContext *previousContext = _localctx;
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, GrammarParser::RuleListStatement, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(41);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      setState(39);
      statement();
      break;
    }

    case 2: {
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(47);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ListStatementContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleListStatement);
        setState(43);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(44);
        statement(); 
      }
      setState(49);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

GrammarParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::StatementsContext* GrammarParser::StatementContext::statements() {
  return getRuleContext<GrammarParser::StatementsContext>(0);
}

GrammarParser::ExprContext* GrammarParser::StatementContext::expr() {
  return getRuleContext<GrammarParser::ExprContext>(0);
}

GrammarParser::AssignmentContext* GrammarParser::StatementContext::assignment() {
  return getRuleContext<GrammarParser::AssignmentContext>(0);
}

GrammarParser::IfStatementContext* GrammarParser::StatementContext::ifStatement() {
  return getRuleContext<GrammarParser::IfStatementContext>(0);
}

GrammarParser::IfChainStatementContext* GrammarParser::StatementContext::ifChainStatement() {
  return getRuleContext<GrammarParser::IfChainStatementContext>(0);
}

GrammarParser::WhileStatementContext* GrammarParser::StatementContext::whileStatement() {
  return getRuleContext<GrammarParser::WhileStatementContext>(0);
}

GrammarParser::DoWhileStatementContext* GrammarParser::StatementContext::doWhileStatement() {
  return getRuleContext<GrammarParser::DoWhileStatementContext>(0);
}


size_t GrammarParser::StatementContext::getRuleIndex() const {
  return GrammarParser::RuleStatement;
}

antlrcpp::Any GrammarParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::StatementContext* GrammarParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 6, GrammarParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(61);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(50);
      statements();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(51);
      expr(0);
      setState(52);
      match(GrammarParser::T__2);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(54);
      assignment();
      setState(55);
      match(GrammarParser::T__2);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(57);
      ifStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(58);
      ifChainStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(59);
      whileStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(60);
      doWhileStatement();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

GrammarParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::IdentExprContext* GrammarParser::AssignmentContext::identExpr() {
  return getRuleContext<GrammarParser::IdentExprContext>(0);
}

GrammarParser::ExprContext* GrammarParser::AssignmentContext::expr() {
  return getRuleContext<GrammarParser::ExprContext>(0);
}


size_t GrammarParser::AssignmentContext::getRuleIndex() const {
  return GrammarParser::RuleAssignment;
}

antlrcpp::Any GrammarParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::AssignmentContext* GrammarParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 8, GrammarParser::RuleAssignment);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(63);
    identExpr();
    setState(64);
    match(GrammarParser::T__3);
    setState(65);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

GrammarParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::IfStatementContext::TokIf() {
  return getToken(GrammarParser::TokIf, 0);
}

GrammarParser::ExprContext* GrammarParser::IfStatementContext::expr() {
  return getRuleContext<GrammarParser::ExprContext>(0);
}

GrammarParser::StatementsContext* GrammarParser::IfStatementContext::statements() {
  return getRuleContext<GrammarParser::StatementsContext>(0);
}


size_t GrammarParser::IfStatementContext::getRuleIndex() const {
  return GrammarParser::RuleIfStatement;
}

antlrcpp::Any GrammarParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::IfStatementContext* GrammarParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 10, GrammarParser::RuleIfStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(67);
    match(GrammarParser::TokIf);
    setState(68);
    match(GrammarParser::T__4);
    setState(69);
    expr(0);
    setState(70);
    match(GrammarParser::T__5);
    setState(71);
    statements();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfChainStatementContext ------------------------------------------------------------------

GrammarParser::IfChainStatementContext::IfChainStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::IfChainStatementContext::TokIf() {
  return getToken(GrammarParser::TokIf, 0);
}

GrammarParser::ExprContext* GrammarParser::IfChainStatementContext::expr() {
  return getRuleContext<GrammarParser::ExprContext>(0);
}

GrammarParser::StatementsContext* GrammarParser::IfChainStatementContext::statements() {
  return getRuleContext<GrammarParser::StatementsContext>(0);
}

tree::TerminalNode* GrammarParser::IfChainStatementContext::TokElse() {
  return getToken(GrammarParser::TokElse, 0);
}

GrammarParser::ElseStatementsContext* GrammarParser::IfChainStatementContext::elseStatements() {
  return getRuleContext<GrammarParser::ElseStatementsContext>(0);
}


size_t GrammarParser::IfChainStatementContext::getRuleIndex() const {
  return GrammarParser::RuleIfChainStatement;
}

antlrcpp::Any GrammarParser::IfChainStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitIfChainStatement(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::IfChainStatementContext* GrammarParser::ifChainStatement() {
  IfChainStatementContext *_localctx = _tracker.createInstance<IfChainStatementContext>(_ctx, getState());
  enterRule(_localctx, 12, GrammarParser::RuleIfChainStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(73);
    match(GrammarParser::TokIf);
    setState(74);
    match(GrammarParser::T__4);
    setState(75);
    expr(0);
    setState(76);
    match(GrammarParser::T__5);
    setState(77);
    statements();
    setState(78);
    match(GrammarParser::TokElse);
    setState(79);
    elseStatements();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseStatementsContext ------------------------------------------------------------------

GrammarParser::ElseStatementsContext::ElseStatementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::IfChainStatementContext* GrammarParser::ElseStatementsContext::ifChainStatement() {
  return getRuleContext<GrammarParser::IfChainStatementContext>(0);
}

GrammarParser::StatementsContext* GrammarParser::ElseStatementsContext::statements() {
  return getRuleContext<GrammarParser::StatementsContext>(0);
}


size_t GrammarParser::ElseStatementsContext::getRuleIndex() const {
  return GrammarParser::RuleElseStatements;
}

antlrcpp::Any GrammarParser::ElseStatementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitElseStatements(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::ElseStatementsContext* GrammarParser::elseStatements() {
  ElseStatementsContext *_localctx = _tracker.createInstance<ElseStatementsContext>(_ctx, getState());
  enterRule(_localctx, 14, GrammarParser::RuleElseStatements);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(83);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GrammarParser::TokIf: {
        enterOuterAlt(_localctx, 1);
        setState(81);
        ifChainStatement();
        break;
      }

      case GrammarParser::T__0: {
        enterOuterAlt(_localctx, 2);
        setState(82);
        statements();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStatementContext ------------------------------------------------------------------

GrammarParser::WhileStatementContext::WhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::WhileStatementContext::TokWhile() {
  return getToken(GrammarParser::TokWhile, 0);
}

GrammarParser::ExprContext* GrammarParser::WhileStatementContext::expr() {
  return getRuleContext<GrammarParser::ExprContext>(0);
}

GrammarParser::StatementsContext* GrammarParser::WhileStatementContext::statements() {
  return getRuleContext<GrammarParser::StatementsContext>(0);
}


size_t GrammarParser::WhileStatementContext::getRuleIndex() const {
  return GrammarParser::RuleWhileStatement;
}

antlrcpp::Any GrammarParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::WhileStatementContext* GrammarParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 16, GrammarParser::RuleWhileStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    match(GrammarParser::TokWhile);
    setState(86);
    match(GrammarParser::T__4);
    setState(87);
    expr(0);
    setState(88);
    match(GrammarParser::T__5);
    setState(89);
    statements();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DoWhileStatementContext ------------------------------------------------------------------

GrammarParser::DoWhileStatementContext::DoWhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::DoWhileStatementContext::TokDo() {
  return getToken(GrammarParser::TokDo, 0);
}

GrammarParser::StatementsContext* GrammarParser::DoWhileStatementContext::statements() {
  return getRuleContext<GrammarParser::StatementsContext>(0);
}

tree::TerminalNode* GrammarParser::DoWhileStatementContext::TokWhile() {
  return getToken(GrammarParser::TokWhile, 0);
}

GrammarParser::ExprContext* GrammarParser::DoWhileStatementContext::expr() {
  return getRuleContext<GrammarParser::ExprContext>(0);
}


size_t GrammarParser::DoWhileStatementContext::getRuleIndex() const {
  return GrammarParser::RuleDoWhileStatement;
}

antlrcpp::Any GrammarParser::DoWhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitDoWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::DoWhileStatementContext* GrammarParser::doWhileStatement() {
  DoWhileStatementContext *_localctx = _tracker.createInstance<DoWhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 18, GrammarParser::RuleDoWhileStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(91);
    match(GrammarParser::TokDo);
    setState(92);
    statements();
    setState(93);
    match(GrammarParser::TokWhile);
    setState(94);
    match(GrammarParser::T__4);
    setState(95);
    expr(0);
    setState(96);
    match(GrammarParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

GrammarParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::ExprLogicalContext* GrammarParser::ExprContext::exprLogical() {
  return getRuleContext<GrammarParser::ExprLogicalContext>(0);
}

GrammarParser::ExprContext* GrammarParser::ExprContext::expr() {
  return getRuleContext<GrammarParser::ExprContext>(0);
}

tree::TerminalNode* GrammarParser::ExprContext::TokOpLogical() {
  return getToken(GrammarParser::TokOpLogical, 0);
}


size_t GrammarParser::ExprContext::getRuleIndex() const {
  return GrammarParser::RuleExpr;
}

antlrcpp::Any GrammarParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}


GrammarParser::ExprContext* GrammarParser::expr() {
   return expr(0);
}

GrammarParser::ExprContext* GrammarParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  GrammarParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  GrammarParser::ExprContext *previousContext = _localctx;
  size_t startState = 20;
  enterRecursionRule(_localctx, 20, GrammarParser::RuleExpr, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(99);
    exprLogical(0);
    _ctx->stop = _input->LT(-1);
    setState(106);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExpr);
        setState(101);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(102);
        match(GrammarParser::TokOpLogical);
        setState(103);
        exprLogical(0); 
      }
      setState(108);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExprLogicalContext ------------------------------------------------------------------

GrammarParser::ExprLogicalContext::ExprLogicalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::ExprCompareContext* GrammarParser::ExprLogicalContext::exprCompare() {
  return getRuleContext<GrammarParser::ExprCompareContext>(0);
}

GrammarParser::ExprLogicalContext* GrammarParser::ExprLogicalContext::exprLogical() {
  return getRuleContext<GrammarParser::ExprLogicalContext>(0);
}

tree::TerminalNode* GrammarParser::ExprLogicalContext::TokOpCompare() {
  return getToken(GrammarParser::TokOpCompare, 0);
}


size_t GrammarParser::ExprLogicalContext::getRuleIndex() const {
  return GrammarParser::RuleExprLogical;
}

antlrcpp::Any GrammarParser::ExprLogicalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitExprLogical(this);
  else
    return visitor->visitChildren(this);
}


GrammarParser::ExprLogicalContext* GrammarParser::exprLogical() {
   return exprLogical(0);
}

GrammarParser::ExprLogicalContext* GrammarParser::exprLogical(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  GrammarParser::ExprLogicalContext *_localctx = _tracker.createInstance<ExprLogicalContext>(_ctx, parentState);
  GrammarParser::ExprLogicalContext *previousContext = _localctx;
  size_t startState = 22;
  enterRecursionRule(_localctx, 22, GrammarParser::RuleExprLogical, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(110);
    exprCompare(0);
    _ctx->stop = _input->LT(-1);
    setState(117);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExprLogicalContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExprLogical);
        setState(112);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(113);
        match(GrammarParser::TokOpCompare);
        setState(114);
        exprCompare(0); 
      }
      setState(119);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExprCompareContext ------------------------------------------------------------------

GrammarParser::ExprCompareContext::ExprCompareContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::ExprAddSubContext* GrammarParser::ExprCompareContext::exprAddSub() {
  return getRuleContext<GrammarParser::ExprAddSubContext>(0);
}

GrammarParser::ExprCompareContext* GrammarParser::ExprCompareContext::exprCompare() {
  return getRuleContext<GrammarParser::ExprCompareContext>(0);
}

tree::TerminalNode* GrammarParser::ExprCompareContext::TokOpAddSub() {
  return getToken(GrammarParser::TokOpAddSub, 0);
}


size_t GrammarParser::ExprCompareContext::getRuleIndex() const {
  return GrammarParser::RuleExprCompare;
}

antlrcpp::Any GrammarParser::ExprCompareContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitExprCompare(this);
  else
    return visitor->visitChildren(this);
}


GrammarParser::ExprCompareContext* GrammarParser::exprCompare() {
   return exprCompare(0);
}

GrammarParser::ExprCompareContext* GrammarParser::exprCompare(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  GrammarParser::ExprCompareContext *_localctx = _tracker.createInstance<ExprCompareContext>(_ctx, parentState);
  GrammarParser::ExprCompareContext *previousContext = _localctx;
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, GrammarParser::RuleExprCompare, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(121);
    exprAddSub(0);
    _ctx->stop = _input->LT(-1);
    setState(128);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExprCompareContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExprCompare);
        setState(123);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(124);
        match(GrammarParser::TokOpAddSub);
        setState(125);
        exprAddSub(0); 
      }
      setState(130);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExprAddSubContext ------------------------------------------------------------------

GrammarParser::ExprAddSubContext::ExprAddSubContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::ExprMulDivModEtcContext* GrammarParser::ExprAddSubContext::exprMulDivModEtc() {
  return getRuleContext<GrammarParser::ExprMulDivModEtcContext>(0);
}

GrammarParser::ExprAddSubContext* GrammarParser::ExprAddSubContext::exprAddSub() {
  return getRuleContext<GrammarParser::ExprAddSubContext>(0);
}

tree::TerminalNode* GrammarParser::ExprAddSubContext::TokOpMulDivMod() {
  return getToken(GrammarParser::TokOpMulDivMod, 0);
}

tree::TerminalNode* GrammarParser::ExprAddSubContext::TokOpBitwise() {
  return getToken(GrammarParser::TokOpBitwise, 0);
}


size_t GrammarParser::ExprAddSubContext::getRuleIndex() const {
  return GrammarParser::RuleExprAddSub;
}

antlrcpp::Any GrammarParser::ExprAddSubContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitExprAddSub(this);
  else
    return visitor->visitChildren(this);
}


GrammarParser::ExprAddSubContext* GrammarParser::exprAddSub() {
   return exprAddSub(0);
}

GrammarParser::ExprAddSubContext* GrammarParser::exprAddSub(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  GrammarParser::ExprAddSubContext *_localctx = _tracker.createInstance<ExprAddSubContext>(_ctx, parentState);
  GrammarParser::ExprAddSubContext *previousContext = _localctx;
  size_t startState = 26;
  enterRecursionRule(_localctx, 26, GrammarParser::RuleExprAddSub, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(132);
    exprMulDivModEtc();
    _ctx->stop = _input->LT(-1);
    setState(142);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(140);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprAddSubContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExprAddSub);
          setState(134);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(135);
          match(GrammarParser::TokOpMulDivMod);
          setState(136);
          exprMulDivModEtc();
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprAddSubContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExprAddSub);
          setState(137);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(138);
          match(GrammarParser::TokOpBitwise);
          setState(139);
          exprMulDivModEtc();
          break;
        }

        } 
      }
      setState(144);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExprMulDivModEtcContext ------------------------------------------------------------------

GrammarParser::ExprMulDivModEtcContext::ExprMulDivModEtcContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::ExprMulDivModEtcContext::TokDecNum() {
  return getToken(GrammarParser::TokDecNum, 0);
}

GrammarParser::ExprContext* GrammarParser::ExprMulDivModEtcContext::expr() {
  return getRuleContext<GrammarParser::ExprContext>(0);
}


size_t GrammarParser::ExprMulDivModEtcContext::getRuleIndex() const {
  return GrammarParser::RuleExprMulDivModEtc;
}

antlrcpp::Any GrammarParser::ExprMulDivModEtcContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitExprMulDivModEtc(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::ExprMulDivModEtcContext* GrammarParser::exprMulDivModEtc() {
  ExprMulDivModEtcContext *_localctx = _tracker.createInstance<ExprMulDivModEtcContext>(_ctx, getState());
  enterRule(_localctx, 28, GrammarParser::RuleExprMulDivModEtc);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(150);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GrammarParser::TokDecNum: {
        enterOuterAlt(_localctx, 1);
        setState(145);
        match(GrammarParser::TokDecNum);
        break;
      }

      case GrammarParser::T__4: {
        enterOuterAlt(_localctx, 2);
        setState(146);
        match(GrammarParser::T__4);
        setState(147);
        expr(0);
        setState(148);
        match(GrammarParser::T__5);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentExprContext ------------------------------------------------------------------

GrammarParser::IdentExprContext::IdentExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::IdentExprContext::TokIdent() {
  return getToken(GrammarParser::TokIdent, 0);
}


size_t GrammarParser::IdentExprContext::getRuleIndex() const {
  return GrammarParser::RuleIdentExpr;
}

antlrcpp::Any GrammarParser::IdentExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitIdentExpr(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::IdentExprContext* GrammarParser::identExpr() {
  IdentExprContext *_localctx = _tracker.createInstance<IdentExprContext>(_ctx, getState());
  enterRule(_localctx, 30, GrammarParser::RuleIdentExpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(152);
    match(GrammarParser::TokIdent);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool GrammarParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return listStatementSempred(dynamic_cast<ListStatementContext *>(context), predicateIndex);
    case 10: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);
    case 11: return exprLogicalSempred(dynamic_cast<ExprLogicalContext *>(context), predicateIndex);
    case 12: return exprCompareSempred(dynamic_cast<ExprCompareContext *>(context), predicateIndex);
    case 13: return exprAddSubSempred(dynamic_cast<ExprAddSubContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool GrammarParser::listStatementSempred(ListStatementContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool GrammarParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool GrammarParser::exprLogicalSempred(ExprLogicalContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool GrammarParser::exprCompareSempred(ExprCompareContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool GrammarParser::exprAddSubSempred(ExprAddSubContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 2);
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> GrammarParser::_decisionToDFA;
atn::PredictionContextCache GrammarParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN GrammarParser::_atn;
std::vector<uint16_t> GrammarParser::_serializedATN;

std::vector<std::string> GrammarParser::_ruleNames = {
  "program", "statements", "listStatement", "statement", "assignment", "ifStatement", 
  "ifChainStatement", "elseStatements", "whileStatement", "doWhileStatement", 
  "expr", "exprLogical", "exprCompare", "exprAddSub", "exprMulDivModEtc", 
  "identExpr"
};

std::vector<std::string> GrammarParser::_literalNames = {
  "", "'{'", "'}'", "';'", "'='", "'('", "')'", "'if'", "'else'", "'while'", 
  "'do'"
};

std::vector<std::string> GrammarParser::_symbolicNames = {
  "", "", "", "", "", "", "", "TokIf", "TokElse", "TokWhile", "TokDo", "LexWhitespace", 
  "TokOpLogical", "TokOpCompare", "TokOpAddSub", "TokOpMulDivMod", "TokOpBitwise", 
  "TokDecNum", "TokIdent"
};

dfa::Vocabulary GrammarParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> GrammarParser::_tokenNames;

GrammarParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x14, 0x9d, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x3, 0x2, 
    0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x5, 0x4, 0x2c, 0xa, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x30, 
    0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x33, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x5, 0x5, 0x40, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x56, 0xa, 0x9, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x6b, 0xa, 0xc, 0xc, 0xc, 
    0xe, 0xc, 0x6e, 0xb, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x7, 0xd, 0x76, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0x79, 0xb, 
    0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 
    0xe, 0x81, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0x84, 0xb, 0xe, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x7, 0xf, 0x8f, 0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 0x92, 0xb, 0xf, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0x99, 0xa, 
    0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x2, 0x7, 0x6, 0x16, 0x18, 0x1a, 
    0x1c, 0x12, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 
    0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x2, 0x2, 0x2, 0x9b, 0x2, 0x22, 0x3, 0x2, 
    0x2, 0x2, 0x4, 0x24, 0x3, 0x2, 0x2, 0x2, 0x6, 0x2b, 0x3, 0x2, 0x2, 0x2, 
    0x8, 0x3f, 0x3, 0x2, 0x2, 0x2, 0xa, 0x41, 0x3, 0x2, 0x2, 0x2, 0xc, 0x45, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x10, 0x55, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x57, 0x3, 0x2, 0x2, 0x2, 0x14, 0x5d, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0x64, 0x3, 0x2, 0x2, 0x2, 0x18, 0x6f, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x85, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0x98, 0x3, 0x2, 0x2, 0x2, 0x20, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x22, 
    0x23, 0x5, 0x4, 0x3, 0x2, 0x23, 0x3, 0x3, 0x2, 0x2, 0x2, 0x24, 0x25, 
    0x7, 0x3, 0x2, 0x2, 0x25, 0x26, 0x5, 0x6, 0x4, 0x2, 0x26, 0x27, 0x7, 
    0x4, 0x2, 0x2, 0x27, 0x5, 0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 0x8, 0x4, 
    0x1, 0x2, 0x29, 0x2c, 0x5, 0x8, 0x5, 0x2, 0x2a, 0x2c, 0x3, 0x2, 0x2, 
    0x2, 0x2b, 0x28, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2a, 0x3, 0x2, 0x2, 0x2, 
    0x2c, 0x31, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2e, 0xc, 0x4, 0x2, 0x2, 0x2e, 
    0x30, 0x5, 0x8, 0x5, 0x2, 0x2f, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x30, 0x33, 
    0x3, 0x2, 0x2, 0x2, 0x31, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x31, 0x32, 0x3, 
    0x2, 0x2, 0x2, 0x32, 0x7, 0x3, 0x2, 0x2, 0x2, 0x33, 0x31, 0x3, 0x2, 
    0x2, 0x2, 0x34, 0x40, 0x5, 0x4, 0x3, 0x2, 0x35, 0x36, 0x5, 0x16, 0xc, 
    0x2, 0x36, 0x37, 0x7, 0x5, 0x2, 0x2, 0x37, 0x40, 0x3, 0x2, 0x2, 0x2, 
    0x38, 0x39, 0x5, 0xa, 0x6, 0x2, 0x39, 0x3a, 0x7, 0x5, 0x2, 0x2, 0x3a, 
    0x40, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x40, 0x5, 0xc, 0x7, 0x2, 0x3c, 0x40, 
    0x5, 0xe, 0x8, 0x2, 0x3d, 0x40, 0x5, 0x12, 0xa, 0x2, 0x3e, 0x40, 0x5, 
    0x14, 0xb, 0x2, 0x3f, 0x34, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x35, 0x3, 0x2, 
    0x2, 0x2, 0x3f, 0x38, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x3b, 0x3, 0x2, 0x2, 
    0x2, 0x3f, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x3d, 0x3, 0x2, 0x2, 0x2, 
    0x3f, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x40, 0x9, 0x3, 0x2, 0x2, 0x2, 0x41, 
    0x42, 0x5, 0x20, 0x11, 0x2, 0x42, 0x43, 0x7, 0x6, 0x2, 0x2, 0x43, 0x44, 
    0x5, 0x16, 0xc, 0x2, 0x44, 0xb, 0x3, 0x2, 0x2, 0x2, 0x45, 0x46, 0x7, 
    0x9, 0x2, 0x2, 0x46, 0x47, 0x7, 0x7, 0x2, 0x2, 0x47, 0x48, 0x5, 0x16, 
    0xc, 0x2, 0x48, 0x49, 0x7, 0x8, 0x2, 0x2, 0x49, 0x4a, 0x5, 0x4, 0x3, 
    0x2, 0x4a, 0xd, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x7, 0x9, 0x2, 0x2, 
    0x4c, 0x4d, 0x7, 0x7, 0x2, 0x2, 0x4d, 0x4e, 0x5, 0x16, 0xc, 0x2, 0x4e, 
    0x4f, 0x7, 0x8, 0x2, 0x2, 0x4f, 0x50, 0x5, 0x4, 0x3, 0x2, 0x50, 0x51, 
    0x7, 0xa, 0x2, 0x2, 0x51, 0x52, 0x5, 0x10, 0x9, 0x2, 0x52, 0xf, 0x3, 
    0x2, 0x2, 0x2, 0x53, 0x56, 0x5, 0xe, 0x8, 0x2, 0x54, 0x56, 0x5, 0x4, 
    0x3, 0x2, 0x55, 0x53, 0x3, 0x2, 0x2, 0x2, 0x55, 0x54, 0x3, 0x2, 0x2, 
    0x2, 0x56, 0x11, 0x3, 0x2, 0x2, 0x2, 0x57, 0x58, 0x7, 0xb, 0x2, 0x2, 
    0x58, 0x59, 0x7, 0x7, 0x2, 0x2, 0x59, 0x5a, 0x5, 0x16, 0xc, 0x2, 0x5a, 
    0x5b, 0x7, 0x8, 0x2, 0x2, 0x5b, 0x5c, 0x5, 0x4, 0x3, 0x2, 0x5c, 0x13, 
    0x3, 0x2, 0x2, 0x2, 0x5d, 0x5e, 0x7, 0xc, 0x2, 0x2, 0x5e, 0x5f, 0x5, 
    0x4, 0x3, 0x2, 0x5f, 0x60, 0x7, 0xb, 0x2, 0x2, 0x60, 0x61, 0x7, 0x7, 
    0x2, 0x2, 0x61, 0x62, 0x5, 0x16, 0xc, 0x2, 0x62, 0x63, 0x7, 0x8, 0x2, 
    0x2, 0x63, 0x15, 0x3, 0x2, 0x2, 0x2, 0x64, 0x65, 0x8, 0xc, 0x1, 0x2, 
    0x65, 0x66, 0x5, 0x18, 0xd, 0x2, 0x66, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x67, 
    0x68, 0xc, 0x3, 0x2, 0x2, 0x68, 0x69, 0x7, 0xe, 0x2, 0x2, 0x69, 0x6b, 
    0x5, 0x18, 0xd, 0x2, 0x6a, 0x67, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6e, 0x3, 
    0x2, 0x2, 0x2, 0x6c, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x3, 0x2, 
    0x2, 0x2, 0x6d, 0x17, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6c, 0x3, 0x2, 0x2, 
    0x2, 0x6f, 0x70, 0x8, 0xd, 0x1, 0x2, 0x70, 0x71, 0x5, 0x1a, 0xe, 0x2, 
    0x71, 0x77, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0xc, 0x3, 0x2, 0x2, 0x73, 
    0x74, 0x7, 0xf, 0x2, 0x2, 0x74, 0x76, 0x5, 0x1a, 0xe, 0x2, 0x75, 0x72, 
    0x3, 0x2, 0x2, 0x2, 0x76, 0x79, 0x3, 0x2, 0x2, 0x2, 0x77, 0x75, 0x3, 
    0x2, 0x2, 0x2, 0x77, 0x78, 0x3, 0x2, 0x2, 0x2, 0x78, 0x19, 0x3, 0x2, 
    0x2, 0x2, 0x79, 0x77, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7b, 0x8, 0xe, 0x1, 
    0x2, 0x7b, 0x7c, 0x5, 0x1c, 0xf, 0x2, 0x7c, 0x82, 0x3, 0x2, 0x2, 0x2, 
    0x7d, 0x7e, 0xc, 0x3, 0x2, 0x2, 0x7e, 0x7f, 0x7, 0x10, 0x2, 0x2, 0x7f, 
    0x81, 0x5, 0x1c, 0xf, 0x2, 0x80, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x81, 0x84, 
    0x3, 0x2, 0x2, 0x2, 0x82, 0x80, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x3, 
    0x2, 0x2, 0x2, 0x83, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x84, 0x82, 0x3, 0x2, 
    0x2, 0x2, 0x85, 0x86, 0x8, 0xf, 0x1, 0x2, 0x86, 0x87, 0x5, 0x1e, 0x10, 
    0x2, 0x87, 0x90, 0x3, 0x2, 0x2, 0x2, 0x88, 0x89, 0xc, 0x4, 0x2, 0x2, 
    0x89, 0x8a, 0x7, 0x11, 0x2, 0x2, 0x8a, 0x8f, 0x5, 0x1e, 0x10, 0x2, 0x8b, 
    0x8c, 0xc, 0x3, 0x2, 0x2, 0x8c, 0x8d, 0x7, 0x12, 0x2, 0x2, 0x8d, 0x8f, 
    0x5, 0x1e, 0x10, 0x2, 0x8e, 0x88, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8b, 0x3, 
    0x2, 0x2, 0x2, 0x8f, 0x92, 0x3, 0x2, 0x2, 0x2, 0x90, 0x8e, 0x3, 0x2, 
    0x2, 0x2, 0x90, 0x91, 0x3, 0x2, 0x2, 0x2, 0x91, 0x1d, 0x3, 0x2, 0x2, 
    0x2, 0x92, 0x90, 0x3, 0x2, 0x2, 0x2, 0x93, 0x99, 0x7, 0x13, 0x2, 0x2, 
    0x94, 0x95, 0x7, 0x7, 0x2, 0x2, 0x95, 0x96, 0x5, 0x16, 0xc, 0x2, 0x96, 
    0x97, 0x7, 0x8, 0x2, 0x2, 0x97, 0x99, 0x3, 0x2, 0x2, 0x2, 0x98, 0x93, 
    0x3, 0x2, 0x2, 0x2, 0x98, 0x94, 0x3, 0x2, 0x2, 0x2, 0x99, 0x1f, 0x3, 
    0x2, 0x2, 0x2, 0x9a, 0x9b, 0x7, 0x14, 0x2, 0x2, 0x9b, 0x21, 0x3, 0x2, 
    0x2, 0x2, 0xc, 0x2b, 0x31, 0x3f, 0x55, 0x6c, 0x77, 0x82, 0x8e, 0x90, 
    0x98, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

GrammarParser::Initializer GrammarParser::_init;
