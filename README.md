# Pocketsphinx demo

## Compile from sources

### Step 1: MATRIXIO Software

``` bash 
curl https://apt.matrix.one/doc/apt-key.gpg | sudo apt-key add -
echo "deb https://apt.matrix.one/raspbian $(lsb_release -sc) main" | sudo tee /etc/apt/sources.list.d/matrixlabs.list
sudo apt update
sudo apt upgrade

sudo apt install matrixio-creator-init matrixio-kernel-modules libmatrixio-creator-hal-dev matrixio-pocketsphinx
sudo reboot
```

### Step 2: Building PocketSphinx demos
``` 
git clone https://github.com/matrix-io/matrix-creator-pocketsphinx.git
cd matrix-creator-pocketsphinx
mkdir build && cd build && cmake .. && make -j $(nproc)
```

### Step 3: Install testing voice commands:
Download sample language and dictionary from [here](https://drive.google.com/file/d/0B3lA7p7SjZu-YUJxYmIwcnh4Qlk/view?usp=sharing) and transfer it to your Pi on `matrix-creator-pocketsphinx/build/demos` directory and then extract it:

``` bash
mkdir assets
tar zxf TAR6706.tgz -C assets
```

**NOTE**: Optional, you can make new models [explanation below](https://github.com/matrix-io/matrix-creator-pocketsphinx#optional-custom-lenguage-and-phrases-for-recognition)

### Step 4: Run DEMO:
on build/demos:
```
./pocketsphinx_demo -keyphrase "MATRIX" -kws_threshold 1e-20 -dict assets/6706.dic -lm assets/6706.lm -inmic yes
``` 
and try it with executing commands with your voice like this: 

- `matrix everloop`
- `matrix stop`
- `matrix clear`
- ...

### (optional) Custom lenguage and phrases for recognition 

+ Make a text plane like this: 
``` 
matrix
everloop
arc 
clear
stop
shutdown
now
ipaddress
matrix everloop
matrix clear
matrix stop
matrix ipaddress
matrix game time
matrix one minute
matrix two minutes
matrix three minutes
matrix four minutes
matrix five minutes
matrix ten seconds
matrix ten minutes
```

+ Upload this file to [Sphinx Knowledge Base Tool](http://www.speech.cs.cmu.edu/tools/lmtool-new.html) and compile knowledge base.

+ Dowload *TARXXXXX.tgz* and upgrade assets. 

