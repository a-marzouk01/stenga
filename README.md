# stenga
A stack based programming language

* `main.c` - the compiler itself
* `libs/dray` - a dynamic-array library [link](https://github.com/a-marzouk01/dynamic-arrays)


---

## Requirements

Linux x86\_64:

* `gcc`
* `make`
* `nasm`

Install on Debian/Ubuntu:

```bash
sudo apt update
sudo apt install build-essential nasm
```

---

## RUNNING

Everything is in the Makefile

### build the code 

```bash
make
```

### Run the code as a simulation 

```bash
make run ARGS="sim"
```

or

```bash
make run-sim
```

### Compile the code to assembly

```bash
make run ARGS="com"
```

or

```bash
make run-com
```

### Assemble & link the generated assembly

```bash
make run-asm
```

### 5. Clean everything

```bash
make clean
```

---
