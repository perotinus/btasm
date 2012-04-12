#ifndef Y_USERDEFS_H
#define Y_USERDEFS_H

/****************************************************
 * User definitions for the parser/lexer
 * For compatibility with older versions of Bison,
 * that do not have the %code directives.
 * 4/11/12 - J. MacMillan
 ****************************************************/

//Name of file currently being parsed
char *fname;

//Redefined location header for lexer/parser.
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
  char *fname;
} YYLTYPE;

#define YYLTYPE_IS_DECLARED 1

//Redefined default location setting macro.
#define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
      (Current).fname        = YYRHSLOC (Rhs, 1).fname;         \
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
      (Current).fname = fname;                       \
	}								\
    while (YYID (0))

#endif
