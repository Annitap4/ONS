# include <grid_panel.H>

Grid_Panel::Grid_Panel(Grid & _grid, QWidget * parent) :
  grid(_grid), QWidget(parent), selected(NULL)
{
  size_t w = grid.get_width();
  size_t h = grid.get_height();

  //Escala de dibujo del grafo
  x_scale = (Default_Values::WIDTH_GRID_DRAW_AREA / w) > Default_Values::MINIMUM_X_SCALE ?
             Default_Values::MINIMUM_X_SCALE : Default_Values::WIDTH_GRID_DRAW_AREA / w;

  y_scale = (Default_Values::HEIGHT_GRID_DRAW_AREA / h) > Default_Values::MINIMUM_Y_SCALE ?
             Default_Values::MINIMUM_Y_SCALE : Default_Values::HEIGHT_GRID_DRAW_AREA / h;

  //Calculo de donde comienza a dibujarse el grafo para que quede centrado
  x_init = Default_Values::X_PANEL_CENTER - (x_scale * (((double)(w) / 2) - 0.5));
  y_init = Default_Values::Y_PANEL_CENTER - (y_scale * (((double)(h) / 2) - 0.5));

  resize(Default_Values::WIDTH_GRID_PANEL, Default_Values::HEIGHT_GRID_PANEL);
}

void Grid_Panel::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.fillRect(0, 0, width(), height(), Qt::white);

  //Dibuja los arcos del grafo
  for (Arc_Iterator<Grid> it(grid); it.has_current();it.next())
    {
      Grid::Arc * arc = it.get_current();
      painter.setPen(Qt::black);

      Grid::Node * src = grid.get_src_node(arc);
      Grid::Node * tgt = grid.get_tgt_node(arc);
      painter.drawLine(QPoint(x_init + src->get_position().get_x().get_d() * x_scale, y_init + src->get_position().get_y().get_d() * y_scale),
                       QPoint(x_init + tgt->get_position().get_x().get_d() * x_scale, y_init + tgt->get_position().get_y().get_d() * y_scale));

      /*Package * package_from_src = arc->get_package_from_src();
      if (package_from_src)
        {

          short sign = 1;
          Grid::Node * n = package_from_src->get_routed_to();
          I(n != NULL);
          QPoint p(x_init + n->get_position().get_x().get_d() * x_scale, y_init + n->get_position().get_y().get_d() * y_scale);
          Direction dir = grid.get_arc_direction_respect_node(arc, n);
          if (dir == West or dir == North)
            sign = -1;
          if (grid.is_arc_horizontal(arc))
            {
              p.setY(p.y() - 10);
              p.setX(p.x() + sign * (Default_Values::X_RATIO + 5));
            }
          else
            {
              p.setY(p.x() - 10);
              p.setY(p.y() + sign * (Default_Values::Y_RATIO + 5));
            }
          painter.drawStaticText(p, QStaticText(QString(package_from_src->to_string().c_str())));
        }
      Package * package_from_tgt = arc->get_package_from_tgt();
      if (package_from_tgt)
        {
          short sign = 1;
          Grid::Node * n = package_from_tgt->get_routed_to();
          I(n != NULL);
          QPoint p(x_init + n->get_position().get_x().get_d() * x_scale, y_init + n->get_position().get_y().get_d() * y_scale);
          Direction dir = grid.get_arc_direction_respect_node(arc, n);
          if (dir == West or dir == North)
            sign = -1;
          if (grid.is_arc_horizontal(arc))
            {
              p.setY(p.y() - 10);
              p.setX(p.x() + sign * (Default_Values::X_RATIO + 5));
            }
          else
            {
              p.setY(p.x() - 10);
              p.setY(p.y() + sign * (Default_Values::Y_RATIO + 5));
            }
          painter.drawStaticText(p, QStaticText(QString(package_from_tgt->to_string().c_str())));
        }*/
    }
  //Dibuja los nodos del grafo
  for (Node_Iterator<Grid> it(grid); it.has_current(); it.next())
    {
      Grid::Node * node = it.get_current();
      painter.setPen(Qt::black);
      painter.setBrush(Qt::transparent);
      QPoint center(x_init + node->get_position().get_x().get_d() * x_scale, y_init + node->get_position().get_y().get_d() * y_scale);

      //Si lo marque (con un click) dibuja un rectangulo a su alrededor
      if (node == selected)
        painter.drawRect(center.x() - Default_Values::X_RATIO, center.y() - Default_Values::Y_RATIO,
                         Default_Values::X2_RATIO, Default_Values::Y2_RATIO);

      //Pinto el nodo actual
      painter.setBrush(Qt::black);
      painter.drawEllipse(center, Default_Values::X_RATIO, Default_Values::Y_RATIO);

      //Si el nodo es de entrada y salida simultaneamente dibuja una elipse
      //con el mismo centro con la mitad de su radio de color amarillo
      if (node->is_io())
        {
          painter.setPen(Qt::yellow);
          painter.setBrush(Qt::yellow);
          painter.drawEllipse(center, Default_Values::X_RATIO_2, Default_Values::Y_RATIO_2);
        }
      //Si es de entrada pinta una elipse verde
      else if (node->is_in())
        {
          painter.setPen(Qt::green);
          painter.setBrush(Qt::green);
          painter.drawEllipse(center, Default_Values::X_RATIO_2, Default_Values::Y_RATIO_2);
        }
     //Si es de salida pinta una elipse roja
     else if (node->is_out())
       {
         painter.setPen(Qt::red);
         painter.setBrush(Qt::red);
         painter.drawEllipse(center, Default_Values::X_RATIO_2, Default_Values::Y_RATIO_2);
       }
    }
}

void Grid_Panel::mousePressEvent(QMouseEvent * evt)
{
  Point clicked_point(evt->pos().x(), evt->pos().y());
  //Itero sobre los nodos para determinar si se hizo click sobre alguno de ellos
  for (Node_Iterator<Grid> it(grid); it.has_current(); it.next())
    {
      Grid::Node * curr = it.get_current();
      const Point center(x_init + curr->get_position().get_x().get_d() * x_scale, y_init + curr->get_position().get_y().get_d() * y_scale);
      if (not Geometric::is_point_inside_ellipse(clicked_point, center, 10, 10))
                                                // Default_Values::X_RATIO, Default_Values::Y_RATIO))
        continue;
      selected = curr;
      repaint();
      fire_event();
      return;
    }
  //Si no fue seleccionado ninguno se coloca a selected como NULL para que no se dibuje ningun rectangulo
  selected = NULL;
  repaint();
  fire_event();
}

void Grid_Panel::add_listener(Grid_Panel_Listener * listener)
{
  listeners.append(listener);
}

void Grid_Panel::fire_event()
{
  for (DynDlist<Grid_Panel_Listener *>::Iterator it(listeners); it.has_current(); it.next())
    it.get_current()->panel_clicked();
}
