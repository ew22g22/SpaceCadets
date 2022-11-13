#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <memory>
#include <array>
#include <string>

#include "netlib.hpp"

namespace protocol
{
  enum Packets : int
  {
    PACKETS_SERVERBOUND_REQUEST_USERNAME = 0,
    PACKETS_SIZE,
  };
}

#endif