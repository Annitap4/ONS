# ifndef SIMULATOR_H
# define SIMULATOR_H

# include <grid.H>
# include <minimum_deflecting.H>
# include <sim_listener.H>

# include <fstream>

# include <gsl/gsl_rng.h>

class Simulator
{
  gsl_rng * rng;

  bool __is_running;

  unsigned long packages_counter;

  unsigned long num_iterations;

  size_t grid_width;

  size_t grid_height;

  DynDlist<Package> packages;

  DynDlist<Grid::Node *> entrances;

  DynDlist<Grid::Node *> exits;

  DynDlist<Sim_Listener *> listeners;

  Grid grid;

  Statistics * statistics;

  void fire_event(const Event_Type &);

public:
  Simulator();

  ~Simulator();

  void add_entrance(Grid::Node *);

  void remove_entrance(Grid::Node *);

  void add_exit(Grid::Node *);

  void remove_exit(Grid::Node *);

  void move_packages();

  void generate_packages();

  void step();

  void add_listener(Sim_Listener *);

  Grid & get_grid() { return grid; }

  bool is_running() const { return __is_running; }
};

# endif // SIMULATOR_H
