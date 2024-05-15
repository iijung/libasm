# libasm

Intel 문법으로 작성된 어셈블리 함수들을 [nasm](https://www.nasm.us/)으로 컴파일하여 라이브러리로 만들어보는 프로젝트입니다.

## Compile

```bash
$ make
$ make bonus
$ make fclean      # remove libasm.a
$ make fclean_nasm # remove nasm
```

## Usage
```bash
$ vi main.c
$ cc -L. main.c -lasm -o main
$ ./main
```
