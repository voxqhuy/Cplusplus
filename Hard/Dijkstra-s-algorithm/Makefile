PROGNAME = test_spm

a.exe: ${PROGNAME}.cpp
	c:/MinGW/bin/g++ -Wall -std=c++17 -o a.exe -g -Ic:/MinGW/include ${PROGNAME}.cpp


run: a.exe
	.\a.exe

clean:
	del /Q a.exe

15: a.exe
	a.exe < s_graph15.text

20: a.exe
	a.exe < s_graph20.text

50: a.exe
	a.exe < s_graph50.text

100: a.exe
	a.exe < s_graph100.text

200: a.exe
	a.exe < s_graph200.text

300: a.exe
	a.exe < s_graph300.text

1000: a.exe
	a.exe < s_graph1000.text

