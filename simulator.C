# include <simulator.H>

Simulator::Simulator() : packages_counter(0)
{
  rng = gsl_rng_alloc(gsl_rng_mt19937);
  statistics = Statistics::get_instance();

  std::ifstream cfg_file("simulator.cfg", ios::in);
  if (not cfg_file)
    {
      num_iterations = 10;
      grid_height = 2;
      grid_width = 2;
    }
  else
    cfg_file >> grid_width >> grid_height >> num_iterations;

  grid.set_height(grid_height);
  grid.set_width(grid_width);

  grid.build_automatic_grid();
}

Simulator::~Simulator()
{
  gsl_rng_free(rng);
}

void Simulator::add_entrance(Grid::Node * e)
{
  entrances.append(e);
}

void Simulator::remove_entrance(Grid::Node * e)
{
  for (DynDlist<Grid::Node *>::Iterator it(entrances); it.has_current(); it.next())
    {
      Grid::Node *& curr = it.get_current();
      if (curr == e)
        {
          entrances.remove(curr);
          break;
        }
    }
}

void Simulator::add_exit(Grid::Node * e)
{
  exits.append(e);
}

void Simulator::remove_exit(Grid::Node * e)
{
  for (DynDlist<Grid::Node *>::Iterator it(exits); it.has_current(); it.next())
    {
      Grid::Node *& curr = it.get_current();
      if (curr == e)
        {
          exits.remove(curr);
          break;
        }
    }
}

void Simulator::move_packages()
{
  for (DynDlist<Package>::Iterator it(packages); it.has_current(); )
    {
      Package & package = it.get_current();
      Grid::Node * node = package.get_routed_to();
      it.next();
      if (node == package.get_target_node())
        {
          packages.remove(package);
          std::string pkn = package.to_string();
          std::string node_name = node->to_string();
          std::string stp = gnu::autosprintf("Paquete entregado en su destino %s", node_name.c_str());
          std::string stn = gnu::autosprintf("Entrego al paquete %s", pkn.c_str());
          statistics->add_statistic_to_package(pkn, stp);
          statistics->add_statistic_to_node(node_name, stn);
          statistics->inc_deliveried_packages();
          continue;
        }
      node->add_client(&package);
    }
}

void Simulator::generate_packages()
{
  if (entrances.is_empty() or exits.is_empty())
    return;
  for (DynDlist<Grid::Node *>::Iterator it(entrances); it.has_current(); it.next())
    {
      Grid::Node * node = it.get_current();
      size_t off_set = grid.get_num_arcs(node) - node->get_clients_list().size();
      for (int i = 0; i < off_set; ++i)
        {
          int num_exit = gsl_rng_uniform_int(rng, exits.size());
          Grid::Node * exit = exits[num_exit];
          Package p(packages_counter++, node, exit);
          Package & pack = packages.append(p);
          node->add_client(&pack);
          std::string pkn = pack.to_string();
          std::string node_name = node->to_string();
          std::string tgt_name = exit->to_string();
          std::string stp = gnu::autosprintf("Se creo el paquete %s en el nodo %s con destino %s",
                                             pkn.c_str(), node_name.c_str(), tgt_name.c_str());
          std::string stn = gnu::autosprintf("Se creo el paquete %s con destino %s",
                                             pkn.c_str(), tgt_name.c_str());
          statistics->add_statistic_to_package(pkn, stp);
          statistics->add_statistic_to_node(node_name, stn);
          statistics->inc_generate_packages();
        }
    }
}

void Simulator::step()
{
  statistics->clear();
  statistics->init();
  fire_event(Start);
  for (int i = 0; i < num_iterations; ++i)
    {
      for (Grid::Node_Iterator it(grid); it.has_current(); it.next())
        {
          Grid::Node * curr_node = it.get_current();
          Minimum_Deflecting()(grid, curr_node);
        }
      move_packages();      
      generate_packages();
      statistics->inc_iterations();
    }
  statistics->print();
  fire_event(Stop);
}

void Simulator::add_listener(Sim_Listener * l)
{
  listeners.append(l);
}

void Simulator::fire_event(const Event_Type & evt)
{
  for (DynDlist<Sim_Listener *>::Iterator it(listeners); it.has_current(); it.next())
    switch(evt)
      {
      case Step:  it.get_current()->step(); break;
      case Start: it.get_current()->start(); break;
      case Stop:  it.get_current()->stop(); break;
      }
}
