//SANTIAGO EXEQUIEL FERNÁNDEZ - MAVI II, U3 - Ejercicio 5:

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
}

void Game::Loop()
{
	while (wnd->isOpen()) // Bucle principal del juego que se ejecuta mientras la ventana esté abierta
	{
		wnd->clear(clearColor); // Limpia la ventana con el color de fondo
		DoEvents(); // Maneja los eventos (input del usuario)
		CheckCollitions(); // Verifica colisiones (a implementar)
		UpdatePhysics(); // Actualiza la simulación de física
		DrawGame(); // Dibuja los elementos del juego
		wnd->display(); // Muestra los cambios en la ventana
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
	while (wnd->pollEvent(evt)) // Procesa todos los eventos acumulados
	{
		switch (evt.type)
		{
		case Event::Closed: // Si se solicita cerrar la ventana
			wnd->close(); // Cierra la ventana
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

void Game::InitPhysics()
{
	// Inicializa el mundo de Box2D con una gravedad hacia abajo
	phyWorld = new b2World(b2Vec2(0.0f, 80.0f));

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


	// CABEZA:
	b2Body* cabeza = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 6, 8, 1.0f, 0.5, 0.1f);
	cabeza->SetTransform(b2Vec2(50.0f, 54.0f), 0.0f);

	// TORSO:
	b2Body* torso = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 8, 16, 1.0f, 0.5, 0.1f);
	torso->SetTransform(b2Vec2(50.0f, 67.0f), 0.0f);

	// BRAZO IZQUIERDO:
	b2Body* brazoIzq = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 4, 18, 1.0f, 0.5, 0.1f);
	brazoIzq->SetTransform(b2Vec2(57.0f, 68.0f), 0.0f);

	// BRAZO DERECHO:
	b2Body* brazoDer = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 4, 18, 1.0f, 0.5, 0.1f);
	brazoDer->SetTransform(b2Vec2(43.0f, 68.0f), 0.0f);

	// PIERNA IZQUIERDA:
	b2Body* piernaIzq = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 4, 18, 1.0f, 0.5, 0.1f);
	piernaIzq->SetTransform(b2Vec2(47.0f, 86.0f), 0.0f);

	// PIERNA DERECHA:
	b2Body* piernaDer = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 4, 18, 1.0f, 0.5, 0.1f);
	piernaDer->SetTransform(b2Vec2(53.0f, 86.0f), 0.0f);

	// ------------------------------------------------------------------------------------------------

	// RESORTES:
	Box2DHelper::CreateDistanceJoint(phyWorld, cabeza, cabeza->GetWorldCenter(),
		torso, torso->GetWorldCenter() + b2Vec2(0.0f, -5.0f), 0.0f, 0.5f, 0.5f);

	Box2DHelper::CreateDistanceJoint(phyWorld, brazoIzq, brazoIzq->GetWorldCenter(),
		torso, torso->GetWorldCenter() + b2Vec2(0.0f, 0.0f), 0.0f, 0.5f, 0.5f);

	Box2DHelper::CreateDistanceJoint(phyWorld, brazoDer, brazoDer->GetWorldCenter(),
		torso, torso->GetWorldCenter() + b2Vec2(0.0f, -10.0f), 0.0f, 0.5f, 0.5f);

	Box2DHelper::CreateDistanceJoint(phyWorld, piernaIzq, piernaIzq->GetWorldCenter(),
		torso, torso->GetWorldCenter() + b2Vec2(-2.0f, 0.0f), 0.0f, 0.1f, 0.0f);

	Box2DHelper::CreateDistanceJoint(phyWorld, piernaDer, piernaDer->GetWorldCenter(),
		torso, torso->GetWorldCenter() + b2Vec2(2.0f, 0.0f), 0.0f, 0.1f, 0.0f);

}

Game::~Game(void)
{
	// Destructor de la clase Game (a implementar si es necesario)
}