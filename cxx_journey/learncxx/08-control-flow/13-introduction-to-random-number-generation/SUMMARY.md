# Conclusion

In generela there is no algorithm for pure random generation. All of this are called **pseudo random number generator** or **PRNG**.

In our days using an old algo like std::rand(), knuth_b or default_random_engine is a bad idea. As they are so deterministic and predictible.

If you don't have to make some system with strong random generation you can use a **mt_19937** and **mt_19937** algo. In case when you need PRNG for strong random generation or more flexible and cryptographic, please use a third-party libraries such as the **Xoshiro family** and **Wayrand** for non-cryptographic PRNGs and the **Chacha family** for cryptographic (non-predictable) PRNGs.

