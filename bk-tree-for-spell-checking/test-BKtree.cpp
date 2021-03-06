#include <iostream>
#include <fstream>
using namespace std;

#include <boost/archive/text_oarchive.hpp>

#include "BKtree.h"
#include "levenshtein_distance.h"

int main(int argc, char const *argv[])
{
  if (argc <= 1) {
    cerr << "Usage: " << argv[0] << " <dict> <query> <tolerance> [serialize]\n";
    return 1;
  }
  ifstream ifs(argv[1]);
  if (!ifs) {
    cerr << "File '" << argv[1] << "' not exist!\n";
    return 2;
  }

  BKTree tree(ifs);

  auto result = tree.search(argv[2], atoi(argv[3]));
  copy(result.begin(), result.end(), 
    ostream_iterator<decltype(result)::value_type>(cout, " "));
  cout << "\n";

  // serialize the tree
  if (argc >= 5) {
    std::ofstream ofs(argv[4]);
    boost::archive::text_oarchive oa(ofs);
    // write class instance to archive
    oa << tree;
    // archive and stream closed when destructors are called
    cout << "Dict serialized to '" << argv[4] << "'\n";
  }

  return 0;
}