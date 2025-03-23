#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

bool pesoCorrecto(float peso) {
    return peso <= 75.0f;
}

int main() {

    // Pedir el peso
    float peso;
    std::cout << "Por favor, ingresa tu peso (kg): ";
    std::cin >> peso;

    // Si el peso es correcto, solo mostrar mensaje
    if (pesoCorrecto(peso)) {
        std::cout << "Peso correcto." << std::endl;
        return 0; // El programa termina
    }

    // Configuración de la ventana SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ventana Bloqueada");

    // Cargar la música de fondo
    sf::Music music;
    if (!music.openFromFile("music.ogg")) { // Aquí debes poner la ruta de tu archivo de música
        std::cerr << "No se pudo cargar la música!" << std::endl;
        return -1;
    }
    music.setLoop(true);
    music.play();

    // Cargar la imagen que se moverá
    sf::Texture texture;
    if (!texture.loadFromFile("img.jpg")) { // Aquí debes poner la ruta de tu imagen
        std::cerr << "No se pudo cargar la imagen!" << std::endl;
        return -1;
    }
    sf::Sprite sprite(texture);
    
    // Establecer el origen de la imagen en su centro para rotarla correctamente
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    
    // Coloca la imagen en el centro de la ventana
    sprite.setPosition(400, 300);

    // Variable para la velocidad de rotación
    float velocidadRotacion = 0.1f;

    // Bucle principal de la ventana
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Si el usuario intenta cerrar la ventana, no permitirlo
            if (event.type == sf::Event::Closed) {
                // No hacer nada, para evitar que cierre la ventana
            }
        }

        // Rotar la imagen
        sprite.rotate(velocidadRotacion);  // Esto hará que la imagen gire sobre su propio eje

        // Limpiar la ventana
        window.clear();
        // Dibujar la imagen
        window.draw(sprite);
        // Mostrar todo en la ventana
        window.display();
    }

    return 0;
}
