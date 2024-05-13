//SANTIAGO EXEQUIEL FERNÁNDEZ - MAVI II, U3 - Ejercicio 2:

#include "Game.h"
#include "Box2DHelper.h"

// Constructor de la clase Game
Game::Game(int ancho, int alto, std::string titulo)
{
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo); // Crea una ventana con las dimensiones y título especificados
	wnd->setVisible(true); // Hace visible la ventana
	fps = 60; // Establece el límite de cuadros por segundo (FPS)
	wnd->setFramerateLimit(fps); // Aplica el límite de FPS a la ventana
	frameTime = 1.0f / fps; // Calcula el tiempo por cuadro en segundos
	SetZoom(); // Configura el "zoom" o vista de la cámara
	InitPhysics(); // Inicializa la simulación de física
	draggedBody = nullptr; // Inicializa draggedBody como nullptr
}

void Game::Loop()
{
	while (wnd->isOpen())
	{
		wnd->clear(clearColor);
		DoEvents();
		CheckCollitions();
		UpdatePhysics();
		HandleDraggedBody();
		DrawGame();
		wnd->display();
	}
}

void Game::UpdatePhysics()
{
	phyWorld->Step(frameTime, 8, 8); // Avanza la simulación de física un paso
	phyWorld->ClearForces(); // Limpia las fuerzas acumuladas
	phyWorld->DebugDraw(); // Dibuja la representación de debug de la simulación
}

void Game::DrawGame()
{
	// Función para dibujar los elementos del juego (a implementar)
}

void Game::DoEvents()
{
	Event evt;
	while (wnd->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			wnd->close();
			break;
		case Event::MouseButtonPressed:
			if (evt.mouseButton.button == Mouse::Left)
			{
				Vector2f clickPos = wnd->mapPixelToCoords(Vector2i(evt.mouseButton.x, evt.mouseButton.y));
				b2Vec2 b2ClickPos(clickPos.x, clickPos.y);

				for (b2Body* b = phyWorld->GetBodyList(); b; b = b->GetNext())
				{
					if (b->GetType() == b2_dynamicBody && b->GetFixtureList() && b->GetFixtureList()->TestPoint(b2ClickPos))
					{
						draggedBody = b;
						clickOffset = b->GetPosition() - b2ClickPos;
						return;
					}
				}
			}
			break;
		case Event::MouseButtonReleased:
			if (evt.mouseButton.button == Mouse::Left)
			{
				draggedBody = nullptr;
			}
			break;
		}
	}
}


void Game::CheckCollitions()
{
	// Verificación de colisiones (a implementar)
}

void Game::SetZoom()
{
	View camara;
	camara.setSize(100.0f, 100.0f); // Establece el tamaño de la vista
	camara.setCenter(50.0f, 50.0f); // Centra la vista en un punto del mundo
	wnd->setView(camara); // Aplica la vista a la ventana
}

void Game::HandleDraggedBody()
{
	if (draggedBody)
	{
		Vector2f mousePos = wnd->mapPixelToCoords(Mouse::getPosition(*wnd));
		b2Vec2 b2MousePos(mousePos.x, mousePos.y);
		draggedBody->SetTransform(b2MousePos + clickOffset, draggedBody->GetAngle());
	}
}

void Game::InitPhysics()
{
	// Inicializa el mundo de Box2D con una gravedad hacia abajo
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	debugRender = new SFMLRenderer(wnd); // Crea un renderizador de debug para SFML
	debugRender->SetFlags(UINT_MAX); // Configura el renderizador para dibujar todas las formas de debug
	phyWorld->SetDebugDraw(debugRender); // Establece el renderizador de debug para el mundo de Box2D

	// Crea cuerpos estáticos para simular el suelo y las paredes
	// También crea cuerpos dinámicos (como círculos) y los une con resortes al techo para demostrar la simulación física
	b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

	b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

	b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

	b2Body* topWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	topWallBody->SetTransform(b2Vec2(50.0f, 0.0f), 0.0f);


	// Creamos el Círculo Derecho.
	b2Body* circuloDer = Box2DHelper::CreateCircularDynamicBody(phyWorld, 5, 1.0f, 0.5, 0.1f);
	circuloDer->SetTransform(b2Vec2(45.0f, 10.0f), 0.0f);

	// Creamos el Círculo Izquierdo.
	b2Body* circuloIzq = Box2DHelper::CreateCircularDynamicBody(phyWorld, 5, 1.0f, 0.5, 0.1f);
	circuloIzq->SetTransform(b2Vec2(55.0f, 10.0f), 0.0f);

	// Atamos ambos círculos con el resorte.
	Box2DHelper::CreateDistanceJoint(phyWorld, circuloDer, circuloDer->GetWorldCenter(),
		circuloIzq, circuloIzq->GetWorldCenter() + b2Vec2(0.0f, 0.0f), 1.0f, 0.1f, 1.0f);
}

Game::~Game(void)
{
	// Destructor de la clase Game (a implementar si es necesario)
}