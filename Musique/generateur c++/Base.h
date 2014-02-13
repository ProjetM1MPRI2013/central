/*
 * Base.h
 *
 *  Created on: 13 févr. 2014
 *      Author: riesner
 */

#ifndef BASE_H_
#define BASE_H_
#include <vector>
#include <string>

class Base {
public:
	std::string m_dominante;
	std::vector<std::string> tabAccord;


	Base(std::string i_m_dominante, std::vector<std::string> tabAccord);

	virtual ~Base();
};

#endif /* BASE_H_ */
