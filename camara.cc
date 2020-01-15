#include "camara.h"

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, TipoCamara tipo, float left, float right, float bottom, float top, float near, float far){
    this->eye = eye;
    this->at = at;
    this-> up = up;
    this->tipo = tipo;
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->near = near;
    this->far = far;
}

void Camara::giroYOrbital(float anguloX){
   Tupla3f n, u, v;

	float modulo_u, modulo_v, modulo_n;

	float x, y, z, s;

	n = eye - at;
	modulo_n = sqrt(n(0)*n(0) + n(1)*n(1) + n(2)*n(2));
	n = {n(0)/modulo_n, n(1)/modulo_n, n(2)/modulo_n};

	up = at - up;
	u = up.cross(n);
	modulo_u = sqrt(u(0)*u(0) + u(1)*u(1) + u(2)*u(2));
	u = {u(0)/modulo_u, u(1)/modulo_u, u(2)/modulo_u};

	v = n.cross(u);
	modulo_v = sqrt(v(0)*v(0) + v(1)*v(1) + v(2)*v(2));
	v = {v(0)/modulo_v, v(1)/modulo_v, v(2)/modulo_v};

    s = u.dot(v.cross(n)) ;

	eye = {eye.dot(u), eye.dot(v), eye.dot(n)};
	eye = {(float)cos(anguloX*M_PI/180)*eye(0) - (float)sin(anguloX*M_PI/180)*eye(2), eye(1), (float)sin(anguloX*M_PI/180)*eye(0) + (float)cos(anguloX*M_PI/180)*eye(2)};
    x = eye[0] * u[0] + eye[1] * v[0] + eye[2] * n[0] ;
    y = eye[0] * u[1] + eye[1] * v[1] + eye[2] * n[1] ;
    z = eye[0] * u[2] + eye[1] * v[2] + eye[2] * n[2] ;
	eye = {x/s, y/s, z/s};


	up = {up.dot(u), up.dot(v), up.dot(n)};
	up = {(float)cos(anguloX*M_PI/180)*up(0) - (float)sin(anguloX*M_PI/180)*up(2), up(1), (float)sin(anguloX*M_PI/180)*up(0) + (float)cos(anguloX*M_PI/180)*up(2)};
    x = up[0] * u[0] + up[1] * v[0] + up[2] * n[0] ;
    y = up[0] * u[1] + up[1] * v[1] + up[2] * n[1] ;
    z = up[0] * u[2] + up[1] * v[2] + up[2] * n[2] ;
	float up_normal = sqrt(x*x + y*y + z*z);
	up = {x/s/up_normal, y/s/up_normal, z/up_normal};
}

void Camara::giroYFirstPerson(float angle){
}

void Camara::zoom(float factor){
    this->left *= factor;
    this->right *= factor;
    this->bottom *= factor;
    this->top *= factor;
}

void Camara::setObserver(){
    gluLookAt(eye(0), eye(1), eye(2),at(0), at(1), at(2), up(0), up(1), up(2));
}

void Camara::setProyeccion(){
    if(tipo == PERSPECTIVA)
        glFrustum(left, right, bottom, top, near, far);
    else if(tipo == ORTOGRAFICA)
        glOrtho(left, right, bottom, top, near, far);
}

void Camara::setAt(Tupla3f at){
    this->at = at;
}

void Camara::setEye(Tupla3f eye){
    this->eye = eye;
}



/*
    Tupla3f u = (eye - at);
    u = u.cross(up);
    u.normalized();

    float x, y, z;

    x = at[0] * (cos(angle) + u[0]*u[0] * (1-cos(angle))) + at[1] * (u[1]*u[0]*(1-cos(angle)) + u[2] * sin(angle)) + at[2] * (u[2]*u[0] * (1-cos(angle)) - u[1] * sin(angle));
    y = at[0] * (u[0]*u[1]*(1-cos(angle)) - u[2] * sin(angle)) + at[1] * (cos(angle) + u[1]*u[1]*(1-cos(angle))) + at[2] * (u[2]*u[1]*(1-cos(angle)) + u[0]*sin(angle));
    z = at[0] * (u[2]*u[0]*(1-cos(angle)) - u[1]*sin(angle)) + at[1] * (u[1]*u[2]*(1-cos(angle)) - u[0]*sin(angle)) + at[2] * (cos(angle) + u[2]*u[2]*(1-cos(angle)));
    
    at = {x,y,z};
*/
