#ifndef CONVERTTOOLS_H
#define CONVERTTOOLS_H

#include "cryptopp/osrng.h"

namespace convertTools
{
    std::string byteBlockToHexString(CryptoPP::SecByteBlock data);
    std::string fromHex(std::string encoded);
    std::string toHex(std::string data);
}


#endif // CONVERTTOOLS_H
