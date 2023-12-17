#include "ParticleClass.h"

Particle::Particle(float start_pos_x, float start_pos_y, float radius, float mass, const sf::Color& color)
    : particleRadius(radius), particleMass(mass), particleColor(color), particlePosition(start_pos_x, start_pos_y)
{
    particleShape.setRadius(radius);
    particleShape.setPosition(start_pos_x, start_pos_y);
    particleShape.setFillColor(color);
    particleShape.setOrigin(radius, radius);
}


void Particle::CollisionParticles(Particle& other)
{
    sf::Vector2f delta = sf::Vector2f(other.GetPosition().x - particlePosition.x, other.GetPosition().y - particlePosition.y);
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (distance < particleRadius + other.GetRadius())
    {
        sf::Vector2f normal = delta / distance;
        sf::Vector2f relativeVelocity = particleVelocity - other.GetVelocity();
        float relativeSpeed = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

        if (relativeSpeed > 0)
        {
            float elasticity = 0.1f;
            float impulse = (2.0f * relativeSpeed) / (particleMass + other.GetMass());
            impulse *= elasticity;

            sf::Vector2f impulsePerMass = impulse * normal;
            particleVelocity -= impulsePerMass * other.GetMass();
            other.SetVelocity(other.GetVelocity() + impulsePerMass * particleMass);
        }

        float overlap = 0.5f * ((particleRadius + other.GetRadius()) - distance);
        sf::Vector2f correction = normal * overlap;
        float totalMass = particleMass + other.GetMass();

        sf::Vector2f temp;
        temp.x = particlePosition.x - correction.x * (other.GetMass() / totalMass);
        temp.y = particlePosition.y - correction.y * (other.GetMass() / totalMass);
        SetPosition(temp);
        temp = { 0, 0 };

        temp.x = other.GetPosition().x + correction.x * (particleMass / totalMass);
        temp.y = other.GetPosition().y + correction.y * (particleMass / totalMass);
        other.SetPosition(temp);
        temp = { 0, 0 };
    }
}

void Particle::CollisionParticleScreen(float windowWidth, float windowHeight, float bounceFactor)
{
    const float velocityThreshold = 0.1f;
    const float epsilon = 0.01f;

    if (particlePosition.x - particleRadius < 0 || particlePosition.x + particleRadius > windowWidth) {
        particleVelocity.x *= -bounceFactor;
        particlePosition.x = std::max(particleRadius, std::min(particlePosition.x, windowWidth - particleRadius));

        if (std::abs(particleVelocity.x) < velocityThreshold + epsilon) {
            particleVelocity.x = 0;
        }
    }

    if (particlePosition.y - particleRadius < 0 || particlePosition.y + particleRadius > windowHeight) {
        particleVelocity.y *= -bounceFactor;
        particlePosition.y = std::max(particleRadius, std::min(particlePosition.y, windowHeight - particleRadius));

        if (std::abs(particleVelocity.y) < velocityThreshold + epsilon) {
            particleVelocity.y = 0;
        }
    }
}

void Particle::FallingDown(float deltaTime)
{
    float gravityAcceleration = PhysicsConstants::GRAVITY;
    float airResistanceCoefficient = 0;

    sf::Vector2f gravityForce(0.0f, gravityAcceleration * particleMass);
    sf::Vector2f airResistanceForce = -airResistanceCoefficient * particleRadius * particleRadius * particleVelocity;

    sf::Vector2f totalForce = gravityForce + airResistanceForce;
    particleVelocity += (totalForce / particleMass) * deltaTime;

    particlePosition.x += particleVelocity.x * deltaTime;
    particlePosition.y += particleVelocity.y * deltaTime;

    particleShape.setPosition(particlePosition.x, particlePosition.y);
}

void Particle::Update(float deltaTime, std::vector<Particle>& allParticles)
{
    // ќбработка движени€ частицы под воздействием силы т€жести и сопротивлени€ воздуха
    FallingDown(deltaTime);

    // ќбработка столкновени€ частицы с другими частицами
    // Ётот код предполагает, что у вас есть доступ к массиву или списку всех частиц
    for (auto& otherParticle : allParticles) {
        if (&otherParticle != this) { // ѕровер€ем, что не сталкиваемс€ с собой
            CollisionParticles(otherParticle);
        }
    }

    // ќбработка столкновени€ частицы с границами экрана
    CollisionParticleScreen(800, 600, 0.4f);

    // ќбновление визуального представлени€ частицы
    particleShape.setPosition(particlePosition);
}

void Particle::Render(sf::RenderWindow& windowRender) const
{
    windowRender.draw(particleShape);
}

void Particle::DrawVelocityVector(sf::RenderWindow& window) const
{
    float vectorLength = 10.0f;
    sf::Vector2f endPos = sf::Vector2f(particlePosition.x, particlePosition.y) + vectorLength * particleVelocity;

    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sf::Vector2f(particlePosition.x, particlePosition.y);
    line[0].color = sf::Color::Red;
    line[1].position = endPos;
    line[1].color = sf::Color::Red;

    window.draw(line);
}

float Particle::GetMass() const noexcept
{
    return particleMass;
}

float Particle::GetRadius() const noexcept
{
    return particleRadius;
}

sf::Vector2f Particle::GetPosition() const noexcept
{
    return particlePosition;
}

sf::Vector2f Particle::GetVelocity() const noexcept
{
    return particleVelocity;
}

sf::Color Particle::GetParticleColor() const noexcept
{
    return particleColor;
}

void Particle::SetMass(float set_mass)
{
    particleMass = set_mass;
}

void Particle::SetRadius(float set_radius)
{
    particleRadius = set_radius;
}

void Particle::SetVelocity(sf::Vector2f set_velocity)
{
    particleVelocity = set_velocity;
}

void Particle::SetParticleColor(const sf::Color& set_color)
{
    particleColor = set_color;
    particleShape.setFillColor(particleColor);
}

void Particle::SetPosition(sf::Vector2f set_position)
{
    particlePosition = set_position;
    particleShape.setPosition(particlePosition);
}

void Particle::RepelFromMouse(sf::Vector2f mousePosition, float repelStrength)
{
    sf::Vector2f direction = particlePosition - mousePosition;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 20)
    {
        direction /= distance; // Ќормализаци€ вектора
        sf::Vector2f repelForce = direction * repelStrength / distance * 20.0f; // —ила обратно пропорциональна рассто€нию
        particleVelocity += repelForce;
    }
}