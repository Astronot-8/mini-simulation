#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "ConstData.h"

class Particle
{
public:
    Particle() = default;
    Particle(float start_pos_x, float start_pos_y, float radius, float mass, const sf::Color& color);
    ~Particle() = default;

public:
    void CollisionParticles(Particle& other);
    void CollisionParticleScreen(float windowWidth, float windowHeight, float bounceFactor);
    void FallingDown(float deltaTime);
    void Update(float deltaTime, std::vector<Particle>& allParticles);
    void Render(sf::RenderWindow& windowRender) const;
    void DrawVelocityVector(sf::RenderWindow& window) const;

public:
    float GetMass() const noexcept;
    float GetRadius() const noexcept;
    sf::Vector2f GetPosition() const noexcept;
    sf::Vector2f GetVelocity() const noexcept;
    sf::Color GetParticleColor() const noexcept;

public:
    void SetMass(float set_mass);
    void SetRadius(float set_radius);
    void SetVelocity(sf::Vector2f set_velocity);
    void SetParticleColor(const sf::Color& set_color);
    void SetPosition(sf::Vector2f set_position);

private:
    float particleMass;
    float particleRadius;

private:
    sf::Vector2f particleVelocity = { 0.0f, 0.0f };
    sf::Vector2f particlePosition;
    sf::CircleShape particleShape;
    sf::Color particleColor;

public:
    void RepelFromMouse(sf::Vector2f mousePosition, float repelStrength);
};