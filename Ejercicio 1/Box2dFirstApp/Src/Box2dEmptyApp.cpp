//SANTIAGO EXEQUIEL FERN�NDEZ - MAVI II, U3 - Ejercicio 1:

#include "Game.h"
#include <tchar.h>

using namespace sf;

class Pelota
{
private:

    Sprite* _sprite;
    Texture* _image;
    RenderWindow* wnd;

    b2Body* _body;

public:
 
    Pelota(b2World* _world, RenderWindow* _wnd)
    {
        // Definimos el cuerpo f�sico y lo creamos
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(100.0f, 0.0f);
        _body = _world->CreateBody(&bodyDef);

        // Creamos su figura de colisi�n (en este caso, una caja cuadrada)
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(20.0f, 20.0f);

        // Creamos el fixture, le asignamos la figura de colisi�n y lo agregamos al cuerpo
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 10.0f;
        fixtureDef.friction = 5.0f;
        fixtureDef.restitution = 4.0f;
        _body->CreateFixture(&fixtureDef);
    }

    // M�todo que actualiza la posici�n del sprite seg�n la posici�n del cuerpo f�sico
    void ActualizarPosiciones()
    {
        b2Vec2 pos = _body->GetPosition();
        _sprite->setPosition(pos.x, pos.y);
    }

    // M�todo que dibuja el sprite en la ventana
    void Dibujar()
    {
        wnd->draw(*_sprite);
    }
};

// Funci�n principal del programa
int _tmain(int argc, _TCHAR* argv[])
{
    // Crear el objeto de la clase Game
    Game* Juego;
    Juego = new Game(800, 600, "MAVII II, U3 - Ejercicio 1");
    Juego->Loop(); // Ejecutar el bucle principal del juego

    return 0; // Retorna 0 indicando que el programa se ha ejecutado correctamente
}
