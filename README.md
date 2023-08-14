
mSTL is a library for creating safe tasks, queues and other useful things for the esp32, in c ++.

Many of the standard STL containers are replaced with their own optimized versions. Recognizable by its own namespace mn.
All containers, such as vector, list, queue, rb-tree  can be found in the namespace mn::container.

Various types of association classes are provided for simplicity. This is just the exchange of the used allocator from the system to the Spiram allocator, whereby certain regions can be swapped out to a different storage capacity without having to rewrite the entire program.
Certain allocation in addition to a limit, the bytes used to be limited.
All allocator find you under the namespace mn::memory.

The containers and pointers use as default the mn::memory::default_allocator_t.

For network programming see mn::net. (net/mn_socket.hpp) they contains a asy to use network socket wrapper for lwip,
IPv4 and IPv6 support. Currently only dgram_socket_ip{4,6} and  stream_socket_ip{4,6} support, raw socket are follow in version 2.30, with class for wifi AP and Wifi STA support

For tickhooks please activated CONFIG_FREERTOS_LEGACY_HOOKS in your sdkconfig !!

## Folder Strutur
- include and src:
  - / : all basics: task, semaphores. timer ...
  - memory: mempool handling
  - queue: FreeRTOS queue's and workqueue-engines
  - slock: ystem interrupt, schedular and ...  autolock helper
- doc: Files to create the docu with doxygen
  - The online pre builded version: [https://roseleblood.github.io/mnthread-docs/](https://roseleblood.github.io/mnthread-docs/)
- example; The basic's example, and for more see extra repository: [mnthread-examples](https://github.com/RoseLeBlood/mnthread-examples)

## Using
Build from git from
1. ```sh ./configure or ./configure --prefix=<path> # without prefix then install to /opt```
2. ```sh make build ```
3. ```sh sudo or doas make install ```
4. ```add  "lib_deps = /opt/mtSTL/mtSTL-2.*.tar.gz"  to your platformio.ini```

### Example
```ini
[env:esp-wrover-kit]
platform = espressif32
board = esp-wrover-kit
framework = espidf
lib_deps = /opt/mtSTL/mtSTL-2.*.tar.gz

```
## Using from platformio
```ini
# platformio.ini – project configuration file

[env:my_build_env]
platform = espressif32
framework = espidf
lib_deps =
  # RECOMMENDED
  # Accept new functionality in a backwards compatible manner and patches
   mstlhost/mstl @ ^3.0.0

  # Accept only backwards compatible bug fixes
  # (any version with the same major and minor versions, and an equal or greater patch version)
  mstlhost/mstl @ ~3.0.0 

  # The exact version
  mstlhost/mstl @ 3.0.0 

```

## ChangeLog

For more see [ChangeLog](ChangeLog.md)


## Contributing

We would love for you to contribute to mtSTL and help make it even better than it is today! See our [Contributing Guidelines](CONTRIBUTING.md) for more information.

Contributors are required to abide by our [Code of Conduct](CODE_OF_CONDUCT.md) and [Coding Conventions and Style Guide](STYLE_GUIDE.md).

# Versioning

mtSTL follows the [Semantic Versioning guidelines](http://semver.org/) for release cycle transparency and to maintain backwards compatibility.

## License

mtSTL is released under the [LGPL](LICENSE.md) file for more information.
