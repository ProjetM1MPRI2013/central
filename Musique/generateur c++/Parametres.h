/*
 * Parametres.h
 *
 *  Created on: 24 janv. 2014
 *      Author: riesner
 */

#ifndef PARAMETRES_H_
#define PARAMETRES_H_


// future coloration harmonique de la mélodie
class Parametres {
public:
	int m_harmonie;
	Parametres(int harmonie);
	Parametres();
	virtual ~Parametres();
};

#endif /* PARAMETRES_H_ */
