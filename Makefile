.PHONY: install run static tags

all: install start_database messages

install:
	python bootstrap.py
	bin/buildout

run:
	bin/django migrate damis
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
