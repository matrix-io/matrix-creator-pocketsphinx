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
### Generate the model

#### Install srilm in your computer
```
Download in http://www.speech.sri.com/projects/srilm/download.html

If your computer is linux or mac:

* mkdir /usr/share/srilm
* mv srilm.tgz /usr/share/srilm
* cd /usr/share/srilm
* tar xzf srilm.tgz
* sudo apt-get install tcl tcl-dev csh gawk
* In Makefile, uncomment the SRILM= parameter and point it to /usr/share/srilm (or your equivalent path)

Add the following to your .bashrc
* SRILM=/usr/share/srilm
* export PATH=$PATH:$SRILM/bin:$SRILM/bin/i686-ubuntu
* export MANPATH=$SRILM/man:$MANPATH

source : http://www.spencegreen.com/2012/02/01/installing-srilm-on-ubuntu-11-10/ 
```
#### Generate the model with srilm
```
* Go to the folder where your train-text is
cd /folder/where/your/text/is
* * Your train-text should be like the train-text in the folder config
* Run the ngram-count that will generate the model
ngram-count -order 2 -interpolate -cdiscount1 0 -cdiscount2 0.5   -text train-text.txt -lm model.lm
* Move the mymodel.lm to /home/pi/matrix-creator-pocketsphinx/build/demos IN YOUR MATRIX
```

### Run DEMO:
on build/demos:
```
./pocketsphinx_demo -keyphrase "MATRIX" -kws_threshold 1e-20 -lm assets/model.lm -inmic yes -adcdev mic_channel8
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

