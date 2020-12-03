# retry with c++

A Retry policy with >c++11 implementation.

## Features

### Retry
`retry` can be used to make a more human-reading _retry_ flow. (influented by idiomatic Go code. I love Go :-))

### Example

```c++11
/**
* Retry something with _withN_ times at maximum, run _withRoll_ if failed.
*/
void function() {
    int n = 0;
    retry([&](){
        std::cout << "hello world with " << n << std::endl;
        return (n++ > 3) ? true : false;
    })
    .withRoll([&](){
        std::cout << "bye world" << std::endl;
    })
    .withN(2)
    .run();
}
```

Output:
```
hello world with 0
hello world with 1
bye world

```

## Compilation

### Library
The library is header only, so it doesn't need to be compiled. Just include the header file when you need it.

### Test cases

To compile the test cases, you need:
* CMake

```sh
mkdir test/build
cd test/build
cmake ../
make
./retry_test
```
## License
MIT
