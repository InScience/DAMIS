==========
DAMIS demo
==========
Atviros mokslo infrastruktūros DAMIS bandomoji versija, kuri prieinama adresu: http://demo.damis.lt.

Programuotojams
===============
Aplinkos paruošimas::
    sudo apt-get install python-numpy python-scipy python-matplotlib ipython
    sudo apt-get install sshpass gettext python-setuptools python-pip
    sudo pip install ipdb
    sudo python ez_setup.py   # Jeigu pasenusi python-setuptools versija
    make


Serverio paleidimas::
    make run     # Serveris pasiekiamas adresu http://127.0.0.1:8000


Duomenų bazės schemos keitimas::
    bin/django schemamigration damis --auto
    bin/django migrate damis


Testų paleidimas::
    make test                      # Įvykdomi visi testai 
    bin/django test -tTestClass    # Įvykdomas testų rinkinys TestClass
    bin/django test -mtest_create  # Įvykdomas testas test_create
