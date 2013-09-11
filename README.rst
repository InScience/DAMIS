Atviros mokslo infrastruktūros DAMIS testinė versija prieinama adresu: http://demo.damis.lt.

Aplinkos paruošimas
===================
sudo apt-get install python-numpy python-scipy python-matplotlib ipython \
	sshpass gettext python-setuptools python-pip
sudo python ez_setup.py # Jeigu pasenusi python-setuptools versija
sudo pip install ipdb
make
bin/django migrate damis

Serverio paleidimas
===================
make run



