#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>

struct CreateLine
{
    sf::RectangleShape shape;

    CreateLine(sf::Vector2f Size, sf::Vector2f position)
    {
        shape.setPosition(position);
        shape.setSize(Size);
    }

    sf::Vector2f getPosition() const 
    {
        return shape.getPosition();
    }

    sf::FloatRect getGlobalBounds() const
    {
        return shape.getGlobalBounds();
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(shape);
    }

    void rotate(sf::Angle angle)
    {
        shape.setRotation(angle);
    }

    void setOrigin(sf::Vector2f pos)
    {
        shape.setOrigin(pos);
    }

    sf::Vector2f getOrigin() const
    {
        return shape.getOrigin();
    }

    sf::Vector2f getSize() const
    {
        return shape.getSize();
    }
};

struct CreateCircle
{
    sf::CircleShape shape;

    CreateCircle(float Size, sf::Vector2f position)
    {
        shape.setPosition(position);
        shape.setRadius(Size);
    }
    sf::Vector2f getPosition() const
    {
        return shape.getPosition();
    }

    sf::FloatRect getGlobalBounds() const
    {
        return shape.getGlobalBounds();
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(shape);
    }
};

//functions
void MakeTurn(int& turn, int& last_turn, sf::Vector2f MousePos, float CellSize, int matrix[3][3], sf::RenderWindow& window);
void ClearBoard(int matrix[3][3]); 
void GameEnd(int martix[3][3], int turn);
void Make_o(float column, float row, sf::RenderWindow& window);
void Make_x(float column, float row, sf::RenderWindow& window);

unsigned int width = 840; 
unsigned int height = 640; 

int main()
{
    //creating the window
    sf::RenderWindow window(sf::VideoMode({width, height}), "Tic Tac Toe");
    
    //system variables 
    float cell = 200.0f; 
    int turn = 1;
    int last_turn = 1;
    float margin = 10.0f;
    int matrix[3][3] = { {0, 0, 0},{0, 0,0}, {0, 0, 0} };
    sf::Vector2f x_LineSize(10.0f, height); 
    sf::Vector2f y_LineSize(width - 200.0f, 10.0f); 

    //Creating the box
    // ---x---
    CreateLine x_1(x_LineSize, sf::Vector2f(0.0f, 0.0f));
    CreateLine x_2(x_LineSize, sf::Vector2f(cell + 10.0f, 0.0f));
    CreateLine x_3(x_LineSize, sf::Vector2f(cell*2 + 20.0f, 0.0f));
    CreateLine x_4(x_LineSize, sf::Vector2f(cell*3 + 30.0f, 0.0f));
    // ---y---
    CreateLine y_1(y_LineSize, sf::Vector2f(0.0f, 0.0f));
    CreateLine y_2(y_LineSize, sf::Vector2f(0.0f, cell + 10.0f));
    CreateLine y_3(y_LineSize, sf::Vector2f(0.0f, cell*2 + 20.0f));
    CreateLine y_4(y_LineSize, sf::Vector2f(0.0f, cell*3 + 30.0f));


    //font and Sprites
    sf::Font font;
    sf::Texture TextCross;
    sf::Texture TextZero;
    sf::Texture TextScore; 

    if (!font.openFromFile("Fonts\\Game Paused DEMO.otf"))
    {
        std::cout << "Font not loaded!";
        return -1; 
    } 
    if (!TextScore.loadFromFile("Assets\\Score.png"))
    {
        std::cout << "Font not loaded!";
        return -1;
    }
    if (!TextZero.loadFromFile("Assets\\Zero.png"))
    {
        std::cout << "Font not loaded!";
        return -1;
    }
    if (!TextCross.loadFromFile("Assets\\Cross.png"))
    {
        std::cout << "Font not loaded!";
        return -1;
    }

    // Sprites and Text
    sf::Sprite Cross(TextCross);
    sf::Sprite Zero(TextZero);
    sf::Sprite Score(TextScore);

    sf::Vector2f pos(cell * 3 + 35.0f + margin, 0.0f + margin);
    Score.setScale(sf::Vector2f(3.5f, 3.5f));
    Score.setPosition(pos);

    while (window.isOpen())
    {
        sf::Vector2i mPos = sf::Mouse::getPosition(window);
        sf::Vector2f RemPos = window.mapPixelToCoords(mPos);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                MakeTurn(turn, last_turn, RemPos, cell, matrix, window);
            }

        }

        //checking for game end 
        GameEnd(matrix, last_turn);

        window.clear();

        //Make O and X
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (matrix[i][j] == 1)
                {
                    Make_o(i * cell + margin * (i + 1), j * cell + margin * (1 + j), window);
                }
                else if (matrix[i][j] == 2)
                {
                    Make_x(i * cell + margin * (i + 1), j * cell + margin * (1 + j), window);
                }
            }
        }

        //Menu
        x_1.draw(window);
        x_2.draw(window);
        x_3.draw(window);
        x_4.draw(window);
        y_1.draw(window);
        y_2.draw(window);
        y_3.draw(window);
        y_4.draw(window);

        // side menu
        window.draw(Score);

        window.display();

    }
    return 0; 
}

void MakeTurn(int& turn, int& last_turn, sf::Vector2f MousePos, float CellSize, int matrix[3][3], sf::RenderWindow& window)
{
    int row = (MousePos.y - 10.0f) / CellSize; 
    int column = (MousePos.x - 10.0f) / CellSize;
    if (row >= 0 && row <= 3 && column >= 0 && column < 3)
    {
        if (matrix[row][column] == 0) // zero means clear
        {
            if (turn == 1)
            {
                matrix[row][column] = 1;
                last_turn = 1;
                turn = 2; 
            }
            else if ( turn == 2)
            {
                matrix[row][column] = 2;
                last_turn = 2;
                turn = 1;
            }
        }
    }
}

void ClearBoard(int matrix[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[i][j] = 0; 
        }
    }
}

void Make_x(float column, float row, sf::RenderWindow& window)
{
    sf::Vector2f cros_size(10.0f, 200.0f);
    float error = 100.0f;
    sf::Vector2f pos(row + error, column + error);

    CreateLine l1(cros_size, pos);
    CreateLine l2(cros_size, pos);

    l1.setOrigin(sf::Vector2f(0, l1.getSize().y / 2.0f));
    l2.setOrigin(sf::Vector2f(0, l2.getSize().y / 2.0f));

    sf::Angle pos_angle = sf::degrees(45);
    sf::Angle neg_angle = sf::degrees(45 + 90);
    l1.rotate(pos_angle);
    l2.rotate(neg_angle);

    l1.draw(window);
    l2.draw(window);
}

void Make_o(float column, float row, sf::RenderWindow& window)
{
    CreateCircle shape(100.0f, sf::Vector2f(row, column));
    shape.draw(window); 
}

void GameEnd(int martix[3][3], int turn)
{
    for (int i = 0; i < 3; i++)
    {
        // Horizontal 
        if (martix[i][0] == turn && martix[i][1] == turn && martix[i][2] == turn)
        {
            std::cout << "Player won" << turn << std::endl;
            ClearBoard(martix);
        }
        //Vertical
        else if (martix[0][i] == turn && martix[1][i] == turn && martix[2][i] == turn)
        {
            std::cout << "Player won" << turn << std::endl;
            ClearBoard(martix);
        }
    }

    if (martix[0][0] == turn && martix[1][1] == turn && martix[2][2] == turn)
    {
        std::cout << "Player won" << turn << std::endl;
        ClearBoard(martix);
    }
    else if (martix[0][2] == turn && martix[1][1] == turn && martix[2][0] == turn)
    {
        std::cout << "Player won" << turn << std::endl;
        ClearBoard(martix);
    }
}
