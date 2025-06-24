#ifndef MACRO_NETWORK_CLIENT_H_
# define MACRO_NETWORK_CLIENT_H_

namespace macro {
  namespace network {
    class Client {
      public:
        inline Client() {}
        virtual inline ~Client() {}

        int run();
    };
  }
}

#endif // !MACRO_NETWORK_CLIENT_H_
