#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <random>
#include "queue.h"
/* body of the dynamic queue
 |front is head | next| next| next |....|back is tail| */
const int XMAX = 200;
const int YMAX = 200;

enum direction{UP,DOWN,LEFT,RIGHT};
	
class snake{
private:
	Queue q;
	direction dir;
	int length, eatcount;
	sf::Vector2f nextheadpos;
public:
	snake();
	void setBody(int index, sf::Vector2f value);
	void setDirection(sf::Keyboard::Key key);
	sf::Vector2f getBody(int index);
	void updateBody(sf::Vector2f *food, char* score);
	Point* getHead();
	bool isEatingItself();
	void exitMessage(bool status);
};

//Constructor for the class
snake::snake(){
	sf::Vector2f loc(10.0,50.0);
	for(int i=0; i<5; i++){
		q.pushBack(loc);
		loc.x = loc.x - 1; }
	dir = RIGHT;
	nextheadpos.x  = 11;
	nextheadpos.y  = 50;
	length = 5;
	eatcount = 0;
}

void snake::setDirection(sf::Keyboard::Key key){
	if(dir==UP||dir==DOWN){
		if(key == sf::Keyboard::Right)
			dir = RIGHT;
		else if(key == sf::Keyboard::Left)
			dir = LEFT;
	}
	else if(dir==LEFT||dir ==RIGHT){
		if(key == sf::Keyboard::Up)
			dir = UP;
		if(key == sf::Keyboard::Down)
			dir = DOWN;
	}
}

Point* snake::getHead(){
	return q.getFront();
}

void snake::updateBody(sf::Vector2f *food, char* score){
	
	Point* temp = NULL;
	temp = q.getBack();//Returns head of the queue
	switch(dir)	{
		case LEFT:	nextheadpos.x = temp->r.x - 10;
					nextheadpos.y = temp->r.y;
					break;
		case RIGHT:	nextheadpos.x = temp->r.x + 10;
					nextheadpos.y = temp->r.y;
					break;
		case UP:	nextheadpos.y = temp->r.y - 10;
					nextheadpos.x = temp->r.x;
					break;
		case DOWN:	nextheadpos.y = temp->r.y + 10;
					nextheadpos.x = temp->r.x;
					break;}

	
	//Exit if collision with screen edge occurs	
	if(nextheadpos.x>=XMAX || nextheadpos.x<=-5 || nextheadpos.y >=YMAX || nextheadpos.y<=-5 || isEatingItself()){
		//printf("Game over! Score:%d\n",length);
		exitMessage(EXIT_FAILURE);}
	if(length == XMAX*YMAX/100){
		//printf("YOU WIN! Score:%d",length);
		exitMessage(EXIT_SUCCESS);}
	
	//Not near food, don't eat
	if((nextheadpos.x-food->x>5)||(nextheadpos.y-food->y>5)||(food->x-nextheadpos.x>5)||(food->y-nextheadpos.y>5)){
		q.pushBack(nextheadpos);//Push nextheadpos to the back of the queue, i.e. the front of the snake.
		q.popFront();//Pop the tail of the snake - the front of the queue
		return;
	}
	else//Find food, eat food
	{ 
	eatcount++;
	q.pushBack(nextheadpos); 
	food->x = (rand()%(XMAX/10))*10;
	food->y = (rand()%(YMAX/10))*10;
	sprintf(score,"%d",length-5);
	if(eatcount == 1	){
		length++;
		eatcount = 0;
	}
	else
		q.popFront();  
	}
}

bool snake::isEatingItself()
{	//What's eating gilbert snake - perform a linear-search collision check with every cell of the snake's body and nextheadpos
	Point* temp=NULL;
	bool flag = false;
	temp = getHead();
	while(temp!=NULL){
		if(!((nextheadpos.x-temp->r.x>5)||(nextheadpos.y-temp->r.y>5)||(temp->r.x-nextheadpos.x>5)||(temp->r.y-nextheadpos.y>5))){
		flag = true;
		}
		temp = temp->next;
	}
	return flag;
}

void snake::exitMessage(bool status)
{
	char score[30];
	sf::RenderWindow gameover(sf::VideoMode(XMAX,YMAX/4),"Game Over");
	sf::Text text;
	sf::Font font;
	if(!font.loadFromFile("UQ_0.ttf"))
		std::cout<<"Error! Font-file UQ_0.ttf not found!";
	text.setFont(font);
	text.setCharacterSize(25);
	text.setPosition(0,0);
	if(status==EXIT_SUCCESS)
		sprintf(score,"You win!\n Score:%d",length-5);
	else
		sprintf(score,"Game over!\n Score:%d",length-5);
	text.setString(score);
	while(gameover.isOpen())
	{
	sf::Event event;
	while(gameover.pollEvent(event))
		if(event.type==sf::Event::Closed)
			gameover.close();
	gameover.draw(text);
	gameover.display();
	}
	exit(status);
}
