# C-
C ++ basic programs

![alt text](https://prod-discovery.edx-cdn.org/media/course/image/72abaeb3-0856-4e89-906a-8b6eef402a1f-05baa5c78f1f.small.jpg)

Sorted in order: **_Easy_**, **_Medium_** and **_Hard_**
The order is based on the complexity of algorithms, from my own experience and webiste geeksforgeeks.org.
Program Descriptions:

B. **_Medium_**
1. **Linked List**:
An implementation of a generic singly linked list. Example functions included are:
  + **operator[]**: the indexing operator allows a client to access an element by its offset from the beginning of the list. As with std::vectors and arrays, the method's behavior is undefined if the client provides an index out of range (this means you need not defend against such attempts). Your method necessarily will be less efficient than **std::vector::operator[]** because linked lists do not support random access.
  + **prepend**: appends an element onto the front of the list. (The class currently offers an insert method that adds an element to the back of the list.)
  + **member**: accepts an argument of the same type as the elements in the list. The function returns *true* if the argument appears in the list; otherwise, the function returns *false*.
  + **operator==**: returns *true* if a list passed as a parameter contains the same elements in the same order as this list; otherwise, the method returns *false*. This method should not copy the elements in the list passed to it, and it should not disturb the contents of either list.
  + **unique**: returns *true* if all of the elements of the list are unique; that is, the list contains no duplicate elements. If at least one of the elements in the list appears more than one time, the method should return *false*. This method should not disturb the contents of the list.

C. **_Hard_**
1. **Huffman Tree**:
Read a text file (the Declaration of Independence in this case), count the frequencies of each charater (uppercased), build a Huffman tree out of the frequencies (%), and encode to bit strings.

```shell
C:\Users\vohuy\Documents\Huffman\>huffman.exe < declaration.text

Counts:
-------
A: 478
B: 95
C: 184
D: 253
E: 862
F: 180
G: 132
H: 350
I: 452
J: 16
K: 14
L: 228
M: 144
N: 484
O: 514
P: 138
Q: 6
R: 425
S: 478
T: 640
U: 209
V: 74
W: 97
X: 9
Y: 81
Z: 4
Total = 6547
---------------------------------

                    / [O:0.078509]
               / (0.152436)
                    \ [N:0.073927]
          / (0.298916)
                         / [D:0.038644]
                    / (0.073469)
                         \ [L:0.034825]
               \ (0.146479)
                    \ [A:0.073011]
     / (0.572629)
                    / [S:0.073011]
               / (0.142050)
                    \ [I:0.069039]
          \ (0.273713)
               \ [E:0.131663]
- (1.000000)
                                   / [V:0.011303]
                              / (0.018787)
                                             / [J:0.002444]
                                        / (0.004582)
                                             \ [K:0.002138]
                                   \ (0.007484)
                                                  / [Q:0.000916]
                                             / (0.001527)
                                                  \ [Z:0.000611]
                                        \ (0.002902)
                                             \ [X:0.001375]
                         / (0.033603)
                              \ [W:0.014816]
                    / (0.065526)
                         \ [U:0.031923]
               / (0.130441)
                    \ [R:0.064915]
          / (0.239499)
                         / [C:0.028104]
                    / (0.055598)
                         \ [F:0.027494]
               \ (0.109058)
                    \ [H:0.053460]
     \ (0.427371)
               / [T:0.097755]
          \ (0.187872)
                              / [B:0.014510]
                         / (0.026883)
                              \ [Y:0.012372]
                    / (0.048877)
                         \ [M:0.021995]
               \ (0.090118)
                         / [P:0.021078]
                    \ (0.041240)
                         \ [G:0.020162]
---------------------------------

A: 1100
B: 000111
C: 01011
D: 11011
E: 100
F: 01010
G: 00000
H: 0100
I: 1010
J: 011111011
K: 011111010
L: 11010
M: 00010
N: 1110
O: 1111
P: 00001
Q: 0111110011
R: 0110
S: 1011
T: 001
U: 01110
V: 0111111
W: 011110
X: 011111000
Y: 000110
Z: 0111110010
```

March 5 2018.
