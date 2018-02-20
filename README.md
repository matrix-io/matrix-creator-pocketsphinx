# Pocketsphinx demo

## Installation

### Raspbian Dependencies 

Before, please install **MALOS** service on your `RaspberryPi3` and perform device reboot: 

``` bash 
curl https://apt.matrix.one/doc/apt-key.gpg | sudo apt-key add -
echo "deb https://apt.matrix.one/raspbian $(lsb_release -sc) main" | sudo tee /etc/apt/sources.list.d/matrixlabs.list
sudo apt-get update
sudo apt-get upgrade
sudo apt install matrixio-malos-wakeword git build-essential cmake
reboot
```

### Testing that MALOS is running

``` bash
ps aux | grep -i malos
```
output:
``` bash
root       561  5.7  0.9 763616  8908 ?        Ssl  12:26   0:06 /usr/bin/malos
root       562  0.0  0.5 122220  5640 ?        Ssl  12:26   0:00 /usr/bin/malos_wakeword
```
**NOTE:** you can stop `malos_wakeword`, for pocketsphinx tests you don't need it. It's only for installing dependencies like pocketsphinx and sphinxbase. If you want to see more info about [malos_wakeword](https://github.com/matrix-io/matrix-malos-wakeword/blob/master/README.md)

``` bash
sudo service matrixio-malos-wakeword stop
```

### Building PocketSphinx demos
``` 
git clone https://github.com/matrix-io/matrix-creator-pocketsphinx.git
cd matrix-creator-pocketsphinx
mkdir build && cd build && cmake .. && make -j $(nproc)
```

### Install testing voice commands:
Download sample language and dictionary from [here](https://drive.google.com/file/d/0B3lA7p7SjZu-YUJxYmIwcnh4Qlk/view?usp=sharing) and transfer it to your Pi on `matrix-creator-pocketsphinx/build/demos` directory and then extract it:

``` bash
mkdir assets
tar zxf TAR6706.tgz -C assets
```

**NOTE**: Optional, you can make new models [explanation below](https://github.com/matrix-io/matrix-creator-pocketsphinx#optional-custom-lenguage-and-phrases-for-recognition)

### Run DEMO:
on build/demos:
```
./pocketsphinx_demo -keyphrase "MATRIX" -kws_threshold 1e-20 -dict assets/6706.dic -lm assets/6706.lm -inmic yes -adcdev mic_channel8
``` 
- *mic_channel8* (all microphones array)
- *mic_channelX* (only X microphone)

and try it with executing commands with your voice like this: 

- `matrix everloop`
- `matrix stop`
- `matrix clear`
- ...

#### (optional) Custom lenguage and phrases for recognition 

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

