# Simple Key-Value Store

## Description
- this project is part of [OSTEP projects](https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/initial-kv)
- implementing the key-value store in C, [project description](https://github.com/remzi-arpacidusseau/ostep-projects/blob/master/initial-kv/README.md)
- 
### How to compile
```bash
gcc -o kv kv.c hashmap.c hashmap.h -Wall
```

### Examples
```bash
./kv p,key1,value1 p,key2,value2 p,key3,value3
```

```bash
./kv g,key3
```
 