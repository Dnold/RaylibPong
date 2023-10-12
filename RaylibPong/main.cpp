#include "raylib.h"

struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw()
	{
		DrawCircle((int)x, (int)y, radius, WHITE);
	}
	Vector2 GetCenter()
	{
		return { x,y };
	}
	void Reset() 
	{
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;
		speedX = 300;
		speedY = 300;
	}
};

struct Paddle
{
	float x, y;
	float speed;
	float width, height;

	void Draw()
	{
		DrawRectangleRec(GetRect(), WHITE);
	}
	Rectangle GetRect()
	{
		return Rectangle{ x - width / 2, y - height / 2,10,100 };
	}

};
int MovePaddleVertical(bool isUp, float speed)
{
	if (isUp)
	{
		return -speed * GetFrameTime();
	}
	else
	{
		return speed * GetFrameTime();
	}
}

int main()
{
	InitWindow(800, 600, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball;
	ball.Reset();
	ball.radius = 5;

	ball.speedX = 200;
	ball.speedY = 300;

	Paddle leftPaddle;
	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 500;

	Paddle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 500;

	const char* winnerText = nullptr;

	

	while (!WindowShouldClose())
	{
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedY *= -1;
		}
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}

		if (IsKeyDown(KEY_W) && leftPaddle.y - leftPaddle.height / 2 > 0)
		{
			leftPaddle.y += MovePaddleVertical(true, leftPaddle.speed);
		}
		if (IsKeyDown(KEY_S) && leftPaddle.y + leftPaddle.height / 2 < GetScreenHeight()) {

			leftPaddle.y += MovePaddleVertical(false, leftPaddle.speed);
		}

		if (IsKeyDown(KEY_UP) && rightPaddle.y - rightPaddle.height / 2 > 0)
		{
			rightPaddle.y += MovePaddleVertical(true, rightPaddle.speed);
		}
		if (IsKeyDown(KEY_DOWN) && rightPaddle.y + rightPaddle.height / 2 < GetScreenHeight())
		{
			rightPaddle.y += MovePaddleVertical(false, rightPaddle.speed);
		}

		if (CheckCollisionCircleRec(ball.GetCenter(), ball.radius, leftPaddle.GetRect()))
		{
			if (ball.speedX < 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
			}
		}
		if (CheckCollisionCircleRec(ball.GetCenter(), ball.radius, rightPaddle.GetRect()))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - rightPaddle.y) / (leftPaddle.height / 2) * -ball.speedX;
			}
		}

		if (ball.x < 0)
		{
			winnerText = "Right Player Wins!";
		}
		if (ball.x > GetScreenWidth())
		{
			winnerText = "Left Player Wins!";
		}
		if (winnerText && IsKeyPressed(KEY_SPACE)) {

			ball.Reset();
			winnerText = nullptr;
		}


		BeginDrawing();
		ClearBackground(BLACK);

		if (winnerText) 
		{
			int textWidth = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
		}
		ball.Draw();

		leftPaddle.Draw();
		rightPaddle.Draw();

		DrawFPS(10, 10);
		EndDrawing();
	}


	CloseWindow();
	return 0;
}
