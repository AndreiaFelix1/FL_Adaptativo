from PIL import Image
from glob import glob 

all_png = glob("*.eps")
for img in all_png:
    im=Image.open(img)
    im = im.resize((1507,1276), resample=Image.NEAREST)
    im.save("R_"+img)
