import os
from PIL import Image

path = os.getcwd()
for root, dirs, files in os.walk(path, topdown=False):
    i = 1
    for name in files:
        extention = os.path.splitext(os.path.join(root, name))[1].lower()
        if extention == ".tif":
            if os.path.isfile(os.path.splitext(os.path.join(root, name))[0] + ".jpg"):
                print("A jpeg file already exists for ",  name)
            else:
                print("else")
                outfile = os.path.splitext(os.path.join(root, name))[0] + ".jpg"
                try:
                    im = Image.open(os.path.join(root, name))
                    print("Generating jpeg for ", name)
                    im.thumbnail(im.size)
                    im.save(str(i)+ ".jpg", "JPEG", quality=100)
                    i = i+1
                except Exception:
                    print(sys.exc_info()[0])
