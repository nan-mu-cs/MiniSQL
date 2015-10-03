// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "sqlparser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "sqlparser.hh"

// User implementation prologue.

#line 51 "sqlparser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 27 "sqlparser.yy" // lalr1.cc:413

	#include "sqlparser_driver.hh"

#line 57 "sqlparser.cpp" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 143 "sqlparser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  sqlparser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  sqlparser::sqlparser (sqlparser_driver &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  sqlparser::~sqlparser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  sqlparser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  sqlparser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  sqlparser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  sqlparser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  sqlparser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  sqlparser::symbol_number_type
  sqlparser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  sqlparser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  sqlparser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 6: // FLOATNUM
      case 67: // floatexp
        value.move< float > (that.value);
        break;

      case 5: // INTNUM
      case 22: // DEFAULT
      case 23: // AUTO_INCREMENT
      case 29: // NULLX
      case 35: // UNIQUE
      case 37: // PRIMARY
      case 60: // COMPARISON
      case 66: // intexp
      case 81: // opt_length
      case 82: // data_type
        value.move< int > (that.value);
        break;

      case 65: // expr
      case 70: // opt_where
        value.move< sqlstruct::astree* > (that.value);
        break;

      case 78: // create_col_list
        value.move< sqlstruct::create_col_list > (that.value);
        break;

      case 83: // create_index_stmt
        value.move< sqlstruct::createindex > (that.value);
        break;

      case 77: // create_table_stmt
        value.move< sqlstruct::createtable > (that.value);
        break;

      case 73: // delete_stmt
        value.move< sqlstruct::deletetable > (that.value);
        break;

      case 85: // drop_index_stmt
        value.move< sqlstruct::dropindex > (that.value);
        break;

      case 74: // insert_stmt
        value.move< sqlstruct::insertvalues > (that.value);
        break;

      case 79: // create_definition
        value.move< sqlstruct::record_t > (that.value);
        break;

      case 69: // select_stmt
        value.move< sqlstruct::selecttable > (that.value);
        break;

      case 3: // NAME
      case 4: // STRING
      case 84: // drop_table_stmt
      case 87: // execfile_stmt
        value.move< std::string > (that.value);
        break;

      case 80: // column_atts
        value.move< std::vector<sqlstruct::col_attr> > (that.value);
        break;

      case 76: // insert_vals
        value.move< std::vector<sqlstruct::insertitem> > (that.value);
        break;

      case 71: // column_list
      case 72: // select_expr_list
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  sqlparser::stack_symbol_type&
  sqlparser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 6: // FLOATNUM
      case 67: // floatexp
        value.copy< float > (that.value);
        break;

      case 5: // INTNUM
      case 22: // DEFAULT
      case 23: // AUTO_INCREMENT
      case 29: // NULLX
      case 35: // UNIQUE
      case 37: // PRIMARY
      case 60: // COMPARISON
      case 66: // intexp
      case 81: // opt_length
      case 82: // data_type
        value.copy< int > (that.value);
        break;

      case 65: // expr
      case 70: // opt_where
        value.copy< sqlstruct::astree* > (that.value);
        break;

      case 78: // create_col_list
        value.copy< sqlstruct::create_col_list > (that.value);
        break;

      case 83: // create_index_stmt
        value.copy< sqlstruct::createindex > (that.value);
        break;

      case 77: // create_table_stmt
        value.copy< sqlstruct::createtable > (that.value);
        break;

      case 73: // delete_stmt
        value.copy< sqlstruct::deletetable > (that.value);
        break;

      case 85: // drop_index_stmt
        value.copy< sqlstruct::dropindex > (that.value);
        break;

      case 74: // insert_stmt
        value.copy< sqlstruct::insertvalues > (that.value);
        break;

      case 79: // create_definition
        value.copy< sqlstruct::record_t > (that.value);
        break;

      case 69: // select_stmt
        value.copy< sqlstruct::selecttable > (that.value);
        break;

      case 3: // NAME
      case 4: // STRING
      case 84: // drop_table_stmt
      case 87: // execfile_stmt
        value.copy< std::string > (that.value);
        break;

      case 80: // column_atts
        value.copy< std::vector<sqlstruct::col_attr> > (that.value);
        break;

      case 76: // insert_vals
        value.copy< std::vector<sqlstruct::insertitem> > (that.value);
        break;

      case 71: // column_list
      case 72: // select_expr_list
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  sqlparser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  sqlparser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  sqlparser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  sqlparser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  sqlparser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  sqlparser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  sqlparser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  sqlparser::debug_level_type
  sqlparser::debug_level () const
  {
    return yydebug_;
  }

  void
  sqlparser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline sqlparser::state_type
  sqlparser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  sqlparser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  sqlparser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  sqlparser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 22 "sqlparser.yy" // lalr1.cc:745
{
	yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 566 "sqlparser.cpp" // lalr1.cc:745

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 6: // FLOATNUM
      case 67: // floatexp
        yylhs.value.build< float > ();
        break;

      case 5: // INTNUM
      case 22: // DEFAULT
      case 23: // AUTO_INCREMENT
      case 29: // NULLX
      case 35: // UNIQUE
      case 37: // PRIMARY
      case 60: // COMPARISON
      case 66: // intexp
      case 81: // opt_length
      case 82: // data_type
        yylhs.value.build< int > ();
        break;

      case 65: // expr
      case 70: // opt_where
        yylhs.value.build< sqlstruct::astree* > ();
        break;

      case 78: // create_col_list
        yylhs.value.build< sqlstruct::create_col_list > ();
        break;

      case 83: // create_index_stmt
        yylhs.value.build< sqlstruct::createindex > ();
        break;

      case 77: // create_table_stmt
        yylhs.value.build< sqlstruct::createtable > ();
        break;

      case 73: // delete_stmt
        yylhs.value.build< sqlstruct::deletetable > ();
        break;

      case 85: // drop_index_stmt
        yylhs.value.build< sqlstruct::dropindex > ();
        break;

      case 74: // insert_stmt
        yylhs.value.build< sqlstruct::insertvalues > ();
        break;

      case 79: // create_definition
        yylhs.value.build< sqlstruct::record_t > ();
        break;

      case 69: // select_stmt
        yylhs.value.build< sqlstruct::selecttable > ();
        break;

      case 3: // NAME
      case 4: // STRING
      case 84: // drop_table_stmt
      case 87: // execfile_stmt
        yylhs.value.build< std::string > ();
        break;

      case 80: // column_atts
        yylhs.value.build< std::vector<sqlstruct::col_attr> > ();
        break;

      case 76: // insert_vals
        yylhs.value.build< std::vector<sqlstruct::insertitem> > ();
        break;

      case 71: // column_list
      case 72: // select_expr_list
        yylhs.value.build< std::vector<std::string> > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 6:
#line 125 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::astree* > () = driver.newLeafNode(yystack_[0].value.as< std::string > ()); }
#line 751 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 126 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::astree* > () = driver.newLeafNode(itostr(yystack_[0].value.as< int > ()));}
#line 757 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 127 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::astree* > () = driver.newLeafNode(ftostr(yystack_[0].value.as< float > ()));}
#line 763 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 128 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::astree* > () = yystack_[1].value.as< sqlstruct::astree* > ();}
#line 769 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 129 "sqlparser.yy" // lalr1.cc:859
    {std::cout << "In and"<< std::endl;yylhs.value.as< sqlstruct::astree* > () = driver.newInternalNode(yystack_[2].value.as< sqlstruct::astree* > (),sqlstruct::AND,yystack_[0].value.as< sqlstruct::astree* > ());}
#line 775 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 130 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::astree* > () = driver.newInternalNode(yystack_[2].value.as< sqlstruct::astree* > (),sqlstruct::OR,yystack_[0].value.as< sqlstruct::astree* > ());}
#line 781 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 131 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::astree* > () = driver.newInternalNode(yystack_[0].value.as< sqlstruct::astree* > (),sqlstruct::NOT,NULL);}
#line 787 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 132 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::astree* > () = driver.newInternalNode(yystack_[0].value.as< sqlstruct::astree* > (),sqlstruct::NOT,NULL);}
#line 793 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 133 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::astree* > () = driver.newInternalNode(yystack_[2].value.as< sqlstruct::astree* > (),yystack_[1].value.as< int > (),yystack_[0].value.as< sqlstruct::astree* > ());}
#line 799 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 134 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::astree* > () = driver.newInternalNode(yystack_[2].value.as< sqlstruct::astree* > (),sqlstruct::ISNULL,NULL);}
#line 805 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 135 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::astree* > () = driver.newInternalNode(yystack_[3].value.as< sqlstruct::astree* > (),sqlstruct::ISNULL,NULL); yylhs.value.as< sqlstruct::astree* > () = driver.newInternalNode(yylhs.value.as< sqlstruct::astree* > (),sqlstruct::NOT,NULL);}
#line 811 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 136 "sqlparser.yy" // lalr1.cc:859
    { 
						    sqlstruct::astree *left,*right;
						    left = driver.newInternalNode(yystack_[4].value.as< sqlstruct::astree* > (),sqlstruct::GREATOREQUAL,yystack_[2].value.as< sqlstruct::astree* > ());
						    right = driver.newInternalNode(yystack_[4].value.as< sqlstruct::astree* > (),sqlstruct::LESSOREQUAL,yystack_[0].value.as< sqlstruct::astree* > ());
						    yylhs.value.as< sqlstruct::astree* > () = driver.newInternalNode(left,sqlstruct::AND,right);}
#line 821 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 145 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[0].value.as< int > ();}
#line 827 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 146 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[2].value.as< int > () + yystack_[0].value.as< int > ();}
#line 833 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 147 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[2].value.as< int > () + yystack_[0].value.as< int > ();}
#line 839 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 148 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[2].value.as< int > () * yystack_[0].value.as< int > ();}
#line 845 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 149 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[2].value.as< int > () / yystack_[0].value.as< int > ();}
#line 851 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 150 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = -yystack_[0].value.as< int > ();}
#line 857 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 151 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[2].value.as< int > () | yystack_[0].value.as< int > ();}
#line 863 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 152 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[2].value.as< int > () & yystack_[0].value.as< int > ();}
#line 869 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 153 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = !yystack_[0].value.as< int > ();}
#line 875 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 154 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[1].value.as< int > ();}
#line 881 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 157 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[0].value.as< float > ();}
#line 887 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 158 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< float > () + yystack_[0].value.as< float > ();}
#line 893 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 159 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< float > () + yystack_[0].value.as< int > ();}
#line 899 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 160 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< int > () + yystack_[0].value.as< float > ();}
#line 905 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 161 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< float > () - yystack_[0].value.as< float > ();}
#line 911 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 162 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< float > () - yystack_[0].value.as< int > ();}
#line 917 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 163 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< int > () - yystack_[0].value.as< float > ();}
#line 923 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 164 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< float > () * yystack_[0].value.as< float > ();}
#line 929 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 165 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< float > () * yystack_[0].value.as< int > ();}
#line 935 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 166 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< int > () * yystack_[0].value.as< float > ();}
#line 941 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 167 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< float > () / yystack_[0].value.as< float > ();}
#line 947 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 168 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< float > () / yystack_[0].value.as< int > ();}
#line 953 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 169 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< int > () / yystack_[0].value.as< float > ();}
#line 959 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 170 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = -yystack_[0].value.as< float > ();}
#line 965 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 171 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[1].value.as< float > ();}
#line 971 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 184 "sqlparser.yy" // lalr1.cc:859
    {driver.Select(yystack_[0].value.as< sqlstruct::selecttable > ());}
#line 977 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 187 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< sqlstruct::selecttable > ()).col = yystack_[3].value.as< std::vector<std::string> > ();(yylhs.value.as< sqlstruct::selecttable > ()).fromtable = yystack_[1].value.as< std::string > ();
	   							(yylhs.value.as< sqlstruct::selecttable > ()).where = yystack_[0].value.as< sqlstruct::astree* > ();
								if((yystack_[3].value.as< std::vector<std::string> > ()).size() == 0) (yylhs.value.as< sqlstruct::selecttable > ()).selectall = true;
								else (yylhs.value.as< sqlstruct::selecttable > ()).selectall = false;}
#line 986 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 193 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::astree* > () = NULL;}
#line 992 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 194 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::astree* > () = yystack_[0].value.as< sqlstruct::astree* > ();}
#line 998 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 224 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< std::vector<std::string> > ()).clear(); (yylhs.value.as< std::vector<std::string> > ()).push_back(yystack_[0].value.as< std::string > ());}
#line 1004 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 225 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< std::vector<std::string> > ()).clear(); (yylhs.value.as< std::vector<std::string> > ()).push_back(yystack_[0].value.as< std::string > ());}
#line 1010 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 226 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< std::vector<std::string> > () = yystack_[2].value.as< std::vector<std::string> > ();(yystack_[2].value.as< std::vector<std::string> > ()).push_back(yystack_[0].value.as< std::string > ());}
#line 1016 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 227 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< std::vector<std::string> > () = yystack_[2].value.as< std::vector<std::string> > ();(yystack_[2].value.as< std::vector<std::string> > ()).push_back(yystack_[0].value.as< std::string > ());}
#line 1022 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 230 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< std::vector<std::string> > ()).clear();(yylhs.value.as< std::vector<std::string> > ()).push_back(yystack_[0].value.as< std::string > ());}
#line 1028 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 231 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< std::vector<std::string> > () = yystack_[2].value.as< std::vector<std::string> > ();(yylhs.value.as< std::vector<std::string> > ()).push_back(yystack_[0].value.as< std::string > ());}
#line 1034 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 232 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< std::vector<std::string> > ()).clear(); }
#line 1040 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 260 "sqlparser.yy" // lalr1.cc:859
    {driver.Delete(yystack_[0].value.as< sqlstruct::deletetable > ());}
#line 1046 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 263 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< sqlstruct::deletetable > ()).fromtable = yystack_[1].value.as< std::string > ();(yylhs.value.as< sqlstruct::deletetable > ()).where = yystack_[0].value.as< sqlstruct::astree* > (); if(yystack_[0].value.as< sqlstruct::astree* > () == NULL) (yylhs.value.as< sqlstruct::deletetable > ()).deleteall = true;else (yylhs.value.as< sqlstruct::deletetable > ()).deleteall = false; }
#line 1052 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 266 "sqlparser.yy" // lalr1.cc:859
    {driver.InsertValues(yystack_[0].value.as< sqlstruct::insertvalues > ());}
#line 1058 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 270 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< sqlstruct::insertvalues > ()).tablename = yystack_[4].value.as< std::string > ();(yylhs.value.as< sqlstruct::insertvalues > ()).item = yystack_[1].value.as< std::vector<sqlstruct::insertitem> > ();}
#line 1064 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 279 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).clear(); sqlstruct::insertitem item;item.data_type = sqlstruct::STRING;item.value = yystack_[0].value.as< std::string > ();(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).push_back(item); }
#line 1070 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 280 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).clear();sqlstruct::insertitem item;item.data_type = sqlstruct::INTNUM;item.value = itostr(yystack_[0].value.as< int > ());(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).push_back(item);}
#line 1076 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 281 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).clear();sqlstruct::insertitem item;item.data_type = sqlstruct::FLOATNUM;item.value = ftostr(yystack_[0].value.as< float > ());(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).push_back(item);}
#line 1082 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 282 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::insertitem item;item.data_type = sqlstruct::DEFAULT;(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).push_back(item);}
#line 1088 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 283 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::insertitem item;item.data_type = sqlstruct::STRING;item.value = yystack_[0].value.as< std::string > ();yylhs.value.as< std::vector<sqlstruct::insertitem> > () = yystack_[2].value.as< std::vector<sqlstruct::insertitem> > ();(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).push_back(item);}
#line 1094 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 284 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::insertitem item;item.data_type = sqlstruct::INTNUM;item.value = itostr(yystack_[0].value.as< int > ());yylhs.value.as< std::vector<sqlstruct::insertitem> > () = yystack_[2].value.as< std::vector<sqlstruct::insertitem> > ();(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).push_back(item);}
#line 1100 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 285 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::insertitem item;item.data_type = sqlstruct::FLOATNUM;item.value = ftostr(yystack_[0].value.as< float > ());yylhs.value.as< std::vector<sqlstruct::insertitem> > () = yystack_[2].value.as< std::vector<sqlstruct::insertitem> > ();(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).push_back(item);}
#line 1106 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 286 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::insertitem item;item.data_type = sqlstruct::DEFAULT;}
#line 1112 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 301 "sqlparser.yy" // lalr1.cc:859
    {
    		//emit("STMT");
		driver.Createtable(yystack_[0].value.as< sqlstruct::createtable > ());
	}
#line 1121 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 306 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< sqlstruct::createtable > ()).name = yystack_[3].value.as< std::string > ();(yylhs.value.as< sqlstruct::createtable > ()).col = yystack_[1].value.as< sqlstruct::create_col_list > (); }
#line 1127 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 309 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< sqlstruct::create_col_list > ()).record.clear();(yylhs.value.as< sqlstruct::create_col_list > ()).record.push_back(yystack_[0].value.as< sqlstruct::record_t > ());}
#line 1133 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 310 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::create_col_list > () = yystack_[2].value.as< sqlstruct::create_col_list > ();(yylhs.value.as< sqlstruct::create_col_list > ()).record.push_back(yystack_[0].value.as< sqlstruct::record_t > ());}
#line 1139 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 311 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::create_col_list > () = yystack_[6].value.as< sqlstruct::create_col_list > ();(yylhs.value.as< sqlstruct::create_col_list > ()).primarykey = yystack_[1].value.as< std::vector<std::string> > ();}
#line 1145 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 312 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::create_col_list > () = yystack_[5].value.as< sqlstruct::create_col_list > ();(yylhs.value.as< sqlstruct::create_col_list > ()).indexkey = yystack_[1].value.as< std::vector<std::string> > ();}
#line 1151 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 314 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< sqlstruct::record_t > ()).name = yystack_[2].value.as< std::string > ();(yylhs.value.as< sqlstruct::record_t > ()).data_type = yystack_[1].value.as< int > ();(yylhs.value.as< sqlstruct::record_t > ()).attr = yystack_[0].value.as< std::vector<sqlstruct::col_attr> > (); }
#line 1157 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 316 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).clear();}
#line 1163 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 317 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr; attr.type = yystack_[0].value.as< int > () + 1000;yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[2].value.as< std::vector<sqlstruct::col_attr> > ();(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1169 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 318 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr; attr.type = yystack_[0].value.as< int > ();yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[1].value.as< std::vector<sqlstruct::col_attr> > ();(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1175 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 319 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr;attr.type = yystack_[1].value.as< int > (); attr.value = yystack_[0].value.as< std::string > (); yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[2].value.as< std::vector<sqlstruct::col_attr> > ();(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1181 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 320 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr;attr.type = yystack_[1].value.as< int > ();attr.value = itostr(yystack_[0].value.as< int > ());yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[2].value.as< std::vector<sqlstruct::col_attr> > ();(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1187 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 321 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr;attr.type = yystack_[1].value.as< int > (); attr.value = ftostr(yystack_[0].value.as< float > ());yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[2].value.as< std::vector<sqlstruct::col_attr> > ();(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1193 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 322 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr; attr.type = yystack_[0].value.as< int > ();yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[1].value.as< std::vector<sqlstruct::col_attr> > ();(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1199 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 323 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr;attr.type = yystack_[0].value.as< int > ();yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[1].value.as< std::vector<sqlstruct::col_attr> > ();(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1205 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 324 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr;attr.type = yystack_[1].value.as< int > ();yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[2].value.as< std::vector<sqlstruct::col_attr> > (); (yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1211 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 327 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 0;}
#line 1217 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 328 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[1].value.as< int > ();}
#line 1223 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 330 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 40000;}
#line 1229 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 331 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 120000 + yystack_[0].value.as< int > ();}
#line 1235 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 332 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 90000;}
#line 1241 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 333 "sqlparser.yy" // lalr1.cc:859
    {driver.CreateIndex(yystack_[0].value.as< sqlstruct::createindex > ());}
#line 1247 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 334 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< sqlstruct::createindex > ()).indexname = yystack_[5].value.as< std::string > ();(yylhs.value.as< sqlstruct::createindex > ()).tablename = yystack_[3].value.as< std::string > ();(yylhs.value.as< sqlstruct::createindex > ()).col = yystack_[1].value.as< std::vector<std::string> > (); }
#line 1253 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 336 "sqlparser.yy" // lalr1.cc:859
    {driver.DropTable(yystack_[0].value.as< std::string > ());}
#line 1259 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 338 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1265 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 340 "sqlparser.yy" // lalr1.cc:859
    {driver.DropIndex(yystack_[0].value.as< sqlstruct::dropindex > ());}
#line 1271 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 342 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< sqlstruct::dropindex > ()).indexname = yystack_[5].value.as< std::string > ();(yylhs.value.as< sqlstruct::dropindex > ()).tablename = yystack_[3].value.as< std::string > ();(yylhs.value.as< sqlstruct::dropindex > ()).col = yystack_[1].value.as< std::vector<std::string> > (); }
#line 1277 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 344 "sqlparser.yy" // lalr1.cc:859
    {driver.Exit();}
#line 1283 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 348 "sqlparser.yy" // lalr1.cc:859
    {driver.ExecFile(yystack_[0].value.as< std::string > ());}
#line 1289 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 350 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1295 "sqlparser.cpp" // lalr1.cc:859
    break;


#line 1299 "sqlparser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  sqlparser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  sqlparser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char sqlparser::yypact_ninf_ = -95;

  const signed char sqlparser::yytable_ninf_ = -1;

  const short int
  sqlparser::yypact_[] =
  {
     117,   -44,    -3,   -11,   -95,     6,    68,     7,   -16,   125,
     -23,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,    58,    61,    65,   -95,    85,   105,   -95,   -95,    47,
     -95,   119,   -95,    50,    86,   -95,    94,   142,   -95,   150,
      99,   148,   186,   162,   -95,   -95,    27,   -95,   188,   198,
     210,    94,   -95,   156,   -95,   -95,   -95,    80,    27,    27,
      27,   147,   108,   187,   200,   201,   153,   -33,   -95,   -95,
      74,    80,    26,   -95,   -95,   137,   116,   181,   147,   108,
      16,    27,    27,    -8,    27,    27,    80,    80,    80,    80,
      26,    26,    80,    80,    80,    80,    87,    87,   202,   -95,
     -95,   -95,   -95,    52,   -95,   -95,   108,   187,    67,   116,
     181,    26,    26,   132,   -95,   -95,   -95,   159,   127,   -95,
     213,     3,   -95,    73,    95,    73,    95,   -95,   -95,   -95,
     -95,   191,   169,   134,    95,   134,    95,    11,   -95,    11,
     -95,   -95,   -95,   101,   172,   219,   -95,    72,   203,   235,
     -95,   -95,    77,   -95,   124,    26,    26,    26,    26,   -95,
      27,   -95,   231,   -95,   204,   199,   -95,   -95,   -95,   237,
     221,    87,   208,   -95,   -95,   108,   187,   195,   195,   -95,
     -95,   192,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     194,    87,   -95,   196,   -95
  };

  const unsigned char
  sqlparser::yydefact_[] =
  {
       0,     0,     0,     0,    95,     0,     0,     0,     0,     0,
       0,    43,    54,    56,    67,    88,    90,    92,    94,    96,
       4,     0,     0,     0,    97,     0,     0,    51,    53,     0,
      58,     0,     1,     0,     0,     2,    45,     0,    91,     0,
       0,     0,     0,     0,     5,     3,     0,    55,     0,     0,
       0,    45,    52,     0,     6,    18,    28,     0,     0,     0,
       0,    46,     7,     8,     0,     0,     0,     0,    69,    44,
       0,     0,     0,    23,    41,     0,     7,     8,    13,     7,
      12,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    83,    85,
      87,    74,    68,     0,    59,    62,    60,    61,     0,     0,
       0,     0,     0,    26,     9,    27,    42,    11,    10,    15,
       0,     0,    14,    20,    34,    19,    31,    21,    37,    22,
      40,    25,    24,    33,    32,    30,    29,    36,    35,    39,
      38,    47,    48,     0,     0,     0,    86,    73,     0,     0,
      70,    57,     0,    23,     0,     0,     0,     0,     0,    16,
       0,    93,     0,    89,     0,     0,    80,    76,    81,     0,
       0,     0,     0,    63,    66,    64,    65,    20,    19,    21,
      22,    17,    49,    50,    84,    77,    78,    79,    82,    75,
       0,     0,    72,     0,    71
  };

  const short int
  sqlparser::yypgoto_[] =
  {
     -95,   -95,   -58,   -52,   -42,   244,   -95,   205,   -94,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   151,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95
  };

  const short int
  sqlparser::yydefgoto_[] =
  {
      -1,     9,    61,    62,    63,    10,    11,    47,   143,    29,
      12,    13,    31,   108,    14,    67,    68,   147,   146,   101,
      15,    16,    17,    18,    19
  };

  const unsigned char
  sqlparser::yytable_[] =
  {
      75,    78,    80,   144,    20,    73,    76,    79,    22,    24,
      27,   102,   103,   160,    23,    74,    77,    21,   106,   109,
     113,   119,    30,   117,   118,    35,   121,   122,   107,   110,
      54,    55,    55,    56,   123,   125,   127,   129,   131,   132,
     133,   135,   137,   139,   124,   126,   128,   130,    28,   120,
     134,   136,   138,   140,    81,    66,    82,    90,    83,   153,
     154,    36,    84,    85,    37,   111,    57,    41,    38,   112,
      58,   148,    91,    72,    59,    84,    85,   190,   104,    55,
      56,   173,    55,    56,    60,    55,    56,    25,    39,   149,
     141,   142,    42,    26,   165,   166,   105,   193,    44,   174,
     175,   167,   181,   177,   178,   179,   180,   168,    40,   169,
     176,   151,   152,    57,    88,    89,    57,    71,     1,    57,
      71,    72,    43,    71,    72,    32,    33,    72,    46,   170,
       2,     3,     4,     5,    45,     6,    94,    95,     2,     3,
       4,     5,    50,     6,     7,   161,   162,    86,    87,    88,
      89,    51,     7,     8,    90,    86,    87,    88,    89,    48,
     115,     8,    90,   155,   156,   157,   158,    49,   115,    91,
      90,   155,   156,   157,   158,    88,    89,    91,    90,    98,
      90,   114,    83,    99,   100,    91,    84,    85,    81,    52,
      82,    64,    83,    91,    53,    91,    84,    85,    81,    70,
      82,    65,    83,   185,   186,   187,    84,    85,   155,   156,
     157,   158,    82,    66,    83,    90,   163,   162,    84,    85,
      92,    93,    94,    95,   164,   116,    92,    93,    94,    95,
     155,   156,   157,   158,   182,   183,   157,   158,   192,   162,
     194,   162,   159,    96,    97,   145,   171,   172,   184,   188,
     189,   191,    85,    34,   150,     0,    69
  };

  const short int
  sqlparser::yycheck_[] =
  {
      58,    59,    60,    97,    48,    57,    58,    59,    19,     3,
       3,    44,    45,    10,    25,    57,    58,    20,    70,    71,
      72,    29,    38,    81,    82,    48,    84,    85,    70,    71,
       3,     5,     5,     6,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    86,    87,    88,    89,    41,    57,
      92,    93,    94,    95,    51,     3,    53,    46,    55,   111,
     112,     3,    59,    60,     3,    39,    39,    20,     3,    43,
      43,    19,    61,    47,    47,    59,    60,   171,     4,     5,
       6,     4,     5,     6,    57,     5,     6,    19,     3,    37,
       3,     4,    45,    25,    22,    23,    22,   191,    48,    22,
     152,    29,   160,   155,   156,   157,   158,    35,     3,    37,
     152,    44,    45,    39,    41,    42,    39,    43,     1,    39,
      43,    47,     3,    43,    47,     0,     1,    47,    34,    57,
      13,    14,    15,    16,    48,    18,    41,    42,    13,    14,
      15,    16,    43,    18,    27,    44,    45,    39,    40,    41,
      42,     3,    27,    36,    46,    39,    40,    41,    42,    17,
      44,    36,    46,    39,    40,    41,    42,    17,    44,    61,
      46,    39,    40,    41,    42,    41,    42,    61,    46,    26,
      46,    44,    55,    30,    31,    61,    59,    60,    51,     3,
      53,     3,    55,    61,    32,    61,    59,    60,    51,    43,
      53,     3,    55,     4,     5,     6,    59,    60,    39,    40,
      41,    42,    53,     3,    55,    46,    44,    45,    59,    60,
      39,    40,    41,    42,     5,    44,    39,    40,    41,    42,
      39,    40,    41,    42,     3,     4,    41,    42,    44,    45,
      44,    45,    29,    43,    43,    43,    43,    12,    44,    12,
      29,    43,    60,     9,   103,    -1,    51
  };

  const unsigned char
  sqlparser::yystos_[] =
  {
       0,     1,    13,    14,    15,    16,    18,    27,    36,    64,
      68,    69,    73,    74,    77,    83,    84,    85,    86,    87,
      48,    20,    19,    25,     3,    19,    25,     3,    41,    72,
      38,    75,     0,     1,    68,    48,     3,     3,     3,     3,
       3,    20,    45,     3,    48,    48,    34,    70,    17,    17,
      43,     3,     3,    32,     3,     5,     6,    39,    43,    47,
      57,    65,    66,    67,     3,     3,     3,    78,    79,    70,
      43,    43,    47,    66,    67,    65,    66,    67,    65,    66,
      65,    51,    53,    55,    59,    60,    39,    40,    41,    42,
      46,    61,    39,    40,    41,    42,    43,    43,    26,    30,
      31,    82,    44,    45,     4,    22,    66,    67,    76,    66,
      67,    39,    43,    66,    44,    44,    44,    65,    65,    29,
      57,    65,    65,    66,    67,    66,    67,    66,    67,    66,
      67,    66,    66,    66,    67,    66,    67,    66,    67,    66,
      67,     3,     4,    71,    71,    43,    81,    80,    19,    37,
      79,    44,    45,    66,    66,    39,    40,    41,    42,    29,
      10,    44,    45,    44,     5,    22,    23,    29,    35,    37,
      57,    43,    12,     4,    22,    66,    67,    66,    66,    66,
      66,    65,     3,     4,    44,     4,     5,     6,    12,    29,
      71,    43,    44,    71,    44
  };

  const unsigned char
  sqlparser::yyr1_[] =
  {
       0,    63,    64,    64,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    68,    69,    70,    70,    71,    71,    71,
      71,    72,    72,    72,    68,    73,    68,    74,    75,    76,
      76,    76,    76,    76,    76,    76,    76,    68,    77,    78,
      78,    78,    78,    79,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    81,    81,    82,    82,    82,    68,    83,
      68,    84,    68,    85,    68,    86,    68,    87
  };

  const unsigned char
  sqlparser::yyr2_[] =
  {
       0,     2,     2,     3,     2,     3,     1,     1,     1,     3,
       3,     3,     2,     2,     3,     3,     4,     5,     1,     3,
       3,     3,     3,     2,     3,     3,     2,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     1,     5,     0,     2,     1,     1,     3,
       3,     1,     3,     1,     1,     4,     1,     7,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     1,     6,     1,
       3,     7,     6,     3,     0,     3,     2,     3,     3,     3,
       2,     2,     3,     0,     3,     1,     2,     1,     1,     8,
       1,     3,     1,     8,     1,     1,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const sqlparser::yytname_[] =
  {
  "END", "error", "$undefined", "NAME", "STRING", "INTNUM", "FLOATNUM",
  "ADD", "ALL", "ALTER", "AND", "AS", "KEY", "DELETE", "DROP", "QUIT",
  "EXECFILE", "ON", "CREATE", "INDEX", "FROM", "UPDATE", "DEFAULT",
  "AUTO_INCREMENT", "EXISTS", "TABLE", "CHAR", "SELECT", "SET", "NULLX",
  "INT", "FLOAT", "VALUES", "DISTINCT", "WHERE", "UNIQUE", "INSERT",
  "PRIMARY", "INTO", "\"-\"", "\"+\"", "\"*\"", "\"/\"", "\"(\"", "\")\"",
  "\",\"", "\"&\"", "\"!\"", "\";\"", "\".\"", "ASSIGN", "OR", "XOR",
  "ANDOP", "IN", "IS", "LIKE", "NOT", "'!'", "BETWEEN", "COMPARISON",
  "\"|\"", "UMINUS", "$accept", "stmt_list", "expr", "intexp", "floatexp",
  "stmt", "select_stmt", "opt_where", "column_list", "select_expr_list",
  "delete_stmt", "insert_stmt", "opt_into", "insert_vals",
  "create_table_stmt", "create_col_list", "create_definition",
  "column_atts", "opt_length", "data_type", "create_index_stmt",
  "drop_table_stmt", "drop_index_stmt", "quit_stmt", "execfile_stmt", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  sqlparser::yyrline_[] =
  {
       0,   120,   120,   121,   122,   123,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   184,   187,   193,   194,   224,   225,   226,
     227,   230,   231,   232,   260,   263,   266,   269,   273,   279,
     280,   281,   282,   283,   284,   285,   286,   301,   306,   309,
     310,   311,   312,   314,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   327,   328,   330,   331,   332,   333,   334,
     336,   338,   340,   342,   344,   346,   348,   350
  };

  // Print the state stack on the debug stream.
  void
  sqlparser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  sqlparser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 1812 "sqlparser.cpp" // lalr1.cc:1167
#line 351 "sqlparser.yy" // lalr1.cc:1168

void emit(char *s,...){
	extern int yylineno;
	va_list ap;
	va_start(ap,s);
	printf("rpn: ");
	vfprintf(stdout,s,ap);
	printf("\n");
}
/*
void error(char *s,...){
	extern int  yylineno;
	va_list ap;
	va_start(ap,s);
	fprintf(stderr,"%d:error: ",yylineno);
	vfprintf(stderr,s,ap);
	fprintf(stderr,"\n");
}
int main(int argc,char **argv){
	extern FILE *yyin;
	if(argc>1&&!strcmp(argv[1],"-d")){
		yydebug = 1;
		argc--;
		argv++;
	}
	if(argc>1&&((yyin = fopen(argv[1],"r")) == NULL)){
		perror(argv[1]);
		exit(1);
	}
	if(!yyparse()){
		printf("SQL parse worked\n");
	}
	else printf("SQL parse failed\n");
	return 0;
}*/
void yy::sqlparser::error(const location_type& l,const std::string &m){
	driver.error(l,m);
}
std::string itostr(int value){
	std::stringstream sstr;
	sstr << value;
	return sstr.str();   
}

std::string ftostr(float value){
	std::stringstream sstr;
	sstr << value;
	return sstr.str();   
}
