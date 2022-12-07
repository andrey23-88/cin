#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define WIDTH 27
#define delimeter "\n--------------------------------------------\n"

class Fraction;
Fraction operator * (Fraction left, Fraction right);
Fraction operator / (const Fraction& left, const Fraction& right);

class Fraction
{
	int integer;
	int numerator;
	int denominator;
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	//               Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout.width(WIDTH);
		cout <<std::left<< "DefaultConstructor:" << this << endl;
	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout.width(WIDTH);
		cout <<std::left<< "SingleArgumentConstructor:" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout.width(WIDTH);
		cout <<std::left<< "Constructor:" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
		cout.width(WIDTH);
		cout <<std::left<< "Constructor:" << this << endl;

	}
	~Fraction()
	{
		cout.width(WIDTH);
		cout <<std::left<< "Destructor:" << this << endl;
	}

	//                   Operators:

	Fraction& operator()(int integer, int numerator, int denominator)
	{
		set_integer(integer);
		set_numerator(numerator);
		set_denominator(denominator);
		return *this;
	}

	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout.width(WIDTH);
		cout << std::left << "CopyAssignment:" << this << endl;
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}
	//                Increment/Decrement
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}
	//               Type-cast operators:
	explicit operator int()const                  //explicit - €вный
	{
		return integer;
	}
	explicit operator double()const
	{
		return integer + (double)numerator / denominator;
	}
	//                   Methods:
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		std::swap(inverted.numerator, inverted.denominator);
		return inverted;
	}
	Fraction& reduce()
	{
		int more, less, rest;
		if (numerator > denominator)
		{
			more = numerator;
			less = denominator;
		}
		else
		{
			less = numerator;
			more = denominator;
		}
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; //GCD-Greatest Common Divisor
		numerator /= GCD;
		denominator /= GCD;
		return *this;
		
	}

	void print()const
	{
		if (integer)cout << integer << " ";
		if (numerator)
		{
			cout << numerator << "/" << denominator;
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	/*Fraction res;
	res.set_numerator(left.get_numerator() * right.get_numerator());
	res.set_denominator(left.get_denominator() * right.get_denominator());
	res.to_proper();*/
	/*Fraction res
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	);
	res.to_proper();
	return res;*/
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator/(const Fraction& left, const Fraction& right)
	{
		/*left.to_improper();
		right.to_improper();
		return Fraction
		(
			left.get_numerator() * right.get_denominator(),
			right.get_numerator() * left.get_denominator()
		).to_proper();*/
	return left * right.inverted();
	}

std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer() << " ";
	if (obj.get_numerator())
	{
		os << obj.get_numerator() << "/" << obj.get_denominator();
	}
	else if(obj.get_integer()==0)os << 0;
	return os;
}

std::istream& operator>>(std::istream& is, Fraction& obj)
{
	
	//int integer, numerator, denominator;
	//is >> integer >> numerator >> denominator;
	/*obj.set_integer(integer);
	obj.set_numerator(numerator);
	obj.set_denominator(denominator);*/
	//obj(integer, numerator, denominator);

	int number[3] = {};    //в этом массиве будут хранитьс€ числовые значени€, полученные из строки.

	const int SIZE = 256;
	char buffer[SIZE] = {};
	char delimeters[] = " /()";
	//is >> buffer;      //cin сохран€ет данные в переменной до пробела
	//ƒл€ того чтобы ввести строку с пробелами нужно использовать cin.getline()
	is.getline(buffer, SIZE);
	int n = 0;   //—четчик полученных чисел
	//‘ункци€ strtok() делит строку на подстроки, использу€ разделители, каждый разделитель замен€етс€ нулем
	for (char* pch = strtok(buffer, delimeters); pch; pch = strtok(NULL, delimeters))
	{
		number[n++] = std::atoi(pch); // ‘ункци€ atoi()- ASCII string to Integer принимает строку, 
		//и если строка €вл€етс€ чмслом, то возвращает интовый эквивалент этого числа
	}
	//cout<<buffer<<endl;
	//for (int i = 0; i < n; i++)cout << number[i] << "\t";
	obj = Fraction();
	switch (n)
	{
	case 1: obj.set_integer(number[0]); break;
	case 2:
		obj.set_numerator(number[0]);
		obj.set_integer(number[1]);
		break;
	case 3:
		obj.set_integer(number[0]);
		obj.set_numerator(number[1]);
		obj.set_denominator(number[2]);
	}
	cout << endl;
	return is;

}

//#define CONSTRUCTORS_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define INCREMENT_CHECK
//#define ISTREAM_OPERATOR_CHECK
//#define CONVERSION_FROM_OTHER_TO_CLASS

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	Fraction A;   //Default constructor
	A.print();

	Fraction B = 5;
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();

	D.to_improper();
	D.print();

	D.to_proper();
	D.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ARITHMETICAL_OPERATORS_CHECK
	Fraction A(2, 3, 4);
	Fraction B(3, 4, 5);
	Fraction C = A / B;
	C.print();

	A *= B;
	A.print();

	A /= B;
	A.print();
#endif // ARITHMETICAL_OPERATORS_CHECK


#ifdef INCREMENT_CHECK
	for (double i = .0325; i < 10; i++)cout << i << "\t"; cout << endl;
	for (Fraction i(1, 2); i.get_integer() < 10; ++i)
	{
		i.print();
	}
#endif // INCREMENT_CHECK

#ifdef ISTREAM_OPERATOR_CHECK
	/*Fraction A(2, 3, 4);
cout << A << endl;*/

	Fraction A(50, 75, 80);
	cout << "¬ведите простую дробь: ";
	cin >> A;
	cout << delimeter << endl;
	cout << A << endl;
	cout << delimeter << endl;
#endif // ISTREAM_OPERATOR_CHECK

#ifdef CONVERSION_FROM_OTHER_TO_CLASS
	int a = 2;       //No conversions
	Fraction A = 5;   // Conversion from 'int' to 'Fraction'
					  //Single-argument constructor
	cout << A << endl;
	cout << delimeter << endl;

	Fraction B;
	B = 8;          //Conversion from 'int' to 'Fraction'
					 //Assignment operator
	cout << B << endl;
#endif // CONVERSION_FROM_OTHER_TO_CLASS

	Fraction A(2, 3, 4);
	cout << A << endl;

	int a = (int)A;
	cout << a << endl;

	double b = (double)A;
	cout << b << endl;
}
