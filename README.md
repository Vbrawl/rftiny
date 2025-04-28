
# RFTINY

RFTINY is an RF protocol designed to require as little resources as possible.
The goal is to support microcontrollers such as ATtiny10.

# PACKET

```
| SYNGID | CODE |
```

Fields:
* SYNGID (8 bits): A byte that helps distinguish noise from data, and device groups
* CODE (8 bits): The code to send as data
