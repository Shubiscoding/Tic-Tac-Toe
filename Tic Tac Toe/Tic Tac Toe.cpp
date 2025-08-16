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

    void draw(sf::RenderWindow& window) const
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

    void setFillColor(sf::Color color)
    {
        shape.setFillColor(color);
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
void DrawGridX(sf::RenderWindow& window, const CreateLine& X1, const CreateLine& X2, const CreateLine& X3, const CreateLine& X4); 
void DrawGridY(sf::RenderWindow& window, const CreateLine& Y1, const CreateLine& Y2, const CreateLine& Y3, const CreateLine& Y4); 
void DrawMenu(sf::RenderWindow& window, sf::Sprite cross, sf::Sprite zero, sf::Sprite score, const CreateLine& X1, const CreateLine& X2, const CreateLine& X3, const CreateLine& X4, const CreateLine& X5, const CreateLine& X6, const CreateLine& X7);
void MakeTurn(int& turn, int& last_turn, sf::Vector2f MousePos, float CellSize, int matrix[3][3], sf::RenderWindow& window); 
void ClearBoard(int matrix[3][3]); 
void GameEnd(int martix[3][3], int turn);
void Make_o(float column, float row, sf::RenderWindow& window);
void Make_x(float column, float row, sf::RenderWindow& window);

int main()
{
    //system variables
    unsigned int width = 840;
    unsigned int height = 640;
    int turn = 1;
    int last_turn = 1;
    int matrix[3][3] = { {0, 0, 0},{0, 0,0}, {0, 0, 0} };
    float cell = 200.0f;
    float displacement = 60.0f;
    float MenuDisplace = cell * 3 + 30.0f;
    float margin = 10.0f;
    
    //creating the window
    sf::RenderWindow window(sf::VideoMode({width, height}), "Tic Tac Toe");


    //Creating the box
    // ---x---
    sf::Vector2f GridSize(10.0f, height);

    CreateLine GridX_1(GridSize, sf::Vector2f(0.0f, 0.0f));
    CreateLine GridX_2(GridSize, sf::Vector2f(cell + 10.0f, 0.0f));
    CreateLine GridX_3(GridSize, sf::Vector2f(cell*2 + 20.0f, 0.0f));
    CreateLine GridX_4(GridSize, sf::Vector2f(cell*3 + 30.0f, 0.0f));
    CreateLine MenuX_1(GridSize, sf::Vector2f(MenuDisplace, 0.0f));
    

    // ---y---
    sf::Vector2f MenuSize(width - 200.0f, 10.0f);

    CreateLine GridY_1(MenuSize, sf::Vector2f(0.0f, 0.0f));
    CreateLine GridY_2(MenuSize, sf::Vector2f(0.0f, cell + 10.0f));
    CreateLine GridY_3(MenuSize, sf::Vector2f(0.0f, cell*2 + 20.0f));
    CreateLine GridY_4(MenuSize, sf::Vector2f(0.0f, cell*3 + 30.0f));
    CreateLine MenuX_2(MenuSize, sf::Vector2f(MenuDisplace, 108.0f));
    CreateLine MenuX_3(MenuSize, sf::Vector2f(MenuDisplace, 208.0f));
    CreateLine MenuX_4(MenuSize, sf::Vector2f(MenuDisplace, 308.0f));
    CreateLine MenuX_5(MenuSize, sf::Vector2f(MenuDisplace, 408.0f));
    CreateLine MenuX_6(MenuSize, sf::Vector2f(MenuDisplace, 508.0f));
    CreateLine MenuX_7(MenuSize, sf::Vector2f(MenuDisplace, 630.0f));
    CreateLine bg(sf::Vector2f(width - MenuDisplace, 122), sf::Vector2f(MenuDisplace, 508.0f));
    bg.setFillColor(sf::Color::Yellow);


    //font and Sprites
    sf::Font font;
    sf::Texture TextCross;
    sf::Texture TextZero;
    sf::Texture TextScore; 

    if (!font.openFromFile("Fonts\\Pixel Sans Serif.ttf"))
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
    sf::Sprite zero_turn(TextZero);
    sf::Sprite crossTurn(TextCross);
    sf::Text zero_text(font);
    sf::Text cross_text(font);
    sf::Sprite Score(TextScore);

    // Side menu
    sf::Vector2f pos(cell * 3 + 35.0f + margin, 0.0f + margin + 5.0f);

    Score.setPosition(pos);
    Score.setScale(sf::Vector2f(3.50f, 3.50f));

    Cross.setPosition(sf::Vector2f(pos.x + 50.0f, pos.y + 106.0f));
    Cross.setScale(sf::Vector2f(5.0f, 5.0f));
    cross_text.setString("0");
    cross_text.setCharacterSize(70.0f);
    cross_text.setPosition(sf::Vector2f(pos.x + displacement, pos.y + 208.0f));

    Zero.setPosition(sf::Vector2f(pos.x + 53.0f, pos.y + 310.0f));
    Zero.setScale(sf::Vector2f(4.5f, 4.5f));
    zero_text.setString("0");
    zero_text.setCharacterSize(70.0f);
    zero_text.setPosition(sf::Vector2f(pos.x + displacement, pos.y + 408.0f));

    crossTurn.setScale(sf::Vector2f(5.0f, 5.0f));
    crossTurn.setPosition(sf::Vector2f(pos.x + 50.0f, pos.y + 518.0f));
    zero_turn.setScale(sf::Vector2f(5.0f, 5.0f));
    zero_turn.setPosition(sf::Vector2f(pos.x + 50.0f, pos.y + 518.0f));


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
        DrawGridX(window, GridX_1, GridX_2, GridX_3, GridX_4);
        DrawGridY(window, GridY_1, GridY_2, GridY_3, GridY_4);

        // side menu
        bg.draw(window);
        DrawMenu(window, Cross, Zero, Score, MenuX_1, MenuX_2, MenuX_3, MenuX_4, MenuX_5, MenuX_6, MenuX_7);
        if (turn == 1)
        {
            window.draw(crossTurn);
        }
        else if (turn == 2)
        {

            window.draw(zero_turn);
        }

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

void DrawGridX(sf::RenderWindow& window, const CreateLine& X1, const CreateLine& X2, const CreateLine& X3, const CreateLine& X4)
{
    X1.draw(window);
    X2.draw(window);
    X3.draw(window);
    X4.draw(window);
}

void DrawGridY(sf::RenderWindow& window, const CreateLine& Y1, const CreateLine& Y2, const CreateLine& Y3, const CreateLine& Y4)
{
    Y1.draw(window);
    Y2.draw(window);
    Y3.draw(window);
    Y4.draw(window);
}

void DrawMenu(sf::RenderWindow& window, sf::Sprite cross, sf::Sprite zero, sf::Sprite score, const CreateLine& X1, const CreateLine& X2, const CreateLine& X3, const CreateLine& X4, const CreateLine& X5, const CreateLine& X6, const CreateLine& X7)
{
    // menu
    X1.draw(window);
    X2.draw(window);
    X3.draw(window);
    X4.draw(window);
    X5.draw(window);
    X6.draw(window);
    X7.draw(window);

    // Sprites

    window.draw(score);
    window.draw(cross);
    window.draw(zero);

}

