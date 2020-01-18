#include "library/server.h"

#include <bits/stdc++.h>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


using namespace std;
using namespace boost::asio;
using namespace chrono;

using boost::asio::ip::tcp;

int main() {
  try
  {
      TServer server("127.0.0.1", "8080");
      cout << "start\n";
      server.Run();
      cout << "end\n";
  }
  catch (std::exception& e)
  {
      std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
