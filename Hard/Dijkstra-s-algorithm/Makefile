a.exe: test_spm.cpp spm.cpp graph.cpp
	c:/MinGW/bin/g++ -Wall -std=c++17 -o a.exe -g -Ic:/MinGW/include test_spm.cpp spm.cpp graph.cpp

run: a.exe
	.\a.exe

clean:
	del /Q a.exe

5: a.exe
	a.exe s_graph5.txt

15: a.exe
	a.exe s_graph15.txt

20: a.exe
	a.exe s_graph20.txt

50: a.exe
	a.exe s_graph50.txt

100: a.exe
	a.exe s_graph100.txt

200: a.exe
	a.exe s_graph200.txt

300: a.exe
	a.exe s_graph300.txt

1000: a.exe
	a.exe s_graph1000.txt

