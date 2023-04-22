import os

os.chdir("/tmp")

for i in range(100):
     os.system("wget -r localhost:80")

