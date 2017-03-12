# Need for Speed: World Web Tools
#### A web interface for a few (maybe) handy tools.

---

## Prerequisites

#### To run:
- Java 8

#### To build fully:

- Java 8 (again)
- Gradle
- GCC or Clang (See note #3)
- [Yarn](https://yarnpkg.com) or NPM (dependencies in `package.json`)
- [Webpack](https://webpack.github.io/)
- Patience

#### Notes
1. Make sure the native library is in the same folder as the .jar!!! The native library should be called: `libwebtools.dylib` on Mac OS X, `libwebtools.so` on Linux, or `webtools.dll` on Windows.
2. On Linux systems, when running the .jar you need to run it with this command: `java -Djava.library.path=. -jar nameofjarhere.jar` in order for it to work.
Not sure why, and it doesn't seem like there's any _easy_ way to get around it.
3. Don't complain if the native libraries won't compile on Windows, because I haven't even added the appropriate code to `build.gradle` for that.

## Features

- `NFSWO_COMMUNICATION_LOG.txt` and `SystemSettings.dat` decryption
- BaseCarId calculator
- PhysicsProfileHash calculator

## Screenshots

![Log Decrypter #1](http://i.imgur.com/LamFyCZ.png)

![Log Decrypter #2](http://i.imgur.com/glLu8jj.png)

![BaseCarId](http://i.imgur.com/6dMlhl2.png)

![PhysicsProfileHash](http://i.imgur.com/o4TfeTO.png)

## Credits

- BaseCarIds and PhysicsProfileHashes: https://github.com/berkay2578/nfsw-server/blob/master/OfflineServer/CarDefinitions.cs
- Initial project base: https://github.com/kolorobot/spring-boot-thymeleaf
- Decryption code (modified by me): https://github.com/ArmsOfSorrow/nfsw-decrypt/blob/master/decrypt.cpp

# Enjoy! 

\* Pull requests are welcome.