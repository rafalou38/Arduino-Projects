width = 4








y = ligne = C4 = 2
x = C5 = colone = 3
height = C2 = 4

leds = [0] * width * height

pos = x * height + (((height - y) - 1) if ((x % 2) == 0) else y)
# pos = C5 * C2 + (((C2 - C4) - 1) if ((C5 % 2) == 0) else C4)

leds[pos] = 1

print(pos, end="\n\n")

print(leds[3], leds[4], leds[11], leds[12])
print(leds[2], leds[5], leds[10], leds[13])
print(leds[1], leds[6], leds[9], leds[14])
print(leds[0], leds[7], leds[8], leds[15])
