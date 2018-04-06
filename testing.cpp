#include <iostream>
#include <random>
#include "snake.h"
#include <SFML/Graphics.hpp>
using namespace std;

int main() 
{
	snake s;
	sf::Vector2f *food = new sf::Vector2f;
	char score[10];
	sprintf(score,"%d",0);

	srand(time(0));
	food->x = (rand()%(XMAX/10))*10;
	food->y = (rand()%(YMAX/10))*10;
	
	sf::Vector2f dotsize(10.0,10.0);
	sf::Time sleeptime = sf::seconds(0.08f);

	sf::RenderWindow window(sf::VideoMode(XMAX,YMAX),"Snek");
	sf::Text text;
	sf::Font font;
	if(!font.loadFromFile("UQ_0.ttf"))
	{
		cout<<"Error! Font-file UQ_0.ttf not found!";
		return -1;
	}
	text.setFont(font);
	text.setCharacterSize(18);
	text.setPosition(0,0);
	text.setString(score);

	//pixelpiece is the 'chalk' drawing all the dotted rectangles onscreen.
	sf::RectangleShape pixelpiece;
	pixelpiece.setSize(dotsize);
	pixelpiece.setFillColor(sf::Color::Red);

	window.clear(sf::Color::Black);
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type==sf::Event::Closed)
				window.close();
			if(event.type==sf::Event::KeyPressed)
				s.setDirection(event.key.code);
		}
		Point* temp=NULL;
		temp = s.getHead();
		while(temp!=NULL){
			pixelpiece.setPosition(temp->r.x,temp->r.y);
			window.draw(pixelpiece);
			temp = temp->next;
		}
		pixelpiece.setPosition(food->x,food->y);
		window.draw(pixelpiece);
		s.updateBody(food,score);
		text.setString(score);
		window.draw(text);
		window.display();
		sf::sleep(sleeptime);
		window.clear(sf::Color::Black);		
	} 
    return 0;
}
