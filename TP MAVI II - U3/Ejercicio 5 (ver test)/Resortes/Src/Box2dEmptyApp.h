#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Ragdoll
{
public:
    Ragdoll(b2World* world, sf::RenderWindow* window, float x, float y);

    // Método para actualizar la posición del sprite basada en la posición del cuerpo físico
    void ActualizarPosiciones();

    // Método para dibujar el sprite en la ventana de renderizado
    void Dibujar();

private:
    b2Body* CreateBodyPart(b2World* world, float x, float y, float width, float height);
    void CreateSpringJoint(b2World* world, b2Body* bodyA, b2Body* bodyB, b2Vec2 localAnchorA, b2Vec2 localAnchorB, float lowerAngle, float upperAngle);

    sf::RenderWindow* wnd; // Ventana de renderizado
    sf::Texture texture;   // Textura del ragdoll
    sf::Sprite sprite;     // Sprite del ragdoll
    b2Body* _body;         // Cuerpo principal del ragdoll
};

