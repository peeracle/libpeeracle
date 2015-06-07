import os
import sys

for root, dirs, files in os.walk(sys.argv[1]):
    for file in files:
        if file.endswith(".lib"):
             print(os.path.join(root, file).replace('\\','\\\\'))
