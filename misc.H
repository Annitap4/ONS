# ifndef MISC_H
# define MISC_H

# include <tpl_euclidian_graph.H>

# include <cmath>

enum Direction
{
  North,
  South,
  East,
  West,
  Num_Directions
};

inline Direction get_reflect_direction(const Direction & dir)
{
  switch(dir)
    {
    case North: return South;
    case South: return North;
    case East:  return West;
    case West:  return East;
    default: throw std::domain_error("Invalid value of direction");
    }
}

/**
  * \brief Clase que contiene constantes est&aacute;ticas.
  *
  * Las constantes que se definen en esta clase tienen los valores que se usan para las ventanas que dibujan la Grid, tama&ntilde;o de los elementos, etc. Esta clase no es instanciable.
  * @authors Alejandro Mujica, Anna Lezama, Yajaira Useche
  */
class Default_Values
{
  Default_Values() { /* Empty */ }

public:
  static const size_t WIDTH_GRID_DRAW_AREA = 600;
  static const size_t MINIMUM_X_SCALE = 100;
  static const size_t X_RATIO = 10;
  static const size_t X_RATIO_2 = X_RATIO / 2;
  static const size_t X2_RATIO = 2 * X_RATIO;
  static const size_t WIDTH_GRID_PANEL = WIDTH_GRID_DRAW_AREA + X2_RATIO;
  static const size_t X_PANEL_CENTER = WIDTH_GRID_PANEL / 2;
  static const size_t HEIGHT_GRID_DRAW_AREA = 600;
  static const size_t MINIMUM_Y_SCALE = 100;
  static const size_t Y_RATIO = 10;
  static const size_t Y_RATIO_2 = Y_RATIO / 2;
  static const size_t Y2_RATIO = 2 * Y_RATIO;
  static const size_t HEIGHT_GRID_PANEL = HEIGHT_GRID_DRAW_AREA + Y2_RATIO;
  static const size_t Y_PANEL_CENTER = HEIGHT_GRID_PANEL / 2;
};

/**
  * \brief Clase de funciones geom&eacute;tricas, no instanciable.
  * @authors Alejandro Mujica, Anna Lezama, Yajaira Useche
  */
class Geometric
{
  Geometric() { /* Empty */ }
public:

  /** Determina si el punto esta dentro de la elipse con centro, radio horizontal y radio vertical dados como par&aacute;metros.
    * @param [in] point Punto en cuesti&oacute;n
    * @param [in] center Centro de la Elipse
    * @param [in] hr Radio horizontal de la Elipse
    * @param [in] vr Radio vertical de la Elipse
    * @return Verdadero si el punto "point" est&aacute; contenido en la elipse y falso en caso contrario.
    */
  static bool is_point_inside_ellipse(const Point & point, const Point & center,
                                      const size_t & hr, const size_t & vr)
  {
    return (pow(point.get_x().get_d() - center.get_x().get_d(), 2) / pow(hr, 2)) + (pow(point.get_y().get_d() - center.get_y().get_d(), 2) / pow(vr, 2)) <= 1;
  }
};

/**
  * \brief Clase que contiene la operacion por defecto a realizarse sobre un nodo al construir en Build_Grid.
  * @authors Alejandro Mujica, Anna Lezama, Yajaira Useche
  */
template <class GT>
struct Default_Operation_On_Node
{
  void operator () (GT &, typename GT::Node *, const size_t &, const size_t &) { /* Empty */ }
};

/**
  * \brief Clase que contiene la operacion por defecto a realizarse sobre un arco al construir en Build_Grid.
  * @authors Alejandro Mujica, Anna Lezama, Yajaira Useche
  */
template <class GT>
struct Default_Operation_On_Arc
{
  void operator () (GT &, typename GT::Arc *, const size_t &, const size_t &) { /* Empty */ }
};

/**
  * \brief Clase que construye un grafo en forma Grid en forma de rejilla
  * 
  * La clase recibe los siguientes par&aacute;metros tipo:
  * <ol>
  * <li> GT: el tipo de grafo basado en <a href="http://webdelprofesor.ula.ve/ingenieria/lrleon/aleph/html" target="_blank">Aleph::List_Graph</a>
  * <li> Operation_On_Node: La clase de operaci&oacute;n sobre los nodos que debe exportar lo siguiente
  *    <ul>
  *    <li> Operation_On_Node::operator()(GT & g, typename GT::Node * node, const size_t & i, const size_t & j) que retorna void.
  *    </ul>
  *    .
  * <li> Operation_On_Arc: La clase de operaci&oacute;n sobre los arcos que debe exportar lo siguiente
  *    <ul>
  *    <li> Operation_On_Arc::operator()(GT & g, typename GT::Arc * arc, const size_t & i, const size_t & j) que retorna void.
  *    </ul>
  * </ol>
  * @authors Alejandro Mujica, Anna Lezama, Yajaira Useche
  */
template <
          class GT,
          class Operation_On_Node = Default_Operation_On_Node<GT>,
          class Operation_On_Arc = Default_Operation_On_Arc<GT>
         >
class Grid_Builder
{
public:
  /**
    * Este operador construye un grafo en forma de grid con topologia octagonal con un ancho width y una altura height.
    *
    * @param [out] g Grafo sobre el cual se construir&aacute; la Grid
    * @param [in] width Cantidad de columnas que tendr&aacute; la Grid
    * @param [in] height Cantidad de filas que tendr&aacute; la Grid
    * @exception domain_error si el Grafo en el que se construir&aacute; la grid ya tiene nodos.
    * @exception length_error Si la el width < 2 o height < 2
    */
  void operator () (GT & g, const size_t & width, const size_t & height)
  {
    clear_graph(g);

    if (width < 2 or height < 2)
      throw std::length_error("The minimun size must be 2 x 2");

    typename GT::Node *** map = new typename GT::Node **[height];
    for (size_t i = 0; i < height; ++i)
      {
	try
	  {
	    map[i] = new typename GT::Node *[width];
	    for (size_t j = 0; j < width; ++j)
	      {
		typename GT::Node * n = g.insert_node(typename GT::Node_Type());
		Operation_On_Node()(g, n, i, j);
		map[i][j] = n;
		if (j > 0) //Conecta con el nodo a su izquierda
		  {
		    typename GT::Arc * a = g.insert_arc(n, map[i][j - 1]);
		    Operation_On_Arc()(g, a, i, j);
		  }
		if (i > 0) //Conecta con el nodo que esta arriba
		  {
		    typename GT::Arc * a = g.insert_arc(n, map[i - 1][j]);
		    Operation_On_Arc()(g, a, i, j);
		  }
	      }
	  }
	catch (...)
	  {
            //Si se captura excepcion libero la memoria apartada hasta ahora y la relanzo	
	    for (size_t k = i - 1; k >= 0; --k)
	      delete [] map[k];
	    delete [] map;
	    clear_graph(g);
	    throw;
	  }
      }

    for (size_t i = 0; i < height; ++i)
      delete [] map[i];
    delete [] map;
  }
};

# endif

