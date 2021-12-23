#pragma once

/**
 * Defines the used boundary property (e.g. Outflow deletes the Particle(s), Reflecting reflects the Particle(s), Periodic works as a never ending domain)
 */
enum BoundaryType {
  Outflow, Reflecting, Periodic
};
