// ConstHeader.h

#ifndef CONST_DATA_H
#define CONST_DATA_H

namespace PhysicsConstants {

    // Универсальные физические константы
    constexpr double GRAVITATIONAL_CONSTANT = 6.67430e-11; // м³ кг⁻¹ с⁻²
    constexpr double SPEED_OF_LIGHT = 299792458;           // м/с
    constexpr double BOLTZMANN_CONSTANT = 1.380649e-23;    // Дж/К
    constexpr double PLANCK_CONSTANT = 6.62607015e-34;     // Дж·с
    constexpr double AVOGADRO_CONSTANT = 6.02214076e23;    // моль⁻¹

    // Константы, связанные с Землей
    constexpr double GRAVITY = 9.80665;                    // м/с² (ускорение свободного падения)

    // Константы для моделирования частиц
    constexpr double DEFAULT_MASS = 1.0;                   // кг
    constexpr double DEFAULT_RADIUS = 1.0;                 // м
    constexpr double ELASTICITY_COEFFICIENT = 1.0;         // Безразмерный (коэффициент упругости)
    constexpr double FRICTION_COEFFICIENT = 0.1;           // Безразмерный (коэффициент трения)
    constexpr double AIR_DENSITY = 1.225;                  // кг/м³
    constexpr double AIR_RESISTANCE_COEFFICIENT = 1.0;     // Безразмерный

    // Электромагнитные константы
    constexpr double COULOMB_CONSTANT = 8.9875517873681764e9; // Н·м²/Кл²

}

#endif // CONST_DATA_H