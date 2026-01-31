#ifndef WORD_HPP
#define WORD_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Word {
public:
    // Constructeur complet
    Word(sf::Font& font, std::string content, int size, sf::Vector2f pos, sf::Color color) {
        text.setFont(font);
        text.setString(content);
        text.setCharacterSize(size);
        text.setPosition(pos);
        text.setFillColor(color);
    }

    // Pour changer le texte dynamiquement (ex: mettre à jour le score)
    void setContent(std::string newContent) {
        text.setString(newContent);
    }

    void setPosition(float x, float y) {
        text.setPosition(x, y);
    }

    void setColor(sf::Color color) {
        text.setFillColor(color);
    }

    // Méthode de dessin
    void draw(sf::RenderWindow& window) {
        window.draw(text);
    }

private:
    sf::Text text;
};

#endif