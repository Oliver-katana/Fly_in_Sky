#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include <thread>
#include <SFML/Audio.hpp>

using namespace std;

void SetPos(double x, double y)
{
	COORD pos;
	pos.X = round(x);
	pos.Y = round(y);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Keyboard(int& angle1, int& angle2, bool& shoot1, bool& shoot2)
{
	bool a = GetKeyState(0x41) & 0x8000;
	bool d = GetKeyState(0x44) & 0x8000;
	bool j = GetKeyState(0x4A) & 0x8000;
	bool l = GetKeyState(0x4C) & 0x8000;
	bool q = GetKeyState(0x51) & 0x8000;
	bool p = GetKeyState(0x50) & 0x8000;
	bool esc = GetKeyState(0x1B) & 0x8000;

	if (esc) { exit(0); }
	if (a) { angle1 -= 5; }
	if (d) { angle1 += 5; }
	if (j) { angle2 -= 5; }
	if (l) { angle2 += 5; }
	if (q) { shoot1 = 1; }
	if (p) { shoot2 = 1; }
};

void Borders(double& x, double& y)
{
	if (x > 115) { x = 5; }
	if (x < 2) { x = 115; }
	if (y > 43) { y = 5; }
	if (y < 2) { y = 40; }
}

void Plane(double x, double y, int angle, int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);

	double
		x_cos = cos((angle) * 3.1415 / 180),
		y_sin = sin((angle) * 3.1415 / 180),
		x_cos135_P = cos((angle + 135) * 3.1415 / 180),
		y_sin135_P = sin((angle + 135) * 3.1415 / 180),
		x_cos135_N = cos((angle - 135) * 3.1415 / 180),
		y_sin135_N = sin((angle - 135) * 3.1415 / 180);

	SetPos(x, y);
	cout << "O";
	SetPos(x + x_cos * 1.2, y + y_sin * 1.2);
	cout << "O";
	SetPos(x - x_cos * 1.2, y - y_sin * 1.2);
	cout << "O";
	SetPos(x - x_cos * 2.2, y - y_sin * 2.2);
	cout << "O";
	SetPos(x - x_cos * 3.2, y - y_sin * 3.2);
	cout << "O";
	SetPos(x - x_cos * 4.2, y - y_sin * 4.2);
	cout << "O";
	SetPos(x + x_cos135_P * 1.2, y + y_sin135_P * 1.2);
	cout << "O";
	SetPos(x + x_cos135_P * 2.2, y + y_sin135_P * 2.2);
	cout << "O";
	SetPos(x + x_cos135_N * 1.2, y + y_sin135_N * 1.2);
	cout << "O";
	SetPos(x + x_cos135_N * 2.2, y + y_sin135_N * 2.2);
	cout << "O";
	SetPos(x - x_cos * 4.2 + x_cos135_P * 1.2, y - y_sin * 4.2 + y_sin135_P * 1.2);
	cout << "O";
	SetPos(x - x_cos * 4.2 + x_cos135_N * 1.2, y - y_sin * 4.2 + y_sin135_N * 1.2);
	cout << "O";
}

void Shoot(double x, double y)
{
	//0-черный цвет текста
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	SetPos(x, y);
	cout << "o";
}

void Badabum(double x, double y)
{
	sf::SoundBuffer buffer_badabum;

	if (!buffer_badabum.loadFromFile("E:/Programming/work/VisualStudio/source/repos/Fly_in_Sky/Sounds/badabum.wav"))
		return;
	sf::Sound sound(buffer_badabum);
	sound.play();
	for (size_t i = 0; i < 5; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		SetPos(x + (i - 2), y + (i - 2));
		cout << "#";
		SetPos(x - (i - 2), y - (i - 2));
		cout << "#";
		SetPos(x + (i - 2), y - (i - 2));
		cout << "#";
		SetPos(x - (i - 2), y + (i - 2));
		cout << "#";
		SetPos(x + i, y);
		cout << "#";
		SetPos(x - i, y);
		cout << "#";
		SetPos(x, y + i);
		cout << "#";
		SetPos(x, y - i);
		cout << "#";

		this_thread::sleep_for(0.5s);
	}
}

void Score(int score1, int score2)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	SetPos(56, 1);
	cout << score1 << "  :  " << score2;
}


int main()
{
	setlocale(LC_ALL, "Rus");
	SetWindowPos(GetConsoleWindow(), NULL, 0, 0, 1220, 780, NULL);

	int plane_angle1 = -90, plane_angle2 = 90, shoot_angle1, shoot_angle2;
	double plane_x1 = 15, plane_y1 = 40, plane_x2 = 105, plane_y2 = 5;
	bool shoot1 = 0, shoot2 = 0;
	int i_shoot1 = 0, i_shoot2 = 0;
	double shoot_x1 = 0, shoot_y1 = 0, shoot_x2 = 0, shoot_y2 = 0;
	int score1 = 0, score2 = 0;


	sf::SoundBuffer buffer_plane;
	if (!buffer_plane.loadFromFile("E:/Programming/work/VisualStudio/source/repos/Fly_in_Sky/Sounds/flying_fly.wav"))
		return 0;
	sf::Sound sound_plane(buffer_plane);

	sf::SoundBuffer buffer_shoot1;
	if (!buffer_shoot1.loadFromFile("E:/Programming/work/VisualStudio/source/repos/Fly_in_Sky/Sounds/vyistrel-i-zvuk-letyaschego-snaryada.wav"))
		return 0;
	sf::Sound sound_shoot(buffer_shoot1);

	for (;;)
	{
		sound_plane.play();
		while (sound_plane.getStatus() == sf::Sound::Playing)
		{
			//Считывание клавиатуры
			Keyboard(plane_angle1, plane_angle2, shoot1, shoot2);

			// Реализация движения самолета
			Borders(plane_x1, plane_y1);
			Borders(plane_x2, plane_y2);

			Plane(plane_x1, plane_y1, plane_angle1, FOREGROUND_RED | FOREGROUND_INTENSITY);
			Plane(plane_x2, plane_y2, plane_angle2, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			plane_x1 += cos(plane_angle1 * 3.1415 / 180);
			plane_y1 += sin(plane_angle1 * 3.1415 / 180);
			plane_x2 += cos(plane_angle2 * 3.1415 / 180);
			plane_y2 += sin(plane_angle2 * 3.1415 / 180);

			//Реализация выстрела
			if (shoot1)
			{
				if (shoot1 && !i_shoot1)
				{
					sound_shoot.play();
				}
				if (!i_shoot1)
				{
					shoot_x1 = plane_x1; shoot_y1 = plane_y1; shoot_angle1 = plane_angle1;
				}
				i_shoot1++;
				if (i_shoot1 == 30)
				{
					shoot1 = 0;
					i_shoot1 = 0;
				}
				shoot_x1 += cos(shoot_angle1 * 3.1415 / 180) * 2;
				shoot_y1 += sin(shoot_angle1 * 3.1415 / 180) * 2;
				Borders(shoot_x1, shoot_y1);
				Shoot(shoot_x1, shoot_y1);
			}
			if (shoot2)
			{
				if (shoot2 && !i_shoot2)
				{
					sound_shoot.play();
				}
				if (!i_shoot2)
				{
					shoot_x2 = plane_x2; shoot_y2 = plane_y2;  shoot_angle2 = plane_angle2;
				}
				i_shoot2++;
				if (i_shoot2 == 30)
				{
					shoot2 = 0;
					i_shoot2 = 0;
				}
				shoot_x2 += cos(shoot_angle2 * 3.1415 / 180) * 2;
				shoot_y2 += sin(shoot_angle2 * 3.1415 / 180) * 2;
				Borders(shoot_x2, shoot_y2);
				Shoot(shoot_x2, shoot_y2);
			}

			//Реализация столкновения и попадания выстрела в цель
			if (abs(plane_x1 - plane_x2) < 3 && abs(plane_y1 - plane_y2) < 3)
			{
				sound_plane.stop();
				Badabum(plane_x1, plane_y1);
				plane_angle1 = -90, plane_angle2 = 90;
				plane_x1 = 15, plane_y1 = 40, plane_x2 = 105, plane_y2 = 5;
			}
			if (abs(shoot_x1 - plane_x2) < 3 && abs(shoot_y1 - plane_y2) < 3 && shoot1)
			{
				sound_plane.stop();
				Badabum(plane_x2, plane_y2);
				plane_angle2 = 90;
				plane_x2 = 105, plane_y2 = 5;
				shoot1 = 0;
				i_shoot1 = 0;
				score1++;
			}
			if (abs(shoot_x2 - plane_x1) < 3 && abs(shoot_y2 - plane_y1) < 3 && shoot2)
			{
				sound_plane.stop();
				Badabum(plane_x1, plane_y1);
				plane_angle1 = -90;
				plane_x1 = 15, plane_y1 = 40;
				shoot2 = 0;
				i_shoot2 = 0;
				score2++;
			}

			//Таблица фрагов
			Score(score1, score2);

			this_thread::sleep_for(0.03s);
			system("cls");
		}
	}
	system("color 02");
	return 0;
};