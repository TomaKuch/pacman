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

	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("Map.png");
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	Image pacmanImg;
	pacmanImg.loadFromFile("pacmans.png");
	Texture pacmanTexture;//������� ������ Texture (��������)
	pacmanTexture.loadFromImage(pacmanImg);//�������� � ���� ������ Image (�����������)
	Sprite pacmanSprite;
	pacmanSprite.setTexture(pacmanTexture);

	double CurrentFrame = 0;//������ ������� ����
	double pacmanPositionX = 32;//������� ���� �� ����
	double pacmanPositionY = 32;//������� ���� �� ������

	pacmanSprite.setTextureRect(IntRect(0, 0, 32, 32));
	pacmanSprite.setPosition(pacmanPositionX, pacmanPositionY);
	
	

	while (window.isOpen())
	{
		Clock clock; //������� ���������� �������, �.�. �������� �� �������
		double time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
		clock.restart(); //������������� �����
		time = time / 15; //�������� ����

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
		

	} //���������� Y, �� ������� ����� ��������� ������ �����

	else if (Keyboard::isKeyPressed(Keyboard::Right)) {
		//direction = 0;
		CurrentFrame += speedForFrame *time; //������ ��� ����������� �� "������".
		//���������� ������� �� ���� �������� ������������ ������� � ��������. 
		//������� 0.005 ����� �������� �������� ��������
		if (CurrentFrame > amountOfSprites) CurrentFrame -= amountOfSprites; // ���� ������ � �������� ����� - ������������ �����.
		pacmanSprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32)); //���������� �� ����������� �. ���������� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0
		dx = translocationInPixels; dy = 0;
		pacmanPositionX += dx * time;
		pacmanPositionY += dy * time;
		pacmanSprite.setPosition(pacmanPositionX, pacmanPositionY);

	} //���������� Y, �� ������� ����� ��������� ������ ������ 

	else if (Keyboard::isKeyPressed(Keyboard::Up)) {
		//direction = 3;
		CurrentFrame += speedForFrame *time;
		if (CurrentFrame > amountOfSprites) CurrentFrame -= amountOfSprites;
		pacmanSprite.setTextureRect(IntRect(32 * int(CurrentFrame), 96, 32, 32));
		dx = 0; dy = -translocationInPixels;
		pacmanPositionX += dx * time;
		pacmanPositionY += dy * time;
		pacmanSprite.setPosition(pacmanPositionX, pacmanPositionY);
		
	} //���������� Y �� ������� ����� ��������� ������ ����� 

	else if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
		//direction = 2;
		CurrentFrame += speedForFrame *time;
		if (CurrentFrame > amountOfSprites) CurrentFrame -= amountOfSprites;
		pacmanSprite.setTextureRect(IntRect(32 * int(CurrentFrame), 32, 32, 32));
		dx = 0; dy = translocationInPixels;
		pacmanPositionX += dx * time;
		pacmanPositionY += dy * time;
		pacmanSprite.setPosition(pacmanPositionX, pacmanPositionY);

	} //���������� ����� ������� ����
	followPacmanMoves(pacmanPositionX,pacmanPositionY,myMapArray,dy,dx);
	return pacmanSprite;	
}
//������� ����������� ��������� �������
void followPacmanMoves(double &pacmanPositionX, double &pacmanPositionY, int myMapArray[31][28] ,double dy,double dx) {
	int height = 8;
	int width = 8;

	for (int i = pacmanPositionY/32; i < (pacmanPositionY + height)/32; i++)
	{
		for (int j = pacmanPositionX/32 ; j < (pacmanPositionY + width) / 32; j++) {
			if (myMapArray[i][j] == BORDER)
			{
				if (dy > 0)//���� �� ��� ����,
				{
					pacmanPositionY = i * 32 - height;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
				}
				if (dy < 0)
				{
					pacmanPositionY = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
				}
				if (dx > 0)
				{
					pacmanPositionX = j * 32 - width;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
				}
				if (dx < 0)
				{
					pacmanPositionX = j * 32 + 32;//���������� ���� �����
				}
			} 
			
		}
	}
	
}

