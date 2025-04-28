
# RFTINY

RFTINY is an RF protocol designed to require as little resources as possible.
The goal is to support microcontrollers such as ATtiny10.

# PACKET

```
| SYN | GID | CODE |
```

Fields:
* SYN (8 bits): A synchronization byte, helps distinguish noise from data
* GID (8 bits): A code used for grouping
* CODE (8 bits): The code to send as data
