/*
 * Printer.h
 *
 *  Created on: 23.02.2015
 *      Author: Caspar
 */

#ifndef PRINTER_H_
#define PRINTER_H_

#include <functional>
#include <iostream>

template<class In>
class Printer {
public:
	Printer();
	virtual ~Printer();

	void operator()()
	{
		std::cout << std::to_string(connection()) << "\n";
	}

	std::function<In()> connection;

};

#endif /* PRINTER_H_ */
