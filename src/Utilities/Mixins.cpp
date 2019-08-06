// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018, The CrowdInvestNetwork Developers
//
// Please see the included LICENSE file for more information.

/////////////////////////////
#include <Utilities/Mixins.h>
/////////////////////////////

#include <config/CryptoNoteConfig.h>

#include <sstream>

#include <tuple>

#include <Wallet/WalletErrors.h>

namespace Utilities
{
    /* Returns {minMixin, maxMixin, defaultMixin} */
    std::tuple<uint64_t, uint64_t, uint64_t> getMixinAllowableRange(const uint64_t height)
    {
	uint64_t minMixin = 0;
        uint64_t maxMixin = CryptoNote::parameters::DEFAULT_MIXIN;
        uint64_t defaultMixin = CryptoNote::parameters::DEFAULT_MIXIN;

        return {minMixin, maxMixin, defaultMixin};
    }

    /* This method is used by WalletService to determine if the mixin amount is correct
     for the current block height */
    std::tuple<bool, std::string, std::error_code> validate(
        const uint64_t mixin,
        const uint64_t height)
    {
        auto [minMixin, maxMixin, defaultMixin] = getMixinAllowableRange(height);

        std::stringstream str;

        if (mixin < minMixin)
        {
            str << "Mixin of " << mixin << " under minimum mixin threshold of " << minMixin;
            return {false, str.str(), make_error_code(CryptoNote::error::MIXIN_BELOW_THRESHOLD)};
        }
        else if (mixin > maxMixin)
        {
            str << "Mixin of " << mixin << " above maximum mixin threshold of " << maxMixin;
            return {false, str.str(), make_error_code(CryptoNote::error::MIXIN_ABOVE_THRESHOLD)};
        }

        return {true, std::string(), std::error_code()};
    }
}
