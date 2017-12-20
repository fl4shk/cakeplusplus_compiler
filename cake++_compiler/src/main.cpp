#include <stdio.h>
#include <stdlib.h>

#include "misc_includes.hpp"


//#include "gen_src/GrammarLexer.h"
//#include "gen_src/GrammarParser.h"
//static constexpr int some_eof = EOF;
//#include "interpreter_class.hpp"
//#include "frontend_class.hpp"

#include "symbol_table_base_class.hpp"
#include "allocation_stuff.hpp"

class FakeSymbol
{
private:		// variables
	Ident __name;

public:		// functions
	

	gen_getter_and_setter_by_con_ref(name);
	gen_setter_by_rval_ref(name);

};


int main(int argc, char** argv)
{
	//std::string from_stdin(get_stdin_as_str());

	//antlr4::ANTLRInputStream input(from_stdin);
	//GrammarLexer lexer(&input);
	//antlr4::CommonTokenStream tokens(&lexer);
	//tokens.fill();

	//GrammarParser parser(&tokens);
	//parser.removeErrorListeners();
	//std::unique_ptr<FrntErrorListener> cstm_error_listener
	//	(new FrntErrorListener());
	//parser.addErrorListener(cstm_error_listener.get());

	//Frontend visitor;
	//visitor.visitProgram(parser.program());

	SymbolTableBase<FakeSymbol> sym_tbl;

	//auto temp = sym_tbl.find_in_this_blklev(cstm_strdup("aaa"));

	sym_tbl.mkscope();

		sym_tbl.mkscope();
		sym_tbl.rmscope();
		sym_tbl.mkscope();
		sym_tbl.rmscope();
		sym_tbl.mkscope();
		sym_tbl.rmscope();

		sym_tbl.mkscope();

			sym_tbl.mkscope();

				sym_tbl.mkscope();
				sym_tbl.rmscope();
				sym_tbl.mkscope();
					sym_tbl.mkscope();
						sym_tbl.mkscope();
						sym_tbl.rmscope();
					sym_tbl.rmscope();
				sym_tbl.rmscope();
				sym_tbl.mkscope();
				sym_tbl.rmscope();

			sym_tbl.rmscope();

		sym_tbl.rmscope();

	sym_tbl.rmscope();

	sym_tbl.mkscope();

		sym_tbl.mkscope();
		sym_tbl.rmscope();

		sym_tbl.mkscope();

			sym_tbl.mkscope();
			sym_tbl.rmscope();
			sym_tbl.mkscope();
			sym_tbl.rmscope();

		sym_tbl.rmscope();

		sym_tbl.mkscope();

			sym_tbl.mkscope();
			sym_tbl.rmscope();
			sym_tbl.mkscope();
			sym_tbl.rmscope();

		sym_tbl.rmscope();

	
	sym_tbl.rmscope();

	//auto temp_2 = sym_tbl.find_in_this_blklev(cstm_strdup("aaa"));
	
	//printout(temp, " ", temp_2, "\n");

	//sym_tbl.tree().print();


	return 0;
}
