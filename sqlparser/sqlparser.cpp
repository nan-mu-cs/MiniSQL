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
      case 66: // numexp
        value.move< float > (that.value);
        break;

      case 5: // INTNUM
      case 22: // DEFAULT
      case 23: // AUTO_INCREMENT
      case 29: // NULLX
      case 35: // UNIQUE
      case 37: // PRIMARY
      case 60: // COMPARISON
      case 65: // expr
      case 71: // select_expr_list
      case 72: // table_references
      case 83: // opt_length
      case 84: // data_type
        value.move< int > (that.value);
        break;

      case 80: // create_col_list
        value.move< sqlstruct::create_col_list > (that.value);
        break;

      case 79: // create_table_stmt
        value.move< sqlstruct::createtable > (that.value);
        break;

      case 87: // drop_index_stmt
        value.move< sqlstruct::dropindex > (that.value);
        break;

      case 76: // insert_stmt
        value.move< sqlstruct::insertvalues > (that.value);
        break;

      case 81: // create_definition
        value.move< sqlstruct::record_t > (that.value);
        break;

      case 3: // NAME
      case 4: // STRING
      case 86: // drop_table_stmt
      case 89: // execfile_stmt
        value.move< std::string > (that.value);
        break;

      case 82: // column_atts
        value.move< std::vector<sqlstruct::col_attr> > (that.value);
        break;

      case 78: // insert_vals
        value.move< std::vector<sqlstruct::insertitem> > (that.value);
        break;

      case 70: // column_list
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
      case 66: // numexp
        value.copy< float > (that.value);
        break;

      case 5: // INTNUM
      case 22: // DEFAULT
      case 23: // AUTO_INCREMENT
      case 29: // NULLX
      case 35: // UNIQUE
      case 37: // PRIMARY
      case 60: // COMPARISON
      case 65: // expr
      case 71: // select_expr_list
      case 72: // table_references
      case 83: // opt_length
      case 84: // data_type
        value.copy< int > (that.value);
        break;

      case 80: // create_col_list
        value.copy< sqlstruct::create_col_list > (that.value);
        break;

      case 79: // create_table_stmt
        value.copy< sqlstruct::createtable > (that.value);
        break;

      case 87: // drop_index_stmt
        value.copy< sqlstruct::dropindex > (that.value);
        break;

      case 76: // insert_stmt
        value.copy< sqlstruct::insertvalues > (that.value);
        break;

      case 81: // create_definition
        value.copy< sqlstruct::record_t > (that.value);
        break;

      case 3: // NAME
      case 4: // STRING
      case 86: // drop_table_stmt
      case 89: // execfile_stmt
        value.copy< std::string > (that.value);
        break;

      case 82: // column_atts
        value.copy< std::vector<sqlstruct::col_attr> > (that.value);
        break;

      case 78: // insert_vals
        value.copy< std::vector<sqlstruct::insertitem> > (that.value);
        break;

      case 70: // column_list
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

#line 534 "sqlparser.cpp" // lalr1.cc:745

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
      case 66: // numexp
        yylhs.value.build< float > ();
        break;

      case 5: // INTNUM
      case 22: // DEFAULT
      case 23: // AUTO_INCREMENT
      case 29: // NULLX
      case 35: // UNIQUE
      case 37: // PRIMARY
      case 60: // COMPARISON
      case 65: // expr
      case 71: // select_expr_list
      case 72: // table_references
      case 83: // opt_length
      case 84: // data_type
        yylhs.value.build< int > ();
        break;

      case 80: // create_col_list
        yylhs.value.build< sqlstruct::create_col_list > ();
        break;

      case 79: // create_table_stmt
        yylhs.value.build< sqlstruct::createtable > ();
        break;

      case 87: // drop_index_stmt
        yylhs.value.build< sqlstruct::dropindex > ();
        break;

      case 76: // insert_stmt
        yylhs.value.build< sqlstruct::insertvalues > ();
        break;

      case 81: // create_definition
        yylhs.value.build< sqlstruct::record_t > ();
        break;

      case 3: // NAME
      case 4: // STRING
      case 86: // drop_table_stmt
      case 89: // execfile_stmt
        yylhs.value.build< std::string > ();
        break;

      case 82: // column_atts
        yylhs.value.build< std::vector<sqlstruct::col_attr> > ();
        break;

      case 78: // insert_vals
        yylhs.value.build< std::vector<sqlstruct::insertitem> > ();
        break;

      case 70: // column_list
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
#line 121 "sqlparser.yy" // lalr1.cc:859
    {emit("NAME %s",(yystack_[0].value.as< std::string > ()).c_str()); }
#line 703 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 122 "sqlparser.yy" // lalr1.cc:859
    {emit("STRING %s",(yystack_[0].value.as< std::string > ()).c_str()); }
#line 709 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 123 "sqlparser.yy" // lalr1.cc:859
    {}
#line 715 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 124 "sqlparser.yy" // lalr1.cc:859
    {emit("AND");}
#line 721 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 125 "sqlparser.yy" // lalr1.cc:859
    {emit("OR");}
#line 727 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 126 "sqlparser.yy" // lalr1.cc:859
    {emit("XOR");}
#line 733 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 127 "sqlparser.yy" // lalr1.cc:859
    {emit("BITAND");}
#line 739 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 128 "sqlparser.yy" // lalr1.cc:859
    {emit("NOT");}
#line 745 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 129 "sqlparser.yy" // lalr1.cc:859
    {emit("NOT");}
#line 751 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 130 "sqlparser.yy" // lalr1.cc:859
    {emit("CMP %d",yystack_[1].value.as< int > ());}
#line 757 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 131 "sqlparser.yy" // lalr1.cc:859
    {emit("ISNULL");}
#line 763 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 132 "sqlparser.yy" // lalr1.cc:859
    {emit("ISNULL"); emit("NOT");}
#line 769 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 133 "sqlparser.yy" // lalr1.cc:859
    {emit("BETWEEN");}
#line 775 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 141 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[0].value.as< int > ();}
#line 781 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 142 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[0].value.as< float > ();}
#line 787 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 143 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< float > () + yystack_[0].value.as< float > ();}
#line 793 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 144 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< float > () + yystack_[0].value.as< float > ();}
#line 799 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 145 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< float > () * yystack_[0].value.as< float > ();}
#line 805 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 146 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = yystack_[2].value.as< float > () / yystack_[0].value.as< float > ();}
#line 811 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 147 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< float > () = -yystack_[0].value.as< float > ();}
#line 817 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 173 "sqlparser.yy" // lalr1.cc:859
    {emit("STMT");}
#line 823 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 176 "sqlparser.yy" // lalr1.cc:859
    {emit("SELECT %d %d %d",yystack_[3].value.as< int > (),yystack_[1].value.as< int > ());}
#line 829 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 180 "sqlparser.yy" // lalr1.cc:859
    {emit("WHERE");}
#line 835 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 210 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< std::vector<std::string> > ()).clear(); (yylhs.value.as< std::vector<std::string> > ()).push_back(yystack_[0].value.as< std::string > ());}
#line 841 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 211 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< std::vector<std::string> > ()).clear(); (yylhs.value.as< std::vector<std::string> > ()).push_back(yystack_[0].value.as< std::string > ());}
#line 847 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 212 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< std::vector<std::string> > () = yystack_[2].value.as< std::vector<std::string> > ();(yystack_[2].value.as< std::vector<std::string> > ()).push_back(yystack_[0].value.as< std::string > ());}
#line 853 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 213 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< std::vector<std::string> > () = yystack_[2].value.as< std::vector<std::string> > ();(yystack_[2].value.as< std::vector<std::string> > ()).push_back(yystack_[0].value.as< std::string > ());}
#line 859 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 216 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1;}
#line 865 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 217 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1;}
#line 871 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 218 "sqlparser.yy" // lalr1.cc:859
    {emit("SELECTALL"); yylhs.value.as< int > () = 1;}
#line 877 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 227 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1;}
#line 883 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 228 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1;}
#line 889 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 235 "sqlparser.yy" // lalr1.cc:859
    {emit("TALBLE %s",(yystack_[0].value.as< std::string > ()).c_str());}
#line 895 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 236 "sqlparser.yy" // lalr1.cc:859
    {emit("TABLE %s.%s",(yystack_[2].value.as< std::string > ()).c_str(),(yystack_[0].value.as< std::string > ()).c_str());}
#line 901 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 237 "sqlparser.yy" // lalr1.cc:859
    {emit("TABLEREFERENCES %d",yystack_[1].value.as< int > ());}
#line 907 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 244 "sqlparser.yy" // lalr1.cc:859
    {emit("STMT");}
#line 913 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 247 "sqlparser.yy" // lalr1.cc:859
    {emit("DELETE %s",(yystack_[1].value.as< std::string > ()).c_str()); }
#line 919 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 250 "sqlparser.yy" // lalr1.cc:859
    {driver.InsertValues(yystack_[0].value.as< sqlstruct::insertvalues > ());}
#line 925 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 254 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< sqlstruct::insertvalues > ()).tablename = yystack_[4].value.as< std::string > ();(yylhs.value.as< sqlstruct::insertvalues > ()).item = yystack_[1].value.as< std::vector<sqlstruct::insertitem> > ();}
#line 931 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 264 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).clear(); sqlstruct::insertitem item;item.data_type = sqlstruct::STRING;item.value = yystack_[0].value.as< std::string > ();(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).push_back(item); }
#line 937 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 265 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).clear();sqlstruct::insertitem item;item.data_type = sqlstruct::INTNUM;item.value = itostr(yystack_[0].value.as< int > ());(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).push_back(item);}
#line 943 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 266 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).clear();sqlstruct::insertitem item;item.data_type = sqlstruct::FLOATNUM;item.value = ftostr(yystack_[0].value.as< float > ());(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).push_back(item);}
#line 949 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 267 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::insertitem item;item.data_type = sqlstruct::DEFAULT;(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).push_back(item);}
#line 955 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 268 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::insertitem item;item.data_type = sqlstruct::STRING;item.value = yystack_[0].value.as< std::string > ();yylhs.value.as< std::vector<sqlstruct::insertitem> > () = yystack_[2].value.as< std::vector<sqlstruct::insertitem> > ();(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).push_back(item);}
#line 961 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 269 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::insertitem item;item.data_type = sqlstruct::INTNUM;item.value = itostr(yystack_[0].value.as< int > ());yylhs.value.as< std::vector<sqlstruct::insertitem> > () = yystack_[2].value.as< std::vector<sqlstruct::insertitem> > ();(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).push_back(item);}
#line 967 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 270 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::insertitem item;item.data_type = sqlstruct::FLOATNUM;item.value = ftostr(yystack_[0].value.as< float > ());yylhs.value.as< std::vector<sqlstruct::insertitem> > () = yystack_[2].value.as< std::vector<sqlstruct::insertitem> > ();(yylhs.value.as< std::vector<sqlstruct::insertitem> > ()).push_back(item);}
#line 973 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 271 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::insertitem item;item.data_type = sqlstruct::DEFAULT;}
#line 979 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 286 "sqlparser.yy" // lalr1.cc:859
    {
    		//emit("STMT");
		driver.Createtable(yystack_[0].value.as< sqlstruct::createtable > ());
	}
#line 988 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 291 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< sqlstruct::createtable > ()).name = yystack_[3].value.as< std::string > ();(yylhs.value.as< sqlstruct::createtable > ()).col = yystack_[1].value.as< sqlstruct::create_col_list > (); }
#line 994 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 294 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< sqlstruct::create_col_list > ()).record.clear();(yylhs.value.as< sqlstruct::create_col_list > ()).record.push_back(yystack_[0].value.as< sqlstruct::record_t > ());}
#line 1000 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 295 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::create_col_list > () = yystack_[2].value.as< sqlstruct::create_col_list > ();(yylhs.value.as< sqlstruct::create_col_list > ()).record.push_back(yystack_[0].value.as< sqlstruct::record_t > ());}
#line 1006 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 296 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::create_col_list > () = yystack_[6].value.as< sqlstruct::create_col_list > ();(yylhs.value.as< sqlstruct::create_col_list > ()).primarykey = yystack_[1].value.as< std::vector<std::string> > ();}
#line 1012 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 297 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< sqlstruct::create_col_list > () = yystack_[5].value.as< sqlstruct::create_col_list > ();(yylhs.value.as< sqlstruct::create_col_list > ()).indexkey = yystack_[1].value.as< std::vector<std::string> > ();}
#line 1018 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 299 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< sqlstruct::record_t > ()).name = yystack_[2].value.as< std::string > ();(yylhs.value.as< sqlstruct::record_t > ()).data_type = yystack_[1].value.as< int > ();(yylhs.value.as< sqlstruct::record_t > ()).attr = yystack_[0].value.as< std::vector<sqlstruct::col_attr> > (); }
#line 1024 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 301 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).clear();}
#line 1030 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 302 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr; attr.type = yystack_[0].value.as< int > () + 1000;yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[2].value.as< std::vector<sqlstruct::col_attr> > ();(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1036 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 303 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr; attr.type = yystack_[0].value.as< int > ();yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[1].value.as< std::vector<sqlstruct::col_attr> > ();(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1042 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 304 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr;attr.type = yystack_[1].value.as< int > (); attr.value = yystack_[0].value.as< std::string > (); yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[2].value.as< std::vector<sqlstruct::col_attr> > ();(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1048 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 305 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr;attr.type = yystack_[1].value.as< int > ();attr.value = itostr(yystack_[0].value.as< int > ());yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[2].value.as< std::vector<sqlstruct::col_attr> > ();(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1054 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 306 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr;attr.type = yystack_[1].value.as< int > (); attr.value = ftostr(yystack_[0].value.as< float > ());yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[2].value.as< std::vector<sqlstruct::col_attr> > ();(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1060 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 307 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr; attr.type = yystack_[0].value.as< int > ();yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[1].value.as< std::vector<sqlstruct::col_attr> > ();(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1066 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 308 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr;attr.type = yystack_[0].value.as< int > ();yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[1].value.as< std::vector<sqlstruct::col_attr> > ();(yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1072 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 309 "sqlparser.yy" // lalr1.cc:859
    {sqlstruct::col_attr attr;attr.type = yystack_[1].value.as< int > ();yylhs.value.as< std::vector<sqlstruct::col_attr> > () = yystack_[2].value.as< std::vector<sqlstruct::col_attr> > (); (yylhs.value.as< std::vector<sqlstruct::col_attr> > ()).push_back(attr);}
#line 1078 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 312 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 0;}
#line 1084 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 313 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[1].value.as< int > ();}
#line 1090 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 315 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 40000;}
#line 1096 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 316 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 120000 + yystack_[0].value.as< int > ();}
#line 1102 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 317 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 90000;}
#line 1108 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 318 "sqlparser.yy" // lalr1.cc:859
    {emit("STMT");}
#line 1114 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 319 "sqlparser.yy" // lalr1.cc:859
    {emit("INDEX %s %s",(yystack_[5].value.as< std::string > ()).c_str(),(yystack_[3].value.as< std::string > ()).c_str()); }
#line 1120 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 321 "sqlparser.yy" // lalr1.cc:859
    {driver.DropTable(yystack_[0].value.as< std::string > ());}
#line 1126 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 323 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1132 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 325 "sqlparser.yy" // lalr1.cc:859
    {driver.DropIndex(yystack_[0].value.as< sqlstruct::dropindex > ());}
#line 1138 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 327 "sqlparser.yy" // lalr1.cc:859
    {(yylhs.value.as< sqlstruct::dropindex > ()).indexname = yystack_[5].value.as< std::string > ();(yylhs.value.as< sqlstruct::dropindex > ()).tablename = yystack_[3].value.as< std::string > ();(yylhs.value.as< sqlstruct::dropindex > ()).col = yystack_[1].value.as< std::vector<std::string> > (); }
#line 1144 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 329 "sqlparser.yy" // lalr1.cc:859
    {emit("STMT");}
#line 1150 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 331 "sqlparser.yy" // lalr1.cc:859
    {exit(0);}
#line 1156 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 333 "sqlparser.yy" // lalr1.cc:859
    {driver.ExecFile(yystack_[0].value.as< std::string > ());}
#line 1162 "sqlparser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 335 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1168 "sqlparser.cpp" // lalr1.cc:859
    break;


#line 1172 "sqlparser.cpp" // lalr1.cc:859
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


  const signed char sqlparser::yypact_ninf_ = -90;

  const signed char sqlparser::yytable_ninf_ = -1;

  const short int
  sqlparser::yypact_[] =
  {
      58,   -12,    63,    -9,   -90,    50,    61,     5,    43,    14,
      39,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,    96,    98,   111,   -90,   115,   125,   -90,   -90,    11,
     -90,   137,   -90,    47,   106,   -90,    69,   136,   -90,   138,
     113,     6,   154,   126,   -90,   -90,     1,   -90,   156,   157,
     158,   114,     6,    23,   -90,   -90,   -90,   119,   -90,   -90,
     -90,   -90,    28,     1,     1,    45,    92,   121,   122,    99,
     -32,   -90,   163,    62,     6,   -90,    20,   -90,    45,    29,
       1,     1,     1,     1,   -18,     1,     1,    28,    28,    28,
      28,   117,   117,   124,   -90,   -90,   -90,   -90,    18,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,    94,   -90,    56,    64,
      67,   -90,   139,    -8,   123,   100,   100,   -90,   -90,   -90,
     -90,   101,   103,   165,   -90,    55,   128,   160,   -90,   -90,
      60,   -90,     1,   -90,   140,   -90,   129,   131,   -90,   -90,
     -90,   162,   146,   117,   133,   -90,   -90,   -90,   -90,    33,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   105,   117,
     -90,   107,   -90
  };

  const unsigned char
  sqlparser::yydefact_[] =
  {
       0,     0,     0,     0,    85,     0,     0,     0,    48,     0,
       0,    26,    43,    45,    57,    78,    80,    82,    84,    86,
       4,     0,     0,     0,    87,     0,     0,    34,    36,     0,
      47,     0,     1,     0,     0,     2,    28,     0,    81,     0,
       0,     0,     0,     0,     5,     3,     0,    44,     0,     0,
       0,    40,     0,    28,    37,    39,    35,     0,     6,     7,
      19,    20,     0,     0,     0,    29,     8,     0,     0,     0,
       0,    59,     0,     0,     0,    27,     0,    25,    14,    13,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,    75,    77,    64,    58,     0,    41,
      42,    38,    49,    50,    51,    52,     0,    12,    10,    11,
       9,    16,     0,     0,    15,    22,    21,    23,    24,    30,
      31,     0,     0,     0,    76,    63,     0,     0,    60,    46,
       0,    17,     0,    83,     0,    79,     0,     0,    70,    66,
      71,     0,     0,     0,     0,    53,    54,    55,    56,    18,
      32,    33,    74,    67,    68,    69,    72,    65,     0,     0,
      62,     0,    61
  };

  const short int
  sqlparser::yypgoto_[] =
  {
     -90,   -90,   -63,   -27,   168,   -90,   127,   -89,   -90,   130,
     104,   -90,   -90,   -90,   -90,   -90,   -90,   -90,    81,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90
  };

  const signed char
  sqlparser::yydefgoto_[] =
  {
      -1,     9,    65,    66,    10,    11,    47,   121,    29,    53,
      54,    55,    12,    13,    31,   106,    14,    70,    71,   125,
     124,    96,    15,    16,    17,    18,    19
  };

  const unsigned char
  sqlparser::yytable_[] =
  {
      78,    79,   132,   122,    58,    59,    60,    61,    27,    51,
      22,   111,    97,    98,    32,    33,    23,   107,   108,   109,
     110,    69,   113,   114,   102,   103,   104,     2,     3,     4,
       5,    41,     6,    60,    61,    77,    20,   126,    80,   112,
      62,     7,   105,    81,    82,    83,    28,    84,    63,    52,
       8,    85,    86,    24,   158,   127,    42,    46,    64,     1,
     115,   116,   117,   118,   145,   146,   147,    62,    74,   149,
     161,     2,     3,     4,     5,    80,     6,   137,   138,    80,
      25,    30,   148,    21,   139,     7,    26,    35,    85,    86,
     140,    80,   141,    86,     8,    44,    81,    82,    83,    36,
      84,    37,    80,    46,    85,    86,   100,    74,    82,    83,
      80,    84,   142,    80,    38,    85,    86,    83,    39,    84,
     119,   120,    84,    85,    86,    93,    85,    86,    40,    94,
      95,    87,    88,    89,    90,   153,   154,   155,   129,   130,
      43,    89,    90,   150,   151,   133,   134,   135,   134,   160,
     134,   162,   134,    48,    45,    49,    50,    56,    57,    67,
      68,    69,    76,    72,    91,    92,    99,   123,   131,    80,
     136,   143,   144,   152,   156,   157,   159,    34,   101,   128,
      75,     0,    73
  };

  const short int
  sqlparser::yycheck_[] =
  {
      63,    64,    10,    92,     3,     4,     5,     6,     3,     3,
      19,    29,    44,    45,     0,     1,    25,    80,    81,    82,
      83,     3,    85,    86,     4,     5,     6,    13,    14,    15,
      16,    20,    18,     5,     6,    62,    48,    19,    46,    57,
      39,    27,    22,    51,    52,    53,    41,    55,    47,    43,
      36,    59,    60,     3,   143,    37,    45,    34,    57,     1,
      87,    88,    89,    90,     4,     5,     6,    39,    45,   132,
     159,    13,    14,    15,    16,    46,    18,    22,    23,    46,
      19,    38,    22,    20,    29,    27,    25,    48,    59,    60,
      35,    46,    37,    60,    36,    48,    51,    52,    53,     3,
      55,     3,    46,    34,    59,    60,    44,    45,    52,    53,
      46,    55,    57,    46,     3,    59,    60,    53,     3,    55,
       3,     4,    55,    59,    60,    26,    59,    60,     3,    30,
      31,    39,    40,    41,    42,     4,     5,     6,    44,    45,
       3,    41,    42,     3,     4,    44,    45,    44,    45,    44,
      45,    44,    45,    17,    48,    17,    43,     3,    32,     3,
       3,     3,    43,    49,    43,    43,     3,    43,    29,    46,
       5,    43,    12,    44,    12,    29,    43,     9,    74,    98,
      53,    -1,    52
  };

  const unsigned char
  sqlparser::yystos_[] =
  {
       0,     1,    13,    14,    15,    16,    18,    27,    36,    64,
      67,    68,    75,    76,    79,    85,    86,    87,    88,    89,
      48,    20,    19,    25,     3,    19,    25,     3,    41,    71,
      38,    77,     0,     1,    67,    48,     3,     3,     3,     3,
       3,    20,    45,     3,    48,    48,    34,    69,    17,    17,
      43,     3,    43,    72,    73,    74,     3,    32,     3,     4,
       5,     6,    39,    47,    57,    65,    66,     3,     3,     3,
      80,    81,    49,    72,    45,    69,    43,    66,    65,    65,
      46,    51,    52,    53,    55,    59,    60,    39,    40,    41,
      42,    43,    43,    26,    30,    31,    84,    44,    45,     3,
      44,    73,     4,     5,     6,    22,    78,    65,    65,    65,
      65,    29,    57,    65,    65,    66,    66,    66,    66,     3,
       4,    70,    70,    43,    83,    82,    19,    37,    81,    44,
      45,    29,    10,    44,    45,    44,     5,    22,    23,    29,
      35,    37,    57,    43,    12,     4,     5,     6,    22,    65,
       3,     4,    44,     4,     5,     6,    12,    29,    70,    43,
      44,    70,    44
  };

  const unsigned char
  sqlparser::yyr1_[] =
  {
       0,    63,    64,    64,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    66,
      66,    66,    66,    66,    66,    66,    67,    68,    69,    69,
      70,    70,    70,    70,    71,    71,    71,    72,    72,    73,
      74,    74,    74,    67,    75,    67,    76,    77,    77,    78,
      78,    78,    78,    78,    78,    78,    78,    67,    79,    80,
      80,    80,    80,    81,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    83,    83,    84,    84,    84,    67,    85,
      67,    86,    67,    87,    67,    88,    67,    89
  };

  const unsigned char
  sqlparser::yyr2_[] =
  {
       0,     2,     2,     3,     2,     3,     1,     1,     1,     3,
       3,     3,     3,     2,     2,     3,     3,     4,     5,     1,
       1,     3,     3,     3,     3,     2,     1,     5,     0,     2,
       1,     1,     3,     3,     1,     3,     1,     1,     3,     1,
       1,     3,     3,     1,     4,     1,     7,     1,     0,     1,
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
  "\"|\"", "UMINUS", "$accept", "stmt_list", "expr", "numexp", "stmt",
  "select_stmt", "opt_where", "column_list", "select_expr_list",
  "table_references", "table_reference", "table_factor", "delete_stmt",
  "insert_stmt", "opt_into", "insert_vals", "create_table_stmt",
  "create_col_list", "create_definition", "column_atts", "opt_length",
  "data_type", "create_index_stmt", "drop_table_stmt", "drop_index_stmt",
  "quit_stmt", "execfile_stmt", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  sqlparser::yyrline_[] =
  {
       0,   116,   116,   117,   118,   119,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   141,
     142,   143,   144,   145,   146,   147,   173,   176,   179,   180,
     210,   211,   212,   213,   216,   217,   218,   227,   228,   231,
     235,   236,   237,   244,   247,   250,   253,   257,   258,   264,
     265,   266,   267,   268,   269,   270,   271,   286,   291,   294,
     295,   296,   297,   299,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   312,   313,   315,   316,   317,   318,   319,
     321,   323,   325,   327,   329,   331,   333,   335
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
#line 1660 "sqlparser.cpp" // lalr1.cc:1167
#line 336 "sqlparser.yy" // lalr1.cc:1168

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
