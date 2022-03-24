/**
    Author: Luccas de Avila Machado.
    This is made after watching CS50's intro to Game Development on youtube: https://youtu.be/jZqYXSmgDuM?list=PLWKjhJtqVAbluXJKKbCIb4xd7fcRkpzoz

    The purpose is to translate the course to C++ using raylib. I am making this for my own study and making it available for everyone else who wants to learn about programming in C++.

    The original comment:
    -   GD50 2018
    -   Pong Remake

        -- Paddle Class --

    -   Author: Colton Ogden
    -   cogden@cs50.harvard.edu

    -   Represents a paddle that can move up and down. Used in the main program to deflect the ball back toward the opponent.
    */

#pragma once

#include "raylib.h"

enum class EInputKeys {MoveUp, MoveDown};

class Paddle
{
public:
    int Width{ 10 };
    int Height{ 108 };
    int MoveSpeed{ 500 };

    int PosX{};
    int PosY{};

    int MoveUpKey{};
    int MoveDownKey{};

    Rectangle Rect{ (float)PosX, (float)PosY, (float)Width, (float)Height };


    Paddle(int posX, int posY, char moveUpKey, char moveDownKey)
    {
        PosX = posX - Width/2;
        PosY = posY - Height/2;

        MoveUpKey = moveUpKey;
        MoveDownKey = moveDownKey;
    }


    void Tick(float dT)
    {
        Rect = { (float)PosX, (float)PosY, (float)Width, (float)Height };

        if (IsKeyDown(MoveUpKey) && PosY > 0)   PosY -= int(MoveSpeed * dT);
        if (IsKeyDown(MoveDownKey) && PosY < GetScreenHeight() - Height)   PosY += int(MoveSpeed * dT);
    }

    void Draw()
    {
        DrawRectangle(PosX, PosY, Width, Height, WHITE);
    }
};

