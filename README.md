����
���������� ������������ ���� ����� �� ����� C++ � �������������� ���������� SFML.

�����������
������� ���� ������� ������� � ���������

������� ����

��������� ������� � ������� SFML

������������������ ������ ����� CMake

��������� ������ ����� Doctest

��������� ������������ ����� Doxygen

��������� � ������
������������ �����������
bash
����������
�������������
git clone https://github.com/mustafayevbst/minesweeper.git
cd minesweeper
����������� �����������
?? ��������: ������������� ������ MinGW ������ ���� ������ 13.1.0 (64-bit)

MinGW 13.1.0 (64-bit)
������� ����� ������:
https://github.com/brechtsanders/winlibs_mingw/releases/download/13.1.0-16.0.5-11.0.0-msvcrt-r5/winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5.7z

��������� �����������:
C++ ���������� � ���������� C++17

CMake 3.10+

SFML 2.6.2 (�������: https://www.sfml-dev.org/download.php)

Doctest (��� ��������� ������)

Doxygen (��� ��������� ������������)

������ �������
bash
����������
�������������
mkdir build
cd build
cmake ..
cmake --build .
������
����� ������ ����� ��������� ����������� ����:

bash
����������
�������������
./minesweeper.exe
��������� �������
bash
����������
�������������
minesweeper/
?
??? src/
?   ??? Board.h / Board.cpp
?   ??? Game.h / Game.cpp
?   ??? Menu.h / Menu.cpp
?   ??? ... (��������� ���������)
?
??? assets/
?   ??? (������� ����: ������, ��������)
?
??? tests/
?   ??? (��������� ����� �� doctest)
?
??? docs/
?   ??? (������������, ������������ Doxygen)
?
??? CMakeLists.txt
??? README.md
�����
mustafayevbst