#include "raylib.h"

struct Ball
{
	float PosX, PosY;
	float SpeedX, SpeedY;
	float Radius;

	void Draw()
	{
		DrawCircle((int)PosX, (int)PosY, Radius, WHITE);
	}
};

struct Paddle
{
	int Width, Height;
	int Speed;
	int PosX, PosY;

	Rectangle GetRectangle()
	{
		return Rectangle{ (float)PosX - Width / 2, (float)PosY - Height / 2, (float)Width, (float)Height };
	}

	void Draw()
	{
		DrawRectangleRec(GetRectangle(), WHITE);
	}
};

int main()
{
	InitWindow(800, 600, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball Ball;
	Ball.PosX = GetScreenWidth() / 2.f;
	Ball.PosY = GetScreenHeight() / 2.f;
	Ball.SpeedX = 300;
	Ball.SpeedY = 300;
	Ball.Radius = 5;

	Paddle LeftPaddle;
	LeftPaddle.Width = 10;
	LeftPaddle.Height = 100;
	LeftPaddle.Speed = 500;
	LeftPaddle.PosX = LeftPaddle.Width * 2;
	LeftPaddle.PosY = GetScreenHeight() / 2 - LeftPaddle.Height / 2;

	Paddle RightPaddle;
	RightPaddle.Width = 10;
	RightPaddle.Height = 100;
	RightPaddle.Speed = 500;
	RightPaddle.PosX = GetScreenWidth() - RightPaddle.Width * (2 + 1);
	RightPaddle.PosY = GetScreenHeight() / 2 - RightPaddle.Height / 2;

	const float BallSpeedMultiplier{ 1.1f };
	const char* WinnerText = nullptr;



	while (!WindowShouldClose())
	{
		Ball.PosX += Ball.SpeedX * GetFrameTime();
		Ball.PosY += Ball.SpeedY * GetFrameTime();

		if (Ball.PosY < 0 || Ball.PosY > GetScreenHeight())
		{
			Ball.SpeedY *= -1;
			if (Ball.PosY < 0)	Ball.PosY = 0;
			else Ball.PosY = GetScreenHeight();
		}


		if (IsKeyDown(KEY_W)) {
			if (LeftPaddle.PosY > LeftPaddle.Height/2)	LeftPaddle.PosY -= LeftPaddle.Speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_S)) {
			if (LeftPaddle.PosY < GetScreenHeight() - LeftPaddle.Height/2)	LeftPaddle.PosY += LeftPaddle.Speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_UP)) {
			if (RightPaddle.PosY > RightPaddle.Height/2)	RightPaddle.PosY -= RightPaddle.Speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_DOWN)) {
			if (RightPaddle.PosY < GetScreenHeight() - RightPaddle.Height/2)	RightPaddle.PosY += RightPaddle.Speed * GetFrameTime();
		}

		if (CheckCollisionCircleRec(Vector2{ Ball.PosX, Ball.PosY }, Ball.Radius, LeftPaddle.GetRectangle()))
		{
			Ball.SpeedX *= -BallSpeedMultiplier;
			Ball.SpeedY += (Ball.PosY - LeftPaddle.PosY) / (LeftPaddle.Height / 2) * 300;
		}

		if (CheckCollisionCircleRec(Vector2{ Ball.PosX, Ball.PosY }, Ball.Radius, RightPaddle.GetRectangle()))
		{
			Ball.SpeedX *= -BallSpeedMultiplier;
			Ball.SpeedY += (Ball.PosY - RightPaddle.PosY) / (RightPaddle.Height / 2) * 300;
		}

		if (Ball.PosX < 0)	WinnerText = "Right Player Won!";
		if (Ball.PosX > GetScreenWidth())	WinnerText = "Left Player Won!";

		if (WinnerText && IsKeyPressed(KEY_SPACE))
		{
			Ball.PosX = GetScreenWidth() / 2;
			Ball.PosY = GetScreenHeight() / 2;
			Ball.SpeedX = 300;
			Ball.SpeedY = 300;
			WinnerText = nullptr;
		}

		BeginDrawing();
		ClearBackground(BLACK);

		Ball.Draw();
		LeftPaddle.Draw();
		RightPaddle.Draw();

		if (WinnerText)
		{
			int TextWidth = MeasureText(WinnerText, 32);
			DrawText(WinnerText, (GetScreenWidth() - TextWidth) / 2, GetScreenHeight() / 4, 32, WHITE);
		}


		EndDrawing();
	}


	CloseWindow();
}