.PHONY: install run static tags

all: install start_database messages

install:
	# sudo apt-get install python-numpy python-scipy python-matplotlib ipython
	python bootstrap.py
	bin/buildout

run:
	bin/django runserver

static:
	bin/django collectstatic --noinput

tags:
	bin/ctags -v

start_database:
	mkdir var || touch var/db
	bin/django syncdb --noinput

messages:
	bin/django compilemessages

clean:
	git clean -dfx

test:
	bin/django test algorithms
