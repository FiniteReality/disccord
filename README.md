# disccord #
A discord library written in C

Join the development server: [![Discord](https://discordapp.com/api/guilds/226692368148070420/widget.png)](https://discord.gg/syNMXxM)

## Dependencies ##

- [libwebsockets](https://libwebsockets.org/)
- [libcurl](https://curl.haxx.se/libcurl/)
- [openssl](https://www.openssl.org/)
- [libsodium](https://download.libsodium.org/doc/)

On Debian Jessie you can retrieve these using:
```shell
sudo apt-get install libwebsockets-dev libcurl4-openssl-dev libssl-dev \
libsodium-dev
``` 

## Building ##
Building should be as simple as using the included makefile:

```shell
$make all
```

## Contributing ##

Help needed. Lots of it.

### Testing ###

Valgrind is needed to run tests.

Please test your code before committing. Use the `make test` command to test
your code to ensure that it works correctly.