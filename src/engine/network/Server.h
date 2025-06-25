#ifndef MACRO_NETWORK_SERVER_H_
# define MACRO_NETWORK_SERVER_H_

namespace macro {
  namespace network {
    class Server {
      public:
        inline Server() {}
        virtual inline ~Server() {}

        int run();
    };
  }
}

#endif // !MACRO_NETWORK_SERVER_H_
