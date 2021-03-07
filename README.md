# My arduino projects

create a link to a library:

```powershell
new-item -itemtype symboliclink -path .\precision_game\ -name leds -value .\leds\

# or

gsudo
new-item -itemtype symboliclink -path .\precision_game\ -name "leds.h" -value .\leds\leds.h
new-item -itemtype symboliclink -path .\precision_game\ -name "leds.ino" -value .\leds\leds.ino
```
