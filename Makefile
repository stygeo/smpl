all:
	export BISON_SIMPLE=/usr/bin/bison
	export BISON_HAIRY=/user/bin/bison
	lex -osrc/lex.cpp rules/string.l
	bison --defines --verbose -o src/parser.cpp rules/string.y
	c++ -std=c++11 -g -I. -Iheader src/*.cpp main.cpp -o smpl
