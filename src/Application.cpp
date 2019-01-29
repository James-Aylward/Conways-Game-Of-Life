// Written by James Aylward - Do not claim


#include "Application.h"

using namespace std;
using namespace sf;

Application::Application(float updateTime)
: _window(VideoMode(8 * 120, 8 * 120), "Conway's Game of Life")
, _font()
, _text()
, _generation(0)
, _updateTime(updateTime)
, _paused(true)
, _leftHeld(false)
, _rightHeld(false)
, _grid(false)
{
    if (!_font.loadFromFile("arial.ttf"))
    {
        //error
    }
    _text.setFont(_font);
    _text.setCharacterSize(20);
    _text.setStyle(Text::Bold);
    _text.setPosition(0.f, 0.f);
    _text.setColor(Color::White);

    repopulate_cells();

}


void Application::repopulate_cells()
{
    vector<Cell> temp;
    _cells.clear();

    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 120; j++)
        {
            Cell cell;
            cell.alive = getRandomBool();
            temp.push_back(cell);
        }
        _cells.push_back(temp);
        temp.clear();
    }
}

void Application::run()
{

    Clock clock;
    render();
    while (_window.isOpen())
    {
        processEvents();
        if (clock.getElapsedTime().asSeconds() >= _updateTime && !_paused)
        {
            clock.restart();
            update();
        }
        render();
    }
}


void Application::processEvents()
{
    Vector2i pos = Mouse::getPosition(_window);
    int x = pos.x / 8;
    int y = pos.y / 8;

    Event event;
    while (_window.pollEvent(event))
    {
        switch (event.type)
        {
            case Event::Closed:
                _window.close();
                break;

            case Event::KeyPressed:
                if (event.key.code == Keyboard::Space)
                    _paused = !_paused;
                else if (event.key.code == Keyboard::Escape)
                    _window.close();
                else if (event.key.code == Keyboard::C && _paused)
                    clearCells();
                else if (event.key.code == Keyboard::T)
                    _grid = !_grid;
                else if (event.key.code == Keyboard::R)
                    repopulate_cells();
                break;

            case Event::MouseButtonPressed:
                    if (event.mouseButton.button == Mouse::Left)
                        _leftHeld = true;
                    else if (event.mouseButton.button == Mouse::Right)
                        _rightHeld = true;
                    break;

            case Event::MouseButtonReleased:
                    if (event.mouseButton.button == Mouse::Left)
                        _leftHeld = false;
                    else if (event.mouseButton.button == Mouse::Right)
                        _rightHeld = false;
                    break;

            default:
                break;
        }
    }

    if (_leftHeld && withinGrid(x, y) && _paused)
        _cells[x][y].alive = true;
    else if (_rightHeld && withinGrid(x, y) && _paused)
        _cells[x][y].alive = false;
}


void Application::update()
{
    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 120; j++)
        {
            int counter = 0;
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (withinGrid(i + x, j + y) && _cells[i + x][j + y].alive)
                        counter++;
                }
            }
            if (_cells[i][j].alive)
            {
                counter--;
                if (counter > 3 || counter < 2)
                    _cells[i][j].aliveNext = false;
                else
                    _cells[i][j].aliveNext = true;
            }

            else //dead
            {
                if (counter == 3)
                    _cells[i][j].aliveNext = true;
                else
                    _cells[i][j].aliveNext = false;
            }
        }
    }

    // make changes
    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 120; j++)
        {
            _cells[i][j].alive = _cells[i][j].aliveNext;
        }
    }

    // update text
    _generation++;
    ostringstream os;
    os << _generation;
    _text.setString("Generation: " + os.str());
}


void Application::render()
{
    RectangleShape rectangle(Vector2f(8, 8));
    rectangle.setFillColor(Color(255, 0, 0));
    rectangle.setOutlineColor(Color(100, 100, 100));

    if (_grid)
        rectangle.setOutlineThickness(1);
    else
        rectangle.setOutlineThickness(0);

    _window.clear(Color::Black);

    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 120; j++)
        {
            rectangle.setPosition(i * 8, j * 8);
            if (_cells[i][j].alive == true)
            {
                rectangle.setFillColor(Color(255, 0, 0));
            }

            else
            {
                rectangle.setFillColor(Color(0, 0, 0));
            }
            _window.draw(rectangle);
        }
    }
    _window.draw(_text);
    _window.display();

}


int Application::getRandomBool()
{
    return rand() % 2 == 1;
}


bool Application::withinGrid(int x, int y)
{
    if (x >= 0 && x < 120 && y >= 0 && y < 120)
        return true;
    else
        return false;
}


void Application::clearCells()
{
    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 120; j++)
        {
            _cells[i][j].alive = false;
        }
    }

    _generation = 0;
}
