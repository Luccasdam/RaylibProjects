/**
	Author: Luccas de Avila Machado.
	This is made after watching CS50's intro to Game Development on youtube: https://youtu.be/jZqYXSmgDuM?list=PLWKjhJtqVAbluXJKKbCIb4xd7fcRkpzoz

	The purpose is to translate the course to C++ using raylib. I am making this for my own study and making it available for everyone else who wants to learn about programming in C++.

	The original comment:
    -   GD50 2018
    -   Pong Remake

        -- Main Program --

    -   Author: Colton Ogden
    -   cogden@cs50.harvard.edu

    -   Originally programmed by Atari in 1972. Features two paddles, controlled by players, with the goal of getting the ball past your opponent's edge. First to 10 points wins.

    -   This version is built to more closely resemble the NES than the original Pong machines or the Atari 2600 in terms of resolution,
    though in widescreen (16:9) so it looks nicer on modern systems.
*/

#include <string>

#include "raylib.h"
#include "Paddle.h"
#include "Ball.h"

int main()
{
    InitWindow(1280, 720, "CS50 - 01 - Pong");
    SetWindowState(FLAG_VSYNC_HINT);

    InitAudioDevice();

    Paddle Player1(16, GetScreenHeight() / 2, KEY_W, KEY_S);
    Paddle Player2(GetScreenWidth() - 16, GetScreenHeight() / 2, KEY_I, KEY_K);

    int Player1Score{};
    int Player2Score{};
    int WinningScore{ 5 };

    int ServingPlayer{ 1 };
    int WinningPlayer{};
    std::string GameState = "Start";

    Sound BallHit = LoadSound("D:/Misc/Studying/RaylibProjects/CS50 - 01 - Pong/Sounds/BallHit.wav");
    Sound BallScore = LoadSound("D:/Misc/Studying/RaylibProjects/CS50 - 01 - Pong/Sounds/BallScore.wav");
    Ball Ball(GetScreenWidth() / 2, GetScreenHeight() / 2);


    while (!WindowShouldClose())
    {
        Player1.Tick(GetFrameTime());
        Player2.Tick(GetFrameTime());


        if (GameState == "Start")
        {
            Ball.Tick(GetFrameTime());

            if (Ball.CheckCollision(Player1))   PlaySound(BallHit);
            if (Ball.CheckCollision(Player2))   PlaySound(BallHit);

            if (Ball.CheckScore())
            {
                if (Ball.PosX > GetScreenWidth())
                {
                    ++Player1Score;
                    PlaySound(BallScore);

                    if (Player1Score == WinningScore)
                    {
                        WinningPlayer = 1;
                        GameState = "End";
                    }
                    else
                    {
                        GameState = "Serving";
                        ServingPlayer = 2;
                        Ball.Reset();
                    }
                }
                else
                {
                    ++Player2Score;
                    PlaySound(BallScore);

                    if (Player2Score == WinningScore)
                    {
                        WinningPlayer = 2;
                        GameState = "End";
                    }
                    else
                    {
                        GameState = "Serving";
                        ServingPlayer = 1;
                        Ball.Reset();
                    }
                }
            }
        }
        else if (GameState == "Serving")
        {
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
            {
                Ball.GetRandomDirection(ServingPlayer);
                GameState = "Start";
            }
        }
        else
        {
            int TextSize = MeasureText("Player 0 is the Winner!", 64);
            DrawText(TextFormat("Player %i is the Winner!", WinningPlayer), (GetScreenWidth() - TextSize) / 2, GetScreenHeight() / 4, 64, WHITE);

            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
            {
                ServingPlayer = 0;
                WinningPlayer = 0;
                Player1Score = 0;
                Player2Score = 0;
                Ball.Reset();
                GameState = "Serving";
            }
        }



        BeginDrawing();
        ClearBackground(BLACK);

        int Score1TextSize = MeasureText(TextFormat("%i", Player1Score), 64);
        DrawText(TextFormat("%i", Player1Score), GetScreenWidth() / 4 - Score1TextSize / 2, GetScreenHeight() / 16, 64, WHITE);

        int Score2TextSize = MeasureText(TextFormat("%i", Player2Score), 64);
        DrawText(TextFormat("%i", Player2Score), GetScreenWidth() - (GetScreenWidth() / 4) - (Score2TextSize / 2), GetScreenHeight() / 16, 64, WHITE);

        Player1.Draw();
        Player2.Draw();
        Ball.Draw();

        EndDrawing();
    };

    UnloadSound(BallHit);
    UnloadSound(BallScore);

    CloseWindow();
};