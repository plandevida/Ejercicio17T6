//
//  main.cpp
//  Ejercicio17T6
//
//  Created by Dani on 27/03/13.
//  Copyright (c) 2013 Dani. All rights reserved.
//

#include <iostream>
#include "Lista.h"
#include "Pila.h"

using namespace std;

Lista<char> codificacion(Lista<char> &lista);
Lista<char> decodificacion(Lista<char> &lista);

int main(int argc, const char * argv[]) {
    
    Lista<char> cadena;
    char cadenaCaracteres[] = "Bond, James Bond";
    
    for (int i = 0; i < strlen(cadenaCaracteres); i++) {
        cadena.ponDr(cadenaCaracteres[i]);
    }
    
    Lista<char>::Iterador itCadena = cadena.principio();
    while (itCadena != cadena.final()) {
        cout << itCadena.elem();
        itCadena.avanza();
    }
    cout << endl;
    
    Lista<char> cadenaCodificada = codificacion(cadena);
    
    Lista<char>::Iterador itCadenaCod = cadenaCodificada.principio();
    while (itCadenaCod != cadenaCodificada.final()) {
        cout << itCadenaCod.elem();
        itCadenaCod.avanza();
    }
    cout << endl;
    
    Lista<char> cadenaDescodificada = decodificacion(cadenaCodificada);
    
    Lista<char>::Iterador itCadenaDec = cadenaDescodificada.principio();
    while (itCadenaDec != cadenaDescodificada.final()) {
        cout << itCadenaDec.elem();
        itCadenaDec.avanza();
    }
    
    return 0;
}

Lista<char> codificacion(Lista<char> &lista) {
    
    Lista<char> auxLista;
    Pila<char> pilaConsonantes;
    
    /*
     * Primer pasdo de la codificación
     */
    Lista<char>::Iterador itLista = lista.principio();
    while (itLista != lista.final()) {
        
        char elem = itLista.elem();
        
        if (elem != 'a' && elem != 'e' && elem != 'i' && elem != 'o' && elem != 'u') {
            pilaConsonantes.apila(elem);
        }
        else {
            while ( !pilaConsonantes.esVacia() ) {
                auxLista.ponDr(pilaConsonantes.cima());
                pilaConsonantes.desapila();
            }
            
            auxLista.ponDr(elem);
        }
        
        itLista.avanza();
    }
    
    while ( !pilaConsonantes.esVacia()) {
        auxLista.ponDr(pilaConsonantes.cima());
        pilaConsonantes.desapila();
    }
    
    /*
     * Segundo paso de la codificación
     */
    Lista<char> cadenaCod;
    
    while ( !auxLista.esVacia() ) {
        // Cogemos el primero
        cadenaCod.ponDr(auxLista.primero());
        // Lo eliminamos
        auxLista.resto();
        
        // Cogemos el último
        cadenaCod.ponDr(auxLista.ultimo());
        // Lo elimimamos
        auxLista.inicio();
    }
    
    return cadenaCod;
}

Lista<char> decodificacion(Lista<char> &lista) {
    Lista<char> cadenaDec;
    Lista<char> auxLista;
    
    /*
     * Primer paso de la decodificación
     */
    Lista<char>::Iterador it = lista.principio();
    while ( it != lista.final() ) {
        
        auxLista.ponDr(it.elem());
        
        it = lista.borra(it);
        
        try {
            it.avanza();
        } catch (EAccesoInvalido e) {
            cout << e.msg() << endl;
            it = lista.principio();
        }
    }
    
    while ( !lista.esVacia()) {
        auxLista.ponDr(lista.ultimo());
        lista.inicio();
    }
    
    /*
     * Primer paso de la codificación realiza el efecto inverso
     * en una cadena ya codificada.
     */
    
    Pila<char> pilaConsonantes;
    
    Lista<char>::Iterador itLista = auxLista.principio();
    while (itLista != auxLista.final()) {
        
        char elem = itLista.elem();
        
        if (elem != 'a' && elem != 'e' && elem != 'i' && elem != 'o' && elem != 'u') {
            pilaConsonantes.apila(elem);
        }
        else {
            while ( !pilaConsonantes.esVacia() ) {
                cadenaDec.ponDr(pilaConsonantes.cima());
                pilaConsonantes.desapila();
            }
            
            cadenaDec.ponDr(elem);
        }
        
        itLista.avanza();
    }
    
    while ( !pilaConsonantes.esVacia()) {
        cadenaDec.ponDr(pilaConsonantes.cima());
        pilaConsonantes.desapila();
    }
    
    return cadenaDec;
}

