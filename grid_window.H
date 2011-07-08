# ifndef GRID_WINDOW_H
# define GRID_WINDOW_H

# include <QtGui>

# include <ui_grid_form.h>

# include <grid_panel.H>

# include <grid_panel_listener.H>
# include <sim_listener.H>


class Grid_Window : public QWidget, Grid_Panel_Listener, Sim_Listener
{
Q_OBJECT

  Simulator simulator;

  Grid_Panel panel;

  Ui_Grid_Form ui;

  bool editable;

public:
  explicit Grid_Window(QWidget * parent = 0);

  void panel_clicked();

  void step();

  void start();

  void stop();

public slots:
  void check_in_clicked();

  void check_out_clicked();

  void execute();
};

# endif // GRID_WINDOW_H
