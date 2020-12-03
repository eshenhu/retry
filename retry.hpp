#if !defined(RETRY_FUNCTION_HPP_INCLUDED)
#define RETRY_FUNCTION_HPP_INCLUDED

#include <functional>

namespace detail {

namespace {
/**
 * @brief 
 * 
 * @tparam F 
 * @tparam R 
 */

template <typename F, typename R = std::function<void()>>
class retry_tails {
  public:
    retry_tails(F &&lambda) : fn(std::forward<F>(lambda)) {}

    retry_tails(retry_tails &&) = delete;
    retry_tails(const retry_tails &) = delete;
    retry_tails &operator=(const retry_tails &) = delete;
    retry_tails &operator=(retry_tails &&) = delete;

    template <typename Func>
    retry_tails<F> &withRoll(Func &&lambda) {
        this->roll = lambda;
        return *this;
    }

    retry_tails<F> &withN(int n) {
        this->retry_count = n;
        return *this;
    }

    void run() {
        int n = 0;
        for (; n < this->retry_count; ++n) {
            if (this->fn())
                break;
        }
        if (n == this->retry_count && this->roll) {
            this->roll();
        }
    }

  private:
    F fn;
    R roll = nullptr;
    int retry_count = 0;
};

} // namespace
} // namespace detail

template <typename F>
detail::retry_tails<F> retry(F &&lambda) {
    return {std::forward<F>(lambda)};
}

#endif // RETRY_FUNCTION_HPP_INCLUDED