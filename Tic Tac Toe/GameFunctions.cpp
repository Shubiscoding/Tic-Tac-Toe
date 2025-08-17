#include "GameFunctions.h"

void MakeTurn(int& turn, int& totalturns, sf::Vector2f MousePos, float CellSize, int matrix[3][3], sf::RenderWindow& window)
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
                turn = 2;
                totalturns++;
            }
            else if (turn == 2)
            {
                matrix[row][column] = 2;
                turn = 1;
                totalturns++;
            }
        }
    }
}

void ClearBoard(int matrix[3][3], int& totalturns)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[i][j] = 0;
        }
    }

    totalturns = 0;
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

bool GameEnd(int matrix[3][3], int& totalturns, int turn, int& score_x, int& score_o, bool& NoWin)
{
    int last_turn = 3 - turn; 

    for (int i = 0; i < 3; i++)
    {
        // Horizontal 
        if ((matrix[i][0] == last_turn && matrix[i][1] == last_turn && matrix[i][2] == last_turn) || (matrix[0][i] == last_turn && matrix[1][i] == last_turn && matrix[2][i] == last_turn))
        {
            return true; 
        }
    }
    if ((matrix[0][0] == last_turn && matrix[1][1] == last_turn && matrix[2][2] == last_turn) || (matrix[0][2] == last_turn && matrix[1][1] == last_turn && matrix[2][0] == last_turn))
    {
        return true; 
    }
    else if (totalturns == 9)
    {
        NoWin = false; 
        return true;
    }
    return false; 
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

void UpdateScore(sf::Text& score, int increment)
{
    score.setString(std::to_string(increment));
}

bool checkButtonCollision(sf::Sprite& Button, sf::Vector2f Mousepos)
{
    if (Button.getGlobalBounds().contains(Mousepos))
    {
        Button.setScale(sf::Vector2f(6, 6));
        return true;
    }
    else
    {
        Button.setScale(sf::Vector2f(5, 5));
        return false;
    }
}
