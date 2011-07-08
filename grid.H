# ifndef GRID_H
# define GRID_H

# include <tpl_euclidian_graph.H>
# include <package.H>

class Grid;

class Package;

class Op_Node;

class Op_Arc;

/**
  * \brief Clase que define el nodo para una Grid.
  *
  * Clase basada en <a href="http://webdelprofesor.ula.ve/ingenieria/lrleon/aleph/html" target="_blank">Aleph::Graph_Node</a> con par&aacute;metro tipo long.
  * @authors: Alejandro Mujica, Anna Lezama, Yajaira Useche
  */
class Grid_Node : public Euclidian_Node<long>
{
  bool __is_in;
  bool __is_out;

  DynDlist<Package *> clients;

public:
  Grid_Node() : Euclidian_Node<long>(),
                __is_in(false), __is_out(false)
  {
    /* Empty */
  }

  Grid_Node(const long & num)
    : Euclidian_Node<long>(num), __is_in(false), __is_out(false)
  {
    /* Empty */
  }

  Grid_Node(Grid_Node * node)
    : Euclidian_Node<long>(this), __is_in(node->__is_in), __is_out(node->__is_out)
  {
    /* Empty */
  }

  Grid_Node(const Point & point)
    : Euclidian_Node<long>(point),  __is_in(false), __is_out(false)
  {
    /* Empty */
  }

  Grid_Node(const long & num, const Point & point)
    : Euclidian_Node<long>(num, point),  __is_in(false), __is_out(false)
  {
    /* Empty */
  }

  bool & is_in() { return __is_in; }

  bool & is_out() { return __is_out; }

  /**
    * @return Verdadero si un nodo trabaja como entrada y salida simult&aacute;neamente, Falso si no se cumple al menos una de las dos condiciones.
    */
  const bool is_io() const { return __is_in and __is_out; }

  void add_client(Package * p)
  {
    p->reset();
    Grid_Node * package_target = p->get_target_node();
    if (package_target->get_position().get_x().get_d() < get_position().get_x().get_d())
      p->get_h_favorable_direction() = West;
    else if (package_target->get_position().get_x().get_d() > get_position().get_x().get_d())
      p->get_h_favorable_direction() = East;
    if (package_target->get_position().get_y().get_d() < get_position().get_y().get_d())
      p->get_v_favorable_direction() = North;
    else if (package_target->get_position().get_y().get_d() > get_position().get_y().get_d())
      p->get_v_favorable_direction() = South;
    clients.append(p);
  }

  DynDlist<Package *> & get_clients_list() { return clients; }

  const std::string to_string() const { return gnu::autosprintf("Node%ld", get_info()); }
};

/**
  * \brief Clase que define el enlace de nodos en una Grid.
  *
  * Clase basada en <a href="http://webdelprofesor.ula.ve/ingenieria/lrleon/aleph/html" target="_blank">Aleph::Graph_Arc</a> con par&aacute;metro tipo <a href="http://webdelprofesor.ula.ve/ingenieria/lrleon/aleph/html" target="_blank">Aleph::Empty_Class</a>.
  * @authors Alejandro Mujica, Anna Lezama, Yajaira Useche
  */
class Link : public Euclidian_Arc<Empty_Class>
{
  Direction dir;

  Package * package_from_src;
  Package * package_from_tgt;

public:
  Link() : Euclidian_Arc<Empty_Class>(), dir(Num_Directions), package_from_src(NULL), package_from_tgt(NULL)
  { 
    /* Empty */
  }

  Link(const Empty_Class & info) : Euclidian_Arc<Empty_Class>(info),
  dir(Num_Directions), package_from_src(NULL), package_from_tgt(NULL)
  {
    /* Empty */
  }

  Link(void * src, void * tgt, const Empty_Class & data) : Euclidian_Arc<Empty_Class>(src, tgt, data),
  dir(Num_Directions), package_from_src(NULL), package_from_tgt(NULL)
  {
    /* Empty */
  }

  Link(void * src, void * tgt) : Euclidian_Arc<Empty_Class>(src, tgt),
  dir(Num_Directions), package_from_src(NULL), package_from_tgt(NULL)
  {
    /* Empty */
  }

  Direction & get_direction() { return dir; }

  const Direction & get_direction() const { return dir; }

  Package * get_package_from_src()
  {
    return package_from_src;
  }

  void set_package_from_src(Package * p)
  {
    package_from_src = p;

  }

  Package * get_package_from_tgt()
  {
    return package_from_tgt;
  }

  void set_package_from_tgt(Package * p)
  {
    package_from_tgt = p;
  }

  const bool is_busy_for_src() const { return package_from_src != NULL; }

  const bool is_busy_for_tgt() const { return package_from_tgt != NULL; }

  void reset()
  {
    package_from_src = package_from_tgt = NULL;
  }
};

/**
  * \brief Clase que define una Grid
  *
  * Est&aacute; basada en la clase <a href="http://webdelprofesor.ula.ve/ingenieria/lrleon/aleph/html" target="_blank">Aleph::List_Graph</a> con par&aacute;metros tipo Grid_Node y Link.
  * @authors Alejandro Mujica, Anna Lezama, Yajaira Useche
  */
class Grid : public Euclidian_Graph<Grid_Node, Link>
{
  size_t width;   ///< N&uacute;umero de columnas de la Grid
  size_t height;  ///< N&uacute;mero de columnas de la Grid
  
public:
  typedef Euclidian_Graph<Grid_Node, Link> Graph;

  Grid()
    : Graph(), width(), height() { /* Empty */ }

  Grid(const size_t & w, const size_t & h)
    : Graph(), width(w), height(h) { /* Empty */ }

  Grid(const Grid & grid)
    : Graph(grid), width(grid.width), height(grid.height)
  { /* Empty */ }

  ~Grid() { /* Empty */ }

  void set_height(const size_t & h) { height = h; }

  const size_t & get_height() const { return height; }

  void set_width(const size_t & w) { width = w; }

  const size_t & get_width() const { return width; }

  /**
    * \brief  Construye una grid con las dimensiones definidas por width y height.
    *
    * Hace uso de la clase Build_Grid con par&aacute;metros this, Op_Node y la operaci&oacute;n sobre arcos se deja por omisi&oacute;n
    */
  void build_automatic_grid()
  {
    Grid_Builder<Grid, Op_Node> ()(*this, width, height);
  }

  /**
    * Inserta un nuevo nodo en la grid.
    * @param [in] num Etiqueta que identifica al nodo
    * @param [in] x N&uacute;mero de fila que ocupa en la Grid
    * @param [in] y N&uacute;mero de columna que ocupa en la Grid
    * @return El puntero al nodo insertado
    */
  Node * insert_grid_node(const int & num, const long & x, const long & y)
  {
    std::auto_ptr<Node> node(new Node(num));
    node->get_position() = Point(x, y);
    return Graph::insert_node(node.release());
  }

  Arc * insert_arc(Node * src, Node * tgt)
  {
    Arc * arc = Graph::insert_arc(src, tgt);
    if (src->get_position().get_x().get_d() < tgt->get_position().get_x().get_d() and
        src->get_position().get_y().get_d() == tgt->get_position().get_y().get_d())
      arc->get_direction() = East;
    else if (src->get_position().get_x().get_d() > tgt->get_position().get_x().get_d() and
             src->get_position().get_y().get_d() == tgt->get_position().get_y().get_d())
      arc->get_direction() = West;
    else if (src->get_position().get_y().get_d() < tgt->get_position().get_y().get_d() and
             src->get_position().get_x().get_d() == tgt->get_position().get_x().get_d())
      arc->get_direction() = South;
    else if (src->get_position().get_y().get_d() > tgt->get_position().get_y().get_d() and
             src->get_position().get_x().get_d() == tgt->get_position().get_x().get_d())
      arc->get_direction() = North;
    return arc;
  }

  Direction get_arc_direction_respect_node(Arc * arc, Node * node)
  {
    return get_src_node(arc) == node ? arc->get_direction() : get_reflect_direction(arc->get_direction());
  }

  Arc * get_arc_by_rout(Node * node, const Direction & dir)
  {
    for (Node_Arc_Iterator it(node); it.has_current(); it.next())
      {
        Arc * a = it.get_current();
        if (get_src_node(a) == node and dir == a->get_direction())
          return a;
        if (get_tgt_node(a) == node and dir == get_reflect_direction(a->get_direction()))
          return a;
      }
    return NULL;
  }

  const bool is_arc_busy_for_node(Arc * arc, Node * node)
  {
    return get_src_node(arc) == node ? arc->is_busy_for_src() : arc->is_busy_for_tgt();
  }

  Arc * get_first_free_link(Node * node)
  {
    for (Node_Arc_Iterator it(node); it.has_current(); it.next())
      {
        Arc * arc = it.get_current();
        if (not is_arc_busy_for_node(arc, node))
          return arc;
      }
    return NULL;
  }

  void set_arc_busy_for_node(Arc * arc, Node * node, Package * p)
  {
    if (get_src_node(arc) == node)
      arc->set_package_from_src(p);
    else
      arc->set_package_from_tgt(p);
  }

  bool is_arc_horizontal(Arc * arc)
  {
    Node * src = get_src_node(arc);
    Node * tgt = get_tgt_node(arc);
    return src->get_position().get_y().get_d() == tgt->get_position().get_y().get_d();
  }

  bool is_arc_vertical(Arc * arc)
  {
    Node * src = get_src_node(arc);
    Node * tgt = get_tgt_node(arc);
    return src->get_position().get_x().get_d() == tgt->get_position().get_x().get_d();
  }

  void reset_all_arcs()
  {
    for (Arc_Iterator it(*this); it.has_current(); it.next())
      {
        Arc * arc = it.get_current();
        arc->reset();
      }
  }
};

/**
  * \brief Clase que contiene la operaci&oacute;n que se efectuar&aacute; al construir la grid.
  *
  * La clase se pasa como par&aacute;metro a la clase Build_Grid al dentro del m&eacute;todo Grid::build()
  * @authors Alejandro Mujica, Anna Lezama, Yajaira Useche
  */
class Op_Node
{
public:
  /**
    * \brief Definici&oacute;n del operador ()
    *
    * Esta es la operaci&oacute;n que se ejecuta sobre los nodos al construir la grid en el m&eacute;todo Grid::build() y se encarga de escribir en el nodo su n&uacute;mero identificados y la fila y columna donde se ubica en la Grid
    * @param g Grafo que se est&aacute; construyendo como grid
    * @param node Nodo sobre el cual se efect&uacute;a la operaci&oacute;n
    * @param [in] i N&uacute;mero de fila donde se ubica el nodo en la grid
    * @param [in] j N&uacute;mero de columna donde se ubica el nodo en la grid
    */
  void operator () (Grid & g, Grid_Node * node, const size_t & i, const size_t & j)
  {
    node->get_info() = g.get_width() * i + j;
    node->get_position() = Point(j, i);
  }
};

# endif
