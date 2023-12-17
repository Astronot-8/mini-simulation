#include <vector>
#include <random>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "ParticleClass.h"

int main()
{
    setlocale(LC_ALL, "russian");

    sf::RenderWindow window(sf::VideoMode(800, 600), "Fire Simulation");
    std::vector<Particle> particles;

    sf::Clock clock;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disPos(0, 800);  // ��� �������
    std::uniform_real_distribution<> disRadius(5.0, 15.0);    // ��� �������
    std::uniform_real_distribution<> disMass(0.5, 2.0);       // ��� �����
    std::uniform_int_distribution<> disColor(0, 255);         // ��� �����

    int countParticles;

    std::cout << "����� ��������� ������ ��� ��������� ������ � ��� ��� ���:\n" << "Upd �� ������ ������, � �� ����� ����, ��� ��� ��������� ������" << std::endl;

    std::cin >> countParticles;

    if (countParticles >= 500)
    {
        std::cout << "���� ����� ����� �� ��";
    }

    // �������� ��������� ������
    for (int i = 0; i < countParticles; ++i) {
        float x = disPos(gen);
        float y = disPos(gen);
        float radius = disRadius(gen);
        float mass = disMass(gen);
        sf::Color color(disColor(gen), disColor(gen), disColor(gen));

        particles.emplace_back(x, y, radius, mass, color);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);

        for (auto& particle : particles) 
        {
            particle.RepelFromMouse(mousePos, 100);
            particle.Update(deltaTime * 10.0f, particles);
        }

        window.clear();

        for (const auto& particle : particles)
        {
            particle.Render(window);
            //particle.DrawVelocityVector(window); //������ ����� ������� ����������� ������ ��������� ��� �����
        }

        window.display();
    }

    return 0;
}
