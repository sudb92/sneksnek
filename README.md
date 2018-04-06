sneksnek 1.0
B Sudarsan, sometime in August 2017
My attempt at teaching myself how to actually use OOP in c++. 

queue.h 
-----------
Implements a single ended queue, which has dynamical memory storage. Each node of the queue
is a coordinate (x,y) - this would be used to store the snake's body in snake.h. The queue class is written out separately.

Class queue has the following private members:
Point *front
Point *back
where Point is a structure having an sf::Vector2f and a Point * pointer. 

Class queue has the following public member functions:
getBack()
getFront()
pushBack()
popFront()

snake.h
----------
Uses a class snake with a queue as its main component. The full list of components include -
1) a queue
2) a direction
3) number of things the snake has eaten
4) the position the head is going to at each instant, called nextheadpos

It has the following member functions:
	snake();
	void setBody(int index, sf::Vector2f value);
	void setDirection(sf::Keyboard::Key key);
	sf::Vector2f getBody(int index);
	void updateBody(sf::Vector2f *food, char* score);
	Point* getHead();
	bool isEatingItself();
	void exitMessage(bool status);


The program depends on sfml library built to the 

libsfml-dev 2.1+dfsg-4ubuntu2
libsfml-network2 2.1+dfsg-4ubuntu2
libsfml-system2 2.1+dfsg-4ubuntu2
libsfml-window2 2.1+dfsg-4ubuntu2
libsfml-graphics2 2.1+dfsg-4ubuntu2
libsfml-audio2 2.1+dfsg-4ubuntu2
