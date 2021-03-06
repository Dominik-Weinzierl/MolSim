#pragma once

#include <functional>
#include <iostream>
#include <utility>
#include <omp.h>

#include "particles/Particle.h"
#include "boundaryType/BoundaryType.h"

/**
 * Describes the direction of this cell in relation to the board.
 */
enum BoardDirectionType {
  RIGHT, LEFT, TOP, BOTTOM, BACK, FRONT
};

/**
 * Cell is a container which handles pointer to neighbour Cell(s) and Particles(s).
 * @tparam dim dimension for the simulation
 */
template<size_t dim>
class Cell {
 protected:
#ifdef _OPENMP
  omp_lock_t lock;
#endif
  /**
   * Vector of Particle(s) in this Cell.
   */
  std::vector<Particle<dim> *> particles{};

  /**
   * Vector of neighbours of this Cell.
   */
  std::vector<Cell<dim> *> neighbours{};

  /**
   * Vector of cells which are influenced through periodic.
   */
  std::vector<std::tuple<Cell<dim> *, Vector<dim>>> periodicNeighbours{};

  /**
   * Current position of this Cell. This is fixed and won't change during the simulation.
   */
  const Vector<dim> position;

  /**
   * Cell size of each Cell. This is fixed and won't change during the simulation.
   */
  const Vector<dim> cellSize;

  /**
   * BoundaryType of this Cell. Used to handle correct boundary options (e.g. Outflow, Reflection, ...)
   */
  const std::vector<BoundaryType> boundaryType{BoundaryType::Outflow};

  /**
   * Defines the side on which this Cell is.
   */
  const std::vector<BoardDirectionType> borderDirection;

  /**
   * Domain of our simulation.
   */
  const Vector<dim> domain;

 public:

  //----------------------------------------Constructor & Destructor----------------------------------------

  /**
   * Constructor to create our Cell(s).
   * @param pBoundaryType default is Outflow (but other types are also possible)
   * @param pBorderDirection direct of this cell
   * @param pPosition position of this Cell in our Mesh
   * @param pCellSize size of this cell (each Cell has the same size)
   * @param pDomain domain size used during this simulation
   */
  Cell(std::vector<BoundaryType> pBoundaryType, std::vector<BoardDirectionType> pBorderDirection, Vector<dim> pPosition,
       Vector<dim> pCellSize, Vector<dim> pDomain) : boundaryType{std::move(pBoundaryType)},
                                                     borderDirection{std::move(pBorderDirection)}, position{pPosition},
                                                     cellSize{pCellSize}, domain{pDomain} {
#ifdef _OPENMP
    omp_init_lock(&lock);
#endif
  };

  /**
   * Constructor to create our Cell(s). In this case our boundary type is always Outflow.
   * @param pPosition position of this Cell in our Mesh
   * @param pCellSize size of this cell (each Cell has the same size)
   * @param pDomain domain size used during this simulation
   */
  Cell(Vector<dim> pPosition, Vector<dim> pCellSize, Vector<dim> pDomain) : position{pPosition}, cellSize{pCellSize},
                                                                            domain{pDomain} {
#ifdef _OPENMP
    omp_init_lock(&lock);
#endif
  };

  /**
   * Default destructor used for inheritance.
   */
  virtual ~Cell() {
#ifdef _OPENMP
    omp_destroy_lock(&lock);
#endif
  }

  //----------------------------------------Methods----------------------------------------

  /**
   * Each Cell type has different actions they need to perform on Particle(s).
   */
  virtual void applyCellProperties() = 0;

  /**
   * Insert a Particle (in this case a pointer to a Particle) into our Cell.
   * @param p pointer to Particle in ParticleContainer (e.g. LinkedCellContainer)
   */
  void insertParticle(Particle<dim> *p) {
    SPDLOG_TRACE("Cell->insertParticle(): {}", p->toString());
    particles.push_back(p);
  }

  //----------------------------------------Getter & Setter----------------------------------------

  /**
   * @return Iterator to the beginning of the particles-Vector.
   */
  [[nodiscard]] auto begin() { return particles.begin(); }

  /**
   * @return Iterator to the end of the particles-Vector.
   */
  [[nodiscard]] auto end() { return particles.end(); }

  /**
   * @return Iterator to the beginning of the neighbours-Vector.
   */
  [[nodiscard]] auto nBegin() { return neighbours.begin(); }

  /**
   * @return Iterator to the end of the neighbours-Vector.
   */
  [[nodiscard]] auto nEnd() { return neighbours.end(); }

  /**
   * Getter for the Particle(s) which are in this Cell.
   * @return std::vector<Particle<dim> *> particles
   */
  std::vector<Particle<dim> *> &getParticles() {
    return particles;
  }

  /**
   * Getter for the neighbours (relevant cells).
   * @return std::vector<Cell<dim> *> neighbours
   */
  std::vector<Cell<dim> *> &getNeighbours() {
    return neighbours;
  }

  /**
   * Getter for the periodic neighbours.
   * @return std::vector<Cell<dim> *> neighbours
   */
  std::vector<std::tuple<Cell<dim> *, Vector<dim>>> &getPeriodicNeighbours() {
    return periodicNeighbours;
  }

  /**
   * Getter for the border directions.
   * @return std::vector<BoardDirectionType> borderDirection
   */
  [[nodiscard]] const std::vector<BoardDirectionType> &getBorderDirection() const {
    return borderDirection;
  }

  /**
   * Getter for the position of the cell in the mesh.
   * @return Vector<dim> position
   */
  const Vector<dim> &getPosition() const {
    return position;
  }

  /**
   * Getter for the cell size of the current cell.
   * @return Vector<dim> cellSize
   */
  const Vector<dim> &getCellSize() const {
    return cellSize;
  }

  inline void setLock() {
#ifdef _OPENMP
    omp_set_lock(&lock);
#endif
  }

  inline void unsetLock() {
#ifdef _OPENMP
    omp_unset_lock(&lock);
#endif

  }
};
