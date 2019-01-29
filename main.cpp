// Written by James Aylward - Do not claim

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <Application.h>

int main()
{
    srand(time(NULL));

    float update;
    std::cout << "Enter update time (float): ";
    std::cin >> update;

    Application app(update);
    app.run();

    return 0;
}
