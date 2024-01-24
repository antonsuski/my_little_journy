# Conclustion

The `mt19937` algorithm is prity old. But still wokrs.

For more conviniet generating of random numbers use seeding. With out seed the RPNGs will genrate seme sequence evry time when you run your program.

Do not reseeding your RPNG becuse it cause to increase chance to make the same random numbers sequence as previouse. Or repeat it at all. Also it will reduse dedicated random numbers of std::random_device.

Remeber that the internal state of mt19937 algorithm is 626 bytes size. And try to seed it not all but most part or more than with one 4 byte value. In other case underseeding issues will accure.

