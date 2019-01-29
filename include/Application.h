// Written by James Aylward - Do not claim

#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>


class Application
{
    public:
                                        Application(float updateTime);
        void                            run();

    private:
        void                            processEvents();
        void                            update();
        void                            render();
        int                             getRandomBool();
        bool                            withinGrid(int x, int y);
        void                            clearCells();
        void                            repopulate_cells();

    private:
        struct Cell
        {
            bool aliveNext;
            bool alive;
        };

        sf::RenderWindow                _window;
        std::vector<std::vector<Cell>>  _cells;
        sf::Font                        _font;
        sf::Text                        _text;
        int                             _generation;
        float                           _updateTime;
        bool                            _paused;
        bool                            _leftHeld;
        bool                            _rightHeld;
        bool                            _grid;

};

#endif // APPLICATION_H
