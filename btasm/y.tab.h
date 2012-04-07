/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     GOTO = 258,
     SET = 259,
     SET_HARNESS = 260,
     INC = 261,
     DEC = 262,
     HUD_DIGIT = 263,
     HUD_DIGIT_BLINK = 264,
     HUD_DIGIT_OFF = 265,
     HUD_JAUGE = 266,
     HUD_ICON_ON = 267,
     HUD_ICON_OFF = 268,
     ITYPE = 269,
     ANIM = 270,
     SND = 271,
     LED_ON = 272,
     FLASH_ORANGE = 273,
     FLASH_RED = 274,
     FLASH_GREEN = 275,
     IR = 276,
     MOTOR = 277,
     STATE = 278,
     FIRST_STATE = 279,
     END_STATE = 280,
     EVENT = 281,
     END_EVENT = 282,
     FUN = 283,
     END_FUNCTION = 284,
     IF = 285,
     ELSE = 286,
     END_IF = 287,
     VAR = 288,
     SEQ = 289,
     HUD_JAUGE_BLINK = 290,
     CONFIG = 291,
     SEND = 292,
     RECEIVE = 293,
     LED_OFF = 294,
     LED_INFINITE = 295,
     ANIM_OFF = 296,
     SND_PRIO = 297,
     HARNESS = 298,
     RFID_SCAN = 299,
     RFID_TYPE_MAJOR = 300,
     RFID_TYPE_MINOR = 301,
     INT = 302,
     RTYPE = 303,
     COMP = 304,
     VARATTR = 305,
     ETYPE = 306,
     ID = 307
   };
#endif
/* Tokens.  */
#define GOTO 258
#define SET 259
#define SET_HARNESS 260
#define INC 261
#define DEC 262
#define HUD_DIGIT 263
#define HUD_DIGIT_BLINK 264
#define HUD_DIGIT_OFF 265
#define HUD_JAUGE 266
#define HUD_ICON_ON 267
#define HUD_ICON_OFF 268
#define ITYPE 269
#define ANIM 270
#define SND 271
#define LED_ON 272
#define FLASH_ORANGE 273
#define FLASH_RED 274
#define FLASH_GREEN 275
#define IR 276
#define MOTOR 277
#define STATE 278
#define FIRST_STATE 279
#define END_STATE 280
#define EVENT 281
#define END_EVENT 282
#define FUN 283
#define END_FUNCTION 284
#define IF 285
#define ELSE 286
#define END_IF 287
#define VAR 288
#define SEQ 289
#define HUD_JAUGE_BLINK 290
#define CONFIG 291
#define SEND 292
#define RECEIVE 293
#define LED_OFF 294
#define LED_INFINITE 295
#define ANIM_OFF 296
#define SND_PRIO 297
#define HARNESS 298
#define RFID_SCAN 299
#define RFID_TYPE_MAJOR 300
#define RFID_TYPE_MINOR 301
#define INT 302
#define RTYPE 303
#define COMP 304
#define VARATTR 305
#define ETYPE 306
#define ID 307




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 30 "btasm_ubi.y"
{
    int iVal;
    char *sVal;
    node *nPtr;
}
/* Line 1529 of yacc.c.  */
#line 159 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

