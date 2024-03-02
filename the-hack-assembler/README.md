# My own version of The Hack Assembler implemented in  Go

This is my own implementation of the Hack Assembler in Go. 

## Hack Assembly language
The Hack Assembler is a program that translates Hack Assembly code `.asm` into Hack Machine code `.hack`.
The Hack Assembly language is a simple language that is used to write programs for the Hack computer, which is a simple computer architecture that is used in the book [The Elements of Computing Systems](https://www.goodreads.com/book/show/910789.The_Elements_Of_Computing_Systems) by Noam Nisan and Shimon Schocken.


## How to use

```bash
./assembler <input-file.asm>
```

#### Example
```bash
./assembler examples/MaxL.asm
```