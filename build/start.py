import os
# os.system('tree')
os.system('cmake ..')
os.system('make')
os.system('./Render')
os.system('display ../photo.ppm')
