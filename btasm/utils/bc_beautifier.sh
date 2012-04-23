#!/bin/bash
cat $1 | sed 's/\(0x[cd].\)/:\1/g' | sed 's/0x53/:0x53/g' | sed 's/0x41/:0x41/g' |tr ':' '\n' 
