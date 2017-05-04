# Pocketsphinx demo

### Dependencies 

Before, please install MALOS and perform device reboot. For more details: [Getting Started Guide](https://github.com/matrix-io/matrix-creator-quickstart/wiki/2.-Getting-Started)
```
echo "deb http://packages.matrix.one/matrix-creator/ ./" | sudo tee --append /etc/apt/sources.list
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install matrix-creator-init matrix-creator-malos cmake g++ git libzmq3-dev --no-install-recommends
reboot
```
Add some dependencies and pocketsphinx package
```
echo "deb http://unstable-packages.matrix.one/ stable main" | sudo tee -a /etc/apt/sources.list
sudo apt-get update
sudo apt-get install libblas-dev liblapack-dev pocketsphinx --no-install-recommends
```

### Building PocketSphinx demo
``` 
git clone https://github.com/carlaecomp/matrix-creator-pocketsphinx.git
cd matrix-creator-pocketsphinx
mkdir build && cd build && cmake .. && make
```
### --------------
http://www.speech.sri.com/projects/srilm/download.html
mkdir srilm
scp /home/carla/Documentos/Admobilize/srilm-1.7.2.tar.gz pi@192.168.15.29:/home/pi/matrix-creator-pocketsphinx/srilm 
cd srilm
tar xzf srilm-1.7.2.tar.gz
sudo apt-get install tcl tcl-dev csh gawk
In Makefile, uncomment the SRILM= parameter and point it to /usr/share/srilm (or your equivalent path)
criar home/tools/user
SRILM = /home/pi/matrix-creator-pocketsphinx/srilm
----
ngram-count -order 2 -interpolate -cdiscount1 0 -cdiscount2 0.5   -text train-text.txt -lm mymodel.lm
--------------------------

### Install testing voice commands:
Download sample language and dictionary from [here](https://drive.google.com/file/d/0B3lA7p7SjZu-YUJxYmIwcnh4Qlk/view?usp=sharing) or make new models (explanation below) then extract it:
```
cd demos
mkdir assets
tar xf TAR6706.tgz -C assets
```

### Run DEMO:
on build/demos:
```
./pocketsphinx_demo -keyphrase "MATRIX" -kws_threshold 1e-20 -dict assets/6706.dic -lm assets/6706.lm -inmic yes -adcdev mic_channel8
``` 
- *mic_channel8* (all microphones array)
- *mic_channelX* (only X microphone)

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

+ Dowload *TARXXXXX.tgz* and upgrade assets: 

