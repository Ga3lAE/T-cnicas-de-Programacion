/* 
 * File:   NodoCurso.h
 * Author: arias
 *
 * Created on 5 de julio de 2025, 05:01 PM
 */

#ifndef NODOCURSO_H
#define NODOCURSO_H

#include "Curso.h"

struct NodoCurso{
    struct Curso curso;
    struct NodoCurso *siguiente;
};

#endif /* NODOCURSO_H */

