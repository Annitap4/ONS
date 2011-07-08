# ifndef STATISTICS_H
# define STATISTICS_H

# include <statistics_per_element.H>
# include <cstdio>

class Statistics
{
  struct Pair_Of_List
  {
    DynDlist<Statistics_Per_Element> statistics_per_package;
    DynDlist<Statistics_Per_Element> statistics_per_node;
  };

  static Statistics * instance;

  unsigned long num_iterations;
  unsigned long generate_packages;
  unsigned long deliveried_packages;

  DynDlist<Pair_Of_List> events_list_per_iteration;

  Statistics();

  Statistics_Per_Element * search_package_statistic(std::string &);

  Statistics_Per_Element * search_node_statistic(std::string &);

public:

  ~Statistics();

  const unsigned long & get_num_iterations() const
  {
    return num_iterations;
  }

  const unsigned long & get_generate_packages() const
  {
    return generate_packages;
  }

  const unsigned long & get_deliveried_packages() const
  {
    return deliveried_packages;
  }

  const unsigned long & get_on_grid_packages() const
  {
    return generate_packages - deliveried_packages;
  }

  static Statistics * get_instance();

  void inc_iterations();

  void inc_generate_packages();

  void inc_deliveried_packages();

  void add_statistic_to_node(std::string &, std::string &);

  void add_statistic_to_package(std::string &, std::string &);

  void print();

  void clear();

  void init();
};

#endif // STATISTICS_H
