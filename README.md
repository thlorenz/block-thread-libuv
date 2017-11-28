# libuv-threading

Sandbox to play with different pthread threading features exposed by libuv

## Simple Version, One main file

```sh
git checkout simple-main
make main
./bin/main /dev/random
```

## Reader + Writer Classes

```sh
git checkout reader+writer 
make main
./bin/main /dev/random
```

## Reader + Writer combined into a Writable Class

```sh
git checkout writable 
make main
./bin/main /dev/random
```

## Writable JSON SAX parser

This parser supports pushing chunks to it asynchronously via the `writable.write`.
It will block the reader thread if it runs out of chunks and waits until the main thread pushes
more data.

```sh
git checkout json-parser 
make main
./bin/main <path>/<to>/<file.json> 
```

## License

MIT
