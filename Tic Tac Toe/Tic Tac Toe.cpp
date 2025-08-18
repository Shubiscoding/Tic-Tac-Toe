#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>
#include "Shapes.h"
#include "GameFunctions.h"

enum GameState
{
    START, 
    GAME, 
    LOADING,
    GAMEOVER
};

// Constants
const unsigned int SCREEN_WIDTH = 840;
const unsigned int SCREEN_HEIGHT = 640;

const float CELL_SIZE = 200.0f; 
const float CELL_DISPLACEMENT = 60.0f; 
const float CELL_MARGIN = 10.0f; 

const float MENU_DISPLACEMENT = CELL_SIZE * 3 + CELL_DISPLACEMENT / 2.0f; 

const sf::Vector2f BUTTON_SIZE(150.0f, 75.0f);
const sf::Vector2f BUTTON_POSITION(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f + 50.0f);
const sf::Vector2f TITLE_SCALE(13, 13);
const sf::Vector2f BUTTON_SCALE(5, 5);

GameState GS = START; 
int main()
{
    // Game state variables
    int turn = 1;
    int total_turns = 0;
    int rounds = 2;
    int score_x = 0;
    int score_o = 0;
    int matrix[3][3] = { {0, 0, 0},{0, 0,0}, {0, 0, 0} };
    bool ShowMenuBox = false;
    bool NoWin = true;
    bool Gostart = false;

    // Create Window
    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "Tic Tac Toe");
    window.setFramerateLimit(30);

    // GRID
    sf::Vector2f GridSize(10.0f, SCREEN_HEIGHT);

    CreateLine GridX_1(GridSize, sf::Vector2f(0.0f, 0.0f));
    CreateLine GridX_2(GridSize, sf::Vector2f(CELL_SIZE + 10.0f, 0.0f));
    CreateLine GridX_3(GridSize, sf::Vector2f(CELL_SIZE * 2 + 20.0f, 0.0f));
    CreateLine GridX_4(GridSize, sf::Vector2f(CELL_SIZE * 3 + 30.0f, 0.0f));
    CreateLine MenuX_1(GridSize, sf::Vector2f(MENU_DISPLACEMENT, 0.0f));

    // ---y---
    sf::Vector2f MenuSize(SCREEN_WIDTH - 200.0f, 10.0f);

    CreateLine GridY_1(MenuSize, sf::Vector2f(0.0f, 0.0f));
    CreateLine GridY_2(MenuSize, sf::Vector2f(0.0f, CELL_SIZE + 10.0f));
    CreateLine GridY_3(MenuSize, sf::Vector2f(0.0f, CELL_SIZE * 2 + 20.0f));
    CreateLine GridY_4(MenuSize, sf::Vector2f(0.0f, CELL_SIZE * 3 + 30.0f));

    CreateLine MenuX_2(MenuSize, sf::Vector2f(MENU_DISPLACEMENT, 108.0f));
    CreateLine MenuX_3(MenuSize, sf::Vector2f(MENU_DISPLACEMENT, 208.0f));
    CreateLine MenuX_4(MenuSize, sf::Vector2f(MENU_DISPLACEMENT, 308.0f));
    CreateLine MenuX_5(MenuSize, sf::Vector2f(MENU_DISPLACEMENT, 408.0f));
    CreateLine MenuX_6(MenuSize, sf::Vector2f(MENU_DISPLACEMENT, 508.0f));
    CreateLine MenuX_7(MenuSize, sf::Vector2f(MENU_DISPLACEMENT, 630.0f));

    CreateLine bg_1(sf::Vector2f(SCREEN_WIDTH - MENU_DISPLACEMENT, 100.0f), sf::Vector2f(MENU_DISPLACEMENT, 108.0f));
    bg_1.setFillColor(sf::Color::Green);

    CreateLine bg_2(sf::Vector2f(SCREEN_WIDTH - MENU_DISPLACEMENT, 100.0f), sf::Vector2f(MENU_DISPLACEMENT, 308.0f));
    bg_2.setFillColor(sf::Color::Green);

    //font and Sprites
    sf::Font font;
    if (!font.openFromFile("C:\\Users\\91813\\source\\repos\\Tic Tac Toe\\Tic Tac Toe\\Fonts\\Pixel Sans Serif.ttf")) { return -1; }

    sf::Texture TextZero;
    if (!TextZero.loadFromFile("Assets\\Zero.png")) { return -1; }

    sf::Texture TextScore;
    if (!TextScore.loadFromFile("Assets\\Score.png")) { return -1; }

    sf::Texture TextCross;
    if (!TextCross.loadFromFile("Assets\\Cross.png")) { return -1; }

    // Sprites and Text
    sf::Vector2f pos(CELL_SIZE * 3 + 35.0f + CELL_MARGIN, 0.0f + CELL_MARGIN + 5.0f);

    sf::Sprite Score(TextScore);
    Score.setPosition(pos);
    Score.setScale(sf::Vector2f(3.50f, 3.50f));

    sf::Sprite Cross(TextCross);
    Cross.setPosition(sf::Vector2f(pos.x + 50.0f, pos.y + 106.0f));
    Cross.setScale(sf::Vector2f(5.0f, 5.0f));

    sf::Text cross_text(font);
    cross_text.setString("0");
    cross_text.setCharacterSize(70);
    cross_text.setPosition(sf::Vector2f(pos.x + CELL_DISPLACEMENT, pos.y + 208.0f));

    sf::Sprite Zero(TextZero);
    Zero.setPosition(sf::Vector2f(pos.x + 53.0f, pos.y + 310.0f));
    Zero.setScale(sf::Vector2f(4.5f, 4.5f));

    sf::Text zero_text(font);
    zero_text.setString("0");
    zero_text.setCharacterSize(70);
    zero_text.setPosition(sf::Vector2f(pos.x + CELL_DISPLACEMENT, pos.y + 408.0f));

    sf::Text rounds_to_win(font);
    rounds_to_win.setString("RTP");
    rounds_to_win.setCharacterSize(25);
    rounds_to_win.setPosition(sf::Vector2f(MENU_DISPLACEMENT + CELL_MARGIN * 2, pos.y + 508.0f + CELL_MARGIN * 1.5f));

    sf::Text total_rounds(font);
    total_rounds.setString(std::to_string(rounds));
    total_rounds.setCharacterSize(70);
    total_rounds.setPosition(sf::Vector2f(pos.x + CELL_DISPLACEMENT * 1.5f, pos.y + 508.0f + CELL_MARGIN * 1.5f));

    // Menu items
    // creating sprites
    sf::Texture TitleTexture;
    if (!TitleTexture.loadFromFile("Assets\\tictactoe.png")) { return -1; }

    sf::Texture PlayTexture;
    if (!PlayTexture.loadFromFile("Assets\\PlayBtn.png")) { return -1; };

    sf::Texture QuitTexture;
    if (!QuitTexture.loadFromFile("Assets\\StopBtn.png")) { return -1; }

    sf::Sprite TitleSprite(TitleTexture);
    TitleSprite.setScale(TITLE_SCALE);
    TitleSprite.setPosition(sf::Vector2f(BUTTON_POSITION.x, BUTTON_POSITION.y - 200.0f));
    TitleSprite.setOrigin(TitleSprite.getLocalBounds().getCenter());

    sf::Sprite PlayBtn(PlayTexture);
    PlayBtn.setScale(BUTTON_SCALE);
    PlayBtn.setPosition(BUTTON_POSITION);
    PlayBtn.setOrigin(PlayBtn.getLocalBounds().getCenter());

    sf::Sprite StopBtn(QuitTexture);
    StopBtn.setScale(BUTTON_SCALE);
    StopBtn.setPosition(sf::Vector2f(BUTTON_POSITION.x, BUTTON_POSITION.y + 160.0f));
    StopBtn.setOrigin(PlayBtn.getLocalBounds().getCenter());

    // Loading screen
    sf::Text LoadingScreenText(font);
    LoadingScreenText.setString("LOADING...");
    LoadingScreenText.setOrigin(LoadingScreenText.getLocalBounds().getCenter());
    LoadingScreenText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

    sf::Text Winner(font);
    Winner.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    Winner.setOrigin(Winner.getLocalBounds().getCenter());
    Winner.setCharacterSize(30);

    sf::Text EnterText(font);
    EnterText.setString("Enter to go to start screen");
    EnterText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100.0f));
    EnterText.setOrigin(EnterText.getLocalBounds().getCenter());
    EnterText.setCharacterSize(10);

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
            if (GS == GAMEOVER)
            {
               if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter))
                    {
                        GS = LOADING;
                        Gostart = true; 
                    }
            }

            switch (GS)
            {
            case GAME:

                if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    MakeTurn(turn, total_turns, RemPos, CELL_SIZE, matrix, window);
                }
                break;

            case START:

                if (checkButtonCollision(PlayBtn, RemPos))
                {
                    if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
                    {
                        GS = LOADING;
                    }
                }

                if (checkButtonCollision(StopBtn, RemPos))
                {
                    if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
                    {
                        window.close();
                    }
                }
                break;

            case LOADING:
                break;
                
            }
        }
        if (GS == GAME)
        {
            if (score_o >= rounds || score_x >= rounds)
            {
                GS = GAMEOVER;
            }
            else
            {
                //checking for game end 
                if (GameEnd(matrix, total_turns, turn, score_x, score_o, NoWin))
                {
                    if (NoWin)
                    {
                        if (turn == 1)
                        {
                            score_x++;
                            UpdateScore(cross_text, score_x);
                        }
                        else
                        {
                            score_o++;
                            UpdateScore(zero_text, score_o);
                        }
                    }

                    NoWin = true;
                    ShowMenuBox = true;
                    ClearBoard(matrix, total_turns);
                };

                window.clear();

                //Make O and X
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (matrix[i][j] == 1)
                        {
                            Make_o(i * CELL_SIZE + CELL_MARGIN * (i + 1), j * CELL_SIZE + CELL_MARGIN * (1 + j), window);
                        }
                        else if (matrix[i][j] == 2)
                        {
                            Make_x(i * CELL_SIZE + CELL_MARGIN * (i + 1), j * CELL_SIZE + CELL_MARGIN * (1 + j), window);
                        }
                    }
                }

                //Menu
                DrawGridX(window, GridX_1, GridX_2, GridX_3, GridX_4);
                DrawGridY(window, GridY_1, GridY_2, GridY_3, GridY_4);

                // side menu
                if (turn == 1)
                {
                    bg_2.draw(window);
                }
                else
                {
                    bg_1.draw(window);
                }

                DrawMenu(window, Cross, Zero, Score, MenuX_1, MenuX_2, MenuX_3, MenuX_4, MenuX_5, MenuX_6, MenuX_7);

                window.draw(cross_text);
                window.draw(zero_text);
                window.draw(rounds_to_win);
                window.draw(total_rounds);

                window.display();
            }
        }

        else if (GS == START)
        {

            // window clear
            window.clear(sf::Color::White);

            // drawing
            window.draw(TitleSprite);
            window.draw(PlayBtn);
            window.draw(StopBtn);

            // window display
            window.display();
        }

        else if (GS == LOADING)
        {
            // window clear
            window.clear();

            window.draw(LoadingScreenText);

            // window display 
            window.display();

            // time sleep
            sf::sleep(sf::seconds(2));

            if (!Gostart) 
            { 
                GS = GAME; 
            }
            else 
            { 
                GS = START; 
                Gostart = false; 
            }
        }

        else if (GS == GAMEOVER)
        {
            window.clear();

            // checking the winner
            DrawGameOver(window, score_x, score_o, Winner);


            // resetting the variables
            rounds = 0;
            total_turns = 0;
            score_o = 0;
            score_x = 0;
            window.draw(EnterText);

            window.display();
        }
    }
    return 0;
}
    

// add time Stop and a line 
// Game over and score system
// GameStates
// Music
