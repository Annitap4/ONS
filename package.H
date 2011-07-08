# ifndef PACKAGE_H
# define PACKAGE_H

# include <grid.H>
# include <misc.H>

# include <string>

# include <autosprintf.h>

class Grid;

class Grid_Node;

class Link;

/**
  * \brief Clase que define un paquete que se mueve por la red
  * @authors Alejandro Mujica, Anna Lezama, Yajaira Useche
  */
class Package
{
  unsigned long id;      // Identificador unico de cada paquete
  unsigned short ttl;    // Tiempo de vida de un paquete, por cuantos enlaces ha pasado
  Grid_Node * source;    // Direccion del nodo que envia el paquete
  Grid_Node * target;    // Direccion del destino del paquete
  Grid_Node * routed_to; // Hacia donde se ha enrutado el paquete en un instante de tiempo

  Direction h_favorable_direction; // Direccion favorable horizontal
  Direction v_favorable_direction; // Direccion favorable vertical

public:
  Package() : id(0), ttl(0), source(NULL), target(NULL), routed_to(NULL),
              h_favorable_direction(Num_Directions), v_favorable_direction(Num_Directions)
  {
    // Empty
  }

  Package(const unsigned long & _id, Grid_Node * src, Grid_Node * tgt)
    : id(_id), ttl(0), source(src), target(tgt), routed_to(NULL),
      h_favorable_direction(Num_Directions), v_favorable_direction(Num_Directions)
  {
    // Empty
  }

  Package(const Package & p) : id(p.id), ttl(p.ttl), source(p.source), target(p.target), routed_to(p.routed_to),
                               h_favorable_direction(p.h_favorable_direction), v_favorable_direction(p.v_favorable_direction)
  {
    // Empty
  }

  ~Package()
  {
    // Empty
  }

  const unsigned long & get_id() const { return id; }

  const unsigned short & get_ttl() const { return ttl; }

  void inc_ttl() { ++ttl; }

  Grid_Node * get_source_node() { return source; }

  Grid_Node * get_target_node() { return target; }

  Grid_Node * get_routed_to() { return routed_to; }

  const unsigned short get_num_favorable_directions() const
  {
    int ret_val = 0;
    if (h_favorable_direction != Num_Directions)
      ++ret_val;
    if (v_favorable_direction != Num_Directions)
      ++ret_val;
    return ret_val;
  }

  void reset()
  {
    routed_to = NULL;
    v_favorable_direction = Num_Directions;
    h_favorable_direction = Num_Directions;
  }

  void rout_to(Grid_Node * node)
  {
    routed_to = node;
  }

  const Direction & get_h_favorable_direction() const { return h_favorable_direction; }

  Direction & get_h_favorable_direction() { return h_favorable_direction; }

  const Direction & get_v_favorable_direction() const { return v_favorable_direction; }

  Direction & get_v_favorable_direction() { return v_favorable_direction; }

  const std::string to_string()
  {
    return gnu::autosprintf("P%ld", id);
  }
};

# endif
