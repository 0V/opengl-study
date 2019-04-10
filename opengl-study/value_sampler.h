#pragma once
#include <random>

template <typename T>
class ValueSampler
{
private:
    using ThisType = ValueSampler<T>;
    mutable std::random_device seed_gen_;
    mutable std::mt19937 engine_ = std::mt19937(seed_gen_());
    mutable std::uniform_real_distribution<T> dist_;

public:
    ValueSampler(ThisType&& o) noexcept { }
    ValueSampler(T min, T max) : dist_(std::uniform_real_distribution<T>(min, max)) {}

    double sample() const
    {
        return dist_(engine_);
    }
};

template <>
class ValueSampler<int>
{
private:
    using ThisType = ValueSampler<int>;
    mutable std::random_device seed_gen_;
    mutable std::mt19937 engine_ = std::mt19937(seed_gen_());
    mutable std::uniform_int_distribution<int> dist_;

public:
    ValueSampler(ThisType&& o) noexcept { }
    ValueSampler(int min, int max) : dist_(std::uniform_int_distribution<int>(min, max)) {}

    double sample() const
    {
        return dist_(engine_);
    }
};
