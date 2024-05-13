//SANTIAGO EXEQUIEL FERNÁNDEZ - MAVI II, U3 - Ejercicio 1:

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
        // Definimos el cuerpo físico y lo creamos
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(100.0f, 0.0f);
        _body = _world->CreateBody(&bodyDef);

        // Creamos su figura de colisión (en este caso, una caja cuadrada)
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(20.0f, 20.0f);

        // Creamos el fixture, le asignamos la figura de colisión y lo agregamos al cuerpo
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 10.0f;
        fixtureDef.friction = 5.0f;
        fixtureDef.restitution = 4.0f;
        _body->CreateFixture(&fixtureDef);
    }

    // Método que actualiza la posición del sprite según la posición del cuerpo físico
    void ActualizarPosiciones()
    {
        b2Vec2 pos = _body->GetPosition();
        _sprite->setPosition(pos.x, pos.y);
    }

    // Método que dibuja el sprite en la ventana
    void Dibujar()
    {
        wnd->draw(*_sprite);
    }
};

// Función principal del programa
int _tmain(int argc, _TCHAR* argv[])
{
    // Crear el objeto de la clase Game
    Game* Juego;
    Juego = new Game(800, 600, "MAVII II, U3 - Ejercicio 1");
    Juego->Loop(); // Ejecutar el bucle principal del juego

    return 0; // Retorna 0 indicando que el programa se ha ejecutado correctamente
}
