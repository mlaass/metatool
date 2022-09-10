grammar templ8;
// file        : (name NEWLINE (TAB elements+=action NEWLINE?)* ) EOF;
file        : (name NEWLINE (definition NEWLINE?)* ) EOF;

name        : NAME ':';
definition  : BEGIN deftype (attribute COMMA?)* codeblock;
attribute   : NAME '=' STRING;
deftype     : MEMBER | METHOD | ARGUMENT | STRUCT | FUNCTION | FILE ;
codeblock   : CODE;

// lexer

BEGIN       : 'def';
END         : NEWLINE 'end';
COMMA       : ',';

MEMBER      : 'member';
METHOD      : 'method';
ARGUMENT    : 'argument';
STRUCT      : 'struct';
FUNCTION    : 'function';
FILE        : 'file';

CODE        : '->' CODE_ITEM*? END;


/// longstringitem  ::=  longstringchar | stringescapeseq
fragment CODE_ITEM
 : LONG_STRING_CHAR
 | STRING_ESCAPE_SEQ
 ;

/// longstringchar  ::=  <any source character except "\">
fragment LONG_STRING_CHAR
 : ~'\\'
 ;

/// stringescapeseq ::=  "\" <any source character>
fragment STRING_ESCAPE_SEQ
 : '\\' .
 | '\\' NEWLINE
 ;

STRING      : '\'' .*? '\''
            | '"' .*? '"'
            ;

NAME        : [a-zA-Z0-9\-_]+;
NEWLINE     : ('\r'? '\n' | '\r')+ ;

COMMENT : '#' .*? NEWLINE -> skip;
WHITESPACE  : [ \t] -> skip ;