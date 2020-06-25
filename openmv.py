import sensor, image, time, os, tf
import pyb

sensor.reset()                         # Reset and initialize the sensor.
sensor.set_pixformat(sensor.RGB565)    # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)      # Set frame size to QVGA (?x?)
sensor.set_windowing((240, 240))       # Set 240x240 window.
sensor.skip_frames(time=2000)          # Let the camera adjust.

labels = ['3', '4', '0', 'other']


img = sensor.snapshot()


for obj in tf.classify('/model_demo.tflite',img, min_scale=1.0, scale_mul=0.5, x_overlap=0.0, y_overlap=0.0):

    for i in range(len(obj.output())):

        print("%s = %f" % (labels[i], obj.output()[i]))

while(True):
    status = uart.readline()
    print(status.decode())
    frame += a.decode()

    if frame == "image_classification":

        label = image_classification()
        uart.write(label.encode())


    if frame == "data":

        clock.tick()
        img = sensor.snapshot()
        img.lens_corr(1.8) # strength of 1.8 is good for the 2.8mm lens. 
        matrices = img.find_datamatrices()

        for matrix in matrices:
            img.draw_rectangle(matrix.rect(), color = (255, 0, 0))
            print_args = ((180 * matrix.rotation()) / math.pi)
            uart.write(("%1.3f\r\n" % print_args).encode())
