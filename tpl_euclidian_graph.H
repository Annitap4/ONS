/*
  This file is part of Aleph system

  Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011
  UNIVERSITY LOS ANDES (ULA) Merida - REPÚBLICA BOLIVARIANA DE VENEZUELA  

  - Center of Studies in Microelectronics & Distributed Systems (CEMISID) 
  - ULA Computer Science Department

  PERMISSION TO USE, COPY, MODIFY AND DISTRIBUTE THIS SOFTWARE AND ITS
  DOCUMENTATION IS HEREBY GRANTED, PROVIDED THAT BOTH THE COPYRIGHT
  NOTICE AND THIS PERMISSION NOTICE APPEAR IN ALL COPIES OF THE
  SOFTWARE, DERIVATIVE WORKS OR MODIFIED VERSIONS, AND ANY PORTIONS
  THEREOF, AND THAT BOTH NOTICES APPEAR IN SUPPORTING DOCUMENTATION.

  Aleph is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.

  UNIVERSIDAD DE LOS ANDES requests users of this software to return to 

  Leandro Rabindranath Leon
  CEMISID 
  Ed La Hechicera 
  3er piso, ala sur
  Facultad de Ingenieria 
  Universidad de Los Andes 
  Merida - REPÚBLICA BOLIVARIANA DE VENEZUELA    or

  lrleon@ula.ve
  leandro.r.leon@gmail.com

  any improvements or extensions that they make and grant Universidad 
  de Los Andes (ULA) the rights to redistribute these changes. 
*/

# ifndef TPL_EUCLIDIAN_GRAPH_H
# define TPL_EUCLIDIAN_GRAPH_H

# include <tpl_graph.H>
# include <point.H>

namespace Aleph
{

  template <typename Node_Info>
  class Euclidian_Node : public Graph_Node <Node_Info>
  {
  public:
    typedef Node_Info Item_Type;

    typedef Euclidian_Node Node;

    typedef Node_Info Node_Type;

  private:
    Point position;

  public:

    Euclidian_Node()
     : Graph_Node<Node_Info>(), position()
    {
      /* Empty */
    }

    Euclidian_Node(const Node_Info & info)
      : Graph_Node<Node_Info>(info), position()
    {
      /* Empty */
    }

    Euclidian_Node(const Point & _position)
      : Graph_Node<Node_Info>(), position(_position)
    {
      /* Empty */
    }

    Euclidian_Node(const Node_Info & info, const Point & _position)
      : Graph_Node<Node_Info>(info), position(_position)
    {
      /* Empty */
    }

    Euclidian_Node(Euclidian_Node * node)
      : Graph_Node<Node_Info>(node), position(node->get_position())
    {
      /* Empty */
    }

    Point & get_position() { return position; }

    const Point & get_position() const { return position; }

  };  // End class Euclidian_Node

  template <typename Arc_Info>
  class Euclidian_Arc : public Graph_Arc <Arc_Info>
  {
  public:
    typedef Arc_Info Arc_Item;

    typedef Euclidian_Arc Arc;

    typedef Arc_Info Arc_Type;

    Euclidian_Arc()
      : Graph_Arc<Arc_Info>()
    {
      /* Empty */
    }

    Euclidian_Arc(const Arc_Info & info)
      : Graph_Arc<Arc_Info>(info)
    {
      /* Empty */
    }

    Euclidian_Arc(void * src, void * tgt, const Arc_Info & info)
      : Graph_Arc<Arc_Info>(src, tgt, info)
    {
      /* Empty */
    }

    Euclidian_Arc(void * src, void * tgt)
      : Graph_Arc<Arc_Info>(src, tgt)
    {
      /* Empty */
    }

  }; // End class Euclidian_Arc

  template <class __Euclidian_Node, class __Euclidian_Arc>
  class Euclidian_Graph : public List_Graph <__Euclidian_Node, __Euclidian_Arc>
  {
  public:
    typedef __Euclidian_Node Node;

    typedef __Euclidian_Arc Arc;

    typedef List_Graph<Node, Arc> Graph;

    typedef typename Node::Node_Type Node_Type;

    typedef typename Arc::Arc_Type Arc_Type;

    Euclidian_Graph() : Graph()
    {
      /* Empty */
    }

    Euclidian_Graph(const Euclidian_Graph <Node, Arc> & euclidian_graph)
      : Graph()
    {
      copy_graph(*this, const_cast<Euclidian_Graph <Node, Arc> &> (euclidian_graph), false);
    }

    virtual Node * insert_node(Node * node)
    {
      return Graph::insert_node(node);
    }

    virtual Node * insert_node(const Node_Type & info)
    {
      return insert_node(new Node(info));
    }

    virtual Node * insert_node(const Point & position)
    {
      return insert_node(new Node(position));
    }

    virtual Node * insert_node(const Node_Type & info, const Point & position)
    {
      return insert_node(new Node(info, position));
    }

    Geom_Number get_distance(Arc * arc)
    {
      const Point & src_point = get_src_node(arc)->get_position();
      const Point & tgt_point = get_tgt_node(arc)->get_position();
      return src_point.distance_with(tgt_point);
    }

    Euclidian_Graph<Node, Arc> & operator = (Euclidian_Graph<Node, Arc> & eg)
    {
      if (this == &eg)
        return *this;
      copy_graph(*this, const_cast<Euclidian_Graph<Node, Arc> &>(eg), false);
      return *this;
    }

    virtual ~Euclidian_Graph()
    {
      clear_graph(*this);
    }

    Node * search_node(const Point &);

  };  // End class Euclidian_Graph

  template <class __Euclidian_Node, class __Euclidian_Arc>
  class Euclidian_Digraph : public Euclidian_Graph<__Euclidian_Node, __Euclidian_Arc>
  {
  public:
    Euclidian_Digraph()
    {
      Euclidian_Graph<__Euclidian_Node, __Euclidian_Arc>::digraph = true;
    }

    Euclidian_Digraph(const Euclidian_Digraph <__Euclidian_Node, __Euclidian_Arc> & euclidian_digraph)
      : Euclidian_Graph<__Euclidian_Node, __Euclidian_Arc>(euclidian_digraph)
    {
      Euclidian_Graph<__Euclidian_Node, __Euclidian_Arc>::digraph = true;
    }

    Euclidian_Digraph<__Euclidian_Node, __Euclidian_Arc> & operator = (Euclidian_Digraph<__Euclidian_Node, __Euclidian_Arc> & eg)
    {
      return Euclidian_Graph<__Euclidian_Node, __Euclidian_Arc>::operator = (eg);
    }

  };  // End class Euclidian_Digraph

  template <class Node, class Arc>
  Node * Euclidian_Graph<Node, Arc>::search_node(const Point & point)
  {
    for (typename Euclidian_Graph<Node, Arc>::Node_Iterator it; it.has_current(); it.next())
      {
        Euclidian_Graph<Node, Arc>::Node * curr = it.get_current();
        if (curr->get_position() == point)
          return curr;
      }
    return NULL;
  }

} // End namespace Aleph

# endif // TPL_EUCLIDIAN_GRAPH_H

