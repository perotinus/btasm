#!/bin/bash

#prepare the given source file
tr ',' '\n' < tests/bytecodes/$1.ByteCode.lua | sed 's/ //g' | sed '/^0x[0-9a-f][0-9a-f]/!d' > given010

#prepare the compiled source file
./lexer -c $1.ByteCode.bit tests/$1.ByteCode.txt
tr ',' '\n' < $1.ByteCode.bit | sed 's/ //g' > compiled010

vimdiff compiled010 given010

rm $1.ByteCode.bit
