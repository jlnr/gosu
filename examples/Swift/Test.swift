import Gosu

print("Hello, Gosu! \(Gosu.VERSION)")

let random = Gosu.random(0, 100)
print("Random: \(random)")

let color = Gosu.Color(0, 0, 0)
print("Color: \(color.red), \(color.green), \(color.blue), \(color.alpha)")

let bitmap = Gosu.Bitmap(100, 100, Gosu.Color.RED)
print("Bitmap: \(bitmap.width()), \(bitmap.height())")

let image = Gosu.Image("media/Starfighter.bmp", 0)
print("Image: \(image.width()), \(image.height())")

let sample = Gosu.Sample("media/Beep.wav")
sample.play(1, 1, false)

// TODO: Implement support for the Window class
//var window = Gosu.Window(640, 480, 0, 16.666666)

Gosu.sleep(500)
