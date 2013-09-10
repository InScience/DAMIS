Atviros mokslo infrastruktūros DAMIS testinė versija prieinama adresu: http://demo.damis.lt.

Aplinkos paruošimas
===================
sudo apt-get install python-numpy python-scipy python-matplotlib ipython \
	sshpass gettext python-setuptools
sudo python ez_setup.py # Jeigu pasenusi python-setuptools versija
make
bin/django migrate damis

Serverio paleidimas
===================
make run



