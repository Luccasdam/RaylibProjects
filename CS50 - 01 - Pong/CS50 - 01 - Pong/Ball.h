/**
	Author: Luccas de Avila Machado.
	This is made after watching CS50's intro to Game Development on youtube: https://youtu.be/jZqYXSmgDuM?list=PLWKjhJtqVAbluXJKKbCIb4xd7fcRkpzoz

	The purpose is to translate the course to C++ using raylib. I am making this for my own study and making it available for everyone else who wants to learn about programming in C++.

	The original comment:
    -   GD50 2018
    -   Pong Remake

        -- Ball Class --

    -   Author: Colton Ogden
    -   cogden@cs50.harvard.edu

    -   Represents a ball which will bounce back and forth between paddles and walls until it passes a left or right boundary of the screen, scoring a point for the opponent.
	*/

#pragma once

#include <random>
#include <ctime>

#include "raylib.h"

class Ball
{
public:
    float Radius{ 5 };
    float BaseSpeed{ 750 };

    int InitPosX{};
    int InitPosY{};

    int PosX{};
    int PosY{};

    float SpeedX{ BaseSpeed };
    float SpeedY{};

    std::time_t TimeSeconds = std::time(nullptr);


    Ball(int posX, int posY)
    {
        PosX = InitPosX = posX;
        PosY = InitPosY = posY;

        GetRandomDirection(0);
    }


    void Reset()
    {
        PosX = InitPosX;
        PosY = InitPosY;
        SpeedX = BaseSpeed;
    }


    void GetRandomDirection(int servingPlayer)
    {        
        #pragma warning(suppress : 4996) std::asctime(std::localtime(&TimeSeconds));
        SetRandomSeed((unsigned int)TimeSeconds);

        switch (servingPlayer)
        {
            case 1:
                SpeedX = BaseSpeed;
                break;

            case 2:
                SpeedX = BaseSpeed * -1;
                break;

            default:
                SpeedX *= GetRandomValue(1, 2) == 1 ? 1 : -1;
                break;
        }

        SpeedY = (float)GetRandomValue(-(int)BaseSpeed, (int)BaseSpeed);
    }


    void Tick(float dT)
    {
        PosX += (int)(SpeedX * dT);
        PosY += (int)(SpeedY * dT);

        if (PosY < 0)
        {
            PosY = 0;
            SpeedY *= -1;
        }

        if (PosY > GetScreenHeight())
        {
            PosY = GetScreenHeight();
            SpeedY *= -1;
        }
    }


    bool CheckCollision(Paddle paddle)
    {
        const Vector2 PosCenter{ (float)PosX, (float)PosY };

        if (CheckCollisionCircleRec(PosCenter, Radius, paddle.Rect))
        {
            SpeedX *= -1.05f;
            SpeedY = BaseSpeed * ((PosCenter.y - (paddle.PosY + paddle.Height / 2))) / paddle.Height;
            return true;
        }
        return false;
    }

    bool CheckScore()
    {
        if (PosX < 0 || PosX > GetScreenWidth())    return true;
        else return false;
    }

    void Draw()
    {
        DrawCircle(PosX, PosY, Radius, WHITE);
    }
};

