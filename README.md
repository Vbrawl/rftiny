
# RFTINY

RFTINY is an RF protocol designed to require as little resources as possible.
The goal is to support microcontrollers such as ATtiny10.

# PACKET

```
| SYN | GID | CODE |
```

Fields:
* GID (8 bits): A code that's used for synchronization and grouping
* CODE (8 bits): The code to send as data