#include <iostream>

// const objects can call non const member functions

// struct Date
// {
//     int year {};
//     int month {};
//     int day {};

//     void print()
//     {
//         std::cout << year << '/' << month << '/' << day;
//     }
// };

// int main()
// {
//     const Date today { 2020, 10, 14 }; // const

//     today.print();  // compile error: const objects can't call non-const member function
//     // if you need it to compile, then void print() const

//     return 0;
// }

// return by value can be expensive

// #include <iostream>
// #include <string>

// class Employee
// {
// 	std::string m_name{};

// public:
// 	void setName(std::string_view name) { m_name = name; }
// 	std::string getName() const { return m_name; } //  getter returns by value
// };

// int main()
// {
// 	Employee joe{};
// 	joe.setName("Joe");
// 	std::cout << joe.getName();

// 	return 0;
// }

// what you can rather do is to return a const lvalue

#include <iostream>
#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const std::string& getName() const { return m_name; } //  getter returns by value
};

int main()
{
	Employee joe{};
	joe.setName("Joe");
	std::cout << joe.getName();

	return 0;
}