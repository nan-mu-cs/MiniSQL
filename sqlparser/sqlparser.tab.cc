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

#line 37 "sqlparser.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "sqlparser.tab.hh"

// User implementation prologue.

#line 51 "sqlparser.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 19 "sqlparser.yy" // lalr1.cc:413

#include "sqlparser_driver.hh"

#line 57 "sqlparser.tab.cc" // lalr1.cc:413


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
#line 143 "sqlparser.tab.cc" // lalr1.cc:479

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
  sqlparser::sqlparser (sqlparser_driver &driver;_yyarg)
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
        value.move< float > (that.value);
        break;

      case 5: // INTNUM
      case 64: // expr
      case 65: // val_list
      case 69: // column_list
      case 70: // select_opts
      case 71: // select_expr_list
      case 74: // table_references
      case 78: // insert_stmt
      case 80: // insert_val_list
      case 81: // insert_vals
      case 82: // update_stmt
      case 83: // update_asgn_list
      case 85: // create_col_list
      case 88: // column_atts
      case 89: // opt_length
      case 90: // data_type
        value.move< int > (that.value);
        break;

      case 3: // NAME
      case 4: // STRING
        value.move< std::string > (that.value);
        break;

      case 49: // COMPARISON
        value.move< subtok > (that.value);
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
        value.copy< float > (that.value);
        break;

      case 5: // INTNUM
      case 64: // expr
      case 65: // val_list
      case 69: // column_list
      case 70: // select_opts
      case 71: // select_expr_list
      case 74: // table_references
      case 78: // insert_stmt
      case 80: // insert_val_list
      case 81: // insert_vals
      case 82: // update_stmt
      case 83: // update_asgn_list
      case 85: // create_col_list
      case 88: // column_atts
      case 89: // opt_length
      case 90: // data_type
        value.copy< int > (that.value);
        break;

      case 3: // NAME
      case 4: // STRING
        value.copy< std::string > (that.value);
        break;

      case 49: // COMPARISON
        value.copy< subtok > (that.value);
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
    #line 14 "sqlparser.yy" // lalr1.cc:745
{
	yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 480 "sqlparser.tab.cc" // lalr1.cc:745

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
        yylhs.value.build< float > ();
        break;

      case 5: // INTNUM
      case 64: // expr
      case 65: // val_list
      case 69: // column_list
      case 70: // select_opts
      case 71: // select_expr_list
      case 74: // table_references
      case 78: // insert_stmt
      case 80: // insert_val_list
      case 81: // insert_vals
      case 82: // update_stmt
      case 83: // update_asgn_list
      case 85: // create_col_list
      case 88: // column_atts
      case 89: // opt_length
      case 90: // data_type
        yylhs.value.build< int > ();
        break;

      case 3: // NAME
      case 4: // STRING
        yylhs.value.build< std::string > ();
        break;

      case 49: // COMPARISON
        yylhs.value.build< subtok > ();
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
#line 92 "sqlparser.yy" // lalr1.cc:859
    {emit("NAME %s",yystack_[0].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ());}
#line 622 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 93 "sqlparser.yy" // lalr1.cc:859
    {emit("FILEDNAME %s.%s",yystack_[2].value.as< std::string > (),yystack_[0].value.as< std::string > ()); free(yystack_[2].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ()); }
#line 628 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 94 "sqlparser.yy" // lalr1.cc:859
    {emit("STRING %s",yystack_[0].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ());}
#line 634 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 95 "sqlparser.yy" // lalr1.cc:859
    {emit("NUMBER %d",yystack_[0].value.as< int > ());}
#line 640 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 10:
#line 96 "sqlparser.yy" // lalr1.cc:859
    {emit("FLOAT %g",yystack_[0].value.as< float > ());}
#line 646 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 97 "sqlparser.yy" // lalr1.cc:859
    {emit("ADD");}
#line 652 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 98 "sqlparser.yy" // lalr1.cc:859
    {emit("SUB");}
#line 658 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 99 "sqlparser.yy" // lalr1.cc:859
    {emit("MUL");}
#line 664 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 100 "sqlparser.yy" // lalr1.cc:859
    {emit("DIV");}
#line 670 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 101 "sqlparser.yy" // lalr1.cc:859
    {emit("NEG");}
#line 676 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 102 "sqlparser.yy" // lalr1.cc:859
    {emit("AND");}
#line 682 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 103 "sqlparser.yy" // lalr1.cc:859
    {emit("OR");}
#line 688 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 104 "sqlparser.yy" // lalr1.cc:859
    {emit("XOR");}
#line 694 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 105 "sqlparser.yy" // lalr1.cc:859
    {emit("BITAND");}
#line 700 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 106 "sqlparser.yy" // lalr1.cc:859
    {emit("NOT");}
#line 706 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 107 "sqlparser.yy" // lalr1.cc:859
    {emit("NOT");}
#line 712 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 108 "sqlparser.yy" // lalr1.cc:859
    {emit("CMP %d",yystack_[1].value.as< subtok > ());}
#line 718 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 109 "sqlparser.yy" // lalr1.cc:859
    {emit("ISNULL");}
#line 724 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 110 "sqlparser.yy" // lalr1.cc:859
    {emit("ISNULL"); emit("NOT");}
#line 730 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 111 "sqlparser.yy" // lalr1.cc:859
    {emit("BETWEEN");}
#line 736 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 113 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1;}
#line 742 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 114 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[0].value.as< int > () + 1;}
#line 748 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 121 "sqlparser.yy" // lalr1.cc:859
    {emit("ISIN %d",yystack_[1].value.as< int > ());}
#line 754 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 122 "sqlparser.yy" // lalr1.cc:859
    {emit("ISIN %d",yystack_[1].value.as< int > ()); emit("NOT");}
#line 760 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 123 "sqlparser.yy" // lalr1.cc:859
    {emit("CMPANYSELECT 4");}
#line 766 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 124 "sqlparser.yy" // lalr1.cc:859
    {emit("COMPANYSELECT 3");}
#line 772 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 127 "sqlparser.yy" // lalr1.cc:859
    {emit("LIKE");}
#line 778 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 33:
#line 128 "sqlparser.yy" // lalr1.cc:859
    {emit("LIKE"); emit("NOT");}
#line 784 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 34:
#line 131 "sqlparser.yy" // lalr1.cc:859
    {emit("STMT");}
#line 790 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 35:
#line 134 "sqlparser.yy" // lalr1.cc:859
    {emit("SELECTNODATA %d %d",yystack_[1].value.as< int > (),yystack_[0].value.as< int > ());}
#line 796 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 36:
#line 137 "sqlparser.yy" // lalr1.cc:859
    {emit("SELECT %d %d %d",yystack_[4].value.as< int > (),yystack_[3].value.as< int > (),yystack_[1].value.as< int > ());}
#line 802 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 38:
#line 141 "sqlparser.yy" // lalr1.cc:859
    {emit("WHERE");}
#line 808 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 39:
#line 170 "sqlparser.yy" // lalr1.cc:859
    {emit("COLUMN %s",yystack_[0].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ()); yylhs.value.as< int > () = 1;}
#line 814 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 40:
#line 171 "sqlparser.yy" // lalr1.cc:859
    {emit("COLUMN %s",yystack_[0].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ()); yylhs.value.as< int > () = 1;}
#line 820 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 172 "sqlparser.yy" // lalr1.cc:859
    {emit("COLUMN %s",yystack_[0].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ()); yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1;}
#line 826 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 42:
#line 173 "sqlparser.yy" // lalr1.cc:859
    {emit("COLUMN %s",yystack_[0].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ()); yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1;}
#line 832 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 43:
#line 175 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 0;}
#line 838 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 176 "sqlparser.yy" // lalr1.cc:859
    {if(yystack_[1].value.as< int > () & 01) yyerror("duplicate ALL option"); yylhs.value.as< int > () = yystack_[1].value.as< int > () | 01;}
#line 844 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 45:
#line 177 "sqlparser.yy" // lalr1.cc:859
    {if(yystack_[1].value.as< int > () & 02) yyerror("duplicate DISTINCT option"); yylhs.value.as< int > () = yystack_[1].value.as< int > () | 02;}
#line 850 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 46:
#line 180 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1;}
#line 856 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 47:
#line 181 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1;}
#line 862 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 182 "sqlparser.yy" // lalr1.cc:859
    {emit("SELECTALL"); yylhs.value.as< int > () = 1;}
#line 868 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 187 "sqlparser.yy" // lalr1.cc:859
    {emit("ALIAS %s",yystack_[0].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ());}
#line 874 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 188 "sqlparser.yy" // lalr1.cc:859
    {emit("ALIAS %s",yystack_[0].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ());}
#line 880 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 192 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1;}
#line 886 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 193 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1;}
#line 892 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 200 "sqlparser.yy" // lalr1.cc:859
    {emit("TALBLE %s",yystack_[0].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ());}
#line 898 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 201 "sqlparser.yy" // lalr1.cc:859
    {emit("TABLE %s.%s",yystack_[2].value.as< std::string > (),yystack_[0].value.as< std::string > ()); free(yystack_[2].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ());}
#line 904 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 58:
#line 202 "sqlparser.yy" // lalr1.cc:859
    {emit("TABLEREFERENCES %d",yystack_[1].value.as< int > ());}
#line 910 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 209 "sqlparser.yy" // lalr1.cc:859
    {emit("STMT");}
#line 916 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 60:
#line 212 "sqlparser.yy" // lalr1.cc:859
    {emit("DELETEONE %s",yystack_[1].value.as< std::string > ()); free(yystack_[1].value.as< std::string > ());}
#line 922 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 215 "sqlparser.yy" // lalr1.cc:859
    {emit("STMT");}
#line 928 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 62:
#line 219 "sqlparser.yy" // lalr1.cc:859
    {emit("INSERTVALS  %d %s",yystack_[0].value.as< int > (),yystack_[2].value.as< std::string > ()); free(yystack_[2].value.as< std::string > ());}
#line 934 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 226 "sqlparser.yy" // lalr1.cc:859
    {emit("VALUES %d",yystack_[1].value.as< int > ()); yylhs.value.as< int > () = 1;}
#line 940 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 66:
#line 227 "sqlparser.yy" // lalr1.cc:859
    {emit("VALUES %d",yystack_[1].value.as< int > ()); yylhs.value.as< int > () = yystack_[4].value.as< int > () + 1;}
#line 946 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 228 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1;}
#line 952 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 229 "sqlparser.yy" // lalr1.cc:859
    {emit("DEFAULT"); yylhs.value.as< int > () = 1;}
#line 958 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 69:
#line 230 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1;}
#line 964 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 231 "sqlparser.yy" // lalr1.cc:859
    {emit("DEFAULT"); yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1;}
#line 970 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 233 "sqlparser.yy" // lalr1.cc:859
    {emit("STMT");}
#line 976 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 236 "sqlparser.yy" // lalr1.cc:859
    {emit("UPDATE %d %d",yystack_[3].value.as< int > (),yystack_[1].value.as< int > ());}
#line 982 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 73:
#line 239 "sqlparser.yy" // lalr1.cc:859
    {if(yystack_[1].value.as< subtok > () != 4) {yyerror("Bad update assignment to %s",yystack_[2].value.as< std::string > ()); YYERROR;}
				      emit("ASSIGN %s",yystack_[2].value.as< std::string > ()); free(yystack_[2].value.as< std::string > ()); yylhs.value.as< int > () = 1;}
#line 989 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 241 "sqlparser.yy" // lalr1.cc:859
    {if(yystack_[1].value.as< subtok > () != 4) {yyerror("Bad update assignment to %s",yystack_[4].value.as< std::string > ()); 
			YYERROR;} emit("ASSIGN %s.%s",yystack_[4].value.as< std::string > (),yystack_[2].value.as< std::string > ()); free(yystack_[4].value.as< std::string > ()); free(yystack_[2].value.as< std::string > ()); yylhs.value.as< int > () = 1;}
#line 996 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 75:
#line 245 "sqlparser.yy" // lalr1.cc:859
    {
    		emit("STMT");
	}
#line 1004 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 249 "sqlparser.yy" // lalr1.cc:859
    {emit("CREATE %d %s",yystack_[1].value.as< int > (),yystack_[3].value.as< std::string > ()); free(yystack_[3].value.as< std::string > ());}
#line 1010 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 252 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1;}
#line 1016 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 253 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[2].value.as< int > ()+1;}
#line 1022 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 255 "sqlparser.yy" // lalr1.cc:859
    {emit("PRIKEY %d",yystack_[1].value.as< int > ());}
#line 1028 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 256 "sqlparser.yy" // lalr1.cc:859
    {emit("INDEX %d",yystack_[1].value.as< int > ());}
#line 1034 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 81:
#line 258 "sqlparser.yy" // lalr1.cc:859
    {emit("STARTCOL");}
#line 1040 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 258 "sqlparser.yy" // lalr1.cc:859
    {emit("COLUMNDEF %d %s",yystack_[1].value.as< int > (),yystack_[2].value.as< std::string > ()); free(yystack_[2].value.as< std::string > ());}
#line 1046 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 260 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 0;}
#line 1052 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 261 "sqlparser.yy" // lalr1.cc:859
    {emit("ATTR NOTNULL"); yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1;}
#line 1058 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 86:
#line 263 "sqlparser.yy" // lalr1.cc:859
    {emit("ATTR DEFAULT STRING %s",yystack_[0].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ()); yylhs.value.as< int > () = yystack_[2].value.as< int > ()+1;}
#line 1064 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 87:
#line 264 "sqlparser.yy" // lalr1.cc:859
    {emit("ATTR DEFAULT NUMBER %d",yystack_[0].value.as< int > ()); yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1;}
#line 1070 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 88:
#line 265 "sqlparser.yy" // lalr1.cc:859
    {emit("ATTR DEFAULT FLOAT %g",yystack_[0].value.as< float > ()); yylhs.value.as< int > () = yystack_[2].value.as< int > ()+1;}
#line 1076 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 89:
#line 266 "sqlparser.yy" // lalr1.cc:859
    {emit("ATTR AUTOINC"); yylhs.value.as< int > () = yystack_[1].value.as< int > () +1;}
#line 1082 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 267 "sqlparser.yy" // lalr1.cc:859
    {emit("ATTR UNIQUEKEY %d",yystack_[1].value.as< int > ()); yylhs.value.as< int > () = yystack_[4].value.as< int > () + 1;}
#line 1088 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 268 "sqlparser.yy" // lalr1.cc:859
    {emit("ATTR UNIQUEKEY"); yylhs.value.as< int > () = yystack_[2].value.as< int > ()+1;}
#line 1094 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 269 "sqlparser.yy" // lalr1.cc:859
    {emit("ATTR PRIKEY"); yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1;}
#line 1100 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 272 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 0;}
#line 1106 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 94:
#line 273 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[1].value.as< int > ();}
#line 1112 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 95:
#line 275 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 40000;}
#line 1118 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 96:
#line 276 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 120000 + yystack_[0].value.as< int > ();}
#line 1124 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 97:
#line 277 "sqlparser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 90000;}
#line 1130 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 98:
#line 278 "sqlparser.yy" // lalr1.cc:859
    {emit("STMT");}
#line 1136 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 99:
#line 279 "sqlparser.yy" // lalr1.cc:859
    {emit("INDEX %s %s",yystack_[5].value.as< std::string > (),yystack_[3].value.as< std::string > ()); free(yystack_[5].value.as< std::string > ()); free(yystack_[3].value.as< std::string > ());}
#line 1142 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 100:
#line 281 "sqlparser.yy" // lalr1.cc:859
    {emit("STMT");}
#line 1148 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 101:
#line 283 "sqlparser.yy" // lalr1.cc:859
    {emit("DROPTABLE %s",yystack_[0].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ());}
#line 1154 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 102:
#line 285 "sqlparser.yy" // lalr1.cc:859
    {emit("STMT");}
#line 1160 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 103:
#line 287 "sqlparser.yy" // lalr1.cc:859
    {emit("DROPINDEX %s",yystack_[0].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ());}
#line 1166 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 104:
#line 289 "sqlparser.yy" // lalr1.cc:859
    {emit("STMT");}
#line 1172 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 105:
#line 291 "sqlparser.yy" // lalr1.cc:859
    {exit(0);}
#line 1178 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 106:
#line 293 "sqlparser.yy" // lalr1.cc:859
    {emit("STMT");}
#line 1184 "sqlparser.tab.cc" // lalr1.cc:859
    break;

  case 107:
#line 295 "sqlparser.yy" // lalr1.cc:859
    {emit("EXECFILE %s",yystack_[0].value.as< std::string > ()); free(yystack_[0].value.as< std::string > ());}
#line 1190 "sqlparser.tab.cc" // lalr1.cc:859
    break;


#line 1194 "sqlparser.tab.cc" // lalr1.cc:859
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


  const short int sqlparser::yypact_ninf_ = -134;

  const signed char sqlparser::yytable_ninf_ = -1;

  const short int
  sqlparser::yypact_[] =
  {
     179,   -26,    33,    -4,  -134,    32,    49,     1,  -134,    28,
     189,    25,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,    91,   106,   114,  -134,   132,   135,   125,
       1,   -22,  -134,  -134,    93,  -134,   138,  -134,    88,   103,
    -134,   130,  -134,  -134,   174,   139,   205,   -19,   206,     1,
     143,  -134,  -134,  -134,  -134,  -134,   119,   119,   119,  -134,
      35,   -15,  -134,   185,  -134,  -134,   119,  -134,   225,    -7,
    -134,  -134,    15,   130,  -134,   231,   -35,   -35,  -134,  -134,
     232,   119,   119,   119,   176,   -18,   119,     0,   119,   119,
     119,   119,   119,   119,   119,  -134,     1,   119,   188,   198,
     200,   203,   233,    41,  -134,   271,   119,   274,  -134,  -134,
    -134,   213,   227,   240,   102,  -134,   258,   253,   230,   119,
     133,    99,   159,   104,   104,  -134,  -134,   -25,  -134,   110,
     241,   100,   100,   243,    -7,  -134,    39,   198,   261,   178,
     255,   256,  -134,   102,   253,   119,  -134,  -134,   198,    51,
     259,  -134,  -134,    69,    72,   100,  -134,   262,  -134,  -134,
    -134,   119,   119,  -134,  -134,   257,   263,   260,   115,  -134,
     110,   167,  -134,  -134,    83,   315,  -134,     4,   198,  -134,
    -134,  -134,  -134,   198,   108,  -134,  -134,  -134,   264,    87,
    -134,  -134,    -9,   309,   294,  -134,  -134,  -134,  -134,  -134,
    -134,   100,  -134,  -134,   137,  -134
  };

  const unsigned char
  sqlparser::yydefact_[] =
  {
       0,     0,     0,     0,   105,     0,     0,     0,    43,    64,
       0,     0,    34,    59,    61,    71,    75,    98,   100,   102,
     104,   106,     4,     0,     0,     0,   107,     0,     0,    56,
       0,     0,    53,    55,     0,    63,     0,     1,     0,     0,
       2,    37,   103,   101,     0,     0,     0,     0,     0,     0,
       6,     8,     9,    10,    44,    45,     0,     0,     0,    48,
      52,    35,    46,     0,     5,     3,     0,    60,     0,    81,
      57,    58,     0,    37,    54,     0,    20,    21,    15,    51,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,     0,     0,     0,    38,
       0,     0,     0,     0,    77,     0,     0,     0,    72,     7,
      50,    17,    18,    16,     0,    23,     0,    32,     0,     0,
       0,    22,    19,    11,    12,    13,    14,    37,    47,     0,
      62,     0,     0,     0,    81,    76,     0,    73,     0,    26,
       0,     0,    24,     0,    33,     0,    36,    68,    67,     0,
       0,    39,    40,     0,     0,     0,    78,    93,    95,    97,
      83,     0,     0,    28,    30,     0,     0,    25,     0,    65,
       0,     0,    99,    80,     0,     0,    96,    82,    74,    27,
      29,    31,    70,    69,     0,    41,    42,    79,     0,     0,
      89,    85,     0,     0,     0,    66,    94,    86,    87,    88,
      91,     0,    92,    84,     0,    90
  };

  const short int
  sqlparser::yypgoto_[] =
  {
    -134,  -134,   -34,  -133,   316,  -107,   -65,  -130,  -134,  -134,
     234,  -134,   -29,   278,  -134,  -134,  -134,  -134,  -134,   158,
    -134,  -134,  -134,  -134,   195,  -134,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,  -134
  };

  const short int
  sqlparser::yydefgoto_[] =
  {
      -1,    10,   139,   140,    11,    12,    67,   153,    34,    61,
      62,    95,    31,    32,    33,    13,    14,    36,   130,   149,
      15,    73,    16,   103,   104,   105,   177,   176,   160,    17,
      18,    19,    20,    21
  };

  const short int
  sqlparser::yytable_[] =
  {
      60,    47,   154,   200,    29,    96,    48,   141,   108,    66,
     165,   115,   101,    88,    89,    24,    90,    91,    92,    93,
      94,    25,    76,    77,    78,   174,   189,   190,   116,   179,
     102,    22,    99,   191,    49,    26,   166,    49,    79,   192,
      49,   193,    71,   118,    97,   119,    80,   111,   112,   113,
     194,   201,   117,    23,   120,   121,   122,   123,   124,   125,
     126,    30,   146,    60,   106,   157,    35,   127,    27,   158,
     159,   204,   137,   107,    28,    81,    82,    83,    84,    85,
      86,    87,    40,    88,    89,   144,    90,    91,    92,    93,
      94,   197,   198,   199,    41,   148,    50,    51,    52,    53,
     134,    54,   135,   151,   152,    50,    51,    52,    53,    42,
     168,   167,   169,    50,    51,    52,    53,    43,    50,    51,
      52,    53,    50,    51,    52,    53,    55,   178,   171,     8,
     172,   171,   147,   173,   183,    44,   148,   182,    45,    56,
      57,    63,   171,   145,   187,    64,    58,    59,    56,    57,
      90,    91,    92,    93,    94,    58,    56,    57,    93,    94,
      65,    56,    57,    58,    66,    56,    57,   168,    58,   195,
     185,   186,    58,    81,    82,    83,    84,    85,    86,    87,
       1,    88,    89,    46,    90,    91,    92,    93,    94,    37,
      38,    68,     2,     3,     4,     5,   171,     6,   205,    69,
       7,    75,     2,     3,     4,     5,     8,     6,    70,    72,
       7,    91,    92,    93,    94,     9,     8,    98,    81,    82,
      83,    84,    85,    86,    87,     9,    88,    89,   100,    90,
      91,    92,    93,    94,   109,   110,   114,   162,    81,    82,
      83,    84,    85,    86,    87,   133,    88,    89,   129,    90,
      91,    92,    93,    94,    82,    83,    84,    85,    86,    87,
     131,    88,    89,   132,    90,    91,    92,    93,    94,    83,
      84,    85,    86,    87,   136,    88,    89,   138,    90,    91,
      92,    93,    94,    84,    85,    86,    87,   142,    88,    89,
     143,    90,    91,    92,    93,    94,    -1,    -1,    -1,    87,
     150,    88,    89,   155,    90,    91,    92,    93,    94,    89,
     161,    90,    91,    92,    93,    94,   163,   164,   180,   170,
     188,   202,   175,   203,   181,   196,    39,    74,   184,   156,
       0,   128
  };

  const short int
  sqlparser::yycheck_[] =
  {
      34,    30,   132,    12,     3,    20,    28,   114,    73,    34,
     143,    29,    19,    48,    49,    19,    51,    52,    53,    54,
      55,    25,    56,    57,    58,   155,    22,    23,    46,   162,
      37,    57,    66,    29,    59,     3,   143,    59,     3,    35,
      59,    37,    61,    43,    59,    45,    11,    81,    82,    83,
      46,    60,    86,    20,    88,    89,    90,    91,    92,    93,
      94,    60,   127,    97,    49,    26,    38,    96,    19,    30,
      31,   201,   106,    58,    25,    40,    41,    42,    43,    44,
      45,    46,    57,    48,    49,   119,    51,    52,    53,    54,
      55,     4,     5,     6,     3,   129,     3,     4,     5,     6,
      59,     8,    61,     3,     4,     3,     4,     5,     6,     3,
      59,   145,    61,     3,     4,     5,     6,     3,     3,     4,
       5,     6,     3,     4,     5,     6,    33,   161,    59,    27,
      61,    59,    22,    61,   168,     3,   170,    22,     3,    46,
      47,     3,    59,    10,    61,    57,    53,    54,    46,    47,
      51,    52,    53,    54,    55,    53,    46,    47,    54,    55,
      57,    46,    47,    53,    34,    46,    47,    59,    53,    61,
       3,     4,    53,    40,    41,    42,    43,    44,    45,    46,
       1,    48,    49,    58,    51,    52,    53,    54,    55,     0,
       1,    17,    13,    14,    15,    16,    59,    18,    61,    60,
      21,    58,    13,    14,    15,    16,    27,    18,     3,     3,
      21,    52,    53,    54,    55,    36,    27,    32,    40,    41,
      42,    43,    44,    45,    46,    36,    48,    49,     3,    51,
      52,    53,    54,    55,     3,     3,    60,    59,    40,    41,
      42,    43,    44,    45,    46,    12,    48,    49,    60,    51,
      52,    53,    54,    55,    41,    42,    43,    44,    45,    46,
      60,    48,    49,    60,    51,    52,    53,    54,    55,    42,
      43,    44,    45,    46,     3,    48,    49,     3,    51,    52,
      53,    54,    55,    43,    44,    45,    46,    29,    48,    49,
      60,    51,    52,    53,    54,    55,    43,    44,    45,    46,
      59,    48,    49,    60,    51,    52,    53,    54,    55,    49,
      49,    51,    52,    53,    54,    55,    61,    61,    61,    60,
       5,    12,    60,    29,    61,    61,    10,    49,   170,   134,
      -1,    97
  };

  const unsigned char
  sqlparser::yystos_[] =
  {
       0,     1,    13,    14,    15,    16,    18,    21,    27,    36,
      63,    66,    67,    77,    78,    82,    84,    91,    92,    93,
      94,    95,    57,    20,    19,    25,     3,    19,    25,     3,
      60,    74,    75,    76,    70,    38,    79,     0,     1,    66,
      57,     3,     3,     3,     3,     3,    58,    74,    28,    59,
       3,     4,     5,     6,     8,    33,    46,    47,    53,    54,
      64,    71,    72,     3,    57,    57,    34,    68,    17,    60,
       3,    61,     3,    83,    75,    58,    64,    64,    64,     3,
      11,    40,    41,    42,    43,    44,    45,    46,    48,    49,
      51,    52,    53,    54,    55,    73,    20,    59,    32,    64,
       3,    19,    37,    85,    86,    87,    49,    58,    68,     3,
       3,    64,    64,    64,    60,    29,    46,    64,    43,    45,
      64,    64,    64,    64,    64,    64,    64,    74,    72,    60,
      80,    60,    60,    12,    59,    61,     3,    64,     3,    64,
      65,    67,    29,    60,    64,    10,    68,    22,    64,    81,
      59,     3,     4,    69,    69,    60,    86,    26,    30,    31,
      90,    49,    59,    61,    61,    65,    67,    64,    59,    61,
      60,    59,    61,    61,    69,    60,    89,    88,    64,    65,
      61,    61,    22,    64,    81,     3,     4,    61,     5,    22,
      23,    29,    35,    37,    46,    61,    61,     4,     5,     6,
      12,    60,    12,    29,    69,    61
  };

  const unsigned char
  sqlparser::yyr1_[] =
  {
       0,    62,    63,    63,    63,    63,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    65,    65,    64,    64,
      64,    64,    64,    64,    66,    67,    67,    68,    68,    69,
      69,    69,    69,    70,    70,    70,    71,    71,    71,    72,
      73,    73,    73,    74,    74,    75,    76,    76,    76,    66,
      77,    66,    78,    79,    79,    80,    80,    81,    81,    81,
      81,    66,    82,    83,    83,    66,    84,    85,    85,    86,
      86,    87,    86,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    89,    89,    90,    90,    90,    66,    91,
      66,    92,    66,    93,    66,    94,    66,    95
  };

  const unsigned char
  sqlparser::yyr2_[] =
  {
       0,     2,     2,     3,     2,     3,     1,     3,     1,     1,
       1,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       2,     2,     3,     3,     4,     5,     1,     3,     5,     6,
       5,     6,     3,     4,     1,     3,     6,     0,     2,     1,
       1,     3,     3,     0,     2,     2,     1,     3,     1,     2,
       2,     1,     0,     1,     3,     1,     1,     3,     3,     1,
       4,     1,     5,     1,     0,     3,     5,     1,     1,     3,
       3,     1,     5,     3,     5,     1,     6,     1,     3,     5,
       4,     0,     4,     0,     3,     2,     3,     3,     3,     2,
       5,     3,     3,     0,     3,     1,     2,     1,     1,     8,
       1,     3,     1,     3,     1,     1,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const sqlparser::yytname_[] =
  {
  "$end", "error", "$undefined", "NAME", "STRING", "INTNUM", "FLOATNUM",
  "ADD", "ALL", "ALTER", "AND", "AS", "KEY", "DELETE", "DROP", "QUIT",
  "EXECFILE", "ON", "CREATE", "INDEX", "FROM", "UPDATE", "DEFAULT",
  "AUTO_INCREMENT", "EXISTS", "TABLE", "CHAR", "SELECT", "SET", "NULLX",
  "INT", "FLOAT", "VALUES", "DISTINCT", "WHERE", "UNIQUE", "INSERT",
  "PRIMARY", "INTO", "ASSIGN", "OR", "XOR", "ANDOP", "IN", "IS", "LIKE",
  "NOT", "'!'", "BETWEEN", "COMPARISON", "'|'", "'&'", "'+'", "'-'", "'*'",
  "'/'", "UMINUS", "';'", "'.'", "','", "'('", "')'", "$accept",
  "stmt_list", "expr", "val_list", "stmt", "select_stmt", "opt_where",
  "column_list", "select_opts", "select_expr_list", "select_expr",
  "opt_as_alias", "table_references", "table_reference", "table_factor",
  "delete_stmt", "insert_stmt", "opt_into", "insert_val_list",
  "insert_vals", "update_stmt", "update_asgn_list", "create_table_stmt",
  "create_col_list", "create_definition", "$@1", "column_atts",
  "opt_length", "data_type", "create_index_stmt", "drop_table_stmt",
  "drop_index_stmt", "quit_stmt", "execfile_stmt", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  sqlparser::yyrline_[] =
  {
       0,    87,    87,    88,    89,    90,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   113,   114,   121,   122,
     123,   124,   127,   128,   131,   134,   135,   140,   141,   170,
     171,   172,   173,   175,   176,   177,   180,   181,   182,   185,
     187,   188,   189,   192,   193,   196,   200,   201,   202,   209,
     212,   215,   218,   222,   223,   226,   227,   228,   229,   230,
     231,   233,   236,   239,   241,   245,   249,   252,   253,   255,
     256,   258,   258,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   272,   273,   275,   276,   277,   278,   279,
     281,   283,   285,   287,   289,   291,   293,   295
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
#line 1733 "sqlparser.tab.cc" // lalr1.cc:1167
#line 296 "sqlparser.yy" // lalr1.cc:1168

void emit(char *s,...){
	extern int yylineno;
	va_list ap;
	va_start(ap,s);
	printf("rpn: ");
	vfprintf(stdout,s,ap);
	printf("\n");
}
/*
void yyerror(char *s,...){
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
