all:
	lex -olex.cpp string.l
	g++ *.cpp -o smpl
