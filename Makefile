install:
	python bootstrap.py
	bin/buildout

run:
	bin/django runserver
