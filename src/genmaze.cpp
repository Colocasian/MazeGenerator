#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <boost/program_options/variables_map.hpp>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include <unistd.h>

#include "MazeGenerator/maze_algos.hpp"
#include "MazeGenerator/maze_print.hpp"
#include "MazeGenerator/version.h"

namespace po = boost::program_options;

int error_prompt(char *argv[]) {
  std::cerr << argv[0] << ": do `mazer -h` for help" << std::endl;
  return 1;
}

int error_prompt(char *argv[], const char *e) {
  std::cerr << argv[0] << ": " << e << '\n';
  return error_prompt(argv);
}

int main(int argc, char *argv[]) {
  std::string algo;
  std::string printer;
  std::size_t x = 0;
  std::size_t y = 0;
  unsigned int seed;

  po::options_description generic("Generic options");
  generic.add_options()("version", "print version string")(
      "help,h", "produce help message");

  po::options_description mz_desc("Setting maze parameters");
  mz_desc.add_options()("algo,a", po::value<std::string>(&algo),
                        "algorithm used for maze generation")(
      "print-style,p", po::value<std::string>(&printer)->default_value("block"),
      "printing style used to print maze")(
      "width,x", po::value<std::size_t>(&x), "set width of main maze grid")(
      "height,y", po::value<std::size_t>(&y),
      "set height of main maze grid")("seed,s", po::value<unsigned int>(&seed),
                                      "set seed (randomised if not specified)");

  po::options_description cmd_line_opts(std::string("MazeGenerator v") +
                                        MAZER_VERSION);
  cmd_line_opts.add(generic).add(mz_desc);

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, cmd_line_opts), vm);
  po::notify(vm);

  if (vm.count("version")) {
    std::cout << "Maze Generator v" << MAZER_VERSION << std::endl;
    return 0;
  }
  if (vm.count("help")) {
    std::cout << cmd_line_opts << std::endl;
    return 0;
  }

  if (x <= 0 || y <= 0)
    return error_prompt(argv, "invalid maze dimensions");

  mbit *mz = new mbit[((x - 1) * y + x * (y - 1) + BSZ - 1) / BSZ];

  if (!vm.count("seed")) {
    seed = (std::random_device())();
    std::cout << "Seed used was " << seed << std::endl;
  }

  if (algo == "kruskal")
    kruskal_gen(mz, x, y, seed);
  else if (algo == "dfs")
    dfs_gen(mz, x, y, seed);
  else if (algo == "recurse_div")
    recurse_div_gen(mz, x, y, seed);
  else if (algo == "wilson")
    wilson_gen(mz, x, y, seed);
  else
    return error_prompt(argv, "Invalid algorithm name");

  if (printer == "block")
    printmaze_block(mz, x, y);
  else if (printer == "thinwall")
    printmaze_thinwall(mz, x, y);
  else
    return error_prompt(argv, "Invalid printing style");

  std::cout << std::flush;
}
