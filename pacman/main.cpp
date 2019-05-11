#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;
enum myMap {GO=1,BORDER=2,WOW=3,TENPOINTS=4,EXITFORGHOSTS=5} Map;

Sprite movePacman(double &CurrentFrame, double &time, Sprite pacmanSprite, Texture pacmanTexture,
	Image pacmanImg, double &pacmanPositionX, double &pacmanPositionY, int myMapArray[31][28]);
void followPacmanMoves(double &pacmanPositionX, double &pacmanPositionY, int myMapArray[31][28], double dy, double dx);

int main()
{
	const int width = 28;
	const int height = 31;
	int myMapArray[height][width] =
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	 2,4,4,4,4,4,4,4,4,4,4,4,4,2,2,4,4,4,4,4,4,4,4,4,4,4,4,2,
	 2,1,2,2,2,2,4,2,2,4,2,2,4,2,2,4,2,2,2,2,2,4,2,2,2,2,4,2,
	 2,1,2,1,1,2,4,2,2,4,4,2,4,4,4,4,4,4,4,4,4,4,2,1,1,2,4,2,
	 2,4,2,2,2,2,4,2,2,2,4,2,2,2,2,2,2,2,2,4,2,4,2,2,2,2,4,2,
	 2,4,4,4,4,4,4,4,2,2,4,2,2,2,2,2,2,2,2,4,2,4,4,4,4,4,4,2,
     2,4,2,2,2,2,2,4,2,2,4,4,4,4,2,2,4,4,4,4,4,4,2,2,2,2,4,2,
	 2,1,2,2,2,4,4,3,2,2,4,2,2,4,2,2,4,2,2,2,4,2,2,2,2,2,4,2,
	 2,1,4,4,4,4,2,4,2,2,2,2,2,4,2,2,1,2,2,1,4,4,4,4,4,4,4,2,
	 2,2,2,2,2,2,2,4,2,2,2,2,2,4,2,2,1,1,1,1,2,4,2,2,2,2,2,2,
	 1,1,1,1,1,2,1,4,2,2,1,1,1,1,1,1,1,1,1,1,2,4,2,1,1,1,1,1,
	 1,1,1,1,1,2,1,2,2,2,1,5,5,5,5,5,5,5,5,1,2,4,2,1,1,1,1,1,
	 1,1,1,1,1,2,4,2,2,2,1,5,1,1,1,1,1,1,5,1,2,4,2,1,1,1,1,1,
	 2,2,2,2,2,2,4,1,1,1,1,5,1,1,1,1,1,1,5,1,2,4,2,2,2,2,2,2,
	 1,1,1,1,1,1,1,2,2,2,1,5,1,1,1,1,1,1,5,1,1,1,1,1,1,1,1,1,
	 2,2,2,2,2,2,4,2,2,2,1,5,5,5,5,5,5,5,5,1,2,4,2,2,2,2,2,2,
	 1,1,1,1,1,2,4,2,2,1,1,1,1,1,1,1,1,1,1,1,2,4,2,1,1,1,1,1,
	 1,1,1,1,1,2,4,2,2,1,2,2,2,2,2,2,2,2,2,1,2,4,2,1,1,1,1,1,
	 1,1,1,1,1,2,4,2,2,1,2,2,2,2,2,2,2,2,2,1,2,4,2,1,1,1,1,1,
	 2,2,2,2,2,2,4,4,4,4,4,4,4,4,2,2,4,4,4,4,2,4,2,2,2,2,2,2,
	 2,4,4,4,4,4,4,2,2,2,2,2,2,4,2,2,4,2,2,4,4,4,4,4,4,4,4,2,
	 2,4,2,2,2,2,4,2,2,2,2,2,2,4,2,2,4,2,2,2,2,1,2,2,2,2,4,2,
	 2,4,2,2,2,2,4,2,2,4,4,4,4,4,4,4,4,4,4,2,2,1,2,2,2,2,4,2,
	 2,3,4,4,2,2,4,1,1,1,2,2,2,2,2,2,2,2,4,1,1,1,2,2,4,4,4,2,
	 2,2,2,4,2,2,4,2,2,4,4,2,2,2,2,2,2,2,1,2,2,1,2,2,4,2,2,2,
	 2,2,2,4,2,2,4,2,2,4,2,2,2,2,2,4,2,1,4,2,2,1,2,2,4,2,2,2,
	 2,1,4,4,1,1,4,2,2,4,4,4,4,2,2,1,4,4,4,2,2,1,1,1,4,4,3,2,
	 2,1,2,2,2,2,4,2,2,2,2,2,1,2,2,4,2,2,2,2,2,2,2,2,2,2,1,2,
	 2,1,2,2,2,2,4,2,2,2,2,2,1,2,2,4,2,2,2,2,2,2,2,2,2,2,1,2,
	 2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
	 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
	};

	RenderWindow window(sf::VideoMode(896, 992), "SFMLworks");

	Image map_image;//объект изображения для карты
	map_image.loadFromFile("Map.png");
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Image pacmanImg;
	pacmanImg.loadFromFile("pacmans.png");
	Texture pacmanTexture;//создаем объект Texture (текстура)
	pacmanTexture.loadFromImage(pacmanImg);//передаем в него объект Image (изображения)
	Sprite pacmanSprite;
	pacmanSprite.setTexture(pacmanTexture);

	double CurrentFrame = 0;//хранит текущий кадр
	double pacmanPositionX = 32;//текущий кадр по иксу
	double pacmanPositionY = 32;//текущий кадр по игреку

	pacmanSprite.setTextureRect(IntRect(0, 0, 32, 32));
	pacmanSprite.setPosition(pacmanPositionX, pacmanPositionY);
	
	

	while (window.isOpen())
	{
		Clock clock; //создаем переменную времени, т.о. привязка ко времени
		double time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time = time / 15; //скорость игры

		Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == Event::Closed)
				window.close();
		}

		pacmanSprite = movePacman(CurrentFrame, time, pacmanSprite, pacmanTexture, pacmanImg, pacmanPositionX,
			pacmanPositionY, myMapArray);

		window.clear();
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (myMapArray[i][j] == GO) {
					s_map.setTextureRect(IntRect(0, 0, 32, 32));
					
				}else if (myMapArray[i][j] == BORDER) {
					s_map.setTextureRect(IntRect(32, 0, 32, 32));
				}
				else if (myMapArray[i][j] == WOW) {
					s_map.setTextureRect(IntRect(64, 0, 32, 32)); 
				}
				else if (myMapArray[i][j] == TENPOINTS) {
					if (int(pacmanPositionX / 32) == j && int(pacmanPositionY / 32) == i) {
						myMapArray[i][j] = GO;
						s_map.setTextureRect(IntRect(0, 0, 32, 32));
					}else
					s_map.setTextureRect(IntRect(96, 0, 32, 32));
				}
				else if (myMapArray[i][j] == EXITFORGHOSTS) {
					s_map.setTextureRect(IntRect(128, 0, 32, 32));
				}

				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}
			
		}
		window.draw(pacmanSprite);
		window.display();
	}

	return 0;
}

Sprite movePacman(double &CurrentFrame, double &time, Sprite pacmanSprite, Texture pacmanTexture,
	Image pacmanImg, double &pacmanPositionX, double &pacmanPositionY , int myMapArray[31][28]) {
	double speedForFrame = 0.5;//dx or dy
	int amountOfSprites = 2;
	int translocationInPixels = 8;
	double dx = 0, dy = 0;
	if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
		//direction = 1;
		CurrentFrame += speedForFrame *time;
		if (CurrentFrame > amountOfSprites) CurrentFrame -= amountOfSprites;
		pacmanSprite.setTextureRect(IntRect(32 * int(CurrentFrame), 64, 32, 32));
		dx = -translocationInPixels; dy = 0;
		pacmanPositionX += dx * time;
		pacmanPositionY += dy * time;
		pacmanSprite.setPosition(pacmanPositionX, pacmanPositionY);
		

	} //координата Y, на которой герой изображен идущим влево

	else if (Keyboard::isKeyPressed(Keyboard::Right)) {
		//direction = 0;
		CurrentFrame += speedForFrame *time; //служит для прохождения по "кадрам".
		//переменная доходит до трех суммируя произведение времени и скорости. 
		//изменив 0.005 можно изменить скорость анимации
		if (CurrentFrame > amountOfSprites) CurrentFrame -= amountOfSprites; // если пришли к третьему кадру - откидываемся назад.
		pacmanSprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
		dx = translocationInPixels; dy = 0;
		pacmanPositionX += dx * time;
		pacmanPositionY += dy * time;
		pacmanSprite.setPosition(pacmanPositionX, pacmanPositionY);

	} //координата Y, на которой герой изображен идущем вправо 

	else if (Keyboard::isKeyPressed(Keyboard::Up)) {
		//direction = 3;
		CurrentFrame += speedForFrame *time;
		if (CurrentFrame > amountOfSprites) CurrentFrame -= amountOfSprites;
		pacmanSprite.setTextureRect(IntRect(32 * int(CurrentFrame), 96, 32, 32));
		dx = 0; dy = -translocationInPixels;
		pacmanPositionX += dx * time;
		pacmanPositionY += dy * time;
		pacmanSprite.setPosition(pacmanPositionX, pacmanPositionY);
		
	} //координата Y на которой герой изображен идущим вверх 

	else if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
		//direction = 2;
		CurrentFrame += speedForFrame *time;
		if (CurrentFrame > amountOfSprites) CurrentFrame -= amountOfSprites;
		pacmanSprite.setTextureRect(IntRect(32 * int(CurrentFrame), 32, 32, 32));
		dx = 0; dy = translocationInPixels;
		pacmanPositionX += dx * time;
		pacmanPositionY += dy * time;
		pacmanSprite.setPosition(pacmanPositionX, pacmanPositionY);

	} //координата героя идущего вниз
	followPacmanMoves(pacmanPositionX,pacmanPositionY,myMapArray,dy,dx);
	return pacmanSprite;	
}
//функция отслеживает положение пэкмена
void followPacmanMoves(double &pacmanPositionX, double &pacmanPositionY, int myMapArray[31][28] ,double dy,double dx) {
	int height = 8;
	int width = 8;

	for (int i = pacmanPositionY/32; i < (pacmanPositionY + height)/32; i++)
	{
		for (int j = pacmanPositionX/32 ; j < (pacmanPositionY + width) / 32; j++) {
			if (myMapArray[i][j] == BORDER)
			{
				if (dy > 0)//если мы шли вниз,
				{
					pacmanPositionY = i * 32 - height;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
				}
				if (dy < 0)
				{
					pacmanPositionY = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
				}
				if (dx > 0)
				{
					pacmanPositionX = j * 32 - width;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
				}
				if (dx < 0)
				{
					pacmanPositionX = j * 32 + 32;//аналогично идем влево
				}
			} 
			
		}
	}
	
}

