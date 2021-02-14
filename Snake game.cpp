#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "Header.h"

extern bool gameOver;
extern char mode;

using namespace std;

int main()
{
    bool continua = true;

    for (;continua;)
    {
		choose();
		setup();

        switch (mode)
        {
        case '1':
			for (; !gameOver;)
				infinity();
            break;
        case '2':
			for (; !gameOver;)
				boxmode();
            break;
        }
        int con = continuare();

		continua = con == 1 ? true : false;
    }
}