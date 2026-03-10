#pragma once

#include <memory>

using ull = unsigned long long;

class PlayerScore
{
  public:
    ull userId = 0;
    int score = 0;

    bool operator==(const PlayerScore& other) const
    {
        return userId == other.userId;
    }

    static bool psCmp(const PlayerScore&, const PlayerScore&);
};

template <> struct std::hash<PlayerScore>
{
    size_t operator()(const PlayerScore& p) const noexcept
    {
        return std::hash<uint64_t>()(p.userId);
    }
};
