## 1. Insall & Setup Environment
``` python
git clone --recursive https://github.com/espressif/esp-idf

cd esp-idf

./install.sh 

. ./export.sh  # each time open esp-idf always run this line to use idf.py
```

## 2. Create & build and upload program to MCU
``` python
idf.py create-project your_project_name
cd your_project_name
idf.py set-target esp32s3 #or the mcu you use, ex: esp32, esp32s2, ...
idf.py build # build your program
idf.py flash # upload your program to mcu
idf.py -p PORT flash # upload if you use 2 or more mcu same time. PORT will be your mcu port in use
idf.py monitor # turn on terminal to see output
```