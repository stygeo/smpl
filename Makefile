all:
	lex -olex.cpp string.l
	bison --defines --verbose -o parser.cpp string.y
	g++ *.cpp -o smpl
