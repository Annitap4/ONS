# include <statistics.H>

Statistics * Statistics::instance = NULL;

Statistics::Statistics()
  : num_iterations(0), generate_packages(0), deliveried_packages(0)
{
  // Empty
}

Statistics::~Statistics()
{
  if (instance != NULL)
    delete instance;
}

Statistics * Statistics::get_instance()
{
  if (instance == NULL)
    instance = new Statistics();
  return instance;
}

void Statistics::inc_iterations()
{
  ++num_iterations;
  events_list_per_iteration.append(Pair_Of_List());
}

void Statistics::inc_generate_packages()
{
  ++generate_packages;
}

void Statistics::inc_deliveried_packages()
{
  ++deliveried_packages;
}

void Statistics::add_statistic_to_node(std::string & node_name, std::string & statistic)
{
  Statistics_Per_Element * s = search_node_statistic(node_name);
  if (s == NULL)
    s = &(events_list_per_iteration.get_last().statistics_per_node.append(Statistics_Per_Element(node_name)));
  s->add_statistic(statistic);
}

void Statistics::add_statistic_to_package(std::string & package_name, std::string & statistic)
{
  Statistics_Per_Element * s = search_package_statistic(package_name);
  if (s == NULL)
    s = &(events_list_per_iteration.get_last().statistics_per_package.append(Statistics_Per_Element(package_name)));
  s->add_statistic(statistic);
}

Statistics_Per_Element * Statistics::search_package_statistic(std::string & name)
{
  DynDlist<Statistics_Per_Element> & statistics_per_package = events_list_per_iteration.get_last().statistics_per_package;
  for (DynDlist<Statistics_Per_Element>::Iterator it(statistics_per_package); it.has_current(); it.next())
    {
      Statistics_Per_Element & s = it.get_current();
      if (s.get_element_name() == name)
        return &s;
    }
  return NULL;
}

Statistics_Per_Element * Statistics::search_node_statistic(std::string & name)
{
  DynDlist<Statistics_Per_Element> & statistics_per_node = events_list_per_iteration.get_last().statistics_per_node;
  for (DynDlist<Statistics_Per_Element>::Iterator it(statistics_per_node); it.has_current(); it.next())
    {
      Statistics_Per_Element & s = it.get_current();
      if (s.get_element_name() == name)
        return &s;
    }
  return NULL;
}

# include <iostream>

void Statistics::print()
{
  std::cout << "Resultados de la Simulacion" << std::endl << std::endl;
  std::cout << "Numero de iteraciones: " << get_num_iterations() << std::endl;
  std::cout << "Numero de paquetes generados: " <<  get_generate_packages() << std::endl;
  std::cout << "Numero de paquetes entregados: " << get_deliveried_packages() << std::endl;
  std::cout << "Numero de paquetes en movimiento: " << get_on_grid_packages() << std::endl << std::endl;

  std::cout << "Resultados por paquete" << std::endl << std::endl;
  unsigned long i = 0;
  for (DynDlist<Pair_Of_List>::Iterator it(events_list_per_iteration); it.has_current(); it.next(), ++i)
    {
     if (i > 0)
       std::cout << "Iteracion numero " << i << std::endl << std::endl;
     else
       std::cout << "Estado inicial" << std::endl << std::endl;
      DynDlist<Statistics_Per_Element> & statistics_per_package = it.get_current().statistics_per_package;
      for (DynDlist<Statistics_Per_Element>::Iterator it(statistics_per_package); it.has_current(); it.next())
        {
          Statistics_Per_Element & s = it.get_current();
          std::cout << "Paquete: " << s.get_element_name() << std::endl;
          DynDlist<std::string> & h = s.get_history();
          for (DynDlist<std::string>::Iterator it(h); it.has_current(); it.next())
            {
              std::string & st = it.get_current();
              std::cout << "Evento: " << st << std::endl;
            }
          std::cout << std::endl;
        }
    }
}

void Statistics::clear()
{
  num_iterations = generate_packages = deliveried_packages = 0;
  events_list_per_iteration.empty();
}
void Statistics::init()
{
  events_list_per_iteration.append(Pair_Of_List());
}
