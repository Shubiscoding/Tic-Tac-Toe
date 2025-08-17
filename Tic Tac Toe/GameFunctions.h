#pragma once
#include <SFML/Graphics.hpp>
#include "Shapes.h"

// draw grid
void DrawGridX(sf::RenderWindow& window, const CreateLine& X1, const CreateLine& X2, const CreateLine& X3, const CreateLine& X4);
void DrawGridY(sf::RenderWindow& window, const CreateLine& Y1, const CreateLine& Y2, const CreateLine& Y3, const CreateLine& Y4);

// Draw menu
void DrawMenu(sf::RenderWindow& window, sf::Sprite cross, sf::Sprite zero, sf::Sprite score, const CreateLine& X1, const CreateLine& X2, const CreateLine& X3, const CreateLine& X4, const CreateLine& X5, const CreateLine& X6, const CreateLine& X7);

// Make turns
void MakeTurn(int& turn, int& totalturns, sf::Vector2f MousePos, float CellSize, int matrix[3][3], sf::RenderWindow& window);
void Make_o(float column, float row, sf::RenderWindow& window);
void Make_x(float column, float row, sf::RenderWindow& window);

// Game end and Update
void ClearBoard(int matrix[3][3], int& totalturns);
bool GameEnd(int martix[3][3], int& totalturns, int turn, int& score_x, int& score_o, bool& NoWin);
void UpdateScore(sf::Text& score, int increment);

// Menu
bool checkButtonCollision(sf::Sprite& Button, sf::Vector2f Mousepos);