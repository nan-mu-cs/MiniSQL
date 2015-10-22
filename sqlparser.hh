// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file sqlparser.hh
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_SQLPARSER_HH_INCLUDED
# define YY_YY_SQLPARSER_HH_INCLUDED
// //                    "%code requires" blocks.
#line 9 "sqlparser.yy" // lalr1.cc:392

	#include <iostream>
	#include <string>
	#include <vector>
	#include <sstream>
	#include "sqlstruct.h"
	class sqlparser_driver;
	void emit(char *s,...);
	std::string itostr(int value);
	std::string ftostr(float value);

#line 56 "sqlparser.hh" // lalr1.cc:392

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"
# include "location.hh"
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif


namespace yy {
#line 133 "sqlparser.hh" // lalr1.cc:392



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class sqlparser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // FLOATNUM
      // floatexp
      char dummy1[sizeof(float)];

      // INTNUM
      // DEFAULT
      // AUTO_INCREMENT
      // NULLX
      // UNIQUE
      // PRIMARY
      // COMPARISON
      // intexp
      // opt_length
      // data_type
      char dummy2[sizeof(int)];

      // expr
      // opt_where
      char dummy3[sizeof(sqlstruct::astree*)];

      // create_col_list
      char dummy4[sizeof(sqlstruct::create_col_list)];

      // create_index_stmt
      char dummy5[sizeof(sqlstruct::createindex)];

      // create_table_stmt
      char dummy6[sizeof(sqlstruct::createtable)];

      // delete_stmt
      char dummy7[sizeof(sqlstruct::deletetable)];

      // insert_stmt
      char dummy8[sizeof(sqlstruct::insertvalues)];

      // create_definition
      char dummy9[sizeof(sqlstruct::record_t)];

      // select_stmt
      char dummy10[sizeof(sqlstruct::selecttable)];

      // NAME
      // STRING
      // drop_table_stmt
      // drop_index_stmt
      // filename
      // execfile_stmt
      char dummy11[sizeof(std::string)];

      // column_atts
      char dummy12[sizeof(std::vector<sqlstruct::col_attr>)];

      // insert_vals
      char dummy13[sizeof(std::vector<sqlstruct::insertitem>)];

      // column_list
      // select_expr_list
      char dummy14[sizeof(std::vector<std::string>)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        END = 0,
        NAME = 258,
        STRING = 259,
        INTNUM = 260,
        FLOATNUM = 261,
        ADD = 262,
        ALL = 263,
        ALTER = 264,
        AND = 265,
        AS = 266,
        KEY = 267,
        DELETE = 268,
        DROP = 269,
        QUIT = 270,
        EXECFILE = 271,
        ON = 272,
        CREATE = 273,
        INDEX = 274,
        FROM = 275,
        UPDATE = 276,
        DEFAULT = 277,
        AUTO_INCREMENT = 278,
        EXISTS = 279,
        TABLE = 280,
        CHAR = 281,
        SELECT = 282,
        SET = 283,
        NULLX = 284,
        INT = 285,
        FLOAT = 286,
        VALUES = 287,
        DISTINCT = 288,
        WHERE = 289,
        UNIQUE = 290,
        INSERT = 291,
        PRIMARY = 292,
        INTO = 293,
        MINUS = 294,
        PLUS = 295,
        STAR = 296,
        SLASH = 297,
        LPAREN = 298,
        RPAREN = 299,
        COMMA = 300,
        SINGLEAND = 301,
        SYMBOLNOT = 302,
        SEMICOL = 303,
        POINT = 304,
        ASSIGN = 305,
        OR = 306,
        XOR = 307,
        ANDOP = 308,
        IN = 309,
        IS = 310,
        LIKE = 311,
        NOT = 312,
        BETWEEN = 313,
        COMPARISON = 314,
        UMINUS = 316
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const float v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const int v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const sqlstruct::astree* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const sqlstruct::create_col_list v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const sqlstruct::createindex v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const sqlstruct::createtable v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const sqlstruct::deletetable v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const sqlstruct::insertvalues v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const sqlstruct::record_t v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const sqlstruct::selecttable v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<sqlstruct::col_attr> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<sqlstruct::insertitem> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::string> v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_NAME (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_STRING (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_INTNUM (const int& v, const location_type& l);

    static inline
    symbol_type
    make_FLOATNUM (const float& v, const location_type& l);

    static inline
    symbol_type
    make_ADD (const location_type& l);

    static inline
    symbol_type
    make_ALL (const location_type& l);

    static inline
    symbol_type
    make_ALTER (const location_type& l);

    static inline
    symbol_type
    make_AND (const location_type& l);

    static inline
    symbol_type
    make_AS (const location_type& l);

    static inline
    symbol_type
    make_KEY (const location_type& l);

    static inline
    symbol_type
    make_DELETE (const location_type& l);

    static inline
    symbol_type
    make_DROP (const location_type& l);

    static inline
    symbol_type
    make_QUIT (const location_type& l);

    static inline
    symbol_type
    make_EXECFILE (const location_type& l);

    static inline
    symbol_type
    make_ON (const location_type& l);

    static inline
    symbol_type
    make_CREATE (const location_type& l);

    static inline
    symbol_type
    make_INDEX (const location_type& l);

    static inline
    symbol_type
    make_FROM (const location_type& l);

    static inline
    symbol_type
    make_UPDATE (const location_type& l);

    static inline
    symbol_type
    make_DEFAULT (const int& v, const location_type& l);

    static inline
    symbol_type
    make_AUTO_INCREMENT (const int& v, const location_type& l);

    static inline
    symbol_type
    make_EXISTS (const location_type& l);

    static inline
    symbol_type
    make_TABLE (const location_type& l);

    static inline
    symbol_type
    make_CHAR (const location_type& l);

    static inline
    symbol_type
    make_SELECT (const location_type& l);

    static inline
    symbol_type
    make_SET (const location_type& l);

    static inline
    symbol_type
    make_NULLX (const int& v, const location_type& l);

    static inline
    symbol_type
    make_INT (const location_type& l);

    static inline
    symbol_type
    make_FLOAT (const location_type& l);

    static inline
    symbol_type
    make_VALUES (const location_type& l);

    static inline
    symbol_type
    make_DISTINCT (const location_type& l);

    static inline
    symbol_type
    make_WHERE (const location_type& l);

    static inline
    symbol_type
    make_UNIQUE (const int& v, const location_type& l);

    static inline
    symbol_type
    make_INSERT (const location_type& l);

    static inline
    symbol_type
    make_PRIMARY (const int& v, const location_type& l);

    static inline
    symbol_type
    make_INTO (const location_type& l);

    static inline
    symbol_type
    make_MINUS (const location_type& l);

    static inline
    symbol_type
    make_PLUS (const location_type& l);

    static inline
    symbol_type
    make_STAR (const location_type& l);

    static inline
    symbol_type
    make_SLASH (const location_type& l);

    static inline
    symbol_type
    make_LPAREN (const location_type& l);

    static inline
    symbol_type
    make_RPAREN (const location_type& l);

    static inline
    symbol_type
    make_COMMA (const location_type& l);

    static inline
    symbol_type
    make_SINGLEAND (const location_type& l);

    static inline
    symbol_type
    make_SYMBOLNOT (const location_type& l);

    static inline
    symbol_type
    make_SEMICOL (const location_type& l);

    static inline
    symbol_type
    make_POINT (const location_type& l);

    static inline
    symbol_type
    make_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_OR (const location_type& l);

    static inline
    symbol_type
    make_XOR (const location_type& l);

    static inline
    symbol_type
    make_ANDOP (const location_type& l);

    static inline
    symbol_type
    make_IN (const location_type& l);

    static inline
    symbol_type
    make_IS (const location_type& l);

    static inline
    symbol_type
    make_LIKE (const location_type& l);

    static inline
    symbol_type
    make_NOT (const location_type& l);

    static inline
    symbol_type
    make_BETWEEN (const location_type& l);

    static inline
    symbol_type
    make_COMPARISON (const int& v, const location_type& l);

    static inline
    symbol_type
    make_UMINUS (const location_type& l);


    /// Build a parser object.
    sqlparser (sqlparser_driver &driver_yyarg);
    virtual ~sqlparser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    sqlparser (const sqlparser&);
    sqlparser& operator= (const sqlparser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned char yytable_[];

  static const unsigned char yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 251,     ///< Last index in yytable_.
      yynnts_ = 26,  ///< Number of nonterminal symbols.
      yyfinal_ = 34, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 63  ///< Number of tokens.
    };


    // User arguments.
    sqlparser_driver &driver;
  };

  // Symbol number corresponding to token number t.
  inline
  sqlparser::token_number_type
  sqlparser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    59,    60,    61,    62
    };
    const unsigned int user_token_number_max_ = 316;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  sqlparser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  sqlparser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  sqlparser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 6: // FLOATNUM
      case 67: // floatexp
        value.copy< float > (other.value);
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
        value.copy< int > (other.value);
        break;

      case 65: // expr
      case 70: // opt_where
        value.copy< sqlstruct::astree* > (other.value);
        break;

      case 78: // create_col_list
        value.copy< sqlstruct::create_col_list > (other.value);
        break;

      case 83: // create_index_stmt
        value.copy< sqlstruct::createindex > (other.value);
        break;

      case 77: // create_table_stmt
        value.copy< sqlstruct::createtable > (other.value);
        break;

      case 73: // delete_stmt
        value.copy< sqlstruct::deletetable > (other.value);
        break;

      case 74: // insert_stmt
        value.copy< sqlstruct::insertvalues > (other.value);
        break;

      case 79: // create_definition
        value.copy< sqlstruct::record_t > (other.value);
        break;

      case 69: // select_stmt
        value.copy< sqlstruct::selecttable > (other.value);
        break;

      case 3: // NAME
      case 4: // STRING
      case 84: // drop_table_stmt
      case 85: // drop_index_stmt
      case 87: // filename
      case 88: // execfile_stmt
        value.copy< std::string > (other.value);
        break;

      case 80: // column_atts
        value.copy< std::vector<sqlstruct::col_attr> > (other.value);
        break;

      case 76: // insert_vals
        value.copy< std::vector<sqlstruct::insertitem> > (other.value);
        break;

      case 71: // column_list
      case 72: // select_expr_list
        value.copy< std::vector<std::string> > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 6: // FLOATNUM
      case 67: // floatexp
        value.copy< float > (v);
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
        value.copy< int > (v);
        break;

      case 65: // expr
      case 70: // opt_where
        value.copy< sqlstruct::astree* > (v);
        break;

      case 78: // create_col_list
        value.copy< sqlstruct::create_col_list > (v);
        break;

      case 83: // create_index_stmt
        value.copy< sqlstruct::createindex > (v);
        break;

      case 77: // create_table_stmt
        value.copy< sqlstruct::createtable > (v);
        break;

      case 73: // delete_stmt
        value.copy< sqlstruct::deletetable > (v);
        break;

      case 74: // insert_stmt
        value.copy< sqlstruct::insertvalues > (v);
        break;

      case 79: // create_definition
        value.copy< sqlstruct::record_t > (v);
        break;

      case 69: // select_stmt
        value.copy< sqlstruct::selecttable > (v);
        break;

      case 3: // NAME
      case 4: // STRING
      case 84: // drop_table_stmt
      case 85: // drop_index_stmt
      case 87: // filename
      case 88: // execfile_stmt
        value.copy< std::string > (v);
        break;

      case 80: // column_atts
        value.copy< std::vector<sqlstruct::col_attr> > (v);
        break;

      case 76: // insert_vals
        value.copy< std::vector<sqlstruct::insertitem> > (v);
        break;

      case 71: // column_list
      case 72: // select_expr_list
        value.copy< std::vector<std::string> > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const float v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const sqlstruct::astree* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const sqlstruct::create_col_list v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const sqlstruct::createindex v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const sqlstruct::createtable v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const sqlstruct::deletetable v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const sqlstruct::insertvalues v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const sqlstruct::record_t v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const sqlstruct::selecttable v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<sqlstruct::col_attr> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<sqlstruct::insertitem> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  sqlparser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::string> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  sqlparser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  sqlparser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 6: // FLOATNUM
      case 67: // floatexp
        value.template destroy< float > ();
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
        value.template destroy< int > ();
        break;

      case 65: // expr
      case 70: // opt_where
        value.template destroy< sqlstruct::astree* > ();
        break;

      case 78: // create_col_list
        value.template destroy< sqlstruct::create_col_list > ();
        break;

      case 83: // create_index_stmt
        value.template destroy< sqlstruct::createindex > ();
        break;

      case 77: // create_table_stmt
        value.template destroy< sqlstruct::createtable > ();
        break;

      case 73: // delete_stmt
        value.template destroy< sqlstruct::deletetable > ();
        break;

      case 74: // insert_stmt
        value.template destroy< sqlstruct::insertvalues > ();
        break;

      case 79: // create_definition
        value.template destroy< sqlstruct::record_t > ();
        break;

      case 69: // select_stmt
        value.template destroy< sqlstruct::selecttable > ();
        break;

      case 3: // NAME
      case 4: // STRING
      case 84: // drop_table_stmt
      case 85: // drop_index_stmt
      case 87: // filename
      case 88: // execfile_stmt
        value.template destroy< std::string > ();
        break;

      case 80: // column_atts
        value.template destroy< std::vector<sqlstruct::col_attr> > ();
        break;

      case 76: // insert_vals
        value.template destroy< std::vector<sqlstruct::insertitem> > ();
        break;

      case 71: // column_list
      case 72: // select_expr_list
        value.template destroy< std::vector<std::string> > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  sqlparser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  sqlparser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 6: // FLOATNUM
      case 67: // floatexp
        value.move< float > (s.value);
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
        value.move< int > (s.value);
        break;

      case 65: // expr
      case 70: // opt_where
        value.move< sqlstruct::astree* > (s.value);
        break;

      case 78: // create_col_list
        value.move< sqlstruct::create_col_list > (s.value);
        break;

      case 83: // create_index_stmt
        value.move< sqlstruct::createindex > (s.value);
        break;

      case 77: // create_table_stmt
        value.move< sqlstruct::createtable > (s.value);
        break;

      case 73: // delete_stmt
        value.move< sqlstruct::deletetable > (s.value);
        break;

      case 74: // insert_stmt
        value.move< sqlstruct::insertvalues > (s.value);
        break;

      case 79: // create_definition
        value.move< sqlstruct::record_t > (s.value);
        break;

      case 69: // select_stmt
        value.move< sqlstruct::selecttable > (s.value);
        break;

      case 3: // NAME
      case 4: // STRING
      case 84: // drop_table_stmt
      case 85: // drop_index_stmt
      case 87: // filename
      case 88: // execfile_stmt
        value.move< std::string > (s.value);
        break;

      case 80: // column_atts
        value.move< std::vector<sqlstruct::col_attr> > (s.value);
        break;

      case 76: // insert_vals
        value.move< std::vector<sqlstruct::insertitem> > (s.value);
        break;

      case 71: // column_list
      case 72: // select_expr_list
        value.move< std::vector<std::string> > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  sqlparser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  sqlparser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  sqlparser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  sqlparser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  sqlparser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  sqlparser::by_type::type_get () const
  {
    return type;
  }

  inline
  sqlparser::token_type
  sqlparser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,    33,   313,
     314,   315,   316
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  sqlparser::symbol_type
  sqlparser::make_END (const location_type& l)
  {
    return symbol_type (token::END, l);
  }

  sqlparser::symbol_type
  sqlparser::make_NAME (const std::string& v, const location_type& l)
  {
    return symbol_type (token::NAME, v, l);
  }

  sqlparser::symbol_type
  sqlparser::make_STRING (const std::string& v, const location_type& l)
  {
    return symbol_type (token::STRING, v, l);
  }

  sqlparser::symbol_type
  sqlparser::make_INTNUM (const int& v, const location_type& l)
  {
    return symbol_type (token::INTNUM, v, l);
  }

  sqlparser::symbol_type
  sqlparser::make_FLOATNUM (const float& v, const location_type& l)
  {
    return symbol_type (token::FLOATNUM, v, l);
  }

  sqlparser::symbol_type
  sqlparser::make_ADD (const location_type& l)
  {
    return symbol_type (token::ADD, l);
  }

  sqlparser::symbol_type
  sqlparser::make_ALL (const location_type& l)
  {
    return symbol_type (token::ALL, l);
  }

  sqlparser::symbol_type
  sqlparser::make_ALTER (const location_type& l)
  {
    return symbol_type (token::ALTER, l);
  }

  sqlparser::symbol_type
  sqlparser::make_AND (const location_type& l)
  {
    return symbol_type (token::AND, l);
  }

  sqlparser::symbol_type
  sqlparser::make_AS (const location_type& l)
  {
    return symbol_type (token::AS, l);
  }

  sqlparser::symbol_type
  sqlparser::make_KEY (const location_type& l)
  {
    return symbol_type (token::KEY, l);
  }

  sqlparser::symbol_type
  sqlparser::make_DELETE (const location_type& l)
  {
    return symbol_type (token::DELETE, l);
  }

  sqlparser::symbol_type
  sqlparser::make_DROP (const location_type& l)
  {
    return symbol_type (token::DROP, l);
  }

  sqlparser::symbol_type
  sqlparser::make_QUIT (const location_type& l)
  {
    return symbol_type (token::QUIT, l);
  }

  sqlparser::symbol_type
  sqlparser::make_EXECFILE (const location_type& l)
  {
    return symbol_type (token::EXECFILE, l);
  }

  sqlparser::symbol_type
  sqlparser::make_ON (const location_type& l)
  {
    return symbol_type (token::ON, l);
  }

  sqlparser::symbol_type
  sqlparser::make_CREATE (const location_type& l)
  {
    return symbol_type (token::CREATE, l);
  }

  sqlparser::symbol_type
  sqlparser::make_INDEX (const location_type& l)
  {
    return symbol_type (token::INDEX, l);
  }

  sqlparser::symbol_type
  sqlparser::make_FROM (const location_type& l)
  {
    return symbol_type (token::FROM, l);
  }

  sqlparser::symbol_type
  sqlparser::make_UPDATE (const location_type& l)
  {
    return symbol_type (token::UPDATE, l);
  }

  sqlparser::symbol_type
  sqlparser::make_DEFAULT (const int& v, const location_type& l)
  {
    return symbol_type (token::DEFAULT, v, l);
  }

  sqlparser::symbol_type
  sqlparser::make_AUTO_INCREMENT (const int& v, const location_type& l)
  {
    return symbol_type (token::AUTO_INCREMENT, v, l);
  }

  sqlparser::symbol_type
  sqlparser::make_EXISTS (const location_type& l)
  {
    return symbol_type (token::EXISTS, l);
  }

  sqlparser::symbol_type
  sqlparser::make_TABLE (const location_type& l)
  {
    return symbol_type (token::TABLE, l);
  }

  sqlparser::symbol_type
  sqlparser::make_CHAR (const location_type& l)
  {
    return symbol_type (token::CHAR, l);
  }

  sqlparser::symbol_type
  sqlparser::make_SELECT (const location_type& l)
  {
    return symbol_type (token::SELECT, l);
  }

  sqlparser::symbol_type
  sqlparser::make_SET (const location_type& l)
  {
    return symbol_type (token::SET, l);
  }

  sqlparser::symbol_type
  sqlparser::make_NULLX (const int& v, const location_type& l)
  {
    return symbol_type (token::NULLX, v, l);
  }

  sqlparser::symbol_type
  sqlparser::make_INT (const location_type& l)
  {
    return symbol_type (token::INT, l);
  }

  sqlparser::symbol_type
  sqlparser::make_FLOAT (const location_type& l)
  {
    return symbol_type (token::FLOAT, l);
  }

  sqlparser::symbol_type
  sqlparser::make_VALUES (const location_type& l)
  {
    return symbol_type (token::VALUES, l);
  }

  sqlparser::symbol_type
  sqlparser::make_DISTINCT (const location_type& l)
  {
    return symbol_type (token::DISTINCT, l);
  }

  sqlparser::symbol_type
  sqlparser::make_WHERE (const location_type& l)
  {
    return symbol_type (token::WHERE, l);
  }

  sqlparser::symbol_type
  sqlparser::make_UNIQUE (const int& v, const location_type& l)
  {
    return symbol_type (token::UNIQUE, v, l);
  }

  sqlparser::symbol_type
  sqlparser::make_INSERT (const location_type& l)
  {
    return symbol_type (token::INSERT, l);
  }

  sqlparser::symbol_type
  sqlparser::make_PRIMARY (const int& v, const location_type& l)
  {
    return symbol_type (token::PRIMARY, v, l);
  }

  sqlparser::symbol_type
  sqlparser::make_INTO (const location_type& l)
  {
    return symbol_type (token::INTO, l);
  }

  sqlparser::symbol_type
  sqlparser::make_MINUS (const location_type& l)
  {
    return symbol_type (token::MINUS, l);
  }

  sqlparser::symbol_type
  sqlparser::make_PLUS (const location_type& l)
  {
    return symbol_type (token::PLUS, l);
  }

  sqlparser::symbol_type
  sqlparser::make_STAR (const location_type& l)
  {
    return symbol_type (token::STAR, l);
  }

  sqlparser::symbol_type
  sqlparser::make_SLASH (const location_type& l)
  {
    return symbol_type (token::SLASH, l);
  }

  sqlparser::symbol_type
  sqlparser::make_LPAREN (const location_type& l)
  {
    return symbol_type (token::LPAREN, l);
  }

  sqlparser::symbol_type
  sqlparser::make_RPAREN (const location_type& l)
  {
    return symbol_type (token::RPAREN, l);
  }

  sqlparser::symbol_type
  sqlparser::make_COMMA (const location_type& l)
  {
    return symbol_type (token::COMMA, l);
  }

  sqlparser::symbol_type
  sqlparser::make_SINGLEAND (const location_type& l)
  {
    return symbol_type (token::SINGLEAND, l);
  }

  sqlparser::symbol_type
  sqlparser::make_SYMBOLNOT (const location_type& l)
  {
    return symbol_type (token::SYMBOLNOT, l);
  }

  sqlparser::symbol_type
  sqlparser::make_SEMICOL (const location_type& l)
  {
    return symbol_type (token::SEMICOL, l);
  }

  sqlparser::symbol_type
  sqlparser::make_POINT (const location_type& l)
  {
    return symbol_type (token::POINT, l);
  }

  sqlparser::symbol_type
  sqlparser::make_ASSIGN (const location_type& l)
  {
    return symbol_type (token::ASSIGN, l);
  }

  sqlparser::symbol_type
  sqlparser::make_OR (const location_type& l)
  {
    return symbol_type (token::OR, l);
  }

  sqlparser::symbol_type
  sqlparser::make_XOR (const location_type& l)
  {
    return symbol_type (token::XOR, l);
  }

  sqlparser::symbol_type
  sqlparser::make_ANDOP (const location_type& l)
  {
    return symbol_type (token::ANDOP, l);
  }

  sqlparser::symbol_type
  sqlparser::make_IN (const location_type& l)
  {
    return symbol_type (token::IN, l);
  }

  sqlparser::symbol_type
  sqlparser::make_IS (const location_type& l)
  {
    return symbol_type (token::IS, l);
  }

  sqlparser::symbol_type
  sqlparser::make_LIKE (const location_type& l)
  {
    return symbol_type (token::LIKE, l);
  }

  sqlparser::symbol_type
  sqlparser::make_NOT (const location_type& l)
  {
    return symbol_type (token::NOT, l);
  }

  sqlparser::symbol_type
  sqlparser::make_BETWEEN (const location_type& l)
  {
    return symbol_type (token::BETWEEN, l);
  }

  sqlparser::symbol_type
  sqlparser::make_COMPARISON (const int& v, const location_type& l)
  {
    return symbol_type (token::COMPARISON, v, l);
  }

  sqlparser::symbol_type
  sqlparser::make_UMINUS (const location_type& l)
  {
    return symbol_type (token::UMINUS, l);
  }



} // yy
#line 1994 "sqlparser.hh" // lalr1.cc:392




#endif // !YY_YY_SQLPARSER_HH_INCLUDED
