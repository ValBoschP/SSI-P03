# SSI-P03
# Práctica 3: Generador CHACHA20
## Objetivo
Implementar el Generador ChaCha20 usado en SSL/TLS.

## Desarrollo
Implementa el generador ChaCha20 según la descripción incluida en las transparencias pero siguiendo el RFC7539 disponible en [DataTracker](https://datatracker.ietf.org/doc/html/rfc8439)

<image src="/docs/chacha.PNG" alt="CHACHA20 Algorithm">

## Ejemplo
### Entrada:
- **Clave** de *256 bits* en forma de 8 palabras en hexadecimal 

`00:01:02:03: 04:05:06:07: 08:09:0a:0b: 0c:0d:0e:0f: 10:11:12:13: 14:15:16:17: 18:19:1a:1b: 1c:1d:1e:1f`

- **Contador** de *32 bits* en forma de 1 palabra en hexadecimal = `01:00:00:00`
- **Nonce** aleatorio de *96 bit*s en forma de 3 palabras en hexadecimal =  
`00:00:00:09: 00:00:00:4a: 00:00:00:00`

### Salida:
- **Estado inicial** =
```
61707865 3320646e 79622d32 6b206574
03020100 07060504 0b0a0908 0f0e0d0c
13121110 17161514 1b1a1918 1f1e1d1c
00000001 09000000 4a000000 00000000
```
- **Estado final tras las 20 iteraciones** = 
```
837778ab e238d763 a67ae21e 5950bb2f
c4f2d0c7 fc62bb2f 8fa018fc 3f5ec7b7
335271c2 f29489f3 eabda8fc 82e46ebd
d19c12b4 b04e16de 9e83d0cb 4e3c50a2
```
- **Estado de salida del generador** =
```
e4e7f110 15593bd1 1fdd0f50 c47120a3
c7f4d1c7 0368c033 9aaa2204 4e6cd4c3
466482d2 09aa9f07 05d7c214 a2028bd9
d19c12b5 b94e16de e883d0cb 4e3c50a2
```