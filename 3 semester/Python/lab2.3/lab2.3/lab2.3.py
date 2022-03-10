import os

for top, dirs, files in os.walk(os.getcwd()):
    for nm in files:       
        print (os.path.join(top, nm))