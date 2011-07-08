# include <grid_window.H>

Grid_Window::Grid_Window(QWidget * parent) :
  QWidget(parent), simulator(), panel(simulator.get_grid()), editable(true)
{
  ui.setupUi(this);
  ui.vlayout->addWidget(&panel, Qt::AlignCenter);
  panel.add_listener(this);
  simulator.add_listener(this);
  connect(ui.chk_in, SIGNAL(clicked()), this, SLOT(check_in_clicked()));
  connect(ui.chk_out, SIGNAL(clicked()), this, SLOT(check_out_clicked()));
  connect(ui.btn_start, SIGNAL(clicked()), this, SLOT(execute()));
}

void Grid_Window::panel_clicked()
{
  if (not editable)
    return;
  Grid::Node * s = panel.get_selected();
  if (s == NULL)
    {
      ui.chk_in->setChecked(false);
      ui.chk_in->setEnabled(false);
      ui.chk_out->setChecked(false);
      ui.chk_out->setEnabled(false);
    }
  else
    {
      ui.chk_in->setChecked(s->is_in());
      ui.chk_in->setEnabled(true);
      ui.chk_out->setChecked(s->is_out());
      ui.chk_out->setEnabled(true);
    }
}

void Grid_Window::check_in_clicked()
{
  Grid::Node * s = panel.get_selected();
  s->is_in() = ui.chk_in->isChecked();
  if (s->is_in())
    simulator.add_entrance(s);
  else
    simulator.remove_entrance(s);
  panel.update();
}

void Grid_Window::check_out_clicked()
{
  Grid::Node * s = panel.get_selected();
  s->is_out() = ui.chk_out->isChecked();
  if (s->is_out())
    simulator.add_exit(s);
  else
    simulator.remove_exit(s);
  panel.update();
}

void Grid_Window::step()
{
  panel.update();
}

void Grid_Window::start()
{
  editable = false;
  ui.btn_start->setEnabled(false);
  ui.chk_in->setEnabled(false);
  ui.chk_out->setEnabled(false);
}

void Grid_Window::stop()
{
  editable = true;
  ui.btn_start->setEnabled(true);
  ui.chk_in->setEnabled(panel.get_selected() != NULL);
  ui.chk_out->setEnabled(panel.get_selected() != NULL);
}

void Grid_Window::execute()
{
  simulator.step();
}
