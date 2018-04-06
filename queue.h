#include <SFML/Graphics.hpp>
struct Point 
    {
        sf::Vector2f r;
        Point *next;
    };

class Queue
{

public:
    Queue()
    {
        front = NULL; // set head, tail to NULL
		back = NULL;
	}

    // This appends a new ordered pair at the end of the queue
    void pushBack(sf::Vector2f r)
    {
        Point *n = new Point();   
        n->r.x = r.x;
		n->r.y = r.y;
		if(back==NULL||front==NULL)
		{
		  front=n;
		  back=n;
		}
		else
		{
		 back->next = n;         
         back = n;
		}               
    }

	//This pops an element off the front of the queue
    sf::Vector2f popFront()
    {
        Point *n = front;
        sf::Vector2f ret;
		ret.x = front->r.x;
		ret.y = front->r.y;
        front = front->next;
        delete n;
        return ret;
    }

	Point* getFront()
	{
		return front;
	}

	Point* getBack()
	{
		return back;
	}


private:
    Point *front;
	Point *back;
};

