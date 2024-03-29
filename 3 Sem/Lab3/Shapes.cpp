#include "stdafx.h"
#include <typeinfo>
#include <iostream>
#include <math.h>
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

bool DebugMode = 0;
//cout << typeid(int_var).name() << endl;
//------------------------------------------------Exception
class ExceptionShp
{
private:
	string m_error;

public:
	ExceptionShp()
	{}
	ExceptionShp(string error)
		: m_error(error) {}
	template <typename T>
	void typeCheck(T a)
	{
		short int temp = 0;

		if (typeid(a).name() != typeid(1).name()&& typeid(a).name() != typeid(1.2f).name()&& typeid(a).name() != typeid(1.2).name())
		{
			throw ExceptionShp("Invalid type");
		}
	};
	const char* getError() { return m_error.c_str(); }
};

class ExceptionOva : public ExceptionShp
{
private:
	string m_error;

public:
	ExceptionOva(string error)
		: m_error(error) {}
	const char* getError() { return m_error.c_str(); }
};

class ExceptionTri : public ExceptionShp
{
private:
	string m_error;

public:
	ExceptionTri(string error)
		: m_error(error) {}
	const char* getError() { return m_error.c_str(); }
};

class ExceptionRec : public ExceptionShp
{
private:
	string m_error;
public:
	ExceptionRec(string error)
		: m_error(error){}
	const char* getError() { return m_error.c_str(); }
};
//------------------------------------------------Exception - end
//------------------------------------------------Shape - Classes
class myShape
{
protected:
	float pos_x, pos_y;
	string result;
public:
	string type = "Shape ";
	float area = 0;
	myShape(float x=0, float y=0) :
		pos_x(250 + x),
		pos_y(250 - y)
	{
		if (DebugMode) cout << endl << "myShape constructor called" << endl;
	}
	~myShape()
	{
		if (DebugMode) cout << endl << "myShape DEconstructor called" << endl;
	}
	void toString();
	virtual void Area();
	virtual Shape* Draw();
	void Move();
};

class Oval : public myShape
{
public:
	float lgt_a, lgt_b;
	Oval(float a=1, float b=1, float x=0, float y=0) :
		myShape(x, y),
		lgt_a(a),
		lgt_b(b)
	{
		if (DebugMode) cout << endl << "Oval constructor called" << endl;
		type = "Oval ";
		if (lgt_a < 0.f || lgt_b < 0)
		{
			throw ExceptionOva("Negative radius");
		}
	}
	~Oval()
	{
		if (DebugMode) cout << endl << "Oval DEconstructor called" << endl;
	}
	virtual void Area();
	virtual Shape* Draw();

};

class Circle : public Oval
{
public:
	Circle(float r=1, float x=0, float y=0) :
		Oval(r, r, x, y)
	{
		if (DebugMode) cout << endl << "Circle constructor called" << endl;
		type = "Circle ";
	}
	~Circle()
	{
		if (DebugMode) cout << endl << "Circle DEconstructor called" << endl;
	}
};

class Triangle : public myShape
{
private:
	float lgt_a, lgt_b, lgt_c;
public:
	float ax, ay, bx, by, cx, cy;
	Triangle(float ax=0, float ay=0, float bx=10, float by=0, float cx=10, float cy=10) :
		myShape((min(min(ax, bx), cx)), ((min(min(ay, by), cy)))),
		ax(ax),
		ay(-ay),
		bx(bx),
		by(-by),
		cx(cx),
		cy(-cy)
	{
		if (DebugMode) cout << endl << "Triangle constructor called" << endl;
		type = "Triangle ";
		lgt_a = sqrt((pow(by - ay, 2) + pow(bx - ax, 2)));
		lgt_b = sqrt((pow(cy - by, 2) + pow(cx - bx, 2)));
		lgt_c = sqrt((pow(cy - ay, 2) + pow(cx - ax, 2)));
		if (lgt_a+lgt_b <= lgt_c || lgt_c + lgt_b <= lgt_a || lgt_a + lgt_c <= lgt_b)
		{
			throw ExceptionTri("The sum of the two sides is greater than the third");
		}
	}
	~Triangle()
	{
		if (DebugMode) cout << endl << "Triangle DEconstructor called" << endl;
	}
	virtual void Area();
	virtual Shape* Draw();
};

class Rectangle : public myShape
{
public:
	float lgt_a, lgt_b;
	Rectangle(float a=1, float b=1, float x=0, float y=0) :
		myShape(x, y),
		lgt_a(a),
		lgt_b(b)
	{
		if (DebugMode) cout << endl << "Rectangle constructor called" << endl;
		type = "Rectangle ";
		if (lgt_a < 0.f || lgt_b < 0)
		{
			throw ExceptionRec("Negative lgt");
		}
	}
	~Rectangle()
	{
		if (DebugMode) cout << endl << "Rectangle DEconstructor called" << endl;
	}
	virtual void Area();
	virtual Shape* Draw();
};

class Square : public Rectangle
{
public:
	Square(float a=1, float x=0, float y=0) :
		Rectangle(a, a, x, y)
	{
		if (DebugMode) cout << endl << "Square constructor called" << endl;
	}
	~Square()
	{
		if (DebugMode) cout << endl << "Square DEconstructor called" << endl;
	}
};
//------------------------------------------------Shape - Classes - end
//------------------------------------------------Shape - Func - Draw
Shape* myShape::Draw()
{
	return NULL;
}

Shape* Oval::Draw()
{
	Shape* rec = new CircleShape(1.f);
	rec->setFillColor(Color(93, 205, 171, 220));
	rec->setScale(lgt_a, lgt_b);
	rec->setPosition((pos_x - lgt_a), (pos_y - lgt_b));
	return rec;
}

Shape* Triangle::Draw()
{
	ConvexShape tri;
	tri.setPointCount(3);
	tri.setPoint(0, Vector2f(ax, ay));
	tri.setPoint(1, Vector2f(bx, by));
	tri.setPoint(2, Vector2f(cx, cy));
	tri.setFillColor(Color(250, 17, 95, 220));
	tri.move((pos_x - (min(min(ax, bx), cx))), (pos_y - (max(max(ay, by), cy))));
	Shape* rec = new ConvexShape();
	*rec = tri;
	return rec;
}

Shape* Rectangle::Draw()
{
	Shape* rec = new RectangleShape(Vector2f(1.f, 1.f));
	rec->setFillColor(Color(121, 160, 193, 220));
	rec->setScale(lgt_a, lgt_b);
	rec->setPosition((pos_x - lgt_a / 2.f), (pos_y - lgt_b / 2.f));
	return rec;
}
//------------------------------------------------Shape - Func - Draw - end
//------------------------------------------------Shape - Func - Area
void myShape::Area()
{

}

void Oval::Area()
{
	area = 3.1415926535 * lgt_a * lgt_b;
	cout << "Area = " << area << endl;
}

void Triangle::Area()
{
	area = 0.5f * abs(((ax - cx) * (by - cy)) - ((bx - cx) * (ay - cy)));
	cout << "Area = " << area << endl;
}

void Rectangle::Area()
{
	area = lgt_a * lgt_b;
	cout << "Area = " << area << endl;
}
//------------------------------------------------Shape - Func - Area - end
//------------------------------------------------Shape - Func - Another
void myShape::Move()
{
	float temp;
	cout << "Enter Move Direction (float x,float y): ";
	cin >> temp;
	pos_x += temp;
	cin >> temp;
	pos_y += temp;
	cout << endl << "New position (float x,float y): (" << pos_x - 250 << ";" << -pos_y + 250 << ")\n";
}

void myShape::toString()
{
	result += "type: ";
	result += type;
	result += " pos_x: ";
	result += to_string(pos_x - 250);
	result += " pos_y: ";
	result += to_string(-pos_y + 250);
	cout << result << endl;
}
//------------------------------------------------Shape - Func - Another -end
//------------------------------------------------Cylinder
class myCylinder
{
protected:
	float h = 0, volume = 0;
	myShape* shp;
public:
	myCylinder(float h, myShape*shp) :
		h(h),
		shp(shp)
	{
		if (DebugMode) cout << endl << "myCylinder constructor called" << endl;
	}

	~myCylinder()
	{
		if (DebugMode) cout << endl << "myCylinder deconstructor called" << endl;
	}
	void Info();
	void Volume();
};

void myCylinder::Info()
{
	cout << "Base of Cylindre type: " << shp->type << endl;
	Volume();
	cout << "Volume of Cylindre = " << volume << endl;
}

void myCylinder::Volume()
{
	volume = shp->area * h;
}

//------------------------------------------------Cylinder - end
class Application
{
public:
	void Start();
	void Stop();
};

void Application::Start()
{
	float a=10, b=10, c=10, d=10;
	char f='f';

	ExceptionShp* exep = new ExceptionShp("");

	myShape* rec;
	try
	{
		try
		{
			exep->typeCheck(a);
			exep->typeCheck(b);
			exep->typeCheck(c);
			exep->typeCheck(d);
		}
		catch (ExceptionShp &exception)
		{
			throw ExceptionRec(exception.getError());
		}
		rec = new Rectangle(a, b, c, d);
	}
	catch (ExceptionRec &exception)
	{
		cout << "Constructor error: (" << exception.getError() << ")\nStart default constructor\n";
		rec = new Rectangle();
	}
	rec->Area();
	rec->toString();

	Vertex line_without_thickness1[] =
	{
		Vertex(Vector2f(50.f, 250.f)),
		Vertex(Vector2f(450.f, 250.f))
	};
	line_without_thickness1->color = Color::Black;

	Vertex line_without_thickness2[] =
	{
		Vertex(Vector2f(250.f, 50.f)),
		Vertex(Vector2f(250.f, 450.f))
	};
	line_without_thickness2->color = Color::Black;

	RenderWindow window(VideoMode(800, 450), "Woohoo! Watch!");
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color(92, 250, 242, 0));

		window.draw(line_without_thickness1, 2, Lines);
		window.draw(line_without_thickness2, 2, Lines);
		window.draw(*rec->Draw());

		window.display();
	}
}

void Application::Stop()
{

}

int main()
{
	Application app;
	app.Start();
	app.Stop();
	return 0;
}
